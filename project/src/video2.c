#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ts.h"
#include "showbmp.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

//播放视频函数
int video()
{
	//显示背景图
	show_bmp("video.bmp");
	printf("video\n");
	//检测文件是否存在
	int ret = access("myfifo",F_OK);
	if(ret !=0 )
	{
		//创建管道文件
		int fifo_ret = mkfifo("myfifo",0777);
		if(fifo_ret == -1)
		{
			perror("mkfifo");
			return -1;
		}
	}

	//打开管道文件
	int fifo_fd = open("myfifo", O_RDWR);
	if(fifo_fd ==-1)
	{
		perror("open fifo");
		return -1;
	}
	
	while(1)
	{
		
		//播放区域120/190,430/480 播放视频
		if(get_x >120 && get_x <190 && get_y > 430 && get_y <480)
		{
			system("killall -9 mplayer");
			system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp4&");
			printf("player\n");
			get_x=0;get_y=0;
		}
		//暂停区域290/360,430/480 暂停播放
		else if(get_x >290 && get_x <360 && get_y > 430 && get_y <480)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("stop\n");
			get_x=0;get_y=0;
		}
		//继续区域480/550,430/480 继续播放
		else if(get_x >480 && get_x <550 && get_y > 430 && get_y <480)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("continue\n");
			get_x=0;get_y=0;
		}
		//690/800,430/480 退出播放
		else if(get_x >690 && get_x <800 && get_y > 430 && get_y <480)
		{
			system("killall -9 mplayer");
			printf("exit\n");
			get_x=0;get_y=0;
			//显示主界面图片
			show_bmp("main.bmp");
			break;
		}
		//快进
		if(slide == 1)
		{
			write(fifo_fd,"seek +5\n",strlen("seek +5\n"));
			printf("seek +5\n");
			slide = -1;
		}
			
		//快退
		if(slide == 0)
		{
			write(fifo_fd,"seek -5\n",strlen("seek -5\n"));
			printf("seek -5\n");
			slide = -1;
		}
		
		//控制音量,增加音量
		if(slide == 2)
		{
			write(fifo_fd,"volume 80 1\n",strlen("volume 80 1\n"));
			printf("volume 80\n");
			slide = -1;
			
		}
		//控制音量,降低音量
		if(slide == 3)
		{
			write(fifo_fd,"volume 40 1\n",strlen("volume 40 1\n"));
			printf("volume 40\n");
			slide = -1;
			
		}

	}
	
	return 0;
}