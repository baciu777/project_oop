#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"

Produs *create(char* nume, char* producator, int cantitate){
	Produs* p = (Produs*)malloc(sizeof(Produs));
	size_t size_n = strlen(nume) + 1;
	if (p != NULL) {
		p->nume = malloc(sizeof(char) * size_n);
		if (p->nume != NULL)
			strcpy_s(p->nume, size_n, nume);
		size_t size_p = strlen(producator) + 1;
		p->producator = malloc(sizeof(char) * size_p);
		if (p->producator != NULL)
			strcpy_s(p->producator, size_p, producator);
		p->cantitate = cantitate;
	}
	return p;
}

void diss(Produs* p){
	free(p->nume);
	free(p->producator);
	p->nume = NULL;
	p->producator = NULL;
	p->cantitate = -1;
	free(p);

}

Produs* copyprodus(Produs* p){
	return create(p->nume, p->producator, p->cantitate);
}

int get_cantitate(Produs p){
	return p.cantitate;
}

char* get_nume(Produs p){
	return p.nume;
}

char* get_producator(Produs p){
	return p.producator;
}
void set_nume(Produs* p, char* nume){
	free(p->nume);
	size_t size_n= strlen(nume) + 1;
	p->nume = (char*)malloc(size_n * sizeof(char));
	if (p->nume != NULL) {
		strcpy_s(p->nume, size_n, nume);	
	}
}

void set_producator(Produs* p, char* producator){
	free(p->producator);
	size_t size_n = strlen(producator) + 1;
	p->producator = (char*)malloc(size_n * sizeof(char));
	if (p->producator != NULL)
		strcpy_s(p->producator, size_n, producator);
}

void set_cantitate(Produs* p, int cantitate){
	p->cantitate=cantitate;
}

int egale(Produs p1, Produs p2){
	if (strcmp(p1.nume, p2.nume)==0 && strcmp(p1.producator, p2.producator)==0)
		return 1;
	return 0;
}
