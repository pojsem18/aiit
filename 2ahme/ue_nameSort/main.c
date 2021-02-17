#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANZAHL 8
#define MAX_ZEICHEN 13

void ausgabe(char txt[MAX_ANZAHL][MAX_ZEICHEN]) {
    for(int i = 0; i < MAX_ANZAHL; i++){
        printf("%s, ", txt[i]);
    }
}

void sortieren(char txt[MAX_ANZAHL][MAX_ZEICHEN]) {
    char tmp[15];

    for(int i = 0; i < MAX_ANZAHL; i++){
        for(int j = 0; j < MAX_ANZAHL - 1 - i; j++){
            if(strcmp(txt[j], txt[j+1]) > 0){
                strcpy(tmp, txt[j]);
                strcpy(txt[j], txt[j+1]);
                strcpy(txt[j+1], tmp);
            }
        }
    }
}
int main() {

    char namelist[8][13] = {"Sebastian", "Matteo", "Oliver", "Jakob", "Elias", "Jan", "Tobias", "Erik"};

    printf("Unsortiert: \n");
    ausgabe(namelist);

    printf("\nSortiert:\n");
    sortieren(namelist);
    ausgabe(namelist);

    return 0;
}
