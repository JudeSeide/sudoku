#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief sudoku : Classe d'objets.
 *
 * Ce module sert a definir un sudoku et contient les routines
 * definissant les operations sur un sudoku.
 *
 * Les routines de ce module ont une cohesion procedurale.
 *
 * @author Jude Seide
 */
/*@{*/

/**
* @brief Definition de la structure de sudoku
*/
typedef struct
{
    /**	
    * une grille de 9*9 ( tableau d'entier )
    */
    int tab[9][9];
    /**
    * un indice sur un choix eventuel du sudoku
    */
    int choisi ;
    /**    
    * la metrique du sudoku
    */
    double metrique;
}Sudoku;

/**
* Procedure
* @brief Allocation de la memoire necessaire pour construire un Sudoku Initialisation des champs de la structure
* @return resulat Sudoku * : le Sudoku construit
*/
Sudoku * construire_sudoku(void);

/**
* Procedure
* @brief Liberation de la memoire occupee par un tableau de Sudoku
* @param sudoku Sudoku * [] : le tableau a desallouer
* @param taille int : la taille de ce tableau
*/
void liberer_sudoku(Sudoku * sudoku[],const int taille);

/**
* Procedure 
* @brief Affiche un Sudoku de 9 lignes et 9 colonnes separes par des espaces
* @param sudoku Sudoku * : le Sudoku a afficher
*/
void afficher_sudoku(const Sudoku * sudoku);

/**
* Procedure 
* @brief Cree une copie du sudoku a copier
* @param a_copier Sudoku * : le Sudoku a copier
* @return copie Sudoku * : la copie cree
*/
Sudoku * copier_sudoku(const Sudoku * a_copier);

/**
* Procedure
* @brief Genere aleatoirement un Sudoku a partir du	Sudoku sudoku sans modifier les cases non nuls
* @param sudoku Sudoku * : le Sudoku de base
* @return sudoku Sudoku * : le Sudoku genere
*/
Sudoku * generer_sudoku_base(Sudoku * sudoku);

/**
* Procedure
* @brief Determine aleatoirement un point de couplage entre les	Sudoku s1 s2 et effectue le couplage
* @param s1 Sudoku *
* @param s2 Sudoku *
* @return coupler Sudoku * : le Sudoku couple
*/
Sudoku * coupler_sudoku(Sudoku * s1, Sudoku * s2);

/**
* Procedure
* @brief Determine aleatoirement un point de mutation tel que ce point soit	une case vide (0) du Sudoku initital Effectue une mutation en generant aleatoirement une nouvelle valeur en ce point du Sudoku a_muter
* @param initial Sudoku * : le sudoku initial
* @param a_muter Sudoku * : le sudoku a muter
* @return muter Sudou * : le sudoku muter
*/
Sudoku * muter_sudoku(const Sudoku * initial, Sudoku * a_muter);

/*@}*/
#endif // SUDOKU_H_INCLUDED
