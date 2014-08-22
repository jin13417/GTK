#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{    
    GtkWidget* window = NULL;
    GtkWidget* vbox = NULL;
    GtkTextBuffer* buffer = NULL;
    GtkWidget* text_view = NULL;
    GtkTextTag* not_editable_tag = NULL;
    GtkTextIter start = {0};
    GtkTextIter end = {0};

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(window);
    gtk_window_set_title(GTK_WINDOW(window), "text view");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(vbox);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    buffer = gtk_text_buffer_new(NULL);
    text_view = gtk_text_view_new_with_buffer(buffer);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, FALSE, FALSE, 0);
    char ip[] = "192.168. 1";
    gchar* str = g_convert(ip, strlen(ip), "UFT-8", "ASCII", NULL, NULL, NULL);
    gtk_text_buffer_set_text(buffer, ip, -1); /****** 添加一些文本到buffer ***/

    /*************
     * 创建一个GtkTextTag,
     * 为tag设置一些属性
     * ***********/
    not_editable_tag = gtk_text_buffer_create_tag(buffer, NULL, "editable", FALSE, "foreground", "red", NULL);

    /******************* 将第一个'.'设置成一个tag ******************/
    gtk_text_buffer_get_iter_at_line_index(buffer, &start, 1, 3);
    gtk_text_buffer_get_iter_at_line_index(buffer, &end, 1, 4);
    gtk_text_buffer_apply_tag(buffer, not_editable_tag, &start, &end);

    /****************** 将第二个'.'设置成一个tag
     * *********************/
    gtk_text_buffer_get_iter_at_line_index(buffer, &start, 1, 7);
    gtk_text_buffer_get_iter_at_line_index(buffer, &end, 1, 8);
    gtk_text_buffer_apply_tag(buffer, not_editable_tag, &start, &end);

    gtk_widget_show(text_view);

    gtk_main();

    return 0;
}
