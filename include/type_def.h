#include <string>

#pragma once

using namespace std ;

struct personne
{
    string nom;
    string prenom;
    string numero;
};

struct elementListe
{
    personne personne;
    elementListe* suivant;
    elementListe* precedent;

};

