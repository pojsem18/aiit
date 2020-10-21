#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define s_laenge_max 10

int gibZahlenEin(double f[]) 
{

  int z = 1;
  int n;
  int rv = 0; 
  char s[s_laenge_max];
  double zahl;

  printf("Geben Sie Ihre Zahlen ein\n\n\n");
  
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

  } while (rv <= 10 && zahl >= 0);

  return rv;
  
}
double berechneMittelwert(double f[], int anzahl) 
{

  double ze = 0;
  double rv= 0;

  for(int i = 0; i < anzahl; i++) {
    ze = ze + f[i];
    
  }
  
  rv = ze / anzahl;
  return rv;
  
}

double berechneStdAbw(double f[], int anzahl, double mittelwert)
{

  double ze; 
  double rv;
  

  for(int i = 0; i < anzahl; i++) {

    ze = ze + ((f[i] - mittelwert), 2);

  }

  rv = ze / anzahl;
  

  return rv;
  
}

int main ()
{

  double f[10];
  int anzahl; 
  double mittelwert;
  double standardabweichung;

  anzahl = gibZahlenEin(f);
  mittelwert = berechneMittelwert(f, anzahl);
  
  printf("\n\Mittelwert = %.3lf\n", mittelwert);
  printf("\nStandardabweichnug = %.3lf\n", standardabweichung);

  return 0;
  
}