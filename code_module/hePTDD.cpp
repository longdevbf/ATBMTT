#include<bits/stdc++.h>
using namespace std;

// tinh module nghich dao
long long nghichdao(long long a, long long n)
{
    long long z = n;
    long long tmpx, tmpy;
    long long x1 = 0, x2 = 1 , y1 = 1 , y2 = 0;
    long long r = a % n;
    while(r >= 1)
    {
        long long q = a / n;
        tmpx = x1;
        x1 = x2; x2 = tmpx - q*x2;
        tmpy = y1;
        y1 = y2; y2 = tmpy - q*y2;
        a = n;
        n = r;
        r = a % n;
    }
    if( y2 < 0 )
    {
        return y2 + z;
    }
    return y2;
}

// He pt dong du
long long hptdd(long long m1, long long m2, long long m3,
                long long a1, long long a2, long long a3)
{
    long long M = m1 *m2 * m3;
    long long M1 = M / m1, M2 = M / m2, M3 = M / m3;
    long long y1 = nghichdao(M1, m1), y2 = nghichdao(M2, m2), y3 = nghichdao(M3, m3);
    long long x = ((a1 * M1 * y1) + (a2 * M2 * y2) + (a3 * M3 * y3)) % M;
    if (x < 0) x += M;
    return x;
}

int main()
{
    long long m1 = 11, m2 = 13, m3 = 17, a1 = 6, a2 = 11, a3 = 12;
    cout << "Ket qua: " << hptdd(m1,m2,m3,a1,a2,a3);
}
