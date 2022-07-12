#include "slist_goods.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*************************************仅用于数据字段为goods类型的结构体变量建立的链表*************************************/
/**********************************************
 *函数名:slist_showall     			       	  *	
 *功能:输出单链表					          *	
 *参数:	head  链表头指针	   			      *	
 *返回值:									  *
 **********************************************/
void slist_showall(node *head)
{
	node *p = head;

	while(p)
	{
		printf("\tnum=%03d\tname=%s\tprice=%.2f\treserve=%d\n",p->data.num,p->data.name,p->data.price,p->data.reserve);
		p = p -> next;
	}
	printf("\n");
}
/**********************************************
 *函数名:slist_addtail     			       	  *	
 *功能:尾插法将数据插入到链表				  *	
 *参数:	head  链表头指针地址   			      *	
 *		data    数据段					      *	
 *返回值:-1:插入失败		   		     	  *
 *		 0:插入成功						      *
 **********************************************/
int slist_addtail(node **head,Data data)
{
	if(!*head)
	{
		node *t = (node*)malloc(sizeof(node));
		if(!t)
			return -1;

		t -> data = data;
		t -> next = NULL;

		*head = t;
		return 0;

	}
	node *p=(node*)malloc(sizeof(node));
	if(!p)
		return -1;

	p -> data = data;
	p -> next = NULL;

	node *q = *head;
	while(q->next)
		q= q-> next;
	
	q -> next = p;


	return 0;
}

/**********************************************
 *函数名:slist_free     			       	  *	
 *功能:释放内存				  				  *	
 *参数:	head  链表头指针地址   			      *	
 *返回值:		   		     	  			  *
 *		 0:释放成功						      *
 **********************************************/
int slist_free(node **head)
{
	node *p = *head,*q = NULL;
	while(p)
	{
		q = p;
		p = p -> next;
		free(q);
	}
	*head = NULL;
	return 0;
}
