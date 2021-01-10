#pragma once
#include "rally.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct etapa {
	char inicio[3];
	char fim[3];
	float distancia;
	int tempo;
    struct etapa* next;
} Etapa;

typedef struct concorrente{
	int id;
	char nome[50];
	char carro[10];
	Etapa* etapa;
    Etapa* etapa_ult;
} Concorrente;

typedef struct corrida {
	Concorrente concorrente;
	int tempoTotal;
	struct corrida* next;
} InfoCorrida;


int main() {

    InfoCorrida *corrida = NULL; //ponteiro inicial
    InfoCorrida* corrida_ult = NULL; //ponteiro pro ultimo
    int id, tempo;
    char linha[255];
    char* valores;
    char** resultado = NULL;
    int tamanho = 0;

    //Tratamento do arquivo*/
    FILE* arq;
    arq = fopen("corrida.txt", "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else {
        while(fgets(linha, sizeof(linha), arq) != NULL){
            free(resultado);
            resultado = NULL;
            tamanho = 0;
            valores = strtok(linha, ";");
            while (valores)
            {
                resultado = realloc(resultado, sizeof(char*) * ++tamanho);
                resultado[tamanho - 1] = valores;
                valores = strtok(NULL, ";");
            }
            resultado = realloc(resultado, sizeof(char*) * (tamanho + 1));
            resultado[tamanho] = '\0';
            if (resultado[2] == NULL) {
                continue;
            }
            InfoCorrida *newInfo = (InfoCorrida*)malloc(sizeof(InfoCorrida));
            newInfo->concorrente.id = atoi(resultado[0]);
            newInfo->concorrente.etapa = NULL;
            newInfo->concorrente.etapa_ult = NULL;
            newInfo->next = NULL;

            Etapa *newEtapa = (Etapa*)malloc(sizeof(Etapa));
            strcpy(newEtapa->inicio, resultado[1]);
            strcpy(newEtapa->fim, resultado[2]);
            newEtapa->tempo = atoi(resultado[3]);
            newEtapa->next = NULL;

            //getConcorrente
            InfoCorrida* c = corrida;
            bool jaExiste = false;
            while (c) {
                if (c->concorrente.id == atoi(resultado[0])) {
                    newInfo = c;
                    jaExiste = true;
                    break;
                }
                c = c->next;
            }

            if (newInfo->concorrente.etapa == NULL)
                newInfo->concorrente.etapa = newEtapa;
            else
                newInfo->concorrente.etapa_ult->next = newEtapa;
            newInfo->concorrente.etapa_ult = newEtapa;
            
            if (newInfo->tempoTotal < 0)
                newInfo->tempoTotal = newEtapa->tempo;
            else
                newInfo->tempoTotal += newEtapa->tempo;

            //Se nao existir informação ainda na lista
            if (!jaExiste) {
                if (corrida == NULL)
                    corrida = newInfo;
                else
                    corrida_ult->next = newInfo;
                //ponteiro pro ultimo
                corrida_ult = newInfo;
            }
        }
    }

    arq = fopen("etapa.txt", "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else {
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            free(resultado);
            resultado = NULL;
            tamanho = 0;
            valores = strtok(linha, ";");
            while (valores)
            {
                resultado = realloc(resultado, sizeof(char*) * ++tamanho);
                resultado[tamanho - 1] = valores;
                valores = strtok(NULL, ";");
            }
            resultado = realloc(resultado, sizeof(char*) * (tamanho + 1));
            resultado[tamanho] = '\0';

            //getEtapa
            InfoCorrida* cx = corrida;
            while (cx) {
                Etapa* e = cx->concorrente.etapa;
                while (e) {
                    int result1 = strcmp(e->inicio, resultado[0]);
                    int result2 = strcmp(e->fim, resultado[1]);
                    if (!(result1 && result2)) {
                        resultado[2][strlen(resultado[2]) - 1] = 0;
                        e->distancia = atof(resultado[2]);
                        break;
                    }
                    e = e->next;
                }
                cx = cx->next;
            }
        }
    }

    arq = fopen("concorrentes.txt", "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else {
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            free(resultado);
            resultado = NULL;
            tamanho = 0;
            valores = strtok(linha, ";");
            while (valores)
            {
                resultado = realloc(resultado, sizeof(char*) * ++tamanho);
                resultado[tamanho - 1] = valores;
                valores = strtok(NULL, ";");
            }
            resultado = realloc(resultado, sizeof(char*) * (tamanho + 1));
            resultado[tamanho] = '\0';

            //retirar "\n"
            resultado[2][strlen(resultado[2]) - 1] = 0;

            //getConcorrente
            InfoCorrida *c = corrida;
            bool flag = false;
            while (c) {
                if (c->concorrente.id == atoi(resultado[0])) {
                    strcpy(c->concorrente.nome, resultado[1]);
                    strcpy(c->concorrente.carro, resultado[2]);
                    flag = true;
                    break;
                }
                c = c->next;
            }

            if (flag == false) {
                InfoCorrida* newInfo = (InfoCorrida*)malloc(sizeof(InfoCorrida));
                newInfo->concorrente.id = atoi(resultado[0]);
                strcpy(newInfo->concorrente.nome, resultado[1]);
                strcpy(newInfo->concorrente.carro, resultado[2]);
                newInfo->concorrente.etapa = NULL;
                newInfo->concorrente.etapa_ult = NULL;
                newInfo->next = NULL;
                corrida_ult->next = newInfo;
                corrida_ult = newInfo;
            }
        }
    }

    fclose(arq);

	return 0;
}
