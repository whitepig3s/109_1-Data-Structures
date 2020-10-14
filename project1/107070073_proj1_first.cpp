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

bool table[15][40]{false};

//blocks
bool T1_arr[4][4]{
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool T2_arr[4][4]{
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0};
bool T3_arr[4][4]{
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool T4_arr[4][4]{
    1, 0, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0};
bool L1_arr[4][4]{
    1, 1, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0};
bool L2_arr[4][4]{
    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool L3_arr[4][4]{
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0};
bool L4_arr[4][4]{
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool J1_arr[4][4]{
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0};
bool J2_arr[4][4]{
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool J3_arr[4][4]{
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0};
bool J4_arr[4][4]{
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool S1_arr[4][4]{
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool S2_arr[4][4]{
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0};
bool Z1_arr[4][4]{
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool Z2_arr[4][4]{
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0};
bool I1_arr[4][4]{
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0};
bool I2_arr[4][4]{
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
bool O_arr[4][4]{
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};

bool ref[4][4]{false};

void clear_ref()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ref[i][j] = false;
}

void ref_cpy(bool block[][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ref[i][j] = block[i][j];
}

void ref_print()
{
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
            cout << ref[i][j] << ' ';
        cout << endl;
    }
}

//int find(int p, int n /*row*/) //return 在個row可以停下來
//{                              //找哪邊可以放
//while ()
//{
/* code */
//}
/*for (int i = m-1; i >=0; i--)
    {
        for (int j = 0; j < n; j++
        )
            //cout << i * 10 + j << " ";
            cout << *(table+i * n + j )<< " ";
    }*/
//}

int main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*row*/, n /*column*/;
    file >> m >> n;

    /*bool *table = new bool[m * n]; //declare dynamic 2D arr
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            *(table + i * n + j) = false;*/

    /*for (int i = 0; i < m; i++) //print array
    {
        for (int j = 0; j < n; j++)
            cout << *(table + i * n + j) << " ";
        cout << endl;
    }*/

    /*for (int i = m-1; i >=0; i--) //re print array
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
            clear_ref();

            if (v[0].compare("T1") == 0)
            {
                ref_cpy(T1_arr);
            }
            else if (v[0].compare("T2") == 0)
            {
                ref_cpy(T2_arr);
            }
            else if (v[0].compare("T3") == 0)
            {
                ref_cpy(T3_arr);
            }
            else if (v[0].compare("T4") == 0)
            {
                ref_cpy(T4_arr);
            }
            else if (v[0].compare("L1") == 0)
            {
                ref_cpy(L1_arr);
            }
            else if (v[0].compare("L2") == 0)
            {
                ref_cpy(L2_arr);
            }
            else if (v[0].compare("L3") == 0)
            {
                ref_cpy(L3_arr);
            }
            else if (v[0].compare("L4") == 0)
            {
                ref_cpy(L4_arr);
            }
            else if (v[0].compare("J1") == 0)
            {
                ref_cpy(J1_arr);
            }
            else if (v[0].compare("J2") == 0)
            {
                ref_cpy(J2_arr);
            }
            else if (v[0].compare("J3") == 0)
            {
                ref_cpy(J3_arr);
            }
            else if (v[0].compare("J4") == 0)
            {
                ref_cpy(J4_arr);
            }
            else if (v[0].compare("S1") == 0)
            {
                ref_cpy(S1_arr);
            }
            else if (v[0].compare("S2") == 0)
            {
                ref_cpy(S2_arr);
            }
            else if (v[0].compare("Z1") == 0)
            {
                ref_cpy(Z1_arr);
            }
            else if (v[0].compare("JZ") == 0)
            {
                ref_cpy(Z2_arr);
            }
            else if (v[0].compare("I1") == 0)
            {
                ref_cpy(I1_arr);
            }
            else if (v[0].compare("I2") == 0)
            {
                ref_cpy(I2_arr);
            }
            else if (v[0].compare("O") == 0)
            {
                ref_cpy(O_arr);
            }
            
        }
    } while (!file.eof());

    file.close();
    return 0;
}