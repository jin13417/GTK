/*File:menu_item.c
 *Date:2013-11-23
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <stdio.h>

static void menuitem_response(gchar *string)
{
    printf("%s\n",string);
}

static int button_press(GtkWidget *widget,GdkEvent *event)
{
    if(event->type == GDK_BUTTON_PRESS){
        GdkEventButton *bevent = (GdkEventButton *)event;
        gtk_menu_popup(GTK_MENU(widget),NULL,NULL,NULL,NULL,bevent->button,bevent->time);
        /*告诉调用代码我们已经处理这个事件，*/
        return TRUE;
    }
    /*else  未处理*/
    return FALSE;
}

gint delete_event( GtkWidget *widget,GdkEvent  *event,gpointer   data )
{
    /* 如果你的 "delete_event" 信号处理函数返回 FALSE，GTK 会发出 "destroy" 信号。
     * 返回 TRUE，你不希望关闭窗口。
     * 当你想弹出“你确定要退出吗?”对话框时它很有用。*/
    g_print ("delete event occurred\n");
    /* 改 TRUE 为 FALSE 程序会关闭，关闭时调用destroy()。*/
    return TRUE;
}
/* 另一个回调函数 */
void destroy( GtkWidget *widget,gpointer   data )
{
    gtk_main_quit ();
}
int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *menu;
    GtkWidget *menu_bar;
    GtkWidget *root_menu;
    GtkWidget *menu_items;
    GtkWidget *vbox;
    GtkWidget *button;
    char buf[128];
    int i;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"My first program helloworld!");
    
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 delete_event() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (G_OBJECT (window), "delete_event",G_CALLBACK (delete_event), NULL);
    
    /* 在这里我们连接 "destroy" 事件到一个信号处理函数。  
     * 对这个窗口调用 gtk_widget_destroy() 函数或在 "delete_event" 回调函数中返回 FALSE 值
     * 都会触发这个事件。*/
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (destroy), NULL);
    
    /* 设置窗口边框的宽度。*/
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
   /*创建窗口宽度*/
    gtk_widget_set_size_request(GTK_WIDGET(window),200,100);

    /***********************
     * 初始化菜单构件
     * 记住这里永远不要用gtk_widget_show()函数来显示菜单控件
     * 这个是包含菜单项的菜单，运行程序时点击会弹出来
     **********************/
    menu = gtk_menu_new();

    /*****************××××××××××
     *
     *
     * *********************/
    for(i = 0; i < 3; i++){
        /*将名称复制到buf*/
        sprintf(buf,"undetmenu-%d",i);

        /*创建一个菜单项*/
        menu_items = gtk_menu_item_new_with_label(buf);

        /*将它添加到菜单*/
        gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_items);

        /*当菜单被选中时的回调函数*/
        g_signal_connect_swapped(G_OBJECT(menu_items),"activate",G_CALLBACK(menuitem_response),g_strdup(buf));

        /*显示构件*/
        gtk_widget_show(menu_items);
    }

    /*******************************
     *这个是根菜单，将成为现实在菜单栏上的标签
     *这里不会附上信号处理函数，因为它只是在被按下时弹出的其余的菜单
     *******************************/

    root_menu = gtk_menu_item_new_with_label("根菜单");
    gtk_widget_show(root_menu);

    /****************************
     *指定想要穿件的menu成为根菜单
     ***************************/

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);

    /*将一个菜单和一个按钮放到纵向盒子里面*/
    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show(vbox);

    /********************************
     *创建一个菜单栏，并添加到主窗口
     * *****************************/
    menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox),menu_bar,FALSE,FALSE,2);
    gtk_widget_show(menu_bar);

    button = gtk_button_new_with_label("点击");
    g_signal_connect_swapped(G_OBJECT(button),"event",G_CALLBACK(button_press),menu);
    gtk_box_pack_end(GTK_BOX(vbox),button,TRUE,TRUE,2);
    gtk_widget_show(button);

    /**************************
     *最后把菜单项添加到菜单栏上
     * ***************************/
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu);

    gtk_widget_show(window);
    gtk_main ();
    return 0;
}

