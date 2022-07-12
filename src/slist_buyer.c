#include "slist_goods.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slist_buyer.h"
/*************************************仅用于数据字段为buyer类型的结构体变量建立的链表*************************************/
/**********************************************
 *函数名:buy_slist_showall     			       	  *	
 *功能:输出单链表					          *	
 *参数:	head  链表头指针	   			      *	
 *返回值:									  *
 **********************************************/
void buy_slist_showall(buy_node *head)
{
	buy_node *p = head;

	while(p)
	{
		printf("\tname = %s\tpasswd = %d\tmoney = %.2f\n",p->data.name,p->data.passwd,p->data.money);
		p = p -> next;
	}
	printf("\n");
}
/**********************************************
 *函数名:buy_slist_addtail     			       	  *	
 *功能:尾插法将数据插入到链表				  *	
 *参数:	head  链表头指针地址   			      *	
 *		data    数据段					      *	
 *返回值:-1:插入失败		   		     	  *
 *		 0:插入成功						      *
 **********************************************/
int buy_slist_addtail(buy_node **head,buy_Data data)
{
	if(!*head)
	{
		buy_node *t = (buy_node*)malloc(sizeof(buy_node));
		if(!t)
			return -1;

		t -> data = data;
		t -> next = NULL;

		*head = t;
		return 0;

	}
	buy_node *p=(buy_node*)malloc(sizeof(buy_node));
	if(!p)
		return -1;

	p -> data = data;
	p -> next = NULL;

	buy_node *q = *head;
	while(q->next)
		q= q-> next;
	
	q -> next = p;


	return 0;
}

/**********************************************
 *函数名:buy_slist_free     			       	  *	
 *功能:释放内存				  				  *	
 *参数:	head  链表头指针地址   			      *	
 *返回值:		   		     	  			  *
 *		 0:释放成功						      *
 **********************************************/
int buy_slist_free(buy_node **head)
{
	buy_node *p = *head,*q = NULL;
	while(p)
	{
		q = p;
		p = p -> next;
		free(q);
	}
	*head = NULL;
	return 0;
}
