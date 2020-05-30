#include <stdio.h>

int main()
{
	int decks;
	puts("Enter a number of decks");
	scanf("%i", &decks);
	if (decks < 1){
		puts("Thats not a valid number");
		return 1;
	}
	printf("There are %i cards\n", (decks*52));
	return 0;
}

