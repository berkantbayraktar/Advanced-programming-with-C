#include <stdio.h>
#define EMPTY 'e'
#define SPIDER 's'

int c;
int ideal = 0;

void printer(char field[][c])
{
	for (int i = 0; i < c; ++i) {
    for (int j = 0; j < i; ++j) {
        printf(" ");
    }
    for (int j = 0; j < (c - i); ++j) {
        printf("%c ", field[i][j]);
}
    printf("\n");
}
printf("\n");
}

void printer2(char field[][c],int fs)
{
	int r2 = (fs /c) -1;
	for (int k=r2 ; k >= 0 ; --k)
	{
		for (int i = (k * c) ; i < (k+1) * c ; ++i) 
		{
    		for (int j = 0; j < i%c; ++j) 
    		{
        		printf(" ");
    		}
    		for (int j = 0; j < (c- i%c); ++j) 
    		{
        		printf("%c ", field[i][j]);
			}
    	printf("\n");
		}
	printf("\n");
	}
}

void copy(char field[][c],char copy_field[][c])
{
	for (int i=0 ; i < c ; i++)
	{
		for (int j=0 ; j < c - i ; j++)
		{			
		copy_field[i][j] = field[i][j];			
		}
	}
}

void movement(char field[][c],int row,int column,int movetype)
{
	if (movetype == 1)
		field[row][column] = EMPTY,field[row][column-1] = EMPTY,field[row][column-2] = SPIDER;
	else if (movetype == 2)
		field[row][column] = EMPTY,field[row][column+1] = EMPTY,field[row][column+2] = SPIDER;
	else if (movetype == 3)
		field[row][column] = EMPTY,field[row-1][column] = EMPTY,field[row-2][column] = SPIDER;
	else if (movetype == 4)
		field[row][column] = EMPTY,field[row-1][column+1] = EMPTY,field[row-2][column+2] = SPIDER;
	else if (movetype == 5)
		field[row][column] = EMPTY,field[row+1][column-1] = EMPTY,field[row+2][column-2] = SPIDER;
	else if (movetype == 6)
		field[row][column] = EMPTY,field[row+1][column] = EMPTY,field[row+2][column] = SPIDER;
}

void add (char history_field[][c],char field[][c],char history_field2[][c],int hs)
{
	int r = hs;

	for (int i=0 ; i < r ; i++)
	{
		for (int j=0 ; j < c ; j++)
		{			
				history_field2[i][j] = history_field[i][j];
		}
	}

	for (int i=0 ; i < c ; i++)
	{
		for (int j=0 ; j < c ; j++)
		{			
				history_field2[i+r][j] = field[i][j];
		}
	}
}

int isIdeal(char field[][c])
{
	int counter =0;

	for (int i=0 ; i < c ; i++)
	{
		for (int j=0 ; j < c - i ; j++)
		{	
    		if (field[i][j] == SPIDER)
    		{
    			counter ++;
    			continue;
    		}
    	}
    }

    if (counter > 1 || counter == 0)
    	return 0;
    else
    	return 1;
}

void solve(char field[][c],char history_field[][c],int hs)
{
	/* Recursion Function */
	
	int r = hs;
	char history_field2[r+c][c];
	char copy_field[c][c];
	for (int i=0 ; i < c ; i++)
	{
		if (ideal == 1)
			break;

		for (int j=0 ; j < c - i ; j++)
		{	
			if (ideal ==1)
				break;

			else if ((field[i][j] == SPIDER) && (field[i][j-1] == SPIDER) && (field[i][j-2] == EMPTY) && (2 <= j))
			{	copy(field,copy_field);
				movement(copy_field,i,j,1); 
				add(history_field,copy_field,history_field2,r);
				if (isIdeal(copy_field))
				{
					ideal = 1;
					printer2(history_field2,r+c);
					break;
				}
				else
					solve(copy_field,history_field2,r+c);
			}
			else if ((field[i][j] == SPIDER) && (field[i][j+1] == SPIDER) && (field[i][j+2] == EMPTY) && (j+i+2 < c))
			{
				copy(field,copy_field);
				movement(copy_field,i,j,2);
				add(history_field,copy_field,history_field2,r);
				if (isIdeal(copy_field))
				{
					ideal =1;
					printer2(history_field2,r+c);
					break;
				}
				else
					solve(copy_field,history_field2,r+c);
			}

			else if ((field[i][j] == SPIDER) && (field[i-1][j] == SPIDER) && (field[i-2][j] == EMPTY) && (2 <= i))
			{
				copy(field,copy_field);
				movement(copy_field,i,j,3);
				add(history_field,copy_field,history_field2,r);
				if (isIdeal(copy_field))
				{
					ideal = 1;
					printer2(history_field2,r+c);
					break;
				}
				else
					solve(copy_field,history_field2,r+c);
			}
			else if ((field[i][j] == SPIDER) && (field[i-1][j+1] == SPIDER)  && (field[i-2][j+2] == EMPTY) && (2 <= i))
			{
				copy(field,copy_field);
				movement(copy_field,i,j,4);
				add(history_field,copy_field,history_field2,r);
				if (isIdeal(copy_field))
				{
					ideal = 1;
					printer2(history_field2,r+c);
					break;
				}
				else
					solve(copy_field,history_field2,r+c);
			}
			else if ((field[i][j] == SPIDER) && (field[i+1][j-1] == SPIDER) && (field[i+2][j-2] == EMPTY) && (2 <= j))
			{
				copy(field,copy_field);
				movement(copy_field,i,j,5);
				add(history_field,copy_field,history_field2,r);
				if (isIdeal(copy_field))
				{
					ideal = 1;
					printer2(history_field2,r+c);
					break;
				}
				else
					solve(copy_field,history_field2,r+c);
			}
			else if ((field[i][j] == SPIDER) && (field[i+1][j] == SPIDER) && (field[i+2][j] == EMPTY) && (i+j+2 < c))
			{
				copy(field,copy_field);
				movement(copy_field,i,j,6);
				add(history_field,copy_field,history_field2,r);
				if (isIdeal(copy_field))
				{
					ideal = 1;
					printer2(history_field2,r+c);
					break;
				}
				else
					solve(copy_field,history_field2,r+c);
			}
		}
	}
}

int main () 
{
	scanf("%d", &c);
	char field[c][c];
	char history_field[c][c];

	for (int i=0 ; i < c ; i++)
	{
		for (int j=0 ; j < c - i ; j++)
		{			
		scanf(" %c", &field[i][j]);			
		}
	}
	if (isIdeal(field))
		printer(field);
	else
	{
		copy(field,history_field);
		solve(field,history_field,c);
		if (ideal == 0)
		printf("No ideal field!\n");
	}

return 0;	
}