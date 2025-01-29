#include <stdio.h>
#include <stdlib.h>


int Len(FILE *f);
int Len(FILE *f) {
	int len = 0;
	double x;
	while(fscanf(f, "%lf", &x) == 1) {
		len++;
	}
	return len;
}


void Scan(FILE *f, double *arr, int n);
void Scan(FILE *f, double *arr, int n) {
	for (int i = 0; i < n; i++) {
		fscanf(f, "%lf", &arr[i]);
	}
}


int cmp(const void *a, const void *b);
int cmp(const void *a, const void *b) {
	double aa = *(double *)a;
	double bb = *(double *)b;
	if (aa > bb) {
		return 1;
	}
	else if (aa < bb) {
		return -1;
	}
	else return 0;
}


int main(void) {
	FILE *ina, *inb, *output;
	int na, nb;
	double *a, *b;

	ina = fopen("ina.txt", "r");
	if(ina == NULL) {
		printf("1\n");
		return -1;
	}

	inb = fopen("inb.txt", "r");
	if(inb == NULL) {
		printf("2\n");
		fclose(ina);
		return -1;
	}

	printf("Both files are open\n");

	output = fopen("ouput.txt", "w");
	if(output == NULL) {
		printf("3\n");
		fclose(ina);
		fclose(inb);
		return -1;
	}

	printf("Output file is open\n");

	na = Len(ina);
	nb = Len(inb);
	if (na == 0 || nb == 0) {
		printf("4\n");
		fclose(ina);
		fclose(inb);
		fclose(output);
		return -1;
	}

	printf("na = %d\n", na);
	printf("nb = %d\n", nb);

	rewind(ina);
	rewind(inb);

	a = (double *)malloc(na * sizeof(double));
	if (!a) {
		a = 0;
		printf("5\n");
		fclose(ina);
		fclose(inb);
		fclose(output);
		return -1;
	}

	b = (double *)malloc(nb * sizeof(double));
	if (!b) {
		b = 0;
		printf("6\n");
		fclose(ina);
		fclose(inb);
		fclose(output);
		return -1;
	}

	Scan(ina, a, na);
	fclose(ina);
	Scan(inb, b, nb);
	fclose(inb);

	qsort(a, na, sizeof(double), cmp);
	qsort(b, nb, sizeof(double), cmp);

	for (int i = 0; i < na; i++) {
		fprintf(output, "%lf\n", a[i]);
	}
	for (int i = 0; i < nb; i++) {
		fprintf(output, "%lf\n", b[i]);
	}

	fclose(output);
	free(a);
	free(b);
	return 0;
}