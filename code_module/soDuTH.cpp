#include<bits/stdc++.h>
using namespace std;

//  Ham phan tich ra cac thua so nguyen to
vector<long long> pttsnt(long long n)
{
    vector<long long> thuaso;
    long long tmp = n;

    if(tmp % 2 == 0)
    {
        long long ts = 1;
        while (tmp % 2 == 0)
        {
            ts *= 2;
            tmp /= 2;
        }
        thuaso.push_back(ts);
    }

    for(int i = 3 ; i*i <= tmp ; i+=2)
    {
        if(tmp % i == 0)
        {
            long long ts = 1;
            while (tmp % i == 0)
            {
                ts *= i;
                tmp /= i;
            }
            thuaso.push_back(ts);
        }
    }

    if(tmp > 1) thuaso.push_back(tmp);
    return thuaso;
}

// Ham tinh theo pp Binh phuong va nhan
long long bpvn(long long a,long long m, long long n)
{
    a %= n;
    long long kq = 1;
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

// Ham tinh module nghich dao
long long nghich_dao(long long a, long long n)
{
    long long z = n; 
    long long tmpx, tmpy; 
    long long x1 = 0, x2 = 1, y1 = 1, y2 = 0;
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

// Ham tinh phan du trung hoa
long long pdth(long long a, long long m, long long n)
{
    vector<long long> m_nho = pttsnt(n);
    int k = m_nho.size();

    // Tinh module theo cac thua so ngto
    vector<long long> a_nho(k);
    for(int i = 0 ; i < k ; i++)
    {
        a_nho[i] = bpvn(a,m,m_nho[i]);
    }

    // Tinh M_lon[i]
    vector<long long> M_lon(k);
    for(int i = 0 ; i < k ; i++)
    {
        M_lon[i] = n / m_nho[i];
    }

    // Tinh nghich dao va c[i]
    vector<long long> c_nho(k);
    for(int i = 0 ; i < k ; i++)
    {
        c_nho[i] = M_lon[i] * nghich_dao(M_lon[i], m_nho[i]);
    }
    
    long long tong = 0;
    for(int i = 0 ; i < k ; i++)
    {
        tong += (c_nho[i] * a_nho[i]);
    }
    return tong % n;
}

int main()
{
    long long a = 113, m = 58, n = 37259;
    cout << "Ket qua: " << pdth(a,m,n);
}