#include <stdio.h>
#include <math.h>

int wandleDreieckInStern (double rab, double rac, double rbc, double *pRa, double *pRb, double *pRc) {

    double divisor = (rab + rac + rbc);

    if (pRa != NULL && pRb != NULL && pRc != NULL && divisor > 0 && rab > 0 && rac > 0 && rbc > 0) {
        *pRa = (rac * rab) / divisor;
        *pRb = (rab * rbc) / divisor;
        *pRc = (rac * rbc) / divisor;
        return 0;

    } else {
        return 1;
    }
}

int wandleSternInDreieck (double ra, double rb, double rc, double *pRab, double *pRac, double *pRbc) {

    if (ra <= 0 || rb <= 0 || rc <= 0) {
        return 1;
    }
    if (pRab == NULL || pRbc == NULL || pRac == NULL){
        return 2;
    }
    *pRab = (ra * rb + rb * rc + rc * ra) / rc;
    *pRac = (ra * rb + rb * rc + rc * ra) / rb;
    *pRbc = (ra * rb + rb * rc + rc * ra) / ra;
    return 0;
}
int istGleich (double v1, double v2, double eps) {
    return fabs(v1 - v2) <= eps;
}

int testDreieckInStern (double rab, double rac, double rbc,
                        double ra, double rb, double rc, double eps) {
    double cRa, cRb, cRc;
    int rv;

    rv = wandleDreieckInStern(rab, rac, rbc, &cRa, &cRb, &cRc);
    if (rv != 0) {
        printf("Fehler rv = %d\n", rv);
    } else {
        if (istGleich(cRa, ra, eps) && istGleich(cRb, rb, eps) && istGleich(cRc, rc, eps)) {
          printf("OK:  ");
        } else {
          printf("ERR:  ");
          rv = 1;
        }
        printf("rab=%lf, rac=%lf, rbc=%lf -> ra=%lf, rb=%lf, rc=%lf\n",
              rab, rac, rbc, cRa, cRb, cRc);
    }
    return rv;
}
int testSternInDreieck (double ra, double rb, double rc,
                        double rab, double rac, double rbc, double eps) {

    double cRab, cRac, cRbc;
    int rv;

    rv = wandleSternInDreieck(ra, rb, rc, &cRab, &cRac, &cRbc);
    if (rv != 0) {
        printf("Fehler rv = %d\n", rv);
    } else {
        if (istGleich(cRab, rab, eps) && istGleich(cRac, rac, eps) && istGleich(cRbc, rbc, eps)) {
          printf("OK:  ");
        } else {
          printf("ERR:  ");
          rv = 1;
        }
        printf("rab=%lf, rac=%lf, rbc=%lf -> ra=%lf, rb=%lf, rc=%lf\n",
                cRab, cRac, cRbc, ra , rb, rc);
    }
    return rv;
}
int testNULL () {
    int rv = 0;
    double ra, rb, rc, rab, rac, rbc;

    for (int i = 0; i < 6; i++) {
        int rvc;
        switch (i) {
            case 0: rvc = wandleSternInDreieck(1, 1, 1, NULL, &rac, &rbc); break;
            case 1: rvc = wandleSternInDreieck(1, 1, 1, &rab, NULL, &rbc); break;
            case 2: rvc = wandleSternInDreieck(1, 1, 1, &rab, &rac, NULL); break;
            case 3: rvc = wandleDreieckInStern(1, 1, 1, NULL, &rb, &rc); break;
            case 4: rvc = wandleDreieckInStern(1, 1, 1, &ra, NULL, &rc); break;
            case 5: rvc = wandleDreieckInStern(1, 1, 1, &ra, &rb, NULL); break;

        }
        if (rvc == 0) {
            rv++;
            printf("Fehler bei i = %d\n", i);
        }
    }
    if (rv == 0) {
        printf("OK: ");
    }
    printf("\n");
    return rv;
}

int testKleinerGleichNull () {
 int rv = 0;
    double ra, rb, rc, rab, rac, rbc;

    for (int i = 0; i < 6; i++) {
        int rvc;
        switch (i) {
            case 0: rvc = wandleSternInDreieck(-1, 1, 1, &rab, &rac, &rbc); break;
            case 1: rvc = wandleSternInDreieck(1, -1, 1, &rab, &rac, &rbc); break;
            case 2: rvc = wandleSternInDreieck(1, 1, -1, &rab, &rac, &rbc); break;
            case 3: rvc = wandleDreieckInStern(-1, 1, 1, &ra, &rb, &rc); break;
            case 4: rvc = wandleDreieckInStern(1, -1, 1, &ra, &rb, &rc); break;
            case 5: rvc = wandleDreieckInStern(1, 1, -1, &ra, &rb, &rc); break;
        }
        if (rvc == 0) {
            rv++;
            printf("Fehler bei i = %d\n", i);
        }
    }
    if (rv <= 0) {
        printf("OK: ");
    }
    printf("\n");
    return rv;
}

int main () {

  double eps = 1E-8;  // 0.00000001

  // Test 1a: wandleDreieckInStern
  printf("Test 1a(1): "); testDreieckInStern(1, 2, 3, 0.3333333333, 0.5, 1.0, eps);
  printf("Test 1a(2): "); testDreieckInStern(2, 5, 10, 0.5882352941, 1.1764705882, 2.9411764706, eps);

  // Test 1b: wandleSternInDreieck
  printf("Test 1b(1): "); testSternInDreieck(1, 8, 7, 10.14285714, 8.875, 71.0, eps);
  printf("Test 1b(2): "); testSternInDreieck(4, 6, 9, 12.6666666666, 19.0, 28.5, eps);

  // Test 2: testNULL
  printf("Test 2:     "); testNULL ();

  // Test 3: testKleinerGleichNull
  printf("Test 3:     "); testKleinerGleichNull ();

return 0;
}
