#ifndef __ENROLL_H__
#define __ENROLL_H__

typedef struct
{
	char u_name[10];
	int p_wd;
}enroll;//用来存储登录的用户名和密码的结构体

int is_msg(int sel_menu,const char *usr_name,const int passwd);//判断是否是管理员
int add_goods();//添加goods.dat文件中不存在的新商品
int goods_newadd();//添加商品
int bill_print();//账目清算
int bill_sort();//显示售卖商品的情况
int add_money();//账户充值
void show_buyer();//显示账户信息


#endif