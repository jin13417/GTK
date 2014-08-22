/*File:statusbar.c
 *Date:2013-12-22
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>

GtkWidget *status_bar;

void push_item(GtkWidget *widget,gpointer data)
{
    static int count = 1;
    char buf[20] = {'\0'};
    
    g_snprintf(buf,20,"Item %d",count++);
    //将新消息加到状态栏
    gtk_statusbar_push(GTK_STATUSBAR(status_bar),GPOINTER_TO_INT(data),buf);
    return;
}

void pop_item(GtkWidget *widget,gpointer data)
{
    //删除在栈中给定上下文标识符最上面的一个消息
    gtk_statusbar_pop(GTK_STATUSBAR(status_bar),GPOINTER_TO_INT(data));
    return;
}

int main(int argc, char*argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *vbox;
    gint context_id;

	//初始化GTK
	gtk_init(&argc,&argv);
	//创建最上层主窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//连接信号"delete_event",使得窗口关闭时发生
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	//设置窗口标题	
    gtk_window_set_title(GTK_WINDOW(window),"GTK 状态栏工具");
	//设定窗口的默认宽高
	//gtk_window_set_default_size(GTK_WINDOW(window),200,300);
	//设定窗口的位置,让窗口总在最前端
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//设定容器边框的宽度
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

    vbox = gtk_vbox_new(FALSE,1);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show(vbox);

    //创建一个状态栏
    status_bar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox),status_bar,TRUE,TRUE,0);
    gtk_widget_show(status_bar);

    //获得上下文的标识符
    context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(status_bar),"Statusbar example");

    button = gtk_button_new_with_label("push_item");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(push_item),GINT_TO_POINTER(context_id));
    gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,2);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("pop last item");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(pop_item),GINT_TO_POINTER(context_id));
    gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,2);
    gtk_widget_show(button);

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
