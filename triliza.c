#include <stdio.h>
#include <stdlib.h>

int menu();
void clear_stdin();
void init_board(char board[][3]);
void print_board(char board[][3]);
int input(int * row, int * col);
int is_valid_input(char in[4]);

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
	fflush(stdin);
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