#include "metrique.h"


double calculer_metrique_ligne(Sudoku * sudoku,const int valeur)
{
    assert(sudoku != NULL);
    int indice_colonne = 0;
    int indice_ligne = 0;
    double metrique = 0;
    for(indice_ligne = 0; indice_ligne < 9; indice_ligne++)
    {
        int occurence = 0;
        for (indice_colonne = 0; indice_colonne < 9; indice_colonne++)
        {
            if (sudoku->tab[indice_ligne][indice_colonne] == valeur)
            {
                ++occurence;
            }
        }
        if(occurence == 0)
        {
            occurence = 1;
        }
        occurence -= 1;
        metrique += pow(occurence , 2);
    }
    return metrique;
}

double calculer_metrique_colonne(Sudoku * sudoku,const int valeur)
{
    assert(sudoku != NULL);
    int indice_colonne = 0;
    int indice_ligne = 0;
    double metrique = 0;

    for (indice_colonne = 0; indice_colonne < 9; indice_colonne++)
    {
        int occurence = 0;
        for(indice_ligne = 0; indice_ligne < 9; indice_ligne++)
        {
            if (sudoku->tab[indice_ligne][indice_colonne] == valeur)
            {
                ++occurence;
            }
        }
        if(occurence == 0)
        {
            occurence = 1;
        }
        occurence -= 1;
        metrique += pow(occurence , 2);
    }
    return metrique;
}

double calculer_metrique_partition_partiel(Sudoku * sudoku,const int valeur,const int debut_ligne,
                                           const int borne_ligne,const int debut_colonne,const int borne_colonne)
{
    assert(sudoku != NULL);
    assert(debut_ligne >= 0 && borne_ligne >= 0 && debut_colonne >= 0 && borne_colonne >= 0);
    int indice_colonne = debut_colonne;
    int indice_ligne = debut_ligne;
    double metrique = 0;

    for(indice_ligne = debut_ligne; indice_ligne <= borne_ligne; indice_ligne++)
    {
        int occurence = 0;
        for (indice_colonne = debut_colonne; indice_colonne <= borne_colonne; indice_colonne++)
        {
            if (sudoku->tab[indice_ligne][indice_colonne] == valeur)
            {
                ++occurence;
            }
        }
        if(occurence == 0)
        {
            occurence = 1;
        }
        occurence -= 1;
        metrique += pow(occurence , 2);
    }
    return metrique;
}

double calculer_metrique_partition(Sudoku * sudoku,const int valeur)
{
    assert(sudoku != NULL);
    double metrique = 0;
    metrique  = calculer_metrique_partition_partiel(sudoku,valeur,0,2,0,2);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,0,2,3,5);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,0,2,6,8);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,3,5,0,2);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,3,5,3,5);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,3,5,6,8);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,6,8,0,2);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,6,8,3,5);
    metrique += calculer_metrique_partition_partiel(sudoku,valeur,6,8,6,8);
    return metrique;
}

void calculer_metrique(Sudoku * sudoku)
{
    assert(sudoku != NULL);
    double metrique = 0;
    int valeur = 1;
    for(valeur = 1; valeur <= 9; ++valeur)
    {
        metrique += calculer_metrique_ligne(sudoku,valeur);
        metrique += calculer_metrique_colonne(sudoku,valeur);
        metrique += calculer_metrique_partition(sudoku,valeur);
    }

    sudoku->metrique = metrique;
}
