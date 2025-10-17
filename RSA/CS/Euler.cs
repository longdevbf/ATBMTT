using System;
using System.Collections.Generic;

namespace ATBMTT.RSA
{
    public class Euler
    {
        /// <summary>
        /// Tính ước chung lớn nhất (Greatest Common Divisor) của hai số a và b
        /// Sử dụng thuật toán Euclid
        /// </summary>
        public static int Gcd(int a, int b)
        {
            while (b != 0)
            {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        /// <summary>
        /// Tính hàm Euler phi(n) - đếm số lượng số nguyên dương nhỏ hơn n và nguyên tố cùng nhau với n
        /// Phương pháp cơ bản: kiểm tra từng số từ 1 đến n-1
        /// </summary>
        /// <param name="n">Số nguyên dương</param>
        /// <returns>Số lượng các số nguyên tố cùng nhau với n</returns>
        public static int EulerPhiBasic(int n)
        {
            if (n == 1)
                return 1;

            int count = 0;
            for (int i = 1; i < n; i++)
            {
                if (Gcd(i, n) == 1)
                {
                    count++;
                }
            }
            return count;
        }

        /// <summary>
        /// Tính hàm Euler phi(n) - phương pháp tối ưu
        /// Sử dụng công thức: phi(n) = n * ∏(1 - 1/p) với p là các ước nguyên tố của n
        /// </summary>
        /// <param name="n">Số nguyên dương</param>
        /// <returns>Số lượng các số nguyên tố cùng nhau với n</returns>
        public static long EulerPhiOptimized(long n)
        {
            if (n == 1)
                return 1;

            long result = n;
            long p = 2;

            // Tìm tất cả các ước nguyên tố của n
            while (p * p <= n)
            {
                // Nếu p là ước nguyên tố của n
                if (n % p == 0)
                {
                    // Loại bỏ tất cả các ước p khỏi n
                    while (n % p == 0)
                    {
                        n /= p;
                    }
                    // Áp dụng công thức: result = result * (1 - 1/p) = result * (p-1) / p
                    result -= result / p;
                }
                p++;
            }

            // Nếu n > 1, thì n là một số nguyên tố
            if (n > 1)
            {
                result -= result / n;
            }

            return result;
        }

        /// <summary>
        /// Liệt kê tất cả các số nguyên tố cùng nhau với n
        /// </summary>
        /// <param name="n">Số nguyên dương</param>
        /// <returns>Danh sách các số nguyên tố cùng nhau với n</returns>
        public static List<int> ListCoprimeNumbers(int n)
        {
            List<int> coprimeList = new List<int>();
            for (int i = 1; i < n; i++)
            {
                if (Gcd(i, n) == 1)
                {
                    coprimeList.Add(i);
                }
            }
            return coprimeList;
        }

        /// <summary>
        /// Hàm chính để tính Euler phi (mặc định dùng phương pháp tối ưu)
        /// </summary>
        /// <param name="n">Số nguyên dương</param>
        /// <returns>Số lượng các số nguyên tố cùng nhau với n</returns>
        public static long EulerFunc(long n)
        {
            return EulerPhiOptimized(n);
        }
    }
}
