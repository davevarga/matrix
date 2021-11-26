#include "matrix.h"

#define LINE "----------------------------------------------\n"

#pragma warning(suppress : 4996)

int main(void) {
    FILE* fp = fopen("table.txt", "rt");

    Matrix A, B, C;
    mscanf(fp, &A);   mprintf(A);   printf(LINE);
    mscanf(fp, &B);   mprintf(B);   printf(LINE);
    mscanf(fp, &C);   mprintf(C);   printf(LINE);    

    /*ide kerulnek az utasitasok*/

    printf("Az elso ket matrixnak az osszege:\n");
    sum(&A, &B);      mprintf(A);   printf(LINE);
    
    printf("Az elso ket matrixnak a kulombsege:\n");
    sub(&B, &A);      mprintf(B);   printf(LINE);
    
    printf("Az osszeg matrixnak es a kulombseg matrixnak a szorzata:\n");
    mult(&A, &B);     mprintf(A);   printf(LINE);
    
    printf("Az utolso matrix -1 skalarral valo beszorzasa:\n");
    multx(&A, -1);    mprintf(A);   printf(LINE);
    
    double x = det(A);
    printf("Az tolso matrixnak a determinansa: %.2f\n\n", x);
    printf(LINE);

    printf("Igy tehat a matrix inverze az:\n");
    Matrix invA;
    invA = inv(&A);   mprintf(invA);
    printf("\nEzt onnan tudjuk hogy,ha osszeszorozzuk \naz eredetive ezt a matrixot kapjuk:\n");
    mult(&invA, &A);  mprintf(invA); printf(LINE);
    

    printf("A gaussal elvegzett C matrix eredmenye:\n");
    gauss(&C);        mprintf(C);   printf(LINE);

    int r = rang(&C);
    printf("Ennek tehat a rangja: %d\n",r);
    printf(LINE);

    /*A foprogram vege, felszabaditas, file zarasa*/
    
    mfree(A);
    mfree(B);
    mfree(C);
    mfree(invA);
    return 0;
}
