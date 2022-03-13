#ifndef ui_h
#define ui_h
#include "main.h"
void add_ui(Service* serv, Vector* undoList);
/*
* functie de adaugare 
* serv-pointer service
* se citesc elementele si se verifica daca datele sunt valide
* dupa se apeleaza fc de addaugare la service
*/
void update_ui(Service* serv, Vector* undoList);
/*
* functie de modificare
* serv-pointer service
* se citesc elementele si se verifica daca datele sunt valide
* dupa se apeleaza fc de addaugare la service
*/
void delete_ui(Service* serv, Vector* undoList);
/*
* functie de stergere
* serv-pointer service
* se citesc elementele si se verifica daca datele sunt valide
* dupa se apeleaza fc de addaugare la service
*/
void filtrare_caracter(Service* serv);
/*
functia de filtrare dupa un caracter citit
serv-pointer service
se citeste un caracter si se apeleaza functia de filtrare din service
*/
void filtru(Service* serv);
/*
functie de meniu-filtrare
*/
void filtrare_all(Service* serv);
/*
functie de filtrare dupa un caracter citit si cantitatea maxima
serv-pointer service
se citeste un caracter si un numar intreg si se apeleaza functia din service
*/
void filtrare_cantitate(Service* serv);
/*
functie de filtrare dupa un caracter citit 
serv-pointer service
se citeste un numar intreg si se apeleaza functia din service
*/
Repository* filtrare_producator(Service* serv, char* producer);
/*
* Functia filtreaza produsele dupa un producator dat
* Date de intrare:	serv - Service*
*					producer - char*
* Date de iesire: repo - Repository
*/
void undo(Service* serv, Vector* undoList);
/*
* Functia reface ultima operatie
* Date de intrare:  serv - Service*
*					undoList- Vector*
* Date de iesire: - 
*/
void sort(Service* serv);
/*
* Functia sorteaza un repository si afiseaza elementele sortate
* Date de intrare: serv - Service*
* Date de iesire: -
*/
void run(Service* serv, Vector* undoList);
/*
functie care ruleaza programul
serv-pointer service
se citeste o comanda pana la "-1"
se valideaza comanda
*/
void print(Produs p);
/*
functia care afiseaza un produs
p- produs
*/
#endif