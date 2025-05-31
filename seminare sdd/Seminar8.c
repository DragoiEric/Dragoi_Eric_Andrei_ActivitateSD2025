#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// trebuie sa folositi fisierul masini.txt
// sau va creati un alt fisier cu alte date

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};
typedef struct StructuraMasina Masina;

// creare structura pentru un nod dintr-un arbore binar de cautare
struct Nod {
    Masina info;
    struct Nod* stanga;
    struct Nod* dreapta;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char* aux;
    Masina m1;

    aux = strtok(buffer, sep);
    m1.id = atoi(aux);

    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = (float)atof(strtok(NULL, sep));

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

void adaugaMasinaInArbore(Nod** arbore, Masina masinaNoua) {
    Nod** tmp = arbore;
    while (*tmp != NULL) {
        if (masinaNoua.id < (*tmp)->info.id) {
            tmp = &(*tmp)->stanga;
        }
        else {
            tmp = &(*tmp)->dreapta;
        }
    }
    *tmp = malloc(sizeof * *tmp);
    (*tmp)->info = masinaNoua;
    (*tmp)->stanga = NULL;
    (*tmp)->dreapta = NULL;
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
    Nod* arbore = NULL;
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        perror("Nu s-a putut deschide fisierul");
        return NULL;
    }
    while (!feof(f)) {
        Masina m = citireMasinaDinFisier(f);
        adaugaMasinaInArbore(&arbore, m);
    }
    fclose(f);
    return arbore;
}

void afisareMasiniDinArbore(Nod* arbore) {
    if (arbore == NULL)
        return;
    afisareMasiniDinArbore(arbore->stanga);
    afisareMasina(arbore->info);
    afisareMasiniDinArbore(arbore->dreapta);
}

void dezalocareArboreDeMasini(Nod* arbore) {
    if (arbore == NULL)
        return;
    dezalocareArboreDeMasini(arbore->stanga);
    dezalocareArboreDeMasini(arbore->dreapta);
    free(arbore->info.model);
    free(arbore->info.numeSofer);
    free(arbore);
}

Masina getMasinaByID(Nod* arbore, int id) {
    if (arbore == NULL) {
        Masina dummy;
        dummy.id = -1;
        dummy.nrUsi = 0;
        dummy.pret = 0.0f;
        dummy.model = NULL;
        dummy.numeSofer = NULL;
        dummy.serie = 0;
        return dummy;
    }
    if (id == arbore->info.id) {
        return arbore->info;
    }
    else if (id < arbore->info.id) {
        return getMasinaByID(arbore->stanga, id);
    }
    else {
        return getMasinaByID(arbore->dreapta, id);
    }
}

int determinaNumarNoduri(Nod* arbore) {
    if (arbore == NULL)
        return 0;
    int st = determinaNumarNoduri(arbore->stanga);
    int dr = determinaNumarNoduri(arbore->dreapta);
    return 1 + st + dr;
}

int calculeazaInaltimeArbore(Nod* arbore) {
    if (arbore == NULL)
        return 0;
    int hs = calculeazaInaltimeArbore(arbore->stanga);
    int hd = calculeazaInaltimeArbore(arbore->dreapta);
    return 1 + (hs > hd ? hs : hd);
}

float calculeazaPretTotal(Nod* arbore) {
    if (arbore == NULL)
        return 0.0f;
    float s1 = calculeazaPretTotal(arbore->stanga);
    float s2 = calculeazaPretTotal(arbore->dreapta);
    return s1 + s2 + arbore->info.pret;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* arbore, const char* numeSofer) {
    if (arbore == NULL)
        return 0.0f;
    float sumaSt = calculeazaPretulMasinilorUnuiSofer(arbore->stanga, numeSofer);
    float sumaDr = calculeazaPretulMasinilorUnuiSofer(arbore->dreapta, numeSofer);
    if (strcmp(arbore->info.numeSofer, numeSofer) == 0) {
        return sumaSt + sumaDr + arbore->info.pret;
    }
    else {
        return sumaSt + sumaDr;
    }
}

int main() {
    Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
    afisareMasiniDinArbore(arbore);

    int totalNoduri = determinaNumarNoduri(arbore);
    printf("Numar total de noduri în arbore: %d\n", totalNoduri);

    int inaltime = calculeazaInaltimeArbore(arbore);
    printf("Inaltimea arborelui: %d\n", inaltime);

    float pretTotal = calculeazaPretTotal(arbore);
    printf("Pret total al tuturor masinilor: %.2f\n", pretTotal);

    const char* soferCautat = "Ionescu";
    float pretSofer = calculeazaPretulMasinilorUnuiSofer(arbore, soferCautat);
    printf("Pret total al masinilor soferului \"%s\": %.2f\n", soferCautat, pretSofer);

    int idCautat = 5;
    Masina rez = getMasinaByID(arbore, idCautat);
    if (rez.id != -1) {
        printf("\nMasina cu ID=%d a fost gasita:\n", idCautat);
        afisareMasina(rez);
    }
    else {
        printf("\nNu s-a gasit nicio masina cu ID=%d in arbore.\n", idCautat);
    }

    dezalocareArboreDeMasini(arbore);
    return 0;
}
