/*File:tree.c 
 *Auth:sjin
 *Date:2014-03-23
 *Mail:413977243@qq.com
 */
#include <gtk/gtk.h>

enum{
    ID_COLUMN,
    TOGGLE_COLUMN,
    TEXT_COLUMN,
    N_COLUMN
};

typedef struct _listitem ListItem;

struct _listitem{
    gint id;
    gboolean toggle;
    const gchar *text;
};

ListItem t[5] = {
    {1,TRUE,"小明"},
    {2,FALSE,"大宝"},
    {3,TRUE,"测试用名称"},
    {4,FALSE,"显示的文本"},
    {5,TRUE,"是可编辑的"}
};

GtkListStore * create_list_model(void)
{
    GtkListStore *list_store;
    GtkTreeIter iter;
    gint i;
   
    /*创建一个存储，行数和对应的数据类型列表*/
    list_store = gtk_list_store_new(N_COLUMN,G_TYPE_INT,G_TYPE_BOOLEAN,G_TYPE_STRING);
    for(i = 0;i < 5;i++){
        /*向LIST_trore添加一个新行
         * iter将指向这个新行，这个函数调用后事空的
         * 需要gtk_list_store_set()函数来填写数值
         * */
        gtk_list_store_append(list_store,&iter);
        gtk_list_store_set(list_store,&iter,ID_COLUMN,t[i].id,
                           TOGGLE_COLUMN,t[i].toggle,
                           TEXT_COLUMN,t[i].text,
                           -1);
    }

    return list_store;
}

GtkWidget* create_list(GtkListStore* list_store)
{
    GtkWidget* view;
    GtkTreeModel* model;
    GtkCellRenderer* renderer;
    GtkTreeViewColumn* column;

    model = GTK_TREE_MODEL(list_store);
    /*创建一个模型初始化model的控件*/
    view  = gtk_tree_view_new_with_model(model);
    
    /*创建一个文本单元绘制器*/
    renderer = gtk_cell_renderer_text_new();
    /*创建一个视图列表*/
    column = gtk_tree_view_column_new_with_attributes("数字",renderer,"text",ID_COLUMN,NULL);
    /*附加一列列表*/
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);

    /*创建一个开关单元绘制器*/
    renderer = gtk_cell_renderer_toggle_new();
    /*设置控件属性*/
    g_object_set(G_OBJECT(renderer),"activatable",TRUE,NULL);
    /*设置开关单元绘制器为：当为TURE时为单元按钮，为FAULE时为多选按钮*/
    gtk_cell_renderer_toggle_set_radio(GTK_CELL_RENDERER_TOGGLE(renderer),TRUE);
    /**/
    column = gtk_tree_view_column_new_with_attributes("按钮",renderer,"active",TOGGLE_COLUMN,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);
    
    renderer = gtk_cell_renderer_text_new();
    g_object_set(G_OBJECT(renderer),"editable",TRUE,NULL);
    column = gtk_tree_view_column_new_with_attributes("文本",renderer,"text",TEXT_COLUMN,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);
    return view;
}

void show_list(void)
{
    GtkWidget* window;
    GtkWidget* frame;
    GtkWidget* view;
    GtkListStore* model;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),window);
    gtk_window_set_title(GTK_WINDOW(window),"TREEVIEW --使用 LISTSTORE");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    
    frame = gtk_frame_new("可编辑的列表");
    gtk_frame_set_label_align(GTK_FRAME(frame),1.0,0);
    gtk_container_add(GTK_CONTAINER(window),frame);
    
    /*创建一个存储列表*/
    model = create_list_model();
    /*创建单元格列表*/
    view = create_list(model);
    
    gtk_container_add(GTK_CONTAINER(frame),view);
    
    gtk_widget_show_all(window);
}

enum {
    XCLASS_COLUMN,
    LEADER_COLUMN,
    STUDENTS_COLUMN,
    GIRLS_COLUMN
};
typedef struct _treeitem TreeItem;
struct _treeitem{
    const char* xclass;
    const char* leader;
    gint students;
    gint girls;
};

TreeItem ti[3] = {
    {"一年级一班","李晓",40,20},
    {"一年级二班","张红",44,18},
    {"一年级三班","刘丽",42,20}
};
TreeItem tj[3] = {
    {"二年级一班","王可",34,16},
    {"二年级二班","赵倩",34,18},
    {"二年级三班","犹可",38,20}
};

GtkTreeStore* create_tree_model(void)
{
    GtkTreeStore* treestore;
    GtkTreeIter iter,parent;
    gint i;

    /*创建树型存储结构，每行都有一种存储类型*/
    treestore = gtk_tree_store_new(4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT);
    /*向树型存储结构添加新行
     *iter 指向新行的空间
     * */
    gtk_tree_store_append(treestore,&iter,NULL);
    gtk_tree_store_set(treestore,&iter,0,"一年级",-1);

    gtk_tree_store_append(treestore,&iter,NULL);
    gtk_tree_store_set(treestore,&iter,0,"二年级",-1);

    /*gboolean gtk_tree_model_get_iter_from_string(GtkTreeModel *treestore,
     *                                              GtkTreeIter *iter,
     *                                              const gchar *path_string);
     *  参数：treestore ：存储树形列表
     *        iter :    指向存储结构
     *        path_string : 路径
     *  返回值：TRUE : iter 不为空
     *          FAule：     为空
     *
     */

    if(gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(treestore),&parent,"0")){
        for(i = 0; i < 3; i++){
            gtk_tree_store_append(treestore,&iter,&parent);
            gtk_tree_store_set(treestore,&iter,
                               XCLASS_COLUMN,ti[i].xclass,
                               LEADER_COLUMN,ti[i].leader,
                               STUDENTS_COLUMN,ti[i].students,
                               GIRLS_COLUMN,ti[i].girls,
                               -1);
        }
    }

    if(gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(treestore),&parent,"1")){
        for(i = 0; i < 3; i++)
        {
            gtk_tree_store_append(treestore,&iter,&parent);
            gtk_tree_store_set(treestore,&iter,
                               XCLASS_COLUMN,tj[i].xclass,
                               LEADER_COLUMN,tj[i].leader,
                               STUDENTS_COLUMN,tj[i].students,
                               GIRLS_COLUMN,tj[i].girls,
                               -1);
        }
    }

    return treestore;
}	

GtkWidget* create_tree(GtkTreeStore* treestore)
{
    GtkWidget* view;
    GtkCellRenderer* renderer;
    GtkTreeViewColumn* column;
    
    /*创建树型显示模型*/
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treestore));

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("班级名",renderer,"text",XCLASS_COLUMN,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("班主任",renderer,"text",LEADER_COLUMN,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("学生总数",renderer,"text",STUDENTS_COLUMN,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("女生总数",renderer,"text",GIRLS_COLUMN,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);		
    return view;
}

void show_tree(void)
{
    GtkWidget* window;
    GtkWidget* frame;
    GtkWidget* view;
    GtkTreeStore* model;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_widget_destroy),window);
    gtk_window_set_title(GTK_WINDOW(window),"TREEVIEW----使用TreeStore");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    
    frame = gtk_frame_new("树型列表");
    gtk_container_add(GTK_CONTAINER(window),frame);
    
    model = create_tree_model();
    
    view = create_tree(model);
    
    gtk_container_add(GTK_CONTAINER(frame),view);
    
    gtk_widget_show_all(window);
}

int main(int argc,char* argv[])
{
    GtkWidget* window;
    GtkWidget* vbox;
    GtkWidget* button;

    /*初始化*/
    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"TREE_VIEW控件");
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    
    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    button = gtk_button_new_with_label("创建列表显示");
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(show_list),NULL);
    
    button = gtk_button_new_with_label("创建树型显示");
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(show_tree),NULL);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return FALSE;
}
