#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILE_ERROR 2
#define NO_ERROR 0
#define MDATA_MAX_SIZE 2000
#define MOVINGAVERAGING_WINDOW_SIZE 10
#define ECGDATA_SAMPLE_RATE 360 //Hz
#define FILENAME_ECG "mdata.csv"
#define FILENAME1 "ekg1.csv"
#define FILENAME2 "ekg2.csv"
#define FILENAME3 "ekg3.csv"

int genSinusWithNoise(double f[], int length, double length_period, double amplitude, double offset, 
                      double amplitude_noise) {
    
    for (int i = 0; i < length; i++) 
        
        f[i] = amplitude * sin((2 * M_PI) / length_period * i) + offset +(rand() % 100) * amplitude_noise / 100;
}

int readDataFromFile(char *filepath, double *mdata, int max_length, int *length) {
    
  int idummy = 0;
  double ddummy = 0;
  
  FILE* f = fopen(filepath, "r");
  if (f==NULL)
    return FILE_ERROR;
  
  *length = 0;
  while (!feof(f) && (*length < max_length))   
  {
    char s[100];
    if (fgets(s,100,f) == NULL)   
      break;
    
    if (sscanf(s,"%d;%lf;%lf", &idummy, &mdata[*length], &ddummy) == 3)
        (*length)++;
    }
  
  fclose(f);
  return NO_ERROR;
}

int writeData2File(char *filepath, double data[], int length)
{
  FILE* f = fopen(filepath, "w");
  if (f == NULL)
    return FILE_ERROR;
  for (int i=0;i<length;i++)
    fprintf(f,
      "%.3f\n", data[i]
    );
  fclose(f);
  return NO_ERROR;
}

double removeOffset(double f[], int length) {
    
    double offset = 0.0;
    double summe = 0.0;
    
    for(int i = 0; i < length; i++)
        summe += f[i];
    
    offset = summe / length;
    
    for(int i = 0; i < length; i++) {
        f[i] -= offset;
    }
    return offset;
}

void calcMovingAveraging(double f[], int length) {
    
    double sum=0;
    double avg=0;
  
    for(int i = 0; i < 10; i++) {
      sum += f[i];
  }
  
  for(int i = 0; i < (length - 10); i++) {
    avg = sum / 10;
    sum += f[i + 10];
    sum = sum - f[i];
    f[i] = avg;
  }
}

void diffSignal(double f[], int length) {
    
    for(int i = 0; i < length; i++) {
    f[i] = f[i+1] - f[1];
    }
}

double normalizeSignal(double f[], int length) {
    double max;
    
    for(int i = 0; i < length; i++) {
        
        if(abs(f[i]) > max) {
            
            max = abs(f[i]);
        }
    }
    for(int i = 0; i < length; i++) {
        
        f[i] = f[i] / max;
    }
    return max;
}

double getMaxValue(double f[], int length, int *x) {
  
  double groessterWert = 0;
  
  for (int i = 0; i < length; i++) {
    
    if (abs(f[i]) > groessterWert) {
      
      groessterWert = abs(f[i]);
      *x = i;
    }
  }
  return 0;
}

int findRPeak(double f_2diff[], double f_orig[], int length, double rpeak[], int rpeak_length) {

    int nz_legnth = 0;
    int qrs_complex_start = -1, qrs_complex_end = -1;
    int rpeak_i = 0;
    int x = 0;

   //Abtastrate: ECGDATA_SAMPLE_RATE = 360 Hz

    //Abtastdauer: 1/360 s

    //Wieviele Feldelemente sind in 0.6 s enthalten?

    //0.6/(1/360) = 0.6 s * Abtastfrequenz

    const int nsep = 0.6 * ECGDATA_SAMPLE_RATE;

    //1.) Wir suchen den Startpunkt des ersten QRS-Komplexe -> Q-Wert

    for( int i = 0; i < length; ++i) {

        if (f_2diff[i] != 0) {

            qrs_complex_start = i;
            qrs_complex_end = i;
            break;
        }
    }

    //2.) Suche die Start und Endwerte aller restlichen QRS-suchen und zwischen den Start-
    // und Endpunkten wird das Maximum und somit die R-Zacke bestimmt!

    for( int i = qrs_complex_start + 1; i < length; ++i) {

        if (f_2diff[i] != 0) { //Start oder Ende eines QRS-Komplex detektiert?

            if ( (i - qrs_complex_end) >= nsep ) { //neuen QRS-Komplex gefunden!

                if (rpeak_i < rpeak_length) {
                  
                   getMaxValue(&f_orig[qrs_complex_start], qrs_complex_end - qrs_complex_start, &x);
                   rpeak[rpeak_i] = x + qrs_complex_start;

                    //printf("%d.): qrs-start: %d, qrs-length: %d, r-peak: %1.f\n", rpeak_i, qrs_complex_start, qrs_complex_end - qrs_complex_start, rpeak[rpeak_i]);

                    ++rpeak_i;
                    qrs_complex_start = i;
                }
                else {
                    break;
                }
            }
            qrs_complex_end = i;
        }
    }
    /*
     * continue; 
    if (letztes Feldelement - qrs_complex_start > 2*letzterDetektierterHerzschlag)
        ; //-> Stromschlag
    */
    if (qrs_complex_end > qrs_complex_start) {

        getMaxValue(&f_orig[qrs_complex_start], qrs_complex_end - qrs_complex_start, &x);
        rpeak[rpeak_i] = x + qrs_complex_start;
        //printf("%d.): qrs-start: %d, qrs-length: %d, r-peak: %1.f\n", rpeak_i, qrs_complex_start, qrs_complex_end - qrs_complex_start, rpeak[rpeak_i]);
        ++rpeak_i;
    }
    return rpeak_i;
}

void printHeartRate(double rpeak[], int length, double f_rpm[]) {
  
  int anzahl;
  
  for(int i = 0; i < (length - 1); i++) {
    anzahl = rpeak[i + 1] - rpeak[i];
    f_rpm[i] = (ECGDATA_SAMPLE_RATE * 60) /anzahl;
  }
    
}

void printSortHeartRate(double rpeak[], int length){
  
  double f_rpm[length - 1];
  int i, j, tmp;
  
  printHeartRate(rpeak, length, f_rpm);

  for (i = 1; i < length; i++) {
    for (j = 0; j < length - 1 ; j++)  {
      if (f_rpm[j] > f_rpm[j + 1]) {
          tmp = f_rpm[j];
          f_rpm[j] = f_rpm[j + 1];
          f_rpm[j + 1] = tmp;
      }
    }
    printf("\t%.2lf\n", f_rpm[i]);
  }
}
  
int changeFeld(double f[], double f_orgin[], int length) {
  
  for (int i = 0; i < length; i++) {
    f_orgin[i] = f[i];
  }
  return 0;
}

int main () {
    double mdata[MDATA_MAX_SIZE];
    int mdata_length = 0;
    double f[999];
    double f_orig[999];
    double rpeak[10];
    int rpeak_length = 10; 
    int length = 999;
    
    readDataFromFile(FILENAME_ECG, mdata, MDATA_MAX_SIZE, &mdata_length);
    writeData2File(FILENAME1, mdata, MDATA_MAX_SIZE);
    //genSinusWithNoise(mdata, sizeof(mdata)/sizeof(double), 100, 2, 1, 0.5);
    //genSinusWithNoise(mdata, sizeof(mdata)/sizeof(double), 100, 2, 1, 0.0);
    removeOffset(mdata, MDATA_MAX_SIZE);
    calcMovingAveraging(mdata, MDATA_MAX_SIZE);
    changeFeld(f, f_orig, length);
    writeData2File(FILENAME2, mdata, MDATA_MAX_SIZE);
    
    diffSignal(mdata, MDATA_MAX_SIZE);
    normalizeSignal(mdata, MDATA_MAX_SIZE);
    writeData2File(FILENAME3, mdata, MDATA_MAX_SIZE);
    double rpeak_i = findRPeak(f, f_orig, length, rpeak, rpeak_length); 
    printSortHeartRate(rpeak, rpeak_i);
    
    system("python3 plotdata.py " FILENAME1 " " FILENAME2 " " FILENAME3 );
    
    return 0;
}