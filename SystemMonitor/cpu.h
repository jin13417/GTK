/*
 *  cpu.h
 *  helloWorld
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef CPU_H_
#define CPU_H_

GtkWidget *window;
GtkWidget *main_vbox;
GtkWidget *clist; //进程时候需要的列表
GtkWidget *clist2; //模块读取时需要的列表
GtkWidget *cpu_draw_area;
GdkPixmap *cpu_graph;
GtkWidget *pbar_cpu;

/* 全局变量 */
static gint cpuPoints[100];
static gfloat cpu_rate = 0.0;
static char PID[20];
static int selectedRow;
float zuser = 0, ztotal = 0;
typedef struct CPUinfo
{
	char modeName[50]; //line 5
	char cpuMHz[10]; //line 7
	char cacheSize[10];//line 8
	char cpuCores[10]; //line 12
	char addrSize[50]; //line 30
}*cpuInfo;

static gboolean cpu_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data)
{
	gdk_draw_drawable(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(
			widget)], cpu_graph, event->area.x, event->area.y, event->area.x,
			event->area.y, event->area.width, event->area.height);
	return FALSE;
}

static gboolean cpu_configure_event(GtkWidget *widget,
		GdkEventConfigure *event, gpointer data)
{
	if (cpu_graph)
	{
		g_object_unref(cpu_graph);
	}
	cpu_graph = gdk_pixmap_new(widget->window, widget->allocation.width,
			widget->allocation.height, -1);
	gdk_draw_rectangle(cpu_graph, widget->style->white_gc, TRUE, 0, 0,
			widget->allocation.width, widget->allocation.height);
	return TRUE;
}
/* 取得cpu利用率 */
float getCpuUseRatio()
{
	FILE *fp;
	char buffer[1024];
	size_t buf;
	float useRatio;
	/* 分别为用户模式，低优先级用户模式，内核模式，空闲的处理器时间 */
	float user = 0, nice = 0, sys = 0, idle = 0, iowait = 0;

	fp = fopen("/proc/stat", "r");
	/* 从fp中读取sizeof(buffer)块数据放入buffer，每次读一块 */
	buf = fread(buffer, 1, sizeof(buffer), fp);
	fclose(fp);
	if (buf == 0)
		return 0;
	buffer[buf] == '\0';
	sscanf(buffer, "cpu %f %f %f %f %f", &user, &nice, &sys, &idle, &iowait);
	if (idle <= 0)
		idle = 0;
	useRatio = 100 * (user - zuser) / (user + nice + sys + idle - ztotal);
	if (useRatio > 100)
		useRatio = 100;
	ztotal = user + nice + sys + idle;
	zuser = user;
	cpu_rate = useRatio;
	return useRatio;
}

/* cpu标签页，显示cpu信息 */
void createCPUPage(GtkWidget* notebook)
{
	GtkWidget *label;
	GtkWidget *vbox;

	GtkWidget *frame1 = gtk_frame_new("");

	gtk_container_set_border_width(GTK_CONTAINER(frame1), 10);
	gtk_widget_set_size_request(frame1, 120, 500);
	gtk_widget_show(frame1);

	/* 将该标签页加入到notebook中 */
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame1, gtk_label_new(
			"CPU信息"));

	/* 在该页建议个表格，分为上下2行，一列 */
	GtkWidget *table1 = gtk_table_new(10, 10, TRUE);

	/* 将这个表添加到“cpu使用率“页 */
	gtk_container_add(GTK_CONTAINER(frame1), table1);

	/* 新建一个frame框架用于显示图表 */
	GtkWidget *CPU_frame1 = gtk_frame_new("CPU使用历史曲线");

	/* 放到表格第一行 */
	/* 这个函数的参数不懂，不好调整 */
	gtk_table_attach_defaults(GTK_TABLE(table1), CPU_frame1, 0, 8, 0, 5);
	gtk_widget_show(CPU_frame1);

	/* 现在,我们开始向屏幕绘图。
	 * 我们使用的构件是绘图区构件。
	 *一个绘图区构件本质上是一个 X 窗口,没有其它的东西。
	 *它是一个空白的画布,我们可以在其上绘制需要的东西。*/
	cpu_draw_area = gtk_drawing_area_new();

	/* 设置可以画图 */
	gtk_widget_set_app_paintable(cpu_draw_area, TRUE);

	/* 画图区默认大小 */
	gtk_drawing_area_size(GTK_DRAWING_AREA(cpu_draw_area), 40, 80);
	/* 画布添加到cpu曲线框架中 */
	gtk_container_add(GTK_CONTAINER(CPU_frame1), cpu_draw_area);
	gtk_widget_show(cpu_draw_area);
	/* 关联回调函数 */
	/* 关于各种事件不甚了解 */
	g_signal_connect(cpu_draw_area, "expose_event",
			G_CALLBACK(cpu_expose_event), NULL);
	g_signal_connect(cpu_draw_area, "configure_event", G_CALLBACK(
			cpu_configure_event), NULL);
	gtk_widget_show(cpu_draw_area);

	int i;
	for (i = 0; i < 100; i++)
	{
		/* 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
		 * (rand() % (b - a)) + a */
		cpuPoints[i] = (rand() % 30 + 180);
	}

	// 	此处出现问题
	/* 不断刷新画图 */
		//gtk_timeout_add(100, (GtkFunction) drawGraph, NULL);

	/* 取得CPU信息 */
	char modeName[50], cpuMHz[20], cacheSize[20], cpuCores[20], addrSize[50];
	char cpuBuffer[1000];

	//getCPUInfo("/proc/cpuinfo", modeName, cacheSize);
	//cpuMHz,cacheSize,cpuCores,addrSize);
	/* 不能用\t !! */

	getInforNotd("/proc/cpuinfo", "model name", modeName);
	getInforNotd("/proc/cpuinfo", "cache size", cacheSize);
	getInforNotd("/proc/cpuinfo", "cpu MHz", cpuMHz);
	getInforNotd("/proc/cpuinfo", "cpu cores", cpuCores);
	getInforNotd("/proc/cpuinfo", "address sizes", addrSize);

	/* 建一个frame在表一下半部显示cpu信息 */
	GtkWidget *frame_down = gtk_frame_new("系统信息 ");
	gtk_table_attach_defaults(GTK_TABLE(table1), frame_down, 0, 10, 5, 10);
	gtk_widget_show(frame_down);
	/* 这里必须要show表，为什么？不知到该在什么时候show什么 */
	gtk_widget_show(table1);

	/* 在该狂建建一个表格，将下半部分为1行，2列 */
	GtkWidget *table_down = gtk_table_new(1, 2, TRUE);
	/* 将这个表添加到下面框架 */
	gtk_container_add(GTK_CONTAINER(frame_down), table_down);

	/* 建一个frame在表二左半部显示硬件信息 */
	GtkWidget *frame_left_down = gtk_frame_new("硬件");
	gtk_table_attach_defaults(GTK_TABLE(table_down), frame_left_down, 0, 1, 0,
			1);
	gtk_widget_show(frame_left_down);
	/* 这里必须要show表，为什么？不知到该在什么时候show什么 */
	gtk_widget_show(table_down);

	/* 容器 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_container_add(GTK_CONTAINER(frame_left_down), vbox);
	gtk_widget_show(vbox);
	/* 建一个标签显示cpu型号 */
	strcpy(cpuBuffer, "CPU型号和主频:\n");
	strcat(cpuBuffer, modeName);
	/* 这里不该有？
	 * gtk_widget_show(label);
	 * 原来是因为我们有清除cpuBuffer */
	/* 建一个标签显示cache大小 */
	strcat(cpuBuffer, "\n\nCache 大小:");
	strcat(cpuBuffer, cacheSize);
	/* 建一个标签显示cpu主频 */
	strcat(cpuBuffer, "\n\ncpu 主频:");
	strcat(cpuBuffer, cpuMHz);
	strcat(cpuBuffer, " MHz");
	/* 建一个标签显示cpu核数 */
	strcat(cpuBuffer, "\n\ncpu核数:");
	strcat(cpuBuffer, cpuCores);
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
	/* 建一个标签显示addrSize */
	strcat(cpuBuffer, "\n\n寻址位数:");
	strcat(cpuBuffer, addrSize);
	label = gtk_label_new(cpuBuffer);
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
	gtk_widget_show(label);

	/* 建一个frame在表二右半部显示系统版本信号 */
	GtkWidget *frame_right_down = gtk_frame_new("Ubuntu");
	GdkColor color;
	PangoFontDescription *font;
	/* 设置颜色 */
	gdk_color_parse("blue", &color);
	gtk_widget_modify_fg(frame_right_down, GTK_STATE_NORMAL, &color);
	/* 设置字体 */
	font = pango_font_description_from_string("San");
	pango_font_description_set_size(font, 30 * PANGO_SCALE);
	gtk_widget_modify_font(frame_right_down, font);
	gtk_table_attach_defaults(GTK_TABLE(table_down), frame_right_down, 1, 2, 0,
			1);
	gtk_widget_show(frame_right_down);
	/* 这里必须要show表，为什么？不知到该在什么时候show什么 */
	gtk_widget_show(table_down);

	/* 容器 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_container_add(GTK_CONTAINER(frame_right_down), vbox);
	gtk_widget_show(vbox);
	/* 建一个标签显示cpu型号 */
	memset(cpuBuffer, 0, 1000);
	memset(addrSize, 0, 50);
	getSysVersion("/proc/version", "version", addrSize);
	strcat(cpuBuffer, "\n\n内核版本 : ");
	strcat(cpuBuffer, addrSize);
	strcat(cpuBuffer, "\n\n系统版本 10.10 (maverick)");
	strcat(cpuBuffer, "\n\nGNOME 2.32.0");
	GtkWidget *label1 = gtk_label_new(cpuBuffer);
	gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 5);
	gtk_widget_show(label1);

	/* 新建一个frame框架用于显示进度条*/
	GtkWidget *frame_cpu = gtk_frame_new("cpu使用率");
	gtk_table_attach_defaults(GTK_TABLE(table1), frame_cpu, 8, 10, 0, 5);
	gtk_widget_show(frame_cpu);

	/* 创建第一个进度条
	 * GTK_PROGRESS_BOTTOM_TO_TOP */
	pbar_cpu = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(frame_cpu), pbar_cpu);
	gtk_progress_bar_set_orientation(pbar_cpu, GTK_PROGRESS_BOTTOM_TO_TOP);
	gtk_widget_show(pbar_cpu);

	/* 容器 放在右下角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table1), vbox, 6, 10, 7, 10);
	gtk_widget_show(vbox);
	gtk_widget_show(table1);

	/* 创建一个图像 */
	GtkWidget *image = gtk_image_new_from_file("4.png");
	gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 3);
	gtk_widget_show(image);

	/* 容器 放在右下角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table1), vbox, 0, 5, 7, 10);
	gtk_widget_show(vbox);
	gtk_widget_show(table1);

	/* 创建一个图像 */
	image = gtk_image_new_from_file("1.png");
	gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 3);
	gtk_widget_show(image);
}

#endif /* CPU_H_ */
