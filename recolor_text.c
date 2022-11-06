#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.c"
// eloise
//yancouba
//aboubacar
//hichem
void print_game(game g){
    printf("nb coups joués : %d ; nb coups max : %d\n",game_nb_moves_cur(g),game_nb_moves_max(g));
    for(int y=0;y<g->height;y=y+1){
        for(int x=0;x<g->width;x++){
            if((game_cell_current_color(g,x,y) >='A')&&(game_cell_current_color(g,x,y)<='F')){
                printf("%c",game_cell_current_color(g,x,y));
            }else{
                printf("%u",game_cell_current_color(g,x,y));
            }
    }
    printf("\n");
        }
            }

int main(int  argc, char ** argv){
    color col[SIZE*SIZE]={0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    game g = NULL;
    if(argc > 1 ){
        printf("le jeu sera chargé à partir d'un fichier\n");
         g = game_load(argv[1]);
    }else{
         g = game_new(col,12);
    }
    if(g == NULL){
        exit(EXIT_FAILURE);
    }
    while(!game_is_over(g)){
    if((game_nb_moves_cur(g)>game_nb_moves_max(g))){
        printf("DOMMAGE\n");
        game_delete(g);
        exit(EXIT_SUCCESS);
    }
    print_game(g);
    printf("Jouer un coup: ( 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,r ou q ;  r pour redémarrer ou q pour quitter)\n");
    bool valid=false;
    while(!valid){
    int c=getchar();
    if(c =='r'){
        game_restart(g);
        valid=true;
    }
    if((c=='q')){
        printf("DOMMAGE\n");
        game_save(g,argv[1]);
        game_delete(g);
        valid=true;
        exit(EXIT_SUCCESS);
            }
    if((c>='0')&&(c<='9')){
        game_play_one_move(g,c-'0');
                        valid=true;
                    }
            int tab[6]={65,66,67,68,69,70};
    if((c >='A')&&(c<='F')){
         int n=tab[ c %'A'];
                 game_play_one_move(g,n);
                        valid=true;

    }
        }

    }
    print_game(g);
    printf("BRAVO\n");
    game_save(g,argv[1]);
    game_delete(g);
    return EXIT_SUCCESS;
}
