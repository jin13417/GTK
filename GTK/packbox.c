/*File:packbox.c
 *Date:2013-11-17
 *Author:sjin
 *Mail:413977243@qq.com
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

gint delete_event(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

/*生成一个填满按钮-标签的横向盒，我们将感兴趣的参数传递进这个函数
 * 我们不显示这个盒子，但显示它内部的所有东西
 */
GtkWidget * make_box(gboolean homogeneous,gint spacing,gboolean expand,gboolean fill,guint padding)
{
    GtkWidget *box;
    GtkWidget *button;
    char padstr[80];

    /*homogeneous：确定所有控件的大小
     *         TRUE：表示组装和计算最大控件的大小，然后其他控件按照最大控件的大小分配
     *         FALSE：建立不同大小的控件，以各自内容。
     * spacing:用它来确定插入组装和的构件之间的空间。
     *         0：表示空间之间不留空间
     * */
    box = gtk_hbox_new (homogeneous,spacing);

    button = gtk_button_new_with_label("gtk_box_pack");
    gtk_box_pack_start(GTK_BOX(box),button,expand,fill,padding);
    gtk_widget_show(button);


    button = gtk_button_new_with_label("box,");
    gtk_box_pack_start(GTK_BOX(box),button,expand,fill,padding);
    gtk_widget_show(button);


    button = gtk_button_new_with_label("button");
    gtk_box_pack_start(GTK_BOX(box),button,expand,fill,padding);
    gtk_widget_show(button);

    if(expand == TRUE){
        button = gtk_button_new_with_label("TRUE,");
    } else {
        button = gtk_button_new_with_label("FALSE,");
    }
    gtk_box_pack_start(GTK_BOX(box),button,expand,fill,padding);
    gtk_widget_show(button);


    button = gtk_button_new_with_label(fill?"TRUE":"FALSE");
    gtk_box_pack_start(GTK_BOX(box),button,expand,fill,padding);
    gtk_widget_show(button);

    sprintf(padstr,"%d);",padding);


    button = gtk_button_new_with_label(padstr);
    gtk_box_pack_start(GTK_BOX(box),button,expand,fill,padding);
    gtk_widget_show(button);

    return box;
}

int main(int argc,char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *separator;
    GtkWidget *label;
    GtkWidget *quitbox;
    int which;

    /*初始化*/
    gtk_init(&argc,&argv);

    if(argc != 2){
        fprintf(stderr,"usage:packbox num ,where num is 1,2,3\n");
        exit(1);
    }

    which = atoi(argv[1]);

    /*创建窗口*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*这个一般必要有delete_event信号到主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
    
    /*设置窗口宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),80);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"组装盒练习");

    /* 我们创建一个纵向盒（vbox)把横向和组装进来
     *这样我们可以将填满按钮的很想和一个个的堆叠到这个纵向盒子里
     */
     box1 = gtk_vbox_new(FALSE,0);

     /**/
     switch(which){
     case 1:
         /*创建一个标签*/
         label = gtk_label_new("gtk_hbox_new(FALSE,0);");

         /*使标签靠左排列*/
         gtk_misc_set_alignment(GTK_MISC(label),0,0);

         /*将标签组装到纵向盒中*/
         gtk_box_pack_start(GTK_BOX(box1),label,FALSE,FALSE,0);

         /*显示标签*/
         gtk_widget_show(label);

         /*调用我们生成盒的函数-homogeneous = FALSE,spacing = 0         
          * * expand = FALSE,fill = FALSE,padding = 0 */
         box2 = make_box(TRUE,0,FALSE,FALSE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);

         /*调用我们生成盒的函数-homogeneous = FALSE,spacing = 0         
          * * expand = TRUE,fill = FALSE,padding = 0 */
         box2 = make_box(FALSE,0,TRUE,FALSE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);

         
         /*调用我们生成盒的函数-homogeneous = FALSE,spacing = 0         
          * * expand = TRUE,fill = TRUE,padding = 0 */
         box2 = make_box(FALSE,0,TRUE,TRUE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);

         /*创建一个分割线,并组装到纵向盒*/
         separator = gtk_hseparator_new();
         gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,5);
         gtk_widget_show(separator);

         /*创建一个新的标签，并显示它*/
         label = gtk_label_new("gtk_hbox_new(TRUE,0);");
         gtk_misc_set_alignment(GTK_MISC(label),0,0);
         gtk_box_pack_start(GTK_BOX(box1),label,FALSE,FALSE,0);
         gtk_widget_show(label);

         
         box2 = make_box(TRUE,0,TRUE,FALSE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);


         box2 = make_box(FALSE,0,TRUE,TRUE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);


         /*创建一个分割线,并组装到纵向盒*/
         separator = gtk_hseparator_new();
         gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,5);
         gtk_widget_show(separator);

         break;
     case 2:
         /*创建一个新的标签，并显示它*/
         label = gtk_label_new("gtk_hbox_new(FALSE,10);");
         gtk_misc_set_alignment(GTK_MISC(label),0,0);
         gtk_box_pack_start(GTK_BOX(box1),label,FALSE,FALSE,0);
         gtk_widget_show(label);

         
         box2 = make_box(FALSE,10,TRUE,FALSE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);


         box2 = make_box(FALSE,10,TRUE,TRUE,0);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);


         /*创建一个分割线,并组装到纵向盒*/
         separator = gtk_hseparator_new();
         gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,5);
         gtk_widget_show(separator);

         /*创建一个新的标签，并显示它*/
         label = gtk_label_new("gtk_hbox_new(FALSE,0);");
         gtk_misc_set_alignment(GTK_MISC(label),0,0);
         gtk_box_pack_start(GTK_BOX(box1),label,FALSE,FALSE,0);
         gtk_widget_show(label);

         
         box2 = make_box(FALSE,0,TRUE,FALSE,10);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);


         box2 = make_box(FALSE,0,TRUE,TRUE,10);
         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);
         gtk_widget_show(box2);


         /*创建一个分割线,并组装到纵向盒*/
         separator = gtk_hseparator_new();
         gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,5);
         gtk_widget_show(separator);
         break;
     case 3:
         /*示范gtk_box_pack_end()右对齐构件的能力*/
         box2 = make_box(FALSE,0,FALSE,FALSE,0);

         /*创建放在末端的标签*/
         label = gtk_label_new("end");
         gtk_box_pack_end(GTK_BOX(box2),label,FALSE,FALSE,0);
         gtk_widget_show(label);

         gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);

         gtk_widget_show(box2);

         /*放在底部的分割线*/
         separator = gtk_hseparator_new();

         gtk_widget_set_size_request(separator,400,5);

         gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,5);
         gtk_widget_show(separator);
         break;
     default:
         break;
     }

     /*创建一个新的横向盒，用来推出按钮*/
     quitbox = gtk_hbox_new(FALSE,0);
     button = gtk_button_new_with_label("退出");
     g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),window);

     gtk_box_pack_start(GTK_BOX(quitbox),button,TRUE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box1),quitbox,TRUE,FALSE,0);

     gtk_container_add(GTK_CONTAINER(window),box1);

     gtk_widget_show(button);
     gtk_widget_show(quitbox);
     gtk_widget_show(box1);
     gtk_widget_show(window);

     gtk_main();

     return 0;
};






