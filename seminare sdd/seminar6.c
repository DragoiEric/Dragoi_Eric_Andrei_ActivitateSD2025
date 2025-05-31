#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct nod {
	Masina info;
	struct nod* next;
};
typedef struct nod nod;

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	nod** vector;
};
typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(nod* cap) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}

}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vector = (nod**)malloc(sizeof(nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(const char* cheieNumeSofer, int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
	if (dimensiune < 0) {
		return -1;
	}

	unsigned int suma = 0;
	for (int i = 0; i < strlen(cheieNumeSofer); i++) {
		suma += (int)cheieNumeSofer[i];

	}
	suma %= dimensiune;

	return suma;
}

void inserareMasinaInTabela(HashTable hash, Masina galerie) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	int index = calculeazaHash(galerie.numeSofer, hash.dim);
	adaugaMasinaInLista(&(hash.vector[index]), galerie); //nu trebuie sa verific daca e primu nod din cluster deoarece verificare se face in adaugaMasinaInLista
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dim) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(dim);
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		inserareMasinaInTabela(ht, m);
	}
	fclose(f);
	return ht;
}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++) {
		printf("Cluster %d:\n", i);
		afisareListaMasini(ht.vector[i]);
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
	for (int i = 0; i < ht->dim; i++) {
		nod* temp;
		while (ht->vector[i]) {
			temp = ht->vector[i];
			ht->vector[i] = ht->vector[i]->next;
			free(temp->info.model);
			free(temp->info.numeSofer);
			free(temp);
		}
	}
	free(ht->vector);
	printf("Dezalocare realizata cu succes\n");
}

int nrC(HashTable ht) {
	int nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			nrClustere++;
		}
	}
	return nrClustere;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	float* preturi = (float*)malloc(sizeof(float) * nrClustere);
	unsigned int counter = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			float suma = 0;
			float k = 0;
			nod* temp = ht.vector[i];
			while (temp != NULL) {
				suma += temp->info.pret;
				k++;
				temp = temp->next;
			}
			if (suma == 0) {
				preturi[counter] = 0;
				counter++;
			}
			else {
				preturi[counter] = suma / k;
				counter++;
			}
		}
		
	}


	return preturi;
}

Masina getMasinaDupaCheie(HashTable ht, const char* numeSofer) {
	Masina m;
	m.id = -1;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei
	int pozitie = calculeazaHash(numeSofer, ht.dim);
	if (pozitie < 0 || pozitie >= ht.dim || ht.vector[pozitie] == NULL)
		return m;
	nod* aux = ht.vector[pozitie];
	while (aux != NULL && strcmp(aux->info.numeSofer, numeSofer) != 0)
		aux = aux->next;
	if (aux != NULL)
	{
		m.numeSofer = (char*)malloc(strlen(numeSofer) + 1);
		strcpy(m.numeSofer, numeSofer);
		m.model = (char*)malloc(strlen(aux->info.model) + 1);
		strcpy(m.model, aux->info.model);
		m.id = aux->info.id;
		m.nrUsi = aux->info.nrUsi;
		m.pret = aux->info.pret;
		m.serie = aux->info.serie;
	}
	return m;
}

int main() {
	int dim = 7;
	HashTable ht = initializareHashTable(dim);
	ht = citireMasiniDinFisier("masini.txt", dim);
	afisareTabelaDeMasini(ht);
	int nrClustere = nrC(ht);
	float* preturi = calculeazaPreturiMediiPerClustere(ht, nrClustere);
	printf("Preturile medii per cluster non-empty este:\n");
	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f ", preturi[i]);
	}
	printf("\n");
	free(preturi);
	Masina m = getMasinaDupaCheie(ht, "Gigel");
	afisareMasina(m);
	dezalocareTabelaDeMasini(&ht);
	
	return 0;
}