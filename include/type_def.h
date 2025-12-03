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
    personne pers;
    elementListe* suivant;
    elementListe* precedent;

};

