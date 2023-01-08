/*Реализация операций по упаковке шестнадцатеричного дампа вещественного числа (float) в 
символьный одномерный массив и распаковке этого массива для получения исходного вещественного числа в 
рамках 32-разрядной архитектуры. Обработка нуля на входе приводит к выводу inf, потому что мы не можем восстановить 0 из шестнадцатеричного дампа.*/

#include <iostream>
#include <math.h>

using namespace std;


// Проверка на ввод

template <typename T>
T safetyEnter()
{
    T input(0.0);
    cout << "Enter the digit >> ";
    cin >> input;
    do
    {
        if (cin.good())
            break;
        else
        {
            cout << "Invalid input!\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while (1);

    return input;
}


// Вывод дампа

template <typename T>
void print(char* p)
{
    int size(2 * sizeof(T));

    for (int i = 0; i < size; i++) cout <<  p[size - i - 1];
    cout << endl;
}


// Шестнадцатеричный дамп для хранения числа с плавающей точкой

void hexdump(short int n, char* p)
{
    short int mask(0xf00); // bit mask.
    short int digit((n >> 12) & 0xf);

    p[3] = digit > 9 ? char(digit + 87) : char(digit + 48);
    for (int i = 0; i < 3; i++, mask >>=4)
    {
        digit = (n & mask) >> (8 - i * 4);
        p[3 - i - 1] = digit > 9 ? char(digit + 87) : char(digit + 48);
    }
}


// Функция перевода дампа в массив

template <typename T>
void pack(T* pFloat, char* p)
{
    short int* pShort = reinterpret_cast<short int*>(pFloat);
    int size(sizeof(T) / sizeof(short int));
    int index;

    for (int i = 0; i < size; i++)
    {
        index = size - i - 1;
        hexdump(pShort[index], p + 4 * index);
    }
    cout << endl;
}


// Функция распаковки

void unpack(char* p) {
    int size(2 * sizeof(float)); // Размер массива
    float M(0); // Мантиса
    unsigned int raw = 0; // Дополнительная переменная для удобства подбора битов
    unsigned int sign; // Старший разряд

    // Вывод знаков по таблице ASCII

    for (int i = 0; i < size; i++) {
        raw <<= 4;
        if (p[size - i - 1] >= 97)
            raw |= p[size - i - 1] - 97 + 10;
        else
            raw |= p[size - i - 1] - 48;
    }

    sign = raw & 0x80000000; // побитово умножаем упакованный raw, чтобы оставить только знак
    sign >>= 31;
    raw <<= 1; 
    unsigned int E = raw & 0xFF000000; // экспонента
    E >>= 24;
    E -= 127; // по формуле
    raw <<= 8; // сдвиг экспоненты для просмотра мантисы
    int iter = 0;
    while(raw != 0) {
        iter++;
        if ((raw & 0x80000000) != 0)
            M += pow(2.f, (float)-iter);
        raw <<= 1;
    }

    // Формулы взяты из документа
    float result = pow(-1.f, (float)sign) * (1 + M) * pow(2.f, (float)E);
    cout << "Sign >> " << sign << endl; 
    cout << "Exponent >> " << scientific << E << endl; 
    cout << "Mantis >> " << M << endl; 
    cout << "Result >> " << result << endl;
}

int main()
{
    char* pArray;
    float f;
    f = safetyEnter<float>();
    pArray = new char[2* sizeof(float)];
    pack<float>(&f, pArray);
    print<float>(pArray);
    unpack(pArray);

    return 0;
}