#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_ANZAHL_TOUREN 100

struct datum {

    int tag;
    int monat;
    int jahr;
};

struct daten {

    char name[50];
    int laenge;
    int anzahl;
    int hoehe;

};

struct radtour {

    struct daten datentour;
    struct datum datumtour;
};

int eingabeZahl(char* txt, int ug, int og, int *zahl) {
    int ok = 0;
    char s[100];

    do{
        if(ok){
          printf(" Bitte geben sie eine zahl zwischen %d und %d ein", ug, og);
        }
        printf("%s", txt);
        fgets(s, sizeof(s), stdin);
        fflush(stdin);

        if(s[0] == '<') {
            return 0;
        }

        ok = sscanf(s, "%d", zahl);
        ok &=(*zahl >= ug) && (*zahl <= og);

    }while(!ok);

    return 1;
}

int eingabeString(char *txt, char *texteingabe, int len) {
    int ok = 1;
    char s[100];

    do{
         if(!ok){
          printf(" Ihre Eingabe ist zu lang. Bitte geben Sie einen Text mit maximal %d Zeichen ein \n", len);
        }
        printf("%s", txt);
        fgets(s, len, stdin);
        fflush(stdin);

        if( s[0] == '<'){
            return 0;
        }
        ok = (strlen(s) > 0) && (strlen(s) < (len-1));
    }while(!ok);
    strcpy(texteingabe, s);
    texteingabe[strlen(s)-1] = '\0';
    return 1;
}

int eingabedatum(struct datum *datumtour) {
    int tag = 0;
    int monat = 0;
    int jahr = 0;

    printf("\n\n\tBitte geben Sie das Datum der Tour ein: \n");

    if(eingabeZahl("\nTag: ", 1, 31, &tag)){
        if(eingabeZahl("\nMonat: ", 1, 12, &monat)){
            if(eingabeZahl("\nJahr: ", 1, 2021, &jahr)){

      datumtour->tag = tag;
      datumtour->monat = monat;
      datumtour->jahr = jahr;

      return 1;
      }
    }
  }
  return 0;
}

int eingabedaten(struct daten *datentour) {
    char nt[100];
    int l = 0;
    int f = 0;
    int hm = 0;

    printf("\n\n\tBitte tragen Sie nun die Daten Ihrer Tour ein: \n");

    if(eingabeString("\nName der Tour: ", nt, 100)) {
        if(eingabeZahl("\nLaenge in km: ", 0, 9999, &l)) {
            if(eingabeZahl("\nAnzahl der Fahrten: ", 0, 9999, &f)) {
                if(eingabeZahl("\nHoehenmeter der Strecke: ", 0, 9999, &hm)) {

        strcpy(datentour->name, nt);
        datentour->laenge = l;
        datentour->anzahl = f;
        datentour->hoehe = hm;

        return 1;
        }
      }
    }
  }
  return 0;
}

int neuetour(struct radtour **tour, int *anzahl) {

    int merker = 0;

    do{

    merker = 0;
    *tour = realloc(*tour, sizeof(struct radtour) * (*anzahl + 1));
    if(eingabedaten(&((*tour + *anzahl) -> datentour))) {
      for(int i = 0; i < *anzahl; i++) {
        if(strcmp((*tour + *anzahl) -> datentour.name, (*tour + i) -> datentour.name) == 0){
          printf("\n\n Tour existiert bereits, bitte wŠhlen Sie einen anderen Namen!");
            merker++;
          }
        }
      }
    }while(merker > 0);
      if(eingabedatum(&((*tour + *anzahl) -> datumtour))){

      *anzahl = *anzahl + 1;
     return 1;
    }
  return 0;
}

void ausgabeTouren(struct radtour tour[], int anzahl) {

    printf("\nIhre Radtouren\n");
    printf("===================");
    for(int i = 0; i < anzahl; i++) {
        printf("\n%d. \t%s %d %d %d  | %d.%d.%d", i+1,
               tour[i].datentour.name,
               tour[i].datentour.laenge,
               tour[i].datentour.anzahl,
               tour[i].datentour.hoehe,

               tour[i].datumtour.tag,
               tour[i].datumtour.monat,
               tour[i].datumtour.jahr);
    }
}

void sortieren(struct radtour *radtouren, struct radtour *radtouren2, int anzahl) {

    for(int i = 0; i < anzahl -1; i++) {
        for(int j = 0; j < anzahl -1 -i; j++) {
          if(strcmp(radtouren[j].datentour.name, radtouren[j+1].datentour.name) > 0) {
            radtouren2[0] = radtouren[j];
            radtouren[j] = radtouren[j + 1];
            radtouren[j + 1] = radtouren2[0];
      }
    }
  }
}


int suchen(struct radtour *tour, int anzahl) {

    char tmp[100];
    char tmp2[100];
    char tmp3[5];
    int merker = 0;
    int merker2 = 0;
    int i = 0;

    eingabeString("\nSuche: ", tmp, 100);

    do{

        strncpy(tmp2, tour[i].datentour.name, strlen(tmp));

        if(strcmp(tmp, tmp2) == 0) {
        printf("\nErgebnis: %s", tour[i].datentour.name);
        merker ++;
        i++;
        merker2 = i;

    } else {
    i++;
    }

    } while(i != anzahl);


    if(merker > 1) {
    printf("\nMehrere Ergebnisse, bitte genauer!\n");
    return -1;
    }

    else if(merker == 0) {
    printf("\nKein Ergebniss, bitte wiederholen!\n");
    return -1;
    }

    else if(merker == 1){
      printf("\n\nBitte waehlen Sie: ");
      printf("\n====================");
      printf("\nJ fuer bestaetigen ");
      printf("\nN fuer abbrechen ");

      eingabeString("\n\nWahl:", tmp3, 5);

      if (strcmp(tmp3, "J") == 0) {
       return merker2;
        }


      else if (strcmp(tmp3, "N") == 0) {
          return 0;

      }
  }
  return 1;
}


void durchschnitt(struct radtour *tour, int anzahl, double *durchschnitt) {

    int ergebnis = 0;

    for(int i = 0; i < anzahl; i++) {
    ergebnis = ergebnis + tour[i].datentour.laenge;
    }

    *durchschnitt = ergebnis/anzahl;
}

void ladenDerRadTouren(struct radtour *tour, int anzahl) {
    FILE *f = fopen("radtour.txt", "w");
    if(f == NULL) {
        printf("Fehler aufgetreten (Fehler %d)\n", errno);
        printf("-> %s\n", strerror(errno));
    }

    if (fclose(f) == EOF) {
        printf("Datei konnte nicht geschlossen werden");
    }
}

int speichernDerRadTouren(struct radtour *tour, int anzahl) {
    FILE *f;
    int rv;

    f = fopen("radtour.txt", "w");
    if(f == NULL) {
        printf("Fehler aufgetreten (Fehler %d)\n", errno);
        printf("-> %s\n", strerror(errno));
    }
    fprintf(f, "Name\t Laegnge\t Anzahl\t Hoehenmeter\t Datum\t");
    for(int i = 0; i < anzahl; i++) {
               rv = fprintf(f, "%d. \t%s %d %d %d\n  | %d.%d.%d\n", i+1,
               tour[i].datentour.name,
               tour[i].datentour.laenge,
               tour[i].datentour.anzahl,
               tour[i].datentour.hoehe,

               tour[i].datumtour.tag,
               tour[i].datumtour.monat,
               tour[i].datumtour.jahr);
    }

    if (rv == EOF)
        printf("Fehler");
    if (fclose(f) == EOF) {
        printf("Datei konnte nicht geschlossen werden");
    }

    f = fopen("radtour.txt", "r");

    if (f == NULL) {
        return 0;
    }
    return rv;

}


int main() {

    struct radtour *radtouren = NULL;

    radtouren = malloc(sizeof(struct radtour));

    struct radtour *radtouren2 = NULL;

    radtouren2 = malloc(sizeof(struct radtour));

    int tourenanzahl = 0;
    int n = 0;
    int a = 0;
    double durchsch = 0;

    do{

        printf("\n\nMenue: ");
        printf("\n1.........Tour hinzufuegen");
        printf("\n2.........Touren ausgeben");
        printf("\n3.........Tour loeschen");
        printf("\n4.........Speichern der Touren");
        printf("\n5.........Laden der Touren");
        printf("\n6.........Beenden");

        eingabeZahl("\n\nMenue-Auswahl: ", 1, 6, &a);

    switch(a) {

    case 1:
        neuetour(&radtouren, &tourenanzahl);
        ausgabeTouren(radtouren, tourenanzahl);

    break;

    case 2:

      sortieren(radtouren, radtouren2, tourenanzahl);
      durchschnitt(radtouren, tourenanzahl, &durchsch);
      ausgabeTouren(radtouren, tourenanzahl);
      printf("\n\n Durchschnittliche Laenge Ihrer Touren: %.3lf", durchsch);

    break;

    case 3:

    do{
        n = suchen(radtouren, tourenanzahl);
    } while(n == (-1));

      if(n == 0) {
      break;
      }

    for(int i = 0; i < tourenanzahl; i++, n++) {
      radtouren[n - 1] = radtouren[n];
    }
    tourenanzahl = tourenanzahl - 1;
    radtouren = realloc(radtouren, sizeof(struct radtour) * tourenanzahl);
    ausgabeTouren(radtouren, tourenanzahl);
    break;

    case 4:

    speichernDerRadTouren(radtouren, tourenanzahl);
    break;

    case 5:

    ladenDerRadTouren(radtouren, tourenanzahl);
    break;

  }
    } while(a != 6);

    printf("Programm beendet!");

    free(radtouren);
    free(radtouren2);
    return 0;
}
