#include <stdio.h>


int main () {

// Gauss'sche Summenformel
//https://de.wikipedia.org/wiki/Gau%C3%9Fsche_Summenformel
  int s = 0;

  for(int i = 0; i < 100; i++) {
    s = s +i;
  }

 printf("S= %d\n", s);


 // Fibonacci Zahlen

 int i1 =0, i2=1;
while (i2 < 10E10) {

    printf("%d\n", i2);
    int tmp = i1;
    i1=i2;
    i2= i1 + tmp;

}




    return 0;
}
