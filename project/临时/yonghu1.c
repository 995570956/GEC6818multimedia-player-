#include<stdio.h>
#include<string.h>


typedef struct The_users   //typedef 可以定义结构体别名
{
    char id[11]; //账号 
    char pwd[20]; //密码 
    char name[15];//姓名为字符串 
    char sex; //性别为单个字符
	long phone; //电话号码为长整型 
}users;


/*创建储存用户账号密码的文件*/ 
void Create_File()
{
    FILE *fp;
    if ((fp = fopen("users.txt","rb"))==NULL)                 /*如果此文件不存在*/
    {
        if ((fp = fopen("users.txt","wb+"))==NULL)
        {
            printf("无法建立文件！\n");
            exit(0);
            
        }
    }
}



/*注册账号*/ 
void registers()  //按结构体的大小，一次写入或者读入1个结构体大小
     {    
         users a,b;//结构体 The_users 重命名定义
         FILE *fp;
         char temp[20];
         int count = 0;
         printf("欢迎来到注册界面！\n");
         Sleep(1000);
         fp = fopen("users.txt","r");
         
         fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块 到b
          printf("请输入账号\n");
         scanf("%s",&a.id);
         
         
         while (1)
         {    
             if (strcmp(a.id, b.id)) /*如果两串不相等*/
             {
                 if (!feof(fp))    /*如果未到文件尾*/                                
                     
                     
                 {
                     fread(&b, sizeof(struct The_users), 1, fp);
                 }
                 else
                     break;
             }
             else

             {   
                 printf("此用户名已存在！请重新注册！\n"); 
                 Sleep(1000);
                 fclose(fp);
                 return;      
             }
         }
         printf("请输入姓名：\n");
         scanf("%s",&a.name);
         printf("请输入性别(f(女)/m(男))：\n");
         scanf(" %c",&a.sex);
         do{
         	if(a.sex != 'f' && a.sex != 'm'){
			 	printf("性别输入错误！请重新输入！\n");
		        scanf("%c",&a.sex);
			 }
		 }while(a.sex != 'f' && a.sex != 'm');
		 getchar();
         printf("请输入电话号码：\n");
         scanf("%ld",&a.phone);
         printf("请输入密码\n");
         scanf(" %s",&a.pwd);
         printf("请确认密码\n");
         scanf(" %s",&temp);
		 do{
         	if(!strcmp(a.pwd,temp)){
         		fp = fopen("users.txt","a");
		         fwrite(&a, sizeof(struct The_users), 1, fp);
		         printf("账号注册成功，请登录！\n"); 
		         Sleep(500);
		         fclose(fp);
				 return;
			 }else{
			 	printf("两次密码不匹配！请重新输入！\n");
		         scanf("%s",&a.pwd);
		         printf("请确认密码\n");
		         scanf("%s",&temp);
			 }
		 }while(1);
     }

	 
	 /*登录系统*/ 
void  Input_login()
{
    users a,b;//定义结构体The_users别名
    
    FILE *fp;
    printf("欢迎来到登录界面！\n");
         Sleep(1000);
    fp = fopen("users.txt","r");
    
    fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块 写入b
    printf("请输入账号\n");
    scanf("%s",&a.id);   
    
             while (1)
           {   
	           if (strcmp(a.id, b.id)==0)         //如果有此用户名
	           {
	               break;       
	           }
	           
	           else 
	           {
	               if (!feof(fp))  //如果文件没有读完                            
	            
	               {
	                   fread(&b, sizeof(struct The_users), 1, fp);
	               }
	               
	               else
	               {
	                   printf("此用户名不存在，请重新输入！\n");
					   Sleep(500); 
	                   fclose(fp);  
					   return;              
	               }
	             }
             }
       printf("请输入密码\n");
       	scanf("%s",&a.pwd); 
    do{   
	       
		if (strcmp(a.pwd, b.pwd)==0)            /*如果密码匹配*/
	           
	       {  
	          fclose(fp);
	          printf("登录成功,欢迎使用!");
	          Sleep(500);
	          return;
	          }
	       else  
	       {    printf("密码不正确!请重新输入密码\n");
	       		scanf("%s",&a.pwd);         
	       }
	}while(strcmp(a.pwd, b.pwd)==0);
       
}


/*找回密码*/
 
void reback()  //按结构体的大小，一次写入或者读入1个结构体大小
     {    
         users a,b;//结构体 The_users 重命名定义
         FILE *fp;
         char temp[20];
         int count = 0;
         printf("欢迎来到找回密码界面！\n");
         Sleep(1000);
         fp = fopen("users.txt","r");
    
    	fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块 写入b
    	printf("请输入账号\n");
    	scanf("%s",&a.id);   
    
             while (1)
           {   
	           if (strcmp(a.id, b.id)==0)         //如果有此用户名
	           {
	               break;       
	           }
	           
	           else 
	           {
	               if (!feof(fp))  //如果文件没有读完                            
	            
	               {
	                   fread(&b, sizeof(struct The_users), 1, fp);
	               }
	               
	               else
	               {
	                   printf("此用户名不存在，请重新输入！\n");
					   Sleep(500); 
	                   fclose(fp);  
					   return;              
	               }
	           }
       }
         printf("请输入姓名：\n");
         scanf("%s",&a.name);
         do{
         	if(strcmp(a.name,b.name)){
			 	printf("姓名输入错误！请重新输入！\n");
		        scanf("%s",&a.name);
			 }
		 }while(strcmp(a.name,b.name));
         printf("请输入电话号码：\n");
         scanf("%ld",&a.phone);
         do{
         	if(a.phone != b.phone){
			 	printf("电话号码输入错误！请重新输入！\n");
		        scanf("%ld",&a.phone);
			 }
		 }while(a.phone != b.phone);
        printf("您的密码是：%s",b.pwd);
        Sleep(3000);
}

