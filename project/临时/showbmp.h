#ifndef __SHOWBMP_H
#define __SHOWBMP_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int show_bmp(char *bmp_path);


#endif