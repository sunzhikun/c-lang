#include "msginfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "enroll.h"
#include "slist_enroll.h"
/**********************************************
 *				添加用户				      *	
 **********************************************/
/**********************************************
 *函数名:is_newusr     			          	  *	
 *功能:判断是否是新管理员账号			      *	
 *参数:	usr_name  管理员账号   			      *		
 *返回值:1:此用户是管理员		   		      *
 *		 0:此用户不是管理员				      *
 **********************************************/
static int is_newusr(const char *usrname)
{
	FILE *fp = fopen("../file/enroll.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	enroll en;
	while(fread(&en,sizeof(enroll),1,fp))
	{
		if(strcmp(usrname,en.u_name)==0)//用户名存在于文件中，不是新用户
		{
			fclose(fp);
			return 0;
		}
	}
	//用户名不存在于文件中，是新用户
	fclose(fp);
	return 1;
}
/**********************************************
 *函数名:add_newusr     			       	  *	
 *功能:判断要添加的用户名是否存在于enroll.dat中*	
 *参数:	enew  要添加的用户结构体   			  *	
 *返回值:1:用户名不存在于文件中		   	      *
 *		 0:用户名存在于文件中			      *
 **********************************************/
static int add_newusr(enroll enew)
{
	FILE *fp = fopen("../file/enroll.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	enroll en;//用来临时存储从enroll.dat中读取到的数据
	en_node *head=NULL;//用来建立链表
	while(fread(&en,sizeof(enroll),1,fp))//将读取到的数据存储在链表中
		en_slist_addtail(&head,en);
	//puts("\t*************add_goods**********");
	//en_slist_showall(head);
	fclose(fp);
	en_node *p=head;
	en_slist_addtail(&head,enew);//将新用户存储在链表最后的位置
	puts("\t*************add_usr**********");
	en_slist_showall(head);//将链表输出，判断是否正确
	fp = fopen("../file/enroll.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(en_Data),1,fp);//将链表中的数据全部写入到enroll.dat文件中
		p=p->next;
	}
	en_slist_free(&head);
	fclose(fp);
	return 0;
}
/**********************************************
 *函数名:add_usr     				       	  *	
 *功能:添加用户								  *	
 *参数:							  			  *	
 *返回值:							   	      *
 *		 0:添加成功						      *
 **********************************************/
int add_usr()
{
	system("clear");
	enroll en;
	//while(1)
	//{
		puts("\t请输入要添加的用户名:");
		printf("\t");
		scanf("%s",en.u_name);
		if(is_newusr(en.u_name))//要添加的用户是新用户
		{
			puts("\t请输入要添加的用户密码:");
			printf("\t");
			scanf("%d",&en.p_wd);
			add_newusr(en);//将新用户添加到文件中
			puts("\t添加成功！");
			sleep(3);
		}
		else//要添加的用户不是新用户
		{
			puts("\t此用户名已存在！");
			sleep(3);
		}
	//}
	return 0;
}
/**********************************************
 *				修改用户				      *	
 **********************************************/
/**********************************************
 *函数名:change_usr     			       	  *	
 *功能:修改文件中的用户信息				      *	
 *参数:	en  账号信息		   			      *		
 *返回值:-1:文件打开失败		   		      *
 *		 0:修改成功						      *
 **********************************************/
static int change_usr(enroll en)
{
	FILE *fp = fopen("../file/enroll.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	enroll en_list;//用来临时存储从enroll.dat中读取到的数据
	en_node *head=NULL;//用来建立链表
	while(fread(&en_list,sizeof(enroll),1,fp))//将读取到的数据存储在链表中
		en_slist_addtail(&head,en_list);
	fclose(fp);
	en_node *p = head;
	while(p)
	{
		if(strcmp((p -> data).u_name,en.u_name) == 0)//在链表中找到了该用户名
		{
			(p -> data).p_wd = en.p_wd;//修改该用户名的密码
			break;
		}
		p = p -> next;
	}
	fp = fopen("../file/enroll.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(en_Data),1,fp);//将链表中的数据全部写入到enroll.dat文件中
		p=p->next;
	}
	en_slist_free(&head);
	fclose(fp);
	return 0;
}
/**********************************************
 *函数名:ch_usr     			  	     	  *	
 *功能:修改用户信息						      *	
 *参数:						   			      *		
 *返回值:-1:用户不存在			   		      *
 *		 0:修改成功						      *
 **********************************************/
int ch_usr()
{
	enroll en;
	system("clear");
	puts("\t请输入要修改的用户名:");
	printf("\t");
	scanf("%s",en.u_name);
	if(is_newusr(en.u_name))//要修改的用户是新用户
	{
		puts("\t此用户不存在！");
		sleep(3);
		return -1;
	}
	else 
	{
		puts("\t请输入要修改的用户密码：");
		printf("\t");
		scanf("%d",&en.p_wd);
		change_usr(en);
		puts("\t修改成功！");
		sleep(3);
		return 0;
	}
}
/**********************************************
 *				查询用户				      *	
 **********************************************/
/**********************************************
 *函数名:sel_usr     				       	  *	
 *功能:查询用户							      *	
 *参数:						   			      *		
 *返回值:-1:文件打开失败		   		      *
 *		 0:查询成功						      *
 **********************************************/
int sel_usr()
{
	system("clear");
	FILE *fp = fopen("../file/enroll.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	enroll en;
	puts("\t************查询账户信息如下******************");
	while(fread(&en,sizeof(enroll),1,fp))
		printf("\tusrname = %s,passwd = %d\n",en.u_name,en.p_wd);
	puts("");
	fclose(fp);
	sleep(10);
	return 0;
}
/**********************************************
 *				删除用户				      *	
 **********************************************/
/**********************************************
 *函数名:del_usr     				       	  *	
 *功能:删除用户							      *	
 *参数:						   			      *		
 *返回值:-1:文件打开失败或用户信息不存在	  *
 *		 0:删除成功						      *
 **********************************************/
int del_usr()
{
	system("clear");
	char usrname[10];
	puts("\t请输入要删除的用户名:");
	printf("\t");
	scanf("%s",usrname);
	FILE *fp = fopen("../file/enroll.dat","rb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	enroll en_list;//用来临时存储从enroll.dat中读取到的数据
	en_node *head=NULL;//用来建立链表
	int flag =0;
	while(fread(&en_list,sizeof(enroll),1,fp))//将读取到的数据存储在链表中
	{
		if(strcmp(en_list.u_name,usrname) == 0)
		{
			flag = 1;
			continue;
		}
		en_slist_addtail(&head,en_list);
	}
	fclose(fp);
	system("clear");
	puts("\t********************");
	if(flag == 0)
	{
		puts("\t此用户不存在！");
		sleep(3);
		return -1;
	}
	en_slist_showall(head);
	fp = fopen("../file/enroll.dat","wb");
	if(!fp)
	{
		perror("fopen");
		return -1;
	}
	en_node *p=head;
	while(p)
	{
		fwrite(&(p->data),sizeof(en_Data),1,fp);//将链表中的数据全部写入到enroll.dat文件中
		p=p->next;
	}
	en_slist_free(&head);
	fclose(fp);
	puts("\t删除成功！");
	sleep(3);
	return 0;
}