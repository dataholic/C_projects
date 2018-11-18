#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct compl_num
{
	float x; //real part
	float y; //imaginary part
} complex_num;

#define PI 3.1415926535  

typedef struct polar_complex_num
{
	float theta; //argument in radian
	float modulus; //modulus
}polar_complex_num;


int	null_checker(complex_num z1)
{
	if (z1.x == 0 && z1.y == 0)
		return 1;
	return 0;
}

complex_num	complex_addition(complex_num z1, complex_num z2)
{
	complex_num z3;

	z3.x = z1.x + z2.x;
	z3.y = z1.y + z2.y;
	return (z3);
}

complex_num	complex_subtraction(complex_num z1, complex_num z2)
{
	complex_num z3;

	z3.x = z1.x - z2.x;
	z3.y = z1.y - z2.y;
	return (z3);
}

complex_num	complex_multi(complex_num z1, complex_num z2)
{
	complex_num z3;

	z3.x = (z1.x * z2.x) - (z1.y * z2.y);
	if (z3.x == 0)
		z3.x = 0;
	z3.y = (z1.x * z2.y) + (z1.y * z2.x);
	if (z3.y == 0)
		z3.y = 0;
	return (z3);
}


complex_num	complex_scale(complex_num z1, float a)
{
	complex_num z3;

	z3.x = z1.x * a;
	if (z3.x == 0)
		z3.x = 0;
	z3.y = z1.y * a;
	if (z3.y == 0)
		z3.y = 0;
	return (z3);
}

complex_num	complex_division(complex_num z1, complex_num z2)
{
	complex_num z3;

	z3.x = ((z1.x * z2.x) + (z1.y * z2.y)) / ((z2.x * z2.x) + (z2.y * z2.y));
	if (z3.x == 0)
		z3.x = 0;
	z3.y = ((-1 * z1.x * z2.y) + (z1.y * z2.x)) / ((z2.x * z2.x) + (z2.y * z2.y));
	if (z3.y == 0)
		z3.y = 0;
	return (z3);
}

complex_num to_algebraic(polar_complex_num z1)
{
	complex_num z2;

	z2.x = z1.modulus * cos(z1.theta);
	if (z2.x == 0)
		z2.x = 0;
	z2.y = z1.modulus * sin(z1.theta);
	if (z2.y == 0)
		z2.y = 0;
	return z2;
}

polar_complex_num to_polar(complex_num z1)
{
	polar_complex_num z2;

	if (z1.x == 0 || z1.y == 0)
		if (z1.x == 0)
			if (z1.y > 0)
				z2.theta = PI / 2;
			else
				z2.theta = PI / -2;
		else
			if (z1.x > 0)
				z2.theta = 0;
			else
				z2.theta = PI;
	else
		z2.theta = atan(z1.y / z1.x);
	z2.modulus = sqrt((z1.x * z1.x) + (z1.y * z1.y));
	return z2;
}

complex_num	*complex_sqrt(complex_num z1)
{
	complex_num *roots = (complex_num *)malloc(sizeof(complex_num) * 2);
	polar_complex_num z2 = to_polar(z1);
	z2.theta /= 2;
	if (z2.theta == 0)
		z2.theta = 0;
	z2.modulus = sqrt(z2.modulus);
	if (z2.modulus == 0)
		z2.modulus = 0;
	roots[0] = to_algebraic(z2);
	z2.theta += PI;
	roots[1] = to_algebraic(z2);
	return roots;
}

/////////////////////////////////////////////////////////////////////////////////

complex_num	*quadratic_equation_solver(complex_num a, complex_num b, complex_num c)
{
	complex_num *sols = (complex_num *)malloc(sizeof(complex_num) * 2);
	complex_num bsquared = complex_multi(b,b);
	complex_num ac = complex_multi(a,c);
	complex_num fourac = complex_scale(ac,4);
	complex_num delta = complex_subtraction(bsquared,fourac);
	complex_num sol;
	//printf("delta x is %f delta y is %f \n",delta.x,delta.y);
	if (null_checker(delta) == 1)
	{
		//printf("b x is  %f is and b  y is %f\n",b.x,b.y);

		//printf("-b x is  %f is and -b  y is %f\n",complex_scale(b,-1).x,complex_scale(b,-1).y);


		sol = complex_division(complex_scale(b,-1),complex_scale(a,2));
		//printf("sol x is %f is and sol y is %f\n",sol.x,sol.y);
		sols[0] = sol;
		return (sols);
	}
	else
	{
		sol = complex_division(complex_addition(complex_scale(b,-1),complex_sqrt(delta)[0]),complex_scale(a,2));
		sols[0] = sol;
		sol = complex_division(complex_subtraction(complex_scale(b,-1),complex_sqrt(delta)[0]),complex_scale(a,2));
		sols[1] = sol;
		return (sols);
	}
}


int main()
{
	complex_num z1;
	complex_num z2;
	complex_num z3;

	z1.x = 1;
	z1.y = 0;

	z2.x = 0;
	z2.y = 0;
	z3.x = 1;
	z3.y = 0;


	printf("solution 1  is %f + i * %f\n",quadratic_equation_solver(z1,z2,z3)[0].x,quadratic_equation_solver(z1,z2,z3)[0].y);
	printf("solution 2  is %f + i * %f\n",quadratic_equation_solver(z1,z2,z3)[1].x,quadratic_equation_solver(z1,z2,z3)[1].y);

	return (0);
}
