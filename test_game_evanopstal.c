#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

bool test_game_new(color* cells, uint nb_moves_max) {
  game g=game_new(cells, nb_moves_max);
  if (nb_moves_max < 0 || cells == NULL) {
    return false;
  }
  for (int i = 0; i < SIZE * SIZE; i++) {
    if (cells[i] > 3 || cells[i]<0) {
      
      return false;
       
       
    }
  }
  game_delete(g);
  return true;
   
}

bool test_game_new_empty(color* cells) {
  game g = game_new_empty();
  if (game_nb_moves_max(g) != 0 || cells == NULL) {
    game_delete(g);
    return false;
  }
  for (int i = 0; i < SIZE * SIZE; i++) {
    if (cells[i] != 0) {
      game_delete(g);
      return false;
    }
  }
  game_delete(g);
  return true;
}

bool test_game_set_cell_init(game g, uint x, uint y, color c) {
  if (g == NULL || c > 3 || c < 0) {
    return false;
  }
  if (x < 0 || x > SIZE) {
    return false;
  }
  if (y < 0 || y > SIZE) {
    return false;
  }
  if (c > NB_COLORS) {
    return false;
  }
  return true;
}

int main() {
  color cells[SIZE * SIZE] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  uint nb_moves_max = 12;
  game g = game_new(cells, nb_moves_max);
  test_game_new(cells, nb_moves_max);
  test_game_new_empty(cells);
  test_game_set_cell_init(g, 1, 5, 2);
  game_delete(g);
  return EXIT_SUCCESS;
}
