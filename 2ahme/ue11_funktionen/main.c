#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getInputIntegerValue (char text[]) {
    char s[100];
    int n;
    double rv;

    do {
        printf("%s\n", text);
        fgets(s, 100, stdin);
        n = sscanf(s, "%d", &rv);

    } while (n != 1);

    return rv;
}

double getInputDoubleValue (char text[]) {
    char s[100];
    int n;
    double rv;

    do {
        printf("%s", text);
        fgets(s, 100, stdin);
        n = sscanf(s, "%d", &rv);

    } while (n != 1);

    return rv;
}

int getSelectMenu () {
    char s[100];
    int n;
    double rv;

    do {

        printf("----------------");
        printf("1...Würfel");
        printf("2...Quader");
        printf("3...Kugel");
        printf("4...Programm beenden");

        rv = getInputValue("Auswahl (1-4)");

    } while (rv != 1; rv != 2; rv != 3; rv != 4);

return rv;
}

double calcCube () {

    printf("WŸrfel\n");

    do {
        double l = getInputDoubleValue("LŠnge: ");

    } while (l < 0);

    double V = l * l * l;
    double F = 6 * (l*l);

    printf("Volumen: %.2lf\n", V);
    printf("FlŠche: %.2lf\n", F);

return 0;
}

double clacCuboit () {

    printf("Quader\n");

    do {
        double l = getInputDoubleValue("LŠnge: "):
        double b = getInputDoubleValue(" Breite: ");
        double h = getInputDoubleValue("Hšhe: ");

    } while (h < 0; b < 0; l < 0);

    double V = b * l * h
    double F = 2 * l * b + 2 * l * h +2 * b* h

    printf("Volumen: %.2lf\n", V);
    printf("FlŠche: %.2lf\n", F);

return 0;
}

double calcSphere () {

    printf("Kugel: ");

    do {
        double d = getInputDoubleValue("Durchmesser: ");

    } while (d < 0);

        double r = d / 2;
        double V = (4 / 3) * M_PI *r * r* r;
        double F = 4 * M_PI * r * r;

        printf("Volumen: %.2lf\n", V);
        printf("Fläche: %.2lf\n", F);

return 0;
}

int main() {

    int wahl = getSelectedMenu();

    switch (wahl) {

    case 1: calcCube(); break;
    case 2: calcCuboid(); break;
    case 3: calcSphere();break;
    case 4: return 0;

return 0;

}
