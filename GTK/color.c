/*File:color.c
 *Date:2014-01-05
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

GtkWidget *colorseldlg = NULL;
GtkWidget *drawingarea = NULL;
GdkColor color;

/*颜色改变处理信号*/
void color_changed_cb(GtkWidget *widget,GtkColorSelection *colorsel)
{
    GdkColor ncolor;

    gtk_color_selection_get_current_color(colorsel,&ncolor);
    gtk_widget_modify_bg(drawingarea,GTK_STATE_NORMAL,&ncolor);
}

/*绘图区事件处理函数*/
gint area_event(GtkWidget *widget,GdkEvent *event,gpointer client_data)
{
    gint handled = FALSE;
    gint response;
    GtkColorSelection *colorsel;

    /*检查是否收到鼠标按键按下*/

    if(event->type == GDK_BUTTON_PRESS){
        handled = TRUE;
        
        /*创建颜色选择对话框*/
        if(colorseldlg == NULL){
            /*创建一个孤立的颜色选择构件，并需要将其放在某个对话框*/
            colorseldlg = gtk_color_selection_dialog_new("选择背景颜色");
        }
        /*获取颜色选择构件*/
        colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(colorseldlg)->colorsel);
        gtk_color_selection_set_previous_color(colorsel,&color);
        gtk_color_selection_set_current_color(colorsel,&color);
        gtk_color_selection_set_has_palette(colorsel,TRUE);

        /*为color_changed 信号设置回调函数，将用户数据设置为颜色选择构件*/
        g_signal_connect(GTK_OBJECT(colorsel),"color_changed",G_CALLBACK(color_changed_cb),(gpointer)colorsel);

        /*显示对话框*/
        response = gtk_dialog_run(GTK_DIALOG(colorseldlg));

        if(response == GTK_RESPONSE_OK){
            /*获取当前颜色，并保存到color中*/
            gtk_color_selection_get_current_color(colorsel,&color);
        }else{
            /*设置成原来的颜色*/
            gtk_widget_modify_bg(drawingarea,GTK_STATE_NORMAL,&color);
        }

        gtk_widget_hide(colorseldlg);
    }
    /*只有返回True，才能弹出颜色选择控件*/
    return handled;
}

/*关闭、退出事件处理函数*/
gint destroy_window(GtkWidget *widget,GdkEvent *event,gpointer client_data)
{
    gtk_main_quit();
    return TRUE;
}

int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *button;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"My first program helloworld!");
   
    /**/
    gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (GTK_OBJECT(window), "delete_event",G_CALLBACK (destroy_window), (gpointer)window);
    
    /*创建绘图区，设置尺寸，捕捉鼠标按键事件*/
    drawingarea = gtk_drawing_area_new();

    color.red = 0;
    color.blue = 65535;
    color.green = 0;
    
    /*设置背景颜色*/
    gtk_widget_modify_bg(drawingarea,GTK_STATE_NORMAL,&color);

    /*设定绘图区域的大小*/
    gtk_widget_set_size_request(GTK_WIDGET(drawingarea),200,200);

    /*设置成按钮事件*/
    gtk_widget_set_events(drawingarea,GDK_BUTTON_PRESS_MASK);

    g_signal_connect(GTK_OBJECT(drawingarea),"event",GTK_SIGNAL_FUNC(area_event),(gpointer)drawingarea);

    gtk_container_add(GTK_CONTAINER(window),drawingarea);
    /* 最后一步是显示新创建的按钮和窗口 */
    gtk_widget_show (drawingarea);
    gtk_widget_show (window);
    
    /* 所有的 GTK 程序必须有一个 gtk_main() 函数。程序运行停在这里
     * 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
