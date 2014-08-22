
/*File:dialogs2.c
 *Date:2013-12-16
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
GtkTooltips *tooltips;

void button_click(GtkWidget *widget,GtkWindow *parent)
{
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *image;
    GtkWidget *hbox;

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
    dialog = gtk_dialog_new_with_buttons("我的第一个对话框",parent,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
    /*设置分割线是否隐藏：FALSE：隐藏。*/
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog),FALSE);
    label = gtk_label_new("the button was clicked!");
    image = gtk_image_new_from_stock(GTK_STOCK_DIALOG_INFO,GTK_ICON_SIZE_DIALOG);
    
    hbox = gtk_hbox_new(FALSE,5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox),10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox),image);
    gtk_box_pack_start_defaults(GTK_BOX(hbox),label);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox);
    gtk_widget_show_all(dialog);

    /*显示对话框*/
    //gtk_dialog_run(GTK_DIALOG(dialog));
    //gtk_widget_destroy(dialog);
    g_signal_connect(G_OBJECT(dialog),"response",G_CALLBACK(gtk_widget_destroy),NULL);


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
    gtk_window_set_title(GTK_WINDOW(window),"对话框练习");
	//设定窗口的默认宽高
	//gtk_window_set_default_size(GTK_WINDOW(window),200,300);
	//设定窗口的位置,让窗口总在最前端
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//设定容器边框的宽度
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	//创建按钮
	button = gtk_button_new_with_mnemonic("clicked me");
	gtk_container_add(GTK_CONTAINER(window),button);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(button_click),(gpointer)window);
	gtk_widget_show(button);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
