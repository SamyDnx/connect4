#include <stdio.h>

#define COLUMNS 7
#define ROWS 6

#define TOKEN1 'O'
#define TOKEN2 'X'

#define ACT_PLAYED 0
#define ACT_STOP 8
#define ACT_ERR 9

struct pos
{
    unsigned column;
    unsigned row;
};


// Prototypes
void initialise_grid(void);
void display_grid(void);
int ask_action(void);
int check_validity(struct pos *);
void update_grid(struct pos *, int);


char grid[COLUMNS][ROWS];


int main (void)
{
    initialise_grid();
    display_grid();

    int player_turn = 1;
    int action;

    int running = 1;
    while (running)
    {
        printf("\n");
        printf("Joueur %d: ", player_turn);

        action = ask_action();
        
        int validity;
        struct pos *play;
        switch (action)
        {
            case ACT_ERR:
                printf("\n");
                printf("Unexpected input");
                return 1;
                break;
            case ACT_STOP:
                printf("\n");
                printf("Game exited by player %d", player_turn);
                return 0;
                break;
            default:
                play = &(struct pos) { .column = action, .row = 0};
                validity = check_validity(play);
                break;
        }

        if (validity)
        {
            update_grid(play, player_turn);
            player_turn = 3 - player_turn;
        }

    }

    return 0;
}

void initialise_grid(void)
{
    /*
    Inistialise grid with withespace char
    */

    unsigned cols;
    unsigned rows;

    for(cols = 0; cols < COLUMNS; cols++)
    {
        for(rows = 0; rows < ROWS; rows++)
        {
            grid[cols][rows] = ' ';
        }
    }
}

void display_grid(void)
{
    /*
    Display the grid in a pretty format
    */

    // Top column's number
    for(unsigned col = 0; col < COLUMNS; col++)
    {
        printf("  %d ", col+1);
    }

    printf("\n");
    // Start of grid
    printf("+");

    for (unsigned col = 0; col < COLUMNS; col++)
    {
        printf("---+");
    }
    
    printf("\n");
    
    for(unsigned row = 0; row < ROWS; row++)
    {
        printf("|");

        for (unsigned col = 0; col < COLUMNS; col++)
        {
            printf(" %c |", grid[row][col]);
        }

        printf("\n");
        printf("+");

        for (unsigned col = 0; col < COLUMNS; col++)
        {
            printf("---+");
        }
        
        printf("\n");
    }

    // Bottom column's number   
    for(unsigned col = 0; col < COLUMNS; col++)
    {
        printf("  %d ", col+1);
    }

    printf("\n");
}

int ask_action(void)
{
    int action;

    scanf("%d", &action);

    if (action >= 1 && action <= 7)
        return action-1;
    else if (action == 0)
        return ACT_STOP;
    else
        return ACT_ERR;
}

int check_validity(struct pos *play)
{
    if (play->column < 1 || play->column > 7)
    {
        return 0;
    }
    else
    {
        struct pos *play = &(struct pos) {.column = play->column, .row = 0};
        for (unsigned row = 0; row < ROWS; row++)
        {
            if (row == 0 && grid[play->row][play->column] != ' ')
            {
                printf("\nCoup Invalide");
                return 0;
            }
            else if (row != 0 && grid[play->row][play->column] != ' ')
            {
                return 1;
            }
            play->row++;
        }
        return 1;
    }
}

void update_grid(struct pos *play, int player_turn)
{
    if (player_turn == 1)
    {
        grid[play->row][play->column] = TOKEN1;
    }
    else
    {
        grid[play->row][play->column] = TOKEN2;
    }

    display_grid();
}