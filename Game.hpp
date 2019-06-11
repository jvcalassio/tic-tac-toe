class Game {
    private:
        int matrix[3][3];
        int curr_player;
        bool check_pos_int(int x, int y);
        void place_int(int x, int y);

    public:
        Game();
        void start();
        void print();
        bool check_pos(char a, char b);
        void place(char a, char b);
        int winner();
        void IA();
};

// constructor
Game::Game(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            matrix[i][j] = 0;
        }
    }

    curr_player = 1;
}

// reinicia jogo
void Game::start(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            matrix[i][j] = 0;
        }
    }

    curr_player = 1;
}

// imprime tabuleiro na tela
void Game::print(){
    printf("  1 2 3\n");
    for(int i=0;i<3;i++){
        printf("%c",i+'A');
        for(int j=0;j<3;j++){
            if(matrix[i][j] == 0){
                printf("  ");
            } else if(matrix[i][j] == 1){
                printf(" X");
            } else if(matrix[i][j] == 2){
                printf(" O");
            }
        }
        printf("\n");
    }
}

// verifica se a posicao desejada pode receber uma jogada
bool Game::check_pos_int(int x, int y){
    if(x > 2 || x < 0 || y > 2 || y < 0 || matrix[x][y] != 0){
        return false;
    } else {
        return true;
    }
}

// verifica se a posicao desejada pode receber uma jogada auxiliar, com char
bool Game::check_pos(char a, char b){
    if(a >= 'a' && a <= 'z'){
        a -= 32;
    }
    int x = a - 'A'; // y correspondente
    int y = b - '0' - 1; // x correspondente
    return check_pos_int(x,y);
}

// faz uma jogada na coord A x B
void Game::place_int(int x, int y){
    if(!check_pos_int(x,y)) // so insere se posicao valida
        return;

    matrix[x][y] = curr_player;
    curr_player == 1 ? curr_player = 2 : curr_player = 1;
}

// faz uma jogada na coord A x B auxiliar, com char
void Game::place(char a, char b){
    if(a >= 'a' && a <= 'z'){
        a -= 32;
    }
    int x = a - 'A'; // y correspondente
    int y = b - '0' - 1; // x correspondente
    place_int(x,y);
}

// verifica se alguem ganhou o jogo
int Game::winner(){
    // verifica linhas
    for(int i=0;i<3;i++){
        if(matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2])
            return matrix[i][0];
    }
    // verifica colunas
    for(int i=0;i<3;i++){
        if(matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i])
            return matrix[0][i];
    }
    // verifica diagonais
    if(matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2])
        return matrix[0][0];
    if(matrix[0][2] == matrix[1][1] && matrix[0][2] == matrix[2][0])
        return matrix[0][2];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matrix[i][j] == 0)
                return 0;
        }
    }
    return 3;
}

// realiza jogadas do PC
// calcular pontos para cada possivel posicao escolhida pelo pc e realiza a jogada nessa posicao
// pc sempre eh o jogador 2
void Game::IA(){
    if(winner() != 0) // verifica se o player venceu nessa rodada, se venceu, nao joga
        return;

    int position_points[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            position_points[i][j] = 0;
        }
    }

    // Verificacao das posicoes horizontais
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(check_pos_int(i,j)){
                if(j == 0 && matrix[i][j+1] == matrix[i][j+2] && matrix[i][j+1] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i][j+1] == 2){
                        position_points[i][j] += 5;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(j == 1 && matrix[i][j+1] == matrix[i][j-1] && matrix[i][j+1] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i][j+1] == 2){
                        position_points[i][j] += 5;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(j == 2 && matrix[i][j-1] == matrix[i][j-2] && matrix[i][j-1] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i][j-1] == 2){
                        position_points[i][j] += 5;
                    } else {
                        position_points[i][j] += 2;
                    }
                }

                if(j == 0 && ((matrix[i][j+1] == 2 && matrix[i][j+2] == 0) || (matrix[i][j+2] == 2 && matrix[i][j+1] == 0)))
                    position_points[i][j] += 2;
                if(j == 1 && ((matrix[i][j+1] == 2 && matrix[i][j-1] == 0) || (matrix[i][j-1] == 2 && matrix[i][j+1] == 0)))
                    position_points[i][j] += 2;
                if(j == 2 && ((matrix[i][j-1] == 2 && matrix[i][j-2] == 0) || (matrix[i][j-2] == 2 && matrix[i][j-1] == 0)))
                    position_points[i][j] += 2;

                if((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 2)){
                    position_points[i][j] += 1;
                }
                if(i == 1 && j == 1){
                    position_points[i][j] += 2;
                }
            } else {
                position_points[i][j] = -1;
            }
        }
    }

    // Verificacao das posicoes verticais
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(check_pos_int(i,j)){
                if(i == 0 && matrix[i+1][j] == matrix[i+2][j] && matrix[i+1][j] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i+1][j] == 2){
                        position_points[i][j] += 5;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(i == 1 && matrix[i+1][j] == matrix[i-1][j] && matrix[i+1][j] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i+1][j] == 2){
                        position_points[i][j] += 5;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(i == 2 && matrix[i-1][j] == matrix[i-2][j] && matrix[i-1][j] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i-1][j] == 2){
                        position_points[i][j] += 5;
                    } else {
                        position_points[i][j] += 2;
                    }
                }

                if(i == 0 && ((matrix[i+1][j] == 2 && matrix[i+2][j] == 0) || (matrix[i+2][j] == 2 && matrix[i+1][j] == 0)))
                    position_points[i][j] += 2;
                if(i == 1 && ((matrix[i+1][j] == 2 && matrix[i-1][j] == 0) || (matrix[i-1][j] == 2 && matrix[i+1][j] == 0)))
                    position_points[i][j] += 2;
                if(i == 2 && ((matrix[i-1][j] == 2 && matrix[i-2][j] == 0) || (matrix[i-2][j] == 2 && matrix[i-1][j] == 0)))
                    position_points[i][j] += 2;
            } else {
                position_points[i][j] = -1;
            }
        }
    }

    // Verificacao das posicoes das diagonais
    if(check_pos_int(0, 0)){
        if(matrix[1][1] == matrix[2][2] && matrix[1][1] != 0){
            position_points[0][0] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    if(check_pos_int(2, 2)){
        if(matrix[1][1] == matrix[0][0] && matrix[1][1] != 0){
            position_points[2][2] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    if(check_pos_int(1, 1)){
        // diagonal principal
        if(matrix[0][0] == matrix[2][2] && matrix[0][0] != 0){
            position_points[1][1] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
        // diagonal secundaria
        if(matrix[0][2] == matrix[2][0] && matrix[0][2] != 0){
            position_points[1][1] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }
    if(check_pos_int(0, 2)){
        if(matrix[1][1] == matrix[2][0] && matrix[1][1] != 0){
            position_points[0][2] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    if(check_pos_int(2, 0)){
        if(matrix[1][1] == matrix[0][2] && matrix[1][1] != 0){
            position_points[2][0] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    // excessoes de casos especificos
    if(check_pos_int(0, 0)){
        if(matrix[1][0] == 1 && matrix[0][1] == 1)
            position_points[0][0] += 5;
    }
    if(check_pos_int(0, 2)){
        if(matrix[0][1] == 1 && matrix[1][2] == 1)
            position_points[0][2] += 5;
    }
    if(check_pos_int(2, 0)){
        if(matrix[1][0] == 1 && matrix[2][1] == 1)
            position_points[2][0] += 5;
    }
    if(check_pos_int(2, 2)){
        if(matrix[1][2] == 1 && matrix[2][1] == 1)
            position_points[2][2] += 5;
    }

    // Verifica qual posicao tem mais pontos, e joga nela
    int x_best = -1, y_best = -1;
    int best = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(position_points[i][j] > best){
                best = position_points[i][j];
                x_best = j;
                y_best = i;
            }
        }
    }
    // se nenhuma posicao tiver pontos > 0, escolhe a primeira com 0 pontos
    if(best == 0){
        for(int i=0;i<3 && x_best == -1;i++){
            for(int j=0;j<3 && x_best == -1;j++){
                if(position_points[i][j] == 0){
                    best = position_points[i][j];
                    x_best = j;
                    y_best = i;
                }
            }
        }
    }
    place_int(y_best, x_best);

    /*
     * Printa matriz de pontos de posicao
     * Apenas para debug
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",position_points[i][j]);
        }
        printf("\n");
    }
    */
}