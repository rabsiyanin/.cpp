// Passing the examination beforehand; addition of two positive numbers with the representation of a column. */

#include <iostream>

using namespace std;

long long power(int base, int exp)
{
    long long result(1);
    for (int i = 0; i < exp; i++)
        result = result * base;
    return result;
}

template<typename T>
void arrayPrint(char* p, T n)
{
    int size = (n + 2) * (n + 7);
    short k;
    bool t;
    for (int i = 0; i < size; i = i + n + 2)
    {
        k = 0;
        t = true;
        for (int l = 0; l < n + 2; ++l)
            if (p[i + l] == ' ') ++k;
        if (k != n + 2)
            for (int l = 0; l < n + 2; ++l)
            {
                if ((p[i+l] == 48) & (t) & (l!=(n+1)) & (i < 3*n + 7) & (p[i+l]!='_'))
                {
                    p[i+l] = ' ';
                    if (p[i+l+1] != 48) t = !t;
                }
                cout << p[i + l];
                if (((i + l + 1) % (n + 2) == 0) && ((i + l + 1) != size)) cout << endl;
            }
    }
    cout << '\n';
}

template<typename T>
void algorithm(char* p, T n, T n1, T n2)
{
    int size = (n + 2) * (n + 7);
    for (int i = 0; i < size; ++i)
        p[i] = ' ';
    for (int i = 0; i < size; ++i)
    {
        for (int l = 0; l < (n + 2); ++l)
            p[l] = ' ';
        if (i / ((n + 2) * 5) == 1)
            for (int j = (n + 2) * 4 + 2; j < (n + 2) * 5; ++j)
                p[j] = '_';
        if ((i % (n + 2) == 0) && (i != size) && (i != 0)) p[i] = ' ';
    }
    for (int i = 0; i < n + 2; ++i)
    {
        if (n1 >= 0)
        {
            p[(n + 2) * 2 - (i + 1)] = (n1 % 10) + 48;
            n1 = n1 / 10;
        }
        if (n2 >= 0)
        {
            p[(n + 2) * 4 - (i + 1)] = (n2 % 10) + 48;
            n2 = n2 / 10;
        }
    }
    int na, st(0), ya(6);
    for (int i = 0; i < n + 1; ++i)
    {
        if ((p[(n + 2) * 2 - (i + 1)] == ' ') & (p[(n + 2) * 4 - (i + 1)] == ' '))
            na = st;
        else
            if (p[(n + 2) * 2 - (i + 1)] == ' ')
                na = ((p[(n + 2) * 4 - (i + 1)] + st) - 48); else
                if (p[(n + 2) * 4 - (i + 1)] == ' ')
                    na = ((p[(n + 2) * 2 - (i + 1)] + st) - 48); else
                    na = (((p[(n + 2) * 2 - (i + 1)] + p[(n + 2) * 4 - (i + 1)]) + st) - 96);
        if (st == 1)
        {
            --st;
            p[n + 2 - (i + 1)] = '.';
        }
        if (na > 9) ++st;
        if (!(char((na % 10) + 48) == '0') || !(((n + 2) * ya - (i + 1) - 1) % (n + 2) == 0))
        {
            p[(n + 2) * ya - (i + 1)] = char((na % 10) + 48);
            p[(n + 2) * (n + 7) - (i + 1)] = char((na % 10) + 48);
        }
        ++ya;
    }
    p[(n + 2) * 2] = '+';
    if (p[1] == '.') p[1+(n+2)*4] = '_';
}

short countDigits(int n)
{
    bool i(0);
    int k(0);
    do
    {
        n = n / 10;
        ++k;
        if (n < 1) i = !i;
    } while (!i);
    return k;
}

int main()
{
    int n1, n2, n;
    char* p;
    do
    {
        cout << "Enter the first value: " << endl;
        cin >> n1;
        if (cin.good())
            if (n1 >= 0)
                break;
            else
            {
                cout << "The value is negative! Input the value again.\n";
                cin.clear();
                while (cin.get() != '\n');
            }
        else
        {
            cout << "Invalid data! Input the value again.\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    } while (1);
    do
    {
        cout << "Enter the second value: " << endl;
        cin >> n2;
        if (cin.good())
            if (n2 >= 0)
                break;
            else
            {
                cout << "The value is negative! Input the value again.\n";
                cin.clear();
                while (cin.get() != '\n');
            }
        else
        {
            cout << "Invalid data! Input the value again.\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    } while (1);
    if (countDigits(n1) < countDigits(n2))
    {
        int x = n1;
        n1 = n2;
        n2 = x;
    }
    n = countDigits(n1);
    p = new char[(n + 2) * (n + 7)];
    cout << "\nInt:" << endl;
    algorithm<int>(p, n, n1, n2);
    arrayPrint<int>(p, n);
    cout << '\n';
    if ((n1 < 32768) & (n2 < 32768))
    {
        cout << "Short int:" << endl;
        algorithm<short>(p, n, n1, n2);
        arrayPrint<short>(p, n);
    }
    return 0;
}