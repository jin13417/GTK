
/*******************************
 *使用套件生成菜单方式
 *gtk_item_factory
 **********************/

/*File:menu_item2.c
 *Date:2014-03-23
 *Author:sjin
 *Mail:413977243@qq.com
 */


#include <gtk/gtk.h>
#include <stdio.h>

/*必要的回调函数*/
static void print_hello(GtkWidget *w,gpointer data)
{
    g_message("Hello,World!\n");
}

/****************************************
 * 这是用来生成新惨淡的GtkItemFactoryEntry结构
 * 第一项 菜单路径 下划线后字母指出惨淡打开的快捷键
 * 第二项：这个条目的快捷键
 * 第三项：回调函数
 * 第四项，回调动作
 * 第五项：项类型用
 *         NULL   -> "Item"
 *         ""        "Item"
 *         "<Title>"  标题
 *         "<Item>"   创建一个简单的项
 *         "<CheckItem>" 创建一个检查项
 *         "<ToggleItem>" 创建一个开关项
 *         "<RadioItem>" 创建一个选择项
 *         <path>     选择项链接到的路径
 *         "<Separator>" 分割线
 *         "Branch"    创建一个包含子项的项
 *         "LastBranch" 创建一个右对齐的分支
 *************************************/

static GtkItemFactoryEntry menu_items[] = {
    {"/_File", NULL, NULL,0,"<Branch>"},
    {"/File/_New", "<control>N", print_hello,0,NULL},
    {"/File/_Open", "<control>O", print_hello,0,NULL},
    {"/File/_Save", "<control>S" ,print_hello,0,NULL},
    {"/File/Save _As", NULL,NULL,0,NULL},
    {"/File/sepl", NULL,NULL,0,"<Separator>"},
    {"/File/Quit", "<control>Q", gtk_main_quit,0,NULL},
    {"/_Options", NULL,NULL,0,"<Branch>"},
    {"/Options/Test", NULL,NULL,0,NULL},
    {"/_Help", NULL,NULL,0,"<LastBranch>"},
    {"/Help/About", NULL,NULL,0,NULL},
};


void get_main_menu(GtkWidget *window,GtkWidget **menu_bar)
{
    GtkItemFactory *item_factory;
    GtkAccelGroup *accel_group;
    gint nmenu_items = sizeof(menu_items)/sizeof(menu_items[0]);

    accel_group = gtk_accel_group_new();

    /****************************
     *这个函数初始化套件
     *参数1：菜单类型-
     *参数2：菜单路径 
     *参数3：指向一个gtk_accel_group 的指针
     * *****************************/

    item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<main>",accel_group);
    
    /*生成菜单项，把数组里想的数量，数组自身，和菜单项的任意
     * 回调函数以此传递给套件*/
    gtk_item_factory_create_items(item_factory,nmenu_items,menu_items,NULL);

    /*把新的加速组绑定到窗口*/
    gtk_window_add_accel_group(GTK_WINDOW(window),accel_group);

    if(menu_bar){
        /*返回套件已经创建的菜单栏*/
        *menu_bar = gtk_item_factory_get_widget(item_factory,"<main>");
    }

}

gint delete_event( GtkWidget *widget,GdkEvent  *event,gpointer   data )
{
    /* 如果你的 "delete_event" 信号处理函数返回 FALSE，GTK 会发出 "destroy" 信号。
     * 返回 TRUE，你不希望关闭窗口。
     * 当你想弹出“你确定要退出吗?”对话框时它很有用。*/
    g_print ("delete event occurred\n");
    /* 改 TRUE 为 FALSE 程序会关闭，关闭时调用destroy()。*/
    return TRUE;
}
/* 另一个回调函数 */
void destroy( GtkWidget *widget,gpointer   data )
{
    gtk_main_quit ();
}
int main( int   argc, char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *menu_bar;
    GtkWidget *vbox;
    
    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
    gtk_init (&argc, &argv);
        /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"My first program helloworld!");
    
    /* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
     * 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 delete_event() 函数。
     * 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
    g_signal_connect (G_OBJECT (window), "delete_event",G_CALLBACK (delete_event), NULL);
    
    /* 在这里我们连接 "destroy" 事件到一个信号处理函数。  
     * 对这个窗口调用 gtk_widget_destroy() 函数或在 "delete_event" 回调函数中返回 FALSE 值
     * 都会触发这个事件。*/
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (destroy), NULL);
    
    /* 设置窗口边框的宽度。*/
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
   /*创建窗口宽度*/
    gtk_widget_set_size_request(GTK_WIDGET(window),200,100);


    vbox = gtk_vbox_new(FALSE,1);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show(vbox);

    get_main_menu(window,&menu_bar);
    gtk_box_pack_start(GTK_BOX(vbox),menu_bar,FALSE,TRUE,0);
    gtk_widget_show(menu_bar);


    gtk_widget_show(window);
    gtk_main ();
    return 0;
}

