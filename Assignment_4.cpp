#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

// Constant variable size for all of the arrays
// Increase if need more storing space
const int arraySize = 100;

// Forward declarations
void Check_For_Read_Input_Error(ifstream &inFile);
void Read_From_Input_File(ifstream &inFile,string firstName[arraySize],string lastName[arraySize],double testOne[arraySize],
                          double testTwo[arraySize],double testThree[arraySize],double testFour[arraySize]);

void Sorting_Names_Alphabetically(string firstName[arraySize],string lastName[arraySize],double testOne[arraySize],
                                  double testTwo[arraySize],double testThree[arraySize],double testFour[arraySize],
                                  double finalNumberGrade[arraySize],string finalLetterGrade[arraySize]);

void Print_Results(ofstream &gradesFile,string firstName[arraySize],string lastName[arraySize],double testOne[arraySize],
                   double testTwo[arraySize],double testThree[arraySize],double testFour[arraySize],
                   double finalNumberGrade[arraySize],string finalLetterGrade[arraySize]);

void Find_Min_Max_And_Average_And_Print(ofstream &gradesFile,double finalNumberGrade[arraySize]);

int main()
{

    // Variables for input and output files
    ifstream inFile;
    inFile.open("students.txt");
    ofstream gradesFile;
    gradesFile.open("grades.txt");

    // Variables for first and last name
    string firstName[arraySize];
    string lastName[arraySize];

    // Variables for test scores
    double testOne[arraySize];
    double testTwo[arraySize];
    double testThree[arraySize];
    double testFour[arraySize];

    // Variables to hold the letter grades and final number grades
    double finalNumberGrade[arraySize];
    string finalLetterGrade[arraySize];

    Check_For_Read_Input_Error(inFile);
    Read_From_Input_File(inFile,firstName,lastName,testOne,testTwo,testThree,testFour);
    Sorting_Names_Alphabetically(firstName,lastName,testOne,testTwo,testThree,testFour,finalNumberGrade,finalLetterGrade);
    Print_Results(gradesFile,firstName,lastName,testOne,testTwo,testThree,testFour,finalNumberGrade,finalLetterGrade);
    Find_Min_Max_And_Average_And_Print(gradesFile,finalNumberGrade);

    // Close the input streams
    inFile.close();
    gradesFile.close();

    return 0;
}

// ---------------FUNCTIONS BELOW THIS LINE--------------------------


// Function to see if you can open the input file
void Check_For_Read_Input_Error(ifstream &inFile)
{
    // Check if the file was open
    // if not throw an error
    if(!inFile)
    {
        cerr << "Unable to open file students.txt";
        exit(1); // Call system to stop
    }
}

// Function that reads in the contents from the input file and stores the values
void Read_From_Input_File(ifstream &inFile,string firstName[arraySize],string lastName[arraySize],double testOne[arraySize],
                          double testTwo[arraySize],double testThree[arraySize],double testFour[arraySize])
{
    // Reads in the inFile contents
    if (inFile.is_open())
    {
        // For loop for storing the input file names and scores
        int i = 0;
        while(inFile >> firstName[i] >> lastName[i] >> testOne[i] >> testTwo[i] >> testThree[i] >> testFour[i])
        {
            i++;
        }
    }
}

// Function that takes the names and sorts everything by last name alphabetically
void Sorting_Names_Alphabetically(string firstName[arraySize],string lastName[arraySize],double testOne[arraySize],
                                  double testTwo[arraySize],double testThree[arraySize],double testFour[arraySize],
                                  double finalNumberGrade[arraySize],string finalLetterGrade[arraySize])
{
    // For loop that finds the final grade and final letter grade
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11 - i ; j++)
        {
            finalNumberGrade[j] =  ((testOne[j] * 0.2) + (testTwo[j] * 0.25) +
                                    (testThree[j] * 0.25) + (testFour[j] * 0.30));

            // If statement to find the letter grade of the student
            if (finalNumberGrade[j] >= 90)
            {
                finalLetterGrade[j] = "A";
            }
            else if(finalNumberGrade[j] >= 80)
            {
                finalLetterGrade[j] = "B";
            }
            else if(finalNumberGrade[j] >= 70)
            {
                finalLetterGrade[j] = "C";
            }
            else if(finalNumberGrade[j] >= 60)
            {
                finalLetterGrade[j] = "D";
            }
            else
            {
                finalLetterGrade[j] = "F";
            }
        }
    }

    // For loop to get all the names in alphabetical order
    // while also making sure to get all the first names, test scores,
    // final grades, and final letter grades in order
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11 - i - 1; j++)
        {
            string temp;
            double numTemp;
            string fullName1 = lastName[j] + firstName[j];
            string fullName2 = lastName[j+1] + firstName[j+1];

            // Compares full names in order to sort alphabetically without
            // running into issues of people with same last names
            if(fullName1.compare(fullName2) > 0)
            {
                temp = lastName[j];
                lastName[j] = lastName[j+1];
                lastName[j+1] = temp;

                temp = firstName[j];
                firstName[j] = firstName[j+1];
                firstName[j+1] = temp;

                numTemp = testOne[j];
                testOne[j] = testOne[j+1];
                testOne[j+1] = numTemp;

                numTemp = testTwo[j];
                testTwo[j] = testTwo[j+1];
                testTwo[j+1] = numTemp;

                numTemp = testThree[j];
                testThree[j] = testThree[j+1];
                testThree[j+1] = numTemp;

                numTemp = testFour[j];
                testFour[j] = testFour[j+1];
                testFour[j+1] = numTemp;

                numTemp = finalNumberGrade[j];
                finalNumberGrade[j] = finalNumberGrade[j+1];
                finalNumberGrade[j+1] = numTemp;

                temp = finalLetterGrade[j];
                finalLetterGrade[j] = finalLetterGrade[j+1];
                finalLetterGrade[j+1] = temp;
            }
        }
    }
}

// Function that prints the final results of the input file in formatted style
void Print_Results(ofstream &gradesFile,string firstName[arraySize],string lastName[arraySize],double testOne[arraySize],
                   double testTwo[arraySize],double testThree[arraySize],double testFour[arraySize],
                   double finalNumberGrade[arraySize],string finalLetterGrade[arraySize])
{
    // Headers for the console
    cout << left
         << setw(15)
         << "Last Name"
         << left
         << setw(15)
         << "First Name"
         << right
         << setw(6)
         << "Test1"
         << right
         << setw(6)
         << "Test2"
         << right
         << setw(6)
         << "Test3"
         << right
         << setw(6)
         << "Test4"
         << right
         << setw(6)
         << "Grade"
         << right
         << setw(7)
         << "Letter"
         << endl;

    // Headers for the .txt file
    gradesFile << left
               << setw(15)
               << "Last Name"
               << left
               << setw(15)
               << "First Name"
               << right
               << setw(6)
               << "Test1"
               << right
               << setw(6)
               << "Test2"
               << right
               << setw(6)
               << "Test3"
               << right
               << setw(6)
               << "Test4"
               << right
               << setw(6)
               << "Grade"
               << right
               << setw(7)
               << "Letter"
               << endl;

    // Outputs the results
    for(int i = 0; i < 11; i++)
    {
        cout << left
             << setw(15)
             << lastName[i]
             << left
             << setw(15)
             << firstName[i]
             << right
             << setprecision(1)
             << fixed
             << setw(6)
             << testOne[i]
             << right
             << setw(6)
             << testTwo[i]
             << right
             << setw(6)
             << testThree[i]
             << right
             << setw(6)
             << testFour[i]
             << right
             << setw(6)
             << finalNumberGrade[i]
             << right
             << setw(7)
             << finalLetterGrade[i]
             << endl;

        // Output results to new .txt file
        gradesFile << left
                   << setw(15)
                   << lastName[i]
                   << left
                   << setw(15)
                   << firstName[i]
                   << right
                   << setprecision(1)
                   << fixed
                   << setw(6)
                   << testOne[i]
                   << right
                   << setw(6)
                   << testTwo[i]
                   << right
                   << setw(6)
                   << testThree[i]
                   << right
                   << setw(6)
                   << testFour[i]
                   << right
                   << setw(6)
                   << finalNumberGrade[i]
                   << right
                   << setw(7)
                   << finalLetterGrade[i]
                   << endl;
    }
    cout << endl;
    gradesFile << endl;
}

// Function that sorts all the final number grades in order to find min, max, and average
// Then outputs the 3 results
void Find_Min_Max_And_Average_And_Print(ofstream &gradesFile, double finalNumberGrade[arraySize])
{
    // Sorts the numbers in ascending order
    double temp;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11 - 1; j++)
        {
            if (finalNumberGrade[j] > finalNumberGrade[j+1])
            {
                temp = finalNumberGrade[j];
                finalNumberGrade[j] = finalNumberGrade[j+1];
                finalNumberGrade[j+1] = temp;
            }
        }
    }

    // Calculate the average
    double sum = 0;
    double average = 0;
    for(int i = 0; i < 11; i++)
    {
        sum += finalNumberGrade[i];
    }
    average = sum / 11;

    // Output to console
    cout << "Class Average: " << average << endl;
    cout << "Class minimum: " << finalNumberGrade[0] << endl;
    cout << "Class Maximum: " << finalNumberGrade[10] << endl;

    // Output to new .txt file
    gradesFile << "Class Average: " << average << endl;
    gradesFile << "Class minimum: " << finalNumberGrade[0] << endl;
    gradesFile << "Class Maximum: " << finalNumberGrade[10] << endl;
}








