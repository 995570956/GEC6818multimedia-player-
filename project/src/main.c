#include <stdio.h>
#include "showbmp.h"
#include "ts.h"
#include <pthread.h>


//arm-linux-gcc main.c showbmp.c ts.c video2.c -o project -lpthread
int main()
{
	//��¼����
	//login();
	//��ʾ������ͼƬ
	show_bmp("main.bmp");
	//�����̻߳�ȡ����
	pthread_t pid;
	pthread_create(&pid, NULL, (void *)get_xy, NULL);
	//���ݵ������ѡ��ͬ�Ĺ���
	while(1)
	{

		
		//���
		if(get_x >70 && get_x < 230 && get_y >170 && get_y <280)
		{
			photo()��
			printf("photo\n");
		}
			
		//����
		if(get_x >340 && get_x < 520 && get_y >170 && get_y <280)
		{
			printf("music\n");
		}
		
		//��Ƶ
		if(get_x >580 && get_x < 750 && get_y >170 && get_y <280)
		{
			video();
		}
	}
	
	
}