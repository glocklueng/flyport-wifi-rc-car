#include "include/astar.h"

ListeRes aStar(int numDep, int numArr, Station * plan)
{
	ListeData open = NULL, close = NULL;
	Data k;
	ListeArcs s = NULL;
	ListeRes res = NULL;
	ListeSouv souvenir = NULL;
	int tentativeCscore, tentativeIsBetter;

	/*On ajoute le premier point à la liste ouverte, a est donc nul*/
	open = setData(open, numDep, 0, heuristic(numDep,numArr,plan));
	
	/*Tant que la liste ouverte n'est pas nulle, on prend le point qui a le meilleur cout*/
	while (open != NULL)
	{
		k  = getLowestC(open);

		if (k.num == numArr)//si on est arrivé
		{
			res = reconstruire(souvenir, numDep, numArr);//reconstruction du chemin grace a la liste souv
			suppData(open);
			suppData(close);
			suppSouv(souvenir);
			return res;
		}
		open = remove(open,k.num);//inutile ou pas, suivant ce que fait getLowestC()
		/*On ajoute ce point dans la liste fermée*/
		close = setData(close, k.num, k.a, k.h); //la copie de a,h et c est inutile : à améliorer par la suite

		s = plan[k.num].arcs; // = la liste de ses fils
		/* Pour tout les fils s de k*/
		while (s != NULL)
		{
			if (isInListe(close,s->num))
				continue; //on passe au fis suivant

			tentativeCscore = k.c + s->cout;

			if (!isInListe(open,s->num))
			{
				//open = ajouterData(open ,s->num, -1, heuristic(s->num, numArr, plan)); //-1 sera defini plus tard
				tentativeIsBetter = 1;
			}
			else if (tentativeCscore < getCscore(open,s->num))
			{
				tentativeIsBetter = 1;
			}
			else
			{
				tentativeIsBetter = 0;
			}
			
			if (tentativeIsBetter)
			{
				souvenir = ajouterSouv(souvenir, s->num, k.num);
				open = setData(open, s->num, tentativeCscore, heuristic(s->num, numArr, plan));
			}
			
			s = s->next;
		}
	}
	return NULL;
}

ListeRes reconstruire(ListeSouv souv, int numDep, int numArr)
{
    ListeRes p = NULL;
    int x;
    p = ajouterRes(p,numArr);
    x = getSouv(souv,numArr);
    p = ajouterRes(p,x);
    while ( x != numDep)
    {
        x = getSouv(souv,x);
        p = ajouterRes(p,x);
    }
    return p;
}

int heuristic(int numDep,int numArr,Station * plan)
{
	int xDep,yDep,xArr,yArr;
	xDep = plan[numDep].lat;
	yDep = plan[numDep].lon;
	xArr = plan[numArr].lat;
	yArr = plan[numArr].lon;

	return (abs(xDep-xArr)+abs(yDep-yArr));
}

ListeRes ajouterRes( ListeRes l, int num)
{
	ListeRes p = malloc(sizeof(*p));
	if (p == NULL)
		return p;
	p->num = num;
	p->next = l;
	
	return p;	
}

ListeSouv ajouterSouv( ListeSouv l, int numFils, int numPere)
{
	ListeSouv p = malloc(sizeof(*p));
	if (p == NULL)
		return p;
	p->num = numFils;
	p->numPere = numPere;
	p->next = l;
	
	return p;	
}

ListeData setData(ListeData l, int num , int a , int h)
{
	ListeData p = l;
	while ( p != NULL )
	{
		if ( p->num == num)
		{ 
			p->a = a;
			p->h = h;
			p->c = a+h;
			return l;
		}
		p = p->next;
	}

	ListeData nouveau = (ListeData)malloc(sizeof(*nouveau));
	nouveau->num = num;
	nouveau->a =a;
	nouveau->h = h;
	nouveau->c = a + h;
	nouveau->next = l;
	return nouveau;
}

int isInListe(ListeData l,int num)
{
	ListeData p = l;
	while (p != NULL)
	{
		if ( p->num == num )
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int getCscore(ListeData l,int num)
{
	ListeData p = l;
	while ( p != NULL)
	{
		if ( p->num == num)
		{
			return p->c;
		}
		p = p->next;
	}
	return -1;
}





