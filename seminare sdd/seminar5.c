//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
////creare structura pentru un nod dintr-o lista dublu inlantuita
//struct nod {
//	Masina info;
//	struct nod* prev;
//	struct nod* next;
//};
//typedef struct nod nod;
//
////creare structura pentru Lista Dubla 
//
//struct LDI {
//	nod* first;
//	nod* last;
//};
//typedef struct LDI ldi;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(ldi lista) {
//	//afiseaza toate elemente de tip masina din lista dublu inlantuita
//	//prin apelarea functiei afisareMasina()
//	while (lista.first != NULL) {
//		afisareMasina(lista.first->info);
//		lista.first = lista.first->next;
//	}
//}
//
//void adaugaMasinaInLista(ldi* lista, Masina masinaNoua) {
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//	nod* masina = (nod*)malloc(sizeof(nod));
//	masina->info = masinaNoua;
//	masina->next = NULL;
//	masina->prev = lista->last;
//	if (lista->last != NULL) {
//		lista->last->next = masina;
//	}
//	else {
//		lista->first = masina;
//	}
//	lista->last = masina;
//}
//
//void adaugaLaInceputInLista(ldi* lista, Masina masinaNoua) {
//	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
//	nod* masina = (nod*)malloc(sizeof(nod));
//	masina->info = masinaNoua;
//	masina->prev = NULL;
//	masina->next = lista->first;
//	if (lista->first != NULL) {
//		lista->first->prev = masina;
//	}
//	else {
//		lista->last = masina;
//	}
//	lista->first = masina;
//}
//
//ldi citireLDMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	ldi lista;
//	lista.first = NULL;
//	lista.last = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		adaugaMasinaInLista(&lista, m);
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocareLDMasini(ldi* lista) {
//	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
//	while (lista->first != NULL) {
//		nod* aux = lista->first; // un pointer care duce la primul nod din heap
//		free(aux->info.numeSofer);
//		free(aux->info.model);
//		lista->first = lista->first->next;
//		free(aux);
//	}
//	printf("Dezalocare realizata cu succes");
//}
//
//float calculeazaPretMediu(ldi lista) {
//	//calculeaza pretul mediu al masinilor din lista.
//	float suma = 0;
//	unsigned int k = 0;
//	while (lista.first != NULL) {
//		suma += lista.first->info.pret;
//		k++;
//		lista.first = lista.first->next;
//	}
//	return (suma > 0) ? suma / k : 0; //daca suma mai mare ca 0 returneaza suma / k, alfel return 0
//}
//
//void stergeMasinaDupaID(ldi* lista, int id) {
//	// Dacă lista e goală, ieși direct.
//	if (lista->first == NULL) {
//		return;
//	}
//
//	nod* current = lista->first;
//
//	// Parcurgem lista până la sfârșit.
//	while (current != NULL) {
//		// Verificăm dacă nodul curent are ID-ul căutat.
//		if (current->info.id == id) {
//			// Reținem nodul pe care vrem să-l ștergem.
//			nod* toDelete = current;
//
//			// Pentru a continua parcurgerea după ștergere,
//			// avansăm `current` la nodul următor.
//			current = current->next;
//
//			// 1. Dacă e nodul de la începutul listei.
//			if (toDelete->prev == NULL) {
//				// Mutăm începutul listei la următorul nod.
//				lista->first = toDelete->next;
//				// Dacă există următorul nod, îi resetăm `prev`.
//				if (lista->first != NULL) {
//					lista->first->prev = NULL;
//				}
//				else {
//					// Dacă nu mai există noduri, lista devine goală complet.
//					lista->last = NULL;
//				}
//			}
//			// 2. Dacă nu e primul, dar poate fi ultimul sau unul din mijloc.
//			else {
//				// Legăm nodul precedent cu următorul nod.
//				toDelete->prev->next = toDelete->next;
//				// Dacă `toDelete->next` există, îi resetăm legătura înapoi.
//				if (toDelete->next != NULL) {
//					toDelete->next->prev = toDelete->prev;
//				}
//				else {
//					// Dacă e chiar ultimul nod, actualizăm `lista->last`.
//					lista->last = toDelete->prev;
//				}
//			}
//
//			// Acum, eliberăm ce a fost alocat dinamic.
//			free(toDelete->info.numeSofer);
//			free(toDelete->info.model);
//			free(toDelete);
//
//			// Dacă vrei să ștergi doar **prima** apariție cu acel ID,
//			// poți face `break;` aici. 
//			// Dacă vrei să ștergi toate aparițiile, 
//			// lași bucla să continue cu `while`.
//		}
//		else {
//			// Dacă ID-ul nu corespunde, doar trecem la următorul nod.
//			current = current->next;
//		}
//	}
//}
//
//char* getNumeSoferMasinaScumpa(ldi lista) {
//	//cauta masina cea mai scumpa si 
//	//returneaza numele soferului acestei maasini.
//	nod* pretmax = lista.first;
//	lista.first = lista.first->next;
//	while (lista.first != NULL) {
//		if (lista.first->info.pret >= pretmax->info.pret) {
//			pretmax = lista.first;
//		}
//		lista.first = lista.first->next;
//	}
//	return pretmax->info.numeSofer;
//}
//
//int main() {
//	ldi lista = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	stergeMasinaDupaID(&lista, 5);
//	afisareListaMasini(lista);
//	char* numeSofer = getNumeSoferMasinaScumpa(lista);
//	printf("Soferul cu cea mai scumpa masina este: %s\n", numeSofer);
//	dezalocareLDMasini(&lista);
//
//	return 0;
//}