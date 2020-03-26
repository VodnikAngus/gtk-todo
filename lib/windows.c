
#include "./windows.h"

#include <windows.h>

struct lista *spisakfoldera(char *putanja) {
  HANDLE hFind;
  WIN32_FIND_DATA FindData;

  // Find the first filestruct
  struct lista *l = malloc(sizeof(struct lista));
  l->prvi = NULL;

  char putanjaN[strlen(putanja) + 2];
  sprintf(putanjaN, "%s" KC "*", putanja);
  hFind = FindFirstFile(putanjaN, &FindData);

  do {
    if (strcmp(FindData.cFileName, ".") && strcmp(FindData.cFileName, "..")) {
      if (!dodajl(l, FindData.cFileName)) return NULL;
    }
  } while (FindNextFile(hFind, &FindData));

  FindClose(hFind);
  return l;
}
