/*File: aboutdialogs.c
 *Date:2013-12-21
 *Author:sjin
 *Mail:43977243@qq.com
 */

#include <gtk/gtk.h>

int main(int argc,char* argv[])
{
    GtkWidget *dialog;
    GdkPixbuf *logo;
    GError *error = NULL;

    const gchar *authors[] ={
        "Kyle Loudon",
        "sjin",
        NULL
    };

    const gchar *documenters[]={
        "指针操作",
        "递归",
        "算法",
        "链表",
        "栈和队列",
        "集合",
        "哈希表",
        "树",
        NULL
    };

    const gchar * translators = "肖翔\n陈珂";

    //初始化环境
    gtk_init(&argc,&argv);
    //创建对话框
    dialog = gtk_about_dialog_new();
    //创建一个图标
    logo = gdk_pixbuf_new_from_file("./logo.jpg",&error);

    if(error == NULL){
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog),logo);
    } else {
        if(error->domain == GDK_PIXBUF_ERROR){
            g_print("GdkPixbuf Error : %s\n",error->message);
        } else if(error->domain == G_FILE_ERROR){
            g_print("GFileError : %s\n",error->message);
        } else {
            g_print("an error in the domain : %d has occured!\n",error->domain);
        }
    }

    //设置显示在主对话框上的数据
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog),"算法精解-C语言描述");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"1.0");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C)2007 Andrew Krause");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"我的第一本算法书籍");
    //设置作者，文档，翻译
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog),authors);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(dialog),documenters);
    gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(dialog),translators);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return FALSE;
}

