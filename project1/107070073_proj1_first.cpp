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

int main(int argc, char *argv[])
{
    ifstream file(argv[1], ios::in);
    int m /*column*/, n /*row*/;
    file >> m >> n;
    cout << "column:" << m << endl
         << "rol:" << n<<endl;
    
    string line;
    getline(file, line); //要把換行吃掉
    do
    {
        int point,move;
        getline(file, line);
        if (line != "End")
        {
            vector<string> v;
            v = split(line);
            point=stoi(v[1]);
            move=stoi(v[2]);
            cout<<v[0]<<" "<<point<<" "<<move<<endl;
        }
    }while (!file.eof());

    file.close();
    return 0;
}