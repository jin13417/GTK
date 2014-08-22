/*File:Normal_Button.c
 *Date:2013-12-03
 *Author:sjin
 *Mail:413977243@qq.com
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

/*创建一个横向盒，它包含一个图像和一个标签，并非你会这个盒子*/
GtkWidget *xpm_label_box(gchar *xpm_filename,gchar *label_text)
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /*为图像和标签创建盒*/
    box = gtk_hbox_new(FALSE,0);
    gtk_container_set_border_width(GTK_CONTAINER(box),2);

    /*创建一个图像*/
    image = gtk_image_new_from_file(xpm_filename);

    /*为按钮创建一个标签*/
    label = gtk_label_new(label_text);

    /*图像和按钮组装到盒子里*/
    gtk_box_pack_start(GTK_BOX(box),image,FALSE,FALSE,3);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,3);
    
    gtk_widget_show(image);
    gtk_widget_show(label);

    return box;
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
    GtkWidget *box;

    /*初始化*/
    gtk_init(&argc,&argv);

    /*创建窗口*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*这个一般必要有delete_event信号到主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
    
    /*设置窗口宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),80);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"普通按钮练习");

    button = gtk_button_new();
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(callback),(gpointer)"cool button");

    box = xpm_label_box("info.xpm","cool button");
    gtk_widget_show(box);
    gtk_container_add(GTK_CONTAINER(button),box);

    gtk_widget_show(button);
    gtk_container_add(GTK_CONTAINER(window),button);

    gtk_widget_show(window);

    gtk_main();
    return 0;
}
