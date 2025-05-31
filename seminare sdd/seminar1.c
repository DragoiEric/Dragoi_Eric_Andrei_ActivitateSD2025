//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
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
//Masina initializare(int id, int nrUsi, float pret, char* model, char* numeSofer, unsigned char serie) {
//	Masina masina;
//	masina.id = id;
//	masina.nrUsi = nrUsi;
//	masina.pret = pret;
//	masina.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
//	strcpy(masina.model, model);
//	masina.numeSofer = (char*)malloc(sizeof(char) * (strlen(numeSofer) + 1));
//	strcpy(masina.numeSofer, numeSofer);
//	masina.serie = serie;
//	return masina;
//}
//
//
//void afisare(Masina masina) {
//	//afisarea tuturor atributelor.
//	printf("Masina cu id-ul: %d\n", masina.id);
//	printf("NR USI: %d\n", masina.nrUsi);
//	printf("PRET: %.2f\n", masina.pret);
//	printf("MODEL: %s\n", masina.model);
//	printf("NUME SOFER: %s\n", masina.numeSofer);
//	printf("SERIE: %c\n", masina.serie);
//	printf("\n");
//}
//
//void modifica_sofer(Masina* masina, char* numeNou) {
//	if (masina->numeSofer != NULL) {
//		free(masina->numeSofer);
//	}
//	masina->numeSofer = (char*)malloc(sizeof(char) * (strlen(numeNou) + 1));
//	strcpy(masina->numeSofer, numeNou);
//}
//
//void dezalocare(Masina* masina) {
//	//dezalocare campuri alocate dinamic
//	free(masina->model);
//	masina->model = NULL;
//	free(masina->numeSofer);
//	masina->numeSofer= NULL;
//}
//
//int main() {
//	Masina masina;
//	masina = initializare(0, 5, 5000, "Logan", "Eric", 'A');
//	afisare(masina);
//	modifica_sofer(&masina, "Arici");
//	afisare(masina);
//	dezalocare(&masina);
//	afisare(masina);
//
//	return 0;
//}