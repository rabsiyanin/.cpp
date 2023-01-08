#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    using namespace std;
    double result;
    if (argc > 3 && !(argc % 2))
    {
        result = atof(argv[1]);
            for (int i = 2; i < argc; i += 2)
            {
                if (*argv[i] == '+') result += atof(argv[i+1]);
                else if (*argv[i] == '-') result -= atof(argv[i+1]);
                else if (*argv[i] == '*' || *argv[i] == 'x')  result *= atof(argv[i+1]);
                else if (*argv[i] == '/' || *argv[i] == ':')
                {
                    if (atof(argv[i+1])) result /= atof(argv[i+1]);
                    else
                    {
                        cout << "Zero as denominator.\n";
                        exit(0);
                    }
                }
                else
                {
                    cout << "Invalid operation.\n";
                    exit(0);
                }
            }
        cout << "The result is: " << result << endl;
    }
    else cout << "Invalid input.\n";
    return 0;
}