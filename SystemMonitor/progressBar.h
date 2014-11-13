/*
 *  progressBar.h
 *  systemMonitor
 *  Created on: 2012-2-19
 *      Author: zhushengben
 */

#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_
typedef struct ProgressData
{
	GtkWidget *pbar;
	int timer;
	gboolean activity_mode;
	gboolean showCpuProgress;
} _ProgressData;
_ProgressData *pdata;

int createProgressBar(GtkWidget *vbox, gboolean activity_mode,
		gboolean showCpuProgress)
{

	GtkWidget *align;
	GtkWidget *separator;
	GtkWidget *table;
	GtkWidget *button;
	GtkWidget *check;

	/* 为传递到回调函数中的数据分配内存 */
	pdata = g_malloc(sizeof(_ProgressData));
	pdata->showCpuProgress = showCpuProgress;
	/* 创建进度条 */
	pdata->pbar = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(vbox), pdata->pbar);
	gtk_progress_bar_set_orientation(pbar_cpu, GTK_PROGRESS_BOTTOM_TO_TOP);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata->pbar), "running...");
	pdata->activity_mode = activity_mode;
	gtk_widget_show(pdata->pbar);
	separator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox), separator, FALSE, FALSE, 0);
	gtk_widget_show(separator);

	return 0;
}

#endif /* PROGRESSBAR_H_ */
