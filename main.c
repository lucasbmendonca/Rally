/**
 * @main.c
 * @author  Lucas Mendonça <a17870@alunos.ipca.pt>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Ficheiro com a chamada das funções.
 */

#include "rally.h"

int main() {
	processaCorrida();
	processaEtapa();
	processaConcorrentes();
	InfoCorrida* result = getResult();
	printf("1. Dados carregados para os concorrrentes:\n");
	while (result) {
		printf("%s\n", result->concorrente.nome);
		result = result->next;
	}
	printf("2. Quantidade de concorrentes: %d\n", getQtdConcorrentes());
	printf("3. Quantidade de concorrentes com provas validas: %d\n", getConcProvaVal());
	printf("4. Listagem, ordenada por ordem decrescente de tempo da prova, de todos os concorrentes que efetuaram uma prova valida.\n");
	displayListTempoProva();
	printf("5. Calculo das medias dos tempos por etapa e ordenado por ocorrencia.\n");
	calcMediaEtapa();
	printf("6. Apresentacao do concorrente mais rapido / mais lento a efetuar uma prova valida.\n");
	displayRapidoLento();
	printf("7. Calculo do menor tempo em que e possível efetuar a prova na totalidade\n");
	printf("%d ms\n", displayMinTempProva());
	printf("8. Listagem das velocidades medias de toda a prova, ordenada por ordem decrescente\n");
	calcVelocidadeMedia();
	printf("9. Geracao da tabela classificativa da prova.\n");
	displayTabela();
}
