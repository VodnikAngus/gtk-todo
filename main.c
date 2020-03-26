#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "widgets/task.c"

#include "src/liste.h"

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  GdkGeometry min_size;
  min_size.min_width = 600;
  gtk_window_set_geometry_hints(GTK_WINDOW(window), NULL, &min_size,
                                GDK_HINT_MIN_SIZE);

  gtk_container_add(GTK_CONTAINER(window), listeW());

  gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;

  int status;
  app = gtk_application_new("com.daredon.todo", G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}