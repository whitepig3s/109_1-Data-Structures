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
bool T1_arr[2][3]{
    0, 1, 0,
    1, 1, 1};
bool T2_arr[3][2]{
    0, 1,
    1, 1,
    0, 1};
bool T3_arr[2][3]{
    1, 1, 1,
    0, 1, 0};
bool T4_arr[3][2]{
    1, 0,
    1, 1,
    1, 0};
bool L1_arr[3][2]{
    1, 1,
    1, 0,
    1, 0};
bool L2_arr[2][3]{
    1, 0, 0,
    1, 1, 1};
bool L3_arr[3][2]{
    1, 0,
    1, 0,
    1, 1};
bool L4_arr[2][3]{
    1, 1, 1,
    0, 0, 1};
bool J1_arr[3][2]{
    1, 1,
    0, 1,
    0, 1};
bool J2_arr[2][3]{
    1, 1, 1,
    1, 0, 0};
bool J3_arr[3][2]{
    1, 0,
    1, 0,
    1, 1};
bool J4_arr[2][3]{
    0, 0, 1,
    1, 1, 1};
bool S1_arr[2][3]{
    1, 1, 0,
    0, 1, 1};
bool S2_arr[3][2]{
    0, 1,
    1, 1,
    1, 0};
bool Z1_arr[2][3]{
    0, 1, 1,
    1, 1, 0};
bool Z2_arr[3][2]{
    1, 0,
    1, 1,
    0, 1};
bool I1_arr[4][1]{
    1,
    1,
    1,
    1};
bool I2_arr[1][4]{
    1,
    1,
    1,
    1};
bool O_arr[2][2]{
    1, 1,
    1, 1};

/*enum blocks {
    T1,T2,T3,T4,
    L1,L2,L3,L4,
    J1,J2,J3,J4,
    S1,S2,
    Z1,Z2,
    I1,I2,
    O
};*/

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

    /*for (int i = m-1; i >=0; i--)
    {
        for (int j = 0; j < n; j++)
            //cout << i * 10 + j << " ";
            cout << *(table+i * n + j )<< " ";
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
            if (v[0].compare("O")==0)
                cout<<"test";



                

        }
    } while (!file.eof());

    file.close();
    return 0;
}