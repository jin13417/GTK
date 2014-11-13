/*
 *  refresh.h
 *  SystemMonitor
 *  Created on: 2012-2-21
 *      Author: zhushengben
 */

#ifndef REFRESH_H_
#define REFRESH_H_
/* 更新进度条,这样就能够看到进度条的移动 */
gint refresh(gpointer data)
{
	/* cpu */
	/* 建一个矩形绘图区 */
	GdkGC *gc_chart = gdk_gc_new(cpu_draw_area->window);
	//	update_widget_bg(gc_chart, BACK_IMAGE);

	/* 背景颜色 */
	GdkColor color;
	color.red = 0x0000;
	color.green = 0x0000;
	color.blue = 0x0000;
	gdk_gc_set_rgb_fg_color(gc_chart, &color);
	int width, height, curPoint, step;
	cpu_rate = getCpuUseRatio() / 100;
	gdk_draw_rectangle(cpu_graph, gc_chart, TRUE, 0, 0,
			cpu_draw_area->allocation.width, cpu_draw_area->allocation.height);
	width = cpu_draw_area->allocation.width;
	height = cpu_draw_area->allocation.height;
	curPoint = (int) (cpu_rate * (double) height);
	cpuPoints[99] = height - curPoint;
	int i;
	for (i = 0; i < 99; i++)
	{
		/* 后一时刻的为前面取代 */
		cpuPoints[i] = cpuPoints[i + 1];
	}
	step = width / 99;
	GdkGC *gc = gdk_gc_new(GDK_DRAWABLE(cpu_graph));
	gdk_color_parse("darkred", &color);
	if (cpu_rate > 0.1)
		gdk_color_parse("red", &color);
	gdk_gc_set_foreground(gc, &color);
	/*	gdk_gc_set_line_attributes(GdkGC *gc,//
	 line_width,
	 GdkLineStyle line_style,
	 GdkCapStyle cap_style,
	 GdkJoinStyle join_style);
	 */
	gdk_gc_set_line_attributes(gc, 1, GDK_LINE_SOLID, GDK_CAP_ROUND,
			GDK_JOIN_MITER);

	for (i = 99; i >= 1; i--)
	{
		gdk_draw_line(GDK_DRAWABLE(cpu_graph), gc, i * step, cpuPoints[i], /* 第一个点坐标 */
		(i - 1) * step, cpuPoints[i - 1]); /* 第二个点坐标 */
	}

	gtk_widget_queue_draw(cpu_draw_area);
	char buffer[50] = "cpu使用率:\n\n";
	char cbuf[5];
	gcvt(cpu_rate * 100, 5, cbuf);
	strcat(cbuf, "%");
	strcat(buffer, cbuf);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar_cpu), buffer);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar_cpu), cpu_rate);

	_ProgressData *pdata = (_ProgressData *) data;
	gdouble new_val;
	if (pdata->activity_mode)
		gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pdata->pbar));
	else
	{
		if (!pdata->showCpuProgress)
		{
			/* 使用在调整对象中设置的取值范围计算进度条的值 */
			new_val = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(
					pdata->pbar)) + 0.01;
			if (new_val > 1.0)
				new_val = 0.0;
		}
		else
			new_val = cpu_rate;
		/* 设置进度条的新值 */
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata->pbar), new_val);
	}

	set_label_mem_text();

	set_label_proc_text(label_proc);
	/* 这是一个 timeout 函数,返回 TRUE,这样它就能够继续被调用 */
	return TRUE;
}

#endif /* REFRESH_H_ */
