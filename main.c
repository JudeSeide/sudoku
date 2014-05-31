#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "sudoku.h"
#include "metrique.h"
#include "tri.h"

/**
* @mainpage SOLVEUR DE SUDOKU
* @author SEIDE JUDE 
*
* Ce projet contient les routines necessaires a la resolution d'un sudoku.
* Le solveur va lire les informations sur le probleme dans un fichier choisi par l'utilisateur.
* Ensuite un algorithme generique sera utilise pour trouver des solutions.
* Le logiciel affiche la meilleure solution par generation.
*/

/**
* Fonction qui ouvre le fichier recu par son chemin.
* Si le fichier n'existe pas un message d'erreur est affiche et le programme se termine.
* @param chemin char* : le chemin vers le fichier
* @return fichier FILE * : le fichier ouvert
*/
FILE * fichierRecu(const char *chemin)
{
    assert(chemin != NULL);
    FILE* fichier = fopen(chemin, "r");
    if(fichier == NULL)
    {
        printf("Le fichier n'existe pas\n");
        exit(1);
    }
    return fichier;
}

/**
* Procedure qui
* Lit et valide le fichier passe en parametre
* Recupere le sudoku lu dans celui passe en parametre
* @param fichier FILE* : le fichier a lire
* @param sudoku Sudoku* : le sudoku a remplir
*/
void lireEtValiderFichier(FILE* fichier, Sudoku * sudoku)
{
    assert(sudoku != NULL);
    const char FIN_DE_LIGNE = 13; 
    int char_courant = 0;
    int indice_ligne = 0;
	int indice_colonne = -1;
    do
    {
        char_courant = fgetc(fichier);
        if(isdigit(char_courant))
        {
            if(indice_colonne < 8)
            {
                sudoku->tab[indice_ligne][++indice_colonne] = char_courant - '0';
            }
        }
        if(char_courant == FIN_DE_LIGNE)
        {
            if(indice_colonne < 8)
            {
                printf("\nLigne invalide\n");
                exit(1);
            }
            else if(indice_colonne == 8)
            {
                indice_colonne = -1;
                ++indice_ligne;
            }
        }
    }while (char_courant != EOF && indice_ligne < 9);
    fclose(fichier);
}

/**
* Procedure qui
* Genere taille sudokus aleatoirement a partir du sudoku initial
* et remplit le tableau PS avec
* @param taille int : la taille du tableau de sudoku PS
* @param PS Sudoku * [] : le tableau a remplier
* @param initial Sudoku * : le sudoku initial
*/
void generer_population_base(int taille, Sudoku * PS[],const Sudoku * initial)
{
    assert(PS != NULL && taille != 0 && initial != NULL);
    int indice_sudoku = 0;
    do
    {
        Sudoku * base = copier_sudoku(initial);
        base = generer_sudoku_base(base);
        PS[indice_sudoku] = base;
        ++indice_sudoku;
    }while(indice_sudoku < taille);
}

/**
* Procedure qui
* Genere taille sudokus aleatoirement a partir du tableau de sudoku PB
* Remplit le tableau PS avec les sudokus construit par mutation et/ou couplage
* @param int taille : la taille du tableau de sudoku PS
* @param PS Sudoku * [] : le tableau a remplier
* @param PB Sudoku * [] : le tableau pour choisir les sudoku a modifier
* @param initial Sudoku * : le sudoku initial
*/
void generer_population_suivante(int taille,Sudoku * PB[], Sudoku * PS[],const Sudoku * initial)
{
    assert(taille > 0 && PB != NULL && PS != NULL && initial != NULL);
    int indice_sudoku = 0;
    do
    {
        int nb_aleatoire = (rand() % 100);
        int nb_aleatoire2 = (rand() % 100);
        Sudoku * s1 = PB[nb_aleatoire];
        Sudoku * s2 = PB[nb_aleatoire2];
        int choix_aleatoire_methode = (rand() % 101);

        if(choix_aleatoire_methode <= 70)
        {
            Sudoku * coupler = coupler_sudoku(s1,s2);
            PS[indice_sudoku] = coupler;
        }
        else
        {
            Sudoku * muter = muter_sudoku(initial,s2);
            PS[indice_sudoku] = muter;
        }
        ++indice_sudoku;
    }while(indice_sudoku < taille);
}

/**
* Procedure qui
* Ajoute les sudokus non choisis pour mutation ou couplage au tableau
* de la nouvelle generation et ajuste sa taille
* @param taille int * : taille du tableau PS
* @param taille_b int : taille du tableau PB
* @param PB Sudoku * [] : tableau des sudokus non choisis potentiels
* @param PS Sudoku * [] : tableau des sudokus de la nouvelle generation
*/
void ajouter_sudokus_non_choisis(int *taille,int taille_b,Sudoku * PB[], Sudoku * PS[])
{
    assert(taille != NULL && PB != NULL && PS != NULL);
    int indice_non_choisis = 0;
    int indice_sudoku = 0;
    int taille_temp = *taille;
    while(indice_sudoku < taille_b)
    {
        if((PB[indice_sudoku])->choisi == 0)
        {
            PS[taille_temp + indice_non_choisis] = PB[indice_sudoku];
            ++indice_non_choisis;
        }
        ++indice_sudoku;
    }
    taille_temp += indice_non_choisis;
    *taille = taille_temp;
}

/**
* Procedure qui
* Calcule de metrique pour chaque Sudoku contenu dans le tableau PS
* @param PS Sudoku * [] : le tableau de Sudoku passe en parametre
* @param taille int : la taille du tableau PS
*/
void calculer_metrique_sudoku(Sudoku * PS[],int taille)
{
	assert(PS != NULL);
    int indice_sudoku = 0;
    for(indice_sudoku = 0; indice_sudoku < taille; ++indice_sudoku)
    {
        calculer_metrique(PS[indice_sudoku]);
    }
}

/**
* Procedure qui
* Garde les 100 meilleurs sudoku du tableau PS
* @pre le tableau PS doit etre trie en ordre croissant de metrique par sudoku pour que la selection fonctionne
* @param PS Sudoku * [] 
* @param top Sudoku * [] : le tableau a remplir avec les top 100 sudoku
* @param taille int : la taille du tableau top 
*/
void garder_top_sudoku(Sudoku * PS[], Sudoku * top[],int taille)
{
	assert(PS != NULL && top != NULL);
    int indice_sudoku = 0;
    for(indice_sudoku = 0; indice_sudoku < taille; ++indice_sudoku)
    {
        top[indice_sudoku] = copier_sudoku(PS[indice_sudoku]);
    }
}

/**
* Procedure qui
* Valide le choix au clavier de l'utilisateur
* @pre Les seuls choix possibles sont 'o' et 'n' tout autre saisi provoque l'affichage d'un message d'erreur et l'arret du programme
* @param c char 
* @return c char : le choix de l'utilisateur
*/
char lireEtValiderChoix(char c )
{
    printf("%s\n","Une autre generation ? (o/n)");
    c = getchar();
    if(c != 'o' && c != 'n')
    {
        printf("%s\n","caractere invalide");
        exit(1);
    }
    return c;
}

/**
* Le programme principal
* @pre char *argv[] != NULL
* le programme se termine sans message d'erreur si on ne lui passe pas
* exactement un argument lors de l'execution en ligne de commande
*/
int main(int argc, char *argv[])
{
    const int NB_ARGUMENT = 2;
    assert(argc == NB_ARGUMENT);

    Sudoku * initial = construire_sudoku();
    lireEtValiderFichier(fichierRecu(argv[1]),initial);

    const int MAX_POPULATION_BASE = 100;
    const int MAX_TOP_METRIQUE = 100;
    int max_population_suivante = 1000;

    Sudoku * POPULATION_BASE [MAX_POPULATION_BASE];
    Sudoku * POPULATION_SUIVANTE[max_population_suivante];
    Sudoku * TOP_100_METRIQUE[MAX_TOP_METRIQUE];

    char choix;
    int generation = 0;

    do
    {
        choix = 0;
        ++generation;

        generer_population_base(MAX_POPULATION_BASE,POPULATION_BASE,initial);
        generer_population_suivante(max_population_suivante,POPULATION_BASE,POPULATION_SUIVANTE,initial);
        ajouter_sudokus_non_choisis(&max_population_suivante,MAX_POPULATION_BASE,
                                POPULATION_BASE,POPULATION_SUIVANTE);

        calculer_metrique_sudoku(POPULATION_SUIVANTE,max_population_suivante);
        trier(POPULATION_SUIVANTE,max_population_suivante);
        garder_top_sudoku(POPULATION_SUIVANTE,TOP_100_METRIQUE,MAX_TOP_METRIQUE);

        printf("\ngeneration %d :\n\n",generation);
        afficher_sudoku(TOP_100_METRIQUE[0]);

        choix = lireEtValiderChoix(choix);
        getchar();

        liberer_sudoku(POPULATION_BASE,MAX_POPULATION_BASE);
        liberer_sudoku(POPULATION_SUIVANTE,max_population_suivante);
        liberer_sudoku(TOP_100_METRIQUE,MAX_TOP_METRIQUE);

    }while(choix == 'o');

    free(initial);

    return 0;
}
