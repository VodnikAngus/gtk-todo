#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  GdkGeometry min_size;
  min_size.min_width = 800;
  gtk_window_set_geometry_hints(GTK_WINDOW(window), NULL, &min_size,
                                GDK_HINT_MIN_SIZE);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *sidebar = gtk_stack_sidebar_new();

  GtkWidget *header1 = gtk_header_bar_new();
  GtkWidget *header2 = gtk_header_bar_new();
  GtkWidget *header3 = gtk_header_bar_new();
  GtkWidget *header4 = gtk_header_bar_new();
  GtkWidget *header5 = gtk_header_bar_new();

  gtk_header_bar_set_title(GTK_HEADER_BAR(header1), "oof");
  gtk_header_bar_set_title(GTK_HEADER_BAR(header2), "oof");
  gtk_header_bar_set_title(GTK_HEADER_BAR(header3), "oof");
  gtk_header_bar_set_title(GTK_HEADER_BAR(header4), "oof");
  gtk_header_bar_set_title(GTK_HEADER_BAR(header5), "oof");

  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header5), TRUE);

  gtk_box_pack_start(GTK_BOX(box), header1, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), header2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), header3, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), header4, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), header5, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(window), box);

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