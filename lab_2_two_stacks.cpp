#include <iostream>
#include <string>

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

int countSpaces(string input)
{
    int spaces(0);
    for (int i = 0; i < input.length(); i++)
        if (input[i] == ' ') spaces += 1;
    return spaces;
}

void inputEdit(string& input)
{
    bool flag(false);
    do
    {
        flag = false;
        for (int i = 0; i < input.length(); i++)
            if (((i == 0) || (i == input.length() - 1)) && (input[i] == ' '))
            {
                input.erase(i, 1);
                flag = true;
            }
            else
                if ((input[i] == ' ') && (input[i + 1] == ' '))
                {
                    input.erase(i, 1);
                    flag = true;
                }
    } while (flag);
}

void checkInput(string input)
{
    int operators(0), wrongMinuses(0);

    if (((input[0] == '*') || ((input[0] == '-') && (!isdigit(input[1]))) || (input[0] == '+') || (input[0] == ' '))) throw 1;
    for (int i = 0; i < input.length(); i++)
        if ((i != (input.length() - 1)) && (input[i] == '-') && (isdigit(input[i + 1]))) wrongMinuses += 1;
        else
            if ((((isdigit(input[i]) == false) && (input[i] != ' ') && (!((input[i] == '*') || (input[i] == '-') || (input[i] == '+'))))) |
                ((i == input.length() - 1) && (input[i] != '+') && (input[i] != '*') && (input[i] != '-'))) throw 1;

    for (int i = 1; i < input.length() - 1; i++)
        if (((input[i] == '+') || (input[i] == '*') || ((input[0] == '-') && (!isdigit(input[1])))) && ((input[i - 1] != ' ') && (input[i + 1] != ' '))) throw 1;

    for (int i = 0; i < input.length(); i++)
    {
        if ((input[i] == '*') || (input[i] == '-') || (input[i] == '+')) operators += 1;
        if (isdigit(input[i]))
            for (int j = i; j < input.length(); j++)
                if ((!(isdigit(input[j]))) && (input[j] != ' ')) throw 1;
                else if ((!(isdigit(input[j]))) && (input[j] == ' ')) break;
    }
    operators -= wrongMinuses;
    if (operators != (countSpaces(input) / 2)) throw 1;
    bool operatorsDetected(false), valuesDetected(false);
    for (int i = 0; i < input.length(); i++)
        if (isdigit(input[i])) valuesDetected = true;
    if (operators != 0) operatorsDetected = true;
    if ((valuesDetected == false) || (operatorsDetected == false)) throw 1;
}

template <typename T>
class Stack
{
private:

    struct Node
    {
        T data;
        struct Node* next;
    };
    struct Node* top = NULL;

public:

    void push(T value)
    {
        struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = value;
        newnode->next = top;
        top = newnode;
    }

    T pop()
    {
        if (top == NULL) throw 1;
        else
        {
            T temp = T(0);
            temp = top->data;
            top = top->next;
            return temp;
        }
    }

    void clear()
    {
        T out = T(0);
        do
        {
            out = pop();
        } while (!is_stack_empty());
    }

    bool is_stack_empty()
    {
        bool result;
        return top == NULL;
    }
};

void ifOperator(Stack<Number>& values, Stack<char>& operators, Number n, Number n2)
{
    n2 = values.pop();
    n = values.pop();
    switch (operators.pop())
    {
    case '+':
        n.addition(n2, true);
        break;

    case '-':
        n.subtraction(n2);
        break;

    case '*':
        n.multiplication(n2);
        break;
    }
    values.push(n);
}

Number calculating(Stack<Number>& values, Stack<char>& operators, string input, bool permit)
{
    Number temp = Number(0);
    Number n(Number(0)), n2(Number(0));

    for (int i = input.length() - 1; i > 0; i--)
        if (((input[i] == '*') || ((input[i] == '-') && (!isdigit(input[i + 1]))) || (input[i] == '+')) && permit)
            operators.push(input[i]);

    for (int i = 0; i < input.length() - 1; i++)
    {
        if ((isdigit(input[i])) || ((input[i] == '-') && (isdigit(input[i + 1]))))
        {
            for (int j = i; j < input.length() - 1; j++)
                if (input[j] == ' ')
                {
                    temp = Number(stoi(input.substr(i, (j - i))));
                    if (!permit) break;
                    values.push(temp);
                    i = j - 1;
                    break;
                }
        }
        else
            if (input[i] != ' ') ifOperator(values, operators, n, n2);
    }
    ifOperator(values, operators, n, n2);
    return values.pop();
}

void exprBin(Stack<Number>& values, string input)
{
    cout << "\nThe expression in binary is: \n";
    Number temp = Number(0);
    for (int i = 0; i < input.length(); i++)
    {
        if ((isdigit(input[i])) || ((input[i] == '-') && (isdigit(input[i + 1]))))
        {
            for (int j = i; j < input.length() - 1; j++)
                if (input[j] == ' ')
                {
                    temp = Number(stoi(input.substr(i, (j - i))));
                    temp.printer();
                    i = j - 1;
                    break;
                }
        }
        else
            if ((input[i] == '*') || ((input[i] == '-') && (!isdigit(input[i + 1]))) || (input[i] == '+')) cout << input[i] << ' ';
    }
}

int main()
{
    bool permit;
    string input;
    Stack<Number> values;
    Stack<char> operators;
    Number result(Number(0));

    do
    {
        cout << "Enter the expression: ";
        getline(cin, input);
        inputEdit(input);
        try
        {
            permit = 1;
            checkInput(input);
            if (permit)
            {
                permit = true;
                result = calculating(values, operators, input, permit);
            }
        }
        catch (int excType)
        {
            switch (excType)
            {
            case 1:
            {
                cout << "\nAn exception has been caught: invalid input.\n" << endl;
                break;
            }
            case 2:
            {
                cout << "\nAn exception has been caught: some of the inputted values are too large.\n" << endl;
                break;
            }
            case 3:
            {
                cout << "\nAn exception has been caught: the calculated value is too large.\n" << endl;
                break;
            }
            }
            permit = false;
            if (!(values.is_stack_empty())) values.clear();
            if (!(operators.is_stack_empty())) operators.clear();
        }
    } while (!permit);
    exprBin(values, input);
    cout << "\n\nThe result is: " << result.getDecimal() << endl;
    cout << "The result in binary is: ";
    result.printer(); cout << endl;
}