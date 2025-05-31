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

//creare structura pentru Heap
//un vector de elemente, lungimea vectorului si numarul de elemente din vector
struct Heap {
	int lungime;
	Masina* vec;
	int nrElem;
};
typedef struct Heap Heap;

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

Heap initializareHeap(int lungime) {
	//initializeaza heap-ul cu 0 elemente 
	//dar cu o lungime primita ca parametru
	Heap h;
	h.vec = (Masina*)malloc(lungime * sizeof(Masina));
	if (!h.vec) {
		printf("Eroare alocare heap");
		return h;
	}
	h.lungime = 0;
	h.nrElem = 0;
	return h;
}

void filtreazaHeap_max(Heap* h, int i) {
	int n = h->nrElem;
	while (1) {
		int st = 2 * i + 1;
		int dr = 2 * i + 2;
		int best = i;

		if (st < n && h->vec[st].id > h->vec[best].id)
			best = st;
		if (dr < n && h->vec[dr].id > h->vec[best].id)
			best = dr;

		if (best == i) break;

		Masina tmp = h->vec[i];
		h->vec[i] = h->vec[best];
		h->vec[best] = tmp;
		i = best;
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	//citim toate masinile din fisier si le stocam intr-un heap 
	// pe care trebuie sa il filtram astfel incat sa respecte 
	// principiul de MAX-HEAP sau MIN-HEAP dupa un anumit criteriu
	// sunt citite toate elementele si abia apoi este filtrat vectorul
	FILE* f = fopen(numeFisier, "r");
	Heap h = initializareHeap(11);
	int i = 0;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		h.vec[i] = m;
		h.nrElem++;
		i++;
	}
	for (int j = h.nrElem - 1; j >= 0; --j) {
		filtreazaHeap_max(&h, j);
	}
	fclose(f);
	return h;

}



void afisareHeap(Heap heap) {
	//afiseaza elementele vizibile din heap
	//afisare psd (parinte-standa-dreapta)
	for (int i = 0; i < heap.nrElem; i++) {
		afisareMasina(heap.vec[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	//afiseaza elementele ascunse din heap
}

Masina extrageMasina(void* heap) {
	Heap* h = (Heap*)heap;
	if (h->nrElem == 0) {
		fprintf(stderr, "Eroare: extrageMasina din heap gol\n");
		exit(EXIT_FAILURE);
	}

	// 1) Salvează rădăcina
	Masina rezultat = h->vec[0];

	// 2) Mută ultimul element pe poziția 0 și „ascunde” rădăcina
	h->vec[0] = h->vec[h->nrElem - 1];
	h->nrElem--;

	// 3) Restaurează proprietatea de heap
	filtreazaHeap_max(h, 0);

	return rezultat;
}


void dezalocareHeap(Heap* heap) {
	//sterge toate elementele din Heap
	free(heap->vec);

}

int main() {
	Heap h = citireHeapDeMasiniDinFisier("masini.txt");
	afisareHeap(h);
	Masina rezultat = extrageMasina(&h);
	afisareHeap(h);
	dezalocareHeap(&h);
	return 0;
}