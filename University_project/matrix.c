#include "matrix.h"

/*Mas modulbol lathato tipusok*/

/*Mas modulbol lathato fuggvenyek*/
void sum(Matrix *A, Matrix const *B)
{
    /*Csak egyforma meretu matrixok kozott ertelmezett az osszeadas*/
    if (A->nrw == B->nrw && A->nclmn == B->nclmn)
    {
        for (int i = 0; i < A->nrw; ++i)
            for (int j = 0; j < A->nclmn; ++j)
                A->elm[i][j] = A->elm[i][j] + B->elm[i][j];
    }
    else {
        /*Hibakeyeles*/
        printf("Error1: Different Matrix size\n");
    }
    return;
}

void sub(Matrix *A, Matrix const *B)
{
    /*Csak egyforma meretu matrixok kozott ertelmezett a kivonas*/
    if (A->nrw == B->nrw && A->nclmn == B->nclmn)
    {
        for (int i = 0; i < A->nrw; ++i)
            for (int j = 0; j < A->nclmn; ++j)
                A->elm[i][j] = A->elm[i][j] - B->elm[i][j];
    }
    else {
        /*Hibakezeles*/
        printf("Error1: Different Matrix size\n");
    }
    return;
}

void multx(Matrix* A, double const x)
{
    /*Skalarral valo beszorzas eseten nincs semmi fele kikotes,
    barmilyen matrixot barmilyen szammal be lehet szorozni*/
    for (int i = 0; i < A->nrw; ++i)
        for (int j = 0; j < A->nclmn; ++j)
            A->elm[i][j] *= x;
}

void mult(Matrix *A, Matrix const *B)
{
    if (A->nclmn == B->nrw)
    {
        /*Letrehozunk egy seged matrix tablazatot hogy
        az A matrix elemeinek tablazatat erre kicsereljuk*/
        double** content;
        content = (double**)malloc(A->nrw * sizeof(double*));
        if (content != NULL)
            for (int i = 0; i < A->nrw; ++i) {
                content[i] = (double*)malloc(B->nclmn * sizeof(double));
                if (content[i] == NULL)
                    printf("Error3: Nem sikerult a foglalas");
            }
        else printf("Error3: Nem sikerult a foglalas");

        /*Kiszamoljuk a szorzatot a content segedtablaba*/
        for (int i = 0; i < A->nrw; ++i)
            for (int j = 0; j < B->nclmn; ++j)
            {
                double elemij = 0;
                for (int k = 0; k < A->nclmn; ++k)
                    elemij += A->elm[i][k] * B->elm[k][j];
                content[i][j] = elemij;
            }

        /*Felszabaditjuk az A matrix tartalmat, majd ugy
        modositjuk hogy ez tarolja a szorzat eredmenyet*/
        mfree(*A);   A->nclmn = B->nclmn;    A->elm = content;
    }
    else {
        printf("Error2: Not compatible Matrix size\n");
    }
    return;
}

double det(Matrix const A)
{
    /*A fuggveny nem kezeli a meretbol adodo hibakat.
    Erre a felasznalo kell figyeljen.*/
    int N = A.nrw;

    if (N == 1) {
        /*A rekurzio kilepo feltetele. Az 1x1-es
        determinans erteke egyenlo onmagaval*/
        return A.elm[0][0];

    } else {

        /*Alkalmazzuk a felbontas tetelet*/
        double osszeg = 0;
        for (int k = 0; k < N; ++k)
        {
            /*Letrehozzuk a konjugalt matrixot*/
            Matrix B = { .nrw = N - 1, .nclmn = N - 1 };
            B.elm = (double**)malloc((N - 1) * sizeof(double*));
            if(B.elm != NULL)
                for (int i = 0; i < N - 1; ++i) {
                    B.elm[i] = (double*)malloc((N - 1) * sizeof(double));
                    if(B.elm[i] == NULL)
                        printf("Error3: Nem sikerult a foglalas");
                }
            else printf("Error3: Nem sikerult a foglalas");

            /*Csak azokat az elemeket vesszuk figyelembe
            amelyek nincsenek az konjugalt elem oszlopaban*/
            for (int i = 0; i < N - 1; ++i)
                for (int j = 0; j < N; ++j)
                {
                    if (j < k) B.elm[i][j] = A.elm[i][j];
                    if (j > k) B.elm[i][j - 1] = A.elm[i][j];
                }
            osszeg += pow(-1, N - 1 + k) * A.elm[N - 1][k] * det(B);
            mfree(B);
        }
        return osszeg;
    }
}

void trans(Matrix* A)
{
    /*Az aij elem lessz az aji elem,
    azaz megforditjuk a sorokat az oszlopokkal*/
    for (int i = 0; i < A->nrw; ++i)
        for (int j = i; j < A->nclmn; ++j)
        {
            double temp = A->elm[i][j];
            A->elm[i][j] = A->elm[j][i];
            A->elm[j][i] = temp;
        }

    /*A meretet is meg kell forditani*/
    int temp = A->nrw;
    A->nrw = A->nclmn;
    A->nclmn = temp;
}

Matrix inv(Matrix const *A)
{
    if (A->nrw == A->nclmn) 
    {
        double determinans = det(*A);
        if (determinans == 0) {
            /*Nem letezik az inverze a matrixnak*/
            printf("Nem letezik inverze a matrixnak");
            return;

        } else {
            int N = A->nrw;

            /*Letrehozzuk a transponalt matrixot es a conjugalt matrixot
            kulon-kulon, mivel nem akarjuk modositani az eredeti matrixot.
            Ezek csak ameneti tarhelyek.A merete ugyanakkora mint az eredeti matrixnak*/
            double** content_trans;
            content_trans = (double**)malloc(N * sizeof(double*));
            if(content_trans != NULL)
                for (int i = 0; i < N; ++i) {
                    content_trans[i] = (double*)malloc(N * sizeof(double));
                    if(content_trans[i] == NULL)
                        printf("Error3: Nem sikerult a foglalas\n");
                }
            else printf("Error3: Nem sikerult a foglalas\n");

            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    content_trans[i][j] = A->elm[i][j];
            Matrix Trans = { .nrw = N, .nclmn = N, .elm = content_trans };

            double** content_conj;
            content_conj = (double**)malloc(N * sizeof(double*));
            if(content_conj != NULL)
                for (int i = 0; i < N; ++i) {
                    content_conj[i] = (double*)malloc(N * sizeof(double));
                    if(content_conj[i])
                        printf("Error3: Nem sikerult a foglalas");
                }
            else printf("Error3: Nem sikerult a foglalas");

            Matrix Conj = { .nrw = N, .nclmn = N, .elm = content_conj };

            /*A conjugalt matrix a transponalt matrix elemenketni 
            determinans szamit, figyelembe veve az elojelt, viszont az elem erteket nem*/
            trans(&Trans);             
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j) {

                    /*A determinans fugvenybol kimasolt algoritmust alkalmazzuk*/
                    Matrix D = { .nrw = N - 1, .nclmn = N - 1 };
                    D.elm = (double**)malloc((N - 1) * sizeof(double*));
                    for (int k = 0; k < N - 1; ++k)
                        D.elm[k] = (double*)malloc((N - 1) * sizeof(double));

                    /*Csak azokat az elemeket vesszuk figyelembe
                    amelyek nincsenek az konjugalt elem oszlopaban
                    es ez esetbe soraban*/
                    for (int k = 0; k < N; ++k)
                        for (int t = 0; t < N; ++t)
                        {
                            if (k < i && t < j) D.elm[k][t] = Trans.elm[k][t];
                            if (k < i && t > j) D.elm[k][t - 1] = Trans.elm[k][t];
                            if (k > i && t < j) D.elm[k - 1][t] = Trans.elm[k][t];
                            if (k > i && t > j) D.elm[k - 1][t - 1] = Trans.elm[k][t];
                        }
                    /*A determinans szamitassal ellententbe nem szamit a konjugalt elem erteke*/
                    Conj.elm[i][j] = pow(-1, i + j) * det(D);
                    mfree(D);
                }
            
            mfree(Trans);
            multx(&Conj, 1.00 / determinans);
            return Conj;
        }
    } else {
        /*Hibakezeles*/
        printf("Error: Not square matrix given");
        return;
    }
}

/*A Gauss eliminacio algoritmusa ket reszre van osztva, ket fugvenyre
amelyik a ket resszel felel meg*/
void gauss(Matrix *A)
{
    int i = 0, j = 0;
    while (i < A->nrw && j < A->nclmn - 1)
        
    {
        if (A->elm[i][j] != 0) {
            /*Leosztjuk a sort a vezeregyes ertekevel*/
            for (int k = A->nclmn - 1; k >= 0; --k)
                A->elm[i][k] = A->elm[i][k] / A->elm[i][j];

            /*Az alatta levo sorokat leosztjuk a vezeregyes
            soraval, ugy hogy az alatt csak 0 legyen*/
            for (int t = i + 1; t < A->nrw; ++t) {
                for (int k = A->nclmn - 1; k >= 0; --k)
                    A->elm[t][k] -= A->elm[i][k] * A->elm[t][j];
            }
            ++i; ++j;
        }
        else {

            /*Keressunk olyan sort amelyikbe, a j oszlopba
            van 0-tol kulombozo szam. Ha talaltunk akkor,
            mar nem keresunk, de feltetelezzuk hogy nincs ilyen sor*/
            bool talalt = false;
            for (int t = i + 1; t < A->nrw && !talalt; ++t)
                if (A->elm[t][j] != 0)
                {
                    /*Felcsereljuk a ket sort*/
                    for (int k = j; k < A->nclmn; ++k) {
                        double temp = A->elm[i][k];
                        A->elm[i][k] = A->elm[t][k];
                        A->elm[t][k] = temp;
                    }
                    /*Talaltunk olyan sort ami megfelel,
                    ezert majd ujra el kell vegezni az iteraciot*/
                    talalt = true;
                }
            mprintf(*A);
            /*Ha nem talalt akkor, ha meg vannak tovabbi valtozok ez egy
            parameter valtozo, ha viszont ez volt az utolso sor, akkor
            olyan soraink vannak amik csak 0-bol alnak, ezert --i*/
            if (!talalt)
                if (j + 1 < A->nclmn - 1) ++j;
                else --i;
        }
    }
    /*Jon a kovetkezo resze a gauss eliminacionak*/   
    gauss_vege(A, i);
    return;
}

static void gauss_vege(Matrix *A, int i)
{
    /*Leellenorizzuk ha van tilos sor*/
    for (int t = i + 1; t < A->nrw; ++t)
        if (A->elm[t][A->nclmn - 1] != 0) {
            printf("Nem megoldhato az egyenletrendszer");
            return;
        }
    /*elhanyagoljuk azokat a sorokat amelyeben csak 0 van*/
    A->nrw = i;

    /*Elkezdunk visszafele nullazni, kiveve az elso sort,
    mert az folott nem kell. Ez a tulajdonsag segit a vezer-
    egyesek azonositasaban, mert vannak hamis vezeregyesek is*/
    int j = A->nclmn - 2;
    i = i - 1;
    while (i > 0 && j > 0)
    {
        /*Leellenorizzuk ha ez vezeregyes*/
        for (int k = j - 1; k >= 0; --k)
            if (A->elm[i][k] != 0)
                j = k;

        for (int t = i - 1; t >= 0; --t)
            for (int k = A->nclmn - 1; k >= 0; --k)
                A->elm[t][k] -= A->elm[i][k] * A->elm[t][j];

        --i; --j;
    }
    return;
}

int rang(Matrix const *A)
{
    /*Kesziteni kell egy masolatot a matrixrol
    hogy ne modositsuk az eredeti tartalma.
    Ezen alkamazzuk gauss() fuggvenyt*/
    double** content;
    content = (double**)malloc(A->nrw * sizeof(double*));
    if(content  != NULL)
        for (int i = 0; i < A->nrw; ++i) {
            content[i] = (double*)malloc(A->nclmn * sizeof(double));
            if(content[i] == NULL)
                printf("Error3: Nem sikerult a foglalas");
        }
    else printf("Error3: Nem sikerult a foglalas");

    for (int i = 0; i < A->nrw; ++i)
        for (int j = 0; j < A->nclmn; ++j)
            content[i][j] = A->elm[i][j];
    Matrix Aux = { .nrw = A->nrw, .nclmn = A->nclmn, .elm = content };

    gauss(&Aux);
    /*Megszamoljuk a vezeregyesek szamat*/
    int r = 0;
    int i = Aux.nrw - 1;
    int j = Aux.nclmn -1;
    while (i >= 0 && j >= 0)
    {
        printf(" r=%d:", r);
        if (Aux.elm[i][j] == 1.00) {
            /*Megnezzuk ha ez hamis vezeregyes.
            Ha igen akkor szerepelnie kell balra egy masik eggyesnek*/
            printf(" i=%d j=%d", i, j);
            for (int k = j - 1; k >= 0; --k)
                if (Aux.elm[i][k] == 1.00)
                    j = k;

            r++; i--; j--;
            printf(" -> i=%d j=%d\n", i, j);
        }
        else {
            printf(" i=%d j=%d", i, j);
            int k = j;
            bool talalt = false;
            while (k >= 0 && !talalt) {
                if (Aux.elm[i][k] == 1) {
                    j = k; r++;
                    talalt = true;
                }
                k--;
            }

            /*Ha nem talalunk abba a sorba vezeregyest
            akkor a kovetkezo sorba megyunk. Csak az i-t modositjuk
            mert a kovetkezo vezeregyes meg lehet e folott*/
            if (!talalt) 
                i--;

            printf(" -> i=%d j=%d\n", i, j);
        }
    }
    mfree(Aux);
    return r - 1;
}