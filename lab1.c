#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_N_M 204

typedef int Tab[MAX_N_M][MAX_N_M];

void InitLab(Tab t, int mF, int nF)	//initie la matrice comme une tableau de mn-1 chemins numeroté de 0 à mn-2
{					//Chaques case chemin est entourée de 4 cases murs
    int k=0, i=0, j=0;
    for(i=0; i<mF; i++)
    {
        for(j=0; j<nF; j++)
        {
            if(i%2 == 1 && j%2 == 1)	//Si l'indice est impair : c'est un chemin, t[i][j] = nombre ("k")
            {							// incrémenter nombre
                t[i][j] = k;
                printf("\n %d", k);
                k++;
            }
            else
                t[i][j] = -1;		//Si l'indice est pair : c'est un mur, mettre t[i][j] = -1
        }
    }
}

int NbCasesAZero(Tab t, int mF, int nF) //Compte le nombre de cases chemin ou t[i][j] = 0, 
{										//Si nb case à 0 = m*n-1
    int i=0, j=0, NbCasesAZero = 0;
    for(i=1; i<mF; i=i+2)
    {
        for(j=1; j<nF; j=j+2)
        {
            if(t[i][j] == 0)
            {
                NbCasesAZero ++;
            }
        }
    }
    return NbCasesAZero;
}

void AffLab(Tab t, int mF, int nF)
{
	for(int i=0;i<mF;i++)
	{	printf("\n");
		for(int j=0;j<nF;j++)
		{	
		
			
			
				if(t[i][j] == -1)	printf("XX");
				else 				printf("..");
		
		}
	}
}

void AffTabNumChemin(Tab t,int mF,int nF)	//affiche "+" pour les murs et le numero du chemin de la case pour le reste
{
    int i=0, j=0, valMax = t[mF-2][nF-2];
    for(i=0; i<mF; i++)
    {
        printf("\n");
        for(j=0; j<nF; j++)
        {
            if(t[i][j] != -1)
            {
                if(valMax>=100 && t[i][j]<10)                                   {printf("  %d  ", t[i][j]);}
                else if (valMax>=100 && t[i][j]>=10 && t[i][j]<100)             {printf(" %d  ", t[i][j]);}
                else if (valMax>=100 && t[i][j]>=100)                           {printf(" %d ", t[i][j]);}
                else if (valMax>=10 && valMax<100 && t[i][j]>=10 && t[i][j]<100){printf(" %d ", t[i][j]);}
                else if (valMax>=10 && valMax<100 && t[i][j]>=0 && t[i][j]<10)  {printf(" %d  ", t[i][j]);}
                else if (valMax>=0 && valMax<10)                                {printf(" %d ", t[i][j]);}

            }
            else{
                if(i%2==0 && j%2==1 && valMax>=100)                     {printf("+++++");}
                else if (i%2==0 && j%2==1 && valMax>=10 && valMax<100)  {printf("++++");}
                else if (i%2==0 && j%2==1 && valMax>=-1 && valMax<10)   {printf("+++");}
                else printf("+++");
            }
        }
    }

}

int XAlea(int m)
{
	int x=0;
	x=rand()%((m-1)-1) +1;
	return x;
}

int YAlea(int n)
{
	int y=0;
	y=rand()%((n-1)-1) +1;
	return y;
}

void FaireChemin(Tab t, int mF, int nF, int finiF)
{
	int rndX=0, rndY=0, d=0, i=0, j=0, buff = 0;	
	rndX = XAlea(mF);


	if(rndX%2 == 0) //si x pair (donc y impair)
	{
		do
		{
			rndY = YAlea(nF);		
		}while(rndY%2 == 0);

		d = t[rndX-1][rndY]-t[rndX+1][rndY];

		if(d>0) //si la variable contenue par la case d'indice [x+1,y] est plus PETITE que celle en [x-1,y] 
		{	
			buff = t[rndX-1][rndY];
			
			for(i=1; i<mF;i++)
			{
				for(j=1;j<nF;j++)
				{//printf("\n\nA");
					
					if (t[i][j] == buff){
						t[i][j] = t[rndX+1][rndY];}
				}
			}
			//t[rndX-1][rndY] = t[rndX+1][rndY];
			//t[rndX][rndY]   = t[rndX+1][rndY];
			t[rndX][rndY]   = t[rndX+1][rndY];
		}
		else if(d<0) //si la variable contenue par la case d'indice [x-1,y] est plus PETITE que celle en [x+1,y] 
		{
			buff = t[rndX+1][rndY];
			
			for(i=1; i<mF;i++)
			{
				for(j=1;j<nF;j++)
				{	//printf("\n\nB, %d, -1 : %d, +1 : %d", t[i][j], t[rndX-1][rndY], t[rndX+1][rndY]);
					
					if (t[i][j] == buff){
						t[i][j] = t[rndX-1][rndY];}
				}
			}
			//t[rndX+1][rndY] = t[rndX-1][rndY];
			//t[rndX][rndY]   = t[rndX-1][rndY];
			t[rndX][rndY]   = t[rndX-1][rndY];			
		}

	}
	else if(rndX%2 == 1)// si x impair (donc y pair)
	{
		do
		{
			rndY = YAlea(nF);		
		}while(rndY%2 == 1);
		
		d = t[rndX][rndY-1]-t[rndX][rndY+1];

		if(d>0)
		{
			buff = t[rndX][rndY-1];
			for(i=1; i<mF;i++)
			{
				for(j=1;j<nF;j++)
				{	//printf("\n\nC");
					
					if (t[i][j] == buff){
						t[i][j] = t[rndX][rndY+1];}
				}
			}
			//t[rndX][rndY-1] = t[rndX][rndY+1];
			//t[rndX][rndY]   = t[rndX][rndY+1];
			t[rndX][rndY]   = t[rndX][rndY+1];
		}
		else if(d<0)
		{	
			//t[rndX][rndY]   = t[rndX][rndY-1];
			buff = t[rndX][rndY+1];
			for(i=1; i<mF;i++)
			{
				for(j=1;j<nF;j++)
				{	//printf("\n\nD");
					
					if (t[i][j] == buff){
						t[i][j] = t[rndX][rndY-1];}
				}
			}
			//t[rndX][rndY+1] = t[rndX][rndY-1];
			//t[rndX][rndY]   = t[rndX][rndY-1];
			t[rndX][rndY]   = t[rndX][rndY-1];
		}

	}
	
	printf("\n\n********************\n***[X][Y] :[%d][%d]***\n********************\n", rndX, rndY);
}

int main()
{
    Tab t;
    int m = 0, n = 0, caseZero = 0;
    int fini = 1;
    srand(time(NULL));

    printf("pour un labyrinthe de M lignes par N colonnes,\nentrez un entier M pour 0<N<101 : ");
    scanf("%d", &m);
    printf("\nPuis entrez un entier N pour 0<M<101 : ");
    scanf("%d", &n);

    InitLab(t, (2*m)+1, (2*n)+1 );
    AffTabNumChemin(t, (2*m)+1, (2*n)+1 );
    caseZero = NbCasesAZero(t, (2*m)+1, (2*n)+1);
    printf("\nCases à Zero : %d ****\n", caseZero);

	do
	{
		FaireChemin(t, m*2+1, n*2+1, fini);
		//AffTabNumChemin(t, (2*m)+1, (2*n)+1 );
		//scanf("%d", &fini);
	}while(caseZero=NbCasesAZero(t, m*2+1, n*2+1) < m*n-1);
    
	AffLab(t, m*2+1, n*2+1);
    return 0;
}


