#include "zadaci.h"

#include "../lib/fajlovi.h"

static void zadatakW(char *, struct zadatak *);

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

static int dodajzadatak(struct zadaci *l, const gchar *zadatakfajl,
                        const char *zadatakfolder, enum uredi u) {
  struct zadatak *novi = malloc(sizeof(struct zadatak));
  FILE *zadatak;
  zadatak = fopen(zadatakfajl, "r");
  if (!fscanf(zadatak, "%hd\n", &(novi->prioritet))) return 1;

  int d_ime = 1;
  gchar c;
  do {
    d_ime++;
    c = fgetc(zadatak);
  } while (c != '\n');

  novi->ime = malloc(d_ime * sizeof(gchar));

  novi->datum = malloc(14 * sizeof(gchar));
  if (!fgets(novi->datum, 13, zadatak)) return 1;
  novi->datum[12] = '\0';

  if (!fscanf(zadatak, "%d\n", &(novi->broj_fajlova))) return 1;
  novi->fajlovi = malloc(novi->broj_fajlova * sizeof(gchar *));
  int *d_fajl = malloc(novi->broj_fajlova * sizeof(int));
  for (int i = 0; i < novi->broj_fajlova; ++i) {
    d_fajl[i] = 1;
    do {
      d_fajl[i]++;
      c = fgetc(zadatak);
    } while (c != '\n');
    novi->fajlovi[i] = malloc(d_fajl[i] * sizeof(gchar));
  }

  int d_opis = 0;

  do {
    d_opis++;
    c = fgetc(zadatak);
  } while (c != EOF);

  novi->opis = malloc(d_opis * sizeof(gchar));

  fclose(zadatak);
  zadatak = fopen(zadatakfajl, "r");

  if (!fscanf(zadatak, "%hd\n", &(novi->prioritet))) return 1;

  if (!fgets(novi->ime, d_ime, zadatak)) return 1;
  novi->ime[strlen(novi->ime) - 1] = '\0';

  if (!fgets(novi->datum, 13, zadatak)) return 1;
  novi->datum[12] = '\0';

  if (!fscanf(zadatak, "%d\n", &(novi->broj_fajlova))) return 1;

  for (int i = 0; i < novi->broj_fajlova; ++i) {
    if (!fgets(novi->fajlovi[i], d_fajl[i], zadatak)) return 1;
    novi->fajlovi[i][strlen(novi->fajlovi[i]) - 1] = '\0';
  }
  for (int i = 0; i < d_opis; i++) {
    novi->opis[i] = fgetc(zadatak);
  }
  novi->opis[d_opis - 1] = '\0';

  novi->lista = malloc((sizeof(l->ime) + 1) * sizeof(gchar));
  strcpy(novi->lista, l->ime);

  novi->ime_foldera = malloc((strlen(zadatakfolder) + 1) * sizeof(gchar));
  strcpy(novi->ime_foldera, zadatakfolder);
  fclose(zadatak);

  struct zadatak *trenutni = l->prvi;
  if (trenutni == NULL) {
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
  l->ime = malloc((sizeof(strlen(ime_liste)) + 1) * sizeof(gchar));
  strcpy(l->ime, ime_liste);
  l->prvi = NULL;

  const gchar *de;

  while ((de = g_dir_read_name(dir)) != NULL) {
    if (strcmp(de, ".") && strcmp(de, "..")) {
      gchar *fajl = malloc((strlen(folder) + strlen(de) + 18) * sizeof(gchar));
      sprintf(fajl, "%s" KC "%s" KC "__zadatak__.txt", folder, de);

      if (dodajzadatak(l, fajl, de, DATUM)) return NULL;
    }
  }

  g_dir_close(dir);

  return l;
}

static void napravizadatak(GtkWidget *button, gchar *lista) {
  struct zadatak *novi = malloc(sizeof(struct zadatak));
  novi->lista = malloc(strlen(lista) * sizeof(gchar));
  strcpy(novi->lista, lista);
  novi->prioritet = 0;

  novi->ime = malloc(4 * sizeof(gchar));
  strcpy(novi->ime, "ime");
  novi->datum = malloc(13 * sizeof(gchar));
  strcpy(novi->datum, "202004031600");

  novi->broj_fajlova = 0;

  novi->opis = malloc(5 * sizeof(gchar));
  novi->opis = "opis";

  gchar *noviFolder = malloc((4 + strlen(lista)) * sizeof(gchar));
  sprintf(noviFolder, "db" KC "%s", lista);
  napravifolder(noviFolder, novi->ime);

  gchar *noviFajl =
      malloc((17 + strlen(noviFolder) + strlen(novi->ime)) * sizeof(gchar));
  sprintf(noviFajl, "%s" KC "%s" KC "__zadatak__.txt", noviFolder, novi->ime);

  FILE *noviF = fopen(noviFajl, "w");

  fprintf(noviF, "%hd\n", novi->prioritet);
  fprintf(noviF, "%s\n", novi->ime);
  fprintf(noviF, "%s\n", novi->datum);
  fprintf(noviF, "%d\n", novi->broj_fajlova);
  for (int i = 0; i < novi->broj_fajlova; i++) {
    fprintf(noviF, "%s\n", novi->fajlovi[i]);
  }
  fprintf(noviF, "%s", novi->opis);

  fclose(noviF);
}

static gboolean hide(gpointer data) {
  struct zadatak *zadatak = (struct zadatak *)data;
  GtkRevealer *revealer = GTK_REVEALER(zadatak->widget);
  gtk_revealer_set_reveal_child(revealer, FALSE);

  return FALSE;
}

static gboolean wait(GtkWidget *widget, gpointer zadatak) {
  g_timeout_add(300, hide, zadatak);
  return FALSE;
}

static void open_menu(GtkWidget *widget, gpointer data) {
  gtk_menu_popup_at_widget(GTK_MENU(data), widget, GDK_GRAVITY_SOUTH,
                           GDK_GRAVITY_NORTH, NULL);
}

static void delete (GtkWidget *widget, struct zadatak *zadatak) {
  wait(NULL, zadatak);
  gchar *folder = malloc((5 + strlen(zadatak->lista)) * sizeof(gchar));
  sprintf(folder, "db" KC "%s", zadatak->lista);
  obrisifolder(folder, zadatak->ime_foldera);
}

static void zadatakW(char *lista, struct zadatak *zadatak) {
  GtkWidget *revealer = gtk_revealer_new();
  gtk_revealer_set_reveal_child(GTK_REVEALER(revealer), TRUE);
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  GtkWidget *check = gtk_check_button_new_with_label(zadatak->ime);
  g_signal_connect(check, "toggled", G_CALLBACK(wait),
                   (struct zadatak *)zadatak);
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
  GtkWidget *menu_item = gtk_menu_item_new_with_label("Obriši");
  g_signal_connect(menu_item, "activate", G_CALLBACK(delete), zadatak);
  gtk_widget_show(menu_item);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

  g_signal_connect(button, "clicked", G_CALLBACK(open_menu), menu);

  gtk_container_add(GTK_CONTAINER(revealer), box);
  zadatak->widget = revealer;
}

GtkWidget *zadaciW(gchar *lista) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  struct zadaci *l = citajzadatke(lista);
  struct zadatak *zadatak = l->prvi;

  while (zadatak != NULL) {
    zadatakW(lista, zadatak);

    gtk_box_pack_start(GTK_BOX(box), zadatak->widget, FALSE, FALSE, 0);
    zadatak = zadatak->sledeci;
  }
  GtkWidget *new_button = gtk_button_new_with_label("novi");
  g_signal_connect(new_button, "clicked", G_CALLBACK(napravizadatak), lista);
  GtkWidget *new_button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(new_button_box), new_button);
  gtk_box_pack_start(GTK_BOX(box), new_button_box, FALSE, FALSE, 0);

  return box;
}