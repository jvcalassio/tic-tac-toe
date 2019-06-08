class Game {
    private:
        int matrix[3][3];
        int curr_player;

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
bool Game::check_pos(char a, char b){
    if(a >= 'a' && a <= 'z'){
        a -= 32;
    }
    int x = a - 'A'; // y correspondente
    int y = b - '0' - 1; // x correspondente
    if(matrix[x][y] != 0 || x > 2 || x < 0 || y > 2 || y < 0){
        return false;
    } else {
        return true;
    }
}
// faz uma jogada na coord A x B
void Game::place(char a, char b){
    if(a >= 'a' && a <= 'z'){
        a -= 32;
    }
    int x = a - 'A'; // y correspondente
    int y = b - '0' - 1; // x correspondente
    matrix[x][y] = curr_player;
    curr_player == 1 ? curr_player = 2 : curr_player = 1;
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
    int position_points[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            position_points[i][j] = 0;
        }
    }

    // Verificacao das posicoes horizontais
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(check_pos(i+'A', j+'0'+1)){
                if(j == 0 && matrix[i][j+1] == matrix[i][j+2] && matrix[i][j+1] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i][j+1] == 2){
                        position_points[i][j] += 3;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(j == 1 && matrix[i][j+1] == matrix[i][j-1] && matrix[i][j+1] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i][j+1] == 2){
                        position_points[i][j] += 3;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(j == 2 && matrix[i][j-1] == matrix[i][j-2] && matrix[i][j-1] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i][j-1] == 2){
                        position_points[i][j] += 3;
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
            if(check_pos(i+'A', j+'0'+1)){
                if(i == 0 && matrix[i+1][j] == matrix[i+2][j] && matrix[i+1][j] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i+1][j] == 2){
                        position_points[i][j] += 3;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(i == 1 && matrix[i+1][j] == matrix[i-1][j] && matrix[i+1][j] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i+1][j] == 2){
                        position_points[i][j] += 3;
                    } else {
                        position_points[i][j] += 2;
                    }
                }
                if(i == 2 && matrix[i-1][j] == matrix[i-2][j] && matrix[i-1][j] != 0){
                    position_points[i][j] += 5;
                    if(matrix[i-1][j] == 2){
                        position_points[i][j] += 3;
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
    if(check_pos(0 + 'A', 0 + '0' + 1)){
        if(matrix[1][1] == matrix[2][2] && matrix[1][1] != 0){
            position_points[0][0] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    if(check_pos(2 + 'A', 2 + '0' + 1)){
        if(matrix[1][1] == matrix[0][0] && matrix[1][1] != 0){
            position_points[2][2] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    if(check_pos(1 + 'A', 1 + '0' + 1)){
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
    if(check_pos(0 + 'A', 2 + '0' + 1)){
        if(matrix[1][1] == matrix[2][0] && matrix[1][1] != 0){
            position_points[0][2] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    if(check_pos(2 + 'A', 0 + '0' + 1)){
        if(matrix[1][1] == matrix[0][2] && matrix[1][1] != 0){
            position_points[2][0] += 5;
            if(matrix[1][1] == 2){
                position_points[0][0] += 3;
            } else {
                position_points[0][0] += 2;
            }
        }
    }

    // Verifica qual posicao tem mais pontos, e joga nela
    int x_best, y_best;
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
    place(y_best + 'A', x_best + '0' + 1);

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