/*File:scrlled_windows.c
 *Date:2014-02-10
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <stdio.h>

int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *scrlled_window;
    GtkWidget *table;
    GtkWidget *button;
    GtkWidget *box;
    char buffer[32];
    int i,j;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"Scrolled Windows Example!");
   
    /**/
    gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (GTK_OBJECT(window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
    
    gtk_widget_set_size_request(window,300,300);
    /*设置窗口的边框宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),5);

    /*创建一个滚动窗口*/
    scrlled_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_container_set_border_width(GTK_CONTAINER(scrlled_window),10);

    /*滚动条的出现方式：
     *    GTK_POLICY_AUTOMATIC：自动决定是否需要出现滚动条
     *    GTK_POLICY_ALWAYS：一直显示滚动条
     * */
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrlled_window),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);

    /*创建一个纵向盒子来组装控件*/
    
    box = gtk_vbox_new(TRUE,10);
    /*对话框矿口内部包含一个VBOX控件*/
    gtk_box_pack_start(GTK_BOX(box),scrlled_window,TRUE,TRUE,0);
    gtk_widget_show(scrlled_window);
    gtk_container_add(GTK_CONTAINER(window),box);
    /*创建一个包含10X10的表格*/
    table = gtk_table_new(10,10,FALSE);

    /*设置X Y 方向的行间间距为10像素*/
    gtk_table_set_row_spacings(GTK_TABLE(table),10);
    gtk_table_set_col_spacings(GTK_TABLE(table),10);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrlled_window),table);
    gtk_widget_show(table);

    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            sprintf(buffer,"button(%d,%d)\n",i,j);
            button = gtk_toggle_button_new_with_label(buffer);
            gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j,j+1);
            gtk_widget_show(button);
        }
    }

    /*在对话框的底部添加一个“close”按钮*/
    button = gtk_button_new_with_label("close");
    g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_main_quit),window);

    /*此按钮被缺省*/
    GTK_WIDGET_SET_FLAGS(button,GTK_CAN_DEFAULT);
    gtk_box_pack_start(GTK_BOX(box),button,TRUE,TRUE,0);

    gtk_widget_show(box);

    /*按钮固定为缺省按钮，只要按回车键就相当于点击这个按钮*/
    gtk_widget_grab_default(button);
    gtk_widget_show(button);

    gtk_widget_show(window);

     /* 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
