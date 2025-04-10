#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date
{
    char jour[3];
    char mois[3];
    char annee[5];
} Date;

typedef struct Produit
{
    char Nom_produit[100];
    char Reference[100];
    float Montant;
    Date DateAchat;
} Produit;

typedef struct Liste
{
    Produit cellule;
    struct Liste* suivant;
} Liste;

Liste* creer_liste_produits()
{
    return NULL;
}

int est_vide(Liste* tete)
{
    if (tete == NULL)
        return 1;
    else
        return 0;
}

Produit creer_produit()
{
    Produit p;
    printf("Nom du produit : ");
    scanf("%s", p.Nom_produit);
    printf("Reference : ");
    scanf("%s", p.Reference);
    printf("Montant : ");
    scanf("%f", &p.Montant);
    printf("Date d'achat (jj mm aaaa) : ");
    scanf("%s %s %s", p.DateAchat.jour, p.DateAchat.mois, p.DateAchat.annee);
    return p;
}

void afficher_produit(Produit p)
{
    printf("Nom : %s | Réf : %s | Montant : %.2f | Date : %s/%s/%s\n", p.Nom_produit, p.Reference, p.Montant, p.DateAchat.jour, p.DateAchat.mois, p.DateAchat.annee);
}

Liste* ajouter_debut(Liste* tete, Produit p)
{
    Liste* nouveau = (Liste*)malloc(sizeof(Liste));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }
    nouveau->cellule = p;
    nouveau->suivant = tete;
    return nouveau;
}

Liste* ajouter_fin(Liste* tete, Produit p)
{
    Liste* nouveau = (Liste*)malloc(sizeof(Liste));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }
    nouveau->cellule = p;
    nouveau->suivant = NULL;
    if (tete == NULL)
        return nouveau;
    Liste* temp = tete;
    while (temp->suivant != NULL)
        temp = temp->suivant;
    temp->suivant = nouveau;
    return tete;
}

void afficher_liste(Liste* tete)
{
    if (est_vide(tete))
    {
        printf("La liste est vide\n");
        return;
    }
    Liste* temp = tete;
    while (temp != NULL)
    {
        afficher_produit(temp->cellule);
        temp = temp->suivant;
    }
}

Liste* supprimer_debut(Liste* tete)
{
    if (est_vide(tete))
    {
        printf("Liste déjà vide\n");
        return NULL;
    }
    Liste* temp = tete;
    tete = tete->suivant;
    free(temp);
    return tete;
}

Liste* supprimer_fin(Liste* tete)
{
    if (est_vide(tete))
    {
        printf("Liste déjà vide\n");
        return NULL;
    }
    if (tete->suivant == NULL)
    {
        free(tete);
        return NULL;
    }
    Liste* temp = tete;
    while (temp->suivant->suivant != NULL)
        temp = temp->suivant;
    free(temp->suivant);
    temp->suivant = NULL;
    return tete;
}

Liste* rembourser(Liste* tete, char* refer)
{
    if (est_vide(tete))
    {
        printf("Liste vide\n");
        return NULL;
    }
    if (strcmp(tete->cellule.Reference, refer) == 0)
        return supprimer_debut(tete);
    Liste* temp = tete;
    Liste* prec = NULL;
    while (temp != NULL && strcmp(temp->cellule.Reference, refer) != 0)
    {
        prec = temp;
        temp = temp->suivant;
    }
    if (temp == NULL)
    {
        printf("Produit non trouvé\n");
        return tete;
    }
    prec->suivant = temp->suivant;
    free(temp);
    return tete;
}

int main()
{
    Liste* maListe = creer_liste_produits();
    int choix;
    Produit p;
    char ref[100];
    do
    {
        printf("\nMenu :\n");
        printf("1. Ajouter produit au début\n");
        printf("2. Ajouter produit à la fin\n");
        printf("3. Afficher liste des produits\n");
        printf("4. Supprimer produit au début\n");
        printf("5. Supprimer produit à la fin\n");
        printf("6. Supprimer un produit par référence\n");
        printf("7. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        switch (choix)
        {
            case 1:
                p = creer_produit();
                maListe = ajouter_debut(maListe, p);
                break;
            case 2:
                p = creer_produit();
                maListe = ajouter_fin(maListe, p);
                break;
            case 3:
                afficher_liste(maListe);
                break;
            case 4:
                maListe = supprimer_debut(maListe);
                break;
            case 5:
                maListe = supprimer_fin(maListe);
                break;
            case 6:
                printf("Entrer la référence à supprimer : ");
                scanf("%s", ref);
                maListe = rembourser(maListe, ref);
                break;
            case 7:
                printf("Fin du programme\n");
                break;
            default:
                printf("Choix invalide\n");
        }
    } while (choix != 7);
    return 0;
}
