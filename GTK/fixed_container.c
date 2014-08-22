/*File:color.c
 *Date:2014-01-07
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

/*用全局变量储存固定容器里构件的位置*/
gint x = 50;
gint y = 50;

/*这个回调函数将按钮移动到固定容器的位置*/
void move_button(GtkWidget *widget,GtkWidget *fixed)
{
    x = (x + 30)%300;
    y = (y + 30)%300;
    gtk_fixed_move(GTK_FIXED(fixed),widget,x,y);
}

int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *fixed;
    gint i;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"Fixed Container");
   
    /**/
    gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (GTK_OBJECT(window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
    
    /*设置窗口的边框宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    /*创建一个固定容器*/
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_widget_show(fixed);

    for(i = 0; i < 3; i++){
        /*创建一个按钮*/
        button = gtk_button_new_with_label("miss you!");

        g_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(move_button),fixed);

        /*将按钮组装到一个固定容器的窗口中*/
        gtk_fixed_put(GTK_FIXED(fixed),button,i*50,i*50);

        gtk_widget_show(button);
    }

    gtk_widget_show (window);
    
    /* 所有的 GTK 程序必须有一个 gtk_main() 函数。程序运行停在这里
     * 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
