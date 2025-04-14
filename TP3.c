#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud
{
    int data;
    struct Noeud *next;
    struct Noeud *prev;
} Noeud;

Noeud* creer(int x)
{
    Noeud *nouveau = malloc(sizeof(Noeud));
    nouveau->data = x;
    nouveau->next = NULL;
    nouveau->prev = NULL;
    return nouveau;
}

void afficher(Noeud *tete)
{
    Noeud *temp = tete;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void afficherInverse(Noeud *tete)
{
    if(tete == NULL) return;
    Noeud *temp = tete;
    while(temp->next != NULL)
        temp = temp->next;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

Noeud* ajouterD(Noeud *tete, int x)
{
    Noeud *nouveau = creer(x);
    if(tete == NULL) return nouveau;
    nouveau->next = tete;
    tete->prev = nouveau;
    return nouveau;
}

Noeud* ajouterF(Noeud *tete, int x)
{
    Noeud *nouveau = creer(x);
    if(tete == NULL) return nouveau;
    Noeud *temp = tete;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = nouveau;
    nouveau->prev = temp;
    return tete;
}

int taille(Noeud *tete)
{
    int count = 0;
    Noeud *temp = tete;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

Noeud* inserer(Noeud *tete, int pos, int x)
{
    if(pos < 1 || pos > taille(tete)+1) return tete;
    if(pos == 1) return ajouterD(tete, x);
    if(pos == taille(tete)+1) return ajouterF(tete, x);
    
    Noeud *nouveau = creer(x);
    Noeud *temp = tete;
    for(int i=1; i<pos-1; i++)
        temp = temp->next;
    
    nouveau->next = temp->next;
    nouveau->prev = temp;
    temp->next->prev = nouveau;
    temp->next = nouveau;
    return tete;
}

Noeud* rechercher(Noeud *tete, int x)
{
    Noeud *temp = tete;
    while(temp != NULL)
    {
        if(temp->data == x) return temp;
        temp = temp->next;
    }
    return NULL;
}

Noeud* supprimerD(Noeud *tete)
{
    if(tete == NULL) return NULL;
    Noeud *temp = tete->next;
    if(temp != NULL) temp->prev = NULL;
    free(tete);
    return temp;
}

Noeud* supprimerF(Noeud *tete)
{
    if(tete == NULL) return NULL;
    if(tete->next == NULL)
    {
        free(tete);
        return NULL;
    }
    Noeud *temp = tete;
    while(temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
    return tete;
}

Noeud* supprimerP(Noeud *tete, int pos)
{
    if(pos < 1 || pos > taille(tete)) return tete;
    if(pos == 1) return supprimerD(tete);
    if(pos == taille(tete)) return supprimerF(tete);
    
    Noeud *temp = tete;
    for(int i=1; i<pos; i++)
        temp = temp->next;
    
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
    return tete;
}

Noeud* modifierD(Noeud *tete, int x)
{
    if(tete != NULL) tete->data = x;
    return tete;
}

Noeud* modifierF(Noeud *tete, int x)
{
    if(tete == NULL) return NULL;
    Noeud *temp = tete;
    while(temp->next != NULL)
        temp = temp->next;
    temp->data = x;
    return tete;
}

Noeud* modifierP(Noeud *tete, int pos, int x)
{
    if(pos < 1 || pos > taille(tete)) return tete;
    Noeud *temp = tete;
    for(int i=1; i<pos; i++)
        temp = temp->next;
    temp->data = x;
    return tete;
}

Noeud* trier(Noeud *tete)
{
    if(tete == NULL || tete->next == NULL) return tete;
    int swapped;
    Noeud *ptr;
    Noeud *last = NULL;
    
    do
    {
        swapped = 0;
        ptr = tete;
        
        while(ptr->next != last)
        {
            if(ptr->data > ptr->next->data)
            {
                int tmp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = tmp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
    while(swapped);
    
    return tete;
}

int main()
{
    Noeud *liste = NULL;
    liste = ajouterF(liste, 30);
    liste = ajouterF(liste, 10);
    liste = ajouterF(liste, 20);
    liste = ajouterF(liste, 40);
    
    printf("Liste initiale: ");
    afficher(liste);
    
    liste = ajouterD(liste, 5);
    printf("Apres ajout debut: ");
    afficher(liste);
    
    liste = ajouterF(liste, 50);
    printf("Apres ajout fin: ");
    afficher(liste);
    
    liste = inserer(liste, 3, 15);
    printf("Apres insertion position 3: ");
    afficher(liste);
    
    liste = supprimerD(liste);
    printf("Apres suppression debut: ");
    afficher(liste);
    
    liste = supprimerF(liste);
    printf("Apres suppression fin: ");
    afficher(liste);
    
    liste = supprimerP(liste, 2);
    printf("Apres suppression position 2: ");
    afficher(liste);
    
    liste = modifierD(liste, 100);
    printf("Apres modification debut: ");
    afficher(liste);
    
    liste = modifierF(liste, 200);
    printf("Apres modification fin: ");
    afficher(liste);
    
    liste = modifierP(liste, 2, 150);
    printf("Apres modification position 2: ");
    afficher(liste);
    
    Noeud *result = rechercher(liste, 150);
    if(result != NULL)
        printf("150 trouve dans la liste\n");
    else
        printf("150 non trouve\n");
    
    liste = trier(liste);
    printf("Liste triee: ");
    afficher(liste);
    
    printf("Affichage inverse: ");
    afficherInverse(liste);
    
    return 0;
}