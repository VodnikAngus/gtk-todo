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
    // printf("Could not open current directory");
    return NULL;
  }

  struct lista *l = malloc(sizeof(struct lista));
  l->prvi = NULL;

  // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
  // for readdir()

  while ((de = readdir(dr)) != NULL) {
    if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
      if (!dodajl(l, de->d_name)) return NULL;
      // printf("%s\n", l->poslednji->ime);
    }
  }

  closedir(dr);
  return l;
}