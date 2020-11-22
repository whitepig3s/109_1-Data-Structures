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
    int travel;

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
    queue<Node> back;

public:
    binary_tree(int b)
    {
        battery = b;
        travel = 0;
    }
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
        auto iter = mp.find(key);
        if (iter != mp.end())
        {
            int tmp = mp[key];
            Q.push(Node(key, tmp));
        }
    }

    //int add_node(int tmp_m, int tmp_n)
    int add_node(int tmp_k)
    {
        int tmp_n = tmp_k % 1000;
        int tmp_m = tmp_k / 1000;
        find_node(tmp_m + 1, tmp_n);
        find_node(tmp_m, tmp_n + 1);
        find_node(tmp_m - 1, tmp_n);
        find_node(tmp_m, tmp_n - 1);
        Node n = Q.top();
        fwd.push(n);
        back.push(n);
        if (n.value == 0)
        {
            travel++;
        }
        mp[n.key]++;
        //cout<<n.key<<" "<<mp[n.key]<<endl;
        cout << "Q" << endl;
        while (!Q.empty())
        {
            cout << Q.top().key <<" "<<Q.top().value<< endl;
            Q.pop();
        }
        cout << endl;
        //cout << n.key << " " << n.value << endl;
        return n.key;
    }

    void route(int tmp_m, int tmp_n)
    {
        int k = tmp_m * 1000 + tmp_n;
        mp[k]++;
        while (fwd.size() + back.size() <= battery)
        {
            int tmp = add_node(k);
            k = tmp;
        }
        /*while (!fwd.empty())
        {
            cout << fwd.front().key << endl;
            fwd.pop();
        }*/
    }

    void print(void)
    {
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }
    }

    int not_empty()
    {
        int tmp = mp.empty();
        return !tmp;
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

    binary_tree tree(B);
    //print_table(m, n);
    tree.add_child(Rm, Rn);
    tree.route(Rm, Rn);
    /*while (tree.not_empty())
    {
        tree.route(Rm, Rn);
    }*/

    //tree.print();
    //ofstream ofile("107070073_proj2", ios::out);

    //ofile.close();
    return 0;
}