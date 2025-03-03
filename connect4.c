#include <stdio.h>

#define COLUMNS 7
#define ROWS 6

#define TOKEN1 'O'
#define TOKEN2 'X'

#define ACT_PLAYED 0
#define ACT_STOP 8
#define ACT_ERR 9

#define STATUS_DNF 0
#define STATUS_WIN 1
#define STATUS_TIE 2

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
int check_win(struct pos *, int);


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
            int win = check_win(play, player_turn);
            if (win == STATUS_WIN)
            {
                printf("\nPlayer %d wins the match !!!", player_turn);
                return 0;
            }
            else if (win == STATUS_TIE)
            {
                printf("\nTIE !!!");
                return 0;
            }
            else
            {
                player_turn = 3 - player_turn;
            }
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

int check_win(struct pos *play, int player)
{
    // TIE
    int tie = 1;
    for (int i = 0; i < COLUMNS; i++)
    {
        if (grid[0][i] == ' ')
        {
            tie = 0;
            break;
        }
    }

    if (tie == 1)
    {
        return STATUS_TIE;
    }

    // WIN
    char token = (player == 1) ? TOKEN1 : TOKEN2;
    unsigned col = play->column;
    unsigned row = play->row;
    int cnt;

    // Verticql
    cnt = 0;
    for(int r = 0; r < ROWS; r++)
    {
        if (grid[r][col] == token)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
        }
        if (cnt >= 4)
        {
            return STATUS_WIN;
        }
    }

    // Horizontal
    cnt = 0;
    for (int c = 0; c < COLUMNS; c++)
    {
        if (grid[row][c] == token)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
        }
        if (cnt >= 4)
        {
            return STATUS_WIN;
        }
    }
    
    // Check diagonal (top-left to bottom-right)
    for (int startRow = 0; startRow <= ROWS - 4; startRow++) {
        for (int startCol = 0; startCol <= COLUMNS - 4; startCol++) {
            cnt = 0;
            for (int i = 0; i < 4; i++) {
                if (grid[startRow + i][startCol + i] == token)
                    cnt++;
                else
                    break;
            }
            if (cnt >= 4)
                return STATUS_WIN;
        }
    }
    
    // Check diagonal (top-right to bottom-left)
    for (int startRow = ROWS - 1; startRow >= 3; startRow--) {
        for (int startCol = 0; startCol <= COLUMNS - 4; startCol++) {
            cnt = 0;
            for (int i = 0; i < 4; i++) {
                if (grid[startRow - i][startCol + i] == token)
                    cnt++;
                else
                    break;
            }
            if (cnt >= 4)
                return STATUS_WIN;
        }
    }
    
    return STATUS_DNF;
}