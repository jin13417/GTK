/*File: message.c
 *Date:2013-12-21
 *Author:sjin
 *Mail:43977243@qq.com
 */

#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget* button,gpointer data)
{
    GtkWidget* dialog;
    GtkMessageType type;
    gchar* message;
    switch((int)data){
    case 1:
        message = "这是个信息提示对话框.";
        type = GTK_MESSAGE_INFO;
        break;
    case 2:
        message = "这是个错误提示对话框";
        type = GTK_MESSAGE_ERROR;
        break;
    case 3:
        message = "这是个问题提示对话框";
        type = GTK_MESSAGE_QUESTION;
        break;
    case 4:
        message = "这是个警告提示对话框";
        type = GTK_MESSAGE_WARNING;
        break;
    default:
        break;
    }
    /*GtkWidget * gtk_message_dialog_new(GtkWindow *parent,
     *                 GtkDialogFlags flags,
     *                 GtkMessageType type,
     *                 GtkButtonsType buttons,
     *                 const gchar * message_format,
     *                 ...);
     *   type :枚举的五个可能值：
     *        GTK_MESSAGE_INFO：显示用户的一般性消息
     *        GTK_MESSAGE_WARNING:一个警告信息，表示发生了非致命的错误
     *        GTK_MESSAGE_QUESTION:询问用户一个问题，用户必须做出选择。
     *        GTK_MESSAGE_ERROR:警告信息，标识发生了一个致命的错误
     *        GTK_MESSAGE_OTHER:一般类型的消息
     *  buttons:显示什么类型的按钮
     *        GTK_BUTTONS_NONE:不添加任何按钮。
     *        GTK_BUTTONS_OK:添加GTK_STOCK_OK按钮
     *        GTK_BUTTONS_CLOSE:添加GTK_STOCK_CLOSE按钮
     *        GTK_BUTTONS_CANCEL:添加GTK_STOCK_CANCEL按钮
     *        GTK_BUTTONS_YES_NO:添加GTK_STOCK_YES和GTK_STOCK_NO
     *        GTK_BUTTONS_OK_CANCEL: ...
     *   最后一个参数是显示对话框中的内容
     *
     *   void gtk_message_dialog_set_format_secondary_text(GtkMessageDialog*dialog,
     *                          const gchar *message_format,
     *                          ...);
     *   为消息对话框添加第二段文本，他会导致第一个文本被设置成粗体。这个功能
     *   非常有用，它允许您在第一段文字中写一个简短的概要，在第二段文本中详细
     *   描述。通过gtk_message_set_format_secondary_markup()来设置文本格式
     * */

    dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc,char* argv[])
{
    GtkWidget* window;
    GtkWidget* frame;
    GtkWidget* box;
    GtkWidget* button1;
    GtkWidget* button2;
    GtkWidget* button3;
    GtkWidget* button4;

    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"创建消息框");
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window),20);
    frame = gtk_frame_new("四种消息对话框");
    gtk_container_add(GTK_CONTAINER(window),frame);
    box = gtk_hbox_new(TRUE,0);
    gtk_container_add(GTK_CONTAINER(frame),box);
    gtk_container_set_border_width(GTK_CONTAINER(box),20);

    button1 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_INFO);
    gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(on_button_clicked),(gpointer)1);

    /*GtkWidget * gtk_button_new_from_stock(const gchar *stock_id);
     * GTK内部保存的条目：图片和文字。stock_id:对应的ID
     */
    button2 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_ERROR);
    gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(on_button_clicked),(gpointer)2);

    button3 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_QUESTION);
    gtk_box_pack_start(GTK_BOX(box),button3,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button3),"clicked",G_CALLBACK(on_button_clicked),(gpointer)3);

    button4 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_WARNING);
    gtk_box_pack_start(GTK_BOX(box),button4,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button4),"clicked",G_CALLBACK(on_button_clicked),(gpointer)4);

    gtk_widget_show_all(window);
    gtk_main();
    return FALSE;
}

