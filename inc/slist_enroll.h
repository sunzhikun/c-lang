#ifndef __SLIST_ENROLL_H__
#define __SLIST_ENROLL_H__
/*************************************仅用于数据字段为enroll类型的结构体变量建立的链表*************************************/
#include "enroll.h"

typedef enroll en_Data;

typedef struct Node
{
	en_Data 	     data;
	struct Node *next; 
}en_node;

int en_slist_addtail(en_node **head,en_Data data);
void en_slist_showall(en_node *head);
int en_slist_free(en_node **head);
#endif
