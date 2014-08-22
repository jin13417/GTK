/*File:panedWindowWidget.c
 *Date:2014-02-09
 *Author:sjin
 *Mail:413977243@qq.com
 */

#include <gtk/gtk.h>
#include <stdio.h>

/*创建一个消息的列表*/

GtkWidget *create_list(void)
{
    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    GtkListStore *model;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    int i;

    /*创建一个新的滚动窗口，只有需要时，滚动条才会出现*/
    scrolled_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);

    model = gtk_list_store_new(1,G_TYPE_STRING);
    tree_view = gtk_tree_view_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),tree_view);
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view),GTK_TREE_MODEL(model));
    gtk_widget_show(tree_view);

    /*在窗口添加一些消息*/
    for(i = 0;  i < 10; i++){

        gchar *msg = g_strdup_printf("Message #%d.",i);
        gtk_list_store_append(GTK_LIST_STORE(model),&iter);
        gtk_list_store_set(GTK_LIST_STORE(model),&iter,0,msg,-1);
        g_free(msg);
    }

    /*创建列的代表*/
    cell = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Message",cell,"text",0,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),GTK_TREE_VIEW_COLUMN(column));

    gtk_widget_set_size_request(scrolled_window,300,150);
    return scrolled_window;
}

/*向文本构件中添加一些文本- 这是当窗口被实例化时调用的回调函数*/

void insert_text(GtkTextBuffer *buffer)
{
    GtkTextIter iter;

    /*偏移到文本构件的开头*/
    gtk_text_buffer_get_iter_at_offset(buffer,&iter,0);

    gtk_text_buffer_insert(buffer,&iter,
                           "From:jsh@163.com\n"
                           "To:413977243@qq.com\n"
                           "Subject:I Miss You!\n"
                           "\n"
                           "These days have been think you,\nsee you on the QQ no information\n"
                           "are inexplicable pain in my heart,\ncan not let go!\n"
                           "                   love you 阿辉\n",
                           -1);
}

/*创建一个滚动的文本区域，用于显示一个信息*/
GtkWidget *create_text(void)
{
    GtkWidget *scrolled_window;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    scrolled_window = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    gtk_container_add(GTK_CONTAINER(scrolled_window),view);
    insert_text(buffer);

    gtk_widget_show_all(scrolled_window);

    return scrolled_window;
}

int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *vpaned;
    GtkWidget *list;
    GtkWidget *text;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"Frame Example!");
   
    /**/
    gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (GTK_OBJECT(window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
    
    gtk_widget_set_size_request(window,300,300);
    /*设置窗口的边框宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    /*在顶级窗口上添加一个垂直分栏窗口构件*/
    vpaned = gtk_vpaned_new();
    gtk_container_add(GTK_CONTAINER(window),vpaned);
    gtk_widget_show(vpaned);

    /*在分栏窗口的两部分各添加一些构件*/
    list = create_list();
    gtk_paned_add1(GTK_PANED(vpaned),list);
    gtk_widget_show(list);

    text = create_text();
    gtk_paned_add2(GTK_PANED(vpaned),text);
    gtk_widget_show(text);

    gtk_widget_show(window);

     /* 等待事件 (如键盘事件或鼠标事件) 的发生。*/
    gtk_main ();
    
    return 0;
}
