#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANZAHL_TOUREN 100

struct datum {

    int tag;
    int monat;
    int jahr;
};

struct daten{

    char name[50];
    int laenge;
    int anzahl;
    int hoehe;

};

struct radtour {

    struct daten datentour;
    struct datum datumtour;
};

struct radtour2 {

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

        if(s[0] == '<'){
            return 0;
        }

        ok = sscanf(s, "%d", zahl);
        ok &=(*zahl >= ug) && (*zahl <= og);

    } while(!ok);

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

int eingabedaten(struct daten *datentour, int anzahl) {

    char nt[100];
    int l = 0;
    int f = 0;
    int hm = 0;

    printf("\n\n\tBitte tragen Sie nun die Daten Ihrer Tour ein: \n");

    if(eingabeString("\nName der Tour: ", nt, 100)){
        if(eingabeZahl("\nLänge in km: ", 0, 9999, &l)){
            if(eingabeZahl("\nAnzahl der Fahrten: ", 0, 9999, &f)){
                if(eingabeZahl("\nHöhenmeter der Strecke: ", 0, 9999, &hm)){

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

int neuetour(struct radtour *tour, int *anzahl, int anzahl2) {

   if(eingabedaten(&tour[*anzahl].datentour, anzahl2)){
      if(eingabedatum(&tour[*anzahl].datumtour)){

     *anzahl = *anzahl + 1;
     return 1;
    }
  }
  return 0;
}

void ausgabeTour(struct radtour tour[], int anzahl) {

    printf("\nIhre Radtouren\n");
    printf("============================================================================");
    for(int i = 0; i < anzahl; i++){
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

 for(int i = 0; i < anzahl -1; i++){
        for(int j = 0; j < anzahl -1 -i; j++){
          if(strcmp(radtouren[j].datentour.name, radtouren[j + 1].datentour.name) > 0){

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

        if(strcmp(tmp, tmp2) == 0){
            printf("\nErgebnis: %s", tour[i].datentour.name);
            merker ++;
            i++;
            merker2 = i;

        } else {
        i++;
        }

  } while(i != anzahl);


  if(merker > 1){
    printf("\nMehrere Ergebnisse, bitte genauer!\n");
    return -1;
  }

  else if(merker == 0){
    printf("\nKein Ergebniss, bitte wiederholen!\n");
    return -1;
  }

  else if(merker == 1){
      printf("\n\nBitte wählen Sie: ");
      printf("\n====================");
      printf("\nJ für bestätigen ");
      printf("\nN für abbrechen ");

      eingabeString("\n\nWahl:", tmp3, 5);

      if (strcmp(tmp3, "J") == 0){
       return merker2;
        }


      else if (strcmp(tmp3, "N") == 0){
          return 0;

      }
  }
}

void durchschnitt(struct radtour *tour, int anzahl, double *durchschnitt) {

    int ergebnis = 0;

    for(int i = 0; i < anzahl; i++){
        ergebnis = ergebnis + tour[i].datentour.laenge;
    }

    *durchschnitt = ergebnis/anzahl;

}

int main() {

   struct radtour radtouren[MAX_ANZAHL_TOUREN]= {

        {{"Radtour 1", 1000, 6, 350}, {11, 11, 2003}} ,
        {{"Aadtour 2", 1500, 5, 567}, {24, 04, 2020}} ,
        {{"Uadtour 3", 1000, 4, 350}, {1, 11, 2003}} ,
        {{"Oadtour 4", 1600, 3, 567}, {23, 04, 2020}} ,
        {{"Eadtour 5", 1500, 2, 567}, {23, 04, 2020}} ,
        {{"Iadtour 6", 1500, 1, 567}, {23, 04, 2020}} ,

    };

  struct radtour radtouren2[MAX_ANZAHL_TOUREN]= {
    };
    int tourenanzahl = 6;
    int n = 0;
    int a = 0;
    double durchsch = 0;
    char tmp[100];
    int tmp2 = 0;
    int merker = 0;

    do{


    printf("\n\nMenue: ");
    printf("\n1.........Tour hinzufügen:");
    printf("\n2.........Touren ausgeben:");
    printf("\n3............Tour löschen:");
    printf("\n4.................Beenden:");

    eingabeZahl("\n\nMenue-Auswahl: ", 1, 4, &a);

  switch(a) {

 case 1:
   neuetour(radtouren, &tourenanzahl, tourenanzahl);
      ausgabeTour(radtouren, tourenanzahl);

    break;

 case 2:

      sortieren(radtouren, radtouren2, tourenanzahl);
      durchschnitt(radtouren, tourenanzahl, &durchsch);
      ausgabeTour(radtouren, tourenanzahl);
      printf("\n\n Durchschnittliche Länge Ihrer Touren: %.3lf", durchsch);

    break;

 case 3:

    do{
    n = suchen(radtouren, tourenanzahl);
    } while(n == (-1));

      if(n == 0){
      break;
      }

    for(int i = 0; i < tourenanzahl; i++, n++){
      radtouren[n - 1] = radtouren[n];
 }
    tourenanzahl = tourenanzahl - 1;
    ausgabeTour(radtouren, tourenanzahl);
    break;

  }
    } while(a != 4);

printf("Programm beendet!");
return 0;
}
