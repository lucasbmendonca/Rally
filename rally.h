#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 255
#define TXT_CORRIDA "corrida.txt"
#define TXT_ETAPA "etapa.txt"
#define TXT_CONC "concorrentes.txt"

typedef struct etapa {
	char inicio[3];
	char fim[3];
	float distancia;
	int tempo;
	struct etapa* next;
} Etapa;

typedef struct concorrente {
	int id;
	char nome[50];
	char carro[10];
	Etapa* etapa;
	Etapa* etapa_ult;
	int qtdEtapas;
} Concorrente;

typedef struct corrida {
	Concorrente concorrente;
	int num_etapas;
	int tempoTotal;
	struct corrida* next;
} InfoCorrida;

typedef struct prova {
	InfoCorrida* corrida;
	int quantidadeConcorrentes;
} Prova;

extern int processaCorrida();
extern int processaEtapa();
extern int processaConcorrentes();
extern InfoCorrida* getResult();
