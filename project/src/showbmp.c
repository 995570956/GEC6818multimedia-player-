#include "showbmp.h"


//显示800*480的bmp图片
int show_bmp(char *bmp_path)
{
	//打开显示屏驱动  /dev/fb0
	int lcd_fd = open("/dev/fb0", O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open lcd");
		return -1;
	}
	//printf("lcd fd =%d\n",lcd_fd);
	//打开bmp图片
	int bmp_fd = open(bmp_path, O_RDWR);
	if(bmp_fd== -1)
	{
		perror("open bmp");
		return -1;
	}		
	
	//偏移文件头54个字节的图片信息
	lseek(bmp_fd,54,SEEK_SET);
	
	//读取图片数据
	char bmp_buf[800*480*3];
	read(bmp_fd,bmp_buf, 800*480*3);
	
	//申请内核空间
	int *lcd_map = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE,MAP_SHARED, lcd_fd, 0);
	if(lcd_map == (void *)-1 )
	{
		perror("mmap ");
		return -1;
	}	
	
		//先写行
	for(int y=0;y<480; y++)
	{
		for(int x=0;x<800; x++)
		{
			//x*480是那一列，y是列的那个具体的位置
			lcd_map[(479-y)*800+x] = bmp_buf[(y*800+x)*3 +2] << 16 |   //红色数据
							         bmp_buf[(y*800+x)*3 +1] << 8  |   //绿色数据
							         bmp_buf[(y*800+x)*3 +0] << 0;     //蓝色数据
		}
	}
		
	//释放内存空间
	munmap(lcd_map, 800*480*4);
	
	//关闭文件
	close(lcd_fd);
	
	return 0;
}