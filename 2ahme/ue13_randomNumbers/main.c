#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int intRandom (int min, int max) {
  
  int rv;
  rv = rand() % max + min;
  return rv;
}

int main ()
{
  int intRandomZahl;
  double doubleRandomZahl;
  
  srand(time(NULL));
  
  printf("RAND_MAX = %d\n", RAND_MAX);
  
  printf("1:\n");
  for (int i = 0; i < 10; i++) {
    intRandomZahl = intRandom (1, 6);
    printf("Zahl = %d\n", intRandomZahl);
  }
  printf("2:\n");
  for (int a = 0; a < 6; a++) {
    printf("%d\n", rand());
  }
  printf("3:\n");
  for (int b = 0; b < 20; b++) {
    printf("%d\n", rand() % 6 + 1);
  }
  printf("4.\n");
  for (int c = 0; c < 5; c++) {
    printf("%f\n", 1.0 * rand() / RAND_MAX);
  }
  printf("5:\n");
  for (int d = 0; d < 5; d++) {
    printf("%f\n", 200 * rand() / RAND_MAX - 100); 
  }

  return (0);
}

