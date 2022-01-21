#include "ts.h"

//static ��̬�����ؼ��֣�˵���˱���ֻ���ڵ�ǰc�ļ�
//extern �����˱������ⲿ�ļ��ṩ��
int get_x,get_y,slide=-1;

//ѭ����ȡ��������뻬������
//���� x��y������ȡx��y����
//slide��ֵ��0���󻬣�1���һ���2���ϻ���3���»�
//���󷵻�-1��
int get_xy(void)
{
	int x_s,y_s,x_e,y_e;
	//�������ļ� /dev/input/event0
	int fd = open("/dev/input/event0",O_RDWR);
	if(fd == -1)
	{
		perror("open ");
		return -1;
	}
	//�����¼��ṹ��
	struct input_event input;
	while(1)
	{

		read(fd, &input, sizeof(struct input_event));
		if(input.type == 3 && input.code == ABS_X)    //�жϻ�ȡx���ֵ
		{
			//��ɫ�߿������ֱ�����1024*600��ҪתΪ800*480
			//��ɫ�߿������ֱ�����������800*480
			get_x = (input.value*800)/1024;
			//get_x = input.value;
		}
		
		if(input.type == 3 && input.code == ABS_Y)    //�жϻ�ȡy���ֵ
		{
		    get_y = (input.value*480)/600;
			//get_y = input.value;
		}
		//printf("type %d,code %d, value %d\n",input.type, input.code, input.value);		
			
		//�жϻ���,��ȡ���������ʼλ�������λ�����жϻ�������
		if(input.type == 1 && input.value == 1)   //���
		{
			//printf("x=%d.y=%d\n",x,y);
			x_s = get_x;
			y_s = get_y;
		}
		if(input.type == 1 && input.value == 0)   //����
		{
			x_e = get_x;
			y_e = get_y;
			//printf("x_s=%d,y_s=%d,x_e=%d,y_e=%d\n",x_s,y_s,x_e,y_e);
			if(x_s - x_e > 20)  //��
				slide = 0;
			else if(x_s - x_e < -20)  //�һ�
				slide = 1;
			if(y_s - y_e > 20)     //�ϻ�
				slide = 2;
			else if(y_s - y_e <-20)   //�»�
				slide = 3;
		}	
	}
	
	//�ر��ļ�
	close(fd);

	return 0;
}