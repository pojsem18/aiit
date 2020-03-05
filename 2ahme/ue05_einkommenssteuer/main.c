#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
double kreis, rechteck, quadrat, rechteckb, flaeche;
char r[100];
int wahl;


    printf("Was möchten Sie ausrechnen?\n");
    printf("------------------------------------------\n");
    printf("------------------------------------------\n");

      printf("1... Fläche eines Kreises\n");
      printf("2... Fläche eines Quadrats\n");
      printf("3... Fläche eines Rechtecks\n\n");

        printf("Ihre Auswahl: \n");
        fgets(r, 100, stdin);
        sscanf(r, "%d", &wahl);

          if(wahl == 1) {
            printf("Radius: \n");
            fgets(r, 100, stdin);
            sscanf(r, "%lf", &kreis);

            flaeche = (kreis * kreis) * M_PI;

            printf("Die Fläche eines Kreises lautet: \n\n");

          } else if(wahl == 2) {

              printf("Seitenlaenge: \n");
              fgets(r, 100, stdin);
              sscanf(r, "%lf", &quadrat);

              flaeche= quadrat * quadrat;

              printf("Die Fläche eines Quadrats lautet: \n\n");

          } else if (wahl == 3) {

            printf("Seitenlaenge a: \n");
            fgets(r, 100, stdin);
            sscanf(r, "%lf", &rechteck);

            printf("Seitenlaenge b: \n");
            fgets(r, 100, stdin);
            sscanf(r, "%lf", &rechteckb);

            flaeche = rechteck * rechteckb;

            printf("Die Fläche eines Rechtecks lautet: \n\n");

            } else {

            printf("Falsche Eingabe du Trottel\n");

            return 1;
            }

printf("\n\nFläche: %.2f m2\n\n", flaeche);

            return 0;




}
