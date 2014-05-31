#include "sudoku.h"

Sudoku * construire_sudoku(void)
{
	Sudoku * resultat = malloc(sizeof(Sudoku));
	assert(resultat != NULL);
	resultat->choisi = 0;
	resultat->metrique = 0;
	assert(resultat != NULL);
	return resultat;
}

void liberer_sudoku(Sudoku * sudoku[],const int taille)
{
    assert(sudoku != NULL);
    int indice = 0;
    for(indice = 0; indice < taille;++indice)
    {
        free(sudoku[indice]);
    }
}

void afficher_sudoku(const Sudoku * sudoku)
{
    assert(sudoku != NULL);
    int indice_colonne = 0;
    int indice_ligne = 0;
    for(indice_ligne = 0; indice_ligne < 9; indice_ligne++){
        for (indice_colonne = 0; indice_colonne < 9; indice_colonne++)
        {
            printf("%d ",sudoku->tab[indice_ligne][indice_colonne]);
        }
        printf("\n");
    }
    printf("\nmetrique : %.f\n\n",sudoku->metrique);
}

Sudoku * copier_sudoku(const Sudoku * a_copier)
{
    assert(a_copier != NULL);
    Sudoku * copie = construire_sudoku();
    assert(copie != NULL);
    int indice_ligne = 0, indice_colonne = 0;
    for(indice_ligne = 0; indice_ligne < 9; indice_ligne++)
    {
        for (indice_colonne = 0; indice_colonne < 9; indice_colonne++)
        {
            copie->tab[indice_ligne][indice_colonne] = a_copier->tab[indice_ligne][indice_colonne];
        }
    }
    copie->choisi = a_copier->choisi;
    copie->metrique = a_copier->metrique;
    assert(copie != NULL);
    return copie;
}

Sudoku * generer_sudoku_base(Sudoku * sudoku)
{
    assert(sudoku != NULL);
    int indice_colonne = 0;
    int indice_ligne = 0;
    for(indice_ligne = 0; indice_ligne < 9; indice_ligne++)
    {
        for (indice_colonne = 0; indice_colonne < 9; indice_colonne++)
        {
            if (sudoku->tab[indice_ligne][indice_colonne] == 0)
            {
                sudoku->tab[indice_ligne][indice_colonne] = (rand() % 9) + 1;
            }
        }
    }
    assert(sudoku != NULL);
    return sudoku;
}

Sudoku * coupler_sudoku(Sudoku * s1, Sudoku * s2)
{
    assert(s1 != NULL && s2 != NULL);
    const int ALEATOIRE_LIGNE = (rand() % 9);
    const int ALEATOIRE_COLONNE = (rand() % 8);

    Sudoku * coupler = copier_sudoku(s2);
    assert(coupler != NULL);
    int indice_ligne = 0, indice_colonne = 0, borne = 8;

    for(indice_ligne = 0; indice_ligne <= ALEATOIRE_LIGNE; indice_ligne++)
    {
        if( indice_ligne == ALEATOIRE_LIGNE)
        {
            borne = ALEATOIRE_COLONNE;
        }

        for (indice_colonne = 0; indice_colonne <= borne; indice_colonne++)
        {
            coupler->tab[indice_ligne][indice_colonne] = s1->tab[indice_ligne][indice_colonne];
        }
    }
    s1->choisi = 1;
    s2->choisi = 1;
    assert(coupler != NULL);
    return coupler;
}

Sudoku * muter_sudoku(const Sudoku * initial, Sudoku * a_muter)
{
    assert(initial != NULL && a_muter != NULL);
    int aleatoire_ligne = 0, aleatoire_colonne = 0;
    int valeur_aleatoire = 0, valeur_point_mutation = 0;
    Sudoku * muter = copier_sudoku(a_muter);
    assert(muter != NULL);
    a_muter->choisi = 1;
    do
    {
        aleatoire_ligne = (rand() % 9);
        aleatoire_colonne = (rand() % 9);
        valeur_point_mutation = initial->tab[aleatoire_ligne][aleatoire_colonne];
    }while(valeur_point_mutation != 0);
    do
    {
        valeur_aleatoire = (rand() % 9) + 1;
    }while(muter->tab[aleatoire_ligne][aleatoire_colonne] == valeur_aleatoire);

    muter->tab[aleatoire_ligne][aleatoire_colonne] = valeur_aleatoire;
    assert(muter != NULL);
    return muter;
}
