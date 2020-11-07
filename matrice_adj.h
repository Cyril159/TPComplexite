#define MAX 2000
typedef int Bool; 

typedef struct{
int n;
Bool **matrice;
}MatriceAdj;

void initMatr(size_t taille, MatriceAdj *mat){
    int **matr = (int **)malloc(sizeof(int*) * taille);
    for(size_t i = 0; i < taille; i++)
        matr[i] = (int *)malloc(sizeof(int) * taille);
    mat->n = taille;
    mat->matrice = matr;
}

void libererMatr(MatriceAdj *matr){
    for(size_t i = 0; i < matr->n; i++)
        free(matr->matrice[i]);
    free(matr->matrice);
}