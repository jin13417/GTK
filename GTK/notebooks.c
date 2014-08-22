/*File:notebook.c
 *Date:2014-0309
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <stdio.h>

/*这个函数旋转页标签的位置*/
void rotate_book(GtkButton *button,GtkNotebook *notebook)
{
    gtk_notebook_set_tab_pos(notebook,(notebook->tab_pos + 1) % 4);
}

/*隐藏或显示页标签和边框*/
void tabsborder_book(GtkButton *button,GtkNotebook *notebook)
{
    gint tval = FALSE;
    gint bval = FALSE;
    if(notebook->show_tabs == 0){
        tval = TRUE;
    }

    if(notebook->show_border == 0){
        bval = TRUE;
    }

    /*显示或者隐藏页标签*/
    gtk_notebook_set_show_tabs(notebook,tval);
    /*显示或者隐藏边框*/
    gtk_notebook_set_show_border(notebook,bval);
}

/*从笔记本构件上删除页面*/
void remove_book(GtkButton *button,GtkNotebook *notebook)
{
    gint page;
    page = gtk_notebook_get_current_page(notebook);
    gtk_notebook_remove_page(notebook,page);
    /*********************
     * 必须刷新构件-----这会迫使构件重绘自身*/
    gtk_widget_draw(GTK_WIDGET(notebook),NULL);
}

void delete(GtkWidget *widget,GtkWidget *event,gpointer data)
{
    gtk_main_quit();
}


int main(int argc, char*argv[])
{
	GtkWidget *window;
    GtkWidget *button;
	GtkWidget *table;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *checkbutton;
    int i;
    char bufferf[32];
    char bufferl[32];

	//初始化GTK
	gtk_init(&argc,&argv);
	//创建最上层主窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//连接信号"delete_event",使得窗口关闭时发生
	g_signal_connect(G_OBJECT(window),"delete_event",GTK_SIGNAL_FUNC(delete),NULL);
	//设置窗口标题	
	gtk_window_set_title(GTK_WINDOW(window),"notebook 练习");
	//设定窗口的默认宽高
	//gtk_window_set_default_size(GTK_WINDOW(window),200,300);
	//设定窗口的位置,让窗口总在最前端
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//设定容器边框的宽度
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	/*表组装，创建表*/
	table = gtk_table_new(3,6,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);

    /*创建一个笔记本构件，将标签页放在顶部*/
    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);
    gtk_table_attach_defaults(GTK_TABLE(table),notebook,0,6,0,1);
    gtk_widget_show(notebook);

    /*向笔记本构件中插入标签页*/
    for(i = 0; i < 5; i++){
        sprintf(bufferf,"笔记本构件框架 %d",i + 1);
        sprintf(bufferl,"标签页 %d",i + 1);

        frame = gtk_frame_new(bufferf);
        gtk_container_set_border_width(GTK_CONTAINER(frame),10);
        gtk_widget_set_usize(frame,100,75);
        gtk_widget_show(frame);

        label = gtk_label_new(bufferf);
        gtk_container_add(GTK_CONTAINER(frame),label);
        gtk_widget_show(label);

        label = gtk_label_new(bufferl);
        gtk_notebook_prepend_page(GTK_NOTEBOOK(notebook),frame,label);

    }

    /*设置起始页为第四页*/
    gtk_notebook_set_page(GTK_NOTEBOOK(notebook),3);

    /*创建一排按钮*/

    /*关闭*/
    button = gtk_button_new_with_label("关闭");
    gtk_signal_connect_object(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(delete),NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button,0,1,1,2);
    gtk_widget_show(button);

    /*下一页*/
    button = gtk_button_new_with_label("下一页");
    gtk_signal_connect_object(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_notebook_next_page),GTK_NOTEBOOK(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table),button,1,2,1,2);
    gtk_widget_show(button);

    /*上一页*/
    button = gtk_button_new_with_label("上一页");
    gtk_signal_connect_object(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_notebook_prev_page),GTK_NOTEBOOK(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table),button,2,3,1,2);
    gtk_widget_show(button);

    /*标签页位置*/
    button = gtk_button_new_with_label("标签页位置");
    gtk_signal_connect(GTK_OBJECT(button),"clicked",(GtkSignalFunc)rotate_book,GTK_NOTEBOOK(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table),button,3,4,1,2);
    gtk_widget_show(button);

    /*隐藏页标签和边框*/
    button = gtk_button_new_with_label("页标签和边框ON、OFF");
    gtk_signal_connect(GTK_OBJECT(button),"clicked",(GtkSignalFunc)tabsborder_book,GTK_NOTEBOOK(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table),button,4,5,1,2);
    gtk_widget_show(button);

    /*删除*/
    button = gtk_button_new_with_label("删除");
    gtk_signal_connect(GTK_OBJECT(button),"clicked",(GtkSignalFunc)remove_book,GTK_NOTEBOOK(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table),button,5,6,1,2);
    gtk_widget_show(button);

    gtk_widget_show(table);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
