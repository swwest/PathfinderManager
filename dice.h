/*
dice.h
Samuel West
A simple framework for rolling dice using the xdX notation for DND/Pathfinder
v0.01
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef DICE_H
#define DiCE_H

int roll(int numDice, int type, int mod)
{
	// Set the seed for random number generation
	srand(time(0));

	int result,		// Dice roll result
		i;			// Loop variable
	
	result = 0;
	// For each number of dice
	for (i=0;i<numDice;i++) {
		// Roll the dice type
		result += (rand() % type);
	}
	// Add (or subtract) any modifier
	result += mod + 1;;
	return result;
}

#endif
