
struct Changement
{
        char ligne[TAILLE_NOM];
        double cout;
        char nomDep[TAILLE_NOM];
        char nomArr[TAILLE_NOM];
	struct Changement * next;
	
}
typedef Changement * ListeChangement;

ListeChangement traitementAffichage(ListeRes resultat);

ListeChangement ajoutTete(ListeChangement liste, char l[], double c, char dep[], char arr[]);
void supprimer(ListeChangement liste);

char* getLigne(ListeChangement liste, int num);
double getCout(ListeChangement liste, int num);
char* getDep(ListeChangement liste, int num);
char* getArr(ListeChangement liste, int num);
