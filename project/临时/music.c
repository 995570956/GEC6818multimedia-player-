#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ts.h"
#include "showbmp.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


char music_path[3][32] = {"1.mp3", "2.mp3", "3.mp3"};

//播放视频函数
int music()
{
	
	pid_t pid;
	//显示背景图
	show_bmp("1.bmp");
	printf("music\n");
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
		
		//播放区域120/190,430/480 播放音乐
		if(get_x >700 && get_x <780 && get_y > 10 && get_y <80)
		{
			system("killall -9 mplayer");
			system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp4&");
			printf("player\n");
			get_x=0;get_y=0;
		}
		//暂停区域290/360,430/480 暂停播放
		else if(get_x >700 && get_x <780 && get_y > 100 && get_y <170)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("stop\n");
			get_x=0;get_y=0;
		}
		//继续区域480/550,430/480 继续播放
		else if(get_x >700 && get_x <780 && get_y > 190 && get_y <260)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("continue\n");
			get_x=0;get_y=0;
		}
		//690/800,430/480 退出播放
		else if(get_x >10 && get_x <60 && get_y > 10 && get_y <60)
		{
			system("killall -9 mplayer");
			printf("exit\n");
			get_x=0;get_y=0;
			//显示主界面图片
			show_bmp("main.bmp");
			break;
		}
		
		//下一首
		if(get_x >700 && get_x <780 && get_y > 290 && get_y <350)
		{
			pid = fork();	//子进程
			if(pid == 0)	//子进程执行部分-->播放下标为i的音乐
			{
				execl("/usr/bin/madplay", "madplay", music_path[i], NULL);
			}
		
		}
		//点击上一首
		if(get_x >700 && get_x <780 && get_y > 380 && get_y <450)
		{
			//结束当前这一首,然后播放下一首
			kill(pid, SIGKILL);
			i++;
			if(i >2)
				i = 0;
			
			pid = fork();	//子进程
			if(pid == 0)	//子进程执行部分-->播放下标为i的音乐
			{
				execl("/usr/bin/madplay", "madplay", music_path[i], NULL);
			}			
//功能拓展： 列表循环播放(父进程使用wait), 随机播放下一首。
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
		if(get_x >650 && get_x <700 && get_y > 140 && get_y <190)
		{
			write(fifo_fd,"volume 80 1\n",strlen("volume 80 1\n"));
			printf("volume 80\n");

			
		}
		//控制音量,降低音量
		if(get_x >650 && get_x <700 && get_y > 250 && get_y <290)
		{
			write(fifo_fd,"volume 40 1\n",strlen("volume 40 1\n"));
			printf("volume 40\n");
			
		}

	}
	
	return 0;
}