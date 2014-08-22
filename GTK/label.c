
/*File:label.c
 *Date:2013-12-13
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include<gtk/gtk.h>
GtkWidget *label1;

void callBack(GtkWidget *widget,gpointer data)
{
    printf("label1 = %s\n",gtk_label_get_text(GTK_LABEL(label1)));
    gtk_label_set_text(GTK_LABEL(label1),(char*)data);
    sleep(1);
    gtk_main_quit();

}
		

int main(int argc, char*argv[])
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;	
	GtkWidget *frame1;	
	GtkWidget *frame2;	
	GtkWidget *frame3;	
	GtkWidget *frame4;	
    GtkWidget *button;
	gchar *title ;
	//初始化GTK
	gtk_init(&argc,&argv);
	//创建最上层主窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//连接信号"delete_event",使得窗口关闭时发生
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	//设置窗口标题	
	gtk_window_set_title(GTK_WINDOW(window),"多种样式的标签");
	//设定窗口的默认宽高
	//gtk_window_set_default_size(GTK_WINDOW(window),200,300);
	//设定窗口的位置,让窗口总在最前端
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//设定容器边框的宽度
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	//创建盒子
	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);

	//创建框架1
	frame1 = gtk_frame_new("标签一");
	label1 = gtk_label_new("这是第一个标签，居左边的。This is the first label.");
	gtk_container_add(GTK_CONTAINER(frame1),label1);
	/*void gtk_label_set_justify(GtkLabel *label, GtkJustification jtype);
     * jtype 值：GTK_JUSTIFY_LEFT :左对齐
     *           GTK_JUSTIFY_RIGHT:右对齐
     *           GTK_JUSTIFY_CENTER:居中对齐（默认 ）
     *           GTK_JUSTIFY_FILL:充满
     */
	gtk_label_set_justify(GTK_LABEL(label1),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(box),frame1,FALSE,FALSE,5);

	frame2 = gtk_frame_new("标签二");
	label2 = gtk_label_new("这是第二个标签，它是多行的。\n这还是第二个标签的内容，它是居右边的。");
	gtk_container_add(GTK_CONTAINER(frame2),label2);
	gtk_label_set_justify(GTK_LABEL(label2),GTK_JUSTIFY_RIGHT);
    //设置下划线
    gtk_label_set_pattern(GTK_LABEL(label2),"__ __   __  ");
	gtk_box_pack_start(GTK_BOX(box),frame2,FALSE,FALSE,5);

	frame3 = gtk_frame_new("标签三");
	label3 = gtk_label_new(NULL);
	//标记语言形式
	title = "<span foreground=\"red\"><big><i>这是第三个标签。\n它被格式化成红色了，并且字体也大了。</i></big></span>";
	gtk_container_add(GTK_CONTAINER(frame3),label3);
	gtk_label_set_markup(GTK_LABEL(label3),title);
	gtk_box_pack_start(GTK_BOX(box),frame3,FALSE,FALSE,5);

	frame4 = gtk_frame_new("标签四");
	label4 = gtk_label_new("这也是一个多行标签，它的换行方式和上一个有所不同，主要是编辑手段不一样了，请仔细查看一下源码就会明白怎么回事了。");
	gtk_label_set_justify(GTK_LABEL(label1),GTK_JUSTIFY_LEFT);
	//自动换行函数
    gtk_label_set_line_wrap(GTK_LABEL(label4),TRUE);
	gtk_container_add(GTK_CONTAINER(frame4),label4);
	gtk_box_pack_start(GTK_BOX(box),frame4,FALSE,FALSE,5);

    button = gtk_button_new_with_label("set label1");
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(callBack),"set label1 111");
    gtk_container_add(GTK_CONTAINER(window),button);
    gtk_widget_show(button);
    
    

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
