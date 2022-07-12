#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "purchar.h"
#include "slist_goods.h"
#include "slist_purchar.h"
#include "slist_buyer.h"

/**********************************************
 *函数名:is_enough     			          	  *	
 *功能:判断库存是否充足				          *	
 *参数:	name  产品名称		   			      *	
 *		count    产品数量				      *	
 *		totol    购买的所有商品的总价		  *
 *返回值:1:商品库存充足			   		      *
 *		 0:商品库存不充足				      *
 **********************************************/
static int is_enough(const char *name,unsigned int count,float *totol)
{
	goods buy;
	float sum=0;//计算每种商品的价格
	FILE *fp = fopen("../file/goods.dat","rb");
	if(!fp)
	{
		perror("fopen goods.dat");
		return -1;
	}
	FILE *fd = fopen("../file/purchar.dat","ab");
	if(!fd)
	{
		perror("fopen purchar.dat");
		return -1;
	}
	while(fread(&buy,sizeof(goods),1,fp) == 1)//读取goods.dat文件
	{
		if(strcmp(buy.name,name)==0)//文件中有该商品
		{
			if(buy.reserve>=count)//库存充足
			{
				purchar pur;
				sum=buy.price*count;//计算每种商品的价格
				pur.num=buy.num;
				strcpy(pur.name,buy.name);
				pur.price=buy.price;
				pur.count=count;
				printf("\tnum=%03d\tname=%s\tprice=%.2f\tcount=%d\n",buy.num,buy.name,buy.price,count);//显示加入购物车的商品信息
				fwrite(&pur,sizeof(purchar),1,fd);//将购物车中的商品信息写入到purchar.dat文件中
				*totol=*totol+sum;//计算购物车中所有商品的总价
			}
			else//文件中没有该商品
			{
				fclose(fp);
				fclose(fd);
				return 0;
			}
		}
	}
	fclose(fp);
	fclose(fd);
	return -1;
}
/**********************************************
 *函数名:update_reserve     		      	  *	
 *功能:更新产品库存					          *	
 *参数:										  *
 *返回值:-1:文件打开失败			  	      *
 *		 0:更新成功						      *
 **********************************************/
int update_reserve()
{
	goods buy;
	purchar pur;
	node *head=NULL;
	FILE *fp=fopen("../file/goods.dat","rb");
	if(!fp)
	{
		perror("fopen goods.dat");
		return -1;
	}
	while(fread(&buy,sizeof(goods),1,fp)==1)
		slist_addtail(&head,buy);//将所有的数据存储在链表中，方便修改
	//slist_showall(head);
	fclose(fp);
	
	node *p=head;
	fp = fopen("../file/purchar.dat","rb");
	if(!fp)
	{
		perror("fopen purchar.dat");
		return -1;
	}
	while(fread(&pur,sizeof(purchar),1,fp)==1)
	{
		p=head;
		while(p)
		{
			if(strcmp(p -> data.name,pur.name) == 0)	//购物车中的产品名称和库存中的商品名称匹配成功
			{
				p->data.reserve=p->data.reserve-pur.count;//更新产品库存
				//printf("\tnum=%03d\tname=%s\tprice=%.2f\treserve=%d\n",p->data.num,p->data.name,p->data.price,p->data.reserve);
				break;
			}
			p = p -> next;
		}
	}
	fclose(fp);
	
	fp = fopen("../file/goods.dat","wb");
	if(!fp)
	{
		perror("fopen goods.dat");
		return -1;
	}
	p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(Data),1,fp);//将更新后的数据重新写入到库存文件中
		p=p->next;
	}
	fclose(fp);
	//showgoods();
	slist_free(&head);
	return 0;
}
/**********************************************
 *函数名:updata_wallet     		        	  *	
 *功能:更新钱包				                  *	
 *参数:									      *	
 *		totol    购买的所有商品的总价		  *
 *返回值:-1:文件打开失败			   		  *
 *		 0:更新成功				      		  *
 **********************************************/
int updata_wallet(buyer bur,float totol)
{
	FILE *fp = fopen("../file/wallet.dat","rb");
	if(!fp)
	{
		perror("fopen wallet.dat");
		return -1;
	}
	buyer rbuy;
	buy_node *head = NULL;
	while(fread(&rbuy,sizeof(buyer),1,fp))
	{
		if(strcmp(rbuy.name,bur.name) == 0&&rbuy.passwd == bur.passwd)
		{
			rbuy.money-=totol;//更新余额
			if(rbuy.money<=0)
			{
				buy_slist_free(&head);
				fclose(fp);
				return -2;
			}
		}
		buy_slist_addtail(&head,rbuy);
	}
	fclose(fp);
	fp = fopen("../file/wallet.dat","wb");
	if(!fp)
	{
		perror("fopen wallet.dat");
		return -1;
	}
	buy_node *p = head;
	while(p)
	{
		fwrite(&(p->data),sizeof(buy_Data),1,fp);//将更新后的余额重新写回文件
		p=p->next;
	}
	fclose(fp);
	buy_slist_free(&head);
	return 0;
}
/**********************************************
 *函数名:showgoods	     		        	  *	
 *功能:显示库存信息			                  *	
 *参数:									      *	
 *返回值:void			   		  			  *
 **********************************************/
void showgoods()
{
	goods buy;
	FILE *fp = fopen("../file/goods.dat","rb");
	if(!fp)
	{
		perror("fopen goods.dat");
		return;
	}
	while(fread(&buy,sizeof(goods),1,fp) == 1)
	{
		printf("\tnum=%03d\tname=%s\tprice=%.2f\treserve=%d\n",buy.num,buy.name,buy.price,buy.reserve);
	}
	fclose(fp);
	return;
}
/**********************************************
 *函数名:read_file_totol     		          *	
 *功能:读取totol.dat文件中的数据并显示        *	
 *参数:									      *	
 *返回值:-1:文件打开失败			   		  *
 *		 0:读取成功				      		  *
 **********************************************/
int read_file_totol()
{
	FILE *fp=fopen("../file/totol.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	purchar pur;
	puts("\t***********totol.dat*****************************");
	while(fread(&pur,sizeof(purchar),1,fp)==1)
		printf("\tnum=%03d\tname=%s\tprice=%.2f\tcount=%d\n",pur.num,pur.name,pur.price,pur.count);
	fclose(fp);
	return 0;
}
/**********************************************
 *函数名:file_pur_to_totol     		          *	
 *功能:将purchar.dat中的数据写入到totol.dat	  *	
 *参数:									      *	
 *返回值:-1:文件打开失败			   		  *
 *		 0:写入成功				      		  *
 **********************************************/
static int file_pur_to_totol()
{
	/*先把totol.dat的数据放置在链表中，接着读取purchar.dat里面的数据
	将purchar.dat中的数据和totol.dat中的数据进行比较，如果名字相同，
	则直接合并count数据段，否则将新数据追加写入到文件totol.dat中。*/
	purchar pur_totol,pur;
	node_pur *head=NULL,*p=NULL;
	int ass=access("../file/totol.dat",F_OK);//查看当前文件夹下是否已经存在totol.dat文件
	if(ass==-1)
		system("touch ../file/totol.dat");//没有totol.dat文件则自动创建
	FILE *fp = fopen("../file/purchar.dat","rb");
	if(!fp)
	{
		perror("fopen purchar.dat");
		return -1;
	}
	FILE *fd = fopen("../file/totol.dat","rb");
	if(!fd)
	{
		perror("fopen totol.dat189");
		return -1;
	}
	while(fread(&pur_totol,sizeof(purchar),1,fd)==1)
		pur_slist_addtail(&head,pur_totol);
	while(fread(&pur,sizeof(purchar),1,fp)==1)
	{
		p=head;
		while(p)
		{
			if(strcmp(p -> data.name,pur.name) == 0)	
			{
				p->data.count=p->data.count+pur.count;
				break;
			}
			p = p -> next;
		}
		if(!p)
			pur_slist_addtail(&head,pur);
	}
	//pur_slist_showall(head);
	fclose(fp);
	fclose(fd);
	
	fd = fopen("../file/totol.dat","wb");
	if(!fd)
	{
		perror("fopen totol.dat216");
		return -1;
	}
	
	p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(Data_pur),1,fd);
		p = p -> next;
	}
	fclose(fd);
	pur_slist_free(&head);
	read_file_totol();
	return 0;
}
/**********************************************
 *函数名:showpurchar	     		       	  *	
 *功能:显示购物车信息			              *	
 *参数:									      *	
 *返回值:void			   		  			  *
 **********************************************/
static void showpurchar()
{
	system("clear");
	puts("\t所购商品如下:");
	FILE *fp=fopen("../file/purchar.dat","rb");
	if(!fp)
	{
		perror("fopen purchar.dat");
		return;
	}
	purchar pur;
	while(fread(&pur,sizeof(purchar),1,fp)==1)
		printf("\tnum=%03d\tname=%s\tprice=%.2f\tcount=%d\n",pur.num,pur.name,pur.price,pur.count);
	fclose(fp);
	return;
}
/**********************************************
 *函数名:is_buyer	     		       	 	  *	
 *功能:判断付款账户是否存在					  *	
 *参数:	bur 付款账户类型的结构体变量		  *	
 *返回值:-1:文件打开失败			   		  *
 *		  0:用户名不存在于文件中，是新用户	  *
 *		  1:买家用户名存在于文件中，不是新用户*
 **********************************************/
int is_buyer(buyer bur)
{
	FILE *fp = fopen("../file/wallet.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	buyer rbuy;
	while(fread(&rbuy,sizeof(buyer),1,fp))
	{
		if(strcmp(rbuy.name,bur.name)==0&&rbuy.passwd == bur.passwd)//买家用户名存在于文件中，不是新用户
		{
			fclose(fp);
			return 1;
		}
	}
	//用户名不存在于文件中，是新用户
	fclose(fp);
	return 0;
}
/**********************************************
 *函数名:purchar_goods	     		       	  *	
 *功能:用户购物					              *	
 *参数:									      *	
 *返回值:0:购物成功			   		  		  *
 **********************************************/
int purchar_goods()//函数的入口在main
{
	char name[10]={0};
	buyer bur;
	unsigned int count=0;
	float totol=0;
	showgoods();
	while(1)
	{
		puts("\t请输入要买的商品名称(exit退出)：");
		printf("\t");
		scanf("%s",name);
		if(strcmp("exit",name)==0)
		{
			showpurchar();//显示加入购物车的商品信息
			printf("\t\ttotol=%.2f\n",totol);
			puts("\t请输入付款账户:");
			printf("\t");
			scanf("%s",bur.name);
			puts("\t请输入密码:");
			printf("\t");
			scanf("%d",&bur.passwd);
			if(is_buyer(bur))
			{
				if(updata_wallet(bur,totol)==0)//更新钱包
					update_reserve();//更新产品库存
				else
				{
					system("clear");
					puts("\t***************错误提示********************");
					puts("\t*                                         *");
					puts("\t*                                         *");
					puts("\t*               余额不足!                 *");
					puts("\t*             2秒之后自动跳转             *");
					puts("\t*                                         *");
					puts("\t*******************************************");
					sleep(2);
					system("clear");
					break;
				}
			}
			else
			{
				system("clear");
				puts("\t***************错误提示********************");
				puts("\t*                                         *");
				puts("\t*                                         *");
				puts("\t*               未找到该用户!             *");
				puts("\t*             2秒之后自动跳转             *");
				puts("\t*                                         *");
				puts("\t*******************************************");
				sleep(2);
				system("clear");
				break;
			}
			
			file_pur_to_totol();//将购物车中的商品信息写入到totol.dat文件中
			system("rm ../file/purchar.dat");//结账完成后删除购物车信息
			sleep(2);
			system("clear");
			break;
		}
		puts("\t请输入要买的商品数量：");
		printf("\t");
		scanf("%d",&count);
		if(is_enough(name,count,&totol))
		{	
			//显示商品名称和数量
			
		}
		else
		{
			system("clear");
			puts("\t***************错误提示********************");
			puts("\t*                                         *");
			puts("\t*                                         *");
			puts("\t*          库存不足，请重新选择！         *");
			puts("\t*             2秒之后自动跳转             *");
			puts("\t*                                         *");
			puts("\t*******************************************");
			sleep(2);
			system("clear");
		}
		continue;
	}
	return 0;
}