
/*File:range_controls.c
 *Date:2013-12-08
 *Author:sjin
 *Mail:413977243@qq.com
 */
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

/*范围控件：
 *  由一般按钮派生而来，只是开关按钮只有两个状态，通过点击
 *  可以切换。
 *  开关按钮是复选按钮和单选按钮的基础，所以单选按钮和复选按钮继承了
 *  许多开关按钮的函数调用
 */

    GtkWidget *hscale,*vscale;

void cb_pos_menu_select(GtkWidget *item,GtkPositionType pos)
{
    /*设置两个比例构件的比例值的显示位置
     *void gtk_scale_set_value_pos(GtkScale * scale,:比例构件
      *                            GtkPositionType pos);：显示对象的位置
      *                            GTK_POS_TOP
      *                            GTK_POS_RIGHT
      *                            GTK_POS_BOTTOM
      *                            GTK_POS_LEFT
     * */
    printf("###%s,pos = %d \n",__func__,pos);
    gtk_scale_set_value_pos(GTK_SCALE(hscale),pos);
    gtk_scale_set_value_pos(GTK_SCALE(vscale),pos);
}

void cb_update_menu_select(GtkWidget *item,GtkUpdateType Policy)
{
    /*设置两个比例控件的更新方式
     *void gtk_range_set_update_policy(GtkRange *range,GtkUpdateType Policy);
     *range : 范围控件
     *Policy :更新方式，有以下三个
     *        GTK_UPDATE_CONTINUOUS:信号时连续引发的
     *        GTK_UPDATE_DISCONTINUOUS:只有滑块停止移动，用户释放鼠标时才引发
     *        GTK_UPDATE_DELAYED:当用户释放鼠标，或者滑块短期停止移动时引发
     *
     * */
    gtk_range_set_update_policy(GTK_RANGE(hscale),Policy);
    gtk_range_set_update_policy(GTK_RANGE(vscale),Policy);
}

void cb_digits_scale(GtkAdjustment *adj)
{
    /*设置 小数的位数
     *gtk_scale_set_digits(GtkScale *scale,gint Digits)
     *参数：scale:比例构件对象
     *     Digits:要显示小数位数，最大13
     * */
    gtk_scale_set_digits(GTK_SCALE(hscale),(gint)adj->value);
    gtk_scale_set_digits(GTK_SCALE(vscale),(gint)adj->value);
}

void cb_page_size(GtkAdjustment * get,GtkAdjustment * set)
{
    /*将实例调整对象的page_size,和page_increment size设置为“page Size”
     *比例控件指定的数值。
     */
    set->page_size = get->value;
    set->page_increment = get->value;
    /*设置调整对象的值并使它引发一个“changed"信号，以重新配置所有已连接到这个调整对象的构件
     */
    gtk_adjustment_set_value(set,CLAMP(set->value,set->lower,(set->upper-set->page_size)));


}

void cb_draw_value(GtkToggleButton * button)
{
    /*根据复选框的状态设置在比例构件上是否显示比例值
     *TRUE ：显示 FALSE：不显示
     * */
    gtk_scale_set_draw_value(GTK_SCALE(hscale),button->active);
    gtk_scale_set_draw_value(GTK_SCALE(vscale),button->active);
}


GtkWidget * make_menu_item(gchar *name,GCallback callback,gpointer data)
{
    GtkWidget *item;

    item = gtk_menu_item_new_with_label(name);
    g_signal_connect(G_OBJECT(item),"activate",callback,data);
    gtk_widget_show(item);

    return item;
}

/*设置比例控件默认方式*/
void scale_set_default_values(GtkScale * scale)
{
    gtk_range_set_update_policy(GTK_RANGE(scale),GTK_UPDATE_CONTINUOUS);
    gtk_scale_set_digits(scale,1);
    gtk_scale_set_value_pos(scale,GTK_POS_TOP);
    gtk_scale_set_draw_value(scale,TRUE);
}


/*创建示例窗口*/
static void create_range_controls()
{
    GtkWidget *window;
    GtkWidget *button;
    /*box1:纵向组装盒子
     * */
    GtkWidget *box1,*box2,*box3;
    GtkWidget *scrollbar;
    GtkWidget *separator;
    GtkWidget *opt,*menu,*item;
    GtkWidget *label;
    GtkWidget *scale;
    GtkWidget *adj1,*adj2;

    /************************标准的窗口代码********************/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*这个一般必要有delete_event信号到主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    
    /*设置窗口宽度*/
    gtk_container_set_border_width(GTK_CONTAINER(window),20);

    /*设置窗口标题*/
    gtk_window_set_title(GTK_WINDOW(window),"范围控件练习");
    /************************************************************/
    
    /*创建一个纵向组装盒子*/
    box1 = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),box1);
    gtk_widget_show(box1);

    /*创建一个横向组装盒子*/
    box2 = gtk_hbox_new(FALSE,0);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);
    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);

    /*创建一个调整对象
     * GtkObject *gtk_adjustment_new(gdouble value,调整对象的初始值，通常是最高或者最低位置
     *                              gdouble lower,调整对象能取得的最低值
     *                              gdouble upper,用于分栏构件最底部或最右边的坐标
     *                              gdouble step_increment,小步调整的值
     *                              gdouble page_increment,大步调整的值
     *                              gdouble page_size);分栏构件的可视区域
     * */
    adj1 = gtk_adjustment_new(0.0,0.0,101.0,0.1,1.0,1.0);
    
    /*创建一个垂直比例控件*/
    vscale = gtk_vscale_new(GTK_ADJUSTMENT(adj1));
    scale_set_default_values(GTK_SCALE(vscale));
    gtk_box_pack_start(GTK_BOX(box2),vscale,TRUE,TRUE,0);
    gtk_widget_show(vscale);


    /*创建一个纵向组装盒子，并加入2个水平比例控件*/
    box3 = gtk_vbox_new(FALSE,10);
    gtk_box_pack_start(GTK_BOX(box2),box3,TRUE,TRUE,0);
    gtk_widget_show(box3);

    /*创建一个水平比例控件*/
    hscale = gtk_hscale_new(GTK_ADJUSTMENT(adj1));
    /*设置控件的宽度和高度*/
    gtk_widget_set_size_request(GTK_WIDGET(hscale),200,-1);
    scale_set_default_values(GTK_SCALE(hscale));
    gtk_box_pack_start(GTK_BOX(box3),hscale,TRUE,TRUE,0);
    gtk_widget_show(hscale);

    /*创建一个滑动条*/
    scrollbar = gtk_hscrollbar_new(GTK_ADJUSTMENT(adj1));
    /*注意：
     *    这导致当滚动条移动时，比例构件总是连续更新
     * */
    gtk_range_set_update_policy(GTK_RANGE(scrollbar),GTK_UPDATE_CONTINUOUS);
    gtk_box_pack_start(GTK_BOX(box3),scrollbar,TRUE,TRUE,0);
    gtk_widget_show(scrollbar);

    box2 = gtk_hbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);
    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);

    /*用一个复选框控制是否显示比较构件的当前的数值*/
    button = gtk_check_button_new_with_label("Display value on scale widgets");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),TRUE);
    g_signal_connect(G_OBJECT(button),"toggled",G_CALLBACK(cb_draw_value),NULL);
    gtk_box_pack_start(GTK_BOX(box2),button,TRUE,TRUE,0);
    gtk_widget_show(button);

    box2 = gtk_hbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);

    /*用一个选项菜单以改变显示值的位置*/
    label = gtk_label_new("Scale Value Position");
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
    gtk_widget_show(label);

    opt = gtk_option_menu_new();
    menu = gtk_menu_new();

    item = make_menu_item("TOP",G_CALLBACK(cb_pos_menu_select),GINT_TO_POINTER(GTK_POS_TOP));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
    item = make_menu_item("BUTTOM",G_CALLBACK(cb_pos_menu_select),GINT_TO_POINTER(GTK_POS_BOTTOM));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
    item = make_menu_item("RIGHT",G_CALLBACK(cb_pos_menu_select),GINT_TO_POINTER(GTK_POS_RIGHT));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
    item = make_menu_item("LEFT",G_CALLBACK(cb_pos_menu_select),GINT_TO_POINTER(GTK_POS_LEFT));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

    gtk_option_menu_set_menu(GTK_OPTION_MENU(opt),menu);
    gtk_box_pack_start(GTK_BOX(box2),opt,TRUE,TRUE,0);
    gtk_widget_show(opt);

    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);

    box2 = gtk_hbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),0);

    /*设置比例构件的更新方式*/
    label = gtk_label_new("Scale Update Policy:");
    gtk_box_pack_start(GTK_BOX(box2),label,TRUE,TRUE,0);
    gtk_widget_show(label);

    opt = gtk_option_menu_new();
    menu = gtk_menu_new();

    item = make_menu_item("Continuous",G_CALLBACK(cb_update_menu_select),GINT_TO_POINTER(GTK_UPDATE_CONTINUOUS));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
    item = make_menu_item("Discontinuous",G_CALLBACK(cb_update_menu_select),GINT_TO_POINTER(GTK_UPDATE_DISCONTINUOUS));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
    item = make_menu_item("Delayed",G_CALLBACK(cb_update_menu_select),GINT_TO_POINTER(GTK_UPDATE_DELAYED));
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

    gtk_option_menu_set_menu(GTK_OPTION_MENU(opt),menu);
    gtk_box_pack_start(GTK_BOX(box2),opt,TRUE,TRUE,0);
    gtk_widget_show(opt);
    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);

    box2 = gtk_hbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);

    /*用于调整比例构件小数位数*/
    label = gtk_label_new("Scale Digits:");
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
    gtk_widget_show(label);

    adj2 = gtk_adjustment_new(1.0,0.0,5.0,1.0,1.0,0.0);
    g_signal_connect(G_OBJECT(adj2),"value_changed",G_CALLBACK(cb_digits_scale),NULL);
    scale = gtk_hscale_new(GTK_ADJUSTMENT(adj2));
    gtk_scale_set_digits(GTK_SCALE(scale),0);
    gtk_box_pack_start(GTK_BOX(box2),scale,TRUE,TRUE,0);
    gtk_widget_show(scale);

    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);

    box2 = gtk_hbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);

    /*用于调整水平比例构件滚动条的page size */
    label = gtk_label_new("Scrollbar Page Size:");
    gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
    gtk_widget_show(label);

    adj2 = gtk_adjustment_new(1.0,1.0,110.0,1.0,1.0,0.0);
    g_signal_connect(G_OBJECT(adj2),"value_changed",G_CALLBACK(cb_page_size),adj1);
    scale = gtk_hscale_new(GTK_ADJUSTMENT(adj2));
    gtk_scale_set_digits(GTK_SCALE(scale),0);
    gtk_box_pack_start(GTK_BOX(box2),scale,TRUE,TRUE,0);
    gtk_widget_show(scale);

    gtk_box_pack_start(GTK_BOX(box1),box2,TRUE,TRUE,0);
    gtk_widget_show(box2);
    
    /*创建一个分割线*/
    separator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box1),separator,FALSE,TRUE,0);
    gtk_widget_show(separator);

    box2 = gtk_vbox_new(FALSE,10);
    gtk_container_set_border_width(GTK_CONTAINER(box2),10);
    gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,TRUE,0);
    gtk_widget_show(box2);

    /*创建一个退出按钮*/
    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_box_pack_start(GTK_BOX(box2),button,TRUE,TRUE,0);

    /*将退出按钮固定为缺省，只要按回车键就能触发*/
    GTK_WIDGET_SET_FLAGS(button,GTK_CAN_DEFAULT);
    gtk_widget_grab_default(button);

    gtk_widget_show(button);

    gtk_widget_show(window);

}


int main(int argc,char *argv[])
{
    gtk_init(&argc,&argv);

    /*创建范围控件*/
    create_range_controls();

    gtk_main();

    return 0;
}
