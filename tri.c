#include "tri.h"

void echanger(Sudoku * sudoku[], const int indice1, const int indice2)
{
   Sudoku * temp;
   temp = sudoku[indice1];
   sudoku[indice1] = sudoku[indice2];
   sudoku[indice2] = temp;
}

int partition(Sudoku * sudoku[], const int debut, const int fin)
{
   int curseur = debut;
   double pivot = (sudoku[debut])->metrique;
   int indice_sudoku;

   for(indice_sudoku = debut+1; indice_sudoku <= fin; ++indice_sudoku)
   {
      if((sudoku[indice_sudoku])->metrique < pivot)
      {
         curseur++;
         echanger(sudoku, curseur, indice_sudoku);
      }
   }
   echanger(sudoku, curseur, debut);
   return curseur;
}

void tri_rapide(Sudoku * sudoku[], const int debut, const int fin)
{
   if(debut < fin)
   {
      int pivot = partition(sudoku, debut, fin);
      tri_rapide(sudoku, debut, pivot-1);
      tri_rapide(sudoku, pivot+1, fin);
   }
}

void trier(Sudoku * sudoku[], const int taille)
{
   tri_rapide(sudoku, 0, taille-1);
}
