#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

char table[1000][1000] = {0};

int t_m, t_n;

queue<struct Node> nodequeue;

void print_table(int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
}

struct Node
{
    bool exist;
    int node_n, node_m;
    Node *child, *sibling;
};

class binary_tree
{
private:
    Node root;
    Node blackhole;
    bool full;

public:
    Node add_Node(int tmp_m, int tmp_n)
    {
        Node *tmp = new Node;
        tmp->node_m = tmp_m;
        tmp->node_n = tmp_n;
        tmp->child = NULL;
        tmp->sibling = NULL;
        tmp->exist = 0;
        if (tmp_m < t_m && tmp_n < t_n && tmp_m >= 0 && tmp_n >= 0)
        {
            if (table[tmp_m][tmp_n] == '0')
            {
                tmp->exist = 1;
            }
        }
        return *tmp;
    }

    Node add_child(int tmp_m, int tmp_n)
    {
        full = 0;
        Node n[4];
        n[0] = add_Node(tmp_m + 1, tmp_n);
        n[1] = add_Node(tmp_m, tmp_n + 1);
        n[2] = add_Node(tmp_m, tmp_n - 1);
        n[3] = add_Node(tmp_m - 1, tmp_n);
        int last = -1;
        int first = 4;
        for (int i = 0; i < 4; i++)
        {
            if (n[i].exist == 1 && table[n[i].node_m][n[i].node_n] == '0')
            {
                nodequeue.push(n[i]);
                cout << n[i].node_m << " " << n[i].node_n << " " << endl;
                if (first == 4)
                {
                    first = i;
                }
                else
                {
                    n[last].sibling = &n[i];
                }
                last = i;
                table[n[i].node_m][n[i].node_n] = '2';
            }
        }
        //cout <<tmp_m<<" "<<tmp_n<<" "<<nodequeue.size() << endl;  //加了這行就可以運作正常
        cout<<"re"<<endl;
        if (first < 4)
            return n[first];
        else
        {
            cout<<"test"<<endl;
            full = 1;
            //return *(n[0].child); //return NULL
            return blackhole;
        }
    }

    void build_tree(int rm, int rn)
    {
        root.node_m = rm;
        root.node_n = rn;
        Node c = add_child(rm, rn);
        root.child = &c;
        while (!nodequeue.empty())
        {
            Node n = nodequeue.front();
            cout<<"fornt "<<n.node_m<<" "<<n.node_n<<endl;
            c = add_child(n.node_m, n.node_n);
             cout<<"test2"<<endl;
            if (full == 0)
            {
                //c = add_child(n.node_m, n.node_n);
                n.child = &c;
            }
            nodequeue.pop();
        }
    }

    void print(void)
    {
        printInorder(&root);
    }

    void printInorder(Node *node)
    {
        if (node == NULL)
            return;
        printInorder(node->sibling);
        cout << node->node_m << " " << node->node_n << endl;
        printInorder(node->child);
    }
};

main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*row*/, n /*column*/, B /*battery*/;
    file >> m >> n >> B;
    t_m = m;
    t_n = n;
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
    tree.build_tree(Rm, Rn);
    //tree.print();
    print_table(m, n);
    //ofstream ofile("107070073_proj2", ios::out);

    //ofile.close();
    return 0;
}