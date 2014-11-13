/*
 *  module.h
 *  helloWorld
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef MODULE_H_
#define MODULE_H_
GtkWidget * clist_modul;
void getModInfo(char store[], int i, char modName[], char memUse[],
		char times[]);

void createModPage(GtkWidget* notebook)
{
	GtkWidget *frame_up, *frame_down, *table, *align, *button;
	GtkWidget *frame = gtk_frame_new("模块信息表");
	gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
	gtk_widget_set_size_request(frame, 100, 355);
	gtk_widget_show(frame);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, gtk_label_new(
			"模块信息"));

	/* 建一个表格，分为上下两部分 */
	table = gtk_table_new(10, 4, TRUE);
	/* 将这个表添加到框架 */
	gtk_container_add(GTK_CONTAINER(frame), table);

	/* 建一个frame在表上边*/
	frame_down = gtk_frame_new("*0(^_^)0*");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_down, 0, 4, 0, 10);
	gtk_widget_show(frame_down);
	gtk_widget_show(table);

	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_container_add(GTK_CONTAINER(frame_down), scrolled_window);
	gtk_widget_show(scrolled_window);

	/* 老是不能显示，经测试直到这里都可以正确实现 */
	gchar *titles[3] =
	{ "模块名", "占用内存", "加载次数" }; //由于含有特殊情况，所以只读取通//用格式的范例
	clist_modul = gtk_clist_new_with_titles(3, titles);
	gtk_clist_set_shadow_type(GTK_CLIST(clist_modul), GTK_SHADOW_IN);
	gtk_clist_set_column_width(GTK_CLIST(clist_modul), 0, 270);
	gtk_clist_set_column_width(GTK_CLIST(clist_modul), 1, 270);
	gtk_clist_set_column_width(GTK_CLIST(clist_modul), 2, 270);
	gtk_container_add(GTK_CONTAINER(scrolled_window), clist_modul);
	set_modul_info();
	gtk_widget_show(clist_modul);
}
void set_modul_info()
{
	/* 原来是这个函数中出现某种问题，
	 * 删除这个函数后可以出现所有控件
	 * 于是我干脆把那个函数直接整合到这个函数中来
	 * 结果可以运行来！
	 * 我认为可能是将控件作为函数参数传递出的问题 */
	/* 读取当前进程信息，并显示到列表框中 */
	//add_modules_view(clist_modul);
	/* 原来用的是5000，出现问题，于是变小，可以 */
	char infoBuf[2000]; //暂存读取的modules文件内容
	int fd = open("/proc/modules", O_RDONLY);
	read(fd, infoBuf, sizeof(infoBuf));
	close(fd);
	unsigned int lines = 0;
	unsigned int i = 0;
	gtk_clist_clear(clist_modul);
	/* 先取得行数 */
	while (i != sizeof(infoBuf) / sizeof(char))
	{
		if (infoBuf[i] == '\n')
			lines++;
		i++;
	}
	i = 0;
	for (i = 1; i <= lines; i++)
	{
		char convert_mem[25];
		char modName[25]; //模块名
		char memUse[20]; //内存量
		char times[5]; //使用次数
		int mem_num;
		float real_mem;
		getModInfo(infoBuf, i, modName, memUse, times);
		mem_num = atoi(memUse);
		real_mem = (float) mem_num / (1024);
		gcvt(real_mem, 3, convert_mem);
		gchar *list[1][3] =
		{
		{ modName, convert_mem, times } };
		gtk_clist_append((GtkCList*) clist_modul, list[0]);
		gtk_clist_thaw((GtkCList *) clist_modul); //更新list列表显示
	}
}
void getModInfo(char store[], int i, char modName[], char memUse[],
		char times[])
{
	int j = 0;
	int cflags = 0; //记录读取的回车键个数以便判断行数
	int k = 0;
	char name2[25];
	char mem2[20];
	char times2[5];
	while (cflags < i - 1)
	{
		if (store[j] == '\n')
			cflags++; //回车数加1
		j++;
	}
	while (store[j] != ' ')
	{ //读取进程名
		name2[k++] = store[j];
		j++;
	}
	name2[k] = '\0';
	j++; //跳转到下一个不是空格的地方
	k = 0;
	while (store[j] != ' ')
	{
		mem2[k++] = store[j];
		j++;
	}
	mem2[k] = '\0'; //封口
	j++;
	times2[0] = store[j]; //读取模块的使用次数
	times2[1] = '\0'; //封口
	strcpy(modName, name2);
	strcpy(memUse, mem2);
	strcpy(times, times2);
}
void add_modul(void)
{
        system("insmod ./devDrv.ko");
        set_modul_info();
}
void remove_modul(void)
{      
        system("rmmod devDrv.");
        set_modul_info();
}
#endif /* MODULE_H_ */

