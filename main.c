#include <stdio.h>  
#include <string.h>

struct board{
  //placeholders[height][width]
    int placeholders[21][41];
    char filename[100];
    int width;
    int height;
};

void init_board(struct board *board){
    printf("Choose a save file name: ");
    scanf("%s", board->filename);

    do{
        printf("Pick the width of the board size(4-40): "); 
        scanf("%d", &board->width);
    }while(board->width < 4 || board->width > 40);

    do{
        printf("Pick the height of the board size(4-20): ");  
        scanf("%d", &board->height); 
    }while(board->height < 4 || board->height > 20);  
} 

void draw_board(struct board *board, int turn, int invalid){
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
            if (turn == 0){
                printf("        Player 1");
            }
            if (turn == 1){
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
}

int main(){
    struct board main_board = {0};

    init_board(&main_board);
    draw_board(&main_board, 0, 0);

    int in_game = 1, turn = 0;
    while (in_game)
    {
        //printf("\nPLAYER %d\n", turn + 1);

        int pos = 0;
        do
        {
            printf("Type number between 1-%d: ", main_board.width);
            scanf("%d", &pos);
            if (pos < 1 || pos > main_board.width || main_board.placeholders[0][pos-1] != 0)
            {
                draw_board(&main_board, turn, 1);
            }

        } while (pos < 1 || pos > main_board.width || main_board.placeholders[0][pos-1] != 0);        
        pos -= 1;

        for (int i = main_board.height-1; i >= 0; i--)
        {
            if(main_board.placeholders[i][pos] == 0){

                if(turn == 0)
                    main_board.placeholders[i][pos] = 'O';
                else 
                    main_board.placeholders[i][pos] = 'X';
                break;
            }
        }
        
        if(turn == 0) turn = 1;
        else turn = 0;

        draw_board(&main_board, turn, 0);
    }
    
}
