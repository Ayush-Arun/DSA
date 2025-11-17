#include <stdio.h>
#define MAX 50

typedef struct {
    int row;
    int col;
    int value;
} term;

term A[MAX], B[MAX], F[MAX];  // Global arrays

// ------------- SIMPLE TRANSPOSE -------------
void simpleTranspose(term src[], term dest[]) {
    int i, j;
    int rows = src[0].row;
    int cols = src[0].col;
    int num = src[0].value;

    dest[0].row = cols;
    dest[0].col = rows;
    dest[0].value = num;

    int k = 1;

    for (i = 0; i < cols; i++) {
        for (j = 1; j <= num; j++) {
            if (src[j].col == i) {
                dest[k].row = src[j].col;
                dest[k].col = src[j].row;
                dest[k].value = src[j].value;
                k++;
            }
        }
    }
}

// ------------- FAST TRANSPOSE -------------
void fastTranspose(term src[], term dest[]) {
    int rowTerms[MAX], startPos[MAX];
    int i, j;

    int rows = src[0].row;
    int cols = src[0].col;
    int num = src[0].value;

    dest[0].row = cols;
    dest[0].col = rows;
    dest[0].value = num;

    if (num > 0) {
        for (i = 0; i < cols; i++)
            rowTerms[i] = 0;

        for (i = 1; i <= num; i++)
            rowTerms[src[i].col]++;

        startPos[0] = 1;
        for (i = 1; i < cols; i++)
            startPos[i] = startPos[i - 1] + rowTerms[i - 1];

        for (i = 1; i <= num; i++) {
            j = startPos[src[i].col]++;
            dest[j].row = src[i].col;
            dest[j].col = src[i].row;
            dest[j].value = src[i].value;
        }
    }
}

// ------------- DISPLAY FUNCTION -------------
void display(term x[]) {
    int n = x[0].value;

    printf("\nRow  Col  Value\n");
    printf("----------------\n");

    for (int i = 0; i <= n; i++)
        printf("%3d  %3d  %3d\n", x[i].row, x[i].col, x[i].value);
}

// ------------- MAIN PROGRAM -------------
int main() {
    int n;

    printf("Enter rows, cols, and number of non-zero elements: ");
    scanf("%d %d %d", &A[0].row, &A[0].col, &A[0].value);

    n = A[0].value;

    printf("Enter elements (row col value):\n");
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &A[i].row, &A[i].col, &A[i].value);

    simpleTranspose(A, B);
    fastTranspose(A, F);

    printf("\nOriginal Matrix:");
    display(A);

    printf("\nSimple Transpose:");
    display(B);

    printf("\nFast Transpose:");
    display(F);

    return 0;
}
