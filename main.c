#include "rally.h"

int main() {
	processaCorrida();
	processaEtapa();
	processaConcorrentes();
	InfoCorrida* result = getResult();
	printf("2. Quantidade de concorrentes: %d\n", getQtdConcorrentes());
	printf("3. Quantidade de concorrentes com provas validas: %d\n", getConcProvaVal());
	displayListTempoProva();
	return 0;
}
