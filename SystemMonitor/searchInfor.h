/*
 *  searchInfor.h
 *  helloWorld
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef SEARCHINFOR_H_
#define SEARCHINFOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX  1024
#define STANDARD  0
#define SHORT 1
#define LONG 2

/*
 * 在指定的proc文件中查找所需要的内核信息,并将找到的字符串后面的信息输出
 * pah:指定的proc文件的路径
 * name:所要查找的内核信息
 * infor:装载信息，已经转换为MB
 * 内存信息
 * more /proc/meminfo
 * MemTotal:        2058448 kB
 * MemFree:           52496 kB
 * Buffers:          580832 kB
 * Cached:           877024 kB
 */
void getInfor(char *path, char *name, char infor[])
{
	int fd = open(path, O_RDONLY);
	char store[2000];
	int k = 0;
	char *p = NULL;

	read(fd, store, sizeof(store));
	close(fd);
	/* 取得所需要信息所在行首尾指针 */
	p = strstr(store, name);

	/* 跳过标题 */
	while ((*p < '0') || (*p > '9'))
	{
		p++;
	}
	/* 读取数值 */
	while ((*p >= '0') && (*p <= '9'))
	{
		infor[k] = *p;
		k++;
		p++;
	}
	infor[k] = '\0';

	float fInfor = (float) atoi(infor);
	fInfor = fInfor / 1024; //将单位化成MB
	gcvt(fInfor, 5, infor); //换算后的存放在total中

}
/* 直接取空格后数值,没有转换尾MB的 */
void getInforAftSpace(char *path, char *name, char infor[])
{
	int fd = open(path, O_RDONLY);
	char store[2000];
	int k = 0;
	char *p = NULL;

	read(fd, store, sizeof(store));
	close(fd);
	/* 取得所需要信息所在行首尾指针 */
	p = strstr(store, name);

	/* 跳过标题 */
	while ((*p < '0') || (*p > '9'))
	{
		p++;
	}
	/* 读取数值 */
	while ((*p >= '0') && (*p <= '9'))
	{
		infor[k] = *p;
		k++;
		p++;
	}
	infor[k] = '\0';
}
/* 获取cpu信息等 */
/*model name	: Pentium(R) Dual-Core CPU       T4400  @ 2.20GHz
 *stepping		: 10
 *cpu MHz		: 1200.000
 *cache size	: 1024 KB */

void getInforNotd(char *path, char *name, char infor[])
{
	int fd = open(path, O_RDONLY);
	char store[2000];
	int k = 0;
	char *p = NULL;

	read(fd, store, sizeof(store));
	close(fd);
	/* 取得所需要信息所在行首尾指针 */
	p = strstr(store, name);

	/* 跳过标题 */
	do
	{
		p++;
	} while (*p != ':');
	p += 2;
	/* 读取数值 */
	while (*p != '\n')
	{
		infor[k] = *p;
		k++;
		p++;
	}
	infor[k] = '\0';
}

void getSysVersion(char *path, char *name, char infor[])
{
	int fd = open(path, O_RDONLY);
	char store[2000];
	int k = 0;
	char *p = NULL;

	read(fd, store, sizeof(store));
	close(fd);
	/* 取得所需要信息所在行首尾指针 */
	p = strstr(store, name);

	/* 读取数值 */
	while (*p != '\n' && *p != ')')
	{
		infor[k] = *p;
		k++;
		p++;
	}
	infor[k++] = ')';
	infor[k] = '\0';
}
/* 显示系统的平均负载的内容 */
int get_load_avg(char aveLoad[])
{
	int fd;
	int n, k = 0;
	int res = -1;
	char line_buf[50];
	/* 打开存储系统平均负载的proc文件 */
	if ((fd = open("/proc/loadavg", O_RDONLY)) == -1)
	{
		perror("fail to loadavg");
		exit(-1);
	}
	/* 读取系统的平均负载的内容 */
	if ((n = read(fd, line_buf, MAX)) == -1)
	{
		perror("fail to read");
		goto err;
	}
	line_buf[n] = '/0';
	n = 0;
	while (line_buf[n] != '\n' && line_buf[n] != '\0')
	{
		aveLoad[k++] = line_buf[n++];
	}
	aveLoad[k] = '\0';
	res = 0;
	err: close(fd);
	return res;
}

void read_info(char store[], int i, char get[])
{
	int j = 0; //j表示的就是这个字符串的下标
	int k = 0;
	int cflags = 0; //用来记录空格的个数
	char buf[20]; //用来保存需要的信息
	while (cflags < i - 1)
	{ //特别注意此处是i-1，否则输出的顺序都是乱的，因为需要在i之前的空格，所以是i-1，这样执行完才是i-1的空格
		if (store[j++] == ' ')
			cflags++;
	}
	while (store[j] != ' ')
	{ //读取下一个空格之前的
		buf[k++] = store[j];
		j++;
	}
	buf[k] = '\0';
	if (2 == i)
	{//名称，去掉括号
		int i, j = 0;
		for (i = 1; ')' != buf[i]; i++)
		{
			get[j++] = buf[i];
		}
		get[j] = '\0';
	}
	else if (i == 3)
	{//第三个是表示状态
		if (!strcmp(buf, "S"))
			strcpy(get, "睡眠中");
		else if (!strcmp(buf, "R"))
			strcpy(get, "运行中");
		else if (!strcmp(buf, "T"))
			strcpy(get, "已停止");
		else if (!strcmp(buf, "D"))
			strcpy(get, "不可中断");
		else if (!strcmp(buf, "Z"))
			strcpy(get, "死锁中");
		/* 这里出现一个问题，想不通啊！
		 * 为什么上面两行不是放在if外面？
		 * 原来是if中= 和 == 混淆 */
		//else strcpy(get,"奇怪！");
	}
	else
		strcpy(get, buf);
}
#endif /* SEARCHINFOR_H_ */
