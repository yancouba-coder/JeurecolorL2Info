#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


color col[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

bool test_game_delete() {
  game g=game_new(col,SIZE);
  game g_2 = game_copy(g);
  game_delete(g);
  if (g == g_2) {
    fprintf(stderr, "Error in game_delete");
    return false;
  }
  
   game_delete(g_2);
  return true;
  
};

bool test_game_is_over(cgame g, color *cell, uint nb_moves_max) {
  bool game = game_is_over(g);
  bool test;
  for (int i = 0; i < SIZE*SIZE; i++) {
    if (cell[i] != cell[1]) {
      test = false;
    }
  }
  if (test != game) {
    fprintf(stderr, "Error in game_is_over");
    return false;
  }
  if ((test) && (game_nb_moves_cur(g) != nb_moves_max)) {
    fprintf(stderr, "Error in game_is_over");
    return false;
  }
  return true;
}

bool test_game_restart() {
  game s=game_new(col,SIZE);
  if(s==NULL){
    fprintf(stderr,"Mauvais pointeur");
  }
  
  game_play_one_move(s,BLUE);
  game_restart(s);

  if(game_nb_moves_cur(s)!=0){
    

    return false;
}
  for(uint i=0;i<12;i++){
    for(uint j=0;j<12;j++){
      if(game_cell_current_color(s,i,j)!=col[i+ (j*(SIZE-1))])
      
      return false;
    }
  }

game_delete(s);
return true;
  /*game_restart(g);
  int i = 0;
  
  int y = 0;

  while (i < SIZE * SIZE) {
    if (game_cell_current_color(g, x, y) != col[i]) {
      fprintf(stderr, "Error in game_restart");
      return false;
    }
    i = i + 1;
    x = x + 1;
    if (x == 12) {
      y = y + 1;
      x = 0;
    }
  }
  if (game_nb_moves_cur(g) != 0) {
    fprintf(stderr, "Error in game_restart");
    return false;
  }
  return true;*/
}
bool test_game_height(){
  game g=game_new(col,BLUE);

  if(game_height(g)!=SIZE){
    fprintf(stderr,"error de game height ");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;

}

bool test_game_width(){
  game g=game_new(col,BLUE);
  if(game_width(g)!=SIZE){
    fprintf(stderr,"Erreur de game_height");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}


int main(void) {
  color col[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(col, 12);
  uint nb_moves_max = 12;
   if (test_game_restart()){
    printf("test_game_restart   est bien passé\n");
    }
    else{
      printf("test_game_restart    s'est mal passé corrige !\n");


    }
    if(test_game_height()){
      printf("test_game_height s'est bien passé\n");
    }
    else{
      printf("test_game_height s'est mal passé corrige !\n");
    }
    if(test_game_width()){
      printf("test_game_witdh s'est bien passé\n");
    }
    else{
      printf("test_game_width s'est mal passé corrige  !\n");
    }
    
  if (test_game_is_over(g, col, nb_moves_max)&& test_game_delete()) {
     printf("test_game_is_over(g, col, nb_moves_max)&& test_game_delete()  se sont bien passé");
    
     
  } else {
    printf("test_game_is_over(g, col, nb_moves_max)&& test_game_delete()  se sont mal bien passé");
     
  }
  game_delete(g);
  return EXIT_SUCCESS;
}