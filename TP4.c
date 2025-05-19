#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant
{
    int id;
    char nom[50];
    float moyenne;
    struct Etudiant* suivant;
    struct Etudiant* precedent;
} Etudiant;

Etudiant* creer_etudiant()
{
    Etudiant* nouveau = (Etudiant*)malloc(sizeof(Etudiant));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }

    printf("Entrez l'ID de l'etudiant: ");
    scanf("%d", &nouveau->id);
    getchar();

    printf("Entrez le nom de l'etudiant: ");
    fgets(nouveau->nom, 50, stdin);
    nouveau->nom[strcspn(nouveau->nom, "\n")] = '\0';

    printf("Entrez la moyenne de l'etudiant: ");
    scanf("%f", &nouveau->moyenne);

    nouveau->suivant = NULL;
    nouveau->precedent = NULL;

    return nouveau;
}

int longueur(Etudiant* tete)
{
    int count = 0;
    Etudiant* courant = tete;
    while (courant != NULL)
    {
        count++;
        courant = courant->suivant;
    }
    return count;
}

Etudiant* ajouter_position(Etudiant* tete, Etudiant* nouveau, int position)
{
    if (position < 0 || position > longueur(tete))
    {
        printf("Position invalide\n");
        return tete;
    }

    if (position == 0)
    {
        nouveau->suivant = tete;
        if (tete != NULL)
        {
            tete->precedent = nouveau;
        }
        return nouveau;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position - 1 && courant != NULL; i++)
    {
        courant = courant->suivant;
    }

    if (courant == NULL)
    {
        printf("Position invalide\n");
        return tete;
    }

    nouveau->suivant = courant->suivant;
    nouveau->precedent = courant;
    if (courant->suivant != NULL)
    {
        courant->suivant->precedent = nouveau;
    }
    courant->suivant = nouveau;

    return tete;
}

Etudiant* supprimer_position(Etudiant* tete, int position)
{
    if (tete == NULL || position < 0 || position >= longueur(tete))
    {
        printf("Position invalide ou liste vide\n");
        return tete;
    }

    if (position == 0)
    {
        Etudiant* nouvelle_tete = tete->suivant;
        if (nouvelle_tete != NULL)
        {
            nouvelle_tete->precedent = NULL;
        }
        free(tete);
        return nouvelle_tete;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position && courant != NULL; i++)
    {
        courant = courant->suivant;
    }

    if (courant == NULL)
    {
        printf("Position invalide\n");
        return tete;
    }

    if (courant->precedent != NULL)
    {
        courant->precedent->suivant = courant->suivant;
    }
    if (courant->suivant != NULL)
    {
        courant->suivant->precedent = courant->precedent;
    }
    free(courant);

    return tete;
}

void afficher_liste(Etudiant* tete)
{
    if (tete == NULL)
    {
        printf("La liste est vide\n");
        return;
    }

    printf("\nListe des etudiants (de la tete a la fin):\n");
    printf("----------------------------------------\n");
    Etudiant* courant = tete;
    while (courant != NULL)
    {
        printf("ID: %d, Nom: %s, Moyenne: %.2f\n", courant->id, courant->nom, courant->moyenne);
        courant = courant->suivant;
    }
    printf("----------------------------------------\n");
}

Etudiant* derniere_cellule(Etudiant* tete)
{
    if (tete == NULL)
    {
        return NULL;
    }

    Etudiant* courant = tete;
    while (courant->suivant != NULL)
    {
        courant = courant->suivant;
    }
    return courant;
}

void afficher_liste_inverse(Etudiant* dernier)
{
    if (dernier == NULL)
    {
        printf("La liste est vide\n");
        return;
    }

    printf("\nListe des etudiants (de la fin vers le debut):\n");
    printf("----------------------------------------\n");
    Etudiant* courant = dernier;
    while (courant != NULL)
    {
        printf("ID: %d, Nom: %s, Moyenne: %.2f\n", courant->id, courant->nom, courant->moyenne);
        courant = courant->precedent;
    }
    printf("----------------------------------------\n");
}

int chercher_etudiant(Etudiant* tete, int id)
{
    Etudiant* courant = tete;
    while (courant != NULL)
    {
        if (courant->id == id)
        {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

Etudiant* tri(Etudiant* tete)
{
    if (tete == NULL || tete->suivant == NULL)
    {
        return tete;
    }

    Etudiant* courant = tete->suivant;
    while (courant != NULL)
    {
        Etudiant* suivant = courant->suivant;
        Etudiant* precedent = courant->precedent;

        if (precedent != NULL)
        {
            precedent->suivant = suivant;
        }
        if (suivant != NULL)
        {
            suivant->precedent = precedent;
        }

        Etudiant* temp = precedent;
        while (temp != NULL && temp->moyenne > courant->moyenne)
        {
            temp = temp->precedent;
        }

        if (temp == NULL)
        {
            courant->suivant = tete;
            courant->precedent = NULL;
            tete->precedent = courant;
            tete = courant;
        }
        else
        {
            courant->suivant = temp->suivant;
            courant->precedent = temp;
            if (temp->suivant != NULL)
            {
                temp->suivant->precedent = courant;
            }
            temp->suivant = courant;
        }

        courant = suivant;
    }

    return tete;
}

Etudiant* modifier_moyenne(Etudiant* tete, int position, float nouvelle_moyenne)
{
    if (tete == NULL || position < 0 || position >= longueur(tete))
    {
        printf("Position invalide ou liste vide\n");
        return tete;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position && courant != NULL; i++)
    {
        courant = courant->suivant;
    }

    if (courant != NULL)
    {
        courant->moyenne = nouvelle_moyenne;
    }

    return tete;
}

void liberer_liste(Etudiant* tete)
{
    Etudiant* courant = tete;
    while (courant != NULL)
    {
        Etudiant* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
}

int main()
{
    Etudiant* liste = NULL;
    int choix, position, id;
    float nouvelle_moyenne;

    printf("GESTION DES ETUDIANTS - LISTE DOUBLEMENT CHAINEE\n");

    do
    {
        printf("\nMenu:\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher la liste\n");
        printf("3. Afficher la liste en inverse\n");
        printf("4. Supprimer un etudiant\n");
        printf("5. Rechercher un etudiant par ID\n");
        printf("6. Trier la liste par moyenne\n");
        printf("7. Modifier la moyenne d'un etudiant\n");
        printf("8. Afficher la longueur de la liste\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
            {
                Etudiant* nouvel_etudiant = creer_etudiant();
                printf("Position d'insertion (0 pour tete, %d pour fin): ", longueur(liste));
                scanf("%d", &position);
                liste = ajouter_position(liste, nouvel_etudiant, position);
                break;
            }
            case 2:
                afficher_liste(liste);
                break;
            case 3:
                afficher_liste_inverse(derniere_cellule(liste));
                break;
            case 4:
                printf("Position de suppression (0 a %d): ", longueur(liste)-1);
                scanf("%d", &position);
                liste = supprimer_position(liste, position);
                break;
            case 5:
                printf("ID a rechercher: ");
                scanf("%d", &id);
                if (chercher_etudiant(liste, id))
                {
                    printf("Etudiant trouve!\n");
                }
                else
                {
                    printf("Etudiant non trouve.\n");
                }
                break;
            case 6:
                liste = tri(liste);
                printf("Liste triee par moyenne.\n");
                break;
            case 7:
                printf("Position de l'etudiant a modifier (0 a %d): ", longueur(liste)-1);
                scanf("%d", &position);
                printf("Nouvelle moyenne: ");
                scanf("%f", &nouvelle_moyenne);
                liste = modifier_moyenne(liste, position, nouvelle_moyenne);
                break;
            case 8:
                printf("Longueur de la liste: %d\n", longueur(liste));
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);

    liberer_liste(liste);
    return 0;
}
