#include <stdio.h>
#include <stdlib.h>

# define MAX_TERMS 100
typedef struct{
    float coef;
    int expon;
}polynomail;

polynomail terms[MAX_TERMS];
int avail=0;

#define COMPARE(x, y) ((x) < (y) ? -1 : ((x) == (y) ? 0 : 1))
void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void padd(int starta, int finisha, int startb, int finishb,
          int *startd, int *finishd)
{
    float coefficient;
    *startd = avail;

    while (starta <= finisha && startb <= finishb) {

        switch (COMPARE(terms[starta].expon, terms[startb].expon)) {

        case -1:   
            attach(terms[startb].coef, terms[startb].expon);
            startb++;
            break;

        case 0:    
            coefficient = terms[starta].coef + terms[startb].coef;
            if (coefficient) 
                attach(coefficient, terms[starta].expon);
            starta++;
            startb++;
            break;

        case 1:   
            attach(terms[starta].coef, terms[starta].expon);
            starta++;
            break;
        }
    }


    for (; starta <= finisha; starta++)
        attach(terms[starta].coef, terms[starta].expon);


    for (; startb <= finishb; startb++)
        attach(terms[startb].coef, terms[startb].expon);

    *finishd = avail - 1;
}
void printPoly(int start,int end){
    for(int i=start;i<= end;i++){
        printf("%.1fx^%d",terms[i].coef,terms[i].expon);
        if(i<end)
        printf(" + ");
    }
    printf("\n");
}
int main() {
    int starta = 0, finisha, startb, finishb, startd, finishd;

    attach(3, 4);
    attach(2, 2);
    attach(1, 0);
    finisha = avail - 1;

    startb = avail;
    attach(5, 3);
    attach(2, 2);
    attach(4, 0);
    finishb = avail - 1;

    printf("A(x) = ");
    printPoly(starta, finisha);

    printf("B(x) = ");
    printPoly(startb, finishb);

    padd(starta, finisha, startb, finishb, &startd, &finishd);

    printf("D(x) = A(x) + B(x) = ");
    printPoly(startd, finishd);

    return 0;
}