/*File:Toggle_button.c
 *Date:2013-12-07
 *Author:sjin
 *Mail:413977243@qq.com
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

/*开关按钮：
 *  由一般按钮派生而来，只是开关按钮只有两个状态，通过点击
 *  可以切换。
 *  开关按钮是复选按钮和单选按钮的基础，所以单选按钮和复选按钮继承了
 *  许多开关按钮的函数调用
 */

    GtkWidget *button1;
    GtkWidget *button2;

/*回调函数
 *传到这个函数的数据将呗打印到标准输出
 * */
void Toggle_Button_callback(GtkWidget *widget, gpointer data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
        g_print(" 按钮被按下\n");
    }else{
        g_print("按钮是弹起的\n",(char *) data);

    }
}

void callback(GtkWidget *widget, gpointer data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button1))){
        g_print(" 数学被选中\n");
    }else{
        g_print("nothing\n");
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button2))){
        g_print(" 语文被选中\n");
    }else{
        g_print("nothing\n");
    }
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
    GtkWidget *box;

    /*初始化*/
    gtk_init(&argc,&argv);

    /*创建窗口*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*这个一般必要有delete_event信号到主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
    
    /*设置窗口宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),20);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"开关按钮练习");
    
    /*创建一个组装盒子*/
    box = gtk_vbox_new(FALSE,0);

    /*设置一个开关按钮*/
    button = gtk_toggle_button_new_with_label("打开");
    /*设置按钮的状态，默认为弹起 FALSE .*/
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),FALSE);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Toggle_Button_callback),(gpointer)"cool button");
    gtk_box_pack_start(GTK_BOX(box),button,TRUE,TRUE,0);
    gtk_widget_show(button);

    /***************设置复选按钮****************/
    button1 = gtk_check_button_new_with_label("数学");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button1),TRUE);
    gtk_box_pack_start(GTK_BOX(box),button1,TRUE,TRUE,0);
    gtk_widget_show(button1);

    button2 = gtk_check_button_new_with_label("语文");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button2),TRUE);
    gtk_box_pack_start(GTK_BOX(box),button2,TRUE,TRUE,0);
    gtk_widget_show(button2);

    button = gtk_button_new_with_label("OK");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),TRUE);
    gtk_box_pack_start(GTK_BOX(box),button,TRUE,TRUE,0);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(callback),NULL);
    gtk_widget_show(button);

    gtk_container_add(GTK_CONTAINER(window),box);

    gtk_widget_show(box);
    gtk_widget_show(window);
    

    gtk_main();
    return 0;
}
