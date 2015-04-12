/******************************************************************************
 * Bellevue Class: PROG 113
 *           Term: Spring 2015
 *     Instructor: Robert Main
 *
 * Solution/Project Name: BrintonProject1
 *             File Name: MovieStat.cpp
 *
 * This file defines the entry point method, main(), for a C++ Console
 * application. When the executable file is selected for execution, the OS
 * will transfer execution to the first line of code in method main(). Other
 * methods called from main() may be defined here as well.
 *
 * Programmer: Colin Brinton
 *
 * Assigned Project Number: 1
 *
 *
 * Revision     Date                        Release Comment
 * --------  ----------  ------------------------------------------------------
 *   1.0     04/09/2015  Initial Release
 *
 *
 * Program Inputs
 * --------------
 *  Device                              Description
 * --------  ------------------------------------------------------------------
 * Keyboard  User inputs the number of students surveyed
 *			 User inputs the number of movies watched for each student
 *
 *
 * Program Outputs
 * ---------------
 *  Device                            Description
 * --------  ------------------------------------------------------------------
 * Monitor   Program description displayed
 *			 Prompt to enter the number of students surveyed
 *			 Input validation error (if applicable)
 *			 Prompt to enter the number of movies for each student
 *			 Statistics displayed
 *			 Prompt to exit
 *			
 *
 *
 * File Methods
 * ------------
 *     Name                              Description
 * ------------    --------------------------------------------------------------
 * main            Program entry point method
 * getMovies	   Prompts the user to input the number of movies watched, stores responses
 *					in array.
 * selectionSort   Sorts the array of the number of movies
 * calcAvg		   Calculates the average of the array, returns average as double
 * calcMode		   Calculates and returns the mode if the array, tests for unique conditions
 * calcMedian	   Calculates the median of the array, returns a double
 * printArray	   Prints the sorted array and displays the average, median and mode
 *
 ******************************************************************************
 */
// External Definition files
// The first inclusion file MUST always be declared and MUST be first in the list
#include "stdafx.h"  // Defines IDE required external definition files
#include <iostream>  // Defines objects and classes used for stream I/O

// Namespaces utilized in this program
using namespace std; // Announces to the compiler that members of the namespace
                     // "std" are utilized in this program

// Function Prototypes
void getMovies(int* students, int num);
void selectionSort(int* students, int num);
double calcAvg(int* students, int num);
double calcMode(int* students, int num, bool& polyMode);
double calcMedian(int* students, int num);
void printArray(int* students, int num, double average, double mode, double median, bool polyMode);

/******************************************************************************
* Method: main()
* 
* Method Description
* ------------------
* The program opens with a description and prompts the user to enter the number
* of students surveyed. Based on the user's response, the method dynamically
* allocates an array to store data. The method then calls another method that
* sorts the array, followed by three more functions that calculate the average,
* mode and median of the array. Finally printArray is called and the sorted data
* and statistics is displayed. The method cleans up used memory.
*
* Pre-Conditions
* --------------
* The user will enter integer values when prompted. 
* (The array will not contain multiple modes. One mode and error
* message will display.)
*
* Method Arguments
* ----------------
*   Type        Name                        Description
* --------  -------------  ----------------------------------------------------
*                        *** No Arguments supplied ***
*
* Return Value
* ------------
*   Type                              Description
* --------  -------------------------------------------------------------------
* int       Program execution status: 0 - No errors
*
*
* Invoked Methods
* ---------------
*    Name                              Description
* ------------    --------------------------------------------------------------
* getMovies	       Prompts the user to input the number of movies watched, stores responses
*					in array.
* selectionSort    Sorts the array of the number of movies
* calcAvg		   Calculates the average of the array, returns average as double
* calcMode		   Calculates and returns the mode if the array, tests for unique conditions
* calcMedian	   Calculates the median of the array, returns a double
* printArray	   Prints the sorted array and displays the average, median and mode
*
*******************************************************************************
*/
 int main()          
{
	 // Constant "const" Value Declarations
	 const int NO_ERRORS = 0; 
	 const int MIN = 3;		 // Min and max values for surveyed students
	 const int MAX = 10;

	 // Declaring variables later passed to functions
	 int* students;
	 int num;

	 double average, median, mode;

	 // Flag for multiple modes
	 bool polyMode = NULL;

	 // Program description
	 cout << "This program is used to gather statistical data about the" << endl
		 << "number of movies college students see in a given month." << endl << endl;

	 // Prompt to enter the number of students polled
	 cout << "Please enter the number of students polled in the survey." << endl
		 << "Enter a number between 3-10: ";

	 cin >> num;
	 cout << endl;

	 // Input validation
	 while ((num < MIN) || (num > MAX))
	 {
		 cout << "Invalid entry. Please enter a number between 3-10: ";
		 cin >> num;
	 }
	 
	 // Dynamic allocation of array to store movie data
	  students = new int[num];

	  // Function calls
	  getMovies(students, num);
	  selectionSort(students, num);
	  average = calcAvg(students, num);
	  mode = calcMode(students, num, polyMode);
	  median = calcMedian(students, num);
	  printArray(students, num, average, mode, median, polyMode);

	  // Clear used memory
	  delete[] students;
	  students = NULL;

	// This prevents the Console Window from closing during debug mode using
	// the Visual Studio IDE.
	// Note: Generally, you should not remove this code
	cin.ignore(cin.rdbuf()->in_avail());
	cout << "\nPress only the 'Enter' key to exit program: ";
	cin.get();

	return NO_ERRORS;
}

 /******************************************************************************
 * Method: getTests
 *
 * Method Description
 * ------------------
 * Prompts the user to input number of movies watched. Validates input. Stores the input in an array of
 * ints
 *
 *
 * Pre-Conditions
 * --------------
 * User will enter int values
 *
 *
 * Method Arguments
 * ----------------
 * Type      Name                          Description
 * --------  --------  ---------------------------------------------------------
 * int*		tests		An array of ints to hold movie data
 * int		num			User inputted number of movies to sort
 *
 *
 * Return Value
 * ------------
 * void      No value RETurned by the method
 *
 *
 * Invoked Methods
 * ---------------
 *  None
 *
 *******************************************************************************
 */

 void getMovies(int* students, int num)
 {
	 // Constant value declarations
	 const int MIN = 0;
	 const int OFFSET = 1;

	 // Temporary value holding
	 int movieIn;

	 cout << endl;
	 for (int index = 0; index < num; index++)
	 {
		 cout << "Please enter the number of movies that student " << (index + OFFSET) << " watched: ";
		 cin >> movieIn;

		 //  Input validation
		 while (movieIn < MIN)
		 {
			 cout << "Invalid entry. Please enter a positive integer: ";
			 cin >> movieIn;
		 }

		 // Pointer arithmetic used
		 *(students + index) = movieIn;
	 }
	 cout << endl;
 }

 /******************************************************************************
 * Method: selectionSort()
 *
 * Method Description
 * ------------------
 * Sorts an array that is passed to it using the selection sort method. It scans the full array, finds the smallest
 * number and places it at the front.
 *
 *
 * Pre-Conditions
 * --------------
 * None
 *
 *
 * Method Arguments
 * ----------------
 *   Type      Name                          Description
 * --------  --------     ---------------------------------------------------------
 * int		num			    User inputted number of movie numbers to sort
 * int*		students		Array of ints to be sorted based on number of movies
 *
 *
 * Return Value
 * ------------
 * None
 *
 *
 *
 * Invoked Methods 
 * --------------
 * None
 *
 *******************************************************************************
 */
 void selectionSort(int* students, int num)
 {
	 int minIndex;
	 int minElem;
	 for (int scan = 0; scan < (num - 1); scan++)
	 {
		 minIndex = scan;
		 minElem = *(students + scan);
		 for (int index = scan + 1; index < num; index++)
		 {
			 if (*(students + index) < minElem)
			 {
				 minElem = *(students + index);
				 minIndex = index;
			 }
		 }
		 *(students + minIndex) = *(students + scan);
		 *(students + scan) = minElem;

	 }
 }

 /******************************************************************************
 * Method: calcAvg()
 *
 * Method Description
 * ------------------
 * Calculates the average of the array it receives. Returns average as a double.
 *
 *
 * Pre-Conditions
 * --------------
 * Valid arguments will be passed.
 *
 *
 * Method Arguments
 * ----------------
 *    Type      Name                          Description
 * --------  --------    ---------------------------------------------------------
 * int		  num			User inputted number of movies numbers to sort
 * int*	      students		Array of ints holding movie numbers
 *
 * Return Value
 * ------------
 *   Type                              Description
 * --------  -------------------------------------------------------------------
 * double       Returns the calculated average of the movie numbers
 *
 *
 *
 * Invoked Methods
 * --------------
 * None
 *
 *******************************************************************************
 */

 double calcAvg(int* students, int num)
 {
	 double sum = 0.0;

	 for (int count = 0; count < num; count++)
		 sum += *(students + count);

	 return (sum / num);
 }

 /******************************************************************************
 * Method: calcMode()
 *
 * Method Description
 * ------------------
 * Finds the mode of the array it receives. Returns mode as a double. 
 * Also detects if there is no mode or if there are multiple modes.
 *
 *
 * Pre-Conditions
 * --------------
 * Valid arguments will be passed.
 * Will only return the first mode when multiples exist in an array.
 *
 *
 * Method Arguments
 * ----------------
 *    Type      Name                          Description
 * --------  --------    ---------------------------------------------------------
 * int		  num			User inputted number of movie numbers to sort
 * int*	      students		Array of ints holding movie numbers
 *
 *
 * Return Value
 * ------------
 *   Type                              Description
 * --------  -------------------------------------------------------------------
 * double       Returns the mode of the movie numbers
 *
 *
 *
 * Invoked Methods
 * --------------
 * None
 *
 *******************************************************************************
 */

 double calcMode(int* students, int num, bool& polyMode)
 {
	 const int OFFSET = 1;
	 const int NO_MODE = -1;
	 int counter = OFFSET;
	 int max = NULL;
	 int mode = *students;

	 for (int pass = NULL; pass < num - OFFSET; pass++)
	 {
		 if (*(students + pass) == *(students + pass + OFFSET))
		 {
			 counter++;
			 if (counter > max)
			 {
				 max = counter;
				 mode = *(students + pass);
			 }
			 else if (counter == max)
				 polyMode = true;
		 }

		 else
			 counter = OFFSET; // reset counter.
	 }
	 if (max == NULL)
	 {
		 mode = NO_MODE;
		 return mode;
	 }
	 else
		 return mode;
 }

 /******************************************************************************
 * Method: calcAvg()
 *
 * Method Description
 * ------------------
 * Calculates the median of the array it receives. Returns median as a double.
 *
 *
 * Pre-Conditions
 * --------------
 * Valid arguments will be passed.
 *
 *
 * Method Arguments
 * ----------------
 *    Type      Name                          Description
 * --------  --------    ---------------------------------------------------------
 * int		  num			User inputted number of movies
 * int*	      students		Array of ints to be sorted based on movie numbers
 *
 *
 * Return Value
 * ------------
 *   Type                              Description
 * --------  -------------------------------------------------------------------
 * double       Returns the median of the movie numbers
 *
 *
 *
 * Invoked Methods
 * --------------
 * None
 *
 *******************************************************************************
 */

 double calcMedian(int* students, int num)
 {
	 const int OFFSET = 1;
	 const int TWO = 2;
	 const double DOUBLE_TWO = 2.0;

	 double median;

	 // If the the number of elements odd
	 if (num % TWO != NULL)
	 {
		 int temp = ((num + OFFSET) / TWO) - OFFSET;
		 median = *(students + temp);
	 }
	 // If the number of elements is even 
	 else
	 {
		 median = (*(students + ((num / TWO) - OFFSET)) + *(students + (num / TWO))) / DOUBLE_TWO;
	 }
	 return median;
 }

 /******************************************************************************
 * Method: printArray()
 *
 * Method Description
 * ------------------
 * When called this method prints the contents of the array passed to it.
 * The function also prints the average.
 *
 *
 * Pre-Conditions
 * --------------
 * None
 *
 *
 * Method Arguments
 * ----------------
 *   Type      Name                          Description
 * --------  --------  ---------------------------------------------------------
 *	int		  num			User inputted number of movies to sort
 *	int*	  students		Array of ints to be sorted based on the number of movies
 *  double	  average		The movie number average
 *  double    mode			The mode of the array
 *  double    median		The median of the array
 *  bool	  polyMode		If multiple modes exist in the array, this flag will be true
 *
 *
 * Return Value
 * ------------
 *   Type                              Description
 * --------  -------------------------------------------------------------------
 * void      No value RETurned by the method
 *
 *
 * Invoked Methods
 * --------------
 *  None
 *
 *******************************************************************************
 */

 void printArray(int* students, int num, double average, double mode, double median, bool polyMode)
 {
	 //Constant value, flag for no mode
	 const int NO_MODE = -1;

	 // Print sorted array
	 cout << "These are the number of movies you entered in ascending order:" << endl << endl;
	 for (int count = 0; count < num; count++)
	 {
		 if (count < num && !(count == NULL))
			 cout << ", ";
		 cout << *(students + count);
	 }
	 cout << endl << endl;

	 // Print Average
	 cout << "Average: " << average << endl;
	 
	 // Print no mode condition
	 if (mode == NO_MODE)
		 cout << "Mode: No mode found" << endl;

	 // Print mode
	 else
	 {
		 cout << "Mode: " << mode;

		 // Display warning message if multiple modes found
		 if (polyMode)
			 cout << " (Warning: Displaying one of multiple modes)";
		 cout << endl;
	 }

	 //Print median
	 cout << "Median: " << median << endl;
 }