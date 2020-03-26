#include "linux.h"
#include "razno.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

struct lista *spisakfoldera(char *putanja) {
  struct dirent *de;

  DIR *dr = opendir(putanja);

  if (dr == NULL) {
    return NULL;
  }

  struct lista *l = malloc(sizeof(struct lista));
  l->prvi = NULL;


  while ((de = readdir(dr)) != NULL) {
    if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
      if (!dodajl(l, de->d_name)) return NULL;
    }
  }

  closedir(dr);
  return l;
}