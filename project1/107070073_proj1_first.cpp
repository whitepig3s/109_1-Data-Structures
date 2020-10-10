#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*column*/, n /*row*/;
    file >> m >> n;
    cout << "column:" << m << endl
         << "rol:" << n;

    int a, b;
    string line;
    do
    {
        getline(file, line);
        if (line != "End")
        {
            
        }
    } while (!file.eof());

    file.close();
    return 0;
}