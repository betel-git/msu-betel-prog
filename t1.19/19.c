/* Определить, каких участков в последовательности больше - возрастающих или невозрастающих */
/* Алгоритм такой:
	1. Если последовательность возрастающая, то bool == 1
	2. Иначе bool == 0
	3. Если bool меняет значение, то счётчик прибавляет +1
	*/
#include "fun.h"
int main(void) {
	FILE *inputFile = fopen("input.txt", "r");
	FILE *outputFile = fopen("output.txt", "w");

	if (!inputFile) {
		fprintf(stderr, "Error opening input file\n");
		return -1;
	}
	if (!outputFile) {
		fprintf(stderr, "Error opening output file\n");
		return -1;
	}
	Function(inputFile);
	fclose(inputFile);
	fclose(outputFile);
}
