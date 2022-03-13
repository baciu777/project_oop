#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
Service* init_serv(){
	//Service* serv = (Service*)malloc(sizeof(Service));
	Service* serv = (Service*)malloc(sizeof(Service));
	if (serv != NULL)
		serv->repo = init_repo(2);
	return serv;
}
int add_serv(Service* serv, char* nume, char* producator, int cantitate, Vector* undoList){
	Produs* pr = create(nume, producator, cantitate);
	if (add(serv->repo, pr, undoList) == 0){
		diss(pr); 
		return 0;
	}
	return 1;

}
int update_serv(Service* serv, char* nume, char* producator, int cantitate, Vector* undoList){
	Produs* pr = create(nume, producator, cantitate);
	if (update(serv->repo, pr, undoList) == 0){
		diss(pr); 
		return 0;
	}
	return 1;

}
int delete_serv(Service* serv, char* nume, char* producator, int cantitate, Vector* undoList){
	Produs* pr = create(nume, producator, cantitate);
	if (delete(serv->repo, pr, undoList) == 1){
		diss(pr);
		return 1;
	}
	diss(pr);
	return 0;

}

int undoOperation(Vector* undoList, Service *serv) {
	if (!length(undoList))
		return 0;
	distruge_rp(serv->repo);
	serv->repo = copyRepo(ELEMENT(undoList, length(undoList)));
	deleteElement(undoList, length(undoList) - 1, distruge_rp);
	return 1;
}

Repository* filtrare_producator(Service* serv, char* producer) {
	Repository* temp = init_repo(2);
	Repository* nebunie = sortare(serv, cmpnumecresc);
	for (int i = 0; i < get_dim(nebunie); i++){
		Produs* prod = element(nebunie, i + 1);
		if (strcmp(get_producator(*prod), producer) == 0)
			add2(temp, copyprodus(prod));
	}
	distruge_rp(nebunie);
	return temp;
}

Repository* get_filtru_c(Service* serv, char c){
	Repository* repo_new = init_repo(2);
	for (int i = 0; i < get_dim(serv->repo); i++){
		Produs* pp = element(serv->repo, i + 1);
		if (get_nume(*pp)[0] == c)
			add2(repo_new, copyprodus(pp));
	}
	return repo_new;

}
Repository* get_filtru_cant(Service* serv, int cant){
	Repository* repo_new = init_repo(2);
	for (int i = 0; i < get_dim(serv->repo); i++){
		Produs* pp = element(serv->repo, i + 1);
		if (get_cantitate(*pp) < cant)
			add2(repo_new, copyprodus(pp));
	}
	return repo_new;

}
Repository* get_filtru_all(Service* serv, char c, int cant){
	Repository* repo_new = init_repo(2);
	for (int i = 0; i < get_dim(serv->repo); i++){
		Produs* pp = element(serv->repo, i + 1);
		if (get_nume(*pp)[0] == c && get_cantitate(*pp) < cant)
			add2(repo_new, copyprodus(pp));
	}
	return repo_new;
}
int cmpnumecresc(Produs* p1, Produs* p2)
{
	return strcmp(p1->nume, p2->nume);
}
int cmpnumedesc(Produs* p1, Produs* p2)
{
	return strcmp( p2->nume, p1->nume);
}
int cmpcantcresc(Produs* p1, Produs* p2)
{
	return p1->cantitate > p2->cantitate;
}
int cmpcantdesc(Produs* p1, Produs* p2)
{
	return  p1->cantitate < p2->cantitate;
}
Repository* sortare(Service* serv, FunctieComparare cmp)
{
	Repository* repo_new = copyRepo(serv->repo);
	for (int i = 0; i < get_dim(repo_new) - 1; i++)
		for (int j = i + 1; j < get_dim(repo_new); j++){
			Produs* p1 = element(repo_new, i + 1);
			Produs* p2 = element(repo_new, j + 1);
			if (cmp(p1, p2) > 0){
				Produs* aux = copyprodus(p1);
				set_cantitate(p1, get_cantitate(*p2));
				set_nume(p1, get_nume(*p2));
				set_producator(p1, get_producator(*p2));
				set_cantitate(p2, get_cantitate(*aux));
				set_nume(p2, get_nume(*aux));
				set_producator(p2, get_producator(*aux));
				diss(aux);
			}
		}
	return repo_new;
}

Repository* get_produse(Service* serv){	
	return copyRepo(serv->repo);
}
Produs* get_produs(Service* serv,int poz){
	return element(serv->repo, poz);
}

void distruge(Service* serv) {
	distruge_rp(serv->repo);
	free(serv);
}
