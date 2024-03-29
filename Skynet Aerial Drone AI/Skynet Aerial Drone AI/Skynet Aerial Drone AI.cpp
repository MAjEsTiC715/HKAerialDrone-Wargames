// Skynet Aerial Drone AI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib> // includes random number generation
#include <iostream> // includes objects cout
#include <time.h> // include the time when the user opened the program

using namespace std;

int hCounter = 0; // loop counter

// The user is asked to guess the enemy target (random number)
// Using a while loop it repeats the question until the guess
// equals the enemy target

int humanSearch(int x)
{
	int guess = 0;
	while (guess != x)
	{
		hCounter++; // add 1 to the loop counter each iteration
		cout << "Please guess the enemy target from square 1 to 64" << endl;
		cin >> guess; // assign the number entered into guess
		if (guess < 1 || guess > 64)
		{
			cout << "Please enter a number between 1 and 64" << endl;
		}
	}
	return -1; // end
}

int bCounter = 1; // loop counter

// A recursive binary search function. It returns 
// location of enemy x in given array arr[l-64] is present, 
// otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
	while (r >= l)
	{
		int mid = l + (r - l) / 2;

		cout << "============================================================" << endl;
		cout << "Skynet HK-Aerial Radar sending out ping #" << bCounter << endl;

		// If the element is present at the middle
		// Then the target number is itself
		// ***To compensate on finding the random number and not
		// ***Just the index number it is located on the array.
		// ***We add 1 to mid to show what number it is Actually comparing

		if (arr[mid] == x)
		{
			cout << "Enemy was hiding at location #" << x << endl;
			cout << "Target was found at location #" << mid + 1 << endl;
			return mid;
		}

		// If element is smaller than mid, then 
		// it can only be present in left subarray

		if (arr[mid] > x)
		{
			cout << "The target location prediction of " << mid + 1 <<
				" is greater than target enemy " << x << endl;
			bCounter++;
			return binarySearch(arr, l, mid - 1, x);
		}

		// Else the element can only be present
		// in right subarray

		else
		{
			cout << "The target location prediction of " << mid + 1 <<
				" is less than target enemy " << x << endl;
			bCounter++;
			return binarySearch(arr, mid + 1, r, x);
		}
	}

	// We reach here when element is not 
	// present in array

	return -1;
}

// Linearly search x in arr[].  If x is present then return its 
// location,  otherwise return -1

int lCounter = 0; // loop counter

int linearSearch(int arr[], int n, int x)
{
	int i;
	for (i = 0; i < n; i++) // n is 64
	{
		lCounter++; // Add 1 to the loop counter each iteration
		if (arr[i] == x) // If i = x then return the number i
		{
			return i;
		}
	}
	return -1; // end
}

// Randomly search x given 1000 tries.  If x matches with guess
// Then return the location, otherwise return -1

int rCounter = 0; // loop counter

int randomSearch(int x)
{
	for (int t = 0; t <= 1000; t++)
	{
		rCounter++; // add 1 to the loop counter each iteration
		int random_n = (rand() % 64) + 1; // generate a psuedo-random number
		if (random_n == x) // compare the two numbers
		{
			return random_n;
		}
	}
	return -1; // end
}

// The main function which creates an array from 1 to 64
// Here we calculate and set the left and right index for
// BinarySearch

int main(void)
{
	int playAgain = 1;
	while (playAgain == 1)
	{
		int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8,
			9, 10, 11, 12, 13, 14, 15, 16,
			17, 18, 19, 20, 21, 22, 23, 24,
			25, 26, 27, 28, 29, 30, 31, 32,
			33, 34, 35, 36, 37, 38, 39, 40,
			41, 42, 43, 44, 45, 46, 47, 48,
			49, 50, 51, 52, 53, 54, 55, 56,
			57, 58, 59, 60, 61, 62, 63, 64 };

		int n = sizeof(arr) / sizeof(arr[0]);
		srand(time(NULL));  // Set a seed using a time set at the start of the program
		int x = (rand() % 64) + 1; // Get a pseudo-random number in [1,64]

		cout << "Generating Random enemy location on 8x8 grid....." << endl;

		int hResult = humanSearch(x);
		int bResult = binarySearch(arr, 0, n - 1, x); // Call BinarySearch with the given arguments
		int lResult = linearSearch(arr, n - 1, x);
		int rResult = randomSearch(x);

		// A Ternary condition that either prints if the enemy is in the array or not

		cout << "==========================================================================\n\n" << endl;

		(hResult == -1) ? printf("The Human took %d predictions to find the enemy at %d\n\n", hCounter, x)
			: printf("The human could not find the enemy\n\n");

		(bResult == -1) ? printf("Enemy was not found on the grid using Binary search\n\n")
			: printf("The Binary search algorithm took %d predictions to find the enemy at %d\n\n", bCounter, x);

		(lResult == -1) ? printf("Enemy was not found on the grid using Linear search\n\n")
			: printf("The Linear search algorithm took %d predictions to find the enemy at %d\n\n", lCounter, x);

		(rResult == -1) ? printf("Enemy was not found on the grid within 1000 tries\n\n")
			: printf("The Random search algorithm took %d predictions to find the enemy at %d\n\n", rCounter, x);

		cout << "Would you like to play again? Enter 1 or 0" << endl;
		cin >> playAgain;
		hCounter = 0;
		bCounter = 0;
		lCounter = 0;
		rCounter = 0;
	}
	return 0; // end
}