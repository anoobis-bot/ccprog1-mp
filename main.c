/*
	Description: This program is a game where a player can trade items to grow their money (Golden Dragons). 
	Programmed by: De Leon, Francis Zaccharie B. S17B
	Last modified: 1/29/22
	[Acknowledgements:]
		- The library conio.h was used for the arrow key function implementation
		- Many thanks to Michael Hadley for the tutorial for arrow key inplementation on C#. 
			https://youtu.be/qAWhGEPMlS8
		- Felipemaia for clearing the order of operation for incrementing on pointers. 
			https://stackoverflow.com/questions/8208021/how-to-increment-a-pointer-address-and-pointers-value
		- Matticus for his algorithm for printing ascii art from text files.
			https://cboard.cprogramming.com/cplusplus-programming/161868-how-use-ascii-art-c-cplusplus.html
		- Other stackoverflow forums for helping me setup the arrow key function
			https://stackoverflow.com/questions/473661/why-doesnt-pressing-enter-return-n-to-getch
			https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c/1095006
		- jamesdlin for teaching how to flush input buffer
			https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
*/


#include "header.h"


int main(void)
{
	// lists used in game
	char *sName[] = {"Winterfell", "Lys", "Myr", "Pentos", "Qohor", "Volantis", "Controls", "Quit"};	// cities
	char *sProducts[] = {"Sweet Beet", "Timber", "Intricate Lace", "Intoxicating Perfume", "Pale Amber Wine", "Myrish Eye",
							"Qohorik Tapestry", "Valyrian Steel" };		// Products
	char *sArrowOpt_Std[] = {"Buy", "Sell", "Wheel House", "Iron Bank", "Control", "Quit"};	// options in menu when arrow keys are used
	char *sArrowOpt_BS[] = { "Buy", "Sell", "Cancel"};	// options in menue when arrow keys are used and in buy or sell mode
	char *sBankOpt_Arrow[] = { "Deposit", "Withdraw", "Get a loan", "Pay-back a debt", "Control", "Cancel"};// options for Iron Bank
	char* sBankOpt_Std[] = { "[D]eposit", "[W]ithdraw", "[G]et a loan", "[P]ay-back a debt", "[C]ontrol", "[X]Cancel" };


	
	int dProductPrices[SPRODUCT_SIZE];	// this array lists the prices of each product. sProducts[i]'s price is dProductPrices[i]
	int dInventory[SPRODUCT_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};	// this array will be used to store how much of each product the user has
	int newCity = 1;	// this is for the product prices. it signals a function if it can change the prices, it only happens when going to a new city.
	
	//	these variables are for player control method
	int dInMethod = 0;	// 0 is number input, 1 is arrow key
	int dCurSel = 0;	// shows current cursor status
	int cBuffer = 0;	// cBuffer for _getch() arrow keys
	
	int dCity = 0;		// varible that states which city the player is currently in. (based from the elements of sName[])
	int dCityTemp = 0;	// will be used for wheelhouse checking
	int dAction = 0;	// variable to what input the user chooses in the game 
	int OptAct = -1;	// variable to know if the user wants to sell(0), buy(1), or neither(-1). applies in displayCity()

	// in-game variables
	int dDay = 15;
	float dGold = 2000;
	float dSavings = 0;
	float dDebt = 0;
	int dCapacity_Max = 50;
	int dCapacity = 0;

	srand(time(NULL));	// sets seed for rand()
	
	int counter = 0;	// for loop at end screen

	// start screen
	do
	{
		dCity = start(sName, SNAME_SIZE, &dInMethod, &dCurSel, &cBuffer);	// getting input city from user

		// changes dInput if the user wants another control method
		if (dCity == 6)
			dInMethod = (!dInMethod);

	} while (dCity == 6);	// will loop and display start menu again if the user chooses different input method (control).
	
	
	// main game
	if (dCity != 7)	// if the player does not choose quit in the start menu
	{
		do
		{
			// dAction will get what product the user picks or what action the user wants.
			// displayCity will also change OptAct if the user wants to buy, sell, or neither.
			dAction = displayCity(dCity, &newCity, sProducts, dProductPrices, dInventory, &OptAct, sName, &dInMethod,
									dDay, dGold, dSavings, dDebt, dCapacity, dCapacity_Max, 
									&cBuffer, &dCurSel, sArrowOpt_Std, sArrowOpt_BS);

			// if the user picks a product (0-7), opBuySell will computer the necessary action for inventory, capacity, gold, etc...
			if (dAction >= 0 && dAction <= 7)
				opBuySell(&dAction, &OptAct, dProductPrices, dInventory, &dGold, &dCapacity, &dCapacity_Max);
			
			// if the user picks control, it will change the control mode.
			else if (dAction == 'C' || dAction == 'c')
				dInMethod = !(dInMethod);

			else if (dAction == 'I' || dAction == 'i')
			{
				IronBank(&dGold, &dDebt, &dSavings, &dInMethod, sBankOpt_Arrow, sBankOpt_Std, &dCurSel, &cBuffer);
			}

			else if (dAction == 'W' || dAction == 'w')
			{
				do	// this loops if the user decided to switch control method
				{
					dCityTemp = WheelHouseChoice(sName, SNAME_SIZE, &dInMethod, &dCurSel, &cBuffer); // assigns what the user inputs
					if (dCityTemp != dCity)	// if the user did not choose the current city that they are currently in
					{
						if (dCityTemp >= 0 && dCityTemp <= 5)	// if the user chose a city (there is control and cancel choice)
						{
							newCityDay(dCityTemp, &dCity, &newCity, &dDay, &dSavings, &dDebt); // process the necessary variables with a new day and city
							capMerchent(&dCapacity_Max, &dGold, &dInMethod, &dCurSel, &cBuffer);
						}
					}

					if (dCityTemp == 6)		// if the user decided to swithc control method, this part of the code will loop
						dInMethod = !dInMethod;
				} while (dCityTemp == 6);
			}

		} while (dDay > 0 && (dAction != 'Q' && dAction != 'q'));	// loops end if the days are over or the user chooses to exit
	}


	// ending screen
	system("cls");
	printf("Thank you for playing the game! This is your game status:\n");
	printf("Days Remaining:\t\t%d\n", dDay);
	printf("GD:\t\t\t%.2f\n", dGold);
	printf("Debt:\t\t\t%.2f\n", dDebt);
	printf("Savings:\t\t%.2f\n", dSavings);
	printf("Capacity:\t\t%d / %d\n\n", dCapacity, dCapacity_Max);

	printf("Inventory: \n");
	for (counter = 0; counter < SPRODUCT_SIZE; counter++)
	{
		printf("%s", sProducts[counter]);

		printf("\t");
		if (counter == 0 || counter == 2 || counter == 4 || counter == 5 || counter == 7)
			printf("\t");
		else if (counter == 1)
			printf("\t\t");

		printf("%d\n", dInventory[counter]);
	}

	printf("\n\nPress ENTER to terminate the program.");
	while (((cBuffer) = getchar()) != '\n' && cBuffer != EOF) {}
	cBuffer = getchar();

	return 0;
}
