#include <bits/stdc++.h>
using namespace std;
 //a
long long bpvn(long long a, long long m, long long n) {
    a %= n;

    long long result = 1;

    while (m > 0) {
        if (m % 2 != 0) { 
            result = (result * a) % n;
        }

        a = (a * a) % n;

        m /= 2;
    }
    return result;
}

int main() {
    long long a = 113;
    long long m = 58;
    long long n = 37259;
    cout << "Ket qua: " << bpvn(a,m,n);
    return 0;
}