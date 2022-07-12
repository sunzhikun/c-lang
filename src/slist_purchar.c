#include "slist_purchar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*************************************仅用于数据字段为purchar类型的结构体变量建立的链表*************************************/
/**********************************************
 *函数名:pur_slist_showall     			   	  *	
 *功能:输出单链表					          *	
 *参数:	head  链表头指针	   			      *	
 *返回值:									  *
 **********************************************/
void pur_slist_showall(node_pur *head)
{
	node_pur *p = head;

	while(p)
	{
		printf("\tnum=%03d\tname=%s\tprice=%.2f\tcount=%d\n",p->data.num,p->data.name,p->data.price,p->data.count);
		p = p -> next;
	}
	printf("\n");
}
/**********************************************
 *函数名:pur_slist_addtail     			   	  *	
 *功能:尾插法将数据插入到链表				  *	
 *参数:	head  链表头指针地址   			      *	
 *		data    数据段					      *	
 *返回值:-1:插入失败		   		     	  *
 *		 0:插入成功						      *
 **********************************************/
int pur_slist_addtail(node_pur **head,Data_pur data)
{
	if(!*head)
	{
		node_pur *t = (node_pur*)malloc(sizeof(node_pur));
		if(!t)
			return -1;

		t -> data = data;
		t -> next = NULL;

		*head = t;
		return 0;

	}
	node_pur *p=(node_pur*)malloc(sizeof(node_pur));
	if(!p)
		return -1;

	p -> data = data;
	p -> next = NULL;

	node_pur *q = *head;
	while(q->next)
		q= q-> next;
	
	q -> next = p;


	return 0;
}

/**********************************************
 *函数名:pur_slist_free     			   	  *	
 *功能:释放内存				  				  *	
 *参数:	head  链表头指针地址   			      *	
 *返回值:		   		     	  			  *
 *		 0:释放成功						      *
 **********************************************/
int pur_slist_free(node_pur **head)
{
	node_pur *p = *head,*q = NULL;
	while(p)
	{
		q = p;
		p = p -> next;
		free(q);
	}
	*head = NULL;
	return 0;
}
