#ifndef TRI_H_INCLUDED
#define TRI_H_INCLUDED
#include "sudoku.h"

/**
 * @brief tri : bibliotheque de routines.
 *
 * Ce module contient toutes les routines
 * necessaires pour le tri en ordre croissant
 * selon la metrique d'un tableau de sudoku. 
 * Ce module implemente un algorithme de tri rapide.
 *
 * Les routines de ce module ont une cochesion fonctionnelle.
 *
 * Couplage par objet avec le module sudoku
 *
 * @author Jude Seide
 */
/*@{*/

/**
* @brief Procedure qui Permutte les sudokus en indice1 et indice2 du tableau de sudoku
* @param sudoku Sudoku * [] : le tableau de sudoku
* @param indice1 int 
* @param indice2 int
* @pre Le sudoku ne doit pas etre a NULL, les indices doivent etre valides donc compris entre zero et la taille du tableau - 1
*/
void echanger(Sudoku * sudoku[], const int indice1, const int indice2);

/**
* @brief Fonction qui Trie une portion du tableau a l'aide du pivot
* @param sudoku Sudoku * [] : le tableau a trier
* @param debut int : l'indice de debut de la portion du tableau
* @param fin int : l'indice de fin de la portion du tableau
* @return curseur int : le nouveau pivot
* @pre Le sudoku ne doit pas etre a NULL, les indices doivent etre valides donc compris entre zero et la taille du tableau - 1
*/
int partition(Sudoku * sudoku[], const int debut, const int fin);

/**
* @brief Procedure qui Trie par appel recursif le tableau en utilisant un nouveau pivot a chaque appel
* @param sudoku Sudoku * [] : le tableau a trier
* @param debut int : l'indice du pivot dans le tableau il est a zero au premier appel
* @param fin int : l'indice de la fin de la portion du tableau a trier
* @pre Le sudoku ne doit pas etre a NULL, les indices doivent etre valides donc compris entre zero et la taille du tableau - 1
*/
void tri_rapide(Sudoku * sudoku[], const int debut, const int fin);

/**
* @brief Procedure qui fait appel au tri_rapide pour trier le tableau
* @param sudoku Sudoku * [] : le tableau a trier
* @param taille int : la taille du tableau
* @pre Le sudoku ne doit pas etre a NULL
*/
void trier(Sudoku * sudoku[], const int taille);

/*@}*/
#endif // TRI_H_INCLUDED
