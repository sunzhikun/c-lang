#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "menu.h"
#include "enroll.h"
#include "purchar.h"
#include "msginfo.h"

int main()
{
	unsigned int sel_menu,passwd = 0;
	char usr_name[10]={0};
	system("clear");
	int ass=access("../file/totol.dat",F_OK);//查看当前文件夹下是否已经存在totol.dat文件
	if(ass==-1)
		system("touch ../file/totol.dat");//没有totol.dat文件则自动创建
	ass=access("../file/enroll.dat",F_OK);//查看当前文件夹下是否已经存在enroll.dat文件
	if(ass==-1)
		system("touch ../file/enroll.dat");//没有enroll.dat文件则自动创建
	ass=access("../file/purchar.dat",F_OK);//查看当前文件夹下是否已经存在purchar.dat文件
	if(ass==-1)
		system("touch ../file/purchar.dat");//没有purchar.dat文件则自动创建
	ass=access("../file/wallet.dat",F_OK);//查看当前文件夹下是否已经存在wallet.dat文件
	if(ass==-1)
		system("touch ../file/wallet.dat");//没有wallet.dat文件则自动创建
	ass=access("../file/goods.dat",F_OK);//查看当前文件夹下是否已经存在goods.dat文件
	if(ass==-1)
		system("touch ../file/goods.dat");//没有goods.dat文件则自动创建
	while(1)
	{
		menu();
		puts("\t请输入要选择的功能菜单:");
		printf("\t");
		scanf("%d",&sel_menu);
		if(sel_menu == 0)
		{
			system("clear");
			break;
		}
		else if(sel_menu == 1)
		{
			//顾客购物
			system("clear");
			purchar_goods();
		}
		else if(sel_menu == 2)
		{
			//后台登陆
			system("clear");
			puts("\t-----------登录-----------");
			puts("\t请输入账号:");
			printf("\t");
			scanf("%s",usr_name);
			puts("\t请输入密码:");
			printf("\t");
			scanf("%d",&passwd);
			if(is_msg(sel_menu,usr_name,passwd))
			{
				//登陆成功
				system("clear");
				puts("\t***************登陆成功********************");
				puts("\t*                                         *");
				puts("\t*                                         *");
				puts("\t*          欢迎使用后台管理系统           *");
				puts("\t*             2秒之后自动跳转             *");
				puts("\t*                                         *");
				puts("\t*******************************************");
				sleep(2);
				system("clear");
				while(1)
				{
					enroll_menu();
					puts("\t请输入要选择的功能菜单:");
					printf("\t");
					scanf("%d",&sel_menu);
					if(sel_menu == 0)
					{
						system("clear");
						break;
					}
					else if(sel_menu == 1)//添加商品
					{
						goods_newadd();
					}
					else if(sel_menu == 2)//账目清算
					{
						system("clear");
						bill_print();
					}
					else if(sel_menu == 3)//售卖商品情况
					{
						system("clear");
						bill_sort();
					}
					else if(sel_menu == 4)//账户充值
					{
						system("clear");
						add_money();
					}
					else if(sel_menu == 5)//显示账户信息
					{
						system("clear");
						show_buyer();
					}
					else
					{
						system("clear");
						puts("\t***************错误提示********************");
						puts("\t*                                         *");
						puts("\t*                                         *");
						puts("\t*          输入错误，请重新输入！         *");
						puts("\t*             2秒之后自动跳转             *");
						puts("\t*                                         *");
						puts("\t*******************************************");
						sleep(2);
						system("clear");
					}
				}
			}
			else//登陆失败
			{
				system("clear");
				puts("\t***************登陆失败********************");
				puts("\t*                                         *");
				puts("\t*                                         *");
				puts("\t*          请重新登陆后台管理系统         *");
				puts("\t*             2秒之后自动跳转             *");
				puts("\t*                                         *");
				puts("\t*******************************************");
				sleep(2);
				system("clear");
			}
		}
		else if(sel_menu == 3)
		{
			//管理员登陆
			system("clear");
			puts("\t-----------登录-----------");
			puts("\t请输入账号:");
			printf("\t");
			scanf("%s",usr_name);
			puts("\t请输入密码:");
			printf("\t");
			scanf("%d",&passwd);
			if(is_msg(sel_menu,usr_name,passwd))
			{
				//登陆成功
				system("clear");
				puts("\t***************登陆成功********************");
				puts("\t*                                         *");
				puts("\t*                                         *");
				puts("\t*          欢迎使用管理员系统             *");
				puts("\t*             2秒之后自动跳转             *");
				puts("\t*                                         *");
				puts("\t*******************************************");
				sleep(2);
				system("clear");
				while(1)
				{
					msg_menu();
					puts("\t请输入要选择的功能菜单:");
					printf("\t");
					scanf("%d",&sel_menu);
					if(sel_menu == 0)
					{
						system("clear");
						break;
					}
					else if(sel_menu == 1)//添加账户
					{
						add_usr();
						system("clear");
					}
					else if(sel_menu == 2)//修改账户
					{
						system("clear");
						ch_usr();
						system("clear");
					}
					else if(sel_menu == 3)//查询账户
					{
						system("clear");
						sel_usr();
						system("clear");
					}
					else if(sel_menu == 4)//删除账户
					{
						del_usr();
						system("clear");
					}
					else
					{
						system("clear");
						puts("\t***************错误提示********************");
						puts("\t*                                         *");
						puts("\t*                                         *");
						puts("\t*          输入错误，请重新输入！         *");
						puts("\t*             2秒之后自动跳转             *");
						puts("\t*                                         *");
						puts("\t*******************************************");
						sleep(2);
						system("clear");
					}
				}
			}
			else//登陆失败
			{
				system("clear");
				puts("\t***************登陆失败********************");
				puts("\t*                                         *");
				puts("\t*                                         *");
				puts("\t*          请重新登陆管理员系统           *");
				puts("\t*             2秒之后自动跳转             *");
				puts("\t*                                         *");
				puts("\t*******************************************");
				sleep(2);
				system("clear");
			}
		}
		else
		{
			system("clear");
			puts("\t***************错误提示********************");
			puts("\t*                                         *");
			puts("\t*                                         *");
			puts("\t*          输入错误，请重新输入！         *");
			puts("\t*             2秒之后自动跳转             *");
			puts("\t*                                         *");
			puts("\t*******************************************");
			sleep(2);
			system("clear");
			continue;
		}
	}
	return 0;
}