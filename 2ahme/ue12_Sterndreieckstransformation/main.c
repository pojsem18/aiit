#include <stdio.h>
#include <stdlib.h>

int wandleDreieckInStern (double rab, double rac, double rbc, double *pRa, double *pRb, double *pRc) {

  double r = rac + rab + rbc;

  if (pRa != NULL && pRb != NULL && pRc != NULL && r > 0 && rac > 0 && rab > 0 && rbc > 0) {
    *pRa = (rab * rac) / (rac + rab + rbc);
    *pRb = (rab * rbc) / (rac + rab + rbc);
    *pRc = (rac * rab) / (rac + rab + rbc);
    return 0;
  } else {
    return 1;
  }
}

int wandleSternInDreieck (double *pRab, double *pRac, double *pRbc, double ra, double rb, double rc){

  if (pRac != NULL && pRab != NULL && pRbc != NULL && ra > 0 && rb > 0 && rc > 0) {
    *pRac = (ra * rb + rb * rc + rc + ra) / rb;
    *pRab = (ra * rb + rb * rc + rc * ra) / rc;
    *pRbc = (ra * rb + rb * rc + rc * ra) / ra;
    return 0;
  } else {
    return 1;
  }
}

int main () {
  const double eps = 1E-10;
  int rv;
  double ra, rb, rc;
  double rab, rac, rbc;

  // Test 1 wandleDreieckInStern
  rab = 1; rac = 2; rbc = 3;
  rv = wandleDreieckInStern(rab, rac, rbc, &ra, &rb, &rc);
  if (rv != 0) {
    printf("Test 1: Fehler rv = %d\n", rv);
  } else {
    if ((abs(ra - 0.3333333) <= eps) && (abs(rb - 0.5) <= eps) && (abs(rc - 1.0 <= eps))) {
      printf("OK   ");
    } else {
      printf("ERROR   ");
    }
    printf("Test 1: rab=%lf, rac=%lf, rbc%lf -> ra=%lf, rb=%lf, rc=%lf\n", rab, rac, rbc, ra, rb, rc);
  }


}
