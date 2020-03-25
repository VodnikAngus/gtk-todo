#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "widgets/task.c"

#if (defined(_WIN32) || defined(_WIN64))
#include "lib/windows.h"
#else
#include "lib/linux.h"
#endif

#include "lib/razno.h"

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);

  // GtkWidget *list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *tree = gtk_tree_view_new();

  gtk_container_add(GTK_CONTAINER(scroll), tree);
  gtk_container_add(GTK_CONTAINER(window), scroll);
  struct lista *l = spisakfoldera("db");
  struct clan *folder = l->prvi;

  while (folder) {
    GtkWidget *column = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_end(GTK_TREE_VIEW_COLUMN(column),
                                  task(folder->ime), 1);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree),
                                GTK_TREE_VIEW_COLUMN(column));
    // gtk_box_pack_start(GTK_BOX(list), task(folder->ime), 0, 0, 0);
    folder = folder->sledeci;
  }

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