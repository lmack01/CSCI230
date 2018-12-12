#include <stdio.h>

/* @author - Levi Mack */


int main() {
	/* my first program in C */
	printf("Hello, World! \n\n");

	double r, B, P, total;

	r = 0.22;		/* anual interest rate */
	B = 5000.0;		/* ammount borrowed */
	P;// = 500.0;		/* payment amount (user input) */
	int n = 1;		/* month counter starting with first month */
	total = 0.0;		/* total interest paid */

	printf("Enter your monthly payment: ");
	scanf_s("%lf", &P);

	double io = (r / 12)*B;		/* the interest due after the first month */
	total += io;

	printf("\n%d %.2f %.2f\n", n, io, B);
	n++;
	B = B - P + io;

	while (B >= 0) {
		io = (r / 12)*B;
		//float I[n] = (r / 12)*(B - P + I[n - 1]);	/* the interest due after the nth month */
		total += io;
		printf("%d %.2f %.2f\n", n, io, B);
		B = B - P + io;
		n++;
	}

	printf("\nTotal interest paid: %.2f\n\n", total);

	return 0;
}

