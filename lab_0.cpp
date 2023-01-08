// Bubblesorting an array with basic functions to (almost) all iterations, correct inputting is supported.

#include <iostream>
#include <string>

using namespace std;

bool checkInput(string input)
{
    if (input.length() == 0) return false;
    for (size_t i = 0; i < input.length(); i++)
        if ((isdigit(input[i]) == false) & (!((i == 0) & (input[i] == '-') & (input.length()>1)))) return false;
    return true;
}

void replacement(int& firstVariable, int& secondVariable)
{
    int tryout(0);
    tryout = firstVariable;
    firstVariable = secondVariable;
    secondVariable = tryout;
}

void invalidInput(string& input)
{
    cout << "Invalid input! Try again." << endl;
    input.erase();
}

bool checkEquality(int firstVariable, int secondVariable)
{
    if (firstVariable > secondVariable) return true;
    return false;
}

void sorting(int size, int* array, bool order)
{
    if (order) 
    { // true stands for ascending
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size - i - 1; j++)
                if (checkEquality(array[j], array[j + 1])) replacement(array[j], array[j + 1]);
    } // false stands for descending
    else for (int i = size; i >= 0; i--)
        for (int j = size; j >= 0; j--)
            if (checkEquality(array[j], array[j - 1])) replacement(array[j], array[j - 1]);
}

void arrayPrint(int size, int* array)
{
    cout << "The array is: [ ";
    for (int i = 0; i < size; ++i)
        cout << array[i] << ' ';
    cout << ']' << endl;    
}

bool chooseSorting(int size, int* array)
{
    string input;
    do
    {
        cout << "Select the order of sorting (1 for ascending, 0 for descending): ";
        getline(cin, input);
        if ((!checkInput(input)) || ((stoi(input) != 0) & (stoi(input) != 1))) invalidInput(input);
        else 
         { 
            if (stoi(input) == 0) return false;
            return true;
         }
    } while (true);
}

void arrayInput(int size, int* array)
{
    string input;
    cout << "Enter the values of array's elements:" << endl;
    for (int i = 0; i < size; ++i)
        do
        {
            cout << "Element [" << i << "] equals: ";
            getline(cin, input);
            if (checkInput(input))
            {
                array[i] = stoi(input);
                break;
            }
            else invalidInput(input);
        } while (true);
}

int main()
{
    int size(10);
    int* array;
    array = new int[size];
    arrayInput(size, array);
    chooseSorting(size, array) ? sorting(size,array,true) : sorting(size,array,false); 
    arrayPrint(size, array);
}  