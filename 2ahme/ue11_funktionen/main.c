#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getInputIntegerValue (char text[]) {
    char s[100];
    int n;
    int rv;

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
        printf("Auswahl (1-4): ");
        fgets(s, 100, stdin);
        sscanf(s, "%d", &rv);

    } while (rv < 1 || rv > 4);

    return rv;
}

void calcCube () {
    double l;

    printf("Wuerfel\n");

    do {
        l = getInputDoubleValue("Loenge: ");

    } while (l < 0);

    double v = l * l * l;
    double f = 6 * (l*l);

    printf("Volumen: %.2lf\n", v);
    printf("Flaeche: %.2lf\n", f);

}

void clacCuboid () {
    double l;
    double b;
    double h;
    double f;
    double v;

    printf("Quader\n");

    do{
        l = getInputDoubleValue("Laenge: ");

    } while (laenge < 0);

    do{
        b = getInputDoubleValue("Breite: ");

    } while (breite < 0);

    do{
        h = getInputDoubleValue("Hoehe: ");
    } while (hoehe < 0);

    v = b * l * h
    f = 2 * l * b + 2 * l * h +2 * b* h

    printf("Volumen: %.2lf\n", v);
    printf("FlŠche: %.2lf\n", f);

}

void calcSphere () {
    double d;
    double f;
    double v;

    printf("Kugel: ");

    do {
        d = getInputDoubleValue("Durchmesser: ");

    } while (d < 0);

        double v = (4 / 3) * M_PI * ((d / 2) * (d / 2) * (d / 2));
        double F = 4 * M_PI * r * r;

        printf("Volumen: %.2lf\n", v);
        printf("Flaeche: %.2lf\n", f);

}

int main() {

    printf("UE11 - Koerperberechnung mit Menuefunktion\n\n");
    while (1 == 1) {

            printf("\n---------------------\n");
            int auswahl1 = getSelectMenu();

            switch (auswahl1){
                case 1: {
                    calcCube();
                    break;

                } case 2: {
                    calcCuboid();
                    break;

                } case 3: {
                    calcSphere();
                    break;

                } case 4: {
                    return 0;

                }
            }
    }

}
