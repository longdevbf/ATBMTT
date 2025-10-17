#include<bits/stdc++.h>
using namespace std;
//e
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

int main()
{
    long long n = 3353;
    cout << "Ket qua: " << Ham_Euler(n);
}