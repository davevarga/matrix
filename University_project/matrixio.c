#include "matrixio.h"

#pragma warning(suppress : 4996)

void mprintf(Matrix A) {
    for (int i = 0; i < A.nrw; ++i) {
        for (int j = 0; j < A.nclmn; ++j)
            printf("%5.2f ", A.elm[i][j]);
        printf("\n");
    }

    printf("\n");
    return;
}

void mscanf(FILE *fp, Matrix *A)
{
    if (fp == NULL) {
        /*Eselteges hibakezelez
        Vigyazzunk mert akkor nem hivhatunk
        meg mas fugvenyeket*/
        perror("Fajl megnyitasa sikertelen");
        return;

    } else {

        /*A txt file elso soraban a sor es az oszlopszam adott
        pontossan ebben a sorrendben.*/
        fscanf(fp, "%d %d", &(A->nrw), &(A->nclmn));

        /*Lefoglaljuk a helyet egy segedvaltozoba,
        majd ebbe kiolvassuk a txt-ben levo adatokat.*/
        double** content;
        content = (double**)malloc(A->nrw * sizeof(double*));
        if (content != NULL)
            for (int i = 0; i < A->nrw; ++i) {
                content[i] = (double*)malloc(A->nclmn * sizeof(double));
                if (content[i] == NULL)
                    printf("Error2: Nem sikerult a foglalas");
            }
        else printf("Error2: Nem sikerult a foglalas");

        for (int i = 0; i < A->nrw; ++i) {
            for (int j = 0; j < A->nclmn; ++j)
                fscanf(fp, "%lf", &(content[i][j]));
            fscanf(fp, " ");
        }
        /*Osszekotjuk a matrix tartalmat a segedvaltozoval
        !Mivel a matrix pointer-kent van megadva ezert dereferalni kell.*/
        A->elm = content;
    }
}

void mfree(Matrix A)
{
    for (int i = 0; i < A.nrw; ++i)
        free(A.elm[i]);
    free(A.elm);
}


