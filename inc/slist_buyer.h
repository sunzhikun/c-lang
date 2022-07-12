#ifndef __SLIST_BUYER_H__
#define __SLIST_BUYER_H__
/*************************************仅用于数据字段为buyer类型的结构体变量建立的链表*************************************/
#include "purchar.h"

typedef buyer buy_Data;

typedef struct buy_Node
{
	buy_Data 	     data;
	struct buy_Node *next; 
}buy_node;

int buy_slist_addtail(buy_node **head,buy_Data data);
void buy_slist_showall(buy_node *head);
int buy_slist_free(buy_node **head);

#endif
