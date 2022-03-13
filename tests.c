#include "tests.h"
#include "main.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
void testVector() {
	Vector* v = createVector(2);
	assert(length(v) == 0);
	assert(v->capacity == 2);
	Produs* p1 = create("racheta", "spacex", 10);
	addLastElement(v, p1);
	assert(length(v) == 1);
	Produs* temp = ELEMENT(v, 1); /// temp == p1 (au aceeasi adresa)
	assert(strcmp(get_nume(*temp), "racheta") == 0);
	assert(strcmp(get_producator(*temp), "spacex") == 0);
	assert(get_cantitate(*temp) == 10);
	Produs* p2 = create("masina", "maseratti", 100);
	Produs* p3 = create("pateu", "bucegi", 100);
	Produs* p4 = create("lavazza", "giuseppe", 100);
	addLastElement(v, p2);
	assert(length(v) == 2);
	addLastElement(v, p3);
	assert(length(v) == 3);
	assert(v->capacity == 4);
	insertElement(v, 2, p4);
	assert(length(v) == 4);
	assert(v->capacity == 8);
	deleteElement(v, 3, diss); // rip p3
	assert(length(v) == 3);
	deleteElement(v, 2, diss); // rip p4

	assert(length(v) == 2);
	reverse(v);
	/// nu ne ocupam de rez1 si rez2 pt ca sunt referinte din vector nu copii
	Produs* rez1 = ELEMENT(v, 1), * rez2 = ELEMENT(v, 2);
	assert(strcmp(get_nume(*rez2), "racheta") == 0);
	assert(strcmp(get_producator(*rez2), "spacex") == 0);
	assert(get_cantitate(*rez2) == 10);
	assert(strcmp(get_nume(*rez1), "masina") == 0);
	assert(strcmp(get_producator(*rez1), "maseratti") == 0);
	assert(get_cantitate(*rez1) == 100);
	
	Iterator* it = createIterator(v);
	assert(it->curent == 0);
	next(it);
	assert(it->curent == 1);
	rez2 = elementI(it);
	assert(strcmp(get_nume(*rez2), "racheta") == 0);
	assert(strcmp(get_producator(*rez2), "spacex") == 0);
	assert(get_cantitate(*rez2) == 10);
	assert(validate(it) == 1);
	next(it);
	assert(validate(it) == 0);
	first(it);
	assert(it->curent == 0);
	destroyIterator(it);
	destroyVector(v, diss); // sterge el elementele pt ca le tine minte adresa lmao 
}
void domain_test()
{
	Produs* a = create("first", "prod1", 5);
	assert(5 == get_cantitate(*a));
	assert(strcmp(a->nume, "first")==0);
	assert(strcmp(a->producator, "prod1") == 0);
	set_nume(a, "eu");
	set_producator(a, "ff");
	set_cantitate(a, 5);
	assert(strcmp(get_producator(*a), "ff")==0);
	assert(strcmp(get_nume(*a), "eu") == 0);
	diss(a);
}
void repository_test()
{
	Vector* undoList = createVector(2);
	Repository* repo = init_repo(2);
	Produs* a = create("first", "prod1", 5);
	add(repo, a, undoList);
	assert(get_dim(repo) == 1);

	Produs* lala = create("cv", "cv", 5);
	assert(delete(repo, lala, undoList) == 0);
	assert(update(repo,lala, undoList) == 0);

	Produs* a2 = create("second", "prod2", 10);
	add(repo, a2, undoList);
	assert(get_dim(repo) == 2);

	Produs* p1 = element(repo, 1);
	assert(egale(*p1, *a)==1);
	Produs* p2 = element(repo, 2);
	assert(egale(*p2, *a2) == 1);
	assert(get_dim(repo) == 2);

	Produs* u1 = create("second", "prod2", 9999);
	update(repo, u1, undoList);
	assert(add2(repo, u1) == 0);
	assert(get_dim(repo) == 2);
	assert(get_cantitate(*u1) == 9999);
	Produs* rez1 = element(repo, 2);
	assert(get_cantitate(*rez1)==9999);
	Produs* d1 = create("second", "prod2", 9999);
	delete(repo, d1, undoList);
	assert(get_dim(repo) == 1);
	Produs* p3 = element(repo, 1);
	Produs* rez2= create("first", "prod1", 5);
	assert(egale(*p3, *rez2) == 1);
	diss(d1);
	diss(rez2);
	diss(lala);
	distruge_rp(repo);
	destroyVector(undoList, distruge_rp);
}

void service_test()
{
	Service* serv = init_serv(2);
	Vector* undoList = createVector(2);
	assert(undoOperation(undoList, serv) == 0);
	add_serv(serv, "first","prod1",5, undoList);
	assert(get_dim(serv->repo)==1);
	Produs* p1 = get_produs(serv, 1);
	Produs* a1 = create("first", "prod1", 5);
	assert(egale(*p1, *a1)==1);

	add_serv(serv, "second", "prod2", 11, undoList);
	assert(length(undoList) == 2);
	undoOperation(undoList, serv);
	assert(get_dim(serv->repo) == 1);
	assert(length(undoList) == 1);
	undoOperation(undoList, serv);
	assert(get_dim(serv->repo) == 0);
	assert(length(undoList) == 0);
	add_serv(serv, "first","prod1",5, undoList);
	add_serv(serv, "second", "prod2", 11, undoList);
	assert(get_dim(serv->repo) == 2);

	update_serv(serv, "first", "prod1", 9999, undoList);
	assert(get_dim(serv->repo) == 2);

	Produs* s1 = get_produs(serv, 1);
	assert(get_cantitate(*s1) == 9999);
	delete_serv(serv, "first", "prod1",5, undoList);
	add_serv(serv, "f1", "prod1", 5, undoList);
	assert(add_serv(serv, "f1", "prod1", 5, undoList) == 0);
	add_serv(serv, "f2", "prod1", 10, undoList);
	add_serv(serv, "f3", "prod1", 9, undoList);
	add_serv(serv, "ee", "prod1", 15, undoList);
	char c = 'f';
	update_serv(serv, "asda", "as", 5, undoList);
	delete_serv(serv, "asda", "as", 5, undoList);
	
	diss(a1);
	
	Repository* repo = filtrare_producator(serv, "prod1");

	Produs* pp1 = element(repo, 1);
	Produs* pp2 = element(repo, 2);
	Produs* pp3 = element(repo, 3);

	assert(strcmp(get_nume(*pp1), "ee") == 0);
	assert(strcmp(get_nume(*pp2), "f1") == 0);
	assert(strcmp(get_nume(*pp3), "f2") == 0);

	distruge_rp(repo);

	repo = get_filtru_all(serv, c, 10);
	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	pp3;

	assert(strcmp(get_nume(*pp1), "f1") == 0);
	assert(strcmp(get_nume(*pp2), "f3") == 0);
	assert(get_cantitate(*pp1) == 5);
	assert(get_cantitate(*pp2) == 9);

	distruge_rp(repo);

	repo = get_filtru_c(serv, 'f');
	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	pp3 = element(repo, 3);
	assert(strcmp(get_nume(*pp1), "f1") == 0);
	assert(strcmp(get_nume(*pp2), "f2") == 0);
	assert(strcmp(get_nume(*pp3), "f3") == 0);

	distruge_rp(repo);
	
	repo = get_filtru_cant(serv, 10);

	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	assert(get_cantitate(*pp1) == 5);
	assert(get_cantitate(*pp2) == 9);

	distruge_rp(repo);

	repo = sortare(serv,cmpnumecresc);
	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	pp3 = element(repo, 3);

	assert(strcmp(get_nume(*pp1), "ee") == 0);
	assert(strcmp(get_nume(*pp2), "f1") == 0);
	assert(strcmp(get_nume(*pp3), "f2") == 0);

	distruge_rp(repo);

	repo = sortare(serv,cmpnumedesc);
	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	pp3 = element(repo, 3);
	assert(strcmp(get_nume(*pp3), "f2") == 0);
	assert(strcmp(get_nume(*pp2), "f3") == 0);
	assert(strcmp(get_nume(*pp1), "second") == 0);

	distruge_rp(repo);

	repo = sortare(serv,cmpcantcresc);
	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	pp3 = element(repo, 3);
	assert(strcmp(get_nume(*pp1), "f1") == 0);
	assert(strcmp(get_nume(*pp2), "f3") == 0);
	assert(strcmp(get_nume(*pp3), "f2") == 0);

	distruge_rp(repo);

	repo = sortare(serv,cmpcantdesc);
	pp1 = element(repo, 1);
	pp2 = element(repo, 2);
	pp3 = element(repo, 3);

	assert(strcmp(get_nume(*pp1), "ee") == 0);
	assert(strcmp(get_nume(*pp2), "second") == 0);
	assert(strcmp(get_nume(*pp3), "f2") == 0);
	distruge_rp(repo);

	repo = get_produse(serv);
	distruge_rp(repo);
	repo = copyRepo(serv->repo);
	assert(get_dim(repo) == 5);
	distruge_rp(repo);
	distruge(serv);
	destroyVector(undoList, distruge_rp);
}

void run_all_tests()
{
	domain_test();
	testVector();
	repository_test();
	service_test();
	_CrtDumpMemoryLeaks();
}