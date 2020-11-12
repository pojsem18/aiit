#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WINDOW_SIZE 100
#define MDATA_MAX_SIZE 1000

double getSinusWithNoise(double feld[], int lengh, int lengh_period, double amplitude, double offset, double amplitude_noise) {
    int i;
    
      for (i=0; i<lengh; i++) 
        feld[i] = amplitude * sin(((2 * M_PI) / lengh_period * i) + rand() % 100 * amplitude_noise);
    return 0;
}

double removeOffset(double feld[], int lengh) {
    double offset = 0;
    double summe = 0;
    
    for(int i=0; i<lengh; i++)
        summe += feld[i];
    
    offset = summe/lengh;
    
    for(int i=0; i<lengh; i++)
    {
        feld[i] -= offset;
    }
    return offset;
}

calcMovingAveraging(double feld[], int lengh) {
    int n = 10;
    int sum = 0;
    int i;
    int data;

    for(i = 0; i < lengh; i++) {
        if (i <= 989) {

            for(data = 0; data < n; data++) {
                sum = sum + feld[i + data];
            }
            feld[i] = sum/n;

        } else {
            break;
        }
        if( i = 990) {
            for(data = 0; data < 9; data++) {
                sum = sum + feld[i + data];
            }

        }
    }
}

int main () {
    double mdata[MDATA_MAX_SIZE];
    double offset = 0.0;
    
    getSinusWithNoise(mdata, MDATA_MAX_SIZE, 100, 2.0, 1.0, 0.0);
    offset = removeOffset(mdata, MDATA_MAX_SIZE);
    
    if(offset == 1.0)
        printf("HuHu\n");
    else
        printf("Offset-Differenz %3.2f", 1.0 - offset);
    return 0;

}

