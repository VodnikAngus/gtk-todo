#include "razno.h"
#include <stdlib.h>
#include <string.h>

int dodajl(struct lista* l, const char* tekst) {
  struct clan* novi = malloc(sizeof(struct clan));
  novi->ime = malloc(sizeof(char) * (strlen(tekst) + 1));
  if (!novi && !novi->ime) return 0;
  strcpy(novi->ime, tekst);
  novi->sledeci = NULL;

  if (l->prvi == NULL) {
    l->prvi = novi;
    l->poslednji = novi;
    l->duz = 1;
    return 1;
  }
  l->poslednji->sledeci = novi;
  l->poslednji = novi;
  l->duz++;
  return 1;
}

void brisil(struct lista* l) {
  struct clan *t = l->prvi, *t1;
  while (!t) {
    free(t->ime);
    t1 = t->sledeci;
    free(t);
    t = t1;
  }
  free(l);
}