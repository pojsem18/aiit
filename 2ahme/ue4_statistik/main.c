#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define s_laenge_max 100

int gibZahlenEin(double f[]) {

  int z = 1;
  int n;
  int rv = 0; 
  char s[s_laenge_max];
  double zahl;

  printf("Ihre Zahlen\n\n");
  do {

    do {
      printf("Zahl%d: ", z);
      fgets(s, s_laenge_max, stdin);
      fflush(stdin); 
      n = sscanf(s, "%lf", &zahl);
    } while (n < 1);

    if (zahl > 0) {
      f[rv] = zahl;
      rv = rv + 1;
      z = z + 1;
    }

  } while (rv <= 1000 && zahl >= 0);

  return rv;
}
double berechneMittelwert(double f[], int anzahl) {

  double ze = 0;
  double rv= 0;

  for(int i = 0; i < anzahl; i++) {
    ze = ze + f[i];
  }
  rv = ze / anzahl;
  return rv;
}

double berechneStdAbw(double f[], int anzahl, double mittelwert) {

  double ze; 
  double rv;

  for(int i = 0; i < anzahl; i++) {

    ze = ze + pow((f[i] - mittelwert), 2);

  }
  rv = ze / anzahl;
  rv = sqrt (rv);
  return rv;
}

int main ()
{

  double f[999];
  int anzahl; 
  double mittelwert;
  double stdAbw;

  anzahl = gibZahlenEin(f);
  mittelwert = berechneMittelwert(f, anzahl);
  printf("\n\tMittelwert = %.3lf\n", mittelwert);
  stdAbw = berechneStdAbw(f, anzahl, mittelwert);
  printf("\tStellenabweichnug = %.3lf\n", stdAbw);

  return 0;
}