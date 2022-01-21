#include "showbmp.h"


//��ʾ800*480��bmpͼƬ
int show_bmp(char *bmp_path)
{
	//����ʾ������  /dev/fb0
	int lcd_fd = open("/dev/fb0", O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open lcd");
		return -1;
	}
	//printf("lcd fd =%d\n",lcd_fd);
	//��bmpͼƬ
	int bmp_fd = open(bmp_path, O_RDWR);
	if(bmp_fd== -1)
	{
		perror("open bmp");
		return -1;
	}		
	
	//ƫ���ļ�ͷ54���ֽڵ�ͼƬ��Ϣ
	lseek(bmp_fd,54,SEEK_SET);
	
	//��ȡͼƬ����
	char bmp_buf[800*480*3];
	read(bmp_fd,bmp_buf, 800*480*3);
	
	//�����ں˿ռ�
	int *lcd_map = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE,MAP_SHARED, lcd_fd, 0);
	if(lcd_map == (void *)-1 )
	{
		perror("mmap ");
		return -1;
	}	
	
		//��д��
	for(int y=0;y<480; y++)
	{
		for(int x=0;x<800; x++)
		{
			//x*480����һ�У�y���е��Ǹ������λ��
			lcd_map[(479-y)*800+x] = bmp_buf[(y*800+x)*3 +2] << 16 |   //��ɫ����
							         bmp_buf[(y*800+x)*3 +1] << 8  |   //��ɫ����
							         bmp_buf[(y*800+x)*3 +0] << 0;     //��ɫ����
		}
	}
		
	//�ͷ��ڴ�ռ�
	munmap(lcd_map, 800*480*4);
	
	//�ر��ļ�
	close(lcd_fd);
	
	return 0;
}