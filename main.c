#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h>
#include "matrice_adj.h"

Bool estZoneVide(MatriceAdj matr, int sommets[], int nbSommets){
    for(size_t i = 0; i < nbSommets; i++){
        int sommet = sommets[i];
        for(size_t j = 0; j < nbSommets; j++){
            if(matr.matrice[sommet][sommets[j]] == 1)
                return 0;
        }
    }
    return 1;
}

Bool estPasDansTab(size_t sommet, int tabSommets[], size_t taille){
    for(size_t i = 0; i < taille; i++){
        if(tabSommets[i] == sommet)
            return 0;
    }
    return 1;
}

size_t sommet_deg_min(MatriceAdj mat, int sommetsPris[]){
    size_t deg_min = mat.n;
    size_t indice_deg_min = 0;
    for(size_t i = 0; i < mat.n; i++){
        size_t deg = 0;
        for(size_t j = 0; j < mat.n; j++){
            if(mat.matrice[i][j] == 1)
                deg++;
        }
        if(deg < deg_min && sommetsPris[i] != 1){
            deg_min = deg;
            indice_deg_min = i;
        }
    }
    sommetsPris[indice_deg_min] = 1;
    return indice_deg_min;
}

Bool pas_connecte(MatriceAdj mat, size_t sommet, int *ensemble_sommet, size_t taille){
    for(size_t i = 0; i < taille; i++)
    {
        if(mat.matrice[ensemble_sommet[i]][sommet] == 1)
            return 0;
    }
    return 1;
}

int *zoneVideMax(MatriceAdj matrice){
    int  *res =(int*)malloc(sizeof(size_t) * matrice.n * matrice.n);
    for(size_t i = 0; i < matrice.n; i++)
        res[i] = -1;

    size_t res_taille = 0;
    int tabPris[matrice.n];
    for(size_t i = 0; i < matrice.n; i++){tabPris[i] = 0;}
    for(size_t i = 0; i < matrice.n; i++){
        size_t sommet_dg_min = sommet_deg_min(matrice, tabPris);
        if(pas_connecte(matrice, sommet_dg_min, res, res_taille)){
            res[res_taille] = sommet_dg_min;
            res_taille++;
        }
    }
    return res;
}

MatriceAdj creerMatrAlea(size_t taille){
    MatriceAdj mat;
    mat.n = taille;
    for(size_t i = 1; i < taille ; i++){
        for(size_t j =0; j < i; j++){
            int res = rand()%2;
            mat.matrice[i][j] = res;
            mat.matrice[j][i] = res;
        }
        mat.matrice[i][i] = 0;
    }
    mat.matrice[0][0] = 0;
    return mat;
}

int main(){
    srand(time(0));
 
      MatriceAdj mat = creerMatrAlea(600);
    for(size_t i =0; i < mat.n; i++){
        for(size_t j = 0; j < mat.n; j++)
            printf("%d ", mat.matrice[i][j]);
        printf("\n");
    }
    printf("---------\n");
    int * zone_vide_max = zoneVideMax(mat);
    for(size_t i = 0; i < mat.n; i++)
        printf("%d, ", zone_vide_max[i]);

    int taille = 0;
    for(size_t i = 0; i < mat.n; i++){
        if(zone_vide_max[i] == -1)
            break;
        taille++;
    }
    printf("\n Taille : %d \n", taille);
    printf("Vérification : %d \n", estZoneVide(mat, zone_vide_max, taille));
    free(zone_vide_max);
   
    
    return 0;
}

