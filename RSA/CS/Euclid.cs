using System;

namespace ATBMTT.RSA
{
    public class Euclid
    {
        /// <summary>
        /// Tính ước số chung lớn nhất (GCD) của hai số nguyên a và b
        /// Sử dụng thuật toán Euclid
        /// </summary>
        /// <param name="a">Số nguyên dương</param>
        /// <param name="b">Số nguyên dương</param>
        /// <returns>GCD của a và b</returns>
        public static int Gcd(int a, int b)
        {
            if (a < 0 || b < 0)
            {
                throw new ArgumentException("Cả hai số phải là số nguyên dương");
            }

            if (a == 0)
                return b;
            if (b == 0)
                return a;
            return Gcd(b, a % b);
        }

        /// <summary>
        /// Tính toán ước số chung lớn nhất (GCD) của a và m, đồng thời tìm x và y sao cho ax + my = GCD(a, m)
        /// </summary>
        /// <param name="a">Số nguyên dương</param>
        /// <param name="m">Số nguyên dương</param>
        /// <param name="x">Biến để lưu giá trị x</param>
        /// <param name="y">Biến để lưu giá trị y</param>
        /// <returns>Mảng chứa GCD, x, y</returns>
        public static long[] EclidExtended(long a, long m, long x, long y)
        {
            if (m == 0)
            {
                return new long[] { a, 1, 0 };
            }

            long[] result = EclidExtended(m, a % m, x, y);
            long gcd = result[0];
            long x1 = result[1];
            long y1 = result[2];

            x = y1;
            y = x1 - (a / m) * y1;

            return new long[] { gcd, x, y };
        }

        /// <summary>
        /// Tính nghịch đảo modulo của a theo m
        /// Sử dụng thuật toán Euclid mở rộng
        /// </summary>
        /// <param name="a">Số nguyên dương</param>
        /// <param name="m">Số nguyên dương</param>
        /// <returns>Nghịch đảo của a theo m</returns>
        public static long Inverse(long a, long m)
        {
            long[] result = EclidExtended(a, m, 0, 0);
            long gcd = result[0];
            long x = result[1];

            if (gcd != 1)
            {
                throw new ArgumentException($"{a} và {m} không có nghịch đảo modulo");
            }

            return (x % m + m) % m;
        }
    }
}
