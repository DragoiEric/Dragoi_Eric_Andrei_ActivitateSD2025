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
////creare structura pentru un nod dintr-o lista simplu inlantuita
//struct Nod {
//	Masina info;
//	struct nod* next;
//};
//typedef struct Nod nod;
//
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
//	m1.pret= atof(strtok(NULL, sep));
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
//void afisareListaMasini(nod* capLista) {
//	//afiseaza toate elemente de tip masina din lista simplu inlantuita
//	//prin apelarea functiei afisareMasina()
//	nod* temp = capLista; // pointer auxiliar
//	while (temp != NULL) {
//		afisareMasina(temp->info);
//		temp = temp->next;
//	}
//}
//
//void adaugaMasinaInLista(nod** capLista, Masina masinaNoua) {
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//
//	if (*capLista == NULL) {
//		*capLista = nou;
//	}
//	else {
//		nod* temp = *capLista;
//		while (temp->next != NULL) {
//			temp = temp->next;
//		}
//		temp->next = nou;//schimbi ultimul pointer
//	}
//}
//
//void adaugaLaInceputInLista(nod** capLista, Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = masinaNoua;
//	nou->next = *capLista;
//	*capLista = nou;
//}
//
//nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	if (!f) {
//		printf("Eroare la deschiderea fisierului!\n");
//		return NULL;
//	}
//
//	nod* lista = NULL; // lista trebuie initializata cu NULL
//	Masina masina;
//
//	while (!feof(f)) {
//		masina = citireMasinaDinFisier(f);
//
//		// Verifică dacă citirea a fost corectă (ex. model != NULL)
//		if (masina.model != NULL) {
//			adaugaMasinaInLista(&lista, masina);
//		}
//	}
//
//	fclose(f);
//	return lista;  // returnezi lista citită
//}
//
//void dezalocareListaMasini(nod** lista) {
//	//sunt dezalocate toate masinile si lista de elemente
//	while ((*lista) != NULL) {
//		free((*lista)->info.model);
//		free((*lista)->info.numeSofer);
//		(*lista) = (*lista)->next;
//	}
//	free((*lista));
//}
//
//float calculeazaPretMediu(nod* lista) {
//	if (lista == NULL) return 0.0f;
//
//	float suma = 0.0f;
//	int nrMasini = 0;
//
//	nod* temp = lista;
//	while (temp != NULL) {
//		suma += temp->info.pret;
//		nrMasini++;
//		temp = temp->next;
//	}
//
//	return (nrMasini > 0) ? (suma / nrMasini) : 0.0f;
//}
//
//void stergeMasiniDinSeria(nod** lista, char serieCautata) {
//	nod* temp = *lista;
//	nod* anterior = NULL;
//
//	while (temp != NULL) {
//		if (temp->info.serie == serieCautata) {
//			nod* deSters = temp;
//
//			if (anterior == NULL) {
//				// Ștergi primul element
//				*lista = temp->next;
//				temp = *lista;
//			}
//			else {
//				// Ștergi element intermediar sau ultimul element
//				anterior->next = temp->next;
//				temp = anterior->next;
//			}
//
//			// Dezalocare
//			free(deSters->info.model);
//			free(deSters->info.numeSofer);
//			free(deSters);
//		}
//		else {
//			anterior = temp;
//			temp = temp->next;
//		}
//	}
//}
//
//float calculeazaPretulMasinilorUnuiSofer(nod* lista, const char* numeSofer) {
//	float suma = 0.0f;
//	nod* temp = lista;
//
//	while (temp != NULL) {
//		if (strcmp(temp->info.numeSofer, numeSofer) == 0) {
//			suma += temp->info.pret;
//		}
//		temp = temp->next;
//	}
//
//	return suma;
//}
//
//int main() {
//	nod* listaMasini = citireListaMasiniDinFisier("masini.txt");
//
//	printf("Pret mediu: %.2f\n", calculeazaPretMediu(listaMasini));
//
//	stergeMasiniDinSeria(&listaMasini, 'A');
//	printf("Lista dupa stergere masini seria 'A':\n");
//	afisareListaMasini(listaMasini);
//
//	float pretTotalSofer = calculeazaPretulMasinilorUnuiSofer(listaMasini, "Gigel");
//	printf("Pret total masini ale lui Gigel: %.2f\n", pretTotalSofer);
//
//	dezalocareListaMasini(&listaMasini);
//	return 0;
//}