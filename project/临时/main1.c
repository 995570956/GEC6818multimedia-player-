#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ts.h"
#include "showbmp.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


#include <signal.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>


int pos=0;
int ret;
int fifo_ret;
int fifo_fd;

int video();
int music();
int photo();

int main()
{
	show_bmp("main.bmp");//显示背景图
	//检测文件是否存在
	ret = access("myfifo",F_OK);
	if(ret !=0 )
	{
		//创建管道文件
		fifo_ret = mkfifo("myfifo",0777);
		if(fifo_ret == -1)
		{
		perror("mkfifo");return -1;
		}
	}
	fifo_fd = open("myfifo", O_RDWR);//打开管道文件
	if(fifo_fd ==-1)
	{
	perror("open fifo"); return -1;
	}
	
	//创建线程获取坐标
	pthread_t pid;
	pthread_create(&pid, NULL, (void *)get_xy, NULL);

	while(1)
	{
	   if(get_x >560&& get_x <800 && get_y > 50 && get_y <430)
	   { 
         get_x=0;get_y=0;
         video(); 
		 get_x=0;get_y=0;
       }
	   
	   if(get_x >320&& get_x <520 && get_y > 50 && get_y <430)
	   { 
         get_x=0;get_y=0;
		 photo();
		 get_x=0;get_y=0;
       }
	   
	   if(get_x >90&& get_x <250 && get_y > 50 && get_y <430)
	   { 
         get_x=0;get_y=0;
          music(); 
		 get_x=0;get_y=0;
       }
	}
	return 0;
}
int photo()
{
	char *photo[]={"1.bmp","2.bmp","3.bmp"};//用数组保存图片路径
	//相册界面
	show_bmp("welcom.bmp");
	int i=-1;
	while(1)
	{
		//上一张
		if(slide == 1)
		{
			slide = -1;
			if(i==0)
			{
				i=2;
				show_bmp(photo[2]);
			}
			else
			{
				i--;
				show_bmp(photo[i]);
			}
		}	
		//下一张
		if(slide == 0)
		{
			slide = -1;
			if(i<3)
			{
				i++;
				show_bmp(photo[i]);
			}
			else
			{
				i=0;
				show_bmp(photo[0]);
			}
		}	
		//退出
		if(slide == 2)
		{
			
				printf("exit\n");
				//show_bmp("main.bmp");
				slide = -1;
				//break;
			   show_bmp("main.bmp");
			   return 0;
			
		}
	}
	return 0;
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int music()
{
	
	char *music_path[] = {"1.mp3", "2.mp3", "3.mp3"};
	int j=0;
	//显示背景图
	show_bmp("music.bmp");
	while(1)
	{
		//播放区域120/190,430/480 播放音乐
		if(get_x >700 && get_x <780 && get_y > 10 && get_y <80)
		{
			system("killall -9 mplayer");
			system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp3 &");
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
			//break;
			return 0;
		}
		
	     //下一首
		if(get_x >700 && get_x <780 && get_y > 290 && get_y <350)
		{
			system("killall -9 mplayer");
			printf("xiayisho\n");
			j++;
			if(j==4)//0 1 2
			{
			   j=0;
			   system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp3 &");
			}
			else 
			{
				switch (j){
				case 0:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp3 &");break;
				case 1:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 2.mp3 &");break; 
				case 2:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 3.mp3 &");break; 
				case 3:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 4.mp3 &");break; 
				}
			}

			get_x=0;get_y=0;
		}
		//点击上一首
		if(get_x >700 && get_x <780 && get_y > 380 && get_y <450)
		{
			system("killall -9 mplayer");
			//结束当前这一首,然后播放下一首
			printf("shangyishu\n");
			j--;
			if(j==-1)
			{
				j = 3;
				system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 3.mp3 &");
			}
			else 
			{
             switch (j){
				case 0:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp3 &");break;
				case 1:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 2.mp3 &");break;
				case 2:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 3.mp3 &");break; 
				case 3:system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 4.mp3 &");break;
			}

			}
            get_x=0;get_y=0;		
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
			get_x=0;get_y=0;
		}
		//控制音量,降低音量
		if(get_x >650 && get_x <700 && get_y > 250 && get_y <290)
		{
			write(fifo_fd,"volume 40 1\n",strlen("volume 40 1\n"));
			printf("volume 40\n");
			get_x=0;get_y=0;
		}

	}
	
	return 0;
	
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int video()
{
  int flag=0;
  show_bmp("video.bmp");//显示背景图
  while(1)
	{   

        //播放区域120/190,430/480 播放视频
		if(get_x >0 && get_x <60 && get_y > 430 && get_y <480)
		{
			system("killall -9 mplayer");
			system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 a1.mp4&");
			printf("player\n");
			get_x=0;get_y=0;
			flag=1;
		}
       if(flag==1)	
	   {
           //暂停区域290/360,430/480 暂停播放
		  if(get_x >70 && get_x <125 && get_y > 430 && get_y <480)
		  {
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("stop\n");
			get_x=0;get_y=0;
		  }
		  
			//继续区域480/550,430/480 继续播放
		   if(get_x >130 && get_x <190 && get_y > 430 && get_y <480)
			{
				write(fifo_fd,"pause\n",strlen("pause\n"));
				printf("continue\n");
				get_x=0;get_y=0;
			}

           	    //pos=write(fifo_fd,"get_percent_pos\n",strlen("get_percent_pos\n"));
			if((get_x<400)&& (slide==1))//rigth
			 {
				write(fifo_fd,"seek +5\n",strlen("seek +5\n"));
				printf("seek +5\n");
				slide=-1;
				get_x=0;get_y=0;
			 }
			
			if((get_x<400)&&(slide==0))//left
			{
				write(fifo_fd,"seek +5\n",strlen("seek -5\n"));
				printf("seek -5\n");
				slide=-1;
				get_x=0;get_y=0;
			}
	   
			//控制音量
			if((get_x >560 && get_x <615 && get_y > 430 && get_y <480))//||(slide==2))//up
			 {
				write(fifo_fd,"volume 100 1\n",strlen("volume 100 1\n"));
				printf("volume 100\n");
				slide=-1;
				get_x=0;get_y=0;
			 }
			if((get_x >490 && get_x <545 && get_y > 430 && get_y <480))//||(slide==3))//down
			{
				write(fifo_fd,"volume 40 1\n",strlen("volume 40 1\n"));
				printf("volume 40\n");
				slide=-1;
				get_x=0;get_y=0;
			}			
				
	   }
	   
	 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	 //690/800,430/480 退出播放
	  if(get_x >690 && get_x <800 && get_y > 430 && get_y <480)
		{
			flag=0;
			system("killall -9 mplayer");
			printf("exit\n");
			get_x=0;get_y=0;
			show_bmp("main.bmp");
			//break;
			return 0;
		}	   
	}
	
}