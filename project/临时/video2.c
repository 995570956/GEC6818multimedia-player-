#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ts.h"
#include "showbmp.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

//������Ƶ����
int video()
{
	//��ʾ����ͼ
	show_bmp("video.bmp");
	printf("video\n");
	//����ļ��Ƿ����
	int ret = access("myfifo",F_OK);
	if(ret !=0 )
	{
		//�����ܵ��ļ�
		int fifo_ret = mkfifo("myfifo",0777);
		if(fifo_ret == -1)
		{
			perror("mkfifo");
			return -1;
		}
	}

	//�򿪹ܵ��ļ�
	int fifo_fd = open("myfifo", O_RDWR);
	if(fifo_fd ==-1)
	{
		perror("open fifo");
		return -1;
	}
	
	while(1)
	{
		
		//��������120/190,430/480 ������Ƶ
		if(get_x >120 && get_x <190 && get_y > 430 && get_y <480)
		{
			system("killall -9 mplayer");
			system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp4&");
			printf("player\n");
			get_x=0;get_y=0;
		}
		//��ͣ����290/360,430/480 ��ͣ����
		else if(get_x >290 && get_x <360 && get_y > 430 && get_y <480)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("stop\n");
			get_x=0;get_y=0;
		}
		//��������480/550,430/480 ��������
		else if(get_x >480 && get_x <550 && get_y > 430 && get_y <480)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("continue\n");
			get_x=0;get_y=0;
		}
		//690/800,430/480 �˳�����
		else if(get_x >690 && get_x <800 && get_y > 430 && get_y <480)
		{
			system("killall -9 mplayer");
			printf("exit\n");
			get_x=0;get_y=0;
			//��ʾ������ͼƬ
			show_bmp("main.bmp");
			break;
		}
		//���
		if(slide == 1)
		{
			write(fifo_fd,"seek +5\n",strlen("seek +5\n"));
			printf("seek +5\n");
			slide = -1;
		}
			
		//����
		if(slide == 0)
		{
			write(fifo_fd,"seek -5\n",strlen("seek -5\n"));
			printf("seek -5\n");
			slide = -1;
		}
		
		//��������,��������
		if(slide == 2)
		{
			write(fifo_fd,"volume 80 1\n",strlen("volume 80 1\n"));
			printf("volume 80\n");
			slide = -1;
			
		}
		//��������,��������
		if(slide == 3)
		{
			write(fifo_fd,"volume 40 1\n",strlen("volume 40 1\n"));
			printf("volume 40\n");
			slide = -1;
			
		}

	}
	
	return 0;
}