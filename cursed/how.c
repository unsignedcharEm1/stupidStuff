#include<stdio.h>
int main() {
	for (int i = 0, j = 67; i < 10; i++, ++i, j += 2)
		printf("i = %d j = %d\n", i, j);
}
