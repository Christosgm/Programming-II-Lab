#include <stdio.h>
#include <stdlib.h>

int menu();
void clear_stdin();
void print_board();

int main()
{
	int choice = menu();
	if(choice == 2 || choice == 3)
	{
		exit(1);
	}
	print_board();
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
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

void print_board()
{
	int i, j;
    printf("    1   2   3   \n");
    printf("  /-----------\\\n");
    for(i = 0; i < 3; i++)
    {
        printf("%d | ", i + 1);
        for(j = 0; j < 3; j++)
        {
            printf("%d | ", i + j);
        }
        if(i != 2)
        {
            printf("\n  |-----------|\n");
        }
        else
        {
            printf("\n  \\-----------/\n");
        }
    }
}