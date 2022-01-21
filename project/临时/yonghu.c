#include<stdio.h>
#include<string.h>

//编写代码实现，模拟用户登录情景，并且只能登录三次。
//（只允许输入三次密码，如果密码正确则提示登录成，如果三次均输入错误，则退出程序。)

int main()
{
	char passw[] = "12345";
	char test[20] = "0";
	int count = 0;//用来记录登录次数
	
	while (count < 3)
	{
		printf("请输入密码->");
		scanf("%s", &test);
		if (strcmp(passw, test) == 0)
		{
			printf("登陆成功\n");
			break;
		}
		else
		{
			printf("密码错误\n");
			count++;
		}
		
	}
	if (3 == count)
	{
		printf("退出程序\n");
	}
	return 0;
}
