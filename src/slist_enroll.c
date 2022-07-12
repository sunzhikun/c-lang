#include "slist_enroll.h"
#include "enroll.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*************************************仅用于数据字段为enroll类型的结构体变量建立的链表*************************************/
/**********************************************
 *函数名:en_slist_showall     			       	  *	
 *功能:输出单链表					          *	
 *参数:	head  链表头指针	   			      *	
 *返回值:									  *
 **********************************************/
void en_slist_showall(en_node *head)
{
	en_node *p = head;

	while(p)
	{
		printf("\tusrname = %s\tpasswd = %d\n",p->data.u_name,p->data.p_wd);
		p = p -> next;
	}
	printf("\n");
}
/**********************************************
 *函数名:en_slist_addtail     			       	  *	
 *功能:尾插法将数据插入到链表				  *	
 *参数:	head  链表头指针地址   			      *	
 *		data    数据段					      *	
 *返回值:-1:插入失败		   		     	  *
 *		 0:插入成功						      *
 **********************************************/
int en_slist_addtail(en_node **head,en_Data data)
{
	if(!*head)
	{
		en_node *t = (en_node*)malloc(sizeof(en_node));
		if(!t)
			return -1;

		t -> data = data;
		t -> next = NULL;

		*head = t;
		return 0;

	}
	en_node *p=(en_node*)malloc(sizeof(en_node));
	if(!p)
		return -1;

	p -> data = data;
	p -> next = NULL;

	en_node *q = *head;
	while(q->next)
		q= q-> next;
	
	q -> next = p;


	return 0;
}

/**********************************************
 *函数名:en_slist_free     			       	  *	
 *功能:释放内存				  				  *	
 *参数:	head  链表头指针地址   			      *	
 *返回值:		   		     	  			  *
 *		 0:释放成功						      *
 **********************************************/
int en_slist_free(en_node **head)
{
	en_node *p = *head,*q = NULL;
	while(p)
	{
		q = p;
		p = p -> next;
		free(q);
	}
	*head = NULL;
	return 0;
}

