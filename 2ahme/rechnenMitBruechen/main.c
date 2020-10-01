#include <stdio.h>
#include <stdlib.h>

int gibGanzeZahlEin(const char *ptxt) {      //Text verändert sich nicht => const char 
  
  char s[100];
  int wahl;
  int n;
  
  printf("%s: ", ptxt);
  do {
  fgets(s, 100, stdin);
  n = sscanf(s, "%d", &wahl);
  } while (n != 1);
  
  return wahl;
 }

void gibBruchEin(char *ptxt, int *pzaehler, int *pnenner) {
  
  *pzaehler = gibGanzeZahlEin("Zaehler");
  *pnenner  = gibGanzeZahlEin("Nenner");
}

void clrscr () {
  
  system("clear");  //terminal löschen 
  
}
void gibMenueAus() {
  clrscr();
  
  printf("Rechnen mit Bruechen\n"
         "=====================\n");
  printf("1...Addition zweier Brueche\n");
  printf("2...Subtraktion zweier Brueche\n");
  printf("3...Anzahl der Stellen einer Zahl berechnen\n");
  printf("4...Programm beenden\n");
  //Menüfunktion auswählen 
}

void addierenVonBruechen (int z1, int n1, int z2, int n2, int *ze, int *ne) {

    *ze = z1 * n1 + z2 * n2;
    *ne = n1 * n2;

}

void subtrahiereBruch (int z1, int n1, int z2, int n2, int *ze, int *ne) {
    
    *ze = z1 * n1 - z2 * n2;
    *ne = n1 * n2;
}

int ggt (int z, int n) {
    
    if (z < 0) {
        z = -z;
        
    } if (n < 0) {
        n = -n;
        
    } while(z != n) {
         if (z > n) {
             z = z - n;
        
         } else {
             n = n - z;
         }
    }
    return z;
}

void kuerzen (int *ze, int *ne) {
    int teiler = ggt(*ze, *ne);
    *ze = *ze / teiler;
    *ne = *ne / teiler;
}

void gibBruchAus (char *txt, int ze, int ne) {
    
    printf("%s\n", txt);
    kuerzen (&ze, &ne);
    printf("%d / %d\n", ze, ne);
}

int main ()
{
  int wahl = 0;
  char s[4]; 
  int z1, z2, n1, n2;
  int ze = 0;
  int ne = 0;
  do {
    gibMenueAus();
    //Menüfunktion auswählen
    
    wahl = gibGanzeZahlEin("Waehle die Funktion (1-4)");
    switch(wahl) {
    case 1: //addieren 
      printf("Addieren\n");
      gibBruchEin("Bruch 1", &z1, &n1);
      gibBruchEin("Bruch 2", &z2, &n2);
      addierenVonBruechen(z1, n1, z2, n2, &ze, &ne);
      gibBruchAus("Ergebnis:", ze, ne);
      break;
    
    case 2: //Subtrahieren
      printf("Subtrahieren\n");
      gibBruchEin("Bruch 1", &z1, &n1);
      gibBruchEin("Bruch 2", &z2, &n2);
      subtrahiereBruch(z1, n1, z2, n2, &ze, &ne);
      gibBruchAus("Ergebnis:", ze, ne);
      break;
      
    case 3: //Anzahl der Stellen
      printf("Anzahl der Stellen\n");
      z1 = gibGanzeZahlEin("Ihre Zahl: "); 
      break;
      
    case 4: //Programmende
      printf("Programmende\n");
      break;
      
    default: 
      printf("Die Auswahl %d ist ungültig!\n", wahl);
    }
    if (wahl != 4) {
      //warten, bis der User fortfährt
      fgets(s, 4, stdin);
    }
  } while (wahl != 4);
  

  return 0;
}
