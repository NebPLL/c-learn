
#include <stdio.h>
void countUp(int *countUp) { (*countUp)++; }
int main(int argc, char *argv[]) {
  int test = 0;

  for (int i = 0; i < 10; i++) {
    countUp(&test);
    printf("%d \n", test);
  }

  return 0;
}
