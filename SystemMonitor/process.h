/*
 *  process.h
 *  helloWorld
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef PROCESS_H_
#define PROCESS_H_
GtkWidget * clist;
GtkWidget *label_proc;
GtkWidget *label_time;
/* 刷新信息 */
void set_proc_info();
/* 表示读取第i个空格之前的一个字符串(此即获得的数据)) */
void read_info(char store[], int i, char get[]);
/* 用户选中某一行时的回调函数*/
void selection_made(GtkWidget *clist, gint row, gint column,
		GdkEventButton *event, gpointer data);

void createProPage(GtkWidget* notebook)
{
	char buffer[100];
	GtkWidget * table;
	GtkWidget *frame_up;
	GtkWidget *frame_down;
	GtkWidget *vbox;
	GtkWidget *font;
	GtkWidget *tooltip;
	GdkColor color;

	GtkWidget *frame = gtk_frame_new("");
	gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
	gtk_widget_set_size_request(frame, 100, 355);
	gtk_widget_show(frame);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, gtk_label_new(
			"进程信息"));

	/* 建一个表格，分为上下两部分 */
	table = gtk_table_new(10, 4, TRUE);
	/* 将这个表添加到框架 */
	gtk_container_add(GTK_CONTAINER(frame), table);

	/* 建一个frame在表左下边显示标签信息 */
	frame_up = gtk_frame_new("*0(^_^)0*");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_up, 0, 2, 7, 10);
	gtk_widget_show(frame_up);
	gtk_widget_show(table);
	/* 建一个标签显示进程数等(用button代替) */
	label_proc = gtk_button_new_with_label("good");
	gtk_container_add(GTK_CONTAINER(frame_up), label_proc);
	/* 连接刷新 */
	g_signal_connect(G_OBJECT(label_proc), "clicked",
			G_CALLBACK(set_proc_info), NULL);
	tooltip = gtk_tooltips_new();
	gtk_tooltips_set_tip(tooltip, label_proc, "点击刷新", NULL);
	gtk_widget_show(label_proc);

	/* 建一个frame在表右下边显示标签信息 */
	frame_up = gtk_frame_new("(*^_^*)");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_up, 2, 4, 7, 10);
	gtk_widget_show(frame_up);
	gtk_widget_show(table);
	/* 建一个标签显示系统时间(用button代替) */
	label_time = gtk_button_new_with_label("good");
	gtk_tooltips_set_tip(tooltip, label_time, "点击刷新", NULL);
	g_signal_connect(G_OBJECT(label_time), "clicked",
			G_CALLBACK(set_proc_info), NULL);
	gtk_container_add(GTK_CONTAINER(frame_up), label_time);
	gtk_widget_show(label_time);

	/* 建一个frame在表下边显示进程信息 */
	frame_down = gtk_frame_new("进程信息表");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_down, 0, 4, 0, 7);
	gtk_widget_show(frame_down);
	gtk_widget_show(table);
	/* 创建一个滚动窗口构件，将GtkCList组装到里面。
	 * 这样使得内容超出列表时，可以用滚动条浏览*/
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_container_add(GTK_CONTAINER(frame_down), scrolled_window);
	gtk_widget_show(scrolled_window);

	gchar *titles[5] =
	{ "进程名", "进程PID", "进程状态", "占用内存", "优先级" };
	/* 创建GtkCList构件。本例中，我们使用了5列*/
	clist = gtk_clist_new_with_titles(5, titles);
	gtk_tooltips_set_tip(tooltip, clist, "点击杀死进程", NULL);
	/* 当作出选择时，我们要知道选择了哪一个单元格。
	 * 使用 selection_row回调函数，代码在clist.h可以看见*/
	gtk_signal_connect(GTK_OBJECT(clist), "select_row", GTK_SIGNAL_FUNC(
			selection_made), NULL);

	/* 不一定要设置边框的阴影，但是效果挺不错*/
	gtk_clist_set_shadow_type(GTK_CLIST(clist), GTK_SHADOW_OUT);
	/* 设置每一列到宽度 */
	gtk_clist_set_column_width(GTK_CLIST(clist), 0, 200);
	gtk_clist_set_column_width(GTK_CLIST(clist), 1, 120);
	gtk_clist_set_column_width(GTK_CLIST(clist), 2, 110);
	gtk_clist_set_column_width(GTK_CLIST(clist), 3, 100);
	gtk_clist_set_column_width(GTK_CLIST(clist), 4, 100);
	gtk_container_add(GTK_CONTAINER(scrolled_window), clist);
	gtk_widget_show(clist);
	set_proc_info();
}
void set_proc_info()
{
	/* 读取当前进程信息，并显示到列表框中 */
	DIR *dir;
	struct dirent *ptr;
	dir = opendir("/proc");
	char path[20]; //记录pid的数字文件夹
	int fd; //文件描述，用于打开那些数字文件夹的stat文件
	char store[1000]; //将读取的stat文件内容暂时存放到store中
	char name[20]; //进程名
	char pid_num[20]; //pid号
	char stat[20]; //状态
	char memory[20]; //内存
	char priority[20]; //优先级
	gtk_clist_clear(GTK_CLIST(clist));
	while ((ptr = readdir(dir)) != NULL)
	{
		if ((ptr->d_name[0] >= '0') && (ptr->d_name[0] <= '9'))
		{
			sprintf(path, "/proc/%s/stat", ptr->d_name); //将此文件的全部路径写入name中
			//打开这个文件，并且从中读取到有用的信息放在相应的数组中
			fd = open(path, O_RDONLY);
			read(fd, store, sizeof(store));
			close(fd);
			read_info(store, 1, pid_num); //进去的是字符串和号，出来对应信息修改
			read_info(store, 2, name); //读取名称
			read_info(store, 3, stat); //进程状态，SDR已经转化为中文
			read_info(store, 18, priority); //优先级
			read_info(store, 23, memory); //注意是以B为单位，需要换算
			int mem_num = atoi(memory); //转换成整数形式B为单位
			float real_mem = (float) mem_num / (1024 * 1024); //得到MB为单位的信息
			char convert_mem[25];
			gcvt(real_mem, 5, convert_mem); //浮点数转换成字符串
			gchar *list[1][5] =
			{
			{ name, pid_num, stat, convert_mem, priority } };
			/* 把这一行加入到clist中 */
			gtk_clist_append((GtkCList*) clist, list[0]);
			gtk_clist_thaw((GtkCList *) clist); //更新list列表显示
		}
	}
	closedir(dir);
}



/* 用户选中某一行时的回调函数*/
void selection_made(GtkWidget *clist, gint row, gint column,
		GdkEventButton *event, gpointer data)
{
	/* 取得存储在被选中的行和列的单元格上的文本
	 * 当鼠标点击时，我们用t e x t参数接收一个指针*/
	gchar *Pid, *procName, buffer[40] = "Kill the process <";
	/* 该函数读取CLIST被选中到PID，
	 * 它与gtk_clist_set_text函数功能相反。*/
	gtk_clist_get_text(GTK_CLIST(clist), row, 1, &Pid);
	gtk_clist_get_text(GTK_CLIST(clist), row, 0, &procName);
	selectedRow = row;
	strcat(buffer, procName);
	strcat(buffer, "> !?");
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(NULL, //
			GTK_DIALOG_DESTROY_WITH_PARENT, //跟随父窗口关闭
			GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,//
			buffer);
	gtk_window_set_title(GTK_WINDOW(dialog), "*0(^_^)0*");
	GtkResponseType result = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	if (result == GTK_RESPONSE_YES || result == GTK_RESPONSE_APPLY)
	{
		killProcess(Pid);
	}
	return;
}
/* 根据一个pid杀死进程 */
/* 使用全局变量PID */
void killProcess(gchar *Pid)
{
	gchar killCmd[50] = "kill ";
	strcat(killCmd, Pid);
	system(killCmd);
	g_printf("%s", killCmd);
	/* 用gtk_clist_clear函数清除列表
	 * void gtk_clist_remove (GtkCList *clist,gint row);
	 * 该函数用来删除某一索引行。
	 * 行数确定时，直接对应第二个参数即可。
	 * 对于行数不确定，而是由鼠标或键盘随机获得焦点行的动态行删除问题，
	 * 在具体编程实现上，可以通过利用CLIST列表构件头文件
	 * gtkclist.h内GtkCList结构中的属性变量focus_row来实现，语句如下：
	 * gtk_clist_remove (GTK_CLIST(clist),GTK_CLIST (clist)->focus_row);*/
	gtk_clist_remove(clist, selectedRow);

	GtkWidget *dialog;//声明一个对话框
	/* 新建一个消息对话框 */
	dialog = gtk_message_dialog_new(NULL, //没有父窗口
			GTK_DIALOG_DESTROY_WITH_PARENT, //跟随父窗口关闭
			GTK_MESSAGE_WARNING, //显示警告图标
			GTK_BUTTONS_OK, //显示OK按钮
			("人生寂寞啊，被人杀死了！")); //提示信息的内容
	gtk_window_set_title(GTK_WINDOW(dialog), ("进程已经被杀死……"));//对话框的标题
	gtk_dialog_run(GTK_DIALOG(dialog));//运行对话框
	gtk_widget_destroy(dialog);//删除对话框
}
void set_label_proc_text()
{
	char buffer[100];
	char processes[10];
	getInforAftSpace("/proc/stat", "processes", processes);
	strcpy(buffer, "当前进程数 : ");
	strcat(buffer, processes);
	char btime[10];//系统运行时间
	char times[30];
	int fd = open("/proc/uptime", O_RDONLY);
	read(fd, times, sizeof(times));
	close(fd);
	read_info(times, 0, btime);
	float fInfor = (float) atof(btime);
	fInfor = fInfor / 60; //将单位化成min
	gcvt(fInfor, 5, btime);
	strcat(buffer, "\n系统运行时间 : ");
	strcat(buffer, btime);
	strcat(buffer, " min");
	char aveLoad[20];
	get_load_avg(aveLoad);
	strcat(buffer, "\n平均负载 : ");
	strcat(buffer, aveLoad);
	gtk_button_set_label((GtkButton*) label_proc, buffer);
	strcpy(buffer, "--------------点击刷新------------\n\n当前时间 ：");
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strcat(buffer, asctime(timeinfo));
	gtk_button_set_label((GtkButton*) label_time, buffer);
}

#endif /* PROCESS_H_ */
