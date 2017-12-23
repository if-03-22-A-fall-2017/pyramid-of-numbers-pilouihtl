/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Pyramid of Numbers
 * Author:			<your name>
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
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
void print_big_int(const struct BigInt *big_int);

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

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	struct BigInt big_int;
	struct BigInt big_result;
	char str[MAX_DIGITS + 1];
	printf("Pyramid of numbers\n");
	printf("\n");
	printf("Please enter a number: ");
	scanf("%s", str);
	int len = strlen(str);
	int countString = strtobig_int(str, len, &big_int);

	if(countString >= 0)
	{
		printf(" Chars convert: %d\n", countString);
		copy_big_int(&big_int, &big_result);

		for(int i = 2; i < 10; i++){
			print_big_int(&big_result);
			multiply(&big_int, i,&big_result);
			printf(" * %d = ", i);
			print_big_int(&big_result);
			printf("\n");
		}
			for(int i = 9; i >= 2; i--){

			divide(&big_int, i, &big_result);
			printf("\n");
		}
	}
	return 0;
}

int strtobig_int(const char *str, int len, struct BigInt *big_int){
	int count = 0;
	if(len > MAX_DIGITS){
		big_int->digits_count = -1;
		printf("Error -1");
		return -1;
	}
	else{
		for(int i = 0; i < len; i++)
		{
			if(str[i] >= '0' && str[i] <= '9'){
				big_int->digits[i] = str[i] - '0';
				count++;
			}
			else{
				big_int->digits_count = -2;
				printf("Error -2\n");
				return -2;
			}
		}
		big_int->digits_count = count;
	}
	return count;
}

void print_big_int(const struct BigInt *big_result){
	for(int i = 0; i < big_result->digits_count; i++){
		printf("%d", big_result->digits[i]);
	}
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result){
	int carry = 0;
	int length = big_result->digits_count;
	for(int i = length - 1; i > -1; i--){
		int current = big_result->digits[i];
		int current_sum = current * factor + carry;
		carry = current_sum / 10;
		big_result->digits[i] = current_sum % 10;
	}
	if(carry > 0){
		big_result->digits_count = length + 1;
		for(int i = length - 1; i > -1; i--)
		{
			int change = big_result->digits[i];
			big_result->digits[i + 1] = change;
		}
		big_result->digits[0] = carry;
	}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result){
	int c = 0;
	for(int i = 0; i < big_result->digits_count; i++){
		if(big_result->digits[i] != 0 || c != 0)
		{
				printf("%d", big_result->digits[i]);
				c++;
		}
	}
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
	//big_result->digits[0] = carry;
	}
	int a = 0;
	printf(" / %d = ", divisor);
	for(int i = 0; i < big_result->digits_count; i++){
		if(big_result->digits[i] != 0 && a == 0)
		{
			printf("%d", big_result->digits[i]);
			a++;
		}
		else if(a != 0){
			printf("%d", big_result->digits[i]);
		}
	}
}

void copy_big_int(const struct BigInt *from, struct BigInt *to){
	to->digits_count = from->digits_count;
	for(int i = 0; i < to->digits_count; i++){
		to->digits[i] = from->digits[i];
	}
}
