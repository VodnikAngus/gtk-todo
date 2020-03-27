#include "linux.h"
#include "razno.h"

#define _XOPEN_SOURCE 500
#include <dirent.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct lista *spisakfoldera(const char *putanja) {
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

int napravifolder(const char *putanja, char *ime) {
  char folder[strlen(putanja) + strlen(ime) + 2];
  sprintf(folder, "%s" KC "%s", putanja, ime);

  if (mkdir(folder, 0777) == -1) return 0;

  return 1;
}

static int rmrfp(const char *putanja, const struct stat *statb, int tip,
                 struct FTW *ftps) {
  if (tip == FTW_DP) {
    rmdir(putanja);
  } else if (tip == FTW_F) {
    unlink(putanja);
  } else {
    return 1;
  }
  return 0;
}

int obrisifolder(const char *putanja, char *ime) {
  char folder[strlen(putanja) + strlen(ime) + 2];
  sprintf(folder, "%s" KC "%s", putanja, ime);
  return !nftw(folder, rmrfp, 64, FTW_DEPTH | FTW_PHYS);
}