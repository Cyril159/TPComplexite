#include <stdlib.h>
#include <stdio.h>
#include "matrice_adj.h"

Bool estZoneVide(MatriceAdj matr, int sommets[], int nbSommets){
    for(size_t i = 0; i < nbSommets; i++){
        int sommet = sommets[i];
        for(size_t j = i+1; j < nbSommets; j++){
            if(matr.matrice[sommet][j] == 1)
                return 0;
        }
    }
    return 1;

}

size_t sommet_deg_min(MatriceAdj mat){
    size_t deg_min = mat.n;
    for(size_t i = 0; i < mat.n; i++){
        size_t deg = 0;
        for(size_t j = 0; j < mat.n; j++){
            if(mat.matrice[i][j] == 1)
                deg++;
        }
        if(deg < deg_min)
            deg_min = deg;
    }
    return deg_min;
}

Bool pas_connecte(MatriceAdj mat, size_t sommet, int *ensemble_sommet, size_t taille){
    for(size_t i = 0; i < mat.n; i++)
    {
        if(mat.matrice[sommet][i] == 1)
            return 0;
    }
    return 1;
}

int *zoneVideMax(MatriceAdj matrice){
    int  *res =(int*)malloc(sizeof(size_t) * matrice.n * matrice.n);
    for(size_t i = 0; i < matrice.n; i++)
        res[i] = -1;

    size_t res_taille = 0;
    size_t sommet_dg_min = sommet_deg_min(matrice);
    for(size_t i = 0; i < matrice.n; i++){
       if(pas_connecte(matrice, i, res, res_taille)){
           res[res_taille] = i;
           res_taille++;
       }
    }
    return res;
}

int main(){
    MatriceAdj matr;
    matr.n = 5;
    matr.matrice[0][0] = 0;
    matr.matrice[0][1] = 1;
    matr.matrice[0][2] = 1;
    matr.matrice[0][3] = 0;
    matr.matrice[0][4] = 0;

    matr.matrice[1][0] = 1;
    matr.matrice[1][1] = 0;
    matr.matrice[1][2] = 1;
    matr.matrice[1][3] = 0;
    matr.matrice[1][4] = 0;

    matr.matrice[2][0] = 1;
    matr.matrice[2][1] = 1;
    matr.matrice[2][2] = 0;
    matr.matrice[2][3] = 0;
    matr.matrice[2][4] = 0;

    matr.matrice[3][0] = 1;
    matr.matrice[3][1] = 0;
    matr.matrice[3][2] = 1;
    matr.matrice[3][3] = 0;
    matr.matrice[3][4] = 0;

    matr.matrice[4][0] = 1;
    matr.matrice[4][1] = 1;
    matr.matrice[4][2] = 0;
    matr.matrice[4][3] = 0;
    matr.matrice[4][4] = 0;

    int sommets[2] = {3,4};
    printf("Resultat %d :", estZoneVide(matr, sommets,2));
    printf("---------\n");
    int * zone_vide_max = zoneVideMax(matr);
    for(size_t i = 0; i < matr.n; i++)
        printf("%d, ", zone_vide_max[i]);
    free(zone_vide_max);
    return 0;
}