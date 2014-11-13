/*
 *  showAbout.h
 *  systemMonitor
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef SHOWABOUT_H_
#define SHOWABOUT_H_

void showAbout(void)
{

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("3.png", NULL);

	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Ubuntu 系统监视器");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "beta0.1");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),
			"Copyright © 2012-2114 ZhuShengben");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "查看当前进程，监视系统状态 .");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),
			"http://user.qzone.qq.com/337075552");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	g_object_unref(pixbuf), pixbuf = NULL;
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

/* 创建一个滚动文本区域,用于显示一个"信息" */
void createAboutPage(GtkWidget* notebook)
{
	GtkWidget *label;
	GtkWidget *table;
	GtkWidget *button;
	GtkWidget *align;
	GtkWidget *tooltip;
	GtkWidget *vbox;
	GtkWidget *scrolled_window;
	GtkWidget *view;
	GtkWidget *vpaned;
	GtkTextBuffer * buffer;
	GtkWidget *frame = gtk_frame_new("编辑邮件");
	gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
	gtk_widget_set_size_request(frame, 120, 500);
	gtk_widget_show(frame);
	/* 将该标签页加入到notebook中 */
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, gtk_label_new(
			"错误报告"));

	/* 在顶级窗口上添加一个垂直分栏窗口构件 */
	vpaned = gtk_vpaned_new();
	gtk_container_add(GTK_CONTAINER(frame), vpaned);
	gtk_widget_show(vpaned);
	/* 在分栏窗口的两部分各添加一些构件 */
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_paned_add1(GTK_PANED(vpaned), scrolled_window);
	view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window), view);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	insert_text(buffer, TRUE);
	gtk_widget_show_all(scrolled_window);
	gtk_widget_show(scrolled_window);

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_paned_add2(GTK_PANED(vpaned), scrolled_window);
	view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window), view);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	insert_text(buffer, FALSE);
	gtk_widget_show_all(scrolled_window);
	gtk_widget_show(scrolled_window);

	/* 建一个表格，将下半部分为10行，10列 */
	//	table = gtk_table_new(10, 10, TRUE);
	/* 将这个表添加到框架 */
	//	gtk_container_add(GTK_CONTAINER(frame), table);
	/* 创建一个居中对齐的对象 */
	align = gtk_alignment_new(0.5, 0.5, 0.8, 0);
	gtk_container_add(GTK_CONTAINER(frame), align);
	gtk_widget_show(align);

	button = gtk_button_new_with_label("Submit");
	gtk_container_add(GTK_CONTAINER(align), button);
	tooltip = gtk_tooltips_new();
	gtk_tooltips_set_tip(tooltip, button, "点击发送", NULL);
	gtk_widget_show(button);

}
/* 向文本构件中添加一些文本*/
void insert_text(GtkTextBuffer *buffer, gboolean thanks)
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	if (TRUE == thanks)
		gtk_text_buffer_insert(buffer, &iter,//
				"From:  	    @nasa.gov\n"
					"To: SillyBenzhu@gmail.com\n"
					"Subject: Bugs found !\n"
					"There are some bugs just as follows:\n"
				//
				, -1);
	else
		gtk_text_buffer_insert(buffer, &iter,//
				"介绍\n"
					"*\n"
					"系统监视器手册 V2.2\n"
					"	系统监视器程序使您能够显示系统的基本信息，并能够监视系统进程、系统资源使用情况和文件系统。您也可以用系统监视器来修改系统的行为。\n"
					"系统监视器包含四个选项卡部分\n"
					"系统\n"
					"	显示计算机硬件和软件的不同基本信息。\n"
					"发行版\n"
					"*\n"
					"	发行版版本\n"
					"*\n"
					"	Linux 内核版本\n"
					"*\n"
					"	GNOME 版本\n"
					"	硬件\n"
					"*\n"
					"	安装的内存\n"
					"*\n"
					"	处理器和速度\n"
					"	系统状态\n"
					"*\n"
					"	当前可用磁盘空间\n"
					"处理器\n"
					"	显示活动进程和进程之间的相互关系。为每个单独进程提供详细信息，并使您能够控制活动进程。\n"
					"	资源\n"
					"	显示以下系统资源的当前使用情况。\n"
					"*\n"
					"	CPU(中央处理器)时间\n"
					"*\n"
					"	内存和交换空间\n"
					"*\n"
					"	网络使用情况\n"
					"	文件系统\n"
					"% CPU\n"
					"	选中此项以显示进程当前使用的 CPU 时间百分率。\n"
					"CPU 时间\n"

					"	选中此项以显示进程已作用的 CPU 时间。\n"

					"启动\n"

					"	选中此项以显示进程开始运行的时间。\n"

					"优先级\n"

					"	选中此项以显示进程的 nice 值。nice 值设置进程的优先级：nice 值越低，优先极越高。\n"

					"ID\n"

					"	选中此项以显示进程标识符，也即 pid。pid 是一个唯一标识进程的数字。您可以使用 pid 在命令行操纵进程。\n"

					"内存\n"

					"	选中此项以显示进程当前占用的系统内存大小。\n"

				//
				, -1);
}
/* 设置背景图片 */
void update_widget_bg(GtkWidget *widget, gchar *img_file)
{
	GtkStyle *style;
	GdkPixbuf *pixbuf;
	GdkPixmap *pixmap;
	gint width, height;

	pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);
	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);
	pixmap = gdk_pixmap_new(NULL, width, height, 24);
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);
	style = gtk_style_copy(GTK_WIDGET(widget)->style);

	if (style->bg_pixmap[GTK_STATE_NORMAL])
		g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);

	style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);
	gtk_widget_set_style(GTK_WIDGET(widget), style);
	g_object_unref(style);
}
#endif /* SHOWABOUT_H_ */
