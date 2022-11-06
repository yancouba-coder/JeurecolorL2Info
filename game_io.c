#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game.c"
#include "game_io.h"
game game_load(char *filename) {

    FILE * file = NULL;
    file = fopen(filename,"r");
    if(file == NULL){
        exit(EXIT_FAILURE);
    }

    char is_swap='0';
    bool dad=false;
    uint he=0;
    uint wid=0;
    uint nb_m=0;
    fscanf(file,"%d %d %d %c\n" , &wid , &he , &nb_m, &is_swap );
    if(is_swap == 'S'){
    dad=true;
    }
    color nb=0;
    color cel[wid * he]; //le tabelau
    
    for(uint i=0 ; i< wid*he ; i++){
        fscanf(file,"%d",&nb);
        cel[i]=nb;//on remplie les cases du tableau à partir du fichier
    }
    game g=game_new_ext(wid,he,cel,nb_m,dad);  //la fonction game_new se charge de cherger le jeu sur le fichier
    fclose(file);
    return g;
}

void game_save(cgame g, char *filename) {
    FILE* fic = fopen(filename,"w");
    if(fic == NULL){
        exit(EXIT_FAILURE);
    }
    char swap = 'N';
    if(game_is_wrapping(g)){
        swap = 'S';
    }
    fprintf (fic,"%d %d %d %c\n", g->width, g->height, g->move_max , swap);
    
    for(int y=0;y<=(g->height -1);y=y+1){
        for(int x=0;x<=(g->width-1);x++){
            
            if(x==(g->width -1)){
                fprintf(fic,"%u",game_cell_current_color(g,x,y));

            }
            else{
            fprintf(fic,"%u ",game_cell_current_color(g,x,y));
             }
        }
        fprintf(fic,"\n");
     }
    
   
        
    fclose(fic);
}