#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include"game_io.h"

color col[SIZE * SIZE] = {
    0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
    1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
    2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
    1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
    0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
    1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};


/**********TEST DE GAME PLAY ONE MOVE*****************/
bool test_game_play_one_move() {
  
  game g_wrap = game_new_ext(SIZE, SIZE, col, 12,true );

  
  game_play_one_move(g_wrap, 0);
  if ( game_cell_current_color(g_wrap,0,0)!= 0)  {
    
    
    return false;
  }

  
  game_play_one_move(g_wrap, 1);
  if (game_cell_current_color(g_wrap, 0, 0) != 1 ) {
    
    
    return false;
  }

  
  game_play_one_move(g_wrap, 2);
  if ( (game_cell_current_color(g_wrap, 0, 0) != 2) ) {
    
    
    return false;
  }

  

  srand(time(NULL));
  int c = rand() % 3;
  
  game_play_one_move(g_wrap, c);
  if  (game_cell_current_color(g_wrap, 0, 0) != c){
    
    game_delete(g_wrap);
    return false;
  }
  game_delete(g_wrap);
  return true;
}

/*********TEST NB MOVES****/

bool test_game_nb_moves_cur() {
  game g = game_new(col, SIZE);

  uint c = game_nb_moves_cur(g);
  if (c < 0 || c > SIZE * SIZE) {
    fprintf(stderr, "Error : invalid queue!\n");
    
    return false;
  }
  if (game_nb_moves_cur(g) > game_nb_moves_max(g) && game_is_over(g)) {
    fprintf(stderr, "Error game_nb_move_cur");
    
    return false;
  }
  game g2 = game_new_empty();
  if (game_nb_moves_cur(g2) != 0) {
    
    return false;
  }
  game_delete(g);
  game_delete(g2);

  return true;
}

/******************** TEST DE GAME COPY********/

bool test_game_copy() {
  game t = game_new(col, 10);
  game_set_cell_init(t, 5, 5, 3);
  game_set_max_moves(t, 13);
  game_play_one_move(t, 3);
  game gom = game_copy(t);

  if (gom == NULL) {
    fprintf(stderr, "Error : invalid game_copy\n");
    
    printf("Eroor ");
    return false;
  }
  if (game_nb_moves_max(t) != game_nb_moves_max(gom)) {
    fprintf(stderr, "Error : invalid game_copy\n");
    
    printf("Errreur ");
    return false;
  }
  if (game_nb_moves_cur(t) != game_nb_moves_cur(gom)) {
    
    printf("erreur");
    return false;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++)
      if (game_cell_current_color(t, i, j) !=
              game_cell_current_color(gom, i, j) ||
          game_cell_current_color(gom, i, j) < 0 ||
          game_cell_current_color(gom, i, j) > 3) {

        return false;
      }
  }
  game_delete(t);
        game_delete(gom);

  game vide = game_new_empty();
  game ga = game_copy(vide);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (game_cell_current_color(ga, i, j) != 0) {
        fprintf(stderr, "Error : invalid game");

  

        printf("Erreur");
        return false;
      }
    }
  }
  if (game_nb_moves_max(ga) != 0) {
    fprintf(stderr, "Error of copie");
    
    return false;
  }
game_delete(ga);
    game_delete(vide);

  return true;
}

/*********** TEST_GAME_NEW_EXT********/
bool test_game_new_empty_ext(){

  game g=game_new_empty_ext(12,12,true);


  if(g==NULL){
    exit(EXIT_FAILURE); 
  }

  for(uint i=0;i<12;i++){
    for(uint j=0;j<12;j++){
      if(game_cell_current_color(g,i,j)!=RED)
      game_delete(g);
      return false;
    }
  }
  
  if(game_height(g)!=12||game_width(g)!=12){
    game_delete(g);
    return false;
  }
  
  
  if(game_is_wrapping(g)!=true){
    game_delete(g);
    return false;
  }
  
  
  if(game_nb_moves_max(g)!= 0)
  {    
    game_delete(g);
         return false;
  } 
  game_delete(g);
  return true;
}
/***********TEST GAME WRAPPING***************************/
bool test_game_is_wrapping(){
  game g =game_new_empty_ext(12,12,true);
  if(game_is_wrapping(g)) 
  {game_delete(g);
  return true ;}
  else {
    game_delete(g);
    return false;
  }
}
/************************TEST_GAME_SAVE*********************/
bool test_game_save(char* filename){
  bool tr=true;
  game g=game_new_ext(12,12,col,12,tr); //on créé un nouveau jeu
game_save(g,filename);//je sauvegarde le jeu dans le fichier

game g_3=game_load(filename);//je recharge le jeux sauvé
 if(g==NULL){
   return false;
 }
if(game_width(g_3)!=game_width(g)||game_height(g_3)!=game_height(g)||game_is_wrapping(g)!=game_is_wrapping(g_3)){
  game_delete(g);
return false;
}
for(uint i=0;i<game_height(g);i++){
    for(uint j=0;j<game_width(g);j++){
      if(game_cell_current_color(g,i,j)!=game_cell_current_color(g_3,i,j))
      game_delete(g);
      return false;
    }
  }
  game_delete(g);
  game_delete(g_3);

return true;
}
/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
  bool test = false ;
  
  bool test5=test_game_save("../data/fichieDeTexte.rec");
  if(test5){
    printf("test_game_save :succes :OK\n");
  }
  else{
   printf("test_game_save:failed\n");
  }

  test =test_game_nb_moves_cur();
  if(test){
    printf("test 1 : OK\n");
  }else{
    printf("Test 1 : Error\n");
  }
    test =test_game_play_one_move();
  if(test){
    printf("test 2 : OK\n");
  }else{
    printf("Test 2 : Error\n");
  }
    test =test_game_copy();
  if(test){
    printf("test 3 : OK\n");
  }else{
    printf("Test 3 : Error\n");
  }
  test=test_game_new_empty_ext();
  if(test){
    printf("test_game_new_empty_ext reussi\n");
  }
  else{
    printf("test_game_new_empty_ext:FAILED\n");

  }
  bool test1=test_game_is_wrapping();
  if(test1){
    printf("game_iswrapping s'est bien passé\n");
  }
  else{
    printf("game_is_wrapping s'est bien passé\n");
  }
  
  
}
