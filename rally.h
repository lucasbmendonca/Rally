/**
 * @rally.h
 * @author  Lucas Mendonça <a17870@alunos.ipca.pt>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Ficheiro com a definição das estruturas e funções utilizadas ao longo do projeto.
 * Bliblioteca criada para auxílio do processamento.
 */

#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 255
#define TXT_CORRIDA "corrida.txt"
#define TXT_ETAPA "etapa.txt"
#define TXT_CONC "concorrentes.txt"

/**
	Etapa realizada por um concorrente em uma determinada prova, 
	com nome de início da etapa, fim, distância percorrida, 
	tempo em que foi percorrida pelo concorrente e um apontador 
	para a próxima etapa efetuada;
*/
typedef struct etapa {
	char inicio[3];
	char fim[3];
	float distancia;
	int tempo;
	struct etapa* next;
} Etapa;

/**
	Guarda os dados do concorrente, como seu nome, nome do carro,
	primeira etapa realizada, ultima etapa realizada e quantidade
	de etapas realizadas numa determinada prova.
*/
typedef struct concorrente {
	int id;
	char nome[50];
	char carro[10];
	Etapa* etapa;
	Etapa* etapa_ult;
	int qtdEtapas;
} Concorrente;

/**
	Guarda informações relativas à corrida e ao concorrente que 
	a realizou, ou seja, possui uma estrutura de dados de 
	Concorrente, o número de etapas que a corrida possui, 
	tempo total de corrida do concorrente, distancia total 
	que o concorrente percorreu, assim como sua velocidade media 
	ao longo da corrida. Ainda, há um apontador para outra 
	informação de corrida de outro concorrente.
*/
typedef struct corrida {
	Concorrente concorrente;
	int num_etapas;
	int tempoTotal;
	float distanciaTotal;
	float velocidadeMedia;
	struct corrida* next;
} InfoCorrida;

/**
	Guarda um apontador para a informação de um concorrente em uma corrida (início da lista), 
	assim como a quantidade total de concorrentes que participaram daquela prova.
*/
typedef struct prova {
	InfoCorrida* corrida; //inicio da lista
	int quantidadeConcorrentes;
} Prova;

/**
	Contém informações sobre as etapas e suas medias.
*/
typedef struct mediaEtapa {
	char ini[3]; //inicio da etapa
	char fim[3]; //fim da etapa
	int tempoTotal; //tempo total percorrido por todos os concorrentes na etapa
	int cont; //quantas vezes a etapa foi percorrida
	float media; //media da etapa
	int tempoMinimo; //Menor tempo feito na etapa
} MediaEtapa;

/**
	Processa ficheiro de informações sobre uma corrida
*/
extern int processaCorrida();

/**
	Processa as etapas que existem em uma corrida, assim como suas distancias totais
*/
extern int processaEtapa();

/**
	Processa os concorrentes com provas validas ou não
*/
extern int processaConcorrentes();

/**
	Retorna o resultado do carregamento efetuado
*/
extern InfoCorrida* getResult();

/**
	Busca quantidade de concorrentes.
*/
int getQtdConcorrentes();

/**
	Quantidade de concorrentes com provas validas.
*/
int getConcProvaVal();

/**
	Apresentacao do concorrente mais rapido / mais lento a efetuar uma prova valida.
*/
extern void displayListTempoProva();

/**
	Calculo das medias dos tempos por etapa e ordenado por ocorrencia.
*/
extern void calcMediaEtapa();

/**
    Apresentação do concorrente mais rápido / mais lento a efetuar uma prova válida.
*/
extern void displayRapidoLento();

/*
    Cálculo do menor tempo em que é possível efetuar a prova na totalidade, ou seja, soma dos
    tempos mínimos por etapa independentemente de terem sido efetuados por concorrentes com
    provas válidas ou não;
*/
extern int displayMinTempProva();

/*
    Listagem das velocidades médias de toda a prova, ordenada por ordem decrescente.
    Considere apenas as velocidades de concorrentes que efetuaram uma prova válida.
*/
extern void calcVelocidadeMedia();

/*
    Geração da tabela classificativa da prova, onde constem os seguintes campos de informação:
    posição na prova, número do concorrente, tempo total de prova, diferença para o concorrente
    anterior, diferença para o líder. Os concorrentes desclassificados deverão constar no final da
    tabela, ordenados por ordem crescente do seu número.
*/
extern void displayTabela();

