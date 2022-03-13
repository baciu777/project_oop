#ifndef rp_h
#define rp_h
#include "domain.h"
#include "VectorDinamic.h"

typedef struct {
	Vector* e;
}Repository;
/*
structura Repository
cp- numar intreg
e- pointer produs
n-numar natural
*/
Repository* init_repo(int cp);
/*
* initializare repository
* cp-numar natural
* se returneaza un repository creat
*/
void distruge_rp(Repository* v);
/*
functia care distruge repository ul creat
v-pointer repository 
*/
int get_dim(Repository* v);
/*
returneaza numarul de elemente din repository
v- pointer repository
*/
Produs* element(Repository* v, int poz);
/*
v- pointer repository
poz- numar natural
se returneaza produsul de pe pozitia poz
*/
int add(Repository* repo, Produs* p, Vector* undoList);
/*
functie adaugare produs in repository
repo-pointer repository
p- produs
return 1, daca s a realizat cu succes
return 0,altfel
*/
int add2(Repository* repo, Produs* p);
/*
functie adaugare produs in repository (only for copyRepo)
repo-pointer repository
p- produs
return 1, daca s a realizat cu succes
return 0,altfel
*/
int update(Repository* repo, Produs* p, Vector* undoList);
/*
functie modificare produs in repository
repo-pointer repository
p- produs
return 1, daca s a realizat cu succes
return 0,altfel
*/
int search(Repository* repo, Produs* p);
/*
functie cautare produs in repository
repo-pointer repository
p- produs
return 1, daca s a realizat cu succes
return 0,altfel
*/
int delete(Repository* repo, Produs* p, Vector* undoList);
/*
functie stergere produs in repository
repo-pointer repository
p- produs
return 1, daca s a realizat cu succes
return 0,altfel
*/
Repository* copyRepo(Repository* repo);
/*
functie care face o copie la elemente
repo-pointer repository
se returneaza un nou repository*/
void addUndoList(Vector* undoList, Repository* repo);
/*
* functia adauga o copie a repositoryului in undoList
* undoList - Vector*
* repo - Repository*
* nu returneaza nimic
*/
#endif 