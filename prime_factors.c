#include <stdio.h>
#include <stdlib.h>

typedef struct prime_factor
{
	unsigned int factor;
	struct prime_factor *next;
}	prime_factor;

prime_factor	*prime_factors(unsigned int n)
{
	prime_factor *current = malloc(sizeof(prime_factor));
	prime_factor *prev = malloc(sizeof(prime_factor));;
	prime_factor *start = malloc(sizeof(prime_factor));;
	int i = 2;
	int j = 0;
	int m = n;
	while (m != 1)
	{
		if (m % i == 0)
		{
			current->factor = i;
			if (j > 0)
				prev->next = current;
			if (j == 1)
				start = prev;
			if (n == i)
			{
				current->next = NULL;
				return current;
			}
			current->next = malloc(sizeof(prime_factor));
			prev = current;
			current = current->next;
			m /= i;
			i = 2;
			j++;
		}
		else
			i++;
	}
	prev->next = NULL;
	return start;
}
int main()
{
	prime_factor *a = prime_factors(500);

	while(a != NULL)
	{
		printf("%u\n",a->factor);
		a = a->next;
	}
	return 0;
}
