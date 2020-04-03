#ifndef ZADACI_H
#define ZADACI_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/fajlovi.h"
#include "../lib/razno.h"

enum uredi { IME, DATUM };

struct zadaci {
  gchar *ime;
  struct zadatak* prvi;
  unsigned int duz;
};

struct zadatak {
  gchar* lista;
  short int prioritet;
  gchar* ime;
  gchar* datum;
  int broj_fajlova;
  gchar** fajlovi;
  gchar* opis;
  GtkWidget* widget;
  gchar *ime_foldera;
  struct zadatak* sledeci;
};

GtkWidget* zadaciW(char* name);

#endif /* ZADACI_H */