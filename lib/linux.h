#ifndef LINUX_H
#define LINUX_H

#include "razno.h"

// Makroi

#define KC "/"

// Tipovi

// Funkcije

struct lista *spisakfoldera(const char *putanja);
int napravifolder(const char *putanja, char *ime);
int obrisifolder(const char *putanja, char *ime);

#endif /* LINUX_H */