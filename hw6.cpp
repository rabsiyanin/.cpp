/* Calculating an expression with an overloading class structure to each arithmetic operation. */

#include <iostream>

using namespace std;

class Float
{
    float number;
public:
    Float(float n = 0.0) :number(n) {}
    Float(const Float& object) : number(object.number) {}
    Float& operator= (const Float& object) 
    {
        number = object.number;
        return *this;
    }
    Float operator+ (Float);
    Float operator- (Float);
    Float operator* (Float);
    Float operator/ (Float);
    friend ostream& operator<< (ostream&, const Float&);
    friend istream& operator>> (istream&, Float&);
};

Float Float::operator+ (Float n)
{
    Float
        temporary(*this);
    temporary.number += n.number;
    return temporary;
}

Float Float::operator- (Float n)
{
    Float
        temporary(*this);
    temporary.number -= n.number;
    return temporary;
}

Float Float::operator* (Float n)
{
    Float
        temporary(*this);
    temporary.number *= n.number;
    return temporary;
}

Float Float::operator/ (Float n)
{
    Float
        temporary(*this);
    if ((n.number > 0) || (n.number < 0))
    {
        temporary.number /= n.number;
        return temporary;
    }
    else
    {
        cout << "Division by zero. The operation of dividing was ignored." << endl;
        return temporary;
    }
}


istream& operator>> (istream& stream, Float& n)
{
    float
        temporary(0);
    stream >> temporary;
    if (stream.fail())
        stream.clear();
    while (stream.get() != '\n');
    n.number = temporary;
    return stream;
}

ostream& operator<< (ostream& stream, const Float& n)
{
    return stream << float(n.number);
}


int main()
{
    Float a, b, c, d;
    Float result;
    do
    {
        cout << "Enter the first value (a): ";
        cin >> a;
        if (cin.good())
            break;
        else
        {
            cout << "Invalid data!\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    } while (1);
    do
    {
        cout << "Enter the second value (b): ";
        cin >> b;
        if (cin.good())
            break;
        else
        {
            cout << "Invalid data!\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    } while (1);
    do
    {
        cout << "Enter the third value (c): ";
        cin >> c;
        if (cin.good())
            break;
        else
        {
            cout << "Invalid data!\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    } while (1);
    do
    {
        cout << "Enter the fourth value (d): ";
        cin >> d;
        if (cin.good())
            break;
        else
        {
            cout << "Invalid data!\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    } while (1);

    cout << "\n";
    result = ((a + b) * c / d);
    cout << "(a + b) * c / d = " << result << endl;

    return 0;
}