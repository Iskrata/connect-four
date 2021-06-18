#include <stdio.h>  
#include <string.h>

struct board{
  //placeholders[height][width]
    int placeholders[21][41];
    char filename[100];
    int width;
    int height;
    int turn_side;
};

void init_board(struct board *board){
    printf("Choose a save file name: ");
    scanf("%s", board->filename);

    do{
        printf("Pick the height of the board (4-20): ");  
        scanf("%d", &board->height); 
    }while(board->height < 4 || board->height > 20);  

    do{
        printf("Pick the width of the board (4-40): "); 
        scanf("%d", &board->width);
    }while(board->width < 4 || board->width > 40);

    board->turn_side = 0;
} 

int check_for_win(struct board *board){
    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width-3; j++)
        {
            if(board->placeholders[i][j] == board->placeholders[i][j+1] && board->placeholders[i][j+1] == board->placeholders[i][j+2] && board->placeholders[i][j+2] == board->placeholders[i][j+3]){
                if(board->placeholders[i][j] == 'O') return 1;
                if(board->placeholders[i][j] == 'X') return 2;
            }
        }
        
    }
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height-3; j++)
        {
            if(board->placeholders[j][i] == board->placeholders[j+1][i] && board->placeholders[j+1][i] == board->placeholders[j+2][i] && board->placeholders[j+2][i] == board->placeholders[j+3][i]){
                if(board->placeholders[j][i] == 'O') return 1;
                if(board->placeholders[j][i] == 'X') return 2;
            }
        }
        
    }
    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width-3; j++)
        {
            if(board->placeholders[i][j] == board->placeholders[i+1][j+1] && board->placeholders[i+1][j+1] == board->placeholders[i+2][j+2] && board->placeholders[i+2][j+2] == board->placeholders[i+3][j+3]){
                if(board->placeholders[i][j] == 'O') return 1;
                if(board->placeholders[i][j] == 'X') return 2;
            }
            if (i > 3)
            {
                if(board->placeholders[i][j] == board->placeholders[i-1][j+1] && board->placeholders[i-1][j+1] == board->placeholders[i-2][j+2] && board->placeholders[i-2][j+2] == board->placeholders[i-3][j+3]){
                    if(board->placeholders[i][j] == 'O') return 1;
                    if(board->placeholders[i][j] == 'X') return 2;
                }
            }
        }
        
    }
    
    return 0;
}

void draw_board(struct board *board, int invalid){
    char symb;
    for (int i = 0; i < board->height; i++)
    {
        printf("\n");
        for (int j = 0; j < board->width; j++)
        {     
            if(board->placeholders[i][j] == 0) symb = ' ';
            else{
                symb = board->placeholders[i][j];
            }
            printf("|%c", symb);
        }   
        printf("|");

        if(i == 0) {
            if (board->turn_side == 0){
                printf("        Player 1");
            }
            if (board->turn_side == 1){
                printf("        Player 2");
            }
        }
        if(i == 3){
            if (invalid == 1){
                printf("        !Invalid input!");
            }
        }
    }
    printf("\n");
    for (int i = 0; i < board->width; i++)
    {
        printf(" %d", i+1);
    }
    printf("\n\n");

    int found_winner = check_for_win(board);
    if(found_winner){
        if(found_winner == 1) printf("Player 1 wins\n");
        if(found_winner == 2) printf("Player 2 wins\n");
    }
}

void make_move(struct board *main_board, int pos){

        for (int i = main_board->height-1; i >= 0; i--)
        {
            if(main_board->placeholders[i][pos] == 0){

                if(main_board->turn_side == 0)
                    main_board->placeholders[i][pos] = 'O';
                else 
                    main_board->placeholders[i][pos] = 'X';
                break;
            }
        }
}

void save_in_file(struct board *board){
    FILE * fp;
    char symb;
    fp = fopen (board->filename,"a");

    for (int i = 0; i < board->height; i++)
    {
        fprintf(fp, "\n");
        for (int j = 0; j < board->width; j++)
        {     
            if(board->placeholders[i][j] == 0) symb = ' ';
            else{
                symb = board->placeholders[i][j];
            }
            fprintf(fp, "|%c", symb);
        }   
        fprintf(fp, "|");
    }
    fprintf(fp, "\n");
    fclose (fp);
}

int main(){
    struct board main_board = {0};

    init_board(&main_board);
    draw_board(&main_board, 0);

    int in_game = 0;
    while (!in_game)
    {

        int pos = 0;
        // Read player's move
        do
        {
            printf("Type a number between 1-%d: ", main_board.width);
            scanf("%d", &pos);
            if (pos < 1 || pos > main_board.width || main_board.placeholders[0][pos-1] != 0)
            {
                draw_board(&main_board, 1);
            }

        } while (pos < 1 || pos > main_board.width || main_board.placeholders[0][pos-1] != 0); 
        // Adjust to 0 base       
        pos -= 1;

        make_move(&main_board, pos);

        in_game = check_for_win(&main_board);
        
        // Switch sides
        main_board.turn_side = !main_board.turn_side; 

        save_in_file(&main_board);
        draw_board(&main_board, 0);
    }
}
