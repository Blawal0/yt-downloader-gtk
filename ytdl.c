#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *downloads;
char *videoLink;

char filetype[4] = "mp3\0"; /*Default Selected Filetype*/
const char *filetypes[5] = {"mp3\0", "aac\0", "mp4\0", "mkv\0", NULL};

char quality[5] = "720\0"; /*Default Selected Quality*/
const char *qualityOptions[6] = {"1080\0", "720\0", "480\0", "240\0", "144\0", NULL};

static void GetDownloadLocation(GtkWidget *entry, gpointer user_data)
{
	downloads = gtk_editable_get_text(GTK_EDITABLE(entry));
}

static void GetVideoLink(GtkWidget *entry, gpointer user_data)
{
	videoLink = gtk_editable_get_text(GTK_EDITABLE(entry));
}

static void GetFileType(GtkWidget *dropdown, gpointer user_data)
{
	guint index = gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdown));
	strcpy(filetype, filetypes[index]);
	printf("\n%d - %s\n", index, filetype);
}

static void GetMaxQuality(GtkWidget *selector, gpointer user_data)
{
	guint qindex = gtk_drop_down_get_selected(GTK_DROP_DOWN(selector));
	strcpy(quality, qualityOptions[qindex]);
	printf("\n%d - %s\n", qindex, quality);
}

static void DownloadVideo(GtkWidget *dropdown, gpointer user_data)
{
	char commandToExecute[999];
	puts(filetype);
	sprintf(commandToExecute, "yt-dlp --windows-filenames -f \"[height<=%s]\" -t %s -P %s %s", quality, filetype, downloads, videoLink);
	puts(commandToExecute);
	system(commandToExecute);
	GtkWidget *window;
	window = gtk_window_new();
	GtkWidget *label;
	label = gtk_label_new("SUCCESS");
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"><b>Video Download Finished</b></span>");
	GtkWidget *box;
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
	gtk_window_set_child(GTK_WINDOW(window), box);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 150);
	gtk_window_set_title(GTK_WINDOW(window), "Notification");
	gtk_window_set_resizable(GTK_WINDOW(window), false);
	gtk_box_append(GTK_BOX(box), label);
	label = gtk_label_new(" "); /*spacer*/
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"> </span>");
	gtk_box_append(GTK_BOX(box), label);
	GtkWidget *button;
	button = gtk_button_new();
	label = gtk_label_new("OK");
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"><b>OK</b></span>");
	gtk_button_set_child(GTK_BUTTON(button), label);
	gtk_box_append(GTK_BOX(box), button);
	gtk_window_present(GTK_WINDOW(window));
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);
}

static void activate(GtkApplication *app, gpointer user_data)
{	
	#ifdef _WIN32
		if (getenv("USERPROFILE") != NULL)
		{
			char *defaultLocation = getenv("USERPROFILE");
			strcat(defaultLocation, "\\Downloads\\");
			downloads = defaultLocation;
		}
		else
		{
			char *defaultLocation = "NULL";
			downloads = defaultLocation;
		}
	#elif __unix__
		if (getenv("HOME") != NULL)
		{
			char *defaultLocation = getenv("HOME");
			strcat(defaultLocation, "/Downloads/");
			downloads = defaultLocation;
		}
		else
		{
			char *defaultLocation = "NULL";
			downloads = defaultLocation;
		}
	#elif __APPLE__
		if (getenv("HOME") != NULL)
		{
			char *defaultLocation = getenv("HOME");
			strcat(defaultLocation, "/Downloads/");
			downloads = defaultLocation;
		}
		else
		{
			char *defaultLocation = "NULL";
			downloads = defaultLocation;
		}
	#endif

	puts(downloads);
	
	GtkWidget *window;
	GtkWidget *entry;
	GtkWidget *direntry;
	GtkWidget *button;
	GtkWidget *buttonText;
	GtkWidget *label;
	GtkWidget *box;
	GtkEntryBuffer *directory;
	GtkWidget *dropdown;
	GtkWidget *qualitySelect;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "YouTube Downloader");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
	gtk_window_set_resizable(GTK_WINDOW(window), false);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
	gtk_window_set_child(GTK_WINDOW(window), box);

	label = gtk_label_new("YT LINK");
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"20\"><big><b>YouTube Link:</b></big></span>");
	gtk_box_append(GTK_BOX(box), label);

	entry = gtk_entry_new();
	gtk_box_append(GTK_BOX(box), entry);
	gtk_widget_set_size_request(entry, 350, 50);
	g_signal_connect(entry, "changed", G_CALLBACK(GetVideoLink), entry);

	label = gtk_label_new(" "); /*spacer*/
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"> </span>");
	gtk_box_append(GTK_BOX(box), label);

	label = gtk_label_new("DOWNLOAD LOCATION");
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"16\"><big><b>Download Location: </b></big></span>");
	gtk_box_append(GTK_BOX(box), label);

	directory = gtk_entry_buffer_new(downloads, strlen(downloads));

	direntry = gtk_entry_new_with_buffer(directory);
	gtk_box_append(GTK_BOX(box), direntry);
	gtk_widget_set_size_request(direntry, 350, 50);
	g_signal_connect(direntry, "changed", G_CALLBACK(GetDownloadLocation), direntry);

	label = gtk_label_new(" "); /*spacer*/
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"> </span>");
	gtk_box_append(GTK_BOX(box), label);

	label = gtk_label_new("Filetype");
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"16\"><b>File Type</b></span>");
	gtk_box_append(GTK_BOX(box), label);

	dropdown = gtk_drop_down_new_from_strings(filetypes);
	gtk_widget_set_size_request(dropdown, 100, 50);
	gtk_box_append(GTK_BOX(box), dropdown);
	g_signal_connect(dropdown, "notify::selected", G_CALLBACK(GetFileType), dropdown);

	label = gtk_label_new(" "); /*spacer*/
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"> </span>");
	gtk_box_append(GTK_BOX(box), label);

	label = gtk_label_new("MaxQuality");
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"16\"><b>Max. Quality</b></span>");
	gtk_box_append(GTK_BOX(box), label);

	qualitySelect = gtk_drop_down_new_from_strings(qualityOptions);
	gtk_widget_set_size_request(qualitySelect, 100, 50);
	gtk_box_append(GTK_BOX(box), qualitySelect);
	gtk_drop_down_set_selected(GTK_DROP_DOWN(qualitySelect), 1);
	g_signal_connect(qualitySelect, "notify::selected", G_CALLBACK(GetMaxQuality), qualitySelect);

	label = gtk_label_new(" "); /*spacer*/
	gtk_label_set_markup(GTK_LABEL(label), "<span font=\"12\"> </span>");
	gtk_box_append(GTK_BOX(box), label);

	button = gtk_button_new();
	buttonText = gtk_label_new("Download");
	gtk_label_set_markup(GTK_LABEL(buttonText), "<span font=\"24\"><b>Download</b></span>");
	gtk_button_set_child(GTK_BUTTON(button), buttonText);
	gtk_widget_set_size_request(button, 100, 75);
	gtk_box_append(GTK_BOX(box), button);
	g_signal_connect(button, "clicked", G_CALLBACK(DownloadVideo), dropdown);

	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("youtube.downloader", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
