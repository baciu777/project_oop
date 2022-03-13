#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

Repository* init_repo(int cp){
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo != NULL)
		repo->e = createVector(cp);
	return repo;
}

Repository* copyRepo(Repository* repo) {
	Repository* rez = init_repo(2);
	for (int i = 0; i < length(repo->e); i++) {
		Produs* p = ELEMENT(repo->e, i + 1);
		add2(rez, copyprodus(p));
	}
	return rez;
}

void distruge_rp(Repository* repo) {
	destroyVector(repo->e, diss);
	free(repo);
}

int get_dim(Repository* repo) {
	return length(repo->e);
}

void addUndoList(Vector* undoList, Repository* repo) {
	Repository* temp = copyRepo(repo);
	addLastElement(undoList, temp);
}

Produs* element(Repository* v, int poz) {
	return ELEMENT(v->e, poz);
}

int add(Repository* repo, Produs* p, Vector* undoList){
	if (search(repo, p) >= 0)
		return 0;
	addUndoList(undoList, repo);
	addLastElement(repo->e, p);
	return 1;
}

int add2(Repository* repo, Produs* p){
	if (search(repo, p) >= 0)
		return 0;
	addLastElement(repo->e, p);
	return 1;
}

int update(Repository* repo, Produs* p, Vector* undoList){
	int poz = search(repo, p);
	if (poz < 0)
		return 0;
	addUndoList(undoList, repo);
	deleteElement(repo->e, poz, diss);
	insertElement(repo->e, poz, p);
	return 1;

}

int delete(Repository* repo, Produs* p, Vector* undoList){
	int poz = search(repo, p);
	if (poz < 0)
		return 0; 
	else {
		addUndoList(undoList, repo);
		deleteElement(repo->e, poz, diss);
		return 1;
	}
}

int search(Repository* repo, Produs* p){
	for (int i = 0; i < get_dim(repo); i++){
		Produs* temp = ELEMENT(repo->e, i + 1);
		if (egale(*temp, *p))
			return i;
	}
	return -1;
}