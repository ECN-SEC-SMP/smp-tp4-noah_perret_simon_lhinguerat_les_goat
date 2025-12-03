# Rapport de TP4 - raitements d’image PGM

**Nom :** PERRET Noah & L'HINGUERAT Simon 

**Groupe :** SEC28

**Date :** 3 décembre 2025  

## Compilation et exécution

```bash
# Compilation normale
make

# Exécution du main 

./main


# Nettoyage
make clean
```

## Préambule : Représentation des images .PGM

### Choix de représentation :


# 2 - TRUCTURES DE DONNÉES

## Q1) Structure `personne` :

Pour représenter une personne, nous utilisons la structure personne, qui contient les informations essentielles sous forme de chaînes de caractères :

```cpp
struct personne
{
    string nom;
    string prenom;
    string numero;
};
```


**Justification du choix :**
- **Nom et prénom** : Stockés sous forme de string pour permettre la flexibilité de taille et la gestion facile des caractères.
- **Numéro de téléphone** : Stocké sous forme de string (10 chiffres, sans espaces) pour conserver les zéros initiaux et éviter toute interprétation numérique qui pourrait tronquer ou modifier la valeur.
- **Simplicité et lisibilité** : L’usage de chaînes de caractères rend la manipulation (affichage, comparaison, tri) simple et intuitive en C++.
- **Extensibilité** : Cette structure peut être facilement enrichie avec d’autres champs si nécessaire (adresse, email, etc.) sans changer le type de données existant.

### Exemple de représentation :

En mémoire, cette organisation permet de gérer efficacement une liste de personnes pour des opérations comme le tri, la recherche ou l’affichage.

```cpp
personne p1;
p1.nom = "Dupont";
p1.prenom = "Jean";
p1.numero = "0612345678";
```


## Q2) Structure `elementList` :

Pour représenter une liste de personnes, nous utilisons la structure elementListe, qui permet de créer une liste doublement chaînée :

```cpp
struct elementListe
{
    personne pers;
    elementListe* suivant;
    elementListe* precedent;
};
```

**Justification du choix :**
- **Double chaînage** : Les pointeurs `suivant` et `precedent` permettent de naviguer dans les deux sens de la liste, ce qui facilite les opérations d’insertion, de suppression et de parcours.
- **Stockage des données** : Chaque élément contient la structure personne précedemetn définies cela centralise  les informations liées à une personne dans un seul nœud.
- **Simplicité et flexibilité** : L’utilisation de pointeurs rend la liste dynamique, donc on n’a pas besoin de connaître la taille maximale à l’avance.
- **Extensibilité** : La structure peut facilement être enrichie si l’on souhaite ajouter d’autres informations pour chaque personne (adresse, email, etc.).

### Exemple de représentation en mémoire:

```cpp
elementListe* el1 = new elementListe;
el1->pers.nom = "Dupont";
el1->pers.prenom = "Jean";
el1->pers.numero = "0612345678";
el1->suivant = nullptr;
el1->precedent = nullptr;
```

Dans cet exemple, el1 représente un nœud unique de la liste doublement chaînée.

el1->pers contient les informations d’une personne : nom, prénom et numéro de téléphone.

el1->suivant et el1->precedent sont initialisés à nullptr car pour l’instant cet élément n’est relié à aucun autre nœud.

---

# 3 - UTILITAIRES

### Fonction  de différence `genererPersonne()`

#### Algorithmes

<img src="./assets/UML_difference.png" alt="Diagramme UML de differencePgm" width="300" />


#### Description du principe :
Calcule l'image de la différence entre les images `img1` et `img2`.         L'algorithme calcule la valeur absolue de la différence entre chaque pixels des images d'entrer puis stocke ce résultat dans le pixel correspondant de l'image de sortie `imgMod`.


#### Prototypes
```cpp
void differencePgm(t_Image * imgMod, t_Image *  img1, t_Image *  img2);
```

#### Jeux d'essais 

```cpp
void test_difference(){
    //Allocation dynamique des images
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_img2 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement

    //Chargement des images :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"plane"+size1+endFile,ptr_img2,success);
    loadPgm(pathBasic+"noir"+size1+endFile,ptr_imgMod,success);

    //Calcul de la différence :
    differencePgm(ptr_imgMod,ptr_img1,ptr_img2);

    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"lenaplane"+size1+endFile,ptr_imgMod);

    //Libération de la mémoire :
    delete ptr_img1;
    delete ptr_img2;
    delete ptr_imgMod;
}
```
![test_difference](assets/lenaplage.png)

---


## Q2) Choix de la structure de l'élément structurant:

### Choix de représentation :

Pour représenter l’élément structurant, nous nous sommes appuyés sur la structure `t_Image`. <br> Toutefois, comme notre projet ne manipule que des images binaire noir et blanc, nous avons adapté cette structure : chaque pixel de l’élément structurant est désormais représenté par un booléen (true ou false).<br> Cette simplification permet de réduire la taille de stockage de la structure.

```cpp
const int tailleMaxMatrice = 16; //taille maximale de l'élément structurant

typedef  bool t_MatStructurante[tailleMaxMatrice][tailleMaxMatrice]; 

typedef struct{ //élèment structurant
    u_int16_t size; //largeur de l'élèment structurant
	t_MatStructurante em; //tableau des niveaux de gris de le l'élèment structurant
}t_structurant; 
```
## Q3) Fonctions dilatation et érosion :


### Fonction  `erosionPgm()` (Noah)

#### Algorithmes

<img src="./assets/UML_erosion.png" alt="Diagramme UML de l'érosion" width="300" />


#### Description du principe :
L’érosion est une opération fondamentale de traitement d’image binaire utilisée pour réduire les objets blancs (ou noirs) et éliminer les petits détails dans une image. Elle s’appuie sur un élément structurant `t_structurant` qui définit la forme et la taille de l’érosion.


#### Prototypes
```cpp
void erosionPgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
```

#### Jeux d'essais 

```cpp
void test_erosion(){
    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;
    fill_ES(ptr_elementStructurant,3,1);

    bool success = false; //Indicateur de succès du chargement

    //Image 1 avec fond blanc
    //Chargement des images :
    loadPgm(pathBasic+"visageBinaire"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size2+endFile,ptr_imgMod,success);

    //Erosion :
    erosionPgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"visageErosion"+size2+endFile,ptr_imgMod);

    //Image 2 avec fond noir
    /**Voir Code Main pour plus de détails**/
   
    //Libération de la mémoire :
    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}
```
![test_erosion](assets/test_erosion.png)

---


### Fonction  `dilatation()` (Simon)

#### Algorithmes

<img src="./assets/UML_dilatation.png" alt="Diagramme UML de dilatation" width="350" />


#### Description du principe :
La dilatation est une opération fondamentale de traitement d’image binaire utilisée pour agrandir les objets blancs (ou noirs) et combler les petits trous dans une image. Elle s’appuie sur un élément structurant `t_structurant` qui définit la forme et la taille de l’expansion.


#### Prototypes
```cpp
void dilatation(t_Image * Image, t_Image * Image_D, short COULEUR);
```

#### Jeux d'essais 

```cpp
void test_dilatation(){
    ///Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod_2 = new t_Image;
    bool success = false; //Indicateur de succès du chargement

    //Chargement des images :
    loadPgm(pathBasic+"visageBinaireOriginal"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size2+endFile,ptr_imgMod_2,success);

    dilatation(ptr_img1,ptr_imgMod_2,NOIR);

    savePgm(pathMod+"visageBinaireDilatation"+size2+endFile,ptr_imgMod_2);
    //Libération de la mémoire :
    delete ptr_img1;

    delete ptr_imgMod_2;
}//...
```
![test_seuil](assets/dilatation.png)

---




## Q4) Fonctions d'ouverture et de fermeture :


### Fonction  `ouverturePgm()` (Simon)

#### Algorithmes

<img src="./assets/UML_ouverture.png" alt="Diagramme UML de l'érosion" width="250" />


#### Description du principe :
L’ouverture est une opération morphologique qui combine une érosion suivie d’une dilatation. Elle est utilisée pour supprimer les petites structures ou bruits dans une image tout en préservant la forme générale des objets plus grands.


#### Prototypes
```cpp
void ouverturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
```

#### Jeux d'essais 

```cpp
void test_ouverture(){
    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;
    //Initialisation de l'élément structurant (matrice 3x3 pleine) :
    fill_ES(ptr_elementStructurant,3,1);

    //Chargement des images :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size1+endFile,ptr_imgMod,success);


    seuil(ptr_img1,125);

    ouverturePgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    savePgm(pathMod+"lenaOuverture"+size1+endFile,ptr_imgMod);

    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}
```
![test_seuil](assets/ouverture.png)

---


### Fonction  `fermeturePgm()` (Noah)

#### Algorithmes

<img src="./assets/UML_fermeture.png" alt="Diagramme UML de dilatation" width="250" />


#### Description du principe :
La fermeture est l’opération inverse de l’ouverture, qui combine une dilatation suivie d’une érosion. Elle est utilisée pour combler les petites trous ou fissures dans les objets tout en conservant leur forme globale.


#### Prototypes
```cpp
void fermeturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
```

#### Jeux d'essais 

```cpp
void test_fermeture(){
    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;
    //Initialisation de l'élément structurant (matrice 3x3 pleine) :
    fill_ES(ptr_elementStructurant,3,1);

    //Chargement des images :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size1+endFile,ptr_imgMod,success);

    seuil(ptr_img1,125);


    fermeturePgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    savePgm(pathMod+"lenaFermeture"+size1+endFile,ptr_imgMod);

    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}
```
![test_seuil](assets/fermeture.png)

---














