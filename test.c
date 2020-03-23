#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if (defined(_WIN32) || defined(_WIN64))
#define KC "\\"
#else
#define KC "/"
#endif

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "To-do");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;

  const char *folder;
  // folder = "C:\\Users\\SaMaN\\Desktop\\Ppln";
  folder = "." KC "tmp";
  struct stat sb;

  if (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  int status;
  app = gtk_application_new("com.daredon.todo", G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}