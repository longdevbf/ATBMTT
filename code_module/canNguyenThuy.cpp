#include<bits/stdc++.h>
using namespace std;

// tinh binh phuong va nhan
long long bpvn(long long a, long long m, long long n)
{
    a %= n;
    long long kq = 1;
    while (m > 0)
    {
        if(m % 2 != 0) kq = (kq * a) % n;
        a = (a*a) % n;
        m /= 2;
    }
    return kq;
}

// Ham Euler
long long Ham_Euler(long long n)
{
    long long kq = n;
    long long tmp = n;

    if(tmp % 2 == 0)
    {
        kq = (kq / 2) * (2-1);
        while (tmp % 2 == 0)
        {
            tmp /= 2;
        }
    }

    for(int i = 3 ; i*i <= tmp ; i+=2)
    {
        if(tmp % i == 0)
        {
            kq = kq / i * (i-1);
            while(tmp % i == 0)
            {
                tmp /= i;
            }
        }
    }
    if(tmp > 1) kq = kq / tmp * (tmp - 1);
    return kq;
}

// Ham tim cac uoc so cua n
vector<long long> uocso(long long n)
{
    vector<long long> uoc;
    for(int i = 1 ; i <= n/2 ; i++)
    {
        if(n % i == 0)
        {
            uoc.push_back(i);
        }
    }
    sort(uoc.begin(), uoc.end());
    return uoc;
}

// kiem tra can nguyen thuy
bool can_nguyen_thuy(long long a, long long n)
{
    long long phi_n = Ham_Euler(n);
    long long tmp;
    vector<long long> uoc_n = uocso(phi_n);
    for(int i : uoc_n)
    {
        tmp = bpvn(a,i,n);
        if(tmp == 1 && i < phi_n) return 0;
    }
    return 1;
}

int main()
{
    long long a = 3, n = 239;
    if(can_nguyen_thuy(a,n)) cout << a << " la can nguyen thuy cua " << n;
    else cout << a << " khong la can nguyen thuy cua " << n;
}