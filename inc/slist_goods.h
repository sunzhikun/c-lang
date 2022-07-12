#ifndef __SLIST_GOODS_H__
#define __SLIST_GOODS_H__
/*************************************仅用于数据字段为goods类型的结构体变量建立的链表*************************************/
#include "purchar.h"

typedef goods Data;

typedef struct Node
{
	Data 	     data;
	struct Node *next; 
}node;

int slist_addtail(node **head,Data data);
void slist_showall(node *head);
int slist_free(node **head);

#endif
