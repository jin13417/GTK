/*
 *  menuBar.h
 *  systemMonitor
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef MENUBAR_H_
#define MENUBAR_H_
#include <stdio.h>
#include <gtk/gtk.h>
static gint button_press(GtkWidget *, GdkEvent *);
static void menuitem_response(gchar *);
#define BACK_IMAGE ("3.jpg")
int createMenuBar(GtkWidget *vbox)
{
	GtkWidget *menu;
	GtkWidget *menu_bar;
	GtkWidget *monitor_menu;
	GtkWidget *edit_menu;
	GtkWidget *view_menu;
	GtkWidget *help_menu;
	GtkWidget *menu_items;
	char buf[128];
	int i;
	/* 初始化菜单构件,记住,永远也不要用
	 * gtk_show_widget() 来显示菜单构件。
	 * 这个是包含菜单项的菜单,当你在程序的"Root Menu"上点击时
	 * 它会弹出来 */
	menu = gtk_menu_new();
	update_widget_bg(menu,"3.jpg");
	/* 创建一个新的菜单项,名称为... */
	menu_items = gtk_menu_item_new_with_label("刷新模块");
	/* ...并将它加到菜单。 */
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
	/* 当菜单项被选中时做点有趣的事 */
	g_signal_connect_swapped(G_OBJECT(menu_items), "activate", G_CALLBACK(
			set_modul_info), NULL);
	/* 显示构件 */
	gtk_widget_show(menu_items);
	menu_items = gtk_menu_item_new_with_label("装载模块");
	/* ...并将它加到菜单。 */
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
	/* 当菜单项被选中时做点有趣的事 */
	g_signal_connect_swapped(G_OBJECT(menu_items), "activate", G_CALLBACK(
			add_modul), NULL);
	/* 显示构件 */
	gtk_widget_show(menu_items);
	menu_items = gtk_menu_item_new_with_label("卸载模块");
	/* ...并将它加到菜单。 */
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
	/* 当菜单项被选中时做点有趣的事 */
	g_signal_connect_swapped(G_OBJECT(menu_items), "activate", G_CALLBACK(
			remove_modul), NULL);
	/* 显示构件 */
	gtk_widget_show(menu_items);
	/*
	 * 接着我们用一个小循环为"test-menu"产生三个菜单条目。
	 * 注意对 gtk_menu_append 的调用。这里我们将一序列的菜单项
	 * 加到我们的菜单上。通常,我们也捕获每个菜单项的"clicked"
	 * 信号并为它设置一个回调,不过在这里这个被省略了以节省空间。 */
	for (i = 0; i < 3; i++)
	{
		/* 将名称复制到 buf. */
		sprintf(buf, "版权所有", i);
		/* 创建一个新的菜单项,名称为... */
		menu_items = gtk_menu_item_new_with_label(buf);
		/* ...并将它加到菜单。 */
		gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
		/* 当菜单项被选中时做点有趣的事 */
		g_signal_connect_swapped(G_OBJECT(menu_items), "activate", G_CALLBACK(
				menuitem_response), g_strdup(buf));
		/* 显示构件 */
		gtk_widget_show(menu_items);
	}
	/* 这个是根菜单,将成为显示在菜单栏上的标签。
	 * 这里不会附上一个信号处理函数,因为它只是在
	 * 被按下时弹出其余的菜单。 */
	monitor_menu = gtk_menu_item_new_with_label("监视器(M)");
	edit_menu = gtk_menu_item_new_with_label("编辑(E)");
	view_menu = gtk_menu_item_new_with_label("查看(V)");
	help_menu = gtk_menu_item_new_with_label("帮助(H)");
	gtk_widget_show(monitor_menu);
	gtk_widget_show(edit_menu);
	gtk_widget_show(view_menu);
	gtk_widget_show(help_menu);
	/* 现在我们指定我们想要让新创建的"menu"成
	 * 为"root menu"的菜单 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(monitor_menu), menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_menu), menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view_menu), menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_menu), menu);
	/* 创建一个菜单栏以包含菜单,并将它加到主窗口
	 * 一个纵向盒子里: */
	menu_bar = gtk_menu_bar_new();
	update_widget_bg(menu_bar,"3.jpg");
//	update_widget_bg(menu_bar, BACK_IMAGE);

	gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 2);
	gtk_widget_show(menu_bar);
	/* 最后把菜单项添加到菜单栏上 -- 这就是我
	 * 咆哮了多次的“根”菜单项 =) */
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), monitor_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), edit_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), view_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_menu);
	return 0;
}
int createButtonMenu(GtkWidget *vbox)
{
	GtkWidget *menu;
	GtkWidget *menu_items;
	GtkWidget *button;

	/* 初始化菜单构件,记住,永远也不要用
	 * gtk_show_widget() 来显示菜单构件。
	 * 这个是包含菜单项的菜单,当你在程序的"Root Menu"上点击时
	 * 它会弹出来 */
	menu = gtk_menu_new();
	/* 创建一个新的菜单项,名称为... */
	menu_items = gtk_menu_item_new_with_label("Sure to kill the process !!??");
	/* ...并将它加到菜单。 */
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
	/* 当菜单项被选中时做点有趣的事 */
	g_signal_connect_swapped(G_OBJECT(menu_items), "activate", G_CALLBACK(
			killProcess), NULL);
	/* 显示构件 */
	gtk_widget_show(menu_items);

	/* 创建一个按钮,它带了一个弹出菜单 */
	button = gtk_button_new_with_label(
			"*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*");
	/* 连接弹出菜单 */
	g_signal_connect_swapped(G_OBJECT(button), "event",
			G_CALLBACK(button_press), menu);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 2);
	gtk_widget_show(button);
	return 0;
}
/* 对鼠标按下作出回应,弹出 widget 变量传递进来的菜单。
 * 注意"widget"参数是被传递进来的菜单,不是
 * 被按下的按钮。
 */
static gint button_press(GtkWidget *widget, GdkEvent *event)
{
	if (event->type == GDK_BUTTON_PRESS)
	{
		GdkEventButton *bevent = (GdkEventButton *) event;
		gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL,
				bevent->button, bevent->time);
		/* 告诉调用代码我们已经处理了这个事件;事件传播(buck)在
		 * 这里停止。 */
		return TRUE;
	}
	/* 告诉调用代码我们没有处理这个事件;继续传播它。 */
	return FALSE;
}
/* 当菜单项被选中时打印一个字符串 */
static void menuitem_response(gchar *string)
{
	showAbout();
}

#endif /* MENUBAR_H_ */
