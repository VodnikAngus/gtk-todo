#ifndef ZADACI_H
#define ZADACI_H

#include <gtk/gtk.h>

#if (defined(_WIN32) || defined(_WIN64))
#include "../lib/windows.h"
#else
#include "../lib/linux.h"
#endif

#include "../lib/razno.h"

GtkWidget *zadaciW(char *name);

#endif /* ZADACI_H */