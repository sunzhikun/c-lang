#include <stdio.h>
#include <time.h>
#include "get_time.h"
/**********************************************
 *函数名:get_time   			          	  *	
 *功能:获取系统时间  				          *	
 *参数:	void							      *	
 *返回值:strtime:获取到的系统时间		   	  *
 **********************************************/
char *get_time()
{
	time_t timep;
	time(&timep);
	//struct tm *t = localtime(&timep);
	char *strtime = ctime(&timep);
	return strtime;
}