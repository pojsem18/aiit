#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getInputDoubleValue (char text[]) {
    char s[100];
    int n;
    double rv;

    do {
            printf("%s\n", text);
            fgets(s, 100, stdin);
            n = sscanf(s, "%lf", &rv);

            } while (n != 1);

    return rv;

}

double getPositiveDoubleInputValue (char text[]}) {

    double f1;

    do {
        f1 = getInputDoubleValue (text);

    } while (f1 < 0);

    return f1;
}

double calcForce (double fx, double fy) {

    double fres = sqrt(fx * fx + fy * fy);

    return fres;
}


int main() {


    double fx = getPositiveDoubleInputValue("Fx: ");
    double fy = getPositiveDoubleInputValue("Fy: ");
    double ergebnis = calcForce(fx, fy);

    printf("Ergebnis: %.2lf\n", ergebnis);

    return 0;
}
