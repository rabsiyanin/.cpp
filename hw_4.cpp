/*Packing an octal dump of an integer (char, short int, int) into a one-dimensional character array and 
unpacking this array to obtain the original integer within the 32-bit architecture. Templates are supported.*/

#include <iostream>

using namespace std;

long long power(int base, int exp)
{   
    long long result(1);
    for(int i = 0; i < exp; i++)
        result = result * base;
    return result;
}

template<typename T> 
void dumpPack(T n, char* p)
{
    T mask;
    int size((8 * sizeof(T)) / 3);
    int base(3 * ((8 * sizeof(T) / 3) - 1));
    switch (sizeof(T))
    {
        case 1 : // char
        mask = 070;
        p[size] = char(((n >> 6) & 03) + 48);
        break;

        case 2 : // short int 
        mask = 070000;
        p[size] = char(n < 0 ? '1' : '0');
        break;

        case 4 : // int or long int
        mask = 07000000000;
        p[size] = char(((n >> 30) & 03) + 48);
        break;
    }
    for (int i = 0; i < size; ++i, mask >>= 3)
    p[size-i-1]=char(((n & mask) >> base - i * 3) + 48);
    cout << "\n";        
}


template<typename T> 
void arrayPrint(T n, char* p)
{
    int size(1+(8 * sizeof(T)) / 3);
    cout << "The array is: [ ";
    for(int i = 0; i < size; ++i)
        cout << p[size-i-1] << ' ';
    cout << ']' << endl;
}

int octalToDecimal(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;
    while (temp) 
    {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 8;
    }
    return dec_value;
}

template<typename T> 
void intoInt(T n, char* p, bool x)
{
    int size(1+(8 * sizeof(T)) / 3);
    long long num(0);
    long long decrease;
    switch (sizeof(T))
    {
        case 1 : // char
        decrease = 378;
        break;

        case 2 : // short int 
        decrease = 177778;
        break;

        case 4 : // int or long int
        decrease = 37777777778;
        break;
    }
    for (int i = 0; i < (size); ++i)
        num = num+(p[size-i-1]-48)*power(10,(size-i-1));
    cout << "The value in octal: " << num << endl;
    if (x==0) cout << "The value after unpacking: " << octalToDecimal(num) << endl;
    else 
        {   
            num=(num-decrease)*(-1);
            cout << "The value after unpacking: " << (-1)*octalToDecimal(num) << endl;
        }
}

int main()
{
    int n;
    char* p;
    do
    {   
        cout << "Enter the value: " << endl;
        cin >> n;
        if(cin.good())
            break;
        else
        {
            cout << "Invalid data!\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while(1);
    
    bool x(0);

    p = new char[11];
    dumpPack<int>(n,p);
    arrayPrint<int>(n,p);
    if ((p[10]-48)==3) ++x;
    intoInt<int>(n,p,x);
    delete[] p;

    if ((n>-32769) && (n<32768)) 
    {
        p = new char[6];
        dumpPack<short int>(n, p);
        arrayPrint<short int>(n,p);
        if ((p[10]-48)==3) ++x;
        intoInt<short int>(n,p,x);
        delete[] p;
    }
    
    if ((n>-129) && (n<128)) 
    {
        p = new char[3];
        dumpPack<char>(n, p);
        arrayPrint<char>(n,p);
        if ((p[10]-48)==3) ++x;
        intoInt<char>(n,p,x);
        delete[] p;
    }
    
    return 0;
}