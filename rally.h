/**
 * @rally.h
 * @author  Lucas Mendon�a <a17870@alunos.ipca.pt>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Ficheiro com a defini��o das estruturas e fun��es utilizadas ao longo do projeto.
 * Bliblioteca criada para aux�lio do processamento.
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
	com nome de in�cio da etapa, fim, dist�ncia percorrida, 
	tempo em que foi percorrida pelo concorrente e um apontador 
	para a pr�xima etapa efetuada;
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
	Guarda informa��es relativas � corrida e ao concorrente que 
	a realizou, ou seja, possui uma estrutura de dados de 
	Concorrente, o n�mero de etapas que a corrida possui, 
	tempo total de corrida do concorrente, distancia total 
	que o concorrente percorreu, assim como sua velocidade media 
	ao longo da corrida. Ainda, h� um apontador para outra 
	informa��o de corrida de outro concorrente.
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
	Guarda um apontador para a informa��o de um concorrente em uma corrida (in�cio da lista), 
	assim como a quantidade total de concorrentes que participaram daquela prova.
*/
typedef struct prova {
	InfoCorrida* corrida; //inicio da lista
	int quantidadeConcorrentes;
} Prova;

/**
	Cont�m informa��es sobre as etapas e suas medias.
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
	Processa ficheiro de informa��es sobre uma corrida
*/
extern int processaCorrida();

/**
	Processa as etapas que existem em uma corrida, assim como suas distancias totais
*/
extern int processaEtapa();

/**
	Processa os concorrentes com provas validas ou n�o
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
    Apresenta��o do concorrente mais r�pido / mais lento a efetuar uma prova v�lida.
*/
extern void displayRapidoLento();

/*
    C�lculo do menor tempo em que � poss�vel efetuar a prova na totalidade, ou seja, soma dos
    tempos m�nimos por etapa independentemente de terem sido efetuados por concorrentes com
    provas v�lidas ou n�o;
*/
extern int displayMinTempProva();

/*
    Listagem das velocidades m�dias de toda a prova, ordenada por ordem decrescente.
    Considere apenas as velocidades de concorrentes que efetuaram uma prova v�lida.
*/
extern void calcVelocidadeMedia();

/*
    Gera��o da tabela classificativa da prova, onde constem os seguintes campos de informa��o:
    posi��o na prova, n�mero do concorrente, tempo total de prova, diferen�a para o concorrente
    anterior, diferen�a para o l�der. Os concorrentes desclassificados dever�o constar no final da
    tabela, ordenados por ordem crescente do seu n�mero.
*/
extern void displayTabela();

