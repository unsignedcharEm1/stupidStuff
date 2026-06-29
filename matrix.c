#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Matrix
typedef struct dimension {
	int row, column;
} dimension;
typedef struct matrix {
	int **element;
	dimension *dim;
} matrix;
//
// operations
matrix* makeMatrix(int r, int c) {
	// Make the matrix
	matrix *p;
	p = malloc(sizeof(matrix));

	// Set dimensions
	p->dim = malloc(sizeof(dimension));
	p->dim->row = r;
	p->dim->column = c;
	
	// set up matrix elements
	// Rows
	p->element = malloc(sizeof(int *)*r);
	// Columns
	for (int i = 0; i < r; i++) {
	p->element[i] = malloc(sizeof(int) * c);
		for (int j = 0; j < c; j++) p->element[i][j] = 0;
	}
	return p;
}
void printMatrix(matrix *p) {
	for (int r = 0; r < p->dim->row; r++) {
		for (int c = 0; c < p->dim->column; c++) {
			printf("%d ", p->element[r][c]);
		}
		putchar('\n');
	}
}
// Main
int main(int argc, char **argv) {
	matrix *mat = makeMatrix(atoi(argv[1]),atoi(argv[2]));
	printf("dimension %d x %d\n", mat->dim->row, mat->dim->column);
	printMatrix(mat);
}
