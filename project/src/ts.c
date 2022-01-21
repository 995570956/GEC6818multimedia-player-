#include "ts.h"

//static 静态变量关键字，说明此变量只用在当前c文件
//extern 声明此变量由外部文件提供，
int get_x,get_y,slide=-1;

//循环获取点击坐标与滑动方向
//参数 x，y用来获取x，y坐标
//slide的值是0是左滑，1是右滑，2是上滑，3，下滑
//错误返回-1，
int get_xy(void)
{
	int x_s,y_s,x_e,y_e;
	//打开驱动文件 /dev/input/event0
	int fd = open("/dev/input/event0",O_RDWR);
	if(fd == -1)
	{
		perror("open ");
		return -1;
	}
	//定义事件结构体
	struct input_event input;
	while(1)
	{

		read(fd, &input, sizeof(struct input_event));
		if(input.type == 3 && input.code == ABS_X)    //判断获取x轴的值
		{
			//黑色边框触摸屏分辨率是1024*600，要转为800*480
			//蓝色边框触摸屏分辨率是正常的800*480
			get_x = (input.value*800)/1024;
			//get_x = input.value;
		}
		
		if(input.type == 3 && input.code == ABS_Y)    //判断获取y轴的值
		{
		    get_y = (input.value*480)/600;
			//get_y = input.value;
		}
		//printf("type %d,code %d, value %d\n",input.type, input.code, input.value);		
			
		//判断滑动,获取到点击的起始位置与结束位置来判断滑动方向
		if(input.type == 1 && input.value == 1)   //点击
		{
			//printf("x=%d.y=%d\n",x,y);
			x_s = get_x;
			y_s = get_y;
		}
		if(input.type == 1 && input.value == 0)   //松手
		{
			x_e = get_x;
			y_e = get_y;
			//printf("x_s=%d,y_s=%d,x_e=%d,y_e=%d\n",x_s,y_s,x_e,y_e);
			if(x_s - x_e > 20)  //左滑
				slide = 0;
			else if(x_s - x_e < -20)  //右滑
				slide = 1;
			if(y_s - y_e > 20)     //上滑
				slide = 2;
			else if(y_s - y_e <-20)   //下滑
				slide = 3;
		}	
	}
	
	//关闭文件
	close(fd);

	return 0;
}