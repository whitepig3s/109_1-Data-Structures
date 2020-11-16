#include <iostream>
#include <fstream>
#include <string>
//#include <vector>
#include <sstream>
#include <stack>
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
        bool exist = 0;
        if (table[tmp_m][tmp_n] == '0' || table[tmp_m][tmp_n] == 'R')
        {
            bool exist = 1;
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
        cout << "add_child" << endl;
        int last = -1;
        int first = 4;
        for (int i = 0; i < 4; i++)
        {
            if (n[i].exist == true)
            {
                if (first == 4)
                {
                    first = i;
                }
                else
                {
                    n[last].sibling = &n[i];
                }
                last = i;
            }
        }
        if (first < 4)
            return n[first];
        else
            return n[0];
    }

    void build_tree(int rm, int rn)
    {
        root = add_Node(rm, rn);
        Node c = add_child(rm, rn);
        root.child = &c;
        //cout << (root.child)->node_m << " " << (root.child)->node_n<< endl;
    }

    void print(void)
    {
        printInorder(&root);
        //cout << root.node_m << " " << root.node_n << endl;
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
    //print_table(m, n);
    ofstream ofile("107070073_proj2", ios::out);

    ofile.close();
    return 0;
}