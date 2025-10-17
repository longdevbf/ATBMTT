#include<bits/stdc++.h>
using namespace std;

//  tinh binh phuong va nhan
long long bpvn(long long a,long long m, long long n)
{
    a %= n;
    long long kq = 1;
    while( m > 0 )
    {
        if(m % 2 != 0)
        {
            kq = (kq * a) % n;
        }
        a = (a*a) % n;
        m /= 2;
    }
    return kq;
}

// tinh logarit roi rac
long long logarit(long long a, long long b, long long n)
{
    
    long long r;
    for(int i = 1 ; i < n ; i++)
    {
        r = bpvn(a,i,n);
        if(r == b)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    long long a = 6, b = 5, n = 13;
    cout << "Ket qua: " << logarit(a,b,n);
}