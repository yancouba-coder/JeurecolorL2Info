#ifndef SOLVE_H
#define SOLVE_H
#include <stdio.h>
#include "game.h"
#include "game_io.h"
/***

For this rendering, you must generate a new recolor_solve executable which must be able to be launched as follows:

recolor_solve FIND_ONE | NB_SOL | FIND_MIN <pb_fichier_pb> <prefix_fichier_sol>
the first parameter lets you choose the functionality of the program;
the second parameter corresponds to the name of the file containing the instance of the problem to be solved;
the third parameter corresponds to the prefix of the file (s) containing the result of the call to this program. (The extension depends on the type of solution.)
Here is the description of the three requested features:

The format of the solution files is very simple: it is a text file containing the list of played color numbers separated by spaces. 
Examples are provided in the previous section.



FIND_ONE: the program makes it possible to calculate a solution (if it exists) with the problem stored in the file <pn_fichier_pb>. 
If a solution exists, it will be stored in the file <prefix_fichier_sol> .sol. 
If no solution exists, then the file <prefix_fichier_sol> .
sol simply contains the following text "NO SOLUTION \ n".
*/

void find_one(char* first_file_to_solve, char* file_sol_saver);

/*
NB_SOL: the program written in the file <prefix_fichier_sol> .nbsol "NB_SOL = <nb_sol> \ n", 
where <nb_sol> is the number of solutions of the instance passed in parameter. 
NB: Here we only want "minimal" solutions (but not necessarily minimum length). 
So if the maximum number of moves is 4, and the sequence "1 3 2" is a solution. 
We will not consider the suffixes of this solution ("1 3 2 3", "1 3 2 1", ...).
*/

void nb_sol(char* file_to_write);

/*
FIND_MIN: the program makes it possible to calculate a solution with the smallest number of movements 
with the problem stored in the file <fomename_pb>. 
The solution will be stored in the file <prefix_fichier_sol> .sol.
*/

void find_min(char* first_file_to_solve,char* file_sol_saver);

