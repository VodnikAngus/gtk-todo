#include "zadaci.h"

#include "../lib/fajlovi.h"

static int uporedi(const struct zadatak *z1, const struct zadatak *z2,
                   enum uredi u) {
  if (z1->prioritet > z2->prioritet) return 0;
  if (z1->prioritet < z2->prioritet) return 1;

  switch (u) {
    case IME:
      return strcmp(z1->ime, z2->ime) > 0;
      break;

    case DATUM:
      return strcmp(z1->datum, z2->datum) > 0;
      break;
  }

  return -1;
}

int dodajzadatak(struct zadaci *l, const gchar *zadatakfajl, enum uredi u) {
  struct zadatak *novi = malloc(sizeof(struct zadatak));
  FILE *zadatak;
  zadatak = fopen(zadatakfajl, "r");
  fscanf(zadatak, "%hd\n", &(novi->prioritet));

  novi->ime = malloc(51 * sizeof(gchar));
  fgets(novi->ime, 50, zadatak);
  novi->ime[strlen(novi->ime) - 1] = '\0';

  novi->datum = malloc(10 * sizeof(gchar));
  fgets(novi->datum, 9, zadatak);
  novi->datum[8] = '\0';
  g_print("Fajl: %s, Prioritet: %hd Naziv: %s, datum: %s\n", zadatakfajl,
          novi->prioritet, novi->ime, novi->datum);

  int brfajlova;
  fscanf(zadatak, "%d\n", &brfajlova);
  g_print("Broj Fajlova: %d\n", brfajlova);

  novi->fajlovi = malloc(brfajlova * sizeof(gchar *));
  for (int i = 0; i < brfajlova; ++i) {
    novi->fajlovi[i] = malloc(51 * sizeof(gchar));
    fgets(novi->fajlovi[i], 50, zadatak);
    novi->fajlovi[i][strlen(novi->fajlovi[i]) - 1] = '\0';
    g_print("Fajl %d: %s\n", i + 1, novi->fajlovi[i]);
  }
  fclose(zadatak);

  struct zadatak *trenutni = l->prvi;
  if (trenutni == NULL) {
    g_print("NULL\n");
    novi->sledeci = NULL;
    l->prvi = novi;

    return 0;
  }
  if (!uporedi(novi, trenutni, u)) {
    novi->sledeci = trenutni;
    l->prvi = novi;
  } else {
    while (trenutni->sledeci && !uporedi(novi, trenutni->sledeci, u)) {
      trenutni = trenutni->sledeci;
    }
    novi->sledeci = trenutni->sledeci;
    trenutni->sledeci = novi;
  }
  return 0;
}
static struct zadaci *citajzadatke(const gchar *ime_liste) {
  GError **greska = NULL;
  gchar *folder = malloc((strlen(ime_liste) + 4) * sizeof(gchar));
  if (!folder) return NULL;
  sprintf(folder, "db" KC "%s", ime_liste);
  GDir *dir = g_dir_open(folder, 0, greska);

  if (!dir) exit(1);

  struct zadaci *l = malloc(sizeof(struct lista));
  l->prvi = NULL;

  const gchar *de;

  while ((de = g_dir_read_name(dir)) != NULL) {
    if (strcmp(de, ".") && strcmp(de, "..")) {
      gchar *fajl = malloc((strlen(folder) + strlen(de) + 18) * sizeof(gchar));
      sprintf(fajl, "%s" KC "%s" KC "__zadatak__.txt", folder, de);

      if (dodajzadatak(l, fajl, IME)) return NULL;
    }
  }

  g_dir_close(dir);

  return l;
}

static gboolean hide(gpointer data) {
  GtkRevealer *revealer = data;
  gtk_revealer_set_reveal_child(revealer, FALSE);

  return FALSE;
}

static gboolean wait(GtkApplication *app, gpointer data) {
  g_timeout_add(300, hide, data);
  return FALSE;
}

static void open_menu(GtkWidget *widget, gpointer data) {
  gtk_menu_popup_at_widget(GTK_MENU(data), widget, GDK_GRAVITY_SOUTH,
                           GDK_GRAVITY_NORTH, NULL);
}

static void delete (GtkWidget *widget, gpointer data) {}

static GtkWidget *zadtakW(char *lista, gchar *text) {
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

  GtkWidget *menu = gtk_menu_new();
  GtkWidget *menu_item = gtk_menu_item_new_with_label("oof");
  g_signal_connect(menu_item, "activate", G_CALLBACK(delete), text);
  gtk_widget_show(menu_item);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

  g_signal_connect(button, "clicked", G_CALLBACK(open_menu), menu);

  gtk_container_add(GTK_CONTAINER(revealer), box);
  return revealer;
}

GtkWidget *zadaciW(char *name) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  struct zadaci *l = citajzadatke(name);
  struct zadatak *zadatak = l->prvi;

  while (zadatak != NULL) {
    GtkWidget *task = zadtakW(name, zadatak->ime);

    gtk_box_pack_start(GTK_BOX(box), task, FALSE, FALSE, 0);
    zadatak = zadatak->sledeci;
  }

  return box;
}