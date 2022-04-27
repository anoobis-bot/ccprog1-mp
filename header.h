/*
	This header file is used to connect C files in this directory
*/
#pragma once

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
// used in rand() function
#include <time.h>	


#define SNAME_SIZE 8		// this is the number of elements in the sName[] array
#define SNAME_OPT 2			// this is the number of options in the sName[] array. SNAME_SIZE - SNAME_OPT will give the number of
							// cities that is only present in the array
#define SPRODUCT_SIZE 8		// number of elements in sProducts[]
#define SARROWOPT_STD_SIZE 6
#define SARROWOPT_BS_SIZE 3

#define SBANKOPT_SIZE 6


int start(char *sName[], int dArSize, int *dInMethod, int *dCurSel, int *cBuffer);

int displayCity(int dCity, int* newCity, char* sProducts[], int dProductPrices[], int dInventory[], int* OptAct, char* sName[],
				int* dInMethod, int dDays, float dGold, float dSavings, float dDebt, int dCapacity, int dCapacity_Max,
				int* cBuffer, int* dCurSel, char* sArrowOpt_Std[], char* sArrowOpt_BS[]);

void opBuySell(int* dAction, int* OptAct, int dProductPrices[], int dInventory[], float* dGold, int* dCapacity, int* dCapacity_Max);

void IronBank(float* dGold, float* dDebt, float* dSavings, int* dInMethod, char* sBankOpt_Arrow[], char* sBankOpt_Std[],
				int* dCurSel, int* cBuffer);

int WheelHouseChoice(char* sName[], int dArSize, int* dInMethod, int* dCurSel, int* cBuffer);

void newCityDay(int dCityTemp, int* dCity, int* newCity, int* dDay, float* dSavings, float* dDebt);

void capMerchent(int* dCapacity_Max, float* dGold, int* dInMethod, int* dCurSel, int* cBuffer);