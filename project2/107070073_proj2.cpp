#include <iostream>
#include <fstream>
#include <queue>
#include <map>
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

class binary_tree
{
private:
    map<int, int> mp;
    int battery;

    struct Node
    {
        int key, value;
        Node(int key, float value)
            : key(key), value(value)
        {
        }
    };

    struct Comparekey
    {
        bool operator()(Node const &p1, Node const &p2)
        {
            return p1.value > p2.value;
        }
    };

    priority_queue<Node, vector<Node>, Comparekey> Q;
    queue<Node> fwd;
    deque<Node> back;

public:
    int travel;
    int node_r;
    binary_tree(int b, int rm, int rn)
    {
        battery = b;
        travel = 0;
        node_r = rm * 1000 + rn;
    }

    void add_child(int tmp_m, int tmp_n)
    {
        if (table[tmp_m][tmp_n] == '0' || table[tmp_m][tmp_n] == 'R')
        {
            table[tmp_m][tmp_n] = '2';
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
        auto iter = mp.find(key);
        if (iter != mp.end())
        {
            int tmp = mp[key];
            Q.push(Node(key, tmp));
        }
    }

    int select_node(int tmp_k)
    {
        int tmp_n = tmp_k % 1000;
        int tmp_m = tmp_k / 1000;
        find_node(tmp_m + 1, tmp_n);
        find_node(tmp_m, tmp_n + 1);
        find_node(tmp_m - 1, tmp_n);
        find_node(tmp_m, tmp_n - 1);
        Node n = Q.top();
        fwd.push(n);
        back.push_back(n);
        if (n.value == 0)
        {
            travel++;
        }
        mp[n.key]++;
        while (!Q.empty())
        {
            Q.pop();
        }
        if (node_r == n.key)
        {
            while (!back.empty())
            {
                back.pop_back();
            }
        }
        return n.key;
    }

    void route(int tmp_m, int tmp_n)
    {
        int k = tmp_m * 1000 + tmp_n;
        mp[k]++;
        while (fwd.size() + back.size() + 1 <= battery)
        {
            int tmp = select_node(k);
            k = tmp;
            if (travel == size())
            {
                break;
            }
        }
    }

    void write_route(int rm, int rn)
    {
        back.pop_back();
        ofstream tmpfile("tmp", ios::app);
        tmpfile << rm * 1000 + rn << endl;
        int tmp_k;
        while (!fwd.empty())
        {
            tmpfile << fwd.front().key << endl;
            fwd.pop();
        }
        while (!back.empty())
        {
            tmpfile << back.back().key << endl;
            back.pop_back();
        }
        tmpfile.close();
    }

    void clear_queue()
    {
        while (!fwd.empty())
        {
            fwd.pop();
        }
        while (!back.empty())
        {

            back.pop_back();
        }
    }

    void print(void)
    {
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }
    }

    void print_zero(void)
    {
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
            if (it->second == 0)
                cout << it->first << " " << it->second << endl;
        }
    }

    int size()
    {
        return mp.size() - 1;
    }
};

main(int argc, char *argv[])
{
    //----------input file
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
    //==========input file

    //----------build_tree && build_route
    binary_tree tree(B, Rm, Rn);
    tree.add_child(Rm, Rn);
    int count = 0, last_count = 0;
    while (tree.travel < tree.size())
    {
        count = tree.travel;
        tree.route(Rm, Rn);
        if (count > last_count)
            tree.write_route(Rm, Rn);
        else if (tree.travel == tree.size())
            tree.write_route(Rm, Rn);
        else
            tree.clear_queue();
        last_count = count;
    }
    //===========build_tree && build_route

    //-----------計算行數
    string tmps;
    int lines = 0;
    ifstream fin("tmp", ios::in);
    while (getline(fin, tmps))
    {
        lines = lines + 1;
    }
    fin.close();
    //===========計算行數

    //-----------寫入檔案
    ofstream ofile("107070073_proj2", ios::out);
    ifstream f("tmp", ios::in);
    ofile << lines << endl;
    int c = 0;
    for (int i = 0; i < lines; i++)
    {
        int tmp_k;
        f >> tmps;
        tmp_k = stoi(tmps);
        int tmp_n = tmp_k % 1000;
        int tmp_m = tmp_k / 1000;
        ofile << tmp_m << " " << tmp_n << endl;
    }
    f.close();
    ofile << Rm << " " << Rn;
    ofile.close();
    remove("tmp");
    //===========寫入檔案

    return 0;
}