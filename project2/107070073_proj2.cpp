#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

int time = 0;

char table[1000][1000] = {0};

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

public:
    Node add_Node(int tmp_m, int tmp_n)
    {
        Node *tmp = new Node;
        tmp->node_m = tmp_m;
        tmp->node_n = tmp_n;
        tmp->child = NULL;
        tmp->sibling = NULL;
        tmp->exist = 0;
        if (table[tmp_m][tmp_n] == '0' || table[tmp_m][tmp_n] == 'R')
        {
            tmp->exist = 1;
        }
        return *tmp;
    }

    Node add_child(int tmp_m, int tmp_n)
    {
        Node n[4];
        n[0] = add_Node(tmp_m + 1, tmp_n);
        n[1] = add_Node(tmp_m, tmp_n + 1);
        n[2] = add_Node(tmp_m, tmp_n - 1);
        n[3] = add_Node(tmp_m - 1, tmp_n);
        int last = -1;
        int first = 4;
        for (int i = 0; i < 4; i++)
        {
            if (n[i].exist == 1 && table[tmp_m][tmp_n] != '2')
            {
                nodequeue.push(n[i]);
                if (first == 4)
                {
                    first = i;
                }
                else
                {
                    n[last].sibling = &n[i];
                }
                last = i;
                table[tmp_m][tmp_n] = '2';
            }
        }
        if (first < 4)
            return n[first];
        else
            return *(n[0].child); //return NULL
    }
    void recursion()
    {
        while (!nodequeue.empty())
        {
            Node n = nodequeue.front();
            cout << n.node_m << " " << n.node_n << endl;
            Node c = add_child(n.node_m, n.node_n);
            n.child = &c;
            nodequeue.pop();
        }
    }

    void build_tree(int rm, int rn)
    {
        root = add_Node(rm, rn);
        Node c = add_child(rm, rn);
        root.child = &c;
        recursion();
        //cout << (root.child)->node_m << " " << (root.child)->node_n<< endl;
    }

    void print(void)
    {
        printInorder(&root);
    }

    void printInorder(Node *node)
    {
        if (node == NULL)
            return;
        time++;
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
    tree.print();
    cout << time << endl;

    //ofstream ofile("107070073_proj2", ios::out);

    //ofile.close();
    return 0;
}