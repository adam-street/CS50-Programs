/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    //init fill value
    int value = d*d - 1;

    //check if even number of tiles
    if(value % 2 == 0)
    {
        //loop though board(2d array)
        for(int i=0; i<d; i++)
        {
            for(int j=0; j<d; j++)
            {
                //fill board index with current value then subtract 1 from value
                board[i][j] = value;
                value--;
            }
        }
    }

    //if not even then odd number of tiles
    else
    {
        //loop though board(2d array)
        for(int i=0; i<d; i++)
        {
            for(int j=0; j<d; j++)
            {
                //if odd and value is 2 then fill board index with 1
                if(value == 2)
                {
                    //fill board index with current value then subtract 1 from value
                    board[i][j] = 1;
                    value--;
                }
                //if odd and value is 1 then fill board index with 2
                else if(value == 1)
                {
                    //fill board index with current value then subtract 1 from value
                    board[i][j] = 2;
                    value--;
                }
                //else just fill index with value
                else
                {
                    //fill board index with current value then subtract 1 from value
                    board[i][j] = value;
                    value--;
                }
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //print newline for style
    printf("\n");

    //loop through 2d array
    for(int i=0; i<d; i++)
    {
        //print space at beginning of each row
        printf(" ");

         for(int j=0; j<d; j++)
         {
             //if printing single digets IE: 0 - 9
             if(board[i][j] < 10)
             {
                //if board index value is 0 then print a "_" for style with extra space to lineup rows
                 if(board[i][j] == 0)
                 {
                    printf("  _ ");
                 }

                //else just print board index value with extra space to lineup rows
                 else
                 {
                    printf("  %i ", board[i][j]);
                 }
             }

            // if not printing single digets
             else
             {
                 //print board index value without extra space to lineup rows
                printf(" %i ", board[i][j]);
             }
         }
         //end row line
        printf("\n");
    }

    //print space between board and input prompt for style
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    //values to store board index's for selected tile and the blank tile
    int eX;
    int eY;
    int sX;
    int sY;

    //loop through 2d array
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //if found blank tile save location to eX and eY
            if(board[i][j] == 0)
            {
                eX = i;
                eY = j;
            }

            //if found selected tile save location to sX and sY
            if(board[i][j] == tile)
            {
                sX = i;
                sY = j;
            }
        }
    }

    //check for left/right movement and that movement is only 1 space
    if(abs(eX - sX) == 1 && abs(eY - sY) == 0)
    {
        board[eX][eY] = tile;
        board[sX][sY] = 0;
    }

    //else check for up/down movement and that movement is only 1 space
    else if(abs(eX - sX) == 0 && abs(eY - sY) == 1)
    {
        board[eX][eY] = tile;
        board[sX][sY] = 0;
    }

    //if movement is not valid return false
    else
    {
        return false;
    }

    //return true if movement is valid
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    //init counter for checking board index value
    int count = 1;

    //loop though 2d array
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //if board index value = count then add 1 to count
            if(board[i][j] == count)
            {
                count++;
            }

            //if count is at end IE:d*d then check that board index is 0
            else if(count == d*d)
            {
                //if board index is 0 then return true. YOU WIN!
                if(board[i][j] == 0)
                {
                    return true;
                }
            }
        }
    }

    //if check fails return false
    return false;
}
