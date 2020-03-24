#include "windows.h"

#include <stdlib.h>

struct lista *spisakfoldera(char *putanja) {
    struct lista *l = malloc(sizeof(struct lista));
    l->prvi = NULL;
    dodajl(l, "asd1");
    dodajl(l, "asd2");
    dodajl(l, "asd3");
    return l;
}