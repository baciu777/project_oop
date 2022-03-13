#ifndef sv_h
#define sv_h
#include "domain.h"
#include "repository.h"
#include "VectorDinamic.h"
//typedef struct Repository;
typedef struct {
	Repository* repo;
}Service;
/*
struct Service
contine un pointer unde se afla un repository

*/
Service* init_serv();
/*
* cp-numar natural
initializam service ul unde se vor stoca cp pozitii
*/
int add_serv(Service* serv, char* nume, char* producator, int cantitate, Vector* undoList);
/*
functie de adaugare element in service
serv-Service
nume- pointer char
producator- pointer char
cantitate- un numar natural
return 1 daca s a realizat
retrun 0, altfel
*/
int update_serv(Service* serv, char* nume, char* producator, int cantitate, Vector* undoList);
/*
functie de modificare element in service
serv-Service
nume- pointer char
producator- pointer char
cantitate- un numar natural
return 1 daca s a realizat
return 0, altfel
*/
int delete_serv(Service* serv, char* nume, char* producator, int cantitate, Vector* undoList);
/*
functie de stergere element in service
serv-Service
nume- pointer char
producator- pointer char
cantitate- un numar natural
return 1 daca s a realizat
retrun 0, altfel
*/
Repository* get_filtru_c(Service* serv, char c);
/*
functia de filtrare a elementelor
serv-pointer service
c-caracter
se returneaza un nou repository cu elementele filtrare
*/
Repository* get_filtru_cant(Service* serv, int cant);
/*
functie care filtreaza elementele care au cantitatea mai mica decant cant
serv-pointer service
cant-numar intreg
se returneaza un nou repository
*/
Repository* get_filtru_all(Service* serv,char c,int cant);
/*
functie care filtreaza elementele care au cantitatea mai mica decat cant si
numele incepe cu  caracterul c
serv-pointer service
cant-numar intreg
se returneaza un nou repository
*/
/*
Repository sort_nume_cresc(Service* serv);
/*
functie care sorteaza elementele crescator dupa nume
serv-pointer service
se returneaza un nou repository
*/
Repository* sort_nume_desc(Service* serv);
/*
functie care sorteaza elementele descrescator dupa nume
serv-pointer service
se returneaza un nou repository
*/
Repository* sort_cant_cresc(Service* serv);
/*
functie care sorteaza elementele crescator dupa cantitate
serv-pointer service
se returneaza un nou repository
*/
Repository* sort_cant_desc(Service* serv);
/*
functie care sorteaza elementele descrescator dupa cantitate
serv-pointer service
se returneaza un nou repository
*/

Repository* get_produse(Service* serv);
/*
functia ce returneaza produsele din service
serv- service
return- repository type
*/
Produs* get_produs(Service* serv, int poz);
/*
functia ce returneaza un produs din service de pe pozitia poz
serv- service
poz-numar natural
return- Produs type
*/
void distruge(Service* v);
/*
functia care distruge service ul creat
v- pointer serv
*/
typedef int(*FunctieComparare)(Produs* o1, Produs* o2);
int cmpnumecresc(Produs* p1, Produs* p2);
/*
functie compare nume cresc
p1,p2- pointer produs
return numar intreg
*/
int cmpcantcresc(Produs* p1, Produs* p2);
/*
functie compare cantitate cresc
p1,p2- pointer produs
return numar intreg
*/
int cmpnumedesc(Produs* p1, Produs* p2);
/*
functie compare nume desc
p1,p2- pointer produs
return numar intreg
*/
int cmpcantdesc(Produs* p1, Produs* p2);
/*
functie compare cantitate cresc
p1,p2- pointer produs
return numar intreg
*/
int undoOperation(Vector*, Service*);
/*
* Functia revine la stadiul inainte de ultima operatie
* Parametrii de intrare: undoList - Vector* 
*						 serv - Service*
* Parametrii de iesire:	1 - operatia a fost realizata cu succes
*						0 - nu mai exista nici o operatie de refacut
*/
Repository* sortare(Service* serv, FunctieComparare cmp);
/*
* functie de sortare
* serv-pointer service
* cmp-tip FunctieComparare
* se face sortarea elementelor dupa cmp
* se returneaza un nou repository
*/

#endif 