#include<bits/stdc++.h>
using namespace std;

// tinh Ham Euler
long long Ham_Euler(long long n)
{
    long long kq = n;
    long long tmp = n;
    // Kiem tra thua so p = 2
    if(tmp % 2 == 0)
    {
        kq = (kq / 2) * (2-1);
        while(tmp % 2 == 0)
        {
            tmp /= 2;
        }
    }
    
    // Kiem tra cac thua so nguyen to tu 3 den sqrt(n)
    for(long long p = 3 ; p*p <= tmp ; p+=2)
    {
        if(tmp % p == 0)
        {
            kq = (kq / p) * (p-1);
            while(tmp % p == 0)
            {
                tmp /= p;
            }
        }
    }
    // Truong hop dac biet
    if(tmp > 1) kq = (kq / tmp) * (tmp-1);
    return kq;
}

// tinh binh phuong va nhan
long long bpvn(long long a, long long m, long long n)
{
    long long kq = 1;
    a %= n;
    while(m > 0)
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

// tinh Euler
long long Euler(long long a, long long m, long long n)
{
    if(n==1) return 0;
    if(__gcd(a,n) != 1)
    {
        cout << "a va n khong la 2 so nguyen to cung nhau, khong dung Euler\n";
        return 0;
    }
    long long phi_n = Ham_Euler(n);
    long long m2 = m % phi_n; // m' = m mod (phi_n)
    return bpvn(a,m2,n);
}

int main()
{
    long long a = 101, m = 597, n = 323;
    cout << "Ket qua: " << Euler(a,m,n);
}
