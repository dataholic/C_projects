#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	is_prime(unsigned int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return 0;
	}
	return 1;
}

int	*prime_factors(unsigned int n)
{
	int *factors = (int *)malloc(sizeof(int) * (n / 2));
	int i = 2;
	int j = 0;
	int m = n;
	while (m != 1)
	{
		if (m % i == 0)
		{
			factors[j] = i;
			m /= i;
			i = 2;
			j++;
		}
		else
			i++;
	}
	while (j < (n / 2))
	{
		factors[j] = 1;
		j++;
	}
	return (factors);
}
int main()
{
	unsigned int n = 5800;
	for (int i = 0;prime_factors(n)[i] != 1;i++)
	{
		printf("%d\t",prime_factors(n)[i]);
	}
	printf("\n");
	return 0;
}
