#include "rally.h"

int main() {
	processaCorrida();
	processaEtapa();
	processaConcorrentes();
	//InfoCorrida* result = getResult();
	printf("2. Quantidade de concorrentes: %d\n", getQtdConcorrentes());
	printf("3. Quantidade de concorrentes com provas validas: %d\n", getConcProvaVal());
	printf("4. Listagem, ordenada por ordem decrescente de tempo da prova, de todos os concorrentes que efetuaram uma prova valida.\n");
	displayListTempoProva();
	return 0;
}
