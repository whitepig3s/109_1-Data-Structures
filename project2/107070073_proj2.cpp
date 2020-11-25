#include <iostream>
#include <fstream>
#include <queue>
#include <map>
using namespace std;

class binary_tree
{
private:
    map<int, int> mp;
    int battery;
    int node_r;

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
    binary_tree(int b)
    {
        battery = b;
        travel = 0;
    }

    int trans(int tmp_m, int tmp_n)
    {
        return tmp_m * 1000 + tmp_n;
    }

    void set_Root(int rm, int rn)
    {
        node_r = trans(rm, rn);
    }

    void add_node(int tmp_m, int tmp_n)
    {
        mp[trans(tmp_m, tmp_n)] = 0;
    }

    void find_node(int tmp_m, int tmp_n)
    {
        int key = trans(tmp_m, tmp_n);
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
            travel++;
        mp[n.key]++;
        while (!Q.empty())
            Q.pop();
        if (node_r == n.key)
        {
            while (!back.empty())
                back.pop_back();
        }
        return n.key;
    }

    void route(int tmp_m, int tmp_n)
    {
        int k = trans(tmp_m, tmp_n);
        mp[k]++;
        while (fwd.size() + back.size() + 1 <= battery)
        {
            int tmp = select_node(k);
            k = tmp;
            if (travel == size())
                break;
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
            fwd.pop();
        while (!back.empty())
            back.pop_back();
    }

    void print(void)
    {
        for (auto it = mp.begin(); it != mp.end(); it++)
            cout << it->first << " " << it->second << endl;
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
    file.get();
    binary_tree tree(B);
    int Rm, Rn;
    for (int i = 0; i < m; i++)
    {
        char tmp;
        for (int j = 0; j < n; j++)
        {
            file >> tmp;
            if (tmp == '0' || tmp == 'R')
            {
                tree.add_node(i, j);
                if (tmp == 'R')
                {
                    Rm = i;
                    Rn = j;
                }
            }
        }
        file.get();
    }
    tree.set_Root(Rm, Rn);
    file.close();
    //==========input file

    //----------build_route
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
    //===========build_route

    //-----------計算行數
    string tmps;
    count = 0;
    ifstream fin("tmp", ios::in);
    while (getline(fin, tmps))
        count++;
    fin.close();
    //===========計算行數

    //-----------寫入檔案
    ofstream ofile("107070073_proj2", ios::out);
    ifstream f("tmp", ios::in);
    ofile << count << endl;
    for (int i = 0; i < count; i++)
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