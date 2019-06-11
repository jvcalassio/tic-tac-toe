/*
 * Jogo da velha simples, player vs player ou player vs PC
 * Desenvolvido por Joao Victor Calassio
 * https://github.com/jvcalassio
 */
#include <iostream>
#include <stdlib.h>
#include "Game.hpp"
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

int main() {
    Game maingame;
    maingame.start();
    int x = 1;
    while(x){
        system(CLEAR);
        maingame.print();
        int winner = maingame.winner();
        if(winner == 0){
            char coord[] = "Z4";
            while(maingame.check_pos(coord[0],coord[1]) == false){
                printf("\nInsira as coordenadas desejadas: ");
                scanf("%s",coord);
            }
            maingame.place(coord[0],coord[1]);
            maingame.IA(); // comentar essa linha pra jogar player vs player
        } else {
            if(winner == 3)
                printf("\nDeu velha!\n");
            else 
                printf("\nVencedor: Player %d\n",winner);
            x = 0;
        }
    }
    return 0;
}