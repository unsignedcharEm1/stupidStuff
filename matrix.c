#include<stdio.h>
#include<stdlib.h>
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
	for (int i = 0; i < c; i++) {
	p->element[i] = malloc(sizeof(int));
	}
	return p;
}
int main() {
	matrix *mat = makeMatrix(3,3);
	printf("dimension %d x %d\n", mat->dim->row, mat->dim->column);
}
