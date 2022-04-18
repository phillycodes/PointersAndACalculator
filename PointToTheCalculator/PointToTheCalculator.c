/*
 * File Name:		PointToTheCalculator.c
 * Names:			Philben Pierre
 * Course:			COP 2220C at Valencia College
 * Professor:		David Stendel
 * Description:		The first thing to show up in the program is a calculator menu. The menu has
 *					nine options to choose from. Enter values, add, subtract, multiply, divide,
 *					average, maximum value, an option to determine whether each value entered is
 *					positive, negative or zero, and a quit option.
 *					The program presents the menu and requests for an input from the user.
 *					If the user enters an input that is not prompted in the menu then
 *					an error message will pop-up informing the user that they had entered an
 *					invalid entry. The program allows the user to try again. For a few of the
 *					options the user cannot select them without first selecting "Enter Values".
 *					If the user tries to do so without entering the values then an error message
 *					will pop up saying that they have not entered any values. The user can chose
 *					as they please until they select 'Q' for quit. After doing so they will be
 *					thanked for using the application.
 * Date:			04/01/21 - 04/06/21
 */

// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function Prototype(s)
double calculateAddition(double numArray[], int size);
double calculateAverage(double numArray[], int size);
double calculateDifference(double numArray[], int size);
double calculateDivision(double numArray[], int size, double *res);
double calculateMultiplication(double numArray[], int size);
int changeSizeOfArray(int size);
void determineSignage(double numArray[], int size);
char displayMenu();
double getGreatestValue(double numArray[], int size);
void isZeroFound(double numArray[], int size, bool *zero);
void printArray(double numArray[], int arrSize);
void processMenu(char *choice, double numArray[], int *size, bool *valuesEntered);

/*
 * Name:			main()
 * Parameters:		None.
 * Processes:		First thing to show up in the function is a calculator menu. The menu has nine
 *					options to choose from. Enter Values, add, subtract, multiply, divide,
 *					average, maximum value, a possibility to decide whether each value entered is
 *					positive, negative or zero, and a quit option.
 *					The function presents the menu and requests for an input from the keyboard.
 *					If the user enters an input that is not prompted in the menu then
 *					an error message will pop-up informing the user that they had entered an
 *					invalid entry. The function has a loop to try again. For a few of the
 *					cases the user cannot select them without first selecting "Enter Values".
 *					If the user tries to do so without entering the values then an error message
 *					will pop up. The user can continously make different choices as they
 *					please until they select 'Q' for quit. After doing so they will be thanked
 *					for using the application.
 * Return Value:	An integer representing an error code; if the program ends without error, zero
 *					will be returned to the calling program or operating system.
 */
int main() {
	// Variables
	char menuChoice = '\0';
	double *numbersArray = NULL;
	bool *valuesEntered = false;
	bool foundZero = false;
	int size;
	size = 1;
	int *sizePtr = &size;

	printf("Enter number of double values: ");
	scanf_s("%i", &size);

	/*size = changeSizeOfArray();*/
	do {
		// Array Size Configuration
		if (numbersArray == NULL) {
			numbersArray = (double *)calloc(*sizePtr, *sizePtr * sizeof(double));
		} else {
			numbersArray = (double *)realloc(numbersArray, *sizePtr * sizeof(double));
		}
		  // Output - Instructions
		menuChoice = displayMenu();

		// Menu Processing
		processMenu(&menuChoice, numbersArray, &size, &valuesEntered);
	} while (menuChoice != 'q' && menuChoice != 'Q');
	printArray(numbersArray, size);
	free(numbersArray);

	return 0;
}

/*
 * Name:			CalculateAddition()
 * Parameters:		numArr		An array containing double elements.
 *					size		The size of the array.
 * Processes:		The function will take in a double array and int to perform the operation
 *					addition to each element in the array and return that value.
 * Return Value:	Double		The sum of the elements within the array.
 */
double calculateAddition(double numArr[], int size) {
	// Variables
	double result;
	double *pArr = numArr;

	// Calculations 
	result = numArr[0];
	for (pArr = &numArr[1]; pArr < &(numArr[size]); pArr++) {
		result += *pArr;
	}

	return result;
}

/*
 * Name:			CalculateAverage()
 * Parameters:		numArr		A double array with double values.
 *					size		The size of the array.
 * Processes:		Function will calculate the average between the values within the
 *					array numArr. Afterwards it will return the double value.
 * Return Value:	Double		The average of the values in the array.
 */
double calculateAverage(double numArr[], int arrSize) {

		// Variables
	double result;
	double *pArr = numArr;

	// Calculations 
	result = numArr[0];
	for (pArr = &numArr[1]; pArr < &(numArr[arrSize]); pArr++) {
		result += *pArr;
	}
	result /= arrSize;

	return result;
}

/*
 * Name:			CalculateDifference()
 * Parameters:		numArr		A double array with double values.
 *					size		The size of the array.
 * Processes:		Function will calculate the difference between each of the values within the
 *					array passed in as a parameter. Then returns the double value.
 * Return Value:	Double		The differenc between the elements within the array.
 */
double calculateDifference(double numArr[], int size) {
	// Variables
	double result;
	double *pArr = numArr;

	// Calculations 
	result = numArr[0];
	for (pArr = &numArr[1]; pArr < &(numArr[size]); pArr++) {
		result -= *pArr;
	}

	return result;
}

/*
 * Name:			CalculateDivision()
 * Parameters:		numArr		A double array with double values.
 *					arrSize		The size of the array.
 *					result		The result of the calculation.
 * Processes:		Function will divide each of the values within the array as long as it does
 *					not encounter a zero. If it does then the function will output an error
 *					message. Afterwards, if no zeroes are found after the first element the
 *					function will return a double value.
 * Return Value:	Double		The quotient between the elements within the array.
 */
double calculateDivision(double numArr[], int arrSize, double *result) {
	// Variables
	bool zerosFound = false;
	double *pArr = numArr;

	// Zero Check
	isZeroFound(numArr, arrSize, &zerosFound);

		// Calculations 
	if (zerosFound == true) {
		printf("\n\tError: Cannot divide by zero!\n");
	} else {
		*result = numArr[0];
		for (pArr = &numArr[1]; pArr < &(numArr[arrSize]); pArr++) {
			*result /= *pArr;
		}
	}

	return *result;
}

/*
 * Name:			CalculateMultiplication()
 * Parameters:		numArr		A double array with double values.
 *					size		The size of the array.
 * Processes:		Function will multiply each element within the array to each other.
 *					Afterwards it will return the double value.
 * Return Value:	Double		The product of the elements within the array.
 */
double calculateMultiplication(double numArr[], int arrSize) {
	// Variables
	double result;
	double *pArr = numArr;

	// Calculations 
	result = numArr[0];

	for (pArr = &numArr[1]; pArr < &(numArr[arrSize]); pArr++) {
		result *= (*pArr);
	}

	return result;
}

/*
 * Name:			ChangeSizeOfArray()
 * Parameters:		sizeOfArray		The size of the array.
 * Processes:		The function will prompt the user to enter an integer value for
 *					the new size of the array.
 * Return Value:	Int				The size for a new array.
 */
int changeSizeOfArray(int sizeOfArray) {
	int size = 0;
	printf("Enter number of double values: ");
	scanf_s("%i", &size);
	sizeOfArray = size;

	return sizeOfArray;
}

/*
 * Name:			DetermineValueState()
 * Parameters:		numArr		An double array with double values.
 *					arrSize		The size of the array.
 * Processes:		Function will determine whether or not if each element within the array is
 *					positive, negative, or zero and output a statement.
 * Return Value:	None.
 */
void determineSignage(double numArr[], int arrSize) {
	// Variables
	double *pArr = numArr;

	// Calculations 
	for (pArr = &numArr[0]; pArr < &(numArr[arrSize]); pArr++) {
		if (*pArr > 0) {
			printf("The number %.3f is Positive.\n", *pArr);
		} else if (*pArr < 0) {
			printf("The number %.3f is Negative.\n", *pArr);
		} else {
			printf("The number %.3f is Zero.\n", *pArr);
		}
	}
}

/*
 * Name:			DisplayMenu()
 * Parameters:		None.
 * Processes:		Prompts the menu options that are available to the user. Takes a character as
 *					input.
 * Return Value:	Character		The menu selection the user made.
 */
char displayMenu() {
	// Variables
	char choice = '\n';

	// Input Selection Menu
	printf("Calculator Menu\n\n");
	printf("G(E)t Numbers\n");
	printf("(A)dd\n");
	printf("(S)ubtract\n");
	printf("(M)ultiply\n");
	printf("(D)ivide\n");
	printf("A(V)erage\n");
	printf("(G)reatest Value\n");
	printf("(P)ositive, Negative, or Zero\n");
	printf("(C)hange Number of Double Values\n");
	printf("(Q)uit\n");
	printf("Enter Selection: ");
	scanf_s(" %c", &choice, 1);

	return choice;
}

/*
 * Name:			GetGreatestValue()
 * Parameters:		numArr			An array containing double values.
 *					arrSize			The size of the array.
 * Processes:		Function will search the array for the greatest value and return it.
 * Return Value:	Double			The greatest value in the array.
 */
double getGreatestValue(double numArr[], int arrSize) {
	// Variables
	double result;
	double *pArr = numArr;

	// Calculations 
	result = numArr[0];
	for (pArr = &numArr[1]; pArr < &(numArr[arrSize]); pArr++) {
		if (*pArr > result) {
			result = *pArr;
		}
	}

	return result;
}

/*
 * Name:			isZeroFound()
 * Parameters:		numArr		An double array with double values.
 *					size		The size of the array.
 *					bool		The result of if a zero is found in the array
 * Processes:		The function will determine if the array has a zero. If the array has a zero
 *					then the function will return true.
 * Return Value:	None.
 */
void isZeroFound(double numArr[], int arrSize, bool *foundZero) {
	// Variables
	*foundZero = false;
	double *pArr = numArr;
	int i;

	// Checking For Zero After The First Value
	for (pArr = numArr; pArr < &numArr[arrSize]; pArr++) {
		if (pArr == 0) {
			*foundZero = true;
		}
	}
}

/*
 * Name:			PrintArray()
 * Parameters:		numArray	An double array with double values.
 *					arrSize		The size of the array.
 * Processes:		Function will output an array passed in the parameter.
 * Return Value:	None.
 */
void printArray(double numArray[], int arrSize) {
	// Variables
	double *ptr;

	// Output
	printf("The element(s) of the array is/are: ");
	for (ptr = numArray; ptr < &numArray[arrSize]; ptr++) {
		printf("%.3f ", *ptr);
	}
}

/*
 * Name:			ProcessMenu()
 * Parameters:		choice			A character that is used to make a selection in the menu.
 *					numArrs			An array filled with double elements.
 *					arrSize			The size of the array.
 *					valuesEntered	Validates whether the function got numbers.
 * Processes:		Function accepts four parameters.
 * Return Value:	None.
 */
void processMenu(char *choice, double numArrs[], int *arrSize, bool *valuesEntered) {
	// Variables
	int i;
	double result = 0;
	bool *foundZero = false;
	double *arrPointer = numArrs;

	// Menu Input Process
	switch (*choice) {
		case 'e':
		case 'E':

			//Output  - Instruction
			printf("Enter %i double values: ", *arrSize);

			// Gets Input
			for (i = 0; i < *arrSize; i++) {
				scanf_s("%lf", &(numArrs[i]));
				printf("%f\n", numArrs[i]);
			}
			*valuesEntered = true;
			break;
			*valuesEntered = true;
			break;
		case 'a':
		case 'A':
			// Validation - The User Must Already Have Entered The Values In Order To Perform The
			// Calculation
			if (*valuesEntered == true) {
				result = calculateAddition(numArrs, *arrSize);

				// Output
				printf("Answer: ");
				for (i = 0; i < *arrSize - 1; i++) {
					printf("%.3f + ", *(numArrs + i));
				}
				printf("%.3f = %.3f\n", numArrs[i], result);
			} else {
				printf("\n\tError: You have not entered %i numbers!\n\n", *arrSize);
			}
			break;
		case 's':
		case 'S':
			// Validation - The User Must Already Have Entered The Values In Order To Perform The
			// Calculation
			if (*valuesEntered == true) {
				result = calculateDifference(numArrs, *arrSize);

				// Output
				printf("Answer: ");
				for (i = 0; i < *arrSize - 1; i++) {
					printf("%.3f - ", *(numArrs + i));
				}
				printf("%.3f = %.3f\n", numArrs[i], result);
			} else {
				printf("\n\tError: You have not entered %i numbers!\n\n", *arrSize);
			}
			break;
		case 'm':
		case 'M':
			// Validation - The User Must Already Have Entered The Values In Order To Perform The
			// Calculation
			if (*valuesEntered == true) {
				result = calculateMultiplication(numArrs, *arrSize);

				// Output
				printf("Answer: ");
				for (i = 0; i < *arrSize - 1; i++) {
					printf("%.3f * ", numArrs[i]);
				}
				printf("%.3f = %.3f\n", numArrs[i], result);
			} else {
				printf("\n\tError: You have not entered %i numbers!\n\n", *arrSize);
			}
			break;
		case 'd':
		case 'D':
			// Validation - The User Must Already Have Entered The Values In Order To Perform The
			// Calculation
			if (*valuesEntered == true) {
				isZeroFound(numArrs, arrSize, &foundZero);
				if (foundZero == true) {
					printf("\n\tError: You cannot divide by zero!\n\n");
				} else {
					result = calculateDivision(numArrs, *arrSize, &result);
				}

				// Output
				printf("Answer: ");
				for (i = 0; i < *arrSize - 1; i++) {
					printf("%.3f / ", numArrs[i]);
				}
				printf("%.3f = %.3f\n", numArrs[i], result);
			} else {
				printf("\n\tError: You have not entered %i numbers!\n\n", *arrSize);
			}
			break;
		case 'v':
		case 'V':
			// Validation - The User Must Already Have Entered The Values In Order To Perform The
			// Calculation
			if (*valuesEntered == true) {
				result = calculateAverage(numArrs, *arrSize);
				printf("Answer: (");
				for (i = 0; i < *arrSize - 1; i++) {
					printf("%.3f + ", numArrs[i]);
				}
				printf("%.3f) / %i = %.3f\n", numArrs[i], *arrSize, result);
			} else {
				printf("\n\tError: You have not entered %i numbers!\n\n", *arrSize);
			}
			break;
		case 'g':
		case 'G':
			// Validation - The User Must Already Have Entered The Values In Order To Perform The
			// Calculation
			if (*valuesEntered == true) {
				result = getGreatestValue(numArrs, *arrSize);
				printf("Answer: %.3f", result);
			} else {
				printf("\n\tError: You have not entered %i numbers!\n\n", *arrSize);
			}
			break;
		case 'p':
		case 'P':
			determineSignage(numArrs, *arrSize); // Positive, Negative, or Zero
			break;
		case 'c':
		case 'C':
			*arrSize = changeSizeOfArray(arrSize);
			break;
		case 'q':
		case 'Q':
			printf("\nGood-Bye! Thanks for using my program!\n");
			break;
		default:
			printf("\n\tError: You have made an invalid selection!\n\n");
	}
}
