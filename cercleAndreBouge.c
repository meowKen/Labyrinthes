#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef int Tab[MAX][MAX];

void iniTab(Tab t)
{
	for(int i=0; i<MAX; i++)
	{
		for(int j=0; j<MAX; j++)
		{
			t[i][j] = -1;
		}
	}
}

void affTab(Tab t)
{
	for(int i=0; i<MAX; i++)
	{
		printf("\n");
		for(int j=0; j<MAX; j++)
		{
			if(t[i][j] == -1)		printf(" .");
			else if(t[i][j] >= 0)	printf(" %d", t[i][j]);
		}
	}
}


void cercleAndre(Tab t, int xc, int yc, int r)
{
	int x = 0;
	int y = r;
	int d = r - 1;

	t[xc][yc] = 0;
	while(y >= x)
	{	
			t[xc+x][yc+y] = 0;
			t[xc+y][yc+x] = 0;
			t[xc-x][yc+y] = 0;
			t[xc-y][yc+x] = 0;
			t[xc+x][yc-y] = 0;
			t[xc+y][yc-x] = 0;
			t[xc-x][yc-y] = 0;
			t[xc-y][yc-x] = 0;

		if(d >= 2 * x)
		{
			d-= 2 * x + 1;
			x++;
		}
		else if(d < 2 * (r - y))
		{
			d += 2 * y - 1;
			y--;
		}
		else
		{
			d += 2 * (y - x - 1);
			y--;
			x++;
		}
	}
}

void faireDisque(Tab t, int rayon, int cx, int cy)
{	
	int rf = rayon;
	while(rf>0)
	{
		cercleAndre(t, cx, cy, rf);
		rf--;
	}
}

int directionVoulue(int *x, int*y, char direction)
{
	if				(direction == 'W' || direction == 'w'){*x =-1; *y = 0;}
	else if			(direction == 'S' || direction == 's'){*x = 1; *y = 0;}
	else if			(direction == 'A' || direction == 'a'){*x = 0; *y =-1;}
	else if			(direction == 'D' || direction == 'd'){*x = 0; *y = 1;}
	else return 1;															//retourne 1 si entrée invalide
}


int main()
{
	Tab t;
	int rayon = MAX/3, i = 0, x = 0, y = 0, xc = MAX/2, yc = MAX/2, entreeValide = 0, fini=0;
	char car = 0;
	iniTab(t);

	faireDisque(t, rayon, x, y);
	affTab(t);

	while(fini==0)
	{
		printf("\nDIRECTION: " );
		scanf("%s", &car);
		entreeValide = directionVoulue(&x, &y, car);
		printf("\nB");
		//xc += x;
		//yc += y;
		printf("\nC");
		printf("\nx-> %d : y-> %d", x, y);
		printf("\nxc-> %d : yc-> %d", xc, yc);
		faireDisque(t, rayon, MAX/2, MAX/2);
		affTab(t);
	}	

	return 0;
}















