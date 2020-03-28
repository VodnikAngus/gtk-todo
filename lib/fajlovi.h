#ifndef FAJLOVI_H
#define FAJLOVI_H

#include <fcntl.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "razno.h"

// Makroi

#define KC "/"

// Tipovi

// Funkcije

struct lista *spisakfoldera(const gchar *putanja);
int napravifolder(const gchar *putanja, const gchar *ime);
int obrisifolder(const gchar *putanja, const gchar *ime);

#endif /* FAJLOVI_H */