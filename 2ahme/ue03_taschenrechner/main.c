#include <stdio.h>


int main() {

    char s[100]; // Definieren eines character Feldes
    double z1; // Zahl 1
    double z2; // Zahl 2

    double add;
    double sub;
    double mul;
    double div;

    printf("UE03 Taschenrechner\n");
    printf("--------------\n\n");

    printf(" Zahl1: ");
    fgets(s, 100, stdin);
    sscanf(s, "%lf", &z1);

    printf(" Zahl2: ");
    fgets(s, 100, stdin);
    sscanf(s, "%lf", &z2);

    printf("z1=%f z2=%f\n", z1, z2);

    add = z1 + z2;
    sub = z1 - z2;
    mul = z1 * z2;
    div = z1 / z2;

    printf("Ergebnis:\n");
    printf("-------------\n");

    printf(" z1 + z2 = %.4f\n", add);
    printf(" z1 - z2 = %.4f\n", sub);
    printf(" z1 * z2 = %.4f\n", mul);
    printf(" z1 / z2 = %.4f\n", div);


    return 0;
}
