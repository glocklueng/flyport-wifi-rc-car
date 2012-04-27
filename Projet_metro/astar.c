#include "astar.h"

ListeRes aStar(int numDep, int numArr, Station * plan)
{
	ListeData open = NULL, close = NULL;
	Data k;
	ListeArcs s = NULL;
	ListeRes res = NULL;
	ListeSouv souvenir = NULL;
	int tentativeCscore, tentativeIsBetter;

	open = setData(open, numDep, 0, heuristicCost(numDep,numArr,plan));
	
	while (open != NULL)
	{
		k  = getLowestC(open);
		if (k.num == numArr)
		{
			res = reconstruire(souvenir, numDep, numArr);
			suppData(open);
			suppData(close);
			suppSouv(souvenr);
			return res;
		}
		open = remove(open,k.num);
		close = setData(close, k.num, k.a, k.h); //la copie de a,h et c est inutile
		s = plan[k.num].arcs;
		while (s != NULL)
		{
			if (isInListe(close,s->num))
				continue; //on passe au suivant

			tentativeCscore = k.c + s->cout;

			if (!isInListe(open,s->num))
			{
				//open = ajouterData(open ,s->num, -1, heursticCost(s->num, numArr, plan)); //-1 sera defini plus tard
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
				souv = ajouterSouv(souv, s->num, k.num);
				open = setData(open, s->num, tentativeCscore, heursticCost(s->num, numArr, plan));
			}
			
			s = s->suiv;
		}
	}
	return NULL;
}

