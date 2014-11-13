/*
 *  memory.h
 *  systemMonitor
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef MEMORY_H_
#define MEMORY_H_

typedef struct _ProgressData
{
	GtkWidget *frame1;
	GtkWidget *pbar;
	GtkWidget *pbar1;
	GtkWidget *pbar2;
	GtkWidget *pbar3;
	gboolean activity_mode;
} ProgressData;
ProgressData *pdata_mem;

GtkWidget *label_memSize;
GtkWidget *label_freeSize;
GtkWidget *label_cacheSize;
GtkWidget *label_cacheUse;

gdouble memUseRatio, swapUse;

char totalMem[20], freeMem[20], SwapTotal[20], SwapFree[20];
char Buffers[20], Cached[20], buffer[40];
/* 更新进度条,这样就能够看到进度条的移动 */
gint progress_timeout(gpointer data);

/* MEMERY标签页，显示内存信息 */
void createMemPage(GtkWidget* notebook)
{
	GtkWidget *align;
	GtkWidget *table;
	GtkWidget *vbox;
	GtkWidget *image;
	GdkColor color;
	PangoFontDescription *font;
	memUseRatio = 0;
	memset(buffer, 0, 40);

	/* 为传递到回调函数中的数据分配内存 */
	pdata_mem = g_malloc(sizeof(ProgressData));

	pdata_mem->frame1 = gtk_frame_new("");
	gtk_container_set_border_width(GTK_CONTAINER(pdata_mem->frame1), 0);
	gtk_widget_set_size_request(pdata_mem->frame1, 120, 500);

	gtk_widget_show(pdata_mem->frame1);
	/* 将该标签页加入到notebook中 */
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), pdata_mem->frame1,
			gtk_label_new("内存信息"));

	/* 建一个表格，将下半部分为10行，10列 */
	table = gtk_table_new(10, 10, TRUE);
	/* 将这个表添加到框架 */
	gtk_container_add(GTK_CONTAINER(pdata_mem->frame1), table);

	/* 创建进度条 */
	 /* 新建一个frame框架用于显示进度条*/
	GtkWidget *frame_cpu = gtk_frame_new("内存");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_cpu, 0, 5, 0, 3);
	gtk_widget_show(frame_cpu);
	/* 容器 */
	vbox = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_container_add(GTK_CONTAINER(frame_cpu), vbox);
	gtk_widget_show(vbox);
	gtk_widget_show(table);
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0.8, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 创建第一个进度条
	 * GTK_PROGRESS_BOTTOM_TO_TOP */
	pdata_mem->pbar = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(align), pdata_mem->pbar);
	gtk_progress_bar_set_orientation(pdata_mem->pbar,
			GTK_PROGRESS_LEFT_TO_RIGHT);
	gtk_widget_show(pdata_mem->pbar);
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0.8, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 创建第二个进度条 */
	pdata_mem->pbar1 = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(align), pdata_mem->pbar1);
	//	toggle_show_text("内存使用率", pdata_mem);
	toggle_activity_mode(FALSE, pdata_mem);
	gtk_widget_show(pdata_mem->pbar1);

	/* 新建一个frame框架用于显示进度条*/
	frame_cpu = gtk_frame_new("交换区");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_cpu, 5, 10, 0, 3);
	gtk_widget_show(frame_cpu);
	vbox = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_container_add(GTK_CONTAINER(frame_cpu), vbox);
	gtk_widget_show(vbox);
	gtk_widget_show(table);
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0.8, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 创建第三个进度条 */
	pdata_mem->pbar2 = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(align), pdata_mem->pbar2);
	toggle_show_text("内存交换区", pdata_mem);
	toggle_activity_mode(FALSE, pdata_mem);
	gtk_widget_show(pdata_mem->pbar2);

	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0.8, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 创建第四个进度条 */
	pdata_mem->pbar3 = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(align), pdata_mem->pbar3);
	toggle_show_text("交换区使用量", pdata_mem);
	toggle_activity_mode(FALSE, pdata_mem);
	gtk_widget_show(pdata_mem->pbar3);

	/* 加上这一行后，出现问题
	 * faile to NULL to ProgressBar
	 * 关于timer的使用不明白 */
	/* 不断刷新画图 */
	//gtk_timeout_add(100, (GtkFunction) progress_timeout, pdata_mem);
	progress_timeout(pdata_mem);

	/*************************************/

	/* 容器 放在左下角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0, 6, 4, 10);
	gtk_widget_show(vbox);
	gtk_widget_show(table);
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 建一个标签显示内存大小 */
	label_memSize = gtk_label_new(buffer);
	gtk_container_add(GTK_CONTAINER(align), label_memSize);
	font = pango_font_description_from_string("San");
	pango_font_description_set_size(font, 15 * PANGO_SCALE);
	gtk_widget_modify_font(label_memSize, font);
	/* 设置控件可容字数从而设置其大小 */
	gtk_label_set_width_chars(GTK_LABEL(label_memSize), 20);
	/* 设置控件对齐方式
	 * 第一个参数是lblTest,第二个参数是左右方向的对齐值，第三个参数是上下方向的对齐值;
	 *对齐值的取值范围为0-1.取0时，为左对齐,取1时,为右对齐,取0.5时，为中间对齐. */
	gtk_misc_set_alignment(GTK_MISC(label_memSize), 0, 0.5);
	gtk_widget_show(label_memSize);
	/****************************************************/
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 建一个标签显示空闲区大小 */
	label_freeSize = gtk_label_new(buffer);
	gtk_container_add(GTK_CONTAINER(align), label_freeSize);
	/* 设置颜色 */
	gdk_color_parse("red", &color);
	gtk_widget_modify_fg(label_freeSize, GTK_STATE_NORMAL, &color);
	/* 设置字体 */
	font = pango_font_description_from_string("San");
	pango_font_description_set_size(font, 15 * PANGO_SCALE);
	gtk_widget_modify_font(label_freeSize, font);
	/* 设置控件可容字数从而设置其大小 */
	gtk_label_set_width_chars(GTK_LABEL(label_freeSize), 20);
	/* 设置控件对齐方式
	 * 第一个参数是lblTest,第二个参数是左右方向的对齐值，第三个参数是上下方向的对齐值;
	 *对齐值的取值范围为0-1.取0时，为左对齐,取1时,为右对齐,取0.5时，为中间对齐. */
	gtk_misc_set_alignment(GTK_MISC(label_freeSize), 0, 0.5);
	gtk_widget_show(label_freeSize);
	/****************************************************/
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 建一个标签显示cache大小 */
	label_cacheSize = gtk_label_new(buffer);
	gtk_container_add(GTK_CONTAINER(align), label_cacheSize);
	/* 设置颜色 */
	gdk_color_parse("black", &color);
	gtk_widget_modify_fg(label_cacheSize, GTK_STATE_NORMAL, &color);
	/* 设置字体 */
	font = pango_font_description_from_string("San");
	pango_font_description_set_size(font, 15 * PANGO_SCALE);
	gtk_widget_modify_font(label_cacheSize, font);
	/* 设置控件可容字数从而设置其大小 */
	gtk_label_set_width_chars(GTK_LABEL(label_cacheSize), 20);
	/* 设置控件对齐方式
	 * 第一个参数是lblTest,第二个参数是左右方向的对齐值，第三个参数是上下方向的对齐值;
	 *对齐值的取值范围为0-1.取0时，为左对齐,取1时,为右对齐,取0.5时，为中间对齐. */
	gtk_misc_set_alignment(GTK_MISC(label_cacheSize), 0, 0.5);
	gtk_widget_show(label_cacheSize);
	/****************************************************/
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
	gtk_widget_show(align);
	/* 建一个标签显示空闲区大小 */
	label_cacheUse = gtk_label_new(buffer);
	gtk_container_add(GTK_CONTAINER(align), label_cacheUse);

	/* 设置颜色 */
	gdk_color_parse("black", &color);
	gtk_widget_modify_fg(label_cacheUse, GTK_STATE_NORMAL, &color);
	/* 设置字体 */
	font = pango_font_description_from_string("San");
	pango_font_description_set_size(font, 15 * PANGO_SCALE);
	gtk_widget_modify_font(label_cacheUse, font);
	/* 设置控件可容字数从而设置其大小 */
	gtk_label_set_width_chars(GTK_LABEL(label_cacheUse), 20);
	/* 设置控件对齐方式
	 * 第一个参数是lblTest,第二个参数是左右方向的对齐值，第三个参数是上下方向的对齐值;
	 *对齐值的取值范围为0-1.取0时，为左对齐,取1时,为右对齐,取0.5时，为中间对齐. */
	gtk_misc_set_alignment(GTK_MISC(label_cacheUse), 0, 0.5);
	gtk_widget_show(label_cacheUse);
	/**********************************************/
	/* 容器 放在中间角角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0, 10, 3, 8);
	gtk_widget_show(vbox);
	gtk_widget_show(table);

	/* 新建一个frame框架用于显示进度条*/
	frame_cpu = gtk_frame_new("");
	gtk_table_attach_defaults(GTK_TABLE(table), frame_cpu, 0, 10, 3, 4);
	gtk_widget_show(frame_cpu);
	/* 创建一个进度条 */
	createProgressBar(frame_cpu);

	/* 容器 放在右下角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 4, 10, 5, 10);
	gtk_widget_show(vbox);
	gtk_widget_show(table);

	/* 创建一个图像 */
	image = gtk_image_new_from_file("penguin.gif");
	gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 3);
	gtk_widget_show(image);

	/* 容器 放在右下角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 3, 7, 8, 10);
	gtk_widget_show(vbox);
	gtk_widget_show(table);

	/* 创建一个图像 */
	image = gtk_image_new_from_file("5.png");
	gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 3);
	gtk_widget_show(image);

	/* 容器 放在右下角 */
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0, 2, 4, 6);
	gtk_widget_show(vbox);
	gtk_widget_show(table);

	/* 创建一个图像 */
	image = gtk_image_new_from_file("a.png");
	gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 3);
	gtk_widget_show(image);

}

/* 更新进度条,这样就能够看到进度条的移动 */
gint progress_timeout(gpointer data)
{

	if (pdata_mem->activity_mode)
		gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pdata_mem->pbar));
	else
	{
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar),
				memUseRatio);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar1), 1
				- memUseRatio);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar2),
				swapUse);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar3), 1
				- swapUse);
	}

	return TRUE;
}
/* 设置进度条的滑槽上的文本显示 */
void toggle_show_text(const gchar *text, ProgressData *pdata_mem)
{
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata_mem->pbar), "内存使用率");
}
/* 设置进度条的活动模式 */
void toggle_activity_mode(gboolean activity_mode, ProgressData *pdata_mem)
{
	pdata_mem->activity_mode = activity_mode;
}
/* 回调函数,切换进度条的移动方向 */
void toggle_orientation(GtkWidget *widget, ProgressData *pdata_mem)
{
	switch (gtk_progress_bar_get_orientation(GTK_PROGRESS_BAR(pdata_mem->pbar)))
	{
	case GTK_PROGRESS_LEFT_TO_RIGHT:
		gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pdata_mem->pbar),
				GTK_PROGRESS_RIGHT_TO_LEFT);
		break;
	case GTK_PROGRESS_RIGHT_TO_LEFT:
		gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pdata_mem->pbar),
				GTK_PROGRESS_LEFT_TO_RIGHT);
		break;
	default:
		;// 什么也不做
	}
}
/* 清除分配的内存,删除定时器(timer) */
void destroy_progress(GtkWidget *widget, ProgressData *pdata_mem)
{
	pdata_mem->frame1 = NULL;
	pdata_mem->pbar = NULL;
	pdata_mem->pbar1 = NULL;
	pdata_mem->pbar2 = NULL;
	pdata_mem->pbar3 = NULL;
	g_free(pdata_mem);
	gtk_main_quit();
}

void set_label_mem_text(void)
{
	getInfor("/proc/meminfo", "MemTotal", totalMem);
	getInfor("/proc/meminfo", "MemFree", freeMem);
	getInfor("/proc/meminfo", "SwapTotal", SwapTotal);
	getInfor("/proc/meminfo", "SwapFree", SwapFree);
	float total_mem = (float) atoi(totalMem);
	float free_mem = (float) atoi(freeMem);
	memUseRatio = 1 - free_mem / total_mem;
	float total_swap = (float) atoi(SwapTotal);
	float free_swap = (float) atoi(SwapFree);
	swapUse = 1 - free_swap / total_swap;
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar),
			memUseRatio);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar1), 1
			- memUseRatio);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar2), swapUse);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata_mem->pbar3), 1
			- swapUse);
	char p[20] = "内存使用率(", buf[10];
	gcvt(memUseRatio * 100, 4, buf);
	strcat(buf, "%)");
	strcat(p, buf);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata_mem->pbar), p);
	char p1[20] = "内存剩余量(", buf1[10];
	gcvt(100 - memUseRatio * 100, 4, buf1);
	strcat(buf1, "%)");
	strcat(p1, buf1);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata_mem->pbar1), p1);
	char p2[20] = "交换区使用率(", buf2[10];
	gcvt(swapUse * 100, 4, buf2);
	strcat(buf2, "%)");
	strcat(p2, buf2);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata_mem->pbar2), p2);
	char p3[20] = "交换区剩余量(", buf3[10];
	gcvt(100 - swapUse * 100, 4, buf3);
	strcat(buf3, "%)");
	strcat(p3, buf3);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata_mem->pbar3), p3);

	char buffer[100] = "";
	strcat(buffer, "\n\n内存大小    : ");
	strcat(buffer, totalMem);
	strcat(buffer, " MB");
	gtk_label_set_text((GtkLabel*) label_memSize, buffer);

	memset(buffer, 0, 40);
	strcat(buffer, "\n空闲区大小 : ");
	strcat(buffer, freeMem);
	strcat(buffer, " MB");
	gtk_label_set_text((GtkLabel*) label_freeSize, buffer);

	getInfor("/proc/meminfo", "Buffers", Buffers);
	memset(buffer, 0, 40);
	strcat(buffer, "\n缓存大小   : ");
	strcat(buffer, Buffers);
	strcat(buffer, " MB");
	gtk_label_set_text((GtkLabel*) label_cacheSize, buffer);

	getInfor("/proc/meminfo", "Cached", Cached);
	memset(buffer, 0, 40);
	strcat(buffer, "\nCached大小   : ");
	strcat(buffer, Cached);
	strcat(buffer, " MB");
	gtk_label_set_text((GtkLabel*) label_cacheUse, buffer);
}
#endif /* MEMORY_H_ */
