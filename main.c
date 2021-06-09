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
    }while(board->width < 4 && board->width > 40);

    do{
        printf("Pick the height of the board size(4-20): ");  
        scanf("%d", &board->height); 
    }while(board->height < 4 && board->height > 20);  
} 

void draw_board(struct board *board){
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
    }
    printf("\n");
    for (int i = 0; i < board->width; i++)
    {
        printf(" %d", i+1);
    }
    printf("\n");
}

int main(){
    struct board main_board = {0};

    init_board(&main_board);
    draw_board(&main_board);
}