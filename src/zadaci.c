#include "zadaci.h"

static GtkWidget *zadtakW(char *name) { return gtk_label_new(name); }

GtkWidget *zadaciW(char *name) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  char putanja[strlen(name) + 3];
  sprintf(putanja, "db" KC "%s", name);
  struct lista *l = spisakfoldera(putanja);
  struct clan *folder = l->prvi;

  while (folder != NULL) {
    GtkWidget *task = zadtakW(folder->ime);

    gtk_box_pack_start(GTK_BOX(box), task, FALSE, FALSE, 0);
    folder = folder->sledeci;
  }

  return box;
}