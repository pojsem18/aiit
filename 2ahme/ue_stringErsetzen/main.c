#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strreplace(char *str_source, char *str_search, char *str_replace) {

    char *adresse = 0;
    int element = 0;
    char f[200];
    int l1 = 0;
    int l2 = 0;
    int l3 = 0;


  do {

    adresse = strstr(str_source, str_search);
    element = adresse - str_source;

    strncpy(f, str_source, element);
    strcpy(f + element, str_replace);

    l1 = strlen(str_replace);
    l2 = strlen(str_search);
    l3 = strlen(str_source);

    strncpy(f + (element + l1), str_source + (element + l2), (l3 - element));
    strcpy(str_source, f);

    } while(strstr(str_source, str_search) != NULL);

      l3 = strlen(str_source);
      str_source[l3 + 1] = '\0';
}

void strdelete(char *str_source, char *strc_delete) {

    char *adresse = 0;
    int element = 0;
    char f[200];
    int l1 = 0;
    int l2 = 0;

    l1 = strlen(str_source);
    l2 = strlen(strc_delete);

   do{

    adresse = strstr(str_source, strc_delete);
    element = adresse - str_source;

    strcpy(f, str_source);

    for(int i = 0; i < element + 1; i++) {
      if(i == element){
        for(int j = element - 1; j < l1 + 1; j++)
        strcpy(str_source + j, f + (j + l2 + 1));
        }
      }
    } while(strstr(str_source, strc_delete) != NULL);
}

int main() {

    char beliebigername[200] = "Ich kenne mich nicht gut mit ABC aus, da ich das Programm zum Thema ABC nicht selbstständig gelöst habe!";
    char str_search[] = "ABC";
    char str_replace[] = "Strings";

    printf("\nAusgangssatz:\n%s\n", beliebigername);

    strreplace(beliebigername, str_search, str_replace);
    printf("\nAufgabe 1:\n%s\n", beliebigername);

    strdelete(beliebigername, "nicht");
    printf("\nAufgabe 2:\n%s\n", beliebigername);

    return 0;
}
