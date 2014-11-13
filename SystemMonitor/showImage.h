void showImage(int argc, char *argv[])
{
	GtkWidget *window = NULL;
	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(
			gtk_main_quit), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(
			gtk_main_quit), NULL);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE); // 设置无边框
	gtk_widget_set_app_paintable(window, TRUE);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_widget_realize(window);

	pixbuf = gdk_pixbuf_new_from_file("penguin.gif", NULL); // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 120); // alpha小于128认为透明
	gtk_widget_shape_combine_mask(window, bitmap, 0, 0); // 设置透明蒙板
	gdk_window_set_back_pixmap(window->window, pixmap, FALSE); // 设置窗口背景

	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);

	gtk_widget_show_all(window);
	gtk_main();
}
