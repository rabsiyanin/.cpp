/* Calculating the expression of (x-y)*z with the hexidecimal values of each variable.
The representative is given as forward code for non-negative numbers and two's complement code for negative numbers. */

#include <iostream>

int main()
{
    using namespace std;
    char x, x1, x2, x3;
    int a(0);
    
    cout << "Source data in hexadecimal:" << endl;
    do
    {
        cout << "x1: ";
        cin >> hex >> a;
        if (cin.fail())
        {
            cin.clear();
            while(cin.get() != '\n');
            cout << "The input is invalid.\n";
        } 
        else
        {
            cin.ignore(256, '\n');
            if (!(a >= -128 && a <= -16) && !(a>=16 && a<=255)) 
                cout << "The input must be two-digit.\n";
        }
        if (a & 0200) a ^= 037777777400;
    }
    while (!(a >= -128 && a <= -16) && !(a>=16 && a<=127));
    x1=a;
    do
    {
        cout << "x2: ";
        cin >> hex >> a;
        if (cin.fail())
        {
            cin.clear();
            while(cin.get() != '\n');
            cout << "The input is invalid.\n";
        } 
        else
        {
        cin.ignore(256, '\n');
        if (!(a >= -128 && a <= -16) && !(a>=16 && a<=255)) 
            cout << "The input must be two-digit.\n";
        }
        if (a & 0200) a ^= 037777777400;
    }
    while (!(a >= -128 && a <= -16) && !(a>=16 && a<=127));
    x2=a;
    do
    {
        cout << "x3: ";
        cin >> hex >> a;
        if (cin.fail())
        {
            cin.clear();
            while(cin.get() != '\n');
            cout << "The input is invalid.\n";
        } 
        else
        {
        cin.ignore(256, '\n');
        if (!(a >= -128 && a <= -16) && !(a>=16 && a<=255)) 
            cout << "The input must be two-digit.\n";
        }
        if (a & 0200) a ^= 037777777400;
    }   
    while (!(a >= -128 && a <= -16) && !(a>=16 && a<=127));
    x3=a;
    x = (x1 - x2) * x3;
    cout << "\nResult in decimal: ";
    cout << dec << int(x) << endl;
    cout << "Result in hexadecimal: ";
    cout << hex << int(x & 0377);
    return 0;
}