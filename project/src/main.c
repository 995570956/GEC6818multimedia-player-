#include <stdio.h>
#include "showbmp.h"
#include "ts.h"
#include <pthread.h>


//arm-linux-gcc main.c showbmp.c ts.c video2.c -o project -lpthread
int main()
{
	//登录界面
	//login();
	//显示主界面图片
	show_bmp("main.bmp");
	//创建线程获取坐标
	pthread_t pid;
	pthread_create(&pid, NULL, (void *)get_xy, NULL);
	//根据点击坐标选择不同的功能
	while(1)
	{

		
		//相册
		if(get_x >70 && get_x < 230 && get_y >170 && get_y <280)
		{
			photo()；
			printf("photo\n");
		}
			
		//音乐
		if(get_x >340 && get_x < 520 && get_y >170 && get_y <280)
		{
			printf("music\n");
		}
		
		//视频
		if(get_x >580 && get_x < 750 && get_y >170 && get_y <280)
		{
			video();
		}
	}
	
	
}