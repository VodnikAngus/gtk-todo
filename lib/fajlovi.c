#include "fajlovi.h"

#include <stdlib.h>

struct lista *spisakfoldera(const gchar *putanja) {
  GError **greska;
  GDir *dir = g_dir_open(putanja, 0, greska);

  if (!dir) exit(1);

  struct lista *l = malloc(sizeof(struct lista));
  l->prvi = NULL;

  const gchar *de;

  while ((de = g_dir_read_name(dir)) != NULL) {
    if (strcmp(de, ".") && strcmp(de, "..")) {
      // g_print(de);
      if (!dodajl(l, de)) return NULL;
    }
  }

  g_dir_close(dir);

  return l;
}

int napravifolder(const gchar *putanja, const gchar *ime) {
  gchar *folder = malloc((strlen(putanja) + strlen(ime) + 2));
  if (!folder) return -1;
  sprintf(folder, "%s" KC "%s", putanja, ime);

  return g_mkdir(folder, 0777);
}

int obrisifolder(const gchar *putanja, const gchar *ime) {
  gchar *folder = malloc((strlen(putanja) + strlen(ime) + 2));
  if (!folder) return -1;
  sprintf(folder, "%s" KC "%s", putanja, ime);

  GError **greska;
  GDir *dir = g_dir_open(folder, 0, greska);

  if (!dir) exit(1);

  const gchar *de;

  while ((de = g_dir_read_name(dir)) != NULL) {
    if (strcmp(de, ".") && strcmp(de, "..")) {
      gchar *t = malloc((strlen(folder) + strlen(de) + 2));
      if (!t) return -1;
      sprintf(t, "%s" KC "%s", folder, de);

      if (g_file_test(t, G_FILE_TEST_IS_DIR)) {
        obrisifolder(folder, de);
        g_print("Folder: %s\n", de);
      } else {
        g_print("Fajl: %s\n", de);
        remove(t);
      }
    }
  }

  g_rmdir(folder);
  g_dir_close(dir);
  return 0;
}
