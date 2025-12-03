#include "../include/utilitaire.h"
#include "../include/type_def.h"




elementListe * creerElementListe(string name,string lastName,string phone){
    elementListe* new_el = new elementListe; //création de l'élement

    //On remplie les champs de la structure
    new_el->suivant = nullptr;
    new_el->precedent = nullptr;

    //On remplie l'élèment :
    new_el->pers.nom = lastName; 
    new_el->pers.prenom = name; 
    new_el->pers.numero = phone; 

    return new_el;
}


bool egalitePersonne(personne p1, personne p2){
    //comparaison :
    return (p1.nom == p2.nom) &&
           (p1.prenom == p2.prenom) &&  
           (p1.numero == p2.numero);
}