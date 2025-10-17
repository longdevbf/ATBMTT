#include<bits/stdc++.h>
using namespace std;

// Fermat: (a^n-1) mod n = 1

// Kiem tra so nguyen to
bool snt(long long p) {
    if (p <= 1) return false;
    if (p <= 3) return true;
    if (p % 2 == 0 || p % 3 == 0) return false;
    
    for (long long i = 5; i * i <= p; i = i + 6) {
        if (p % i == 0 || p % (i + 2) == 0) return false;
    }
    return true;
}

// Tinh binh phuong va nhan
long long bpvn(long long a, long long m, long long n) {
    a %= n;
    long long result = 1;

    while (m > 0) {
        if (m % 2 != 0) { 
            result = (result * a) % n;
        }
        a = (a * a) % n;
        m/=2;
    }
    return result;
}

// Tinh Fermat
long long fermat(long long a, long long m, long long n)
{
    if(!snt(n)) return -1; // n phai la so nguyen to
    if(__gcd(a,n) != 1)
    {
        cout << "a va n khong la 2 so nguyen to cung nhau, khong dung Fermat\n";
        return 0;
    }
    long long m2 = m % (n-1); // m' = m mod (n-1) 
    return bpvn(a,m2,n);
}

int main()
{
    long long a = 373, m = 851, n = 6211;
    cout << "Ket qua: " << fermat(a,m,n);
}