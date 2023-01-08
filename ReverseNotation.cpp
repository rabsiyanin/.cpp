#include <iostream>
#include <string>
//#include <cmath>
using namespace std;

class Binary {
private:
    static const int size = 8;    

public:
    int* binary = new int[size];

    Binary(int dec) {
        if (dec >= (pow(2, size - 1)) || dec < (-pow(2, size - 1))) {
            throw 0;
        }
        else if (dec == -pow(2, size - 1)) {
            binary[0] = 1;
            for (int i = 1; i < size; i++) {
                binary[i] = 0;
            }
        }
        else {
            int support(0);
            if (dec < 0) {
                for (int i = 0; i <= size - 1; i++) {
                    support = -dec >> i;
                    support & 1 ? binary[i] = 0 : binary[i] = 1;
                }
                for (int i = 0; i < size / 2; i++) {
                    swap(binary[i], binary[size - 1 - i]);
                }
                addition(Binary(1), true);
            }
            else {
                for (int i = 0; i <= size - 1; i++) {
                    support = dec >> i;
                    support & 1 ? binary[i] = 1 : binary[i] = 0;
                }
                for (int i = 0; i < size / 2; i++) {
                    swap(binary[i], binary[size - 1 - i]);
                }
            }
        }
    }

    int getSize() {
        return size;
    }

    bool lowBorder() {
        if (binary[0] != 1) {
            return 0;
        }
        for (int i = 1; i < size; i++) {
            if (binary[i] != 0) {
                return 0;
            }
        }
        return 1;
    }

    void changeSign() {
        if (binary[0] == 1) {
            subtraction(1);
            for (int i = 0; i < size; i++) {
                binary[i] == 1 ? binary[i] = 0 : binary[i] = 1;
            }
        }
        else {
            for (int i = 0; i < size; i++) {
                binary[i] == 1 ? binary[i] = 0 : binary[i] = 1;
            }
            addition(Binary(1), true);
        }
    }

    void addition(Binary num, bool type) {
        int signFirst = binary[0];
        int signSecond = num.binary[0];
        int carry(0), d1(0), d2(0), sum(0);

        for (int i = size - 1; i >= 0; i--) {
            d1 = binary[i];
            d2 = num.binary[i];
            sum = d1 + d2 + carry;
            switch (sum) {
            case 0:
                binary[i] = 0;
                break;
            case 1:
                binary[i] = 1;
                carry = 0;
                break;
            case 2:
                binary[i] = 0;
                carry = 1;
                break;
            case 3:
                binary[i] = 1;
                carry = 1;
                break;
            }
        }
        if (((type) && signFirst == 0 && signSecond == 0 && binary[0] == 1) || ((type) && signFirst == 1 && signSecond == 1 && binary[0] == 0)) {
            throw 1;
        }
    }

    void subtraction(Binary num) {
        num.changeSign();
        addition(num, true);
    }

    void multiplication(Binary num)
    {
        if (lowBorder()) {
            for (int i = 0; i < size - 1; i++) {
                if (num.binary[i] != 0) { 
                    throw 1;
                }
            }
            if (num.binary[size - 1] == 0) { 
                binary[0] = 0;
            }
        }
        else {
            if (num.lowBorder()) {
                for (int i = 0; i < size - 1; i++) {
                    if (binary[i] != 0) {
                        throw 1;
                    }
                }
                if (binary[size - 1] == 0) {
                    num.binary[0] = 0;
                }
            }
            else {
                bool negativity(false), overflow(false);
                if (binary[0] == 1) {
                    changeSign();
                    negativity = !negativity;
                }
                if (num.binary[0] == 1) {
                    num.changeSign();
                    negativity = !negativity;
                }
                int* sndBinary = new int[size];
                for (int i = 0; i < size; i++) {
                    sndBinary[i] = binary[i];
                    binary[i] = 0;
                }
                for (int i = size - 1; i >= 0; i--) {
                    if (sndBinary[i] == 1) {
                        if (overflow) {
                            throw 1;
                        }
                        else {
                            addition(num, false);
                        }
                    }
                    for (int i = 0; i < size; i++) {
                        swap(num.binary[i], num.binary[i + 1]);
                    }
                    if (num.binary[0] == 1) {
                        overflow = true;
                    }
                }
                if (binary[0] == 1) {
                    throw 1;
                }
                if (negativity) {
                    int temp(1);
                    for (int i = 0; i < size; i++) {
                        binary[i] == 1 ? binary[i] = 0 : binary[i] = 1;
                    }
                    for (int i = size - 1; i >= 0; i--) {
                        if (binary[i] == 1 && temp == 1) {
                            binary[i] = 0;
                        }
                        else if (binary[i] == 0 && temp == 1) {
                            binary[i] = 1;
                            temp = 0;
                        }
                        else {
                            binary[i] = binary[i];
                        }
                    }
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << binary[i];
        }
        cout << " ";
    }

    int inDecimal() {
        int result(0);
        int* sndBinary = new int[size];
        for (int i = 0; i < size; i++) {
            sndBinary[i] = binary[i];
        }
        if (sndBinary[0] == 1) {
            for (int i = 0; i < size; i++) {
                sndBinary[i] == 1 ? sndBinary[i] = 0 : sndBinary[i] = 1;
            }
            for (int i = 0; i < size; i++) {
                result += sndBinary[i] * pow(2, (size - i - 1));
            }
            result = (result + 1) * (-1);
        }
        else {
            for (int i = 0; i < size; i++) {
                result += sndBinary[i] * pow(2, (size - i - 1));
            }
        }
        delete[] sndBinary;
        return result;
    }
};

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        struct Node *next;
    };
    struct Node *top;
public:
    Stack() {
        top = NULL;
    }

    /*struct Node {
        T data;
        struct Node* next;
    };
    struct Node* top; 
    */

    void push(T value) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = value;
        newnode->next = top;
        top = newnode;
    }

    T pop() {
        if (top == NULL) {
            throw - 1;
        }
        else {
            T temp = T(0);
            temp = top->data;
            top = top->next;
            return temp;
        }
    }
};

void checkInput(string expr) {
    int spaces(0);
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') spaces += 1;
    }
    int numberOfOperators(0), minusesOfNumber(0);

    // проверка первого символа (должен быть числом или унарным минусом)
    if ((((expr[0] == '-') && (!isdigit(expr[1]))) || (expr[0] == '*') || (expr[0] == '+') || (expr[0] == ' '))) {
        throw - 1;
    }

    // подсчет унарных минусов 
    for (int i = 0; i < expr.length(); i++) {
        if ((i != (expr.length() - 1)) && (expr[i] == '-') && (isdigit(expr[i + 1]))) {
            minusesOfNumber += 1;
        }
        else {
            // если встречается недопустимый символ или если последний символ - не оператор
            if ((((isdigit(expr[i]) == 0) && (expr[i] != ' ') && (!((expr[i] == '*') || (expr[i] == '-') || (expr[i] == '+'))))) || ((i == expr.length() - 1) && (expr[i] != '+') && (expr[i] != '*') && (expr[i] != '-'))) {
                throw - 1;
            }
        }
    }

    // проверка на пробелы между операторами (должен быть пробел до и после оператора)
    for (int i = 1; i < expr.length() - 1; i++) {
        if (((expr[i] == '+') || (expr[i] == '*') || ((expr[0] == '-') && (!isdigit(expr[1])))) && ((expr[i - 1] != ' ') && (expr[i + 1] != ' '))) throw - 1;
    }
    
    // подсчет всех операторов
    for (int i = 0; i < expr.length(); i++) {
        if ((expr[i] == '*') || (expr[i] == '-') || (expr[i] == '+')) {
            numberOfOperators += 1;
        }
        // проверка на отсутствие операторов внутри числа
        if (isdigit(expr[i])) {
            for (int j = i; j < expr.length(); j++) {
                if ((!(isdigit(expr[j]))) && (expr[j] != ' ')) {
                    throw - 1;
                }
                else if ((!(isdigit(expr[j]))) && (expr[j] == ' ')) {
                    break;
                }
            }
        }
    }

    numberOfOperators = numberOfOperators - minusesOfNumber;
    // проверка количества операторов (должно быьб в два раза меньше, чем пробелов)
    if (numberOfOperators != (spaces / 2)) {
        throw - 1;
    }

    // проверка на наличие чисел и операторов
    bool areThereOperators(false), areThereOperands(false);
    for (int i = 0; i < expr.length(); i++) {
        if (isdigit(expr[i])) {
            areThereOperands = true;
        }
    }
    if (numberOfOperators != 0) {
        areThereOperators = true;
    }
    if ((areThereOperands == false) || (areThereOperators == false)) {
        throw - 1;
    }
}

void operation(Stack<Binary>& numbers, string expr, int i, Binary firstNum, Binary secondNum) {
    secondNum = numbers.pop();
    firstNum = numbers.pop();
    switch (expr[i]) {
    case '+':
        firstNum.addition(secondNum, true);
        break;
    case '-':
        firstNum.subtraction(secondNum);
        break;
    case '*':
        firstNum.multiplication(secondNum);
        break;
    }
    numbers.push(firstNum);
}

Binary getResult(Stack<Binary>& numbers, string expr, bool toContinue) {
    Binary temp = Binary(0);
    Binary firstNum(Binary(0)), secondNum(Binary(0));

    for (int i = 0; i < expr.length() - 1; i++) {
        if ((isdigit(expr[i])) || ((expr[i] == '-') && (isdigit(expr[i + 1])))) {
            for (int j = i; j < expr.length() - 1; j++) {
                if (expr[j] == ' ') {
                    temp = Binary(stoi(expr.substr(i, (j - i))));
                    if (!toContinue) {
                        break;
                    }
                    numbers.push(temp);
                    i = j - 1;
                    break;
                }
                else {
                    continue;
                }
            }
        }
        else if (((expr[i] == '*') || ((expr[i] == '-') && (!isdigit(expr[i + 1]))) || (expr[i] == '+')) && toContinue) {
                operation(numbers, expr, i, firstNum, secondNum);
        }
    }
    operation(numbers, expr, expr.length() - 1, firstNum, secondNum);
    return numbers.pop();
}

void expressionToBinary(/*Stack<Binary>& values,*/ string expr) {
    Binary temp = Binary(0);
    for (int i = 0; i < expr.length(); i++) {
        if ((isdigit(expr[i])) || ((expr[i] == '-') && (isdigit(expr[i + 1])))) {
            for (int j = i; j < expr.length() - 1; j++) {
                if (expr[j] == ' ') {
                    temp = Binary(stoi(expr.substr(i, (j - i))));
                    temp.print();
                    i = j - 1;
                    break;
                }
                else {
                    continue;
                }
            }
        }
        else if ((expr[i] == '*') || ((expr[i] == '-') && (!isdigit(expr[i + 1]))) || (expr[i] == '+')) {
            cout << expr[i] << ' ';
        }
    }
}

int main() {
    bool toContinue;
    Stack<Binary> numbers;
    string expr;
    Binary result(Binary(0));
    do {
        cout << "Write the expression in Reverse Polish Notation:\n";
        getline(cin, expr);
        try {
            toContinue = true;
            checkInput(expr);
            if (toContinue == true) {
                result = getResult(numbers, expr, toContinue);
            }
        }
        catch (int whichType) {
            switch (whichType) {
            case -1:
                cout << "\nException: the expression is written incorrectly.\n" << endl;
                toContinue = false;
                break;
            case 0:
                cout << "\nException: overflow of a given number" << endl;
                toContinue = false;
                break;
            case 1:
                cout << "\nException: overflow of the result" << endl;
                toContinue = false;
                break;
            }
        }
    } while (toContinue == false);
    cout << "The written expression in binary is: \n";
    expressionToBinary(/*numbers, */ expr);
    cout << "\nThe result is: " << result.inDecimal() << endl;
    cout << "The result in binary is: ";
    result.print(); cout << endl;
}