/*
testRoll.c
Samuel West
A simple test program to demonstrate basic functionallity in dice.h
v0.02 - Using command line string parsing
*/
#include <stdio.h>
#include <string.h>
#include "dice.h"

int main(int argc, char *argv[])
{	
	// Assert the command line argument
	if (argc == 1) {
		perror("No argument provided\n");
		return 1;
	}

	/* VARIABLE DECLARATION */
	int		len,			// Length of input string
			i,				// Loop variables
			j,
			dDex,			// Index of character 'd'
			modDex,			// Modifier index
			numDice,		// Number of dice to roll
			type,			// Type of dice to roll
			sign,			// Sign of modifier
			mod,			// Modifier for dice roll
			result;			// Result of dice roll
	char	numDiceBuf[8],	// String form of numDice before conversion
			typeBuf[8],		// String form of type before conversion
			modBuf[8],		// String form of modifier before conversion
			in[25];			// Input from user
	/* OPERATION */
	// Copy the argument into string in and get its length	
	strcpy(in, argv[1]);
	len = strlen(in);

	// Parse the string to find dDex for the dice type
	i = 0;
	while (i < len) {
		if ((in[i] == 'd') || (in[i] == 'D')) {
			dDex = i;
			break;
		}
		if ((in[i] > 57) || (in[i] < 48)) {
			perror("Invalid character in argument\n");
		}
		i++;
	}
	if (i == len) {
		perror("Invalid argument provided\n");
		return 1;
	}

	// Parse the string once more to find any modifiers
	modDex = -1;	// If modDex stays -1, there is no modifier
	i = dDex+1;
	while (i < len) {
		if ((in[i] == '+') || (in[i] == '-')) {
			modDex = i;
			break;
		}
		if ((in[i] > 57) || (in[i] < 48)) {
			perror("Invalid character in argument\n");
			return 1;
		}
		i++;
	}

	// If modDex is not -1, parse for the modifier
	if (modDex != -1) {
		i = modDex+1;
		while (i < len) {
			if ((in[i] > 57) || (in[i] < 48)) {
				perror("Invalid character in argument\n");
				return 1;
			}
			i++;
		}		
	}
	
	// Using the indicies retrieved in the parsing steps, find string variables
	// Find the number of dice to roll
	for (i=0;i<dDex;i++) {
		numDiceBuf[i] = in[i];
	}
	// Find the type of dice and modifier
	sign = 0;								// Sign is zero if no modifier
	mod = 0;								// Mod is zero if no modifier
	if (modDex == -1) {						// No Modifier Case
		j = 0;
		for (i=dDex+1;i<len;i++) {
			typeBuf[j] = in[i];
			j++;
		}
	}
	else {									// Modifier Case
		j = 0;
		for (i=dDex+1;i<modDex;i++) {
			typeBuf[j] = in[i];
			j++;
		}
		if (in[modDex] == '-') {
			sign = 1;
		}
		j = 0;
		for (i=modDex+1;i<len;i++) {
			modBuf[j] = in[i];
			j++;
		}
	}
	// Assign variables for calculation using the strings
	numDice = atoi(numDiceBuf);
	type = atoi(typeBuf);
	if (modDex != -1) {
		mod = atoi(modBuf);
	}
		
	// Roll dice using dice.h roll funciton
	result = roll(numDice, type, mod);

	// Print result to console
	printf("%d\n",result);
	
	return 0;
}
