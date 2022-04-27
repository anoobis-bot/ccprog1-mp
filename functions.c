/* 
	This c source file is where most of the code will be located. I have implemented this separate C file to avoid 
	cluttering in the main.c
*/
#include "header.h"

#define MAX_LEN 128		// will be used for displayText() function. This is the buffer size for fgets.

/*	The price of each product has a pattern. Product 0 has a low price of 180, product 1 has a price of low 280
	With each product, 100 is just added to the price range. All the program needs to generate a price is to know the base price
	and the multiplyer, which is 100 to generate a price with each product*/
#define BASE_PRICE_L 180		
#define BASE_PRICE_H 200
#define DISCOUNT_PRICE_L 100
#define DISCOUNT_PRICE_H 150
#define MULTIPLYER 100


/*	This function display ASCII art that is pasted into text files

	Precondition: the file is existing and has a file type of .txt

	@param filename is the directory for the text file ascii text

	@return void
*/
void displayArt(char* filename)
{
	FILE* fptr = NULL;			// file object

	char read_string[MAX_LEN];	// string buffer

	short int open = 0;			// short was used to save memory

	if ((fptr = fopen(filename, "r")) != NULL)	// checking if file opening is succesful
	{
		open = 1;

		while (fgets(read_string, sizeof(read_string), fptr) != NULL)	// Printing the contents of the text file
			printf("%s", read_string);
	}
	else	// print text if file opening was not succesful
	{
		fprintf(stderr, "error opening %s\n", filename);
	}
	
	if (open == 1)		// closes the file if it was succesfully opened
		fclose(fptr);

	printf("\n");		// design purposee so that in every displayArt() call would automatically move the carriage to a new line
}


/*	This function handles the start screen main menu where the player gets to choose which city to go to first or to quit the game

	Precondition: the input would only be numbers, arrowkey strokes, and enter key. letters would make scanf return an error
					and will make the program loop endlessly.

	@param *sName[] is a poitner to a string located in main.c. This is the list of cities.
	@param dArSize is the  number of elements in *sName[]. This is important for the for loop.
	@param *dInMethod is either 0 or 1 only. 0 means the player is using numbers as input. 1 means the input is arrow keys and enter.
			The other pointer parameters are pointers so variables would not be initialized in every function call.
	@param *dCurSel is refreshed everytime the user presses enter when *intMethod == 1. This value is whatever the current
			value the cursor is on.
	@param *cBuffer is used to hold the 0xE0 in the arrow key function. When _getch() is used, and arrow keys are enterd, 
			it outputs 2 characters. The first is 0xE0, then the second is the character for the specific arrow key.

	@return The choice that the user selected. Count starts with 0, to synchronize with the sName[] array.
*/
int start(char *sName[], int dArSize, int *dInMethod, int *dCurSel, int *cBuffer)
{
	int dChoice = 0;	// variable that will be returned
	int i = 0;			// variable used for for loops
	
	do	// do-while is used to get the right input from user. will loop if the input is invalid.
	{
		if (*dInMethod == 0)	// numbers as input
		{
			system("cls");		// clears the screen every time it loops
			
			displayArt("AsciiArt\\StartArt.txt");

			printf("\n---------------------------------------------------------------------------");
			printf("\nWelcome to The Known World! This game is a trading game where you can \ntrade with other cities and grow your money.");
			printf("\nYou can choose how you can play the game by toggling the \"Controls\" \noptions below. Enjoy the game!\n\n");

			for (i = 0; i < dArSize; i++)
			{
				if (i == SNAME_SIZE - SNAME_OPT)		// design prupose. a new line will be created after the cities
				{
					printf("\n");
				}
				printf("[%d] %s\n", i + 1, sName[i]);	// print each element contents of the array sName[]
			}
			printf("\nChoice: ");			// input after displaying the whole main menu. this will be 1-8
			if (scanf("%d", &dChoice) == 0)	// input guard
				scanf("%c", &dChoice);

			dChoice--;		// if the input method is numbered, this line is used to synchronize the array with the
							// inputed value, since user enters starts counting at 1. So that whenever the user decides to use
							// the arrow keys, they both return the same value.
		}

		else if (*dInMethod == 1)		// arrow keys as input
		{
			while ((*cBuffer) != '\r')	// cBuffer is used to check if the user has pressed the enter key. 
			{							// Loop will end after that.
				
				system("cls");			// same implementation for the numbers input
				displayArt("AsciiArt\\StartArt.txt");
				
				printf("\n---------------------------------------------------------------------------");
				printf("\nWelcome to The Known World! This game is a trading game where you can \ntrade with other cities and grow your money.");
				printf("\nYou can choose how you can play the game by toggling the \"Controls\" \noptions below. Enjoy the game!\n\n");

				for (i = 0; i < dArSize; i++)
				{
					if (i == SNAME_SIZE - SNAME_OPT)
					{
						printf("\n");
					}
					
					if (*dCurSel == i)	// dCurlSel is the value where the cursor is on. If the cursor is in i, print sNum[i] with
						printf(">> ");	// a >>, else print it with just a space "   "
					else
						printf("   ");
					
					printf("%s\n", sName[i]);
				}

				*cBuffer = _getch();	// input. 
										// if the user presses enter key, the cBuffer value, which is '\r' will be used to 
										// stop the while loop. it will skip the if statments below

				if (*cBuffer == 0xE0)	// when control or arrow keys are pressed, _getch() returns 0xE0 and the value of the 
				{						// correesponding keys. cBuffer acts as the catcher of the 0xE0, so that the true value
					switch (_getch())	// can be caught
					{
						/*	this will be 0-7 since dCurSel starts with 0, so does an array count. (sName). 
						basically dCurlSel is a cursor for the array sName, the cursor points and returns the element position*/
						case 'H':		// up arrow jey
							if ((*dCurSel) > 0)	// makes sure the cursor in within the range of the options
								(*dCurSel)--;	// dCurSel is always updated when keys are pressed
							break;
						case 'P':		// down arrow key
							if ((*dCurSel) < dArSize - 1)
								(*dCurSel)++;
							break;
					}
				}
			}

			//	this executes when the user has finally pressed enter or '\r'
			// assigns the dCurSel to the dChoice for return
			dChoice = *dCurSel;
		}
	} while (dChoice < 0 || dChoice > dArSize - 1);	// do-while is used to get the right input from user. 
												// will loop if the input is invalid.
		
	
	*cBuffer = 0;			// resetting values used in arrowkeys input to be used in other functions
	*dCurSel = 0;
	return dChoice;
}



/*	This function returns a random number with a lower and upper bound range

	Precondition: the parameters are all integers

	@param dLowerBound is the lower bound range of random number to be generated
	@param dUpperBound is the upper bound range of random number to be generated

	@return the random number generated within the range
*/
int randomNum(int dLowerBound, int dUpperBound)
{
	int rNum = 0;

	//srand(time(NULL)); this should only be called once

	rNum = rand() % (dUpperBound - dLowerBound + 1) + dLowerBound;	// rand() generated a number while % reduces that number to a 
																	// desired range. 
	return rNum;
}


/*	This function returns a random price of a product, depending on the city and its discounts. 
	Each day, the city would change its products' prices

	Precondition: the parameters are integers

	@param dCity would tell this function which city the user is currently in. Each city has a special discount price 
	in specific products
	@param ProductNumber would tell this function what product the caller is pertaining to, so it would know what price range
	to return

	@return the random price within a range, dpending on the city and current ProductNumber
*/
int getPrice(int dCity, int ProductNumber)
{
	int dFinalPrice = 0;		// the variavle to be returned
	int dCurLowerPrice = -1;	// this variable is the one to be inputted in the randomNum() function. This is the lower bound range
	int dCurHigherPrice = -1;	// this variable is the one to be inputted in the randomNum() function. This is the higher bound range
	
	int discountCase = 0;		// this variavle would tell the function if it should return the discounted price. initialized to no

	switch (dCity)
	{
		// the city has a corresponding number to it. winterfell is 0 ... Volantis is 5
		// the product has a corresponding number to is. Sweet Beet is 0 ... Valyrian Steel is 7
		// please read the Machine Project Specifications to know more
		case 0:
			if (ProductNumber == 1)		// if city is 0 (Winterfel) and Product is 1 (Timber), then the price is discounted 
				discountCase = 1;
			break;
		case 1:
			if (ProductNumber == 3)
				discountCase = 1;
			break;
		case 2:
			if (ProductNumber == 2 || ProductNumber == 5)
				discountCase = 1;
			break;
		case 3:
			if (ProductNumber == 4)
				discountCase = 1;
			break;
		case 4:
			if (ProductNumber == 6 || ProductNumber == 7)
				discountCase = 1;
			break;
		case 5:
			if (ProductNumber == 0)
				discountCase = 1;
			break;
	}

	if (discountCase == 1)
	{
		dCurLowerPrice = DISCOUNT_PRICE_L + ProductNumber * MULTIPLYER;
		dCurHigherPrice = DISCOUNT_PRICE_H + ProductNumber * MULTIPLYER;
	}
	else
	{
		dCurLowerPrice = BASE_PRICE_L + ProductNumber * MULTIPLYER;
		dCurHigherPrice = BASE_PRICE_H + ProductNumber * MULTIPLYER;
	}

	dFinalPrice = randomNum(dCurLowerPrice, dCurHigherPrice);	// passing the lower bound and higher bound number to be randomly
																// generated
	return dFinalPrice;
}


/*	This function performs a repetitive task of displaying the products, their prices, and the user's current inventory

	Precondition: the parameters are valid

	@param dCity tells which city the user is currently in
	@param *newCity tells this function if the user has used the wheelborrow to enter new city. important for generating prices
	@param *sName[] is an array of the name of each city
	@param *sProducts[] an array of strings of the name of each product
	@param *ProductNum will come from the function displayCity. This is the counter for displaying products in loops
	@param dProductPrices[] an array of price information for each product
	@param dDays the parameters below are just information the function uses to display the user's remaining
			days, gold, saving, debt, and capacity
	@param dGold
	@param dSavings
	@param dDebt
	@param dCapacity
	@param dCapacity_Max
	@param dInventory[] is an array of integers, where the information of the amount of each product that the user has bought

	@return void
*/
void displayDashBoard(int dCity, int* newCity, char* sName[], char *sProducts[], int* ProductNum, int dProductPrices[],
						int dDays, float dGold, float dDebt, float dSavings, int dCapacity, int dCapacity_Max, int dInventory[])
{
	system("cls");		// clear screen before displaying the dashboard
	printf("-----------------------------------------------------------------------------------\n");
	printf("                                   %s                                              \n", sName[dCity]);	// prints current city
	printf("-----------------------------------------------------------------------------------\n");
	printf("  ITEM\t\tWARES AND GOODS\t\t\tSELLING/BUYING PRICE\tINVENTORY\n");	// prints 
	printf("-----------------------------------------------------------------------------------\n");

	for (*ProductNum = 0; *ProductNum < SPRODUCT_SIZE; (*ProductNum)++)		// prints the main dashboard, top to bottom, 
	{																	// left to right
		if (*newCity == 1)
			dProductPrices[*ProductNum] = getPrice(dCity, *ProductNum);	// only generates new price if the user change city
																		// if not, keep old prices

		printf("   %d\t\t%s\t", *ProductNum + 1, sProducts[*ProductNum]);

		if (*ProductNum == 1)							// this part is for alignment fixing
			printf("\t\t\t");
		else if (*ProductNum == 3 || *ProductNum == 6)
			printf("\t");
		else
			printf("\t\t");

		printf("     %d", dProductPrices[*ProductNum]);	// prints the price of each

		printf("\t\t");
		printf("   %d\n", dInventory[*ProductNum]);
	}

	*newCity = 0;	// tells the program that the user has already landed into the city. important for prices

	printf("-----------------------------------------------------------------------------------\n");

	// this part just displays the user's status
	printf("\n");
	printf("Days Remaining:\t\t%d\n", dDays);
	printf("GD:\t\t\t%.2f\n", dGold);
	printf("Debt:\t\t\t%.2f\n", dDebt);
	printf("Savings:\t\t%.2f\n", dSavings);
	printf("Capacity:\t\t%d / %d\n", dCapacity, dCapacity_Max);
	printf("\n");
}


/*	This function displays the dashboard for the trading platform. It handles the scenario where the player chooses to 
	play with arrow keys, or just typing out numbers

	Precondition: All parameters are valid

	@param dCity tells which city the user is currently in
	@param *newCity tells this function if the user has used the wheelborrow to enter new city. important for generating prices
	@param *sProducts[] an array of strings of the name of each product
	@param dProductPrices[] an array of price information for each product
	@param dInventory[] is an array of integers, where the information of the amount of each product that the user has bought
	@param *OptAct tells this function what operation is the user trying to do (Buy, Sell, or neither)
	@param *sName[] is an array of the name of each city
	@param *dInMethod tells this function what kind of input control method the user chooses
	@param dDays the parameters below are just information the function uses to display the user's remaining
			days, gold, saving, debt, and capacity
	@param dGold
	@param dSavings
	@param dDebt
	@param dCapacity
	@param dCapacity_Max
	@param *cBuffer is used to hold the 0xE0 in the arrow key function. When _getch() is used, and arrow keys are enterd, 
			it outputs 2 characters. The first is 0xE0, then the second is the character for the specific arrow key.
	@param *dCurSel is refreshed everytime the user presses enter when *intMethod == 1. This value is whatever the current
			value the cursor is on.
	@param *sArrowOpt_Std[] is an array containing the list of strings to be displayed as options
	@param *sArrowOpt_Std[] is an array containing the list of strings to be displayed as options if the operation is buy or sell

	@return this function returns what action the user wants. it can only return the value of possible product numbers (0-7)
			or W, I, C, or Q.
*/
int displayCity(int dCity, int *newCity, char* sProducts[], int dProductPrices[], int dInventory[], int *OptAct, char* sName[], 
					int* dInMethod, int dDays, float dGold, float dSavings, float dDebt, int dCapacity, int dCapacity_Max, 
					int *cBuffer, int *dCurSel, char* sArrowOpt_Std[], char* sArrowOpt_BS[])
{
	int Action = 0;			// this is the variable to be returned

	int ProductNum = 0;		// initializes ProductNumber. This is the variable to be used in for loops
	int OptionNum = 0;		// initializes OptionNum. This is the variable used in for loops in Arrow Keys 
							// when in buy or sell mode

	do	// output guard. will loop if input is invalid from user
	{
		if (*dInMethod == 0)	// if the input control method is with number or char
		{
			displayDashBoard(dCity, newCity, sName, sProducts, &ProductNum, dProductPrices, dDays, dGold, dDebt, 
								dSavings, dCapacity, dCapacity_Max, dInventory);
			
			if (*OptAct == 0 || *OptAct == 1)	// if in buy or sell operation, display other specific menus.
			{
				printf("[B]uy\t[S]ell\t[X]Cancel\n");
				printf("You may enter the product number or B, S, or X for their corresponding function\n\n");
				if (*OptAct == 0)
					printf("Sell: ");
				else if (*OptAct == 1)
					printf("Buy: ");
			}
			else // if not, display these specific things
			{
				printf("[B]uy\t[S]ell\t[W]heel House\t[I]ron Bank\t[C]ontrol\t[Q]uit\n");
				printf("Choice: ");

			}

			if (scanf("%d", &Action) == 0)	// input guard. scanf does not work if "%d" is used and character was inputted
				scanf("%c", &Action);		// the user can input numbers and characters. although if the user has input 81
											// this is also the ascii equivalent of Q, so it will quit the program.

			if ((Action >= 1 && Action <= SPRODUCT_SIZE)) // steps the Action variable down if the input method is by
				Action--;									// numbers and characters, since the program counts starting from 0
				
		} 


		else if (*dInMethod == 1)	// if input method is by arrow keys
		{
			if (*OptAct == -1)	// if not in sell or buy mode
			{
				while (*cBuffer != '\r')
				{
					displayDashBoard(dCity, newCity, sName, sProducts, &ProductNum, dProductPrices, dDays, dGold, dDebt,
						dSavings, dCapacity, dCapacity_Max, dInventory);

					printf("Press left or right arrow keys or enter to navigate\n\n");

					for (OptionNum = 0; OptionNum < SARROWOPT_STD_SIZE; OptionNum++) // print every menu choice (buy, sell, Wheelborrow, iron bank, control, quit)
					{
						if (*dCurSel == OptionNum)	// // display ">> " if cursor is in that choice
							printf(">> ");
						else
							printf("   ");

						printf("%s\t", sArrowOpt_Std[OptionNum]);
					}

					printf("\n");

					// getting input from arrow keys
					*cBuffer = _getch();	// input. 
											// if the user presses enter key, the cBuffer value, which is '\r' will be used to 
											// stop the while loop. it will skip the if statments below

					if (*cBuffer == 0xE0)	// when control or arrow keys are pressed, _getch() returns 0xE0 and the value of the 
					{						// correesponding keys. cBuffer acts as the catcher of the 0xE0, so that the true value
						switch (_getch())	// can be caught
						{
						// dCurlSel is a cursor for the array sName, the cursor points and returns the element position
						case 'K':		// left arrow key
							if ((*dCurSel) > 0)	// makes sure the cursor in within the range of the options
								(*dCurSel)--;	// dCurSel is always updated when keys are pressed
							break;
						case 'M':		// right arrow key
							if ((*dCurSel) < SARROWOPT_STD_SIZE - 1)
								(*dCurSel)++;
							break;
						}
					}
				}

				switch (*dCurSel)		// [B]uy is the first in array in sArrowOpt_Std[], Sell is second, and so on..
				{
					// if the user selected these following
					case 0:
						Action = 'B';	// buy
						break;
					case 1:
						Action = 'S';	// sell
						break;
					case 2:
						Action = 'W';	// wheel borrow
						break;
					case 3:
						Action = 'I';	// iron bank
						break;
					case 4:
						Action = 'C';	// control
						break;
					case 5:
						Action = 'Q';	// quit
						break;
				}

				*dCurSel = 0;		// resetting cursur position to the first choice (int not in buy or sell mode)
			}
			
			else if (*OptAct == 0 || *OptAct == 1)	// buy and sell mode
			{
				while (*cBuffer != '\r')
				{
					system("cls");		// clear screen before displaying the dashboard
					printf("-----------------------------------------------------------------------------------\n");
					printf("                                   %s                                              \n", sName[dCity]);	// prints current city
					printf("-----------------------------------------------------------------------------------\n");
					printf("  ITEM\t\tWARES AND GOODS\t\t\tSELLING/BUYING PRICE\tINVENTORY\n");	// prints 
					printf("-----------------------------------------------------------------------------------\n");

					for (ProductNum = 0; ProductNum < SPRODUCT_SIZE; ProductNum++)
					{
						if (*newCity == 1)
							dProductPrices[ProductNum] = getPrice(dCity, ProductNum);

						if (*dCurSel == ProductNum)	// in the buy and cell operatiojn for arrow keys, you can put the cursor on the products them selves to buy or sell them.
							printf(">> ");
						else
							printf("   ");
						printf("%d\t\t", ProductNum + 1);
						printf("%s\t", sProducts[ProductNum]);
						if (ProductNum == 1)
							printf("\t\t\t");
						else if (ProductNum == 3 || ProductNum == 6)
							printf("\t");
						else
							printf("\t\t");
						printf("     %d", dProductPrices[ProductNum]);	// prints the price of each

						printf("\t\t");
						printf("   %d\n", dInventory[ProductNum]);
					}

					*newCity = 0;

					printf("-----------------------------------------------------------------------------------\n");

					printf("\n");
					printf("Days Remaining:\t\t%d\n", dDays);
					printf("GD:\t\t\t%.2f\n", dGold);
					printf("Debt:\t\t\t%.2f\n", dDebt);
					printf("Savings:\t\t%.2f\n", dSavings);
					printf("Capacity:\t\t%d / %d\n", dCapacity, dCapacity_Max);
					printf("\n");

					printf("Press the up or down arrow keys or enter to navigate\n\n");


					// in the buy and sell operation on arrow keys mode, the ProductNum counter is used on both listing the products
					// and printg the other menu options for this opeartion. that is why there is no ProductNum = 0 in the for loop
					// basically, the array of sProducts[] and sArrowOpt_BS[] is linked together so that the cursor may cross/transition
					// from the array of sProducts to the sArrowOpt_BS
					for (; ProductNum < SPRODUCT_SIZE + SARROWOPT_BS_SIZE; ProductNum++)
					{
						if (*dCurSel == ProductNum)	// same logic below applies when printing out the cursor display. if the 
						{							// cursor is in the current line to be printed (ProductNum), print ">> " 
							printf(">> ");
						}
						else
						{
							printf("   ");
						}

						if ((*OptAct == 0 && ProductNum == SPRODUCT_SIZE + 1) ||
							(*OptAct == 1 && ProductNum == SPRODUCT_SIZE))
						{
							printf("Mode: ");
						}
						else
							printf("      ");

						printf("%s\n", sArrowOpt_BS[ProductNum - SPRODUCT_SIZE]);	// contents of this array is buy, sell, cancel.
					}

					*cBuffer = _getch();	// input. 
										// if the user presses enter key, the cBuffer value, which is '\r' will be used to 
										// stop the while loop. it will skip the if statments below

					if (*cBuffer == 0xE0)	// when control or arrow keys are pressed, _getch() returns 0xE0 and the value of the 
					{						// correesponding keys. cBuffer acts as the catcher of the 0xE0, so that the true value
						switch (_getch())	// can be caught
						{
							/*	this will be 0-7 since dCurSel starts with 0, so does an array count. (sName).
							basically dCurlSel is a cursor for the array sName, the cursor points and returns the element position*/
						case 'H':		// up arrow jey
							if ((*dCurSel) > 0)	// makes sure the cursor in within the range of the options
								(*dCurSel)--;	// dCurSel is always updated when keys are pressed
							break;
						case 'P':		// down arrow key
							if ((*dCurSel) < SPRODUCT_SIZE + (SARROWOPT_BS_SIZE - 1))
								(*dCurSel)++;
							break;
						}
					}
				}

				switch (*dCurSel)
				{
					// since the sProducts and sArrowOpt_BS is linked together, the first element of the sArrowOpt_BS is in the SPRODUCT_SIZE'th element
					case SPRODUCT_SIZE:
						Action = 'B';
						break;
					case SPRODUCT_SIZE + 1:
						Action = 'S';
						break;
					case SPRODUCT_SIZE + 2:
						Action = 'X';
						break;
					default:
						Action = *dCurSel;
				}
			}
		}


		// if the user decides to input the letters b, s, or x, it will change the operation of this dashboard (*OptAct)
		if (Action == 'B' || Action == 'b')
			*OptAct = 1;
		else if (Action == 'S' || Action == 's')
			*OptAct = 0;
		else if (Action == 'X' || Action == 'x')
			*OptAct = -1;
		
		if (*OptAct == -1)
			*dCurSel = 0;		// resetting cursor position to the first choice if not in buy or sell mode
		*cBuffer = 0;			// resetting values used in arrowkeys input to be used in other functions

	} while (((*OptAct == 1 || *OptAct == 0) && (Action < 0 || Action > SPRODUCT_SIZE - 1)) ||
		(*OptAct == -1 && (Action != 'W' && Action != 'w' && Action != 'I' && Action != 'i' && Action != 'C' && 
			Action != 'c' && Action != 'Q' && Action != 'q')));

	return Action;
}



/*	This function accepts the product number and the operation the user wants to do. It calculates if the user can buy a product
	 basedon their current gold (GD), inventory, and capacity.

	Precondition: the file is existing and has a file type of .txt

	@param filename is the directory for the text file ascii text

	@return void
*/
void opBuySell(int *dAction, int *OptAct, int dProductPrices[], int dInventory[], float *dGold, int *dCapacity, int *dCapacity_Max)
{
	if (*OptAct == 0)
	{
		if (dInventory[*dAction] > 0)			// selling. if the user has greater than 0 of a specific product(dAction), they are able to sell
		{
			(dInventory[*dAction])--;			// subtracts the number of item of a specific product the user has.
			*dGold += dProductPrices[*dAction];	// adds user's gold based on product price
			(*dCapacity)--;						// free more room for capacity
		}
	}

	else if (*OptAct == 1)
	{
		if (*dGold >= dProductPrices[*dAction] && *dCapacity < *dCapacity_Max)	// able to buy if gold is higher or equal to
		{																		// product price and there is capacity
			(dInventory[*dAction])++;			// adds the number of item of a specific product the user has.
			*dGold -= dProductPrices[*dAction];	// subtracts user's gold based of product price
			(*dCapacity)++;						// takes room for capacity
		}
	}

	return;
}


/*	This function displays a repetitive task to print out text used in IronBank()

	Precondition: all parameters are appropriate

	@param *dGold The parameters listed below are the information about the player's resources.
	@param *dDebt
	@param *dSavings

	@return void
*/
void displayBankDetails(float* dGold, float* dDebt, float* dSavings)
{
	system("cls");
	printf("Welcome to the Iron Bank of Braavos\n");
	printf("The most powerful bank in The Known World!\n\n");

	printf("In this bank we can offer a 10%% interest on Savings\n");
	printf("And a 5%% interest on loans. Both compounded daily.\n\n");

	printf("Your details are as follows\n");
	printf("GD:\t\t%.2f\n", *dGold);
	printf("Debt:\t\t%.2f\n", *dDebt);
	printf("Savings:\t%.2f\n", *dSavings);
	printf("\n\n");
	printf("What can we do to serve you?\n");
}


/*	This function always returns a positive float number. If given a negative number, it will change its sign to positive. 
	If positive, it will return the same number

	Precondition: the input is a number

	@param num is a positive or negative real

	@return num
*/
float absVal(float num)
{
	if (num < 0)
		num *= -1;
	return num;
}

/*	This function is used when the user decides to go to the Iron Bank

	Precondition: all parameters are appropriate and the input that the user gives are appropriate for the data types used

	@param *dGold The parameters listed below are the information about the player's resources.
	@param *dDebt
	@param *dSavings
	@param *dInMethod is the variable to know what input type the user wants
	@param *sBankOpt_Arrow[] is an array of strings that lists the options available for Iron Bank when in arrow key mode
	@param *sBankOpt_Std[] is an array of strings that lists the options available for Iron Bank when in standard input mode
	@param *dCurSel The parameters listed below are the varaible used for arrow key controls.
	@param *cBuffer

	@return void this function only processes the data that the user already has.
*/
void IronBank(float *dGold, float *dDebt, float *dSavings, int *dInMethod, char* sBankOpt_Arrow[], char *sBankOpt_Std[],
				int *dCurSel, int *cBuffer)
{
	int dChoice = 0;		// variable that will be used to know what kind of operation the user wants (when in standard mode)

	int Operation = -1;		// variable used to know what type of operation the user wants to do
							// -1 is no operation, 0 is deposit, 1 is withdraw, 2 is get a loan, 3 is pay back a debt
	float dAmount = 0;		// this function uses this variable to get amount of money the user inputs

	int counter = 0;		// counter used for for loops

	*cBuffer = 0;			// cleans cBuffer. In this function, this variable is used to handle Inavlid inputs and 
							// for arrow key fucntion

	
	// Introductory Image of the Iron Bank
	system("cls");
	displayArt("AsciiArt/IronBank.txt");
	printf("\nPress ENTER key to continue...");

	// the while loop "flushes" the input buffer since the character '\n' or any keyboard inputmay not be processed and 
	// be carried on to the next scanf calls and may cause unexpected results.
	getchar();
	while (((*cBuffer) = getchar()) != '\n' && (*cBuffer) != EOF) {}
		/* discard */;

	do	// this function will only end if the user cants to go back to the main dash board, which is enetering x as input
	{	// on the menu screen
		
		// getting input in menu screen
		if (*dInMethod == 0)	// standard input
		{
			if (Operation == -1)	// in the user is currently in the menu operation
			{
				displayBankDetails(dGold, dDebt, dSavings);

				for (counter = 0; counter < SBANKOPT_SIZE; counter++)
				{
					printf(" %s\t", sBankOpt_Std[counter]);
				}
				
				printf("\n\n");
				printf("Choice: ");
				if (scanf("%c", &dChoice) == 0)		// input guard. only accepts characters
					while (((*cBuffer) = getchar()) != '\n' && (*cBuffer) != EOF) {}
					/*while (((*cBuffer) = getchar()) != EOF) {}*/
						/* discard */;
				
				switch (dChoice)	// dissecting the input. if the input is not d, w, g, p, c, or x, it will only loops
				{
					// based on the sBankOpt arrays, the 0'th element is deposit... the 4'th element is pay debts
					// the operation variable relfects this.
					case 'D':
					case 'd':
						Operation = 0;
						break;
					case 'W':
					case 'w':
						Operation = 1;
						break;
					case 'G':
					case 'g':
						Operation = 2;
						break;
					case 'P':
					case 'p':
						Operation = 3;
						break;
					case 'C':
					case 'c':
						*dInMethod = !(*dInMethod);
						break;
				}
			}
		}
		else if (*dInMethod == 1)	// arrow keys function
		{
			if (Operation == -1)	// if the user is in the menu operation
			{
				*dCurSel = 0;		// cleans the variable to be used on arrow keys
				*cBuffer = 0;

				do	// loop will only end if the user pressed the enter key
				{
					displayBankDetails(dGold, dDebt, dSavings);

					for (counter = 0; counter < SBANKOPT_SIZE; counter++)	// display the menu options and cursor
					{
						if (*dCurSel == counter)
							printf(">> ");
						else
							printf("   ");

						printf("%s\t", sBankOpt_Arrow[counter]);
					}

					// getting input from arrow keys
					*cBuffer = _getch();	// input. 
											// if the user presses enter key, the cBuffer value, which is '\r' will be used to 
											// stop the while loop. it will skip the if statments below

					if (*cBuffer == 0xE0)	// when control or arrow keys are pressed, _getch() returns 0xE0 and the value of the 
					{						// correesponding keys. cBuffer acts as the catcher of the 0xE0, so that the true value
						switch (_getch())	// can be caught
						{
							// dCurlSel is a cursor for the array sName, the cursor points and returns the element position
						case 'K':		// left arrow key
							if ((*dCurSel) > 0)	// makes sure the cursor in within the range of the options
								(*dCurSel)--;	// dCurSel is always updated when keys are pressed
							break;
						case 'M':		// right arrow key
							if ((*dCurSel) < SBANKOPT_SIZE - 1)
								(*dCurSel)++;
							break;
						}
					}
				} while (*cBuffer != '\r');

				switch (*dCurSel)
				{
					case 4:		// if user decides to change control
						*dInMethod = !(*dInMethod);
						break;
					case 5:		// pr entered in cancel
						dChoice = 'x';
						break;
					default:	// else, wherever the dchoice lands, since it's 0 based, it willl mirror the desired operation.
						Operation = *dCurSel;
						break;
				}

				*dCurSel = 0;	// cleaning variables used in arrow keys after used
				*cBuffer = 0;
			}
		}

		// if the user decides to go into operations except the menu operation (-1), this will trigger. This is the part
		// where input fir dAmount is asked
		if (Operation != -1)
		{
			dAmount = 0;	// cleans the amount so that when this function loops, it is sure that the variable is clean.

			displayBankDetails(dGold, dDebt, dSavings);

			printf("%s Mode\n", sBankOpt_Arrow[Operation]);
			printf("Enter your desired amount or type a negative number if you want to go back to the menu.\n");
			printf("Amount: ");
			if (scanf("%f", &dAmount) == 0)
				scanf("%c", cBuffer);

			if (dAmount >= 0)
			{
				switch (Operation)
				{
					// what type of operation does the user want? based on the input code abover
					case 0:	// deposit
						if (dAmount < *dGold || absVal(dAmount - *dGold) < 0.00000000001) // this is the opeartion for comparing floats
						{
							(*dSavings) += dAmount;
							(*dGold) -= dAmount;
						}
						break;
					case 1:	// withdraw
						if (dAmount < *dSavings || absVal(dAmount - *dSavings) < 0.00000000001) // less than or equal to.
						{
							(*dGold) += dAmount;
							(*dSavings) -= dAmount;
						}
						break;
					case 2:	// get a loan
						(*dGold) += dAmount;
						(*dDebt) += dAmount;
						break;
					case 3:	// pay a debt
						if ((dAmount < *dGold || absVal(dAmount - *dGold) < 0.00000000001)&& 
							(dAmount < *dDebt || absVal(dAmount - *dDebt) < 0.00000000001))	// checks if the user has debt
						{
							(*dGold) -= dAmount;
							(*dDebt) -= dAmount;
						}
						break;
				}
			}
			else
			{
				// if the user enters a negative number, go back to the menu
				Operation = -1;
			}
		}
	} while (dChoice != 'X' && dChoice != 'x');

}


/*	This function handles section when the user decies to go to the the wheelhouse. It handles the input and translates it into numbers
	Remember, cities have corresponsding numbers. This returns what city(number) the player chooses, or if he want to cancel
	sName[] array is still used, instead of "Quit" as its last element, it is replaced with "Cancel"
	This part of the code is very similar to start() function.

	Precondition: the input would only be numbers, arrowkey strokes, and enter key. letters would make scanf return an error
					and will make the program loop endlessly.

	@param *sName[] is a poitner to a string located in main.c. This is the list of cities.
	@param dArSize is the  number of elements in *sName[]. This is important for the for loop.
	@param *dInMethod is either 0 or 1 only. 0 means the player is using numbers as input. 1 means the input is arrow keys and enter.
			The other pointer parameters are pointers so variables would not be initialized in every function call.
	@param *dCurSel is refreshed everytime the user presses enter when *intMethod == 1. This value is whatever the current
			value the cursor is on.
	@param *cBuffer is used to hold the 0xE0 in the arrow key function. When _getch() is used, and arrow keys are enterd,
			it outputs 2 characters. The first is 0xE0, then the second is the character for the specific arrow key.

	@return The choice that the user selected. Count starts with 0, to synchronize with the sName[] array.
*/
int WheelHouseChoice(char* sName[], int dArSize, int* dInMethod, int* dCurSel, int* cBuffer)
{
	int dChoice = 0;	// variable that will be returned
	int i = 0;			// variable used for for loops

	do	// do-while is used to get the right input from user. will loop if the input is invalid.
	{
		if (*dInMethod == 0)	// numbers as input
		{
			system("cls");		// clears the screen every time it loops
			// displayArt("C:\\Users\\Francis\\OneDrive\\Documents\\DLSU\\CCPROG\\Machine Project\\CCPROG1-MP-S17B-De Leon\\AsciiArt\\StartArt.txt");
			displayArt("AsciiArt\\CityLeave.txt");

			printf("\nReady to leave? Where would you want to go?");
			printf("\nTravelling takes 1 day.\n\n");

			for (i = 0; i < dArSize; i++)
			{
				if (i == SNAME_SIZE - SNAME_OPT)		// design prupose. a new line will be created after the cities
				{
					printf("\n");
				}

				if (i != SNAME_SIZE - 1)
					printf("[%d] %s\n", i + 1, sName[i]);	// print each element contents of the array sName[]
				else
					printf("[%d] Cancel\n", i + 1);			// instead of printinf quit, just print cancel
			}
			printf("\nChoice: ");			// input after displaying the whole main menu. this will be 1-8
			if (scanf("%d", &dChoice) == 0)	// input guard
				scanf("%c", &dChoice);

			dChoice--;		// if the input method is numbered, this line is used to synchronize the array with the
							// inputed value, since user enters starts counting at 1. So that whenever the user decides to use
							// the arrow keys, they both return the same value.
		}

		else if (*dInMethod == 1)		// arrow keys as input
		{
			while ((*cBuffer) != '\r')	// cBuffer is used to check if the user has pressed the enter key. 
			{							// Loop will end after that.

				system("cls");		// clears the screen every time it loops
				
				displayArt("AsciiArt\\CityLeave.txt");

				printf("\nReady to leave? Where would you want to go?");
				printf("\nTravelling takes 1 day.\n\n");

				for (i = 0; i < dArSize; i++)
				{
					if (i == SNAME_SIZE - SNAME_OPT)
					{
						printf("\n");
					}

					if (*dCurSel == i)	// dCurlSel is the value where the cursor is on. If the cursor is in i, print sNum[i] with
						printf(">> ");	// a >>, else print it with just a space "   "
					else
						printf("   ");

					if (i != SNAME_SIZE - 1)
						printf("%s\n", sName[i]);
					else
						printf("Cancel\n");
				}

				*cBuffer = _getch();	// input. 
										// if the user presses enter key, the cBuffer value, which is '\r' will be used to 
										// stop the while loop. it will skip the if statments below

				if (*cBuffer == 0xE0)	// when control or arrow keys are pressed, _getch() returns 0xE0 and the value of the 
				{						// correesponding keys. cBuffer acts as the catcher of the 0xE0, so that the true value
					switch (_getch())	// can be caught
					{
						/*	this will be 0-7 since dCurSel starts with 0, so does an array count. (sName).
						basically dCurlSel is a cursor for the array sName, the cursor points and returns the element position*/
					case 'H':		// up arrow jey
						if ((*dCurSel) > 0)	// makes sure the cursor in within the range of the options
							(*dCurSel)--;	// dCurSel is always updated when keys are pressed
						break;
					case 'P':		// down arrow key
						if ((*dCurSel) < dArSize - 1)
							(*dCurSel)++;
						break;
					}
				}
			}

			//	this executes when the user has finally pressed enter or '\r'
			// assigns the dCurSel to the dChoice for return
			dChoice = *dCurSel;
		}
	} while (dChoice < 0 || dChoice > dArSize - 1);	// do-while is used to get the right input from user. 
												// will loop if the input is invalid.


	*cBuffer = 0;			// resetting values used in arrowkeys input to be used in other functions
	*dCurSel = 0;
	return dChoice;
}


/*	This function proccesses the necessary variables to be changed when the user goes to another city, and travels within a day.

	Precondition: all parameter inputs are correct

	@param dCityTemp is what WheelHouseChoice() returned. It is put in a temporary variable since the user might input incorrect inputs.
	@param *dCity is the variable to be changed when the user decides to go to another city. It represents what city the player is currently in based on numbers
	@param *newCity tells the program if the user has entered a new city.
	@param *dDay is the variable containing how mabny days left the user has,
	@param *dSavings will be compunded daily to 10%
	@param *dDebt will be compunded daily to 5%

	@return void
*/
void newCityDay(int dCityTemp, int* dCity, int* newCity, int* dDay, float* dSavings, float* dDebt)
{
	*dCity = dCityTemp;
	*newCity = 1;
	(*dDay)--;

	*dSavings += ((*dSavings) * 0.1);
	*dDebt += ((*dDebt) * .05);
}


/*	This function executes if a player decides to go to another city. It has a 10% chance of executing the whole implementation.
	using the rand() function. if it does execute, it will ask the user if they want to increase their capacity by 50 for 200GD

	Precondition: all parameters inputs are correct

	@param *dCapacity_Max is a pointer to the max capacity variable in main
	@param *dGold is a pointer to the player's gold variable in main
	@param *dInMethod is a pointer to the player's current control mode
	@param *dCurSel the 2 variables that are used for the arrow keys implementation
	@param *cBuffer

	@return void
*/
void capMerchent(int* dCapacity_Max, float *dGold, int* dInMethod, int *dCurSel, int *cBuffer)
{
	int dEncounter;		// variable used to know how often of what are the chances the player will get to meet this merchant

	char cAnswer;		// answer of the player. this will still be converted to a Final answer since input can be 0 or 1 (coming from arrowkeys)
						// or Y or N coming from the normal input
	int dFinalAns = -1;	// -1 since 0 and 1 are used for no and yes, respectively.

	int dErrorCatch = 0;// used for input gurad

	int counter = 0;	// for loops
	
	dEncounter = rand() % 10;	// generates a random number with a range of 0-9
	if (dEncounter == 0)		// if the generated number is a chosen element, out of the 10, it has a 10% chance this will become true
	{
		do {
			// display merchant and text
			system("cls");
			displayArt("AsciiArt/Merchant.txt");

			printf("\nHello Traveler! May I offer my extra capacity to you?\n");
			printf("You can increase your max capacity by 50 for only 200GD\n");
			printf("\n");

			// input method
			if (*dInMethod == 0)
			{
				printf("[Y]es \t [N]o\n");
				printf("Choice: ");

				while (((dErrorCatch) = getchar()) != '\n' && dErrorCatch != EOF) {}	// flushing input buffer
				scanf("%c", &cAnswer);

				switch (cAnswer)
				{
					// in dFinalAns, 0 is no, 1 is yes
					case 'Y':
					case 'y':
						dFinalAns = 1;
						break;
					case 'N':
					case 'n':
						dFinalAns = 0;
						break;
				}
			}

			else if (*dInMethod == 1)
			{
				*dCurSel = 0;	// resetting curor position

				do
				{
					system("cls");
					displayArt("AsciiArt/Merchant.txt");

					printf("\nHello Traveler! May I offer my extra capacity to you?\n");
					printf("You can increase your max capacity by 50 for only 200GD\n");
					printf("\n");
					*cBuffer = 0;	// resetting buffer for arrow input

					for (counter = 0; counter < 2; counter++)
					{
						if (*dCurSel == counter)	// print cursor head to where it is currently pointing
							printf(">> ");
						else
							printf("   ");
						// ------------------------- //
						if (counter == 0)			// Array was not needed to print these strings
							printf("Yes \t");
						else
							printf(" No");
					}

					// getting input from arrow keys
					*cBuffer = _getch();	// input. 
											// if the user presses enter key, the cBuffer value, which is '\r' will be used to 
											// stop the while loop. it will skip the if statments below

					if (*cBuffer == 0xE0)	// when control or arrow keys are pressed, _getch() returns 0xE0 and the value of the 
					{						// correesponding keys. cBuffer acts as the catcher of the 0xE0, so that the true value
						switch (_getch())	// can be caught
						{
							// dCurlSel is a cursor for the array sName, the cursor points and returns the element position
						case 'K':		// left arrow key
							if ((*dCurSel) > 0)	// makes sure the cursor in within the range of the options
								(*dCurSel)--;	// dCurSel is always updated when keys are pressed
							break;
						case 'M':		// right arrow key
							if ((*dCurSel) < 1)
								(*dCurSel)++;
							break;
						}
					}

				} while (*cBuffer != '\r');

				*cBuffer = 0;	// resets the buffer after being used

				switch (*dCurSel)
				{
					case 0:	// when the cursor is in the 0 position, it is poitning to yes
						dFinalAns = 1;
						break;
					case 1:	// poitning to no
						dFinalAns = 0;
						break;
				}
			}

		} while (dFinalAns != 0 && dFinalAns != 1);

		if (dFinalAns == 1)
		{
			system("cls");
			displayArt("AsciiArt/Merchant.txt");

			if (*dGold > 200 || absVal((*dGold) - 200) < 0.00000000001)	// if the player's gold is greater than or equal to the price
			{
				(*dGold) -= 200;		// subtract 200 to the player's gold
				(*dCapacity_Max) += 50;	// add 50 to the maxmum capacity

				printf("\nThank you great traveler! Lets us meet again sometime to do business.\n");
			}
			else
			{
				printf("\nI'm sorry but you seem to have insufficent gold. Let us try to do business again in the future!\n");
			}


			printf("\nPress ENTER key to continue...");

			// the while loop "flushes" the input buffer since the character '\n' or any keyboard inputmay not be processed and 
			// be carried on to the next scanf calls and may cause unexpected results.
			getchar();
			while (((dErrorCatch) = getchar()) != '\n' && dErrorCatch != EOF) {}
			/* discard */;
		}

		
		// no more instructions if the user decides not to buy.
	}

	*cBuffer = 0; // cleaning variables
	*dCurSel = 0;
}