/*File:tableBox.c
 *Date:2013-11-27
 *Author:sjin
 *Mail:413977243@qq.com
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

/*回调函数
 *传到这个函数的数据将呗打印到标准输出
 * */
void callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again -%s was pressed\n",(char *) data);
}

/*退出回调函数*/
gint delete_event(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    gtk_main_quit();
    return FALSE;
}


int main(int argc,char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;

    /*初始化*/
    gtk_init(&argc,&argv);

    /*创建窗口*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*这个一般必要有delete_event信号到主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
    
    /*设置窗口宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),80);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"表组装练习");

    /* 创建一个2X2的表
     *GtkWidget *gtk_table_new(guint rows,guint columns,gboolean homogeneous);
     *rows:表中要安排的行数
     *columns:表中要安排的列数
     *homogeneous:TRUE标示表格框的大小都将调整为表中最大构件的大小。
     *            FALSE每个表格框将会按照同行中最高的构件，与同列中最宽的构件来决定自身的大小
     * */
    table = gtk_table_new(2,2,TRUE);

    /*将表放进主窗口*/
    gtk_container_add(GTK_CONTAINER(window),table);

    /*创建一个按钮*/
    button = gtk_button_new_with_label("love you!");

    /*将按钮设置回调函数*/
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(callback),(gpointer)"I love you songsong!");

    /*将button插入表的左上象限
     *void gtk_table_attach(GtkTable *table,已经创建的表
     *GtkWidget *child,想放进表里的构件
     *guint left_attach,构件的放置位置
     *guint right_attach,
     *guint top_attach,
     *guint bottom_attach,
     *GtkAttachOptions xoptions,下面是用来指定组装时的选项GTK_FILL：构件会扩展以是用所有可用空间
     *GtkAttachOptions yoptions,GTK_SHRINK：构件会和表一个缩小 GTK_EXPAND：
     *guint xpadding,下面2个padding，构件周围的空白区域
     *guint ypadding);
     *这里有个简写的函数
     *void gtk_table_attach_defaults();
     *默认缺省参数options:GTK_FILL|GTK_EXPAND padding:为0；
     *
     * */
    gtk_table_attach_defaults(GTK_TABLE(table),button,0,1,0,1);

    gtk_widget_show(button);

    /*创建第二个按钮*/
    button = gtk_button_new_with_label("miss you!");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(callback),(gpointer)"I miss you songsong!");
    gtk_table_attach_defaults(GTK_TABLE(table),button,1,2,0,1);
    gtk_widget_show(button);

    /*创建quit按钮*/
    button = gtk_button_new_with_label("quit");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button,0,2,1,2);
    gtk_widget_show(button);

    gtk_widget_show(table);
    gtk_widget_show(window);

    gtk_main();
    return 0;
}
