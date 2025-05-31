//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// Structura Masina
//typedef struct {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//} Masina;
//
//// Afisare o masina
//void afisareMasina(Masina masina) {
//	printf("Masina cu ID-ul: %d\n", masina.id);
//	printf("Nr usi: %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n", masina.serie);
//	printf("------------------------\n");
//}
//
//// Afisare vector masini
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//}
//
//// Adaugare masina noua in vector
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	Masina* temp = (Masina*)malloc(sizeof(Masina) * (*nrMasini + 1));
//	for (int i = 0; i < *nrMasini; i++) {
//		temp[i] = (*masini)[i];
//	}
//	temp[*nrMasini] = masinaNoua;
//	free(*masini);
//	*masini = temp;
//	(*nrMasini)++;
//}
//
//// Citire o masina din fisier
//Masina citireMasinaFisier(FILE* file) {
//	char buffer[256];
//	char sep[3] = ",\n";
//	Masina m1;
//
//	if (fgets(buffer, sizeof(buffer), file) == NULL) {
//		m1.model = NULL; // semnalizare ca linia e goala
//		return m1;
//	}
//
//	char* aux = strtok(buffer, sep);
//	if (aux == NULL) {
//		m1.model = NULL;
//		return m1;
//	}
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//
//	aux = strtok(NULL, sep);
//	m1.serie = aux[0];
//
//	return m1;
//}
//
//// Citire vector masini din fisier
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	FILE* f = fopen(numeFisier, "r");
//	if (!f) {
//		printf("Eroare la deschiderea fisierului!\n");
//		*nrMasiniCitite = 0;
//		return NULL;
//	}
//
//	Masina* vector = NULL;
//	*nrMasiniCitite = 0;
//
//	while (!feof(f)) {
//		Masina m = citireMasinaFisier(f);
//		if (m.model != NULL) {
//			adaugaMasinaInVector(&vector, nrMasiniCitite, m);
//		}
//	}
//
//	fclose(f);
//	return vector;
//}
//
//// Dezalocare vector masini
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	for (int i = 0; i < *nrMasini; i++) {
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrMasini = 0;
//}
//
//int main() {
//	int nrMasini = 0;
//	Masina* vectorMasini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//
//	if (vectorMasini != NULL) {
//		printf("Masinile citite din fisier:\n\n");
//		afisareVectorMasini(vectorMasini, nrMasini);
//		dezalocareVectorMasini(&vectorMasini, &nrMasini);
//	}
//
//	return 0;
//}
