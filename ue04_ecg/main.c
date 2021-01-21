/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: lieschnegg
 *
 * Created on 5. November 2020, 05:02
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ECGDATA_FILENAME                "ecg.csv"
#define ECGDATA_SAMPLE_RATE             360         //Hz
#define ECGDATA_QRS_INTERVAL            0.6
#define ECGDATA_TIMEOUT                 (3*ECGDATA_QRS_INTERVAL)

#define ECGDATA_BUFFERSIZE              (5*ECGDATA_SAMPLE_RATE)
#define MOVINGAVERAGING_WINDOW_SIZE     3

#define NO_ERROR 0
#define OUT_OF_MEMORY_ERROR 1
#define FILE_ERROR 2

void genSinusWithNoise(double f[], int length, double length_period, double amplitude, double offset, double amplitude_noise)
{
    for (int i = 0; i < length; ++i)
    {
        f[i] = amplitude * sin(2*M_PI/length_period * i);
        f[i] += offset;
        f[i] += (rand() % 100) * amplitude_noise/100;
    }
}


int readECG(char *filepath, double *mdata, int max_length, int *length)
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

    if (sscanf(s,"%lf", &mdata[*length]) == 1)
        (*length)++;
  }
  fclose(f);
  return NO_ERROR;
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
  double sum = 0;
  double offset = 0;

  for(int i = 0; i < length; ++i)
  {
    sum += f[i];
  }

  offset = sum/length;

  for(int i = 0; i < length; ++i) {

    f[i] -= offset;
  }
  return offset;
}

void calcMovingAveraging(double f[], int length)
{
  double sum=0;
  double avg=0;

  for(int i = 0; i < MOVINGAVERAGING_WINDOW_SIZE; i++)
  {
      sum += f[i];
  }

  for(int i = 0; i < (length - MOVINGAVERAGING_WINDOW_SIZE); i++)
  {
    avg = sum / MOVINGAVERAGING_WINDOW_SIZE;
    sum += f[i + MOVINGAVERAGING_WINDOW_SIZE];
    sum = sum - f[i];
    f[i] = avg;
  }

  for(int i = (length - MOVINGAVERAGING_WINDOW_SIZE); i < length; i++)
  {
    sum = sum - f[i];
    f[i] = sum / (length - i);
  }

}

void diffSignal(double f[], int length)
{
  for(int i = 0; i < (length - 1); i++)
  {
      f[i] = f[i + 1] - f[i];
  }
}

double getMaxValue(double f[], int length, int *max_index)
{
    double max_value = f[0];

    if (max_index != NULL)
    {
        *max_index = 0;
    }

    for(int i=0; i < length; ++i)
    {
        if ((f[i] > max_value) && (f[i] > -max_value) )
        {
            max_value = f[i];
            if (max_index != NULL)
            {
                *max_index = i;
            }
        }
    }
    return max_value;
}


double normalizeSignal(double f[], int length)
{
    double max_value = getMaxValue(f, length, NULL);

    if (max_value < 0)
        max_value *= -1;

    for(int i=0; i < length; ++i)
    {
        if(f[i] < 0)
            f[i] = (int)(f[i] / max_value - 0.5);
        else
            f[i] = (int)(f[i] / max_value + 0.5);
    }
    return max_value;
}
double normalizeSignal2(double f[], int length)
{
    double max_value = getMaxValue(f, length, NULL);

    for(int i=0; i < length; ++i)
    {
        f[i] = f[i] / max_value;
    }
    return max_value;
}

int findRPeak(double f_2diff[], double f_orig[], int length, double rpeak[], int rpeak_length, int *last_qrs_start)
{
    int nz_legnth = 0;
    int qrs_complex_start = -1, qrs_complex_end = -1;
    int rpeak_i = 0;
    int x = 0;

    //Abtastrate: ECGDATA_SAMPLE_RATE = 360 Hz
    //Abtastdauer: 1/360 s
    //Wieviele Feldelemente sind in ECGDATA_QRS_INTERVAL s enthalten?
    //ECGDATA_QRS_INTERVAL/(1/360) = ECGDATA_QRS_INTERVAL s * Abtastfrequenz
    const int nsep = ECGDATA_QRS_INTERVAL * ECGDATA_SAMPLE_RATE;

    //1.) Wir suchen den Startpunkt des ersten QRS-Komplexe -> Q-Wert
    for( int i = 0; i < length; ++i)
    {
        if (f_2diff[i] != 0)
        {
            qrs_complex_start = i;
            qrs_complex_end = i;
            break;
        }
    }

    //2.) Suche die Start und Endwerte aller restlichen QRS-suchen und zwischen den Start-
    // und Endpunkten wird das Maximum und somit die R-Zacke bestimmt!
    for( int i = qrs_complex_start + 1; i < length; ++i)
    {
        if (f_2diff[i] != 0) //Start oder Ende eines QRS-Komplex detektiert?
        {
            if ( (i - qrs_complex_end) >= nsep )  //neuen QRS-Komplex gefunden!
            {
                if (rpeak_i < rpeak_length)
                {

                    getMaxValue(&f_orig[qrs_complex_start], qrs_complex_end - qrs_complex_start, &x);

                    rpeak[rpeak_i] = x + qrs_complex_start;
                    //printf("%d.): qrs-start: %d, qrs-length: %d, r-peak: %1.f\n", rpeak_i, qrs_complex_start, qrs_complex_end - qrs_complex_start, rpeak[rpeak_i]);
                    ++rpeak_i;

                    qrs_complex_start = i;
                }
                else
                    break;
            }
            qrs_complex_end = i;
        }
    }

    /*
    if (letztes Feldelement - qrs_complex_start > 2*letzterDetektierterHerzschlag)
        ; //-> Stromschlag
    */



    if (qrs_complex_end > qrs_complex_start)
    {
        getMaxValue(&f_orig[qrs_complex_start], qrs_complex_end - qrs_complex_start, &x);
        rpeak[rpeak_i] = x + qrs_complex_start;
        //printf("%d.): qrs-start: %d, qrs-length: %d, r-peak: %1.f\n", rpeak_i, qrs_complex_start, qrs_complex_end - qrs_complex_start, rpeak[rpeak_i]);
        ++rpeak_i;
    }
    *last_qrs_start = qrs_complex_start;
    return rpeak_i;
}

void markRPeak(double rpeak[], int length, double rpeaksignal[], int rpeaksignal_length)
{
    for (int i = 0; i < rpeaksignal_length; ++i)
    {
        rpeaksignal[i] = 0;
    }

    for (int i = 0; i < length; ++i)
    {
        rpeaksignal[(int) rpeak[i]] = 1;
    }
}

void printHeartRate(double rpeak[], int length)
{
        for (int i = 0; i < length - 1; ++i)
        printf("Herzfrequenz %.1f BPM\n", ECGDATA_SAMPLE_RATE/(rpeak[i+1] - rpeak[i])*60);
}

void analyseECG()
{
    const int ecg_timeout = ECGDATA_TIMEOUT * ECGDATA_SAMPLE_RATE;

    static int offset = 0;
    static double ecg[ECGDATA_BUFFERSIZE]; //Orgianaldaten vom Messgeraet -> werden waerhend des gesamten Ablaufs nicht veraendert!

    double ecg_compute[ECGDATA_BUFFERSIZE];
    double rpeak[ECGDATA_BUFFERSIZE];
    int ecg_length = 0;
    int rpeak_length = 0;

    while(1)
    {
        //1. Schritt -> Die alten noch nicht analysierten Messdaten zum Anfang des Feldes kopiert
        if (offset > 0)
        {
            for (int i = 0; i < (ecg_length - offset); ++i)
                ecg[i] = ecg[offset + i];
        }
        offset = ecg_length - offset;

        while(readECG(ECGDATA_FILENAME, ecg + offset, ECGDATA_BUFFERSIZE - offset, &ecg_length) == FILE_ERROR)
              ;
        ecg_length = ecg_length + offset;

        for (int i = 0; i < ecg_length; ++i)
            ecg_compute[i] = ecg[i];

        removeOffset(ecg_compute, ecg_length);
        calcMovingAveraging(ecg_compute, ecg_length);

        diffSignal(ecg_compute, ecg_length);
        normalizeSignal(ecg_compute, ecg_length);

        diffSignal(ecg_compute, ecg_length);
        rpeak_length = findRPeak(ecg_compute, ecg, ecg_length, rpeak, ECGDATA_BUFFERSIZE, &offset);

        if ((ecg_length - offset) > ecg_timeout)
        {
            printf("SCHOCK!\n");

            for (int i = 0; i < ecg_timeout; ++i)
                ecg[i] = ecg[ecg_length - ecg_timeout];
            offset = 0;
            ecg_length = ecg_timeout;

        }
        printHeartRate(rpeak, rpeak_length);

        remove(ECGDATA_FILENAME);
    }
}

int main (int argc, char** argv)
{
    analyseECG();
    return (EXIT_SUCCESS);
}

