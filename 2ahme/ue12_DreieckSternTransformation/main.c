#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

int wandleDreieckInStern (double rab, double rac, double rbc, double *pRa, double *pRb, double *pRc) {
  
  double pruefeNennerPositiv = rac + rab + rbc;
  
  if (pRa != NULL && pRb != NULL && pRc != NULL && pruefeNennerPositiv > 0 && rac > 0 && rab > 0 && rbc > 0) {
    
      *pRa = (rac * rab) / (rac + rab + rbc);
      *pRb = (rab * rbc) / (rac + rab + rbc);
      *pRc = (rac * rbc) / (rac + rab + rbc);
    
      return 0;
  } else {
    return 1;
  }
}

int wandleSternInDreieck (double ra, double rb, double rc, double *pRab, double *pRac, double *pRbc) {
  
  if (pRab != NULL && pRac != NULL && pRbc != NULL && ra > 0 && rb > 0 && rc > 0) {
    
    *pRac = (ra * rb + rb * rc + rc * ra) / rb;
    *pRab = (ra * rb + rb * rc + rc * ra) / rc;
    *pRbc = (ra * rb + rb * rc + rc * ra) / ra;
    
    return 0;
  } else {
    return 1; 
  } 
}

int testDreieckInStern (double rab, double rac, double rbc, double eps) {
    
   int rv;
   double ra, rb, rc;
 
   rv = wandleDreieckInStern(rab, rac, rbc, &ra, &rb, &rc); 
         
   double raT = (rac * rab) / (rac + rab + rbc);
   double rbT = (rab * rbc) / (rac + rab + rbc);
   double rcT = (rac * rbc) / (rac + rab + rbc);
  
   if (fabs (ra - raT && rb - rbT && rc - rcT) <= eps) {
  	printf("OK ");
   } else {
  	printf("Fehler Test 1\n");
   }

   if (rv != 0) {
    	printf("Test 1: Fehler rv = %d\n", rv);
   } else {
        printf("rab=%lf, rac=%lf, rbc=%lf -> ra=%lf, rb=%lf, rc=%lf\n",
           		rab, rac, rbc, ra, rb, rc);
   }
   return rv;
}

int testSternInDreieck (double ra, double rb, double rc, double eps) {
    
    int rv;
    double rab, rbc, rac;
 
    rv = wandleSternInDreieck(ra, rb, rc, &rab, &rbc, &rac);
  
    double racT = (ra * rb + rb * rc + rc * ra) / rb;
    double rabT = (ra * rb + rb * rc + rc * ra) / rc;
    double rbcT = (ra * rb + rb * rc + rc * ra) / ra;
 	
    if (fabs (rac - racT) <= eps && fabs(rab - rabT) <= eps && fabs(rbc - rbcT) <= eps) {
  	printf("OK ");
    } else {
  	printf("Fehler Test 1");
    }
  	
    if (rv != 0) {
    	printf("Test 1: Fehler rv = %d\n", rv);
    } else {
    	printf("rab=%lf, rac=%lf, rbc=%lf -> ra=%lf, rb=%lf, rc=%lf\n",
           		rab, rac, rbc, ra, rb, rc);
    }
    return rv;
}

int testNULL () {
  
  int rv = 0;
  double ra, rb, rc, rab, rac, rbc;
  
  int rv1 = wandleSternInDreieck(1, 2, 3, NULL, &rbc, &rac);
  int rv2 = wandleSternInDreieck(1, 2, 3, &rab, NULL, &rac);
  int rv3 = wandleSternInDreieck(1, 2, 3, &rab, &rbc, NULL);
  int rv4 = wandleDreieckInStern(1, 2, 3, NULL, &rb, &rc);
  int rv5 = wandleDreieckInStern(1, 2, 3, &ra, NULL, &rc);
  int rv6 = wandleDreieckInStern(1, 2, 3, &ra, &rb, NULL);
  
  if (rv1 && rv2 && rv3 && rv4 && rv5 && rv6 == 1) {
      printf("Test 2 erfolgreich\n");
  } else {
      printf("rv1=%d, rv2=%d, rv3=%d, rv4=%d, rv5=%d, rv6=%d\n", rv1, rv2, rv3, rv4, rv5, rv6);
      rv = 1;
  }
  return rv;
}

int wertparameterGleichNull () {
  
  double ra, rb, rc, rab, rac, rbc;
  
  int rv1 = wandleSternInDreieck(0, 2, 3, &rab, &rbc, &rac);
  int rv2 = wandleSternInDreieck(1, 0, 3, &rab, &rbc, &rac);
  int rv3 = wandleSternInDreieck(1, 2, 0, &rab, &rbc, &rac);
  int rv4 = wandleDreieckInStern(0, 2, 3, &ra, &rb, &rc);
  int rv5 = wandleDreieckInStern(1, 0, 3, &ra, &rb, &rc);
  int rv6 = wandleDreieckInStern(1, 2, 0, &ra, &rb, &rc);
  
  if(rv1 && rv2 && rv3 && rv4 && rv5 && rv6 == 1) {
      printf("Test 3 erfolgreich\n");
      return 0;
  } else {
      printf("rv1=%d, rv2=%d, rv3=%d, rv4=%d, rv5=%d, rv6=%d\n", rv1, rv2, rv3, rv4, rv5, rv6);
      return 1;
  }
}

// Test 4 Prüfung tausendmal 
int testPruefeTausend () {
 srand(time(NULL));
 for(int i = 1; i <= 1000; i++) {
    
    double rab, rac, rbc;
    double raT, rbT, rcT;
    
    double ra = 1000000.1 * rand() / RAND_MAX + 0.1;
    //int zahl2 = rand() % 0.1;
    double multiplikator = 10.1 *rand() / RAND_MAX + 0.1;    
    double rb = ra * multiplikator + 1;
    double rc = ra * multiplikator + 1;
    
    int f1 = wandleSternInDreieck(ra, rb, rc, &rab, &rac, &rbc);
    int f2 = wandleDreieckInStern(rab, rac, rbc, &raT, &rbT, &rcT);
    
    double eps;
    eps = 1E-8;
    
    if (fabs(ra -raT) <= eps || fabs(rb -rbT) <= eps ||fabs(rc - rcT) <= eps) {
    } else {
      printf (" Ra=%lf, RaT =%lf, Rb =%lf, RbT = %lf, Rc =%lf, RcT =%lf\n", ra, raT, rb, rbT, rc, rcT);
      printf("Fehler bei der Berechnung Test 4\n");
      return 1;
    }
    if (f1 != 0|| f2 != 0) {
      printf ("Fehler Funktion Test 4\n");
      return 2;
    }
  }
  printf("Test 4 erfolgreich\n");
  return 0;
}

int main () {
  
  double eps; 
  eps = 1E-10;
  
  // Test 1a: wandleDreieckInStern
  
  assert(testDreieckInStern (1, 2, 3, eps) == 0);
  assert(testDreieckInStern (4, 9, 2, eps) == 0);
  
  // Test 1b: wandleSternInDreieck
   
  assert(testSternInDreieck(1, 4, 7, eps) == 0);
  assert(testSternInDreieck(2, 5, 8, eps) == 0);
  
  // Test 2: rab, rac, rbc, ra, rb, rc gleich NULL
  
  assert(testNULL()== 0);
  
  // Test 3: Wertparameter <= 0 
  
  assert(wertparameterGleichNull () == 0);
  
  // Test 4
  
  assert(testPruefeTausend() == 0);
  
  return 0;
}