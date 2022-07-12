#ifndef __SLIST_PURCHAR_H__
#define __SLIST_PURCHAR_H__
/*************************************仅用于数据字段为purchar类型的结构体变量建立的链表*************************************/
#include "purchar.h"

typedef purchar Data_pur;

typedef struct NODE
{
	Data_pur 	     data;
	struct NODE *next; 
}node_pur;

int pur_slist_addtail(node_pur **head,Data_pur data);
void pur_slist_showall(node_pur *head);
int pur_slist_free(node_pur **head);

#endif
