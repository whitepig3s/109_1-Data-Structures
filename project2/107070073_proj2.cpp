#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

char table[1000][1000] = {0};

void print_table(int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*row*/, n /*column*/, B /*battery*/;
    file >> m >> n >> B;
    string line;
    file.get();
    for (int i = 0; i < m; i++)
    {
        char tmp;
        for (int j = 0; j < n; j++)
        {
            file >> tmp;
            table[i][j] = tmp;
        }
        file.get();
    }
    file.close();
    print_table(m, n);
    ofstream ofile("107070073_proj2", ios::out);

    ofile.close();
    return 0;
}