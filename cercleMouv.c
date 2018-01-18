#include<stdio.h>
#include<stdlib.h>

#define MAX 17


typedef int Tab[MAX][MAX];

void iniTab(Tab t, int posjx, int posjy)
{
	for(int i=0;i<=MAX;i++)
	{
		for(int j=0;j<=MAX;j++)
		{
			t[i][j] = 1;
		}
	}
	t[posjx][posjy] = 4;
}

void affTab(Tab t)
{
	for(int i=0;i<=MAX;i++)
	{
		printf("\n");
		for(int j=0;j<=MAX;j++)
		{
			if(t[i][j]==0)	printf(" %d", t[i][j]);
			else if(t[i][j]==4) printf("CC");
			else printf(" .");		
		}
	}
}

int abs(int a)
{
	if(a<0) return a*-1;
	else return a;
}

void traceCase(Tab t, int x, int y, int xpos, int ypos) //void traceCase(Tab t, int x, int y, int *xpos, int *ypos)
{		  // MAX/2 = centre du cercle
	int xc = xpos, yc = ypos;		//int xc = MAX/2, yc = MAX/2;

	if(xc-x<0)//N
	{
		if(yc-y<0)//W
		{
			t[xc+x][yc+y] = 0;
		}
		else if(yc+y>MAX)//E
		{
			t[xc+x][yc-y] = 0;
		}
		else
		{
			t[xc+x][yc+y] = 0;
			t[xc+x][yc-y] = 0;
		}
	}
	else if(xc+x>MAX)//S
	{
		if(yc-y<0)//W
		{
			t[xc-x][yc+y] = 0;	
		}
		else if(yc+y>MAX)//E
		{
			t[xc-x][yc-y] = 0;	
		}
		else
		{
			t[xc-x][yc+y] = 0;
			t[xc-x][yc-y] = 0;
		}
	}
	else if(xc+x>=0 && xc-x<MAX)//N-S
	{
		if(yc-y<0)//W
		{
			t[xc+x][yc+y] = 0;
			t[xc-x][yc+y] = 0;
		}
		else if(yc+y>MAX)//E
		{
			t[xc+x][yc-y] = 0;
			t[xc-x][yc-y] = 0;
		}
		else
		{
			t[xc+x][yc+y] = 0;
			t[xc+x][yc-y] = 0;
			t[xc-x][yc+y] = 0;
			t[xc-x][yc-y] = 0;
		}
	}
}

void faireCercle(Tab t, int radius, int xpos, int ypos) //(Tab t, int *xpos, int *ypos)
{
	int r = radius, dr = 0, d1 = 0, d2 = 0,  x = r, y = 0, cx = MAX/2, cy = MAX/2, tempd1 = 0, tempd2 = 0;
	
	iniTab(t, xpos, ypos);
	traceCase(t, r, 0, xpos, ypos);
	traceCase(t, 0, r, xpos, ypos);
	while(x>y)
	{
		d1 = dr+(2*y)-(2*x)+2; 				printf("\n d1:%d", d1);
		d2 = dr+(2*y)+1;							printf("\n d2:%d", d2);
		tempd1 = abs(d1);
		tempd2 = abs(d2);
		if(tempd1 < tempd2)
		{
			dr = d1;
			y++;
			x--;
		}
		else
		{
			dr = d2;
			y++;
		}
		traceCase(t, x, y, xpos, ypos);
		traceCase(t, y, x, xpos, ypos);
	}
}


int main()
{
	int rayon = 10, i = 0;
	int xpos = 0, ypos = 0;
	Tab t;
	iniTab(t, xpos, ypos);
	while(i==0)
	{
		printf("\nPOSITION X: "); scanf("%d", &xpos);
		printf("\nPOSITION Y: "); scanf("%d", &ypos);	
	
		faireCercle(t, rayon, xpos, ypos); //faireCercle(t, int *xpos, *ypos);		
		affTab(t);
	}
	printf("\nhello world\n");
	return 0;
}

