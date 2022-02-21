#include <stdio.h>
/* va_list */
#include <stdarg.h>

int add_multiple_values (int number, ...)
{
	int counter, total = 0;

	/* Declare a variable of type ‘va_list’. */ 
	va_list parameters;

	/* Call the ‘va_start’ function. */ 
	va_start (parameters, number);

	for (counter = 0; counter < number; counter++)
	{
		/* Get the values of the optional parameters. */
		total += va_arg (parameters, int);
	}

	/* End use of the ‘parameters’ variable. */ va_end (parameters);
	return total;
}


int main(){

	printf("sum(1,2,3)=%d\n",add_multiple_values(3,1,2,3));
	printf("sum(1,2,3,4)=%d\n",add_multiple_values(4,1,2,3,4));
	printf("sum(1,2,3,4,5)=%d\n",add_multiple_values(5,1,2,3,4,5));
	printf("sum(1,2,3,4,5,6)=%d\n",add_multiple_values(6,1,2,3,4,5,6));
}



