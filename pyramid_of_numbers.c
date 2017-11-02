#include <stdio.h>
#define MAX_DIGITS 80
/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
/** number of digits of the big int. */
int digits_count;
/** array of digits of big int. */
unsigned int digits[MAX_DIGITS];
};
/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);
/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(struct BigInt *big_result);
/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);
/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);
/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);
void print_big_intDivide(struct BigInt *big_result);
int main(int argc, char *argv[])
{
	struct BigInt big_int;
	struct BigInt big_result;
	char input[MAX_DIGITS + 1];
	printf("Enter a number:");
	scanf("%s",input);
	int len = strlen(input);
	int charsConvertet = strtobig_int(input, len, &big_int);
	printf("%d Convertet Numbers\n", charsConvertet );
	copy_big_int(&big_int,&big_result);
	for (int factor = 2; factor < 10; factor++)
	{

		print_big_int(&big_result);
		multiply(&big_int,factor,&big_result);
		printf("* %d =",factor);
		print_big_int(&big_result);
		printf("\n");
	}
	for (int divisor = 9; divisor > 1; divisor--)
	{
		print_big_intDivide(&big_result);
		divide(&big_int,divisor,&big_result);
		printf("/ %d =",divisor);
		print_big_intDivide(&big_result);
		printf("\n");
	}
	return 0;
}
int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
	if(len > 80)
	{
		printf("Error:-1 input to long\n");
		big_int -> digits_count = -1;
		return -1;
	}
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <='9')
		{
			big_int->digits[i] = str[i] - '0';
		}
		else
		{
			printf("Error= -2 invalid input\n");
			big_int->digits_count = -2;
			return -2;
		}
	}
	big_int->digits_count = len;
	return len;
}
void print_big_int(struct BigInt *big_result)
{
	for(int i = 0; i < big_result->digits_count ; i++)
	{
		printf("%d",big_result->digits[i]);
	}
}
void print_big_intDivide(struct BigInt *big_result)
{
	int counter = big_result->digits_count;
	int check = 0;
	for (int i = 0; i < counter; i++)
	{
		if(big_result->digits[i] != 0 && check == 0)
		{
			printf("%d",big_result->digits[i]);
			check++;
		}
		else if(check != 0){
			printf("%d",big_result->digits[i]);
		}
	}
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int carry = 0;
	int len = big_result->digits_count;
	for (int i = len-1; i >= 0; i--)
	{
		int current_digit = big_result->digits[i];
		int number = current_digit *factor + carry;
		carry = number /10;
		big_result->digits[i] = number %10;
	}
	if (carry > 0)
	{
		big_result->digits_count = len + 1;
		for (int i = len-1; i >= 0; i--)
		{
			int cross = big_result->digits[i];
			big_result->digits[i+1] = cross;
		}
		big_result->digits[0] = carry;
	}
}
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	int carry = 0;
	int len = big_result->digits_count;
	for (int i = 0; i < len; i++)
	{
		int current_digit = big_result->digits[i];
		int number = (current_digit + carry * 10) / divisor;
		if(number == 0)
		{
			carry = current_digit % 10;
		}
		else
		{
			carry = (current_digit+carry*10)-(number*divisor);
		}
		big_result->digits[i] = number %10;
	}
	if (carry > 0)
	{
		big_result->digits_count = len - 1;
		for (int i = 0; i < len; i++)
		{
			int cross = big_result->digits[i];
			big_result->digits[i-1] = cross;
		}
	big_result->digits[0] = carry;
	}
}
void copy_big_int(const struct BigInt *from, struct BigInt *to)
{
	to->digits_count = from->digits_count;
	for(int i = 0;i< to->digits_count;i++)
	{
		to->digits[i]= from->digits[i];
	}
}
