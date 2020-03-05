#include <stdio.h>

int main () {
  
  char s[100];
  int n;
  double r1; // obere Widerstand
  double r2; // unterer Widerstand
  double ue; // Eingangsspannung
  double ua; // Ausgangsspannung
  
  printf("UE07 - Spannungsteiler\n");
  
  do {
    printf("Widerstand R1/Ohm: ");
    fgets(s, 100, stdin);
    n = sscanf(s, "%lf", &r1);
    
  } while (n != 1 || r1 < 0); 
  
  printf(" Widerstand R1: %.2lf\n", r1);
  
  
  do {
    printf("Widerstand R2/Ohm: ");
    fgets(s, 100, stdin);
    n = sscanf(s, "%lf", &r2);
    
  } while (n != 1 || r2 < 0);
  
  printf("Widerstand R2: %.2lf\n", r2);
  
  do {
    printf("Eingangsspannung Ue/V: ");
    fgets(s, 100, stdin);
    sscanf(s, "%lf", &ue);
  } while (n != 1);
  
  if (r1 == 0 && r2 == 0) {
    printf("Berechnung nicht möglich!\n");
  } else {
    ua = ue * r2 / (r1 +r2);
    printf("\nAusgangsspannung: %.2lfV\n", ua);
  }
  
  return 0;
  
}

