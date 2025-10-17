#include <bits/stdc++.h>
using namespace std;

string PhepDichBit(const string &STR, int SoBit)
{
    string str;

    if (STR.empty())
        return str;

    if (SoBit == 1)
    {
        for (int i = 0; i < STR.length() - 1; i++)
        {
            str += STR[i + 1];
        }
        str += STR[0];
    }
    else
    {
        for (int i = 1; i < STR.length() - 1; i++)
        {
            str += STR[i + 1];
        }
        str += STR[0];
        str += STR[1];
    }

    return str;
}

int main()
{
    string s = "ABCDEF";
    cout << PhepDichBit(s, 2);
}