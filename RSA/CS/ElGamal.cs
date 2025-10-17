using System;

namespace ATBMTT.RSA
{
    public class ElGamal
    {
        /// <summary>
        /// Tính khóa công khai y từ khóa bí mật x và các tham số p, a
        /// </summary>
        /// <param name="p">Số nguyên tố</param>
        /// <param name="a">Số nguyên</param>
        /// <param name="x">Khóa bí mật</param>
        /// <returns>Khóa công khai y</returns>
        public static (long p, long a, long y) PublicKey(long p, long a, long x)
        {
            long y = ModPow(a, x, p);
            return (p, a, y);
        }

        /// <summary>
        /// Mã hóa thông điệp m thành cặp (c1, c2) sử dụng khóa công khai (p, a, y)
        /// </summary>
        /// <param name="p">Số nguyên tố</param>
        /// <param name="k">Số ngẫu nhiên</param>
        /// <param name="a">Số nguyên</param>
        /// <param name="y">Khóa công khai</param>
        /// <param name="m">Thông điệp dưới dạng số nguyên</param>
        /// <returns>Cặp (c1, c2) là thông điệp đã mã hóa</returns>
        public static (long c1, long c2) Encrypt(long p, long k, long a, long y, long m)
        {
            long c1 = ModPow(a, k, p);
            long c2 = (m * ModPow(y, k, p)) % p;
            return (c1, c2);
        }

        /// <summary>
        /// Giải mã cặp (c1, c2) thành thông điệp m sử dụng khóa bí mật x và tham số p
        /// </summary>
        /// <param name="p">Số nguyên tố</param>
        /// <param name="x">Khóa bí mật</param>
        /// <param name="C">Cặp (c1, c2) là thông điệp đã mã hóa</param>
        /// <returns>Thông điệp gốc m</returns>
        public static long Decrypt(long p, long x, (long c1, long c2) C)
        {
            long c1 = C.c1;
            long c2 = C.c2;
            long K = ModPow(c1, x, p);
            long K_inv = ModPow(K, p - 2, p);  // Nghịch đảo modulo của K theo p (theo định lý Fermat nhỏ)
            long m = (c2 * K_inv) % p;
            return m;
        }

        /// <summary>
        /// Tính (base^exp) mod mod
        /// </summary>
        private static long ModPow(long baseValue, long exp, long mod)
        {
            long result = 1;
            baseValue = baseValue % mod;
            while (exp > 0)
            {
                if (exp % 2 == 1)
                {
                    result = (result * baseValue) % mod;
                }
                exp = exp >> 1;
                baseValue = (baseValue * baseValue) % mod;
            }
            return result;
        }

        public static void Main()
        {
            Console.Write("Nhập số nguyên tố p: ");
            long p = long.Parse(Console.ReadLine());
            Console.Write("Nhập số a là căn nguyên thủy của p: ");
            long a = long.Parse(Console.ReadLine());
            Console.Write("Nhập sô nguyên x là khóa bí mật: ");
            long x = long.Parse(Console.ReadLine());
            Console.Write("Nhập số nguyên m là thông điệp cần mã hóa (m < p): ");
            long m = long.Parse(Console.ReadLine());
            Console.Write("Nhập số nguyên k là số ngẫu nhiên (1 < k < p-1 và gcd(k, p-1) = 1): ");
            long k = long.Parse(Console.ReadLine());
            var publicKey = PublicKey(p, a, x);
            Console.WriteLine($"Khóa công khai: {publicKey}");
            var C = Encrypt(p, k, a, publicKey.y, m);
            Console.WriteLine($"Thông điệp đã mã hóa: {C}");
            long decryptedM = Decrypt(p, x, C);
            Console.WriteLine($"Thông điệp gốc sau khi giải mã: {decryptedM}");
        }
    }
}
