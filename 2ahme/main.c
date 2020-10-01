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

int main ()
{
  int wahl = 0;
  char s[4]; 
  int z1, z2, n1, n2;
  do {
    gibMenueAus();
    //Menüfunktion auswählen
    
    wahl = gibGanzeZahlEin("Waehle die Funktion (1-4)");
    switch(wahl) {
    case 1: //addieren 
      printf("Addieren\n");
      gibBruchEin("Bruch 1", &z1, &n1);
      gibBruchEin("Bruch 2", &z2, &n2);
      break;
    
    case 2: //Subtrahieren
      printf("Subtrahieren\n");
      gibBruchEin("Bruch 1", &z1, &n1);
      gibBruchEin("Bruch 2", &z2, &n2);
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

