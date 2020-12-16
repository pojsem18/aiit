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

void merge(double f[], int links, int mitte, int rechts)
{
   
    double l[MAX], r[MAX]; 
    int i,j, k;
    int nl = mitte - links + 1;
    int nr = rechts - mitte;
   
    for (i = 0; i < nl; i++)
        l[i] = f[links +i];
    for (j = 0; j < nr; j++)
        r[j] = f[mitte + 1 + j];

    i = 0;
    j = 0;
    k = links;
    while( (i < nl) && (j < nr))
    {
        if(l[i] > r[j])
        {
            f[k] = r[j];
            j++;
            k++;
        }
        else
        {
            f[k] = l[i];
            i++;
            k++;
        }
    }
   
    while( (i < nl) )
        f[k++] = l[i++];
    while( (j < nr) )
        f[k++] = r[j++];
}
void mergeSort2(double f[], int links, int rechts)
{
    if(links < rechts)
    {
        int mitte = links + (rechts - links)/2;
        mergeSort2(f, links, mitte);
        mergeSort2(f, mitte + 1, rechts);
        merge(f, links, mitte, rechts);
    }
}
void mergeSort(double f[], int anzahl)
{
    mergeSort2(f, 0, anzahl-1);
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
  mergeSort(f, anzahl);
  feldAusgabe("Feld sortiert", f, anzahl);
  minMax2(f, anzahl, &min2, &max2);
  printf("Min2 : %.2lf\nMax2 : %.2lf",min2, max2);

  return 0;
}

