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

//������Ƶ����
int music()
{
	
	pid_t pid;
	//��ʾ����ͼ
	show_bmp("1.bmp");
	printf("music\n");
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
		
		//��������120/190,430/480 ��������
		if(get_x >700 && get_x <780 && get_y > 10 && get_y <80)
		{
			system("killall -9 mplayer");
			system("mplayer -slave -quiet -input file=myfifo -geometry 0:0 -zoom -x 800 -y 430 1.mp4&");
			printf("player\n");
			get_x=0;get_y=0;
		}
		//��ͣ����290/360,430/480 ��ͣ����
		else if(get_x >700 && get_x <780 && get_y > 100 && get_y <170)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("stop\n");
			get_x=0;get_y=0;
		}
		//��������480/550,430/480 ��������
		else if(get_x >700 && get_x <780 && get_y > 190 && get_y <260)
		{
			write(fifo_fd,"pause\n",strlen("pause\n"));
			printf("continue\n");
			get_x=0;get_y=0;
		}
		//690/800,430/480 �˳�����
		else if(get_x >10 && get_x <60 && get_y > 10 && get_y <60)
		{
			system("killall -9 mplayer");
			printf("exit\n");
			get_x=0;get_y=0;
			//��ʾ������ͼƬ
			show_bmp("main.bmp");
			break;
		}
		
		//��һ��
		if(get_x >700 && get_x <780 && get_y > 290 && get_y <350)
		{
			pid = fork();	//�ӽ���
			if(pid == 0)	//�ӽ���ִ�в���-->�����±�Ϊi������
			{
				execl("/usr/bin/madplay", "madplay", music_path[i], NULL);
			}
		
		}
		//�����һ��
		if(get_x >700 && get_x <780 && get_y > 380 && get_y <450)
		{
			//������ǰ��һ��,Ȼ�󲥷���һ��
			kill(pid, SIGKILL);
			i++;
			if(i >2)
				i = 0;
			
			pid = fork();	//�ӽ���
			if(pid == 0)	//�ӽ���ִ�в���-->�����±�Ϊi������
			{
				execl("/usr/bin/madplay", "madplay", music_path[i], NULL);
			}			
//������չ�� �б�ѭ������(������ʹ��wait), ���������һ�ס�
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
		if(get_x >650 && get_x <700 && get_y > 140 && get_y <190)
		{
			write(fifo_fd,"volume 80 1\n",strlen("volume 80 1\n"));
			printf("volume 80\n");

			
		}
		//��������,��������
		if(get_x >650 && get_x <700 && get_y > 250 && get_y <290)
		{
			write(fifo_fd,"volume 40 1\n",strlen("volume 40 1\n"));
			printf("volume 40\n");
			
		}

	}
	
	return 0;
}