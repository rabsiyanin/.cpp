/* Permuting two tetrads with the given indexes of an integer (short int, int) for a 32-bit architecture; functions are presented only. */

#include <iostream>

using namespace std;

void BinaryDump (int n)
{
    for(int i = 0; i < 32; ++i, n <<= 1)
    cout << (n < 0 ? '1': '0');
    cout << endl;
}

void BinaryDump (short int n)
{
    for(int i = 0; i < 16; ++i, n <<= 1)
    cout<< (n < 0 ? '1': '0');
    cout << endl;
}

void replace (int n, int num1, int num2)
{	
    int mask1 = (0xf << 4*num1);
    int mask2 = (0xf << 4*num2);
    int mask = 0xffffffff - mask1 - mask2;  
    int result;

    if (num1 <= num2)
    result = (n & mask) | ((n & mask1) << 4*(num2-num1)) | ((n & mask2) >> 4*(num2-num1));
    else
    result = (n & mask) | ((n & mask2) << 4*(num1-num2)) | ((n & mask1) >> 4*(num1-num2));    
    BinaryDump(result);
}

void replace (short n, int num1, int num2)
{
    short int mask1 = (0xf << 4*num1);
    short int mask2 = (0xf << 4*num2);
    short int mask = 0xffff - mask1 - mask2;  
    short int result;
    
    if (num1 <= num2)
    result = (n & mask) | ((n & mask1) << 4*(num2-num1)) | ((n & mask2) >> 4*(num2-num1));
    else
    result = (n & mask) | ((n & mask2) << 4*(num1-num2)) | ((n & mask1) >> 4*(num1-num2));
    BinaryDump (result);
}

int main()
{
	int n;
    int num1;
    int num2;
    
    cout << "Enter the value: \n";
    do
    {
        cin >> n;
        if (cin.good())
           break;
       else
        {
            cout << "Invalid data, repeat an input. \n";
            cin.clear();
            cout << "Enter the values (value, index of the 1st tetrad, index of the 2nd tetrad) \n";
            while(cin.get() != '\n');
        }
    }
    while(true);
    cin.ignore(9999, '\n');
    BinaryDump (n);
    cout << "Enter the index of the 1st tetrad: \n";
    do
    {
        cin >> num1;
        if (cin.good()) {
            if (num1>7 | num1<0)  {
            cout << "The index is out of bounds, repeat an input.\n";
            cin.clear();
            while(cin.get() != '\n');
            }
            else 
            break;
        }
        else
        {
            cout << "Invalid data, repeat an input.\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while(true);
    cin.ignore(256, '\n');
    cout << "Enter the index of the 2nd tetrad: \n";
    do
    {
        cin >> num2;
        if (cin.good()) {
            if (num2>7 | num2<0)  {
            cout << "The index is out of bounds, repeat an input.\n";
            cin.clear();
            while(cin.get() != '\n');
            }
            else 
            break;
        }
        else
        {
            cout << "Invalid data, repeat an input.\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while(true);
    cin.ignore(256, '\n');
    replace(n, num1, num2);
    replace((short int)n, num1, num2);
    return 0;
}