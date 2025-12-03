#include <iostream>

#include "include/utilitaire.h"
#include "include/utilitaire_generation.h"
#include "type_def.h"


void genererPersonne()
{
    personne personne;

    personne.nom = genererNomPrenom("Noms_TP4.txt", 1000);
    personne.prenom = genererNomPrenom("Prenoms_TP4.txt", 11612);
    personne.numero = genererTel();

}

void affichagePersonne(personne personne){
    
    cout << "==============================\n";
    cout << "          PERSONNE            \n";
    cout << "==============================\n";
    cout << "Nom        -> " << personne.nom    << "\n";
    cout << "Prénom     -> " << personne.prenom << "\n";
    cout << "Téléphone  -> " << personne.numero << "\n";
    cout << "==============================\n";

}