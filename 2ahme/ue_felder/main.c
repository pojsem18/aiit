#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int randomNumber(int ug, int og) {
    int rv;
    rv = (rand()%(og - ug +1)) + ug;
    return rv;
}


double FkRandomNumber(double ug, double og) {
    double rv;
    rv = ug + rand() * ((og -ug)/RAND_MAX);
    return rv;
}

int feldErstellen(double f[]) {
    int rv;
    rv = randomNumber(20, 60);

    for(int i = 0; i < rv; i++) {
        f[i] = FkRandomNumber(50, 250);
    }

    return rv;

}

void feldAusgabe(char* txt, double f[], int anzahl) {
  int i;
  printf("%s\n", txt);
  for (i=0; i<anzahl; i++)
    printf("%8.3lf", f[i]);
  printf("\n");
  if ((anzahl % 10) > 0)
    printf("\n");
}

void feldUmkehren(double f[], int anzahl) {
    double tausche = 0;
    anzahl = anzahl - 1;

    for(int i = 0; i < (anzahl / 2); i++) {
        tausche = f[i];
        f[i] = f[anzahl - i];
        f[anzahl - i] = tausche;
    }
}

void minMax2(double f[], int anzahl, double* min2, double* max2) {

    *min2 = f[1];
    *max2 = f[anzahl - 2];
}

void bubbleSort(double f[], int anzahl) {
    double tausch;

    for (int i = 1; i < anzahl; i++) {
        for (int j = 0; j < anzahl - 1 ; j++)  {
            if (f[j] > f[j + 1]) {
                tausch = f[j];
                f[j] = f[j + 1];
                f[j + 1] = tausch;
            }
        }
    }
}

int main() {
  double f[MAX];
  int anzahl = 0;
  double min2, max2;

  srand(time(NULL));

  anzahl = feldErstellen(f);
  feldAusgabe("Feld1", f, anzahl);
  feldUmkehren(f, anzahl);
  feldAusgabe("Feld umgekehrt", f, anzahl);
  bubbleSort(f, anzahl);
  feldAusgabe("Feld sortiert", f, anzahl);
  minMax2(f, anzahl, &min2, &max2);
  printf("Min2 : %.2lf\nMax2 : %.2lf",min2, max2);

  return 0;
}

