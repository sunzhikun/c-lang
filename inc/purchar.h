#ifndef __PURCHAR_H__
#define __PURCHAR_H__

typedef struct
{
	int 		num;//产品编号
	char		name[10];//产品名称
	float		price;//产品单价
	int 		reserve;//产品库存
}goods;//库存类型的结构体变量

typedef struct
{
	int 		num;//产品编号
	char		name[10];//产品名称
	float		price;//产品单价
	int 		count;//产品数量
}purchar;//购物车类型的结构体变量

typedef struct BUYER
{
	char name[10];
	int passwd;
	float money;
}buyer;//买家付款类型的结构体变量

void showgoods();
int purchar_goods();
int update_reserve();
int updata_wallet(buyer bur,float totol);
void showgoods();
int read_file_totol();
int is_buyer(buyer bur);//判断买家用户名是否存在

#endif