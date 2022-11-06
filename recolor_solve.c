#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_io.h"
#include <string.h>


bool find_one_col_rec(cgame g,color * tab_col,color *  tab,uint indice,uint nb_coup){
    if((game_nb_moves_cur(g)>nb_coup)){
            return false;
    }
    if(game_is_over(g)){
        return true ;
    }
    for(uint i=0;i<16 ;i++){
        if(tab_col[i] != game_cell_current_color(g,0,0)){
            game g_copy = game_copy(g);
            tab[indice] = tab_col[i];
            tab[indice+1] = '\0';
            game_play_one_move(g_copy,tab_col[i]);
            if(find_one_col_rec(g_copy,tab_col,tab,indice+1,nb_coup)){
                game_delete(g_copy);
                return true;
            }
            
            
            game_delete(g_copy);
        }
    }
    return false;
}



bool find_one_col(cgame g,color * tab_col,color *  tab,uint indice, uint nb_coup ){
    return find_one_col_rec(g,tab_col,tab,indice,nb_coup);
}
/*
color color_count(char * game ){
    FILE* file = fopen(game,"w");
    color tab_col[hauteur*largeur];
    uint nb;
    for(uint i=0 ; i< game_width(g)*game_height(g) ; i++){
        fscanf(file,"%d",&nb);
        tab_col[i]=nb;
    }

}
*/
void find_one(char* filename_pb, char* filename_save){
    game g = game_load(filename_pb);

    FILE* file_save = fopen(filename_save,"w");
    color  tab[game_nb_moves_max(g)+1];
    tab[0] = '\0';
    color tab_col[16]={0,1,2,3,4,5,6,7,8,9,65,66,67,68,69,70};
    bool sol ;
    sol = find_one_col(g,tab_col,tab,0,game_nb_moves_max(g));
    if(sol){
        for(uint i = 0 ; i < game_nb_moves_max(g) || tab[i] ==  '\0'; i++  ){
            fprintf(file_save,"%d ",tab[i]);
        }
    }else{
        fprintf(file_save,"NO SOLUTION\n");
    }
    fclose(file_save);
}


void rec_nb_sol(game g, uint * tab_col ,uint *compteur){
    if((game_nb_moves_cur(g)>game_nb_moves_max(g))){
        return;
    }
    if(game_is_over(g)){
        compteur=compteur +1;
        return;
    }
    for(uint i=0;i<16 ;i++){
        if(tab_col[i] != game_cell_current_color(g,0,0)){
            game g_copy = game_copy(g);
            game_play_one_move(g_copy,tab_col[i]);
            rec_nb_sol(g_copy,tab_col,compteur);
            game_delete(g_copy);
        }
    }

}

void nb_sol(char * file,char* file_load){
    uint *compteur=0; // the variable wich stocks the result of rec
    uint tab[16]={0,1,2,3,4,5,6,7,8,9,65,66,67,68,69,70};// all the colours
    game g= game_load(file_load);
    rec_nb_sol(g,tab,compteur);
    FILE* fic = fopen(file,"w");
    if(fic == NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(fic,"NB_SOL = %u\n",*compteur);
    fclose(fic);
}



void find_min(char* file,char* filesave){
    game g = game_load(file);
    FILE* file_save = fopen(filesave,"w");
    color tab_col[16]={0,1,2,3,4,5,6,7,8,9,65,66,67,68,69,70};
    color  tab[game_nb_moves_max(g)+1];
    bool sol ;
    for(uint i = 1 ; i < game_nb_moves_max(g)  ;i++){
        sol = find_one_col(g ,tab_col,tab,0,i) ;
        if(sol){
            break;
        }
    }

    if (sol){
        for(uint i = 0 ; i < game_nb_moves_max(g); i++  ){
            fprintf(file_save,"%d ",tab[i]);
            }
    }else{
        fprintf(file_save,"NO SOLUTION\n");
    }
    fclose(file_save);
}



int main(int  argc, char ** argv){
    if(argc==4){
        printf(" le argc est %d\n",argc);
        if(strcmp( argv[1], "FIND_ONE" ) == 0 ){
            find_one(argv[2],argv[3]);
        }
        if(strcmp( argv[1], "NB_SOL" ) == 0 ){
            nb_sol(argv[2],argv[3]);
        }
        if(strcmp( argv[1], "FIND_MIN" ) == 0 ){
            find_min(argv[2],argv[3]);
        }
    }
else{
            fprintf(stderr,"Wrong Arguments\n");
        }
    return EXIT_SUCCESS;

}
