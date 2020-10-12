#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<string> split(string str)
{
    istringstream in(str);
    string tmp_str;
    vector<string> vec;
    while (in >> tmp_str)
        vec.push_back(tmp_str);

    return vec;
}

//blocks
bool T1[2][3]{
    0, 1, 0,
    1, 1, 1};
bool T2[3][2]{
    0, 1,
    1, 1,
    0, 1};
bool T3[2][3]{
    1, 1, 1,
    0, 1, 0};
bool T4[3][2]{
    1, 0,
    1, 1,
    1, 0};
bool L1[3][2]{
    1, 1,
    1, 0,
    1, 0};
bool L2[2][3]{
    1, 0, 0,
    1, 1, 1};
bool L3[3][2]{
    1, 0,
    1, 0,
    1, 1};
bool L4[2][3]{
    1, 1, 1,
    0, 0, 1};
bool J1[3][2]{
    1, 1,
    0, 1,
    0, 1};
bool J2[2][3]{
    1, 1, 1,
    1, 0, 0};
bool J3[3][2]{
    1, 0,
    1, 0,
    1, 1};
bool J4[2][3]{
    0, 0, 1,
    1, 1, 1};
bool I1[4][1]{
    1,
    1,
    1,
    1};
bool I2[1][4]{
    1,
    1,
    1,
    1};
bool O[2][2]{
    1, 1,
    1, 1};

int main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*row*/, n /*column*/;
    file >> m >> n;
    /*cout << "row:" << m << endl
         << "column:" << n << endl;*/

    bool *table = new bool[m * n]; //declare dynamic 2D arr
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            *(table + i * n + j) = false;

    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cout << *(table + i * n + j) << " ";
        cout << endl;
    }*/

    string line;
    getline(file, line); //要把換行吃掉
    do
    {
        int point, move;
        getline(file, line);
        if (line != "End")
        {
            vector<string> v; //v[0] block symbol
            v = split(line);
            point = stoi(v[1]);
            move = stoi(v[2]);
            //cout << v[0] << " " << point << " " << move << endl;
        }
    } while (!file.eof());

    file.close();
    return 0;
}