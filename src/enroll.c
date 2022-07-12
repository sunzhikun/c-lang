#include "enroll.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "purchar.h"
#include "slist_goods.h"
#include "slist_purchar.h"
#include "get_time.h"
#include "slist_buyer.h"

/**********************************************
 *函数名:is_msg     			          	  *	
 *功能:判断是否是管理员				          *	
 *参数:	usr_name  管理员账号   			      *	
 *		passwd    管理员密码			      *	
 *返回值:1:此用户是管理员		   		      *
 *		 0:此用户不是管理员				      *
 **********************************************/
int is_msg(int sel_menu,const char *usr_name,const int passwd)
{
	if(sel_menu == 2)
	{
		FILE *fp = fopen("../file/enroll.dat","rb");
		if(!fp)
		{
			perror("fopen");
			return -1;
		}
		enroll buff;
		while(fread(&buff,sizeof(enroll),1,fp) == 1)
		{
			if(strcmp(buff.u_name,usr_name)==0&&passwd==buff.p_wd)//判断用户名和密码是否匹配
			{
				//登陆成功
				fclose(fp);
				return 1;
			}
		}
		fclose(fp);
		return 0;
	}
	if(sel_menu == 3)
	{
		if(strcmp(usr_name,"chen") == 0 && passwd == 123456)
			return 1;
		else
			return 0;
	}
	return 0;
}
/**********************************************
 *				添加商品				      *	
 **********************************************/
/**********************************************
 *函数名:is_new     			          	  *	
 *功能:判断要添加的商品名是否存在于goods.dat中*	
 *参数:	name  要添加的商品名称   			  *	
 *返回值:1:商品名不存在于文件中		   	      *
 *		 0:商品名存在于文件中			      *
 **********************************************/
int is_new(const char *name)
{
	FILE *fp = fopen("../file/goods.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	goods buy;
	while(fread(&buy,sizeof(goods),1,fp))
	{
		if(strcmp(name,buy.name)==0)//商品名存在于文件中，不是新商品
		{
			fclose(fp);
			return 0;
		}
	}
	//商品名不存在于文件中，是新商品
	fclose(fp);
	return 1;
}
/**********************************************
 *函数名:update_goods     			       	  *	
 *功能:更新已经存在的商品的库存				  *	
 *参数:	name  要更新库存的商品名称   		  *	
 *		count 添加的数量					  *
 *返回值:-1:文件打开失败			   	      *
 *		 0:更新成功						      *
 **********************************************/
int update_goods(const char *name,int count)
{
	FILE *fp = fopen("../file/goods.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	goods buy;
	node *head=NULL;
	while(fread(&buy,sizeof(goods),1,fp))//将文件goods.dat中的商品信息全部读出来
		slist_addtail(&head,buy);//将读出来的数据全部插入到链表中
	fclose(fp);
	puts("\t*********update_goods**********");
	node *p=head;
	while(p)//遍历链表
	{
		if(strcmp(name,p->data.name)==0)//p指针指向要更新数据的节点
			p->data.reserve=p->data.reserve+count;//更新库存信息
		p=p->next;
	}
	slist_showall(head);//输出链表中更新后的数据，判断是否正确
	fp = fopen("../file/goods.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(Data),1,fp);//将链表中的数据写入到goods.dat文件中
		p=p->next;
	}
	fclose(fp);
	slist_free(&head);
	return 0;
}
/**********************************************
 *函数名:add_goods	     			       	  *	
 *功能:添加goods.dat文件中不存在的新商品	  *	
 *参数:	by goods类型的结构体变量    		  *	
 *返回值:-1:文件打开失败			   	      *
 *		 0:更新成功						      *
 **********************************************/
int add_goods(goods by)
{
	FILE *fp = fopen("../file/goods.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	goods buy;//用来临时存储从goods.dat中读取到的数据
	node *head=NULL;//用来建立链表
	while(fread(&buy,sizeof(goods),1,fp))//将读取到的数据存储在链表中
		slist_addtail(&head,buy);
	//puts("\t*************add_goods**********");
	//slist_showall(head);
	fclose(fp);
	node *p=head,*q=NULL;
	while(p)
	{
		q=p;
		p=p->next;
	}
	by.num=q->data.num+1;//商品的编号设置为链表最后一个元素的编号+1，用以自动生成编号
	slist_addtail(&head,by);//将新商品存储在链表最后的位置
	puts("\t*************add_goods**********");
	slist_showall(head);//将链表输出，判断是否正确
	fp = fopen("../file/goods.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(Data),1,fp);//将链表中的数据全部写入到goods.dat文件中
		p=p->next;
	}
	slist_free(&head);
	fclose(fp);
	return 0;
}
/**********************************************
 *函数名:goods_newadd	     			   	  *	
 *功能:添加商品	  							  *	
 *参数:	 						    		  *	
 *返回值:							   	      *
 *		 0:添加成功						      *
 **********************************************/
int goods_newadd()//函数的入口在main
{
	system("clear");
	goods buy;//用以存储新商品的信息，包括编号、名称、单价和库存
	while(1)
	{
		puts("\t请输入要添加的商品名称(exit退出):");
		printf("\t");
		scanf("%s",buy.name);
		if(strcmp("exit",buy.name)==0)
		{
			system("clear");
			break;
		}
		if(is_new(buy.name))//要添加的商品是新商品
		{
			puts("\t请输入要添加的商品单价:");
			printf("\t");
			scanf("%f",&buy.price);
			puts("\t请输入要添加的商品数量:");
			printf("\t");
			scanf("%d",&buy.reserve);
			add_goods(buy);//将新商品添加到文件中
		}
		else//要添加的商品不是新商品
		{
			puts("\t请输入要添加的商品数量:");
			printf("\t");
			scanf("%d",&buy.reserve);
			update_goods(buy.name,buy.reserve);//只需要更新对应商品名称的商品库存
			puts("\t*****************添加成功*******************");
		}
	}
	return 0;
}

/**********************************************
 *				账目清算				      *	
 **********************************************/
/**********************************************
 *函数名:bill_print	     			   	      *	
 *功能:将totol.dat中的数据输出并计算总销售额  *	
 *参数:	 						    		  *	
 *返回值:							   	      *
 *		 0:显示成功						      *
 **********************************************/
int bill_print()
{
	FILE *fp=fopen("../file/totol.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	purchar pur;
	float totol=0;//用以存储销售额
	puts("\t***********totol.dat****************************");
	char *current_time = get_time();		//获取当前系统时间
	printf("\t\t");
	puts(current_time);						//将获取的系统时间显示在屏幕上
	while(fread(&pur,sizeof(purchar),1,fp)==1)//读取totol.dat文件中的信息
	{
		totol=totol+pur.price*pur.count;//更新销售额
		printf("\tnum=%03d\tname=%s\tprice=%.2f\tcount=%d\n",pur.num,pur.name,pur.price,pur.count);
	}
	printf("\t\t\t\ttotol=%.2f\n",totol);//将最后的销售额输出
	fclose(fp);
	puts("\t*****************10秒之后自动跳转***************");
	sleep(10);
	system("clear");
	return 0;
}
/**********************************************
 *				售卖商品情况			      *	
 **********************************************/
/**********************************************
 *函数名:bubble_sort	     			      *	
 *功能:冒泡排序								  *	
 *参数:	 a:要排序的结构体数组				  *
 *	     n:结构体数组的大小					  *
 *返回值:							   	      *
 *		 0:排序成功						      *
 **********************************************/
static int bubble_sort(purchar *a,int n)
{
	purchar t;
	register int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<=i;j++)
		{
			if(a[i].count>a[j].count)//按照结构体中的count字段进行排序
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}			
	}
	return 0;
}
/**********************************************
 *函数名:bill_sort   	     			      *	
 *功能:读取文件totol.dat中的数据并按count字段 *
 *	   从大到小排序							  *
 *参数:	 									  *
 *返回值:-1:文件打开失败			   	      *
 *		 0:排序成功						      *
 **********************************************/
int bill_sort()
{
	FILE *fp=fopen("../file/totol.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	node_pur *head=NULL;
	purchar pur;
	int ct=0;//用以记录数据个数
	while(fread(&pur,sizeof(purchar),1,fp)==1)
	{
		pur_slist_addtail(&head,pur);
		ct++;//每读取一个数据，ct+1
	}
	fclose(fp);
	purchar pchar[ct];//创建一个能存放ct个元素的数组用于排序
	node_pur *p=head;
	int i=0;
	while(p)//将链表中的数据全部存储到数组中
	{
		pchar[i].num=p->data.num;
		strcpy(pchar[i].name,p->data.name);
		pchar[i].price=p->data.price;
		pchar[i].count=p->data.count;
		p=p->next;
		i++;
	}
	pur_slist_free(&head);
	bubble_sort(pchar,ct);//对数组进行冒泡排序
	fp=fopen("../file/totol.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	for(i=0;i<ct;i++)
		fwrite(&pchar[i],sizeof(purchar),1,fp);//将排序后的数组元素一一存储到totol.dat文件中
	fclose(fp);
	char *current_time = get_time();		//获取当前系统时间
	printf("\t\t");
	puts(current_time);						//将获取的系统时间显示在屏幕上
	read_file_totol();//将totol.dat文件中的数据输出
	puts("\t*****************10秒之后自动跳转***************");
	sleep(10);
	system("clear");
	return 0;
}
/**********************************************
 *函数名:update_money   	     		      *	
 *功能:更新钱包中的余额						  *
 *参数:	buy:账户类型结构体					  *
 *返回值:-1:文件打开失败			   	      *
 *		 0:充值成功						      *
 **********************************************/
static int update_money(buyer buy)
{
	FILE *fp=fopen("../file/wallet.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	buy_node *head=NULL;
	buyer rbuy;
	while(fread(&rbuy,sizeof(buyer),1,fp))
	{
		if(strcmp(rbuy.name,buy.name)==0&&rbuy.passwd == buy.passwd)//找到要更新余额的账户
			rbuy.money += buy.money;
		buy_slist_addtail(&head,rbuy);
	}
	fclose(fp);
	fp=fopen("../file/wallet.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	buy_node *p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(buy_Data),1,fp);
		p = p -> next;
	}
	fclose(fp);
	buy_slist_free(&head);
	return 0;
}
/**********************************************
 *函数名:creat_buyer   	     			      *	
 *功能:创建账户								  *
 *参数:	buy:账户类型结构体					  *
 *返回值:-1:文件打开失败				      *
 *		 0:创建成功						      *
 **********************************************/
static int creat_buyer(buyer buy)
{
	FILE *fp=fopen("../file/wallet.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	buy_node *head=NULL;
	buyer rbuy;
	while(fread(&rbuy,sizeof(buyer),1,fp))
		buy_slist_addtail(&head,rbuy);
	buy.money = 0.0f;
	buy_slist_addtail(&head,buy);
	fclose(fp);
	fp=fopen("../file/wallet.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	buy_node *p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(buy_Data),1,fp);
		p = p -> next;
	}
	fclose(fp);
	buy_slist_free(&head);
	return 0;
}
/**********************************************
 *函数名:add_money   	     			      *	
 *功能:账户充值								  *
 *参数:	 									  *
 *返回值:							   	      *
 *		 0:充值成功						      *
 **********************************************/
int add_money()
{
	buyer buy;
	while(1)
	{
		puts("\t请输入要充值的账户:");
		printf("\t");
		scanf("%s",buy.name);
		puts("\t请输入要充值的账户密码:");
		printf("\t");
		scanf("%d",&buy.passwd);
		if(is_buyer(buy))
		{
			break;
		}
		else
		{
			puts("\t未找到该用户!");
			creat_buyer(buy);//创建用户
			puts("\t创建用户完成！");
			sleep(3);
			break;
		}
	}
	puts("\t请输入要充值的数量:");
	printf("\t");
	scanf("%f",&buy.money);
	update_money(buy);
	system("clear");
	return 0;
}
/**********************************************
 *函数名:show_buyer   	     			      *	
 *功能:显示账户信息							  *
 *参数:	 									  *
 *返回值:							   	      *
 **********************************************/
void show_buyer()
{
	FILE *fp=fopen("../file/wallet.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return;
	}
	buyer rbuy;
	puts("\t****************账户信息******************");
	while(fread(&rbuy,sizeof(buyer),1,fp))
		printf("\tname = %s\tpasswd = %d\tmoney =%.2f\n",rbuy.name,rbuy.passwd,rbuy.money);
	printf("\n");
	fclose(fp);
	puts("\t*****************10秒之后自动跳转*********");
	sleep(10);
	system("clear");
}