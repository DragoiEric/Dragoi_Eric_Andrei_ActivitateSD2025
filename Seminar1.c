#include <stdio.h>
#include <stdlib.h>

struct Masina {
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};

struct Masina initializare(int id, int nrKm, const char* model, float pret, char tipMotor) {
	struct Masina m;
	m.id = id;
	m.nrKm = nrKm;
	m.model = (char*)malloc(strlen(model) + 1);
	strcpy_s(m.model, strlen(model) + 1, model);
	m.pret = pret;
	m.tipMotor = tipMotor;
	 
	return m;
}

void afisare(struct Masina m) {
	printf("ID: %d \n", m.id);
	printf("Nr km: %d \n", m.nrKm);
	printf("Model: %s \n", m.model);
	printf("Pret: %f \n", m.pret);
	printf("Tip Motor: %c \n", m.tipMotor);
}

void modifica_Pret(struct Masina* m, float pretNou) {
	if (pretNou >= 0) {
		m->pret = pretNou;
		printf("Modificare realizata cu succes \n");
	}
	else {
		printf("Pretul trebuie sa fie pozitiv \n");
	}
	  
}

void dezalocare(struct Masina* m) {
	if (m->model != NULL) {
		free(m->model);
		m->model = NULL;
	}
}

int main() {
	struct Masina m;
	m = initializare(0, 10000, "Logan", 200.23, 'B');
	afisare(m);
	modifica_Pret(&m, 1000.123);
	afisare(m);
	dezalocare(&m);
	afisare(m);


	return 0;
}
