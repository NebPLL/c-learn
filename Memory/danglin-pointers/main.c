/*
Ein Dangling Pointer ist ein Pointer, der eigentlich mit free() schon
freigegeben ist (es gibt auch andere Wege, z.B. wenn die Variable ihren
Scope verlässt).

Etwas Harmloses, was passieren könnte, ist, dass das Programm abstürzt.
Das kann trotzdem schwer zu finden sein, weil der Absturz oft erst viel
später passiert (z.B. bei einem ganz anderen malloc/free), nicht direkt
an der Stelle, wo der Fehler eigentlich liegt.

Schlimmer wäre, wenn das Programm einfach weiterläuft und der Dangling
Pointer unerkannt bleibt. Im schlimmsten Fall fordert das Programm
später neuen Speicher an (z.B. für Daten von aussen), und der Allocator
gibt dafür genau den freigegebenen Block zurück. Ein Angreifer kann
dann über diese neuen Daten den Inhalt an dieser Adresse kontrollieren,
auf den das Programm über den alten, dangling Pointer weiterhin
zugreift, was zu falschen Ergebnissen oder Sicherheitsproblemen führen
kann.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
  int is_admin;
  char name[32];
};

int main(void) {
  // Normaler-Code
  struct user *u = malloc(sizeof *u);
  u->is_admin = 0; // Der -> Operator ist dafür da das man nicht immer
                   // (*u).is_admin schreiben muss.
  strcpy(u->name, "gast");

  printf("Vorher:  name=%s is_admin=%d (%p)\n", u->name, u->is_admin,
         (void *)u);

  free(u);

  char *eingehende_daten = malloc(sizeof(struct user));
  printf("Neuer Block liegt bei: %p\n", eingehende_daten);

  // Angreiffer code
  memset(eingehende_daten, 0, sizeof(struct user));
  *(int *)eingehende_daten = 1; // entspricht is_admin = 1
  memcpy(eingehende_daten + sizeof(int), "evil-payload", 13);

  // Auswertung
  printf("Nachher: name: %s is_admin: %d (%p)\n", u->name, u->is_admin,
         (void *)u);

  if (u->is_admin) {
    printf(">>> Zugriff als Admin gewaehrt, obwohl 'u' eigentlich der alte, "
           "freigegebene Gast-User ist!\n");
  } else {
    printf(">>> kein Admin-Zugriff\n");
  }

  return 0;
}
