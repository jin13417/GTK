
/*File:frames.c
 *Date:2014-02-09
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>


int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *frames;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"Frame Example!");
   
    /**/
    gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (GTK_OBJECT(window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
    
    gtk_widget_set_size_request(window,300,300);
    /*设置窗口的边框宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),5);

    /**/
    frames = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window),frames);

    /*设置框架的标签*/
    gtk_frame_set_label(GTK_FRAME(frames),"GTK Frame widget");

    /*将标签定位在框架的右边*/
    gtk_frame_set_label_align(GTK_FRAME(frames),1.0,0.0);

    /*设置框架的风格*/
    gtk_frame_set_shadow_type(GTK_FRAME(frames),GTK_SHADOW_OUT);

    gtk_widget_show(frames);

    gtk_widget_show(window);

     /* 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
