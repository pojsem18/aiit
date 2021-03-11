#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getOP(char text){
    int op = 0;

    if(text == '+'){
            op = 1;

    } else if(text == '-'){
            op = 2;

    } else if(text == '*'){
            op = 3;

    } else if(text == '/'){
            op = 4;
    }

    return op;

}

int getLenghOfNumber(char *text){

    //double f[10] = {10, 111, 12, 12.34};
    int merker = 0;
    int laenge = 0;

    for(int i= 0; (merker = 0); i++){
        if(text[i] >= 0 || text[i] <= 9 || text[i] == '.'){
            laenge++;
        } else {
            merker = 1;
        }
    }
    return laenge;
}

void calc(double num1, double num2, int op, double *result){
    if(op == 1){
        *result = num1 + num2;
    } else if(op == 2){
        *result = num1 - num2;
    } else if(op == 3){
        *result = num1 * num2;
    } else if(op == 4){
        *result = num1 / num2;
    }
}

int parseText(char text[], int length, double *result){

double num1 = 0;
double num2 = 0;
int offset = 0;
int op = 0;
int bracket_open = 0;

    if(*text == '\0'){
        return -1;
    } else {
        op = getOP(text[offset]);
    }

    if(text[offset] == '('){
        bracket_open = 1;
        offset++;
    }

    if(text[offset] == '('){
        offset = offset + parseText(text + offset, length - offset, result);
        return offset;
    }

    if(op == 0){
        if(sscanf(text+offset, "%lf", &num1) != 1){
        return -1;
        }
        offset = offset + getLenghOfNumber(text+offset);
        op = getOP(text[offset]);
    } else {
        num1 = *result;
    }

    if(op == 0){
        return -1;
    }

    offset++;

    if(text[offset] == '('){
        offset = offset + parseText(text+offset, length - offset, &num2);
    } else {
        if(sscanf(text+offset, "%lf", &num2) == 1){
            offset = offset + getLenghOfNumber(text + offset);
        } else {
            return -1;
        }
    }

    if((op < 3) && (text[offset] == '*' || text[offset] == '/') && (text[offset]=! ')')){
        offset = offset + parseText(text + offset, length - offset, &num2);
        calc(num1, num2, op, result);
    } else {
        calc(num1, num2, op, result);
    }

    if(text[offset] == ')'){
        if(bracket_open == 0){
            return offset;
        }
        offset = offset + 1;

        if(*(text - 1) == '*' || *(text - 1) == '/'){
        return offset;
        }

    }

    if(text[offset] == ')'){
        return offset;
    }

    return offset + parseText(text + offset, length - offset, result);

}


int main (int argc, char* argv[]) {
    double merker = 1;
    double fzahl[100];
    double fzahlfalsch[100];
    double min = 0;
    double max = 0;
    int n = 0;
    int x = 0;
    double result = 0;

    int zaehler = 0;
    for(int j = 0; j < argc; j++){

      n =  sscanf( argv[j], "%lf", &fzahl[j]);
      if (n == 1){
      zaehler++;
        if (zaehler > 10){
          return 1;
      }
    }
  }

    for(int y = argc - zaehler; y < argc; y++){
      x = sscanf(argv[y], "%lf", &fzahlfalsch[y]);
      if(x != 1){
        printf("\n\tBuchstabe als Eingabe nicht erlaubt!!!\n\n");
        return 1;
      }
    }


    for(int k = 0; k < (argc-zaehler); k++){

      if (strcasecmp("-sum", argv[k+1]) == 0){
        merker = 0;
        for(int l = 0; l < argc; l++){
          merker = merker + fzahl[l];
        }
      printf("\nSumme:\t %lf\n", merker);
      }

      else if (strcasecmp("-avg", argv[k + 1]) == 0){
        merker = 0;
        for(int l = 0; l < argc; l++){
          merker = merker + fzahl[l];
        }
      merker = merker / zaehler;
      printf("\nDurchschnitt:\t %lf\n", merker);
      }

      else if (strcasecmp("-min", argv[k + 1]) == 0){
      merker = 0;
      min = fzahl[argc - zaehler];
        for(int l = argc - zaehler; l < argc; l++){
          if (fzahl[l] < min) {
            min = fzahl[l];
        }
      }
      printf("\nMinimal:\t %lf\n", min);
    }

      else if (strcasecmp("-max", argv[k + 1]) == 0){
      merker = 0;
      max = fzahl[0];
        for(int l = 0; l < argc; l++){
          if (fzahl[l] > max) {
            max = fzahl[l];
        }
      }
      printf("\nMaximal:\t %lf\n", max);
    }
  }
  for(int m = 0; m < argc; m++) {
        if (strcasecmp("-calc", argv[m + 1]) == 0){
            parseText(argv[2], strlen(argv[2]), &result);
            printf("%lf", result);
        }
    }

  return 0;
}
