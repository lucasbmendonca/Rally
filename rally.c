#include "rally.h"

InfoCorrida* corrida = NULL; //ponteiro para o inicio
InfoCorrida* corrida_ult = NULL; //ponteiro para o ultimo
Prova prova = { NULL,0 }; //Estrutura que contém informações acerca de uma prova
char linha[MAX_BUFFER];
char* valores;
char** resultado = NULL;
tamanho = 0;

int processaCorrida() {
    int num_etapas = 0; //numero de etapas

    //Tratamento do arquivo*/
    FILE* arq;
    arq = fopen("corrida.txt", "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
        return 1;
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
            if (resultado[2] == NULL) {
                num_etapas += atoi(resultado[0]);
                continue;
            }
            InfoCorrida* newInfo = (InfoCorrida*)malloc(sizeof(InfoCorrida));
            newInfo->concorrente.id = atoi(resultado[0]);
            newInfo->concorrente.etapa = NULL;
            newInfo->concorrente.etapa_ult = NULL;
            newInfo->concorrente.qtdEtapas = 0;
            newInfo->num_etapas = num_etapas;
            newInfo->next = NULL;

            Etapa* newEtapa = (Etapa*)malloc(sizeof(Etapa));
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
            
            //qtd etapas
            newInfo->concorrente.qtdEtapas += 1;

            if (newInfo->tempoTotal < 0)
                newInfo->tempoTotal = newEtapa->tempo;
            else
                newInfo->tempoTotal += newEtapa->tempo;

            //Se nao existir informação ainda na lista
            if (!jaExiste) {
                if (corrida == NULL) {
                    corrida = newInfo;
                    //guarda na estrutura prova
                    prova.corrida = corrida;
                }
                else
                    corrida_ult->next = newInfo;
                //quantidade de concorrentes
                prova.quantidadeConcorrentes++;
                //ponteiro pro ultimo
                corrida_ult = newInfo;
            }
        }
    }
    fclose(arq);
    return 0;
}

int processaEtapa() {
    FILE* arq = fopen("etapa.txt", "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
        return 1;
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
    fclose(arq);
    return 0;
}

int processaConcorrentes() {
    FILE *arq = fopen("concorrentes.txt", "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
        return 1;
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
            InfoCorrida* c = corrida;
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
                newInfo->concorrente.qtdEtapas = 0;
                newInfo->tempoTotal = 0;
                newInfo->num_etapas = 0;
                newInfo->next = NULL;
                corrida_ult->next = newInfo;
                corrida_ult = newInfo;
                //incrementa quantidade de concorrentes na prova
                prova.quantidadeConcorrentes++;
            }
        }
    }
    fclose(arq);
    return 0;
}

InfoCorrida* getResult() {
    return corrida;
}

int getQtdConcorrentes() {
    return prova.quantidadeConcorrentes;
}

int getConcProvaVal() {
    int cont = 0;
    InfoCorrida* c = prova.corrida;
    while (c) {
        //Se o numero de etapas da corrida for igual ao numero de etapas realizada pelo concorrente na corrida
        if (c->num_etapas == c->concorrente.qtdEtapas && c->num_etapas != 0)
            cont++;
        c = c->next;
    }
    return cont;
}

void displayListTempoProva() {

    InfoCorrida* current = prova.corrida;
    InfoCorrida* ps;
    while (current) {
        ps = current->next;
        while (ps) {
            if (current->tempoTotal < ps->tempoTotal) {
                InfoCorrida aux = *current;
                current->concorrente = ps->concorrente;
                current->num_etapas = ps->num_etapas;
                current->tempoTotal = ps->tempoTotal;
                //current->next = ps->next;
                ps->concorrente = aux.concorrente;
                ps->num_etapas = aux.num_etapas;
                ps->tempoTotal = aux.tempoTotal;
                //ps->next = aux.next;
            }
            ps = ps->next;
        }
        current = current->next;
    }

    InfoCorrida* aux = prova.corrida;
    while (aux) {
        printf("Concorrente %-20s Tempo de prova: %-20d\n", aux->concorrente.nome, aux->tempoTotal);
        aux = aux->next;
    }
}
