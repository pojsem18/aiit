#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILE_ERROR 2
#define NO_ERROR 0
#define MDATA_MAX_SIZE 2000
#define MOVINGAVERAGING_WINDOW_SIZE 10
#define ECGDATA_SAMPLE_RATE 360 //Hz
#define FILENAME_ECG "mdata.csv"
#define FILENAME_ORIG "mdata_orig.csv"
#define FILENAME_FILT "mdata_filt.csv"
#define FILENAME_DIFF1 "mdata_diff1.csv"

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

int main () {
    double mdata[MDATA_MAX_SIZE];
    int mdata_length = 0;
    
    readDataFromFile(FILENAME_ECG, mdata, MDATA_MAX_SIZE, &mdata_length);
    writeData2File(FILENAME_ORIG, mdata, MDATA_MAX_SIZE);
    //genSinusWithNoise(mdata, sizeof(mdata)/sizeof(double), 100, 2, 1, 0.5);
    //genSinusWithNoise(mdata, sizeof(mdata)/sizeof(double), 100, 2, 1, 0.0);
    removeOffset(mdata, MDATA_MAX_SIZE);
    calcMovingAveraging(mdata, MDATA_MAX_SIZE);
    writeData2File(FILENAME_FILT, mdata, MDATA_MAX_SIZE);
    
    diffSignal(mdata, MDATA_MAX_SIZE);
    normalizeSignal(mdata, MDATA_MAX_SIZE);
    writeData2File(FILENAME_DIFF1, mdata, MDATA_MAX_SIZE);
    
    system("python3 plotdata.py " FILENAME_ORIG " " FILENAME_FILT " " FILENAME_DIFF1 );
    
    return 0;
}