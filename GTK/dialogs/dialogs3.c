/*File:dialogs3.c
 *Date:2013-12-16
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>


int main(int argc, char*argv[])
{
    GtkWidget *dialog;
    GtkWidget *table;
    GtkWidget *user,*real,*home,*host;
    GtkWidget *lbl1,*lbl2,*lbl3,*lbl4;
    gint result;

	//初始化GTK
	gtk_init(&argc,&argv);

    /*GtkWidget * gtk_dialog_new_with_buttons(
     *           const gchar *title,对话框标题
     *           GtkWindow *parent,对话框父窗口
     *           GtkDialogFlags flags,
     *           const gchar *first_button_text,动作区域按钮列表
     *           ...);
     *           falgs:GTK_DIALOG_MODAL:对话框始终保持在父窗口的上部，直到关闭，防止父窗口交互
     *                 GTK_DIALOG_DESTROY_WITH_PARENT:父窗口销毁，对话框也销毁
     *                 GTK_DIALOG_NO_SEPARATOR:不显示分割线
     *
     * */
    dialog = gtk_dialog_new_with_buttons("用户信息编辑窗口",NULL,
                                         GTK_DIALOG_MODAL,
                                         GTK_STOCK_OK,GTK_RESPONSE_OK,
                                         GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                         NULL);
    //设置缺省按钮
    gtk_dialog_set_default_response(GTK_DIALOG(dialog),GTK_RESPONSE_OK);
    
    //创建4个条目，告诉用户输入的数据
    lbl1 = gtk_label_new("User Name");
    lbl2 = gtk_label_new("Real Name");
    lbl3 = gtk_label_new("Home Dir");
    lbl4 = gtk_label_new("Host Name");
    user = gtk_entry_new();
    real = gtk_entry_new();
    home = gtk_entry_new();
    host = gtk_entry_new();

    //设置条目的缺省值
    gtk_entry_set_text(GTK_ENTRY(user),g_get_user_name());
    gtk_entry_set_text(GTK_ENTRY(real),g_get_real_name());
    gtk_entry_set_text(GTK_ENTRY(home),g_get_home_dir());
    gtk_entry_set_text(GTK_ENTRY(host),g_get_host_name());

    //表组装
    table = gtk_table_new(4,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),lbl1,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),lbl2,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),lbl3,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),lbl4,0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),user,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),real,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),home,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),host,1,2,3,4);

    gtk_table_set_row_spacings(GTK_TABLE(table),5);
    gtk_table_set_col_spacings(GTK_TABLE(table),5);
    gtk_container_set_border_width(GTK_CONTAINER(table),5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),table);
    gtk_widget_show_all(dialog);

    //运行和输出对话框
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    switch(result){
        case GTK_RESPONSE_NONE:
            /*-1
             * 对话框被窗口管理器销毁或通过gtk_widget_destroy()有其他程序销毁。
             * 如果构件没有设置一个相应标识，会返回它。
             */
            break;
        case GTK_RESPONSE_REJECT:
            /* -2
             * 这个标识没有和对话框内置的任何按钮相关联，可以任意使用它
             * */
            break;
        case GTK_RESPONSE_ACCEPT:
            /* -3
             * 这个标识没有和对话框内置的任何按钮相关联，可以任意使用它
             * */
            break;
        case GTK_RESPONSE_DELETE_EVENT:
            /* -4
             * 每个对话框都会自动连接到delete-event信号，当gtk_dialog_run()
             * 运行是，这个标识会被返回，而且delete-event会被终止、不会像
             * 往常那样销毁窗口
             * */
            break;
            
        case GTK_RESPONSE_OK:
            /* -5
             * GTK_STOCK_OK 被点击
             */
            g_print("User Name:\t%s\n",gtk_entry_get_text(GTK_ENTRY(user)));
            g_print("Real Name:\t%s\n",gtk_entry_get_text(GTK_ENTRY(real)));
            g_print("Home Dir:\t%s\n",gtk_entry_get_text(GTK_ENTRY(home)));
            g_print("Host Name:\t%s\n",gtk_entry_get_text(GTK_ENTRY(host)));

            break;
        case GTK_RESPONSE_CANCEL:
            /*-6
             * GTK_STOCK_CANCEL被点击
             * */
            g_print("cancel is press!\n");

            break;
        case GTK_RESPONSE_CLOSE:
            /* -7
             *GTK_STOCK_CLOSE被点击
             */
            break;
        case GTK_RESPONSE_YES:
            /* -8
             *GTK_STOCK_YES被点击
             */
            break;
        case GTK_RESPONSE_NO:
            /* -9
             *GTK_STOCK_NO被点击
             */
            break;
        case GTK_RESPONSE_APPLY:
            /* -10
             *GTK_STOCK_APPLY被点击
             */
            break;
        case GTK_RESPONSE_HELP:
            /* -11
             *GTK_STOCK_HELP被点击
             */
            break;
        default:
            g_print("something wrong!\n");

            break;
    }

    gtk_widget_destroy(dialog);
	//gtk_main();
	return 0;
}
