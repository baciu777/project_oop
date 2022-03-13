#ifndef domain_h
#define domain_h


typedef struct
{
	char* nume;
	char* producator;
	int cantitate;
}Produs;
/*
structura produs
nume- pointer de vector char
producator- pointer de vector char
cantitate- numar intreg
*/
void diss(Produs* p);
/*
distruge produs
*/
Produs* create(char* nume, char* producator, int cantitate);
/*
functia care creaza un produs
nume- pointer char
producator- pointer char
cantitate- numar natural
returneaza produsul creat
*/
Produs* copyprodus(Produs* p);
int get_cantitate(Produs p);
/*
functia care returneaza cantitatea unui produs
p- produs
*/
char* get_nume(Produs p);
/*
functia care returneaza numele unui produs
p- produs
*/
char* get_producator(Produs p);
/*
functia care returneaza producator unui produs
p- produs
*/
void set_nume(Produs* p, char* nume);
/*
functia care seteaza numele unui produs
p- produs
*/
void set_producator(Produs* p, char* producator);
/*
functia care seteaa producatorul unui produs
p- produs
*/
void set_cantitate(Produs* p, int cantitate);
/*
functia care seteaza cantitatea unui produs
p- produs
*/
int egale(Produs p1, Produs p2);
/*
functia care verifica daca 2 produse sunt egale
return 1, daca sunt egale
return 0, altfel
*/


#endif