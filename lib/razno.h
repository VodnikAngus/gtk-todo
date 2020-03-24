#ifndef RAZNO_H
#define RAZNO_H

// Makroi

// Tipovi

struct lista {
  struct clan* prvi;
  struct clan* poslednji;
  unsigned int duz;
};

struct clan {
  char* ime;
  struct clan* sledeci;
};

// Funkcije

int dodajl(struct lista* l, char* tekst);
void brisil(struct lista* l);

#endif /* RAZNO_H */