#include<stdio.h>
#include"numutil.h"
static unsigned int meowed = 0;
// Functions
void meow() {
	printf("You have meowed %d times!\n", ++meowed);
}
