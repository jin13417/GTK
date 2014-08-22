/*File:tooltip.c
 *Date:2013-12-15
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
GtkTooltips *tooltips;
int ch = 0;

void callback(GtkWidget *widget,gpointer data)
{
	//禁用已经激活的工具提示
	if(ch){
	    gtk_tooltips_disable(tooltips);
		printf("0000\n");
		ch = 0;
	}else{
        ch = 1;
		printf("1111\n");
		gtk_tooltips_enable(tooltips);
	}

}

int main(int argc, char*argv[])
{
	GtkWidget *window;
	GtkWidget *button;

	//初始化GTK
	gtk_init(&argc,&argv);
	//创建最上层主窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//连接信号"delete_event",使得窗口关闭时发生
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	//设置窗口标题	
    gtk_window_set_title(GTK_WINDOW(window),"工具提示对象");
	//设定窗口的默认宽高
	//gtk_window_set_default_size(GTK_WINDOW(window),200,300);
	//设定窗口的位置,让窗口总在最前端
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//设定容器边框的宽度
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	//创建按钮
	button = gtk_button_new_with_label("关闭工具提示");
	gtk_container_add(GTK_CONTAINER(window),button);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(callback),NULL);
	gtk_widget_show(button);

	//创建工具提示
	tooltips = gtk_tooltips_new();
	gtk_tooltips_set_tip(tooltips,button,"这是一个工具提示按钮",NULL);
	gtk_tooltips_disable(tooltips);

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
