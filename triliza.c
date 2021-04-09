#include <stdio.h>
#include <stdlib.h>

int menu();
void clear_stdin();
void init_board(char board[][3]);
void print_board(char board[][3]);
int input(int * row, int * col);
int is_valid_input(char in[4]);
int is_empty_cell(int i, int j, char board[3][3]);
char somebody_wins(char board[3][3]);
int is_draw(char board[3][3]);

/* TESTING FUNCTION */
void test_conditions(int row, int col, char board[3][3]);


int main()
{
    int choice = menu();//Get choice from player
    if(choice == 2 || choice == 3)//If choice == load or exit
    {
        exit(1);
    }
    char board[3][3];

    init_board(board);//Fill board with ' '
    int row, col;//Row and column to put symbol
    print_board(board);
    input(&row, &col);//At the memory address of row and col take the input
    board[row - 1][col - 1] = 'X';//Put symbol at the [row, col]
    print_board(board);

    //Tests for somebody_wins, is_draw and is_empty_cell
    test_conditions(row, col, board);
    return 0;
}

int menu()
{
    printf("1. Play\n2. Load\n3. Exit\n:>");
    char choice;
    do
    {
        scanf("%c", &choice);//Read character from keyboard
        if(choice != '1' && choice != '2' && choice != '3')
        {
            printf("Not valid input!\n:>");
            clear_stdin();
        }
    }
    while(choice != '1' && choice != '2' && choice != '3');//Stop reading when choice is in [1, 2, 3]
    clear_stdin();
    return choice - '0'; //"Convert" char number to int
}

void clear_stdin()
{
    fflush(stdin);//***Windows only!!***
}

void print_board(char board[][3])
{
    int i, j;
    printf("    1   2   3   \n");
    printf("  /-----------\\\n");//Starting divider
    for(i = 0; i < 3; i++)//For every line
    {
        printf("%d | ", i + 1);//Print line number
        for(j = 0; j < 3; j++)//For every column
        {
            printf("%c | ", board[i][j]);//Print content then divider
        }
        if(i != 2)//For the first two loops
        {
            printf("\n  |-----------|\n");//Print middle divider
        }
    }
    printf("\n  \\-----------/\n");//When done print ending divider
}

void init_board(char board[][3])
{
    int i, j;
    //For every line
    for(i = 0; i < 3; i++)
    {
        //For every column
        for(j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

int input(int * row, int * col)
{
    int res;
    char in[4];
    while(1)
    {
        printf("Insert row and column: ");
        fgets(in, 4, stdin);//Get 3 characters from stdin (number space number)
        clear_stdin();//Clear stdin (\n is left in stdin)
        res = is_valid_input(in);//Check for validity
        if(res == 0)//If not valid
        {
            printf("Input must be '[1, 3] [' '] [1, 3]'\n:>");
            continue;
        }
        if(res == 1)//If valid
        {
            *row = in[0] - '0';
            *col = in[2] - '0';
            return 1;
        }
    }
}

int is_valid_input(char in[4])
{
    //String must be of the form ([1-3], space, [1-3], \0)
    if((in[0] >= '1' && in[0] <= '3') && in[1] == ' ' && (in[2] >= '1' && in[2] <= '3') && in[3] == '\0')
    {
        return 1;
    }
    return 0;
}

int is_empty_cell(int i, int j, char board[3][3])
{
    if(board[i][j] != ' ')//If cell has either X or O
    {
        return -1;//It is not empty
    }
    return 1;
}

char somebody_wins(char board[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++)//Check every row
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
        {
            return board[i][0];
        }
    }

    for(j = 0; j < 3; j++)//Check every column
    {
        if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[2][j] != ' ')
        {
            return board[0][j];
        }
    }

    //Check main diagonal
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
    {
        return board[0][0];
    }

    //Check secondary diagonal
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' ')
    {
        return board[0][2];
    }

    return ' ';//If every check before has failed, return ' ' (no one has won) 
}

int is_draw(char board[3][3])
{
    int empty = 0;
    int i, j;

    //Count empty cells
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(board[i][j] == ' ')
            {
                empty++;
            }
        }
    }

    //If no one won and every cell is taken
    if(somebody_wins(board) == ' ' && empty == 0)
    {
        return 1;//It is draw
    }
    return -1;
}

void test_conditions(int row, int col, char board[3][3])
{
	printf("\nTesting...\n");
    char board1[3][3] = {{' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '}};
    printf("1. %s", somebody_wins(board1) == ' ' ? "True\n" : "False\n");
    printf("2. %s", is_draw(board1) == -1 ? "True\n" : "False\n");

    char board2[3][3] = {{'O', ' ', ' '},
                         {'X', 'X', 'X'},
                         {' ', 'O', ' '}};
    printf("3. %s", somebody_wins(board2) == 'X' ? "True\n" : "False\n");
    printf("4. %s", is_draw(board2) == -1 ? "True\n" : "False\n");

    char board3[3][3] = {{' ', ' ', 'O'},
                         {'X', 'X', 'O'},
                         {' ', ' ', 'O'}};
    printf("5. %s", somebody_wins(board3) == 'O' ? "True\n" : "False\n");
    printf("6. %s", is_draw(board3) == -1 ? "True\n" : "False\n");

    char board4[3][3] = {{'X', ' ', ' '},
                         {' ', 'X', ' '},
                         {' ', ' ', 'X'}};
    printf("7. %s", somebody_wins(board4) == 'X' ? "True\n" : "False\n");
    printf("8. %s", is_draw(board4) == -1 ? "True\n" : "False\n");

    char board5[3][3] = {{' ', ' ', 'O'},
                         {' ', 'O', ' '},
                         {'O', ' ', ' '}};
    printf("9. %s", somebody_wins(board5) == 'O' ? "True\n" : "False\n");
    printf("10. %s", is_draw(board5) == -1 ? "True\n" : "False\n");

    char board6[3][3] = {{' ', ' ', 'O'},
                         {' ', 'X', ' '},
                         {'O', ' ', ' '}};
    printf("11. %s", somebody_wins(board6) == ' ' ? "True\n" : "False\n");
    printf("12. %s", is_draw(board6) == -1 ? "True\n" : "False\n");

    char board7[3][3] = {{'O', 'X', 'O'},
                         {'X', 'X', 'O'},
                         {'O', 'O', 'X'}};
    printf("13. %s", somebody_wins(board7) == ' ' ? "True\n" : "False\n");
    printf("14. %s", is_draw(board7) == 1 ? "True\n" : "False\n");

    printf("15. %s", is_empty_cell(row - 1, col - 1, board) == -1 ? "True\n" : "False\n");
    printf("16. %s", is_empty_cell(2, 2, board) == 1 ? "True\n" : "False\n");
}