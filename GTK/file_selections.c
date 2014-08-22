
/*File:color.c
 *Date:2014-01-05
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

/*获得文件名，并将它打印到控制台上*/
void file_ok_sel(GtkWidget *w,GtkFileSelection *fs)
{
    g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
}

int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *filew;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);

    /*创建一个新的文件选择构件*/
    filew = gtk_file_selection_new("文件选择对话框");

    g_signal_connect (GTK_OBJECT(filew), "destroy",G_CALLBACK (gtk_main_quit), NULL);

    /*为ok_button按钮设置回调函数，链接到file_ok_sel 函数*/
    g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(filew)->ok_button),"clicked",G_CALLBACK(file_ok_sel),filew);

    /*为cancel_button设置回调函数*/
    g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(filew)->cancel_button),"clicked",G_CALLBACK(gtk_main_quit),filew);

    /*设置文件名，不如这个一个文件保存对话框，我们给了一个缺省文件名*/
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(filew),"1111.png");
    gtk_widget_show (filew);
    
    /* 所有的 GTK 程序必须有一个 gtk_main() 函数。程序运行停在这里
     * 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
