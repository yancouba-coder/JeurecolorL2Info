#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.c"

bool test_game_set_max_moves(game g, uint nb_max_moves) {
  game_set_max_moves(g, nb_max_moves);
  if(game_nb_moves_max(g) != nb_max_moves){
    return false;
  }
  
  
  /*if (game_is_over(g) == false) {
    fprintf(stderr, "Error : wrong set of nb_move_max\n");
    return false;
  }*/
  return true;
}

bool test_game_nb_moves_max(cgame g, uint nb_max_moves) {
  if (nb_max_moves != game_nb_moves_max(g)) {
    fprintf(stderr, "Error : invalid nb_move_max\n");
    return false;

  }
  return true;
}


bool test_game_cell_current_color(cgame g, color col[]) {
  int i = 0;
  int x = 0;
  int y = 0;

  while (i < SIZE * SIZE) {
    if (game_cell_current_color(g, x, y) != col[i]) {
      fprintf(stderr, "Error : invalid color in cell %u %u\n", x, y);
      return false;
    }
    i = i + 1;
    x = x + 1;
    if (x == 12) {
      y = y + 1;
      x = 0;
    }
  }
  return true;
}

bool test_game_load(game g, char *filename){
  
  game g_load = game_load(filename);
  if(g==NULL){
    return false;
  }
  if ( (  game_nb_moves_max(g)!= game_nb_moves_max(g_load) ) || (game_height(g)!= game_height(g_load) ) || 
  (game_width(g)!=game_width(g_load)) || (game_is_wrapping(g) != game_is_wrapping(g_load)) ){
    return false;
  }
  for(uint i=0;i<game_height(g);i++){
    for(uint j=0;j<game_width(g);j++){
      if(game_cell_current_color(g,i,j)!=game_cell_current_color(g_load,i,j))
      game_delete(g);
      return false;
    }
  }
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
  uint nb_max_moves = 12;
  bool test_ok = false;
  uint sol[12] = {3, 1, 3, 1, 0, 3, 1, 0, 1, 3, 2, 0};

  test_ok = test_game_nb_moves_max(g, nb_max_moves);
  if (test_ok) {
    fprintf(stderr, "test 1 finished : Success\n");
  } else {
    fprintf(stderr, "test 1 finished : Failed\n");
  }
  test_ok = test_game_cell_current_color(g, col);
  if (test_ok) {
    fprintf(stderr, "test 2 finished : Success\n");
  } else {
    fprintf(stderr, "test 2 finished : Failed\n");
  }
  for (int i = 0; i < 12; i++) {
    game_play_one_move(g, sol[i]);
  }
  test_ok = test_game_set_max_moves(g, nb_max_moves);

  if (test_ok) {
    fprintf(stderr, "test 3 finished : Success\n");
    
  } else {
    fprintf(stderr, "test 3 finished : Failed\n");
    
  }

   test_ok = test_game_load(g, "../data/default_game.rec");

  if (test_ok) {
    fprintf(stderr, "test 3 finished : Success\n");
    
  } else {
    fprintf(stderr, "test 3 finished : Failed\n");
    
  }



  game_delete(g);
  return EXIT_SUCCESS;
}
