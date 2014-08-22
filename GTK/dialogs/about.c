/*File:about.c
 *Date:2013-12-22
 *Author:sjin
 *Mail:413977243@qq.com
 * */
#include <gtk/gtk.h>

static GtkWidget* credits_window;
GtkWidget* create_credits()
{
    GtkWidget* window;
    GtkWidget* vbox;
    GtkWidget* notebook;
    GtkWidget* page;
    GtkWidget* label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"开发人员");
    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    //这里使用了notebook
    notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox),notebook,FALSE,FALSE,5);

    page = gtk_vbox_new(FALSE,0);
    label = gtk_label_new("Kyle Loudon");
    gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5);
    label = gtk_label_new("sjin");
    gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5);
    label = gtk_label_new("作者");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,label);

    page = gtk_vbox_new(FALSE,0);
    label = gtk_label_new("集合");
    gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5);
    label = gtk_label_new("文档");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,label);

    page = gtk_vbox_new(FALSE,0);
    label = gtk_label_new("肖翔\n陈珂");
    gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5);
    label = gtk_label_new("翻译");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,label);
    gtk_widget_show_all(window);
    return window;
}


void show_credits()
{
    credits_window = create_credits();
    gtk_widget_show(credits_window);
}

int main(int argc,char* argv[])
{
    GtkWidget* bbox;
    GtkWidget* vbox;
    GtkWidget* label;
    GtkWidget* window;
    GtkWidget* sep;
    GtkWidget* image;
    GtkWidget* button;
    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"关于对话框");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    image = gtk_image_new_from_file("logo.jpg");
    gtk_box_pack_start(GTK_BOX(vbox),image,FALSE,FALSE,5);
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label),"<span><big>算法精解-C语言描述</big></span>");
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5);
    label = gtk_label_new("版权所有:机械工业出版社\n 作者:Kyle Loudon");
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5);
    bbox = gtk_hbutton_box_new();
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_EDGE);
    gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5);
    button = gtk_button_new_with_label("credits");
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,25);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(show_credits),NULL);
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,35);
    gtk_widget_show_all(window);
    gtk_main();
    return FALSE;
}
