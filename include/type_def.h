#include <string>

#pragma once

using namespace std ;

struct personne
{
    string Nom;
    string Prenom;
    string Numero;
};

struct elementListe
{
    personne Personne;
    elementListe* suivant;
    elementListe* precedent;

};

