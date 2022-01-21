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
int main()
{
	//显示背景图
	show_bmp("music.bmp");
	
	 
	char *bmp_ad[5]={"55.mp3","11.mp3","44.mp3","22.mp3","33.mp3"};
	int song_num=0;
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
	printf("%d\n",fifo_fd);
	if(fifo_fd ==-1)
	{
		perror("open fifo");
		return -1;
	}
	
	//创建线程获取坐标
	pthread_t pid;
	pthread_create(&pid, NULL, (void *)get_xy, NULL);
	//初始化音量
	int vol=10;
	char volume_set[30]={0};
	char song_set[60]={0};
	sprintf(volume_set ,"volume %d 1\n",vol);
	write(fifo_fd,volume_set,strlen(volume_set));
	
	while(1)
	{
		
		//播放区域120/190,430/480 播放mp3
		if(get_x >330 && get_x <445 && get_y > 370 && get_y <460)
		{
			
			system("killall -9 mplayer");
			sprintf(volume_set ,"volume %d 1\n",vol);
	        write(fifo_fd,volume_set,strlen(volume_set));
			sprintf(song_set ,"mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 %s &",bmp_ad[song_num]);
			system(song_set);
	        // system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 22.bmp &");
			//write(fifo_fd,"get_file_name\n",strlen("get_file_name\n"));
			printf("player\n");
			//printf("%d\n",fifo_fd);
			get_x=0;get_y=0;
		}
		//暂停区域290/360,430/480 暂停播放
		else if(get_x >200 && get_x <600 && get_y > 100 && get_y <300)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("stop\n");
			get_x=0;get_y=0;
		}
		
		
		//快进
		else if(get_x >490 && get_x <582 && get_y > 370 && get_y <460)
		{
			write(fifo_fd,"seek +5\n",strlen("seek +5\n"));
			printf("seek +5\n");
			printf("%d\n",fifo_fd);
			get_x=0;get_y=0;
		}
			
		//快退
		else if( get_x >200 && get_x <285 && get_y > 370 && get_y <460)
		{
			write(fifo_fd,"seek -5 0\n",strlen("seek -5 0\n"));
			
			printf("seek -5\n");
			get_x=0;get_y=0;
		}
		//上一首
		else if(get_x >60 && get_x <145 && get_y > 370 && get_y <460)
		{
			if (song_num>0)
			{
				--song_num;
				system("killall -9 mplayer");
				sprintf(volume_set ,"volume %d 1\n",vol);
				write(fifo_fd,volume_set,strlen(volume_set));
				sprintf(song_set ,"mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 %s &",bmp_ad[song_num]);
			    system(song_set);
				write(fifo_fd,"get_file_name\n",strlen("get_file_name\n"));
				//write(fifo_fd,"volume 5 1 \n",strlen("volume 5 1 \n"));
				printf("player\n");
				get_x=0;get_y=0;

			}
			else  song_num=0;
		}
			
		//下一首
		else if(get_x >630 && get_x <710 && get_y > 370 && get_y <460)
		{
			if (song_num<4)
			{
			    song_num++;
				system("killall -9 mplayer");
				sprintf(volume_set ,"volume %d 1\n",vol);
				write(fifo_fd,volume_set,strlen(volume_set));
				sprintf(song_set ,"mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 %s &",bmp_ad[song_num]);
				system(song_set);
				write(fifo_fd,"get_file_name\n",strlen("get_file_name\n"));
				//write(fifo_fd,"volume 5 1 \n",strlen("volume 5 1 \n"));
				printf("player\n");
				get_x=0;get_y=0;;
			}
			else song_num=4;
			
		}
		//控制音量,增加音量
		else if(slide == 2 && get_x >710 && get_x <770 && get_y > 90 && get_y <300)
		{
			if(vol<100)
			{ 
		        vol=vol+5;
				sprintf(volume_set ,"volume %d 1\n",vol);
				write(fifo_fd,volume_set,strlen(volume_set));
				printf("%s\n",volume_set);
			    get_x=0;get_y=0;
				//slide = -1;
			}
			else vol =100;
			
			
		}
		//控制音量,降低音量
		else if(slide == 3 && get_x >710 && get_x <770 && get_y > 90 && get_y <300)
		{
			if(vol>0)
			{
				vol=vol-5;
				sprintf(volume_set,"volume %d 1\n",vol);
				write(fifo_fd,volume_set,strlen(volume_set));
				printf("%s\n",volume_set);
				get_x=0;get_y=0;
				//slide = -1;
			}
		    else vol =0;	
		}
		//690/800,430/480 退出播放
		if(get_x >710 && get_x <770 && get_y > 10 && get_y <50)
		{
			system("killall -9 mplayer");
			printf("exit\n");
			show_bmp("jiemian.bmp");
			get_x=0;get_y=0;
			break;
		}

	}
	
	return 0;
}