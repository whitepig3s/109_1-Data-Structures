#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
using namespace std;

char table[1000][1000] = {0};

//queue<struct Node> nodequeue;

void print_table(int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
}

class binary_tree
{
private:
    map<int, int> mp;

public:
    void add_child(int tmp_m, int tmp_n)
    {
        if (table[tmp_m][tmp_n] == '0' || table[tmp_m][tmp_n] == 'R')
        {
            table[tmp_m][tmp_n] = '2';
            //cout << tmp_m << " " << tmp_n << endl;
            mp[tmp_m * 1000 + tmp_n] = 0;
            add_child(tmp_m + 1, tmp_n);
            add_child(tmp_m, tmp_n + 1);
            add_child(tmp_m - 1, tmp_n);
            add_child(tmp_m, tmp_n - 1);
        }
        return;
    }

    void find_node(int tmp_m, int tmp_n)
    {
        int key = tmp_m * 1000 + tmp_n;

    }

    void print(void)
    {
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }
    }
};

main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*row*/, n /*column*/, B /*battery*/;
    file >> m >> n >> B;
    string line;
    file.get();
    int Rm, Rn;
    for (int i = 0; i < m; i++)
    {
        char tmp;
        for (int j = 0; j < n; j++)
        {
            file >> tmp;
            table[i][j] = tmp;
            if (tmp == 'R')
            {
                Rm = i;
                Rn = j;
            }
        }
        file.get();
    }
    file.close();
    binary_tree tree;
    //print_table(m, n);
    tree.add_child(Rm, Rn);
    //tree.print();
    //ofstream ofile("107070073_proj2", ios::out);

    //ofile.close();
    return 0;
}