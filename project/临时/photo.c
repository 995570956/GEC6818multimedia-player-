#include <stdio.h>
#include "showbmp.h"
#include "ts.h"

int photo()
{
	char *photo[]={"1.bmp","2.bmp","3.bmp"};//�����鱣��ͼƬ·��
	//������
	show_bmp("welcom.bmp");
	int i=-1;
	while(1)
	{
		//��һ��
		if(slide == 1)
		{
			slide = -1;
			if(i==0)
			{
				show_bmp(photo[0]);
			}
			else
			{
				i--;
				show_bmp(photo[i]);
			}
		}	
		//��һ��
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
				show_bmp(photo[2]);
			}
		}	
		//�˳�
		if(slide == 2)
		{
			sleep(1);
			if(slide == 2)
			{
				printf("exit\n");
				show_bmp("main.bmp");
				slide = -1;
				break;
			}
		}
	}
	
}