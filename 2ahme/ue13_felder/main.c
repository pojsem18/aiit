#include <stdio.h>
#include <stdlib.h>

double *print1DimFeld(double feld[], int anzahl) {
    printf("print1DimFeld:\n");
    // for (int i = 0; i < sizeof(feld) / sizeof(double); i++) {
    // sizeof(feld)     => 40?
    // sizeof(feld)     => 8
    // sizeof(double)   => 8

    for (int i = 0; i < anzahl; i++) {
        printf("feld[%d] %p => %f\n", i, &feld[i], feld[i]);
    }
    printf("\n\n");
    return &feld[0];
}

void eindimensionalesFeld() {

    char text1[] = "Hi"; // -128..127, ASCII 0..127 <-> Zeichen
    printf("%s\n", text1);
    printf("text1: sizeof(text1) = %d Bytes\n", (int)sizeof(text1));
    for (int i = 0; i < sizeof(text1); i++) {
        printf(" %d", (int)text1[i]);
    }
    // 1.Feldelement -> Index 0 !
    // 2.Feldelement -> Index 1
    printf("\n\n");

    char text2[] = { 'H', 'i', 0};
    printf("text2: %s\n", text2);
    printf("sizeof(text2) = %d Bytes\n", (int)sizeof(text2));
    for (int i =  0; i < sizeof(text2); i++) {
        printf(" %d", (int)text2[i]);
    }
    printf("\n\n");

    char text3[10] = { 'H', 'i', 0};
    printf("text3: %s\n", text3);
    printf("text3: %s\n", text3);
    printf("sizeof(text3) = %d Bytes\n", (int)sizeof(text3));
    for (int i = 0; i < sizeof(text3); i++) {
        printf(" %d", (int)text3[i]);
    }
    printf("\n\n");

    double df1[] = { 1.0, 2.0, 3.0};
    printf("sizeof(df1) = %d Bytes\n", (int)sizeof(df1));
    for (int i = 0; i < sizeof(df1) / sizeof(double); i++) {
        printf(" %f", df1[i]);
    }
    printf("\n\n");

    double df2[5] = { 1.0, 2.0, 3.0, 4.0 };
    printf("sizeof(df2) = %d Bytes\n", (int)sizeof(df2));
    for (int i = 0; i < sizeof(df2) / sizeof(df2[0]); i++) {
        printf(" %f", df2[i]);
    }
    printf("\n\n");

    // ----------------------------------------------

    // text1 = "Ha";
    // rext1 = { 'H' , 'a', '0' };
    text1[0] = 'H';
    text1[1] = 'a';
    text1[2] = 0;

    printf("%s\n", text1);

    // ----------------------------------------------

    double *df3 = print1DimFeld(df2, sizeof(df2) / sizeof(double));
    printf("sizeof(df3) = %d Bytes\n", (int)sizeof(df3));
    for (int i = 0; i < 5; i++) {
        printf(" %f", df3[i]);
    }
    printf("\n\n");
}

void print2DimFeld(double f[][3], int anzahl) {
    printf("print2DimFeld:\n");
    for (int i = 0; i < anzahl; i++) {
        for (int j = 0; j < 3; j++) {
            printf("feld[%d][%d] %p => %f\n",
                   i, j, &f[i][j], f[i][j]);
        }
    }
    printf("\n\n");
}

void zweidimensionaleFelder() {
    // xx-Achse & y-Achse
    // 4 * 3 = 12 Elemente -> 12 * 8 = 96
    double f[4][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };

    printf("\n\n2 Dimensionen:\n");
    printf("sizeof(f) = %d Bytes\n", (int)sizeof(f));
    printf("f[0][0] %p => %f\n", &f[0][0], f[0][0]);
    printf("f[0][1] %p => %f\n", &f[0][1], f[0][1]);
    printf("f[0][2] %p => %f\n", &f[0][2], f[0][2]);
    printf("f[1][0] %p => %f\n", &f[1][0], f[1][0]);
    printf("f[1][1] %p => %f\n", &f[1][1], f[1][1]);
    printf("f[1][2] %p => %f\n", &f[1][2], f[1][2]);
    printf("f[2][0] %p => %f\n", &f[2][0], f[2][0]);
    printf("f[2][1] %p => %f\n", &f[2][1], f[2][1]);
    printf("f[2][2] %p => %f\n", &f[2][2], f[2][2]);
    printf("f[3][0] %p => %f\n", &f[3][0], f[3][0]);
    printf("f[3][1] %p => %f\n", &f[3][1], f[3][1]);
    printf("f[3][2] %p => %f\n", &f[3][2], f[3][2]);

    // f = { { 1, 2, 3 } }; // nicht moeglich, nur bei Initialisierung erlaubt

    f[2][0] = 7;
    f[2][1] = 8;
    f[2][2] = 9;
    f[2][3] = 10;

    print2DimFeld(f, 4);
}

void print3DimFeld(double x[][3][4], int anzahl) {
    printf("print3DimFeld:\n");
    for (int i = 0; i < anzahl; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                printf("x[%d][%d][%d] %p => %f\n",
                       i, j, k, &x[i][j][k], x[i][j][k]);
            }
        }
    }
    printf("\n\n");
}

void dreidimensionalesFeld() {

    double f[2][3][4] =
        {
            {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 }
            }, {
                { 13, 14, 15, 16 },
                { 17, 18, 19, 20 },
                { 21, 22, 23, 24 }
            }
        };

    printf("\n\n3 Dimensionen:\n");
    printf("sizeof(f) = %d Bytes\n", (int)sizeof(f));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                printf("feld[%d][%d] %p => %f\n",
                   i, j, k, &f[i][j][k], f[i][j][k]);
            }
        }
    }
    printf("\n\n");
    
    print3DimFeld(f, 2);
    
}

int main() {

    //eindimensionalesFeld();
    zweidimensionaleFelder();
    return 0;
}