/*File:color.c
 *Date:2014-01-06
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>

int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *event_box;
    GtkWidget *label;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"My first program helloworld!");
   
    /**/
    gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (GTK_OBJECT(window), "destroy",G_CALLBACK (gtk_main_quit), (gpointer)window);
    
    /*创建一个事件盒，并将它加到顶级窗口上*/
    event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(window),event_box);
    gtk_widget_show(event_box);

    /*创建一个长标签*/
    label = gtk_label_new("点击这里，退出");
    gtk_container_add(GTK_CONTAINER(event_box),label);
    gtk_widget_show(label);

    /*将标签剪裁短*/
    gtk_widget_set_size_request(label,110,20);

    /*为它绑定一个动作*/
    gtk_widget_set_events(event_box,GDK_BUTTON_PRESS_MASK);
    g_signal_connect(GTK_OBJECT(event_box),"button_press_event",G_CALLBACK(gtk_main_quit),NULL);

    /*要设置鼠标式样也要有X窗口，
     * gtk_widget_realize使构件在没有show之前就形成X窗口*/
    gtk_widget_realize(event_box);
    gdk_window_set_cursor(event_box->window,gdk_cursor_new(GDK_HAND1));


    gtk_widget_show (window);
    
    /* 所有的 GTK 程序必须有一个 gtk_main() 函数。程序运行停在这里
     * 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
