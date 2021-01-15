/**
 * @rally.c
 * @author  Lucas Mendonça <a17870@alunos.ipca.pt>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Ficheiro com a implementação das funções da biblioteca
 */

#include "rally.h"

InfoCorrida* corrida = NULL; //ponteiro para o inicio
InfoCorrida* corrida_ult = NULL; //ponteiro para o ultimo
Prova prova = { NULL,0 }; //Estrutura que contém informações acerca de uma prova
MediaEtapa mediaEtapa[3] = { {"P","E1",0,0},{"E1","E2", 0, 0},{"E2","C",0,0} };
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
            newInfo->distanciaTotal = 0;
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

            //media etapas
            for (int i = 0; i < 3; i++) {
                if (strcmp(newEtapa->inicio, mediaEtapa[i].ini) == 0 && strcmp(newEtapa->fim, mediaEtapa[i].fim) == 0) {
                    if (newEtapa->tempo < mediaEtapa[i].tempoMinimo || mediaEtapa[i].tempoMinimo == 0) //assignando à estrutura o tempo minimo geral do percurso
                        mediaEtapa[i].tempoMinimo = newEtapa->tempo;
                    mediaEtapa[i].tempoTotal += newEtapa->tempo;
                    mediaEtapa[i].cont += 1;
                    break;
                }
            }

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
                        cx->distanciaTotal += e->distancia;
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

    //lista
    InfoCorrida* current = prova.corrida;
    
    //array
    InfoCorrida resultado[100] = {NULL};
    int tam = 0;
    while (current) {
        //checar se é valido
        if(current->num_etapas == current->concorrente.qtdEtapas && current->num_etapas !=0)
            resultado[tam++] = *current;
        current = current->next;
    }

    //ordenação array
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j <= tam; j++) {
            if (resultado[i].tempoTotal < resultado[j].tempoTotal) {
                InfoCorrida aux = resultado[i];
                resultado[i] = resultado[j];
                resultado[j] = aux;
            }
        }
    }

    //print array
    for (int i = 0; i < tam; i++){
        printf("Concorrente %-20s Tempo de prova: %-20d\n", resultado[i].concorrente.nome, resultado[i].tempoTotal);
    }
}

void calcMediaEtapa() {
    float result = 0;
    for (int i = 0; i < corrida->num_etapas; i++) {
        mediaEtapa[i].media = mediaEtapa[i].tempoTotal / mediaEtapa[i].cont;
        printf("Inicio: %s Fim: %s Total: %d Media %.2f\n", mediaEtapa[i].ini, mediaEtapa[i].fim, mediaEtapa[i].tempoTotal, mediaEtapa[i].media);
    }
}

//Apresentação do concorrente mais rápido / mais lento a efetuar uma prova válida;
void displayRapidoLento() {
    InfoCorrida rapido = *prova.corrida;
    InfoCorrida lento = *prova.corrida;
    InfoCorrida* c = prova.corrida;
    while (c) {
        //Se o numero de etapas da corrida for igual ao numero de etapas realizada pelo concorrente na corrida
        if (c->num_etapas == c->concorrente.qtdEtapas && c->num_etapas != 0) {
            if (c->tempoTotal > lento.tempoTotal) {
                lento = *c;
            }
            if (c->tempoTotal < rapido.tempoTotal) {
                rapido = *c;
            }
        }
        c = c->next;
    }

    printf("Mais rapido: %s com %d ms\n", rapido.concorrente.nome, rapido.tempoTotal);
    printf("Mais lento: %s com %d ms\n", lento.concorrente.nome, lento.tempoTotal);
}

/*  
    Cálculo do menor tempo em que é possível efetuar a prova na totalidade, ou seja, soma dos
    tempos mínimos por etapa independentemente de terem sido efetuados por concorrentes com
    provas válidas ou não; 
*/
int displayMinTempProva() {
    int sum = 0;
    for (int i = 0; i < corrida->num_etapas; i++) {
        sum += mediaEtapa[i].tempoMinimo;
    }
    return sum;
}

/* 
    Listagem das velocidades médias de toda a prova, ordenada por ordem decrescente. 
    Considere apenas as velocidades de concorrentes que efetuaram uma prova válida. 
*/
void calcVelocidadeMedia() {
    InfoCorrida* c = prova.corrida;
    //array
    InfoCorrida resultado[100] = { NULL };
    int tam = 0;
    while (c) {
        //Se o numero de etapas da corrida for igual ao numero de etapas realizada pelo concorrente na corrida
        if (c->num_etapas == c->concorrente.qtdEtapas && c->num_etapas != 0) {
            c->velocidadeMedia = c->distanciaTotal / c->tempoTotal;
            resultado[tam++] = *c;
        }
        c = c->next;
    }

    //ordenação array
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j <= tam; j++) {
            if (resultado[i].velocidadeMedia < resultado[j].velocidadeMedia) {
                InfoCorrida aux = resultado[i];
                resultado[i] = resultado[j];
                resultado[j] = aux;
            }
        }
    }

    //print array
    for (int i = 0; i < tam; i++) {
        printf("Concorrente %-20s Tempo de prova: %-20d ms com velocidade media: %.8f km/ms\n", resultado[i].concorrente.nome, resultado[i].tempoTotal,resultado[i].velocidadeMedia);
    }

}

/*
    Geração da tabela classificativa da prova, onde constem os seguintes campos de informação:
    posição na prova, número do concorrente, tempo total de prova, diferença para o concorrente
    anterior, diferença para o líder. Os concorrentes desclassificados deverão constar no final da
    tabela, ordenados por ordem crescente do seu número.
*/
void displayTabela() {
    FILE* out;
    //lista
    InfoCorrida* current = prova.corrida;

    int diferenca_anterior = 0;
    int diferenca_lider = 0;

    //array
    InfoCorrida resultado[100] = { NULL };
    int tam = 0;
    while (current) {
        resultado[tam++] = *current;
        current = current->next;
    }

    //ordenação array: tempo de prova
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j <= tam; j++) {
            if (resultado[i].tempoTotal > resultado[j].tempoTotal && resultado[i].tempoTotal > 0  && resultado[j].tempoTotal > 0) {
                InfoCorrida aux = resultado[i];
                resultado[i] = resultado[j];
                resultado[j] = aux;
            }
        }
    }

    /* abre o ficheiro resultados.txt para escrita e associa-o a out */
    out = fopen("resultados.txt", "w");
    if (out == NULL)
    {
        printf("ERRO: não consigo abrir o ficheiro resultados.txt\n");
        exit(1);
    }

    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Posicao", "Numero", "Nome", "Carro", "Tempo de prova", "Di. Ant.", "Di. Ldr.\n");
    fprintf(out, "%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Posicao", "Numero", "Nome", "Carro", "Tempo de prova", "Di. Ant.", "Di. Ldr.\n");
    for (int i = 0; i < tam; i++) {
        int posicao = i + 1;
        if (resultado[i].tempoTotal == 0) {
            printf("%-15s%-15d%-15s%-15s%-15d%-15d%-15d\n", "-", resultado[i].concorrente.id, resultado[i].concorrente.nome, resultado[i].concorrente.carro, resultado[i].tempoTotal, 0, 0);
            fprintf(out, "%-15s%-15d%-15s%-15s%-15d%-15d%-15d\n", "-", resultado[i].concorrente.id, resultado[i].concorrente.nome, resultado[i].concorrente.carro, resultado[i].tempoTotal, 0, 0);
            diferenca_anterior = resultado[0].tempoTotal;
        }
        else {
            diferenca_lider = resultado[i].tempoTotal - resultado[0].tempoTotal;
            diferenca_anterior = resultado[i].tempoTotal - diferenca_anterior;
            printf("%-15d%-15d%-15s%-15s%-15d%-15d%-15d\n", posicao, resultado[i].concorrente.id, resultado[i].concorrente.nome, resultado[i].concorrente.carro, resultado[i].tempoTotal, diferenca_anterior, diferenca_lider);
            fprintf(out,"%-15d%-15d%-15s%-15s%-15d%-15d%-15d\n", posicao, resultado[i].concorrente.id, resultado[i].concorrente.nome, resultado[i].concorrente.carro, resultado[i].tempoTotal,diferenca_anterior, diferenca_lider);
        }
    }

    fclose(out);
}
