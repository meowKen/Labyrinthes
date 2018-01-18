#include <stdio.h>
#include <stdlib.h>

#define MAX 31

typedef int Tab[MAX][MAX];


//				//
//	STRUCTS		//
//				//


typedef struct Element Element;
struct Element
{
	int x, y;
	Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
	Element *premier;
};


//	INITIATION STRUCT	&	INSERTION	//


Liste *initialisation() // initialise avec 1 element
{
	Liste *liste = malloc(sizeof(*liste));
	Element *element = malloc(sizeof(*element));

	if(liste == NULL || element == NULL)
	{
		exit(EXIT_FAILURE);
	}

	element->x = 0;
	element->y = 0;
	element->suivant = NULL;
	liste->premier = element;

	return liste;
};


void insertion(Liste *liste, int nvx, int nvy)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if(liste == NULL || nouveau == NULL)
		{
			exit(EXIT_FAILURE);
		}
	nouveau->x = nvx;
	nouveau->y = nvy;

	nouveau->suivant = liste->premier;
	liste->premier = nouveau;
	
}

//	MATRICE D'AFFICHAGE DU CERCLE	//


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


//	AFFICHAGE DE LA LISTE, FONCTION DE CONTROLE	//

void afficherListe(Liste *liste)
{
	if(liste == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *actuel = liste->premier;

	while(actuel != NULL)
	{	
		printf("\nX: %d -> Y: %d", actuel->x, actuel->y);
		actuel = actuel->suivant;
	}

}


//	REMPLIS LA MATRICE D?AFFICHAGE SELON LA LISTE	//
//	(TRACE LE CERCLE)	//


void listeToTab(Liste *liste, Tab t)
{
	if(liste == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *actuel = liste->premier;
	iniTab(t);
	while(actuel != NULL)
	{	
		t[actuel->x][actuel->y] = 0;
		actuel = actuel->suivant;
	}
}


// AFFICHAGE DU TABLEAU "TERRAIN" (APPELER A CHAQUE FRAME)


void affTab(Tab t)
{
	for(int i=0; i<MAX; i++)
	{
		printf("\n");
		for(int j=0; j<MAX; j++)
		{
			if(t[i][j] == -1)	printf(" .");
			else if(t[i][j] >= 0)	printf(" %d", t[i][j]);
		}
	}
}


//	CREE UNE LISTE CONTENANT LES COORDONNEES X ET Y DE CHAQUES POINTS DU CERCLE	//
//	LE CERCLE A POUR RAYON: r ET LES COORDONNEES AU CENTRE SONT: xc ET yc	//	


void cercleAndre(Liste *liste, int xc, int yc, int r)
{
	int x = 0;
	int y = r;
	int d = r - 1;

	insertion(liste,xc,yc);
	while(y >= x)
	{	
		if((xc+x<MAX && xc+x>=0) && (yc+y<MAX && yc+y>=0)) 	insertion(liste,xc+x,yc+y) ;
		if((xc+y<MAX && xc+y>=0) && (yc+x<MAX && yc+x>=0))	insertion(liste,xc+y,yc+x) ;
		if((xc-x<MAX && xc-x>=0) && (yc+y<MAX && yc+y>=0))	insertion(liste,xc-x,yc+y) ;
		if((xc-y<MAX && xc-y>=0) && (yc+x<MAX && yc+x>=0))	insertion(liste,xc-y,yc+x) ;
		if((xc+x<MAX && xc+x>=0) && (yc-y<MAX && yc-y>=0))	insertion(liste,xc+x,yc-y) ;
		if((xc+y<MAX && xc+y>=0) && (yc-y<MAX && yc-y>=0))	insertion(liste,xc+y,yc-x) ;
		if((xc-x<MAX && xc-x>=0) && (yc-y<MAX && yc-y>=0))	insertion(liste,xc-x,yc-y) ;
		if((xc-y<MAX && xc-y>=0) && (yc-x<MAX && yc-x>=0))	insertion(liste,xc-y,yc-x) ;

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


// DEFINI LA DIRECTION D?AVANCE DU PERSONNAGE	//


int directionVoulue(int *x, int*y, char direction)
{
	if			(direction == 'W' || direction == 'w'){*x =-1; *y = 0;}
	else if			(direction == 'S' || direction == 's'){*x = 1; *y = 0;}
	else if			(direction == 'A' || direction == 'a'){*x = 0; *y =-1;}
	else if			(direction == 'D' || direction == 'd'){*x = 0; *y = 1;}
	else return 1;			
}

int main()
{
	Liste *maListe = initialisation();
	Tab t;
	int rayon = MAX/3, rayont = 0, i = 0;
	int x=0, y=0, xc=0, yc=0;
	int fini = 0;
	char car = 0;

	iniTab(t);


	while(!fini)
	{
		rayont=rayon;
		free(maListe);
		maListe = initialisation();
		while(rayont>0)
		{
			cercleAndre(maListe,xc, yc, rayont);   //cercleAndre(t, MAX/2, MAX/2, rayon);
			//afficherListe(maListe);
			//affTab(t);
			rayont-=1;
		}

		listeToTab(maListe, t);
		affTab(t);
		printf("\nHello World\n");
		affTab(t);
		printf("\nDIRECTION:");
		scanf("%s", &car);
		printf("\nX -> %d, Y -> %d", x, y);
		directionVoulue(&x, &y, car);
		xc+=x;
		yc+=y;
	}

	return 0;
}
