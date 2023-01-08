#include <iostream>

using namespace std;

class Number
{
private:
    static const int size = 8;

    long long power(int base, int exp)
    {
        long long result(1);
        for (int i = 0; i < exp; i++)
            result = result * base;
        return result;
    }

    bool checkLowerBorderline()
    {
        if (binary[0] != 1) return false;
        for (int i = 1; i < size; i++)
            if (binary[i] != 0) return false;
        return true;
    }

public:
    int* binary = new int[size];

    Number(int dec)
    {
        if (dec >= power(2, size - 1) || dec < -power(2, size - 1)) throw 2;
        if (!(dec >= power(2, size - 1) || dec <= -power(2, size - 1)))
        {
            int shifted(0);
            if (dec < 0)
            {
                for (int i = size - 1; i >= 0; i--)
                {
                    shifted = -dec >> i;
                    if (shifted & 1) binary[i] = 0; else binary[i] = 1;
                }
                for (int i = 0; i < size / 2; i++)
                    swap(binary[i], binary[size - 1 - i]);
                addition(Number(1), true);
            }
            else
            {
                for (int i = size - 1; i >= 0; i--)
                {
                    shifted = dec >> i;
                    if (shifted & 1) binary[i] = 1; else binary[i] = 0;
                }
                for (int i = 0; i < size / 2; i++)
                    swap(binary[i], binary[size - 1 - i]);
            }
        }
        if (dec == -power(2, size - 1))
        {
            binary[0] = 1;
            for (int i = 1; i < size; i++)
                binary[i] = 0;
        }
    }

    void reverse()
    {
        if (binary[0] == 1)
        {
            addition(Number(-1), true);
            for (int i = 0; i < size; i++)
                if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;
        }
        else
        {
            for (int i = 0; i < size; i++)
                if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;
            addition(Number(1), true);
        }
    }

    int getSize()
    {
        return size;
    }

    void addition(Number n, bool type)
    {
        int signFirst = binary[0];
        int signSecond = n.binary[0];
        int carry(0), d1(0), d2(0), sum(0);

        for (int i = size - 1; i >= 0; i--)
        {
            d1 = binary[i];
            d2 = n.binary[i];
            sum = d1 + d2 + carry;
            if (sum == 0) binary[i] = 0;
            else if (sum == 1)
            {
                binary[i] = 1;
                carry = 0;
            }
            else if (sum == 2)
            {
                binary[i] = 0;
                carry = 1;
            }
            else if (sum == 3)
            {
                binary[i] = 1;
                carry = 1;
            }
        }
        if (((type) && signFirst == 0 && signSecond == 0 && binary[0] == 1) ||
            ((type) && signFirst == 1 && signSecond == 1 && binary[0] == 0)) throw 3;
    }

    void subtraction(Number n)
    {
        n.reverse();
        addition(n, 1);
    }

    void multiplication(Number n)
    {
        if (checkLowerBorderline())
        {
            for (int i = 0; i < size - 1; i++)
                if (n.binary[i] != 0) throw 3;
            if (n.binary[size - 1] == 0) binary[0] = 0;
        }
        else
            if (n.checkLowerBorderline())
            {
                for (int i = 0; i < size - 1; i++)
                    if (binary[i] != 0) throw 3;
                if (binary[size - 1] == 0) n.binary[0] = 0;
            }
            else
            {
                bool negative(false), overflow(false);
                if (binary[0] == 1)
                {
                    reverse();
                    negative = !negative;
                }
                if (n.binary[0] == 1)
                {
                    n.reverse();
                    negative = !negative;
                }
                int* sndBinary = new int[size];
                for (int i = 0; i < size; i++)
                {
                    sndBinary[i] = binary[i];
                    binary[i] = 0;
                }
                for (int i = size - 1; i >= 0; i--)
                {
                    if (sndBinary[i] == 1)
                    {
                        if (overflow) throw 3;
                        else addition(n, false);
                    }
                    for (int i = 0; i < size; i++)
                        swap(n.binary[i], n.binary[i + 1]);
                    if (n.binary[0] == 1) overflow = true;
                }
                if (binary[0] == 1) throw 3;
                if (negative)
                {
                    int temp(1);
                    for (int i = 0; i < size; i++)
                        if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;
                    for (int i = size - 1; i >= 0; i--)
                    {
                        if (binary[i] == 1 && temp == 1) binary[i] = 0; else
                            if (binary[i] == 0 && temp == 1)
                            {
                                binary[i] = 1;
                                temp = 0;
                            }
                            else
                                binary[i] = binary[i];
                    }
                }
            }
    }

    void printer()
    {
        for (int i = 0; i < size; i++)
            cout << binary[i];
        cout << " ";
    }

    int getDecimal()
    {
        int result(0);
        int* sndBinary = new int[size];
        for (int i = 0; i < size; i++)
            sndBinary[i] = binary[i];
        if (sndBinary[0] == 1)
        {
            for (int i = 0; i < size; i++)
                if (sndBinary[i] == 1) sndBinary[i] = 0; else sndBinary[i] = 1;
            for (int i = 0; i < size; i++)
                result = result + sndBinary[i] * power(2, (size - i - 1));
            result = (result + 1) * (-1);
        }
        else
            for (int i = 0; i < size; i++)
                result = result + sndBinary[i] * power(2, (size - i - 1));
        delete[] sndBinary;
        return result;
    }

    operator int* () const
    {
        return binary;
    }
};

void input(int& dec1, char& operand, int& dec2)
{
    cout << "Enter the expression: ";
    do
    {
        if (!(cin >> dec1 >> operand >> dec2))
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Try again." << endl;
        }
        else
            if (operand != '+' && operand != '-' && operand != '*')
            {
                cout << "Please enter '+', '-' or '*'. \n";
                cin.clear();
            }
            else
                break;
    } while (true);
}

int main()
{
    int num1, num2;
    bool permit(false);
    char operand;
    Number n1 = Number(0);
    Number n2 = Number(0);
    cout << "Current bitset is " << n1.getSize() << " bit.\n" << endl;
    do
    {
        try
        {
            input(num1, operand, num2);
            n1 = Number(num1), n2 = Number(num2);
            permit = true;
        }
        catch (int excType)
        {
            if (excType == 20) cout << "\nOverflow of the given number. Please, try inputting once again.\n" << endl;
        }
    } while (!permit);

    cout << "\nFirst number in binary: ";
    n1.printer();
    cout << endl;
    cout << "Second number in binary: ";
    n2.printer();
    cout << endl;

    try
    {
        switch (operand)
        {
        case '+':
            n1.addition(n2, true);
            break;

        case '-':
            n1.subtraction(n2);
            break;

        case '*':
            n1.multiplication(n2);
            break;
        }
        cout << "The result in binary: ";
        n1.printer();
        cout << endl;
        cout << "The result in decimal: ";
        cout << n1.getDecimal() << endl;
        cout << "The result in binary: ";
        n1.printer();
        cout << endl;
    }
    catch (int excType)
    {
        if (excType == 100) cout << "OVERFLOW: the calculated value is too large." << endl;
    }
}
