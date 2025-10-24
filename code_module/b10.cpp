#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
// a
static int64 pow_mod(int64 a, long long b, int64 m)
{
    a %= m;
    int64 res = 1 % m;
    while (b > 0)
    {
        if (b & 1)
        {
            res = ((__int128)res * a) % m;
        }
        a = ((__int128)a * a) % m;
        b >>= 1;
    }
    return res;
}

static int64 inv_fermat(int64 a, int64 p)
{
    return pow_mod(a, p - 2, p);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a = 43, b = 53, x = 308, y = 455, n = 179;

    int64 ax = pow_mod(a, x, n);
    int64 by = pow_mod(b, y, n);

    int64 A1 = (ax + by) % n;
    int64 A2 = (ax - by + n) % n;
    int64 A3 = ((__int128)ax * by) % n;

    if (by == 0)
    {
        cerr << "Khong ton tai nghich dao cua b^y mod n vi b^y â‰¡ 0 (mod n)\n";
        return 0;
    }
    int64 A4 = inv_fermat(by, n);

    int64 A5 = ((__int128)ax * A4) % n;

    cout << "A1 = " << A1 << "\n";
    cout << "A2 = " << A2 << "\n";
    cout << "A3 = " << A3 << "\n";
    cout << "A4 = " << A4 << "\n";
    cout << "A5 = " << A5 << "\n";

    cout << pow_mod(3, 30, 19);
    return 0;
}