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


char grid[ROWS][COLUMNS];


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
        printf("\naction: %d", action);
        
        int validity;
        struct pos *play;
        if (action == ACT_ERR)
        {
            printf("\n");
            printf("Unexpected input");
            return 1;
        }
        else if (action == ACT_STOP)
        {
            printf("\n");
            printf("Game exited by player %d", player_turn);
            return 0;
        }
        else
        {
            play = &(struct pos) { .column = action, .row = 0};
            printf("\nplay: %d:%d", play->column, play->row);
            validity = check_validity(play);
            printf("\nvalidity: %d\n", validity);
        }
        
        if (validity == 1)
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

    unsigned row;
    unsigned col;

    for(row = 0; row < ROWS; row++)
    {
        for(col = 0; col < COLUMNS; col++)
        {
            grid[row][col] = ' ';
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
    if (play->column < 0 || play->column > 6)
    {
        return 0;
    }

    for (play->row = ROWS - 1; play->row >= 0; play->row--)
    {
        if (grid[play->row][play->column] == ' ')
        {
            return 1;
        }
    }

    printf("\nColumn is full");
    return 1;
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