#include <stdio.h>
#include <string.h>
#include "main.h"

void add_ui(Service* serv, Vector* undoList)
{
	printf(" da nume/producator/cantitate\n");
	char nume[20];
	char producator[20];
	int cantitate = 0;
	scanf_s("%s", &nume,20);
	scanf_s("%s", &producator,20);
	int valid = scanf_s("%d", &cantitate);
	

	if (valid == 1)
	{
		
		if (add_serv(serv, nume, producator, cantitate, undoList) ==0)
			printf("produsul se afla deja in stoc\n");
	}
	else
	{
		while (getchar() != '\n')
		{
		}
		printf("date gresite\n");
	}
	
}
void update_ui(Service* serv, Vector* undoList)
{
	printf(" da nume/producator/cantitate\n");
	char nume[20];
	char producator[20];
	int cantitate = 0;
	scanf_s("%s", &nume,20);
	scanf_s("%s", &producator,20);
	int valid = scanf_s("%d", &cantitate);
	
	if (valid == 1)
	{
		if (update_serv(serv, nume, producator, cantitate, undoList) != 1)
			printf("produsul nu se afla in stoc\n");
	}
	else
	{
		while (getchar() != '\n')
		{
		}
		printf("date gresite\n");
	}
}
void delete_ui(Service* serv, Vector* undoList)
{
	printf(" da nume/producator\n");
	char nume[20];
	char producator[20];
	scanf_s("%s", &nume,20);
	scanf_s("%s", &producator,20);
	int cantitate = 100;
	

		if (delete_serv(serv, nume, producator, cantitate, undoList) != 1)
			printf("produsul nu se afla in stoc\n");

}
void undo(Service* serv, Vector* undoList) {
	if (undoOperation(undoList, serv))
		printf("Undo done succesfully!\n");
	else
		printf("No operations left to reverse!\n");
}
void afisare_ui(Service* serv)
{
	
	Repository* p = get_produse(serv);
	int found=0;
	for (int i = 1; i <= get_dim(p); i++)
	{
		found = 1;
		Produs* pr = get_produs(serv, i);
		printf("Produs: ");
		print(*pr);
		printf("\n");
		//printf("%s %s % d", get_nume(pr), get_producator(pr), get_cantitate(pr));
	}
	if (!found)
	printf("0 produse\n");
	distruge_rp(p);
}
void filtru(Service* serv)
{
		printf("filtrare dupa producator?\n");
		char string3[20];
		scanf_s("%s", &string3, 20);
		string3[strlen(string3)] = '\0';
		if (strcmp(string3, "yes") == 0) {
			char producer[30];
			printf("Ce producator doriti?\n>>> ");
			scanf_s("%s", &producer, 30);
			Repository* temp = filtrare_producator(serv, producer);
			if (get_dim(temp) == 0) {
				printf("Nu exista produse fabricate de %s\n", producer);
			}
			else
				for (int i = 0; i < get_dim(temp); i++)
				{
					Produs* pr = element(temp, i + 1);
					printf("Produs: ");
					print(*pr);
					printf("\n");
				}
			distruge_rp(temp);
		}
		else {
			printf("filtrare dupa un primul caracter din nume?\n");
			char string1[20];
			scanf_s("%s", &string1, 20);
			printf("filtrare dupa cantitatea maxima?\n");	
			char string2[20];
			scanf_s("%s", &string2, 20);
			string1[strlen(string1)] = '\0';
			string2[strlen(string2)] = '\0';
			if (strcmp(string1, "yes") == 0 && strcmp(string2, "yes") != 0)
				filtrare_caracter(serv);
			else
			{
				if (strcmp(string1, "yes") == 0 && strcmp(string2, "yes") == 0)
					filtrare_all(serv);

				else



					if (strcmp(string2, "yes") == 0)
						filtrare_cantitate(serv);
			}
		}
}
void filtrare_caracter(Service* serv)
{
	char caracter;
	printf("da caracter: ");

	scanf_s(" %c", &caracter,20);
	
	Repository* repo = get_filtru_c(serv, caracter);
	int found = 0;
	if (get_dim(repo) > 0)
	{
		for (int i = 0; i < get_dim(repo); i++)
		{
			Produs* pr = element(repo, i + 1);
			printf("Produs: ");
			print(*pr);
			printf("\n");
			//printf("%s %s % d", get_nume(pr), get_producator(pr), get_cantitate(pr));
			found = 1;
		}
	}
	else
		printf("nu sunt elemente\n");
	distruge_rp(repo);

}
void filtrare_all(Service* serv)
{
	char caracter;
	int cant;
	printf("da caracter: ");
	scanf_s(" %c", &caracter,20);
	printf("da cantitate: ");
	scanf_s("%d", &cant);
	while (getchar() != '\n')
	{
	}
	Repository* repo = get_filtru_all(serv, caracter,cant);
	
	int found = 0;
	if (get_dim(repo) > 0)
	{
		for (int i = 0; i < get_dim(repo); i++)
		{
			Produs* pr = element(repo, i + 1);
			printf("Produs: ");
			print(*pr);
			printf("\n");
			//printf("%s %s % d", get_nume(pr), get_producator(pr), get_cantitate(pr));
			found = 1;
		}
	}
	else
		printf("nu sunt elemente\n");
	distruge_rp(repo);

}
void filtrare_cantitate(Service* serv)
{
	int cant;
	printf("da cantitate: ");
	scanf_s("%d", &cant);
	while (getchar() != '\n')
	{
	}
	Repository* repo = get_filtru_cant(serv, cant);
	int found = 0;
	if (get_dim(repo) > 0)
	{
		for (int i = 0; i < get_dim(repo); i++)
		{
			Produs* pr = element(repo, i + 1);
			printf("Produs: ");
			print(*pr);
			printf("\n");
			//printf("%s %s % d", get_nume(pr), get_producator(pr), get_cantitate(pr));
			found = 1;
		}
	}
	else
		printf("nu sunt elemente\n");
	distruge_rp(repo);

}
void sort(Service* serv)
{
	printf("1 Sortare dupa nume\n2 Sortare dupa cantitate\n");
		int cmd1;
	if (scanf_s("%d", &cmd1) < 1)
	{
		if (getchar() != '\n')
			cmd1 = -2;


	}
	printf("1 Sortare crescator\n2 Sortare descrescator\n");
	int cmd2;
	if (scanf_s("%d", &cmd2) < 1){
		if (getchar() != '\n')
			cmd2 = -2;
	}

	Repository* repo = init_repo(2);
	distruge_rp(repo);
	int found = 0;
	if (cmd1 == -2 && cmd2 == -2)
		printf("valori introduse gresit\n"); 
	else {
		if (cmd1 == 1 && cmd2 == 1)
			repo = sortare(serv, cmpnumecresc);
		else {
			if (cmd1 == 1 && cmd2 == 2) 
				repo = sortare(serv, cmpnumedesc);
			else {
				if (cmd1 == 2 && cmd2 == 1) 
					repo = sortare(serv, cmpcantcresc);
				else if (cmd1 == 2 && cmd2 == 2) 
					repo = sortare(serv, cmpcantdesc);
			}
		}
	}
	if (found) {
		for (int i = 0; i < get_dim(repo); i++){
			Produs* pr = element(repo, i + 1);
			printf("Produs: ");
			print(*pr);
			printf("\n");
		}
		distruge_rp(repo);
	}
}

void print_meniu(){
	printf("1 afisare produse\n2 adaugare produs\n3 update produs\n4 delete produs\n5 filtrari\n6 sortari\n7 - undo\n -1 EXIT\nend\n");
}

void run(Service* serv, Vector* undoList){
	int cmd;
	printf("meniu\n");
	int ok = 1;
	add_serv(serv, "roata", "volkswagen", 100 , undoList);
	add_serv(serv, "pateu", "antrefig", 100 , undoList);
	add_serv(serv, "laptop", "razer", 100 , undoList);
	add_serv(serv, "mouse", "razer", 100 , undoList);
	for (int i = length(undoList) - 1; i >= 0; i--)
		deleteElement(undoList, i, distruge_rp);
	while (ok){
		print_meniu();
		if (scanf_s("%d", &cmd) < 1)
			if (getchar() != '\n')
				cmd = -2;
		switch (cmd){
			case 1:{
				afisare_ui(serv);
				break;
			}
			case 2:{
				add_ui(serv, undoList);
				break;
			}
			case 3:{
				update_ui(serv, undoList);
				break;
			}
			case 4:{
				delete_ui(serv, undoList);
				break;
			}
			case 5:{
				filtru(serv);
				break;
			}
			case 6:{
				sort(serv);
				break;
			}
			case 7:{
				undo(serv, undoList);
				break;
			}
			case -1:{
			
				printf("goodbye\n");
				ok = 0;
			}
		}
	}
}

void print(Produs p) {
	printf("%s %s %d", p.nume, p.producator, p.cantitate);
}