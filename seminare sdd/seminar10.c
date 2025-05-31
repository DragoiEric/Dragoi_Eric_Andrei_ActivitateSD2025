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

// citeste o masina de pe o linie din fisier (form: id,nrUsi,pret,model,numeSofer,serie)
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
    strcpy(m1.model, aux);
    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy(m1.numeSofer, aux);
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

//==================================
// STIVA (LIFO) folosind lista simplu inlantuita

typedef struct NodStack {
    Masina info;
    struct NodStack* next;
} NodStack;

typedef struct {
    NodStack* top;
    int length;
} Stiva;

// initializeaza stiva (intoarce pointer la structura Stiva)
Stiva* creareStiva() {
    Stiva* s = (Stiva*)malloc(sizeof(Stiva));
    s->top = NULL;
    s->length = 0;
    return s;
}

int emptyStack(Stiva* s) {
    return (s->length == 0);
}

int sizeStack(Stiva* s) {
    return s->length;
}

void pushStack(Stiva* s, Masina masina) {
    NodStack* node = (NodStack*)malloc(sizeof(NodStack));
    node->info = masina;
    node->next = s->top;
    s->top = node;
    s->length++;
}

Masina popStack(Stiva* s) {
    Masina dummy;
    dummy.id = -1;
    dummy.nrUsi = 0;
    dummy.pret = 0.0f;
    dummy.model = NULL;
    dummy.numeSofer = NULL;
    dummy.serie = 0;
    if (emptyStack(s)) {
        return dummy;
    }
    NodStack* temp = s->top;
    Masina ret = temp->info;
    s->top = temp->next;
    free(temp);
    s->length--;
    return ret;
}

void* citireStackMasiniDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        perror("Nu s-a putut deschide fisierul");
        return NULL;
    }
    Stiva* s = creareStiva();
    while (!feof(f)) {
        Masina m = citireMasinaDinFisier(f);
        pushStack(s, m);
    }
    fclose(f);
    return s;
}

void dezalocareStivaDeMasini(Stiva* s) {
    while (!emptyStack(s)) {
        Masina m = popStack(s);
        free(m.model);
        free(m.numeSofer);
    }
    free(s);
}

// cauta o masina in stiva dupa id (nu modifica stiva)
Masina getMasinaByIDStack(Stiva* s, int id) {
    NodStack* curr = s->top;
    while (curr) {
        if (curr->info.id == id) {
            return curr->info;
        }
        curr = curr->next;
    }
    Masina dummy;
    dummy.id = -1;
    dummy.nrUsi = 0;
    dummy.pret = 0.0f;
    dummy.model = NULL;
    dummy.numeSofer = NULL;
    dummy.serie = 0;
    return dummy;
}

// calculeaza suma preturilor din stiva (nu modifica stiva)
float calculeazaPretTotalStack(Stiva* s) {
    float suma = 0.0f;
    NodStack* curr = s->top;
    while (curr) {
        suma += curr->info.pret;
        curr = curr->next;
    }
    return suma;
}

//==================================
// COADA (FIFO) folosind lista simplu inlantuita

typedef struct NodCoada {
    Masina info;
    struct NodCoada* next;
} NodCoada;

typedef struct {
    NodCoada* front;
    NodCoada* rear;
    int length;
} Coada;

Coada* creareCoada() {
    Coada* q = (Coada*)malloc(sizeof(Coada));
    q->front = q->rear = NULL;
    q->length = 0;
    return q;
}

int emptyQueue(Coada* q) {
    return (q->length == 0);
}

int sizeQueue(Coada* q) {
    return q->length;
}

void enqueue(Coada* q, Masina masina) {
    NodCoada* node = (NodCoada*)malloc(sizeof(NodCoada));
    node->info = masina;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
    }
    else {
        q->rear->next = node;
        q->rear = node;
    }
    q->length++;
}

Masina dequeue(Coada* q) {
    Masina dummy;
    dummy.id = -1;
    dummy.nrUsi = 0;
    dummy.pret = 0.0f;
    dummy.model = NULL;
    dummy.numeSofer = NULL;
    dummy.serie = 0;
    if (emptyQueue(q)) {
        return dummy;
    }
    NodCoada* temp = q->front;
    Masina ret = temp->info;
    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->length--;
    return ret;
}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        perror("Nu s-a putut deschide fisierul");
        return NULL;
    }
    Coada* q = creareCoada();
    while (!feof(f)) {
        Masina m = citireMasinaDinFisier(f);
        enqueue(q, m);
    }
    fclose(f);
    return q;
}

void dezalocareCoadaDeMasini(Coada* q) {
    while (!emptyQueue(q)) {
        Masina m = dequeue(q);
        free(m.model);
        free(m.numeSofer);
    }
    free(q);
}

// cauta o masina in coada dupa id (nu modifica coada)
Masina getMasinaByIDQueue(Coada* q, int id) {
    NodCoada* curr = q->front;
    while (curr) {
        if (curr->info.id == id) {
            return curr->info;
        }
        curr = curr->next;
    }
    Masina dummy;
    dummy.id = -1;
    dummy.nrUsi = 0;
    dummy.pret = 0.0f;
    dummy.model = NULL;
    dummy.numeSofer = NULL;
    dummy.serie = 0;
    return dummy;
}

// calculeaza suma preturilor din coada (nu modifica coada)
float calculeazaPretTotalQueue(Coada* q) {
    float suma = 0.0f;
    NodCoada* curr = q->front;
    while (curr) {
        suma += curr->info.pret;
        curr = curr->next;
    }
    return suma;
}


int main() {
    // Citire stiva din fisier
    Stiva* st = (Stiva*)citireStackMasiniDinFisier("masini.txt");
    if (st == NULL) {
        return 1;
    }
    printf("--- STIVA: afisare masina cu ID 3\n");
    Masina gasitS = getMasinaByIDStack(st, 3);
    if (gasitS.id != -1) {
        afisareMasina(gasitS);
    }
    else {
        printf("Nu exista nicio masina cu ID = 3 in stiva\n\n");
    }
    float totalPretStiva = calculeazaPretTotalStack(st);
    printf("Suma preturilor din stiva: %.2f\n\n", totalPretStiva);
    dezalocareStivaDeMasini(st);

    // Citire coada din fisier
    Coada* cq = (Coada*)citireCoadaDeMasiniDinFisier("masini.txt");
    if (cq == NULL) {
        return 1;
    }
    printf("--- COADA: afisare masina cu ID 4\n");
    Masina gasitQ = getMasinaByIDQueue(cq, 4);
    if (gasitQ.id != -1) {
        afisareMasina(gasitQ);
    }
    else {
        printf("Nu exista nicio masina cu ID = 4 in coada\n\n");
    }
    float totalPretCoada = calculeazaPretTotalQueue(cq);
    printf("Suma preturilor din coada: %.2f\n\n", totalPretCoada);
    dezalocareCoadaDeMasini(cq);

    return 0;
}
