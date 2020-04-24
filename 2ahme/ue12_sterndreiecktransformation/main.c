#include <stdio.h>
#include <stdlib.h>

int wandleDreieckInStern (double rab, double rac, double rbc, double *pra, double *prb, double *prc) {

    double pruefe = rac + rab + rbc;

    if (pra != NULL && prb != NULL && prc != NULL && pruefe > 0 && rac > 0 && rab > 0 && rbc > 0) {

        *pra = (rac * rab) / (rac + rab + rbc);
        *prb = (rab * rbc) / (rac + rab + rbc);
        *prc = (rac * rbc) / (rac + rab + rbc);

        return 0;

    } else {
        return 1;
    }
}


int wandleSternInDreieck (double ra, double rb, double rc, double *prac, double *prab, double *prbc) {

    if (prab != NULL && prab != NULL && prac != NULL && ra > 0 && rb > 0 && rc > 0) {

        *prac = (ra * rb + rb * rc + rc * ra) / rb;
        *prab = (ra * rb + rb * rc + rc * ra) / rc;
        *prbc = (ra * rb + rb * rc + rc * ra) / ra;

        return 0;

    } else {
        return 1;
    }

}

int main () {
    int t1;
    int t2;
    double ra, rb, rc;
    double rac, rab, rbc;

}
