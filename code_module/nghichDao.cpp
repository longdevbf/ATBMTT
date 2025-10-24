#include<bits/stdc++.h>
using namespace std;

long long nghichdao(long long a, long long n)
{
    long long z = n;    //  Biến z dùng để lưu giá trị ban đầu của n, dùng trong trường hợp kết quả ra số âm
    // 2 biến tạm dùng để dịch x1-2, y1-2 trong quá trình tính toán
    long long tmpx;
    long long tmpy; 
    // Giá trị cố định
    long long x1 = 0, x2 = 1;
    long long y1 = 1, y2 = 0;
    long long r = a % n;
    while(r >= 1)
    {
        long long q = a / n;
        tmpx = x1;
        x1 = x2;
        x2 = tmpx - q*x2;
        tmpy = y1;
        y1 = y2;
        y2 = tmpy - q*y2;
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

int main()
{
    long long a = 25, n = 31;
    cout << "Ket qua: " << nghichdao(a,n);
}