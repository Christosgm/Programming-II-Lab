#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_board(char board[][3]);

int input(int * row, int * col);

void print_board(char board[][3]);

void clear_stdin();

void clear_screen();

int is_valid_input(char in[5]);

int is_empty_cell(int i, int j, char board[][3]);

char somebody_wins(char board[][3]);

int is_draw(char board[][3]);

int save(char board[][3]);

int load(char board[][3], int * round);

int menu();

int main()
{
    int i, j;
    char board[3][3];

    //Start with empty board (fill with ' ' character)
    init_board(board);

    int round = 1; //Starting round is 1
    int row, col;
    clear_screen();

    int choice = menu(); //Selection from menu
   
    if (choice == 2)//Load selected
    {
        load(board, &round);
    }
    if (choice == 3)//Exit selected
    {
        exit(1);
    }
    clear_screen();
    print_board(board);

    do
    {
        printf("%s enter row and column: ", round%2 == 1 ? "Player X" : "Player O");
        do
        {
            int s = input(&row, &col);//Take input from player
            clear_screen();
            if(s == 1)//Player typed 'save'
            {
                save(board);
                printf("Goodbye!\n");
                exit(1);
            }
            if(is_empty_cell(row - 1, col - 1, board) == -1) //Check if cell is taken
            {
                clear_screen();
                print_board(board);
                printf("Cell must not be  taken!\n");
                printf("%s enter row and column: ", round%2 == 1 ? "Player X" : "Player O");
                continue;
            }
        }
        while(is_empty_cell(row - 1, col - 1, board) == -1);//Stop taking input when cell is empty

        if(round%2 == 1)//X player's turn
        {
            board[row - 1][col - 1] = 'X';
        }
        else//O player's turn
        {
            board[row - 1][col - 1] = 'O';
        }

        print_board(board);

        round++;
    }
    while(somebody_wins(board) == ' ' && is_draw(board) == -1);//Play until somebody wins or draw

    char w = somebody_wins(board);//Find out the result

    if(w != ' ')//If somebody won
    {
    	printf("Player %c wins!\n", w);
    }
    else//Is draw
    {
    	printf("Draw!\n");
    }
    system("pause");//***Windows only!!***
}

void init_board(char board[][3])
{
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void clear_stdin()
{
	fflush(stdin);//***Windows only!!***
}

void clear_screen()
{
	system("cls");//***Windows only!!***
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
	//getchar();
    return choice - '0'; //"Convert" char number to int 
}

int input(int * row, int * col)
{
		int res = 1;// Result from validation
		char in[5]="    ";//Input buffer
		while(1)
		{
            fgets(in, 5, stdin);//Read string from input
            clear_stdin();
            in[strcspn(in, "\n")] = 0;//Replace \n with \0 from input buffer

			res = is_valid_input(in);//Validate input 
			if (res == 0)//Wrong input 
			{
				printf("Input must be either 'save' or '[1-3][' '][1-3]'!\n:>");
				continue;
			}
			if(res == 1)//Save game input
			{
				return 1;
			}
			if(res == 2)//Right input 
			{
				//"Convert" input chars to ints
				*row = in[0] - '0';
				*col = in[2] - '0';
				return 0;
			}	
		}
}

int is_valid_input(char in[5])
{
	if(strcmp(in, "save") == 0)//Input is 'save'
	{
		return 1;
	}
	//Input is valid "[1-3] [1-3]"
	if((in[0] >= '1' && in[0] <= '3') && in[1] == ' ' && (in[2] >= '1' && in[2] <= '3') && in[3] == '\0')
	{
		return 2;
	}
	return 0;//Anything else is not valid
}

void print_board(char board[][3])
{
    int i, j;
    printf("    1   2   3   \n");
    printf("  /-----------\\\n");//Starting divider
    for(i = 0; i < 3; i++)//For every line
    {
        printf("%d | ", i + 1);
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

int is_empty_cell(int i, int j, char board[3][3])
{
    if (board[i][j] != ' ') //Place is taken
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

char somebody_wins(char board[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++) //Check each row
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
        {
            return board[i][1];
        }
    }

    for(j = 0; j < 3; j++) //Check each column
    {
        if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[2][j] != ' ')
        {
            return board[1][j];
        }
    }

    //Check main diagonal
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
    {
        return board[0][0];
    }

    //Check secondary diagonal
    if(board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return ' ';
}

int is_draw(char board[3][3])
{
    //We must count how many empty cells there are
    int empty = 0;
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                empty++;
            }
        }
    }

    if(somebody_wins(board) == ' ' && empty == 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int save(char board[3][3])
{
    FILE * savefile;
    if ((savefile = fopen("data.sav", "w")) == NULL)//Try to open savefile 
    {
        return -1;
    }

    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            fprintf(savefile, "%c", board[i][j]);//Print board char into file
        }
    }

    fclose(savefile);//Close file

    return 1;
}

int load(char board[3][3], int * round)
{
    FILE * savefile;

    if((savefile = fopen("data.sav", "r")) == NULL)//Try to open savefile
    {
        return -1;
    }

    int i = 0;
    int j = 0;

    int r = 1;

    char c;
    while((c = fgetc(savefile)) != EOF)//While we have not reached the end of file 
    {
        if(c != ' ')//If there is a symbol round counter is increased
        {
            r++;
        }
        board[i][j] = c;//Place character into board
        j++;//Count which column we are
        if(j == 3)//If column == 3
        {
            i++;//Change line
            j = 0;//Column becomes first
        }
    }

    *round = r;//"Return" round

    fclose(savefile);//Close savefile 

    return 1;
}