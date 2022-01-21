#ifndef __TS_H
#define __TS_H

#include <stdio.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

//extern声明变量可以提供给其它c文件使用
extern int get_x,get_y,slide;

int get_xy(void);




#endif