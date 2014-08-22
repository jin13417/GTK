
/*File:helloworld.c
 *Date:2013-11-23
 *Author:sjin
 *Mail:413977243@qq.com
 */

/*my first test program*/
#include <gtk-2.0/gtk/gtk.h>
/* ����һ���ص�������data �����ڱ�ʾ���б����ԡ�
 * �����и���Ļص�����ʾ����*/
void hello( GtkWidget *widget,gpointer   data )
{
    g_print ("Hello World\n");
}
gint delete_event( GtkWidget *widget,GdkEvent  *event,gpointer   data )
{
    /* ������ "delete_event" �źŴ��������� FALSE��GTK �ᷢ�� "destroy" �źš�
     * ���� TRUE���㲻ϣ���رմ��ڡ�
     * �����뵯������ȷ��Ҫ�˳���?���Ի���ʱ�������á�*/
    g_print ("delete event occurred\n");
    /* �� TRUE Ϊ FALSE �����رգ��ر�ʱ����destroy()��*/
    return TRUE;
}
/* ��һ���ص����� */
void destroy( GtkWidget *widget,gpointer   data )
{
    gtk_main_quit ();
}
int main( int   argc, char *argv[] )
{
    /* GtkWidget �ǹ����Ĵ洢���� */
    GtkWidget *window;
    GtkWidget *button;
    
    /* ������������е� GTK ����Ҫ���á��������������н������������͵��ó�����*/
    gtk_init (&argc, &argv);
        /* ����һ���´��� */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*���ô��ڱ���*/
    gtk_window_set_title(GTK_WINDOW(window),"My first program helloworld!");
    
    /* �������յ� "delete_event" �ź� (����ź��ɴ��ڹ�����������ͨ���ǡ��رա�
     * ѡ����Ǳ������ϵĹرհ�ť������)����������������ǰ�涨��� delete_event() ������
     * �����ص������� data ����ֵ�� NULL�����ᱻ�ص��������ԡ�*/
    g_signal_connect (G_OBJECT (window), "delete_event",G_CALLBACK (delete_event), NULL);
    
    /* �������������� "destroy" �¼���һ���źŴ�������  
     * ��������ڵ��� gtk_widget_destroy() �������� "delete_event" �ص������з��� FALSE ֵ
     * ���ᴥ������¼���*/
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (destroy), NULL);
    
    /* ���ô��ڱ߿�Ŀ�ȡ�*/
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* ����һ����ǩΪ "Hello World" ���°�ť��*/
    button = gtk_button_new_with_label ("Hello World");
    
    /* ����ť�յ� "clicked" �ź�ʱ����� hello() ����������NULL����
     * ����Ϊ������hello() ������ǰ�涨���ˡ�*/
    g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (hello), NULL);
    
    /* �������ťʱ����ͨ������ gtk_widget_destroy(window) ���رմ��ڡ�
     * "destroy" �źŻ�������Ӵ��ڹ�����������*/
    g_signal_connect_swapped (G_OBJECT (button), "clicked", G_CALLBACK (gtk_widget_destroy),window);
    
    /* �Ѱ�ť���봰�� (һ�� gtk ����) �С�*/
    gtk_container_add (GTK_CONTAINER (window), button);
    
    /* ���һ������ʾ�´����İ�ť�ʹ��� */
    gtk_widget_show (button);
    gtk_widget_show (window);
    
    /* ���е� GTK ���������һ�� gtk_main() ��������������ͣ������
     * �ȴ��¼� (������¼�������¼�) �ķ�����*/
    gtk_main ();
    
    return 0;
}
