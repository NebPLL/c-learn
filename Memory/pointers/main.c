#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {

  int n = 5;

  int *arr = malloc(n * sizeof(int));

  if (arr == NULL) {
    printf("Speicher konnte nicht reserviert werden.");
  }

  for (int i = 0; i <= n; i++) {
    arr[i] = i * sizeof(int);
  }

  for (int i = 0; i < n; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
  }

  printf("%d\n", sizeof(long));

  free(arr);
  arr = NULL;

  return 0;
}
