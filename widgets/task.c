#include <gtk/gtk.h>

gboolean hide(gpointer data) {
  GtkRevealer *revealer = data;
  gtk_revealer_set_reveal_child(revealer, FALSE);

  return FALSE;
}

gboolean wait(GtkApplication *app, gpointer data) {
  g_timeout_add(300, hide, data);
  return FALSE;
}

GtkWidget *task(char *text) {
  GtkWidget *revealer = gtk_revealer_new();
  gtk_revealer_set_reveal_child(GTK_REVEALER(revealer), TRUE);
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  GtkWidget *check = gtk_check_button_new_with_label(text);
  g_signal_connect(check, "toggled", G_CALLBACK(wait), revealer);
  gtk_box_pack_start(GTK_BOX(box), check, 1, 1, 0);

  gtk_widget_set_margin_bottom(box, 5);
  gtk_widget_set_margin_top(box, 5);
  gtk_widget_set_margin_start(box, 10);
  gtk_widget_set_margin_end(box, 10);

  GtkWidget *button = gtk_button_new();
  GtkWidget *buttonImage =
      gtk_image_new_from_icon_name("view-more-symbolic", 1);
  gtk_container_add(GTK_CONTAINER(button), buttonImage);
  gtk_box_pack_start(GTK_BOX(box), button, 0, 0, 0);

  gtk_container_add(GTK_CONTAINER(revealer), box);
  return revealer;
}