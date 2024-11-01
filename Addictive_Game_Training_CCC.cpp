#include <iostream>
#include <stack>
#include <string>
#include <fstream>
using namespace std;
ofstream fout("rezultat.txt");
int a[50][50], aux[50][50], loc_a[100], loc_b[100];
int size_a, size_b;
int nr_puncte;//linii coloane
int dl[] = { -1, 0, 1, 0 };
int dc[] = { 0, -1, 0, 1 };
stack<string> stiva;
int lungimi[100];
int ok, im;
void PrintStack(stack<string> s)
{
    if (s.empty())
        return;
    string x = s.top();
    s.pop();
    PrintStack(s);
    if (isdigit(x[0]) == false)
    {
        ok++;
    }
    else
    {
        ok = 0;
    }
    if (ok == 1)
    {
        im++;
        fout << lungimi[im] << " ";
    }

    cout << x << " ";
    s.push(x);
}
bool plin(int a[50][50])
{
    for (int i = 0; i < size_a; i++)
    {
        for (int j = 0; j < size_b; j++)
        {
            if (a[i][j] == 0)
                return false;
        }
    }
    return true;
}
void solve(int culoare, int i, int j, int a[50][50])
{
    if (i == (loc_b[culoare] - 1) / size_b && j == (loc_b[culoare] - 1) % size_b && culoare == nr_puncte / 2)
    {
        //cout << "1" << endl << endl;
        if (plin(a) == true)
        {
            PrintStack(stiva);
            return;
        }
    }
    else if (i == (loc_b[culoare] - 1) / size_b && j == (loc_b[culoare] - 1) % size_b)
    {
        //cout << "2" << endl;
        int new_i = (loc_a[culoare + 1] - 1) / size_b;
        int new_j = (loc_a[culoare + 1] - 1) % size_b;
        stiva.push(to_string(culoare + 1));
        stiva.push(to_string(loc_a[culoare + 1]));
        solve(culoare + 1, new_i, new_j, a);
        stiva.pop();
        stiva.pop();
    }
    else
    {
        for (int index = 0; index < 4; index++)
        {
            //cout << "3";
            int new_i = i + dl[index];
            int new_j = j + dc[index];
            if (new_i < size_a && new_i >= 0 && new_j < size_b && new_j >= 0 && (a[new_i][new_j] == 0 || (new_i == (loc_b[culoare] - 1) / size_b && new_j == (loc_b[culoare] - 1) % size_b)))
            {
                lungimi[culoare]++;
                a[i][j] = culoare;
                if (index == 0)
                {
                    stiva.push("N");
                }
                if (index == 1)
                {
                    stiva.push("W");
                }
                if (index == 2)
                {
                    stiva.push("S");
                }
                if (index == 3)
                {
                    stiva.push("E");
                }
                solve(culoare, new_i, new_j, a);
                lungimi[culoare]--;
                a[i][j] = 0;
                stiva.pop();
            }
        }
    }
}
void filla()
{
    for (int i = 0; i < size_a; i++)
    {
        for (int j = 0; j < size_b; j++)
        {
            a[i][j] = 0;
        }
    }
}
using namespace std; // 1 10 10 24 1 1 6 2 10 2 14 3 23 3 24 4 32 5 33 6 34 7 37 6 42 8 47 7 49 4 59 9 63 1 66 10 70 5 71 11 72 9 82 12 87 8 89 10 92 11 95 12 0
int main() //   1 5 5 8 1 1 5 1 7 2 8 3 9 2 10 4 17 3 24 4 0 
{

    int teste;
    cin >> teste;
    cout << teste << " ";

    while (teste--)
    {
        cin >> size_a >> size_b;
        int culoare;
        cin >> nr_puncte;
        for (int i = 1; i <= nr_puncte; i++)
        {
            int auxi;
            cin >> auxi;
            cin >> culoare;
            if (loc_a[culoare] == 0)
            {

                loc_a[culoare] = auxi;
                a[(loc_a[culoare] - 1) / size_b][(loc_a[culoare] - 1) % size_b] = culoare;
            }
            else
            {
                loc_b[culoare] = auxi;
                a[(loc_b[culoare] - 1) / size_b][(loc_b[culoare] - 1) % size_b] = culoare;
            }

        }
        /*for (int i = 0; i < size_a; i++)
        {
            for (int j = 0; j < size_b; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }*/

        cin >> culoare;
        cout << nr_puncte / 2 << " ";
        stiva.push("1");
        stiva.push(to_string(loc_a[1]));
        //a[(loc_a[1] - 1) / size_b][(loc_a[1] - 1) % size_b] = 0;
        solve(1, (loc_a[1] - 1) / size_b, (loc_a[1] - 1) % size_b, a);
        while (!stiva.empty())
        {
            stiva.pop();
        }
        fill(lungimi, lungimi + 50, 0);
        fill(loc_a, loc_a + 50, 0);
        fill(loc_b, loc_b + 50, 0);
        filla();
        im = 0;
        //PrintStack(stiva);
    }
}