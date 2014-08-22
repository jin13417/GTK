
/*File:Radio_Button.c
 *Date:2013-12-03
 *Author:sjin
 *Mail:413977243@qq.com
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

/*创建单选按钮，点击close 回输出那个单选按钮被点击
 * 单选按钮是分组的，一个组中只能有一个对象被选中、按下
 *当应用程序中，要从多个选项中选中一个时用到
 */

enum Subject{
    SHUXVE,
    YUWEN,
    YINGYU
};
    GtkWidget *button1;//语文
    GtkWidget *button2;//数学
    GtkWidget *button3;//英语

void Radio_Button_callback(GtkWidget *widget,gpointer data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button1))){
        g_print("语文被点击\n");
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button2))){
        g_print("数学被点击\n");
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button3))){
        g_print("英语被点击\n");
    }

}

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
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *separator;
    GSList *group;

    /*初始化*/
    gtk_init(&argc,&argv);

    /*创建窗口*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*这个一般必要有delete_event信号到主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
    
    /*设置窗口宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),0);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"单选按钮练习");

    box1 = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),box1);
    gtk_widget_show(box1);

    box2 = gtk_vbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);
    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);

    button1 = gtk_radio_button_new_with_label(NULL,"语文");
    gtk_box_pack_start(GTK_BOX(box2),button1,TRUE,TRUE,0);
    gtk_widget_show(button1);

    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1));
    button2 = gtk_radio_button_new_with_label(group,"数学");
    /*默认是选择这个*/
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button2),TRUE);
    gtk_box_pack_start(GTK_BOX(box2),button2,TRUE,TRUE,0);
    gtk_widget_show(button2);
    
    button3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button2),"英语");
    gtk_box_pack_start(GTK_BOX(box2),button3,TRUE,TRUE,0);
    gtk_widget_show(button3);

    /*分割线*/
    separator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,0);
    gtk_widget_show(separator);
    
    box2 = gtk_vbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);
    gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,TRUE,0);
    gtk_widget_show(box2);
    
    /*退出按钮*/
    button = gtk_button_new_with_label("close");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Radio_Button_callback),(gpointer)"cool button");
    gtk_box_pack_start(GTK_BOX(box2),button,TRUE,TRUE,0);
    GTK_WIDGET_SET_FLAGS(button,GTK_CAN_DEFAULT);
    gtk_widget_grab_default(button);
    gtk_widget_show(button);
    gtk_widget_show(window);
    

    gtk_main();
    return 0;
}
