#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{

    double sum;
    if (argc == 1)
    {
        cout << "Please input numbers to find average.";
    }
    else
    {

        for (int i = 0; i < argc - 1; i++)
        {
            sum += atof(argv[i + 1]);
        }
        cout << "---------------------------------" << endl;
        cout << "Average of " << argc - 1 << " numbers"
             << " "
             << "= " << sum / (argc - 1) << "\n";
        cout << "---------------------------------";
    }
}
