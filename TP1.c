#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud
{
    int valeur;
    struct Noeud *suivant;
} Noeud;

Noeud* cree(int _valeur)
{
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL)
    {
        printf("Allocation mémoire échouée\n");
        return NULL;
    }
    nouveau->valeur = _valeur;
    nouveau->suivant = NULL;
    return nouveau;
}

void affiche(Noeud *debut)
{
    Noeud* temp = debut;
    while (temp != NULL) {
        printf("%d -> ", temp->valeur);
        temp = temp->suivant;
    }
    printf("NULL\n");
}

Noeud* ajouterD(Noeud *debut, int _valeur)
{
    Noeud* nouveau = cree(_valeur);
    if (nouveau == NULL)
        return debut;
    nouveau->suivant = debut;
    return nouveau;
}

Noeud* ajouterF(Noeud *debut, int _valeur)
{
    Noeud* nouveau = cree(_valeur);
    if (nouveau == NULL)
        return debut;
    if (debut == NULL)
        return nouveau;
    Noeud* temp = debut;
    while (temp->suivant != NULL)
    {
        temp = temp->suivant;
    }
    temp->suivant = nouveau;
    return debut;
}

int taille(Noeud *debut)
{
    int count = 0;
    Noeud* temp = debut;
    while (temp != NULL)
    {
        count++;
        temp = temp->suivant;
    }
    return count;
}

Noeud* insertion(Noeud *debut, int pos, int _valeur)
{
    if (pos < 1 || pos > taille(debut) + 1)
        return debut;
    if (pos == 1)
        return ajouterD(debut, _valeur);
    Noeud* nouveau = cree(_valeur);
    if (nouveau == NULL)
        return debut;
    Noeud* temp = debut;
    for (int i = 1; i < pos - 1; i++)
    {
        temp = temp->suivant;
    }
    nouveau->suivant = temp->suivant;
    temp->suivant = nouveau;
    return debut;
}

void rechercher(Noeud *debut, int _valeur)
{
    Noeud* temp = debut;
    int pos = 1;
    while (temp != NULL)
    {
        if (temp->valeur == _valeur)
        {
            printf("Valeur %d trouvée à la position %d\n", _valeur, pos);
            return;
        }
        temp = temp->suivant;
        pos++;
    }
    printf("Valeur %d non trouvée\n", _valeur);
}

Noeud* suppressionD(Noeud *debut)
{
    if (debut == NULL)
        return NULL;
    Noeud* temp = debut->suivant;
    free(debut);
    return temp;
}

Noeud* suppressionF(Noeud *debut)
{
    if (debut == NULL || debut->suivant == NULL)
    {
        free(debut);
        return NULL;
    }
    Noeud* temp = debut;
    while (temp->suivant->suivant != NULL)
    {
        temp = temp->suivant;
    }
    free(temp->suivant);
    temp->suivant = NULL;
    return debut;
}

Noeud* suppressionP(Noeud *debut, int pos)
{
    if (debut == NULL || pos < 1 || pos > taille(debut))
        return debut;
    if (pos == 1)
        return suppressionD(debut);
    Noeud* temp = debut;
    for (int i = 1; i < pos - 1; i++)
    {
        temp = temp->suivant;
    }
    Noeud* aSupprimer = temp->suivant;
    temp->suivant = aSupprimer->suivant;
    free(aSupprimer);
    return debut;
}

Noeud* modifierD(Noeud *debut, int _valeur)
{
    if (debut != NULL)
    {
        debut->valeur = _valeur;
    }
    return debut;
}

Noeud* modifierF(Noeud *debut, int _valeur)
{
    if (debut == NULL)
        return debut;
    Noeud* temp = debut;
    while (temp->suivant != NULL)
    {
        temp = temp->suivant;
    }
    temp->valeur = _valeur;
    return debut;
}

Noeud* modifierP(Noeud *debut, int pos, int _valeur)
{
    if (debut == NULL || pos < 1 || pos > taille(debut))
        return debut;
    Noeud* temp = debut;
    for (int i = 1; i < pos; i++)
    {
        temp = temp->suivant;
    }
    temp->valeur = _valeur;
    return debut;
}

int main()
{
    Noeud* liste = NULL;
    liste = ajouterD(liste, 10);
    liste = ajouterD(liste, 20);
    liste = ajouterF(liste, 30);
    affiche(liste);
    liste = insertion(liste, 3, 25);
    affiche(liste);
    rechercher(liste, 30);
    rechercher(liste, 100);
    liste = suppressionD(liste);
    affiche(liste);
    liste = suppressionF(liste);
    affiche(liste);
    liste = suppressionP(liste, 2);
    affiche(liste);
    liste = modifierD(liste, 100);
    affiche(liste);
    liste = modifierF(liste, 200);
    affiche(liste);
    liste = modifierP(liste, 2, 150);
    affiche(liste);
    return 0;
}
