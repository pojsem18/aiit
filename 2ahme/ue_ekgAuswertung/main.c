#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_WINDOW_SIZE 100
#define MDATA_MAX_SIZE 1000
#define MOVINGAVERAGING_WINDOW_SIZE   10
#define NO_ERROR 0
#define OUT_OF_MEMORY_ERROR 1
#define FILE_ERROR 2
#define FILENAME1  "ekg1.csv"
#define FILENAME2  "ekg2.csv"


double getSinusWithNoise(double f[], int length, double length_period, double amplitude, double offset, double amplitude_noise)
{



    for(int i=0; i <length ; i++)
        f[i] = amplitude * sin(2*M_PI/length_period * i) + offset + (rand() % 100) * amplitude_noise/100;



    return 0;
}


int readDataFromFile(char *filepath, double *mdata, int max_length, int *length)
{
  int idummy = 0;
  double ddummy = 0;

  FILE* f = fopen(filepath, "r");
  if (f==NULL)
    return FILE_ERROR;

  *length = 0;
  while (!feof(f) && (*length < max_length))    // Solange Dateiende NICHT erreicht ist
  {
    char s[100];
    if (fgets(s,100,f) == NULL)   // Nächste Zeile einlesen
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


double removeOffset(double f[], int length)
{
    double summe = 0;
	double offset = 0;

    for(int i=0; i < length; ++i) {
        summe += f[i];
    }
    offset = summe/length;

    for(int i=0; i < length; ++i)
    {
        f[i] -= offset;
    }

    return offset;
}

void calcMovingAveraging(double f[], int length)
{
    int sum = 0;
    int n = 10;

    for(int f_i = 0; f_i < length; f_i++)
    {
        if( f_i <= 989){

            for(int data_i = 0; data_i < n; data_i ++)
            {
            sum = sum + f[f_i+data_i];

            }
            f[f_i] = sum/n;

        }else{
            break;
        }
        if(f_i = 990){
          for(int data_i = 0; data_i < 9; data_i ++)
            {
            sum = sum + f[f_i+data_i];

            }
            f[f_i] = sum/n;
        }
    }

}

void diffSignal(double f[], int length) {

  for(int i = 0; i < length; i++) {
    f[i] = f[i + 1] - f[i];
  }
}

double normalizeSignal(double f[], int length) {
    double maximalwert;
    int i;

    for(i = 0; i < length; i++) {
        maximalwert = abs(f[i]);
    }

    for(i = 0; i < length; i++) {
        f[i] = f[i] / maximalwert;
        f[i] = round(f[i]);
    }
}

int main () {


  double f[999];
  int length = 999;

  readDataFromFile("mdata.csv", f, length, &length);
  writeData2File("EKG1.csv", f, length);
  removeOffset(f, length);
  calcMovingAveraging(f, length);
  writeData2File("EKG_gefiltert.csv", f, length);
  diffSignal(f, length);
  normalizeSignal(f, length);
  writeData2File("EKG3.csv", f, length);
  system("python3 plotdata.py EKG1.csv EKG3.csv");


  return 0;
}