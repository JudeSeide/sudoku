#ifndef METRIQUE_H_INCLUDED
#define METRIQUE_H_INCLUDED
#include "sudoku.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief metrique : bibliotheque de routines.
 *
 * Ce module contient toutes les routines
 * necessaires au calcul de la metrique d'un sudoku.
 * Les routines de ce module ont une cohesion fonctionnelle.
 *
 * Couplage par objet avec le module sudoku
 *
 * @author Jude Seide
 */
/*@{*/

/**
* @brief Procedure qui Calcule le nombre d'occurence de valeur dans chaque ligne du sudoku et calcule la metrique avec
* @return le resultat du calcul de la metrique pour valeur
* @param sudoku Sudoku * : le sudoku a calculer la metrique 
* @param valeur int : la valeur a rechercher le nombr d'occurence dans le sudoku
*/
double calculer_metrique_ligne(Sudoku * sudoku,const int valeur);

/**
* @brief Procedure qui Calcule le nombre d'occurence de valeur dans chaque colonne du sudoku et calcule la metrique avec
* @return le resultat du calcul de la metrique pour valeur
* @param sudoku Sudoku * : le sudoku a calculer la metrique 
* @param valeur int : la valeur a rechercher le nombr d'occurence dans le sudoku
*/
double calculer_metrique_colonne(Sudoku * sudoku,const int valeur);

/**
* @brief Procedure qui Calcule le nombre d'occurence de valeur dans la partition du sudoku et calcule la metrique avec
* @return le resultat du calcul de la metrique pour valeur
* @param sudoku Sudoku * : le sudoku a calculer la metrique 
* @param valeur int : la valeur a rechercher le nombre d'occurence dans le sudoku
* @param debut_ligne int : la ligne ou debute la partition
* @param borne_ligne int : la ligne ou finit la partition
* @param debut_colonne int : la colonne ou debute la partition
* @param borne_colonne int : la colonne ou finit la partition
*/
double calculer_metrique_partition_partiel(Sudoku * sudoku,const int valeur,const int debut_ligne,
											const int borne_ligne,const int debut_colonne,
											const int borne_colonne);

/**
* @brief Procedure qui Calcule le nombre d'occurence de valeur dans chaque chaque partition du sudoku delimite par leur bornes et calcule la metrique avec
* @return le resultat du calcul de la metrique pour valeur
* @param sudoku Sudoku * : le sudoku a calculer la metrique 
* @param valeur int : la valeur a rechercher le nombr d'occurence dans le sudoku
*/
double calculer_metrique_partition(Sudoku * sudoku,const int valeur);

/**
* @brief Procedure qui Calcule la metrique en additionnant toutes les metriques de toutes le valeurs compris entre 1 et 9 pour chaque ligne colonne et partition possible
* @param sudoku Sudoku * : le sudoku a calculer la metrique
*/
void calculer_metrique(Sudoku * sudoku);

/*@}*/

#endif // METRIQUE_H_INCLUDED
