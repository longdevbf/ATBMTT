using System;
using System.Collections.Generic;

namespace ATBMTT.RSA
{
    public class ChuKyDienTuDSA
    {
        private static HashSet<long> kUsed = new HashSet<long>();

        /// <summary>
        /// Tính khóa công khai y = g^xA mod p
        /// </summary>
        /// <param name="xA">Khóa riêng</param>
        /// <param name="p">Số nguyên tố</param>
        /// <param name="g">Cơ số</param>
        /// <returns>Khóa công khai y</returns>
        public static long PublicKey(long xA, long p, long g)
        {
            long y = ModPow(g, xA, p);
            return y;
        }

        /// <summary>
        /// Tạo chữ ký số (r, s)
        /// </summary>
        /// <param name="g">Cơ số</param>
        /// <param name="p">Số nguyên tố</param>
        /// <param name="q">Số nguyên tố</param>
        /// <param name="h">Giá trị băm</param>
        /// <param name="xA">Khóa riêng</param>
        /// <returns>Chữ ký số (r, s)</returns>
        public static (long r, long s) ChuKy(long g, long p, long q, long h, long xA)
        {
            Console.Write("Nhập số nguyên k: ");
            long k = long.Parse(Console.ReadLine());
            if (kUsed.Contains(k))
            {
                Console.WriteLine("Lỗi: k đã được sử dụng trước đó. Vui lòng chọn k khác.");
                return (0, 0);
            }
            kUsed.Add(k);
            long r = ModPow(g, k, p) % q;
            long inv_k = ModPow(k, q - 2, q);
            long s = ((h + xA * r) * inv_k) % q;
            Console.WriteLine($"r = ({g}^{k} mod {p}) mod {q}: {r}");
            Console.WriteLine($"s = (({h} + {xA} * {r}) * {inv_k}) mod {q}: {s}");
            return (r, s);
        }

        /// <summary>
        /// Xác minh chữ ký số
        /// </summary>
        /// <param name="signature">Chữ ký số (r, s)</param>
        /// <param name="q">Số nguyên tố</param>
        /// <param name="p">Số nguyên tố</param>
        /// <param name="h">Giá trị băm</param>
        /// <param name="g">Cơ số</param>
        /// <param name="yA">Khóa công khai</param>
        /// <returns>True nếu chữ ký hợp lệ, False nếu không</returns>
        public static bool XacMinh((long r, long s) signature, long q, long p, long h, long g, long yA)
        {
            Console.WriteLine("Xác minh chữ ký...");
            long r = signature.r;
            long s = signature.s;
            long w = ModPow(s, q - 2, q);
            Console.WriteLine($"w = {s}^(-1) mod {q}: {w}");
            long u1 = (h * w) % q;
            Console.WriteLine($"u1 = ({h} * {w}) mod {q}: {u1}");
            long u2 = (r * w) % q;
            Console.WriteLine($"u2 = ({r} * {w}) mod {q}: {u2}");
            long v = ((ModPow(g, u1, p) * ModPow(yA, u2, p)) % p) % q;
            Console.WriteLine($"v = (({g}^{u1} * yA^{u2}) mod {p}) mod {q}: {v}");
            return v == r;
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
            Console.Write("Nhập số nguyên tố q: ");
            long q = long.Parse(Console.ReadLine());
            Console.Write("Nhập giá trị băm h: ");
            long h = long.Parse(Console.ReadLine());
            long g = ModPow(h, (p - 1) / q, p);
            Console.Write("Nhập giá trị băm HM: ");
            long HM = long.Parse(Console.ReadLine());
            Console.Write("Nhập khóa riêng xA: ");
            long xA = long.Parse(Console.ReadLine());
            long yA = PublicKey(xA, p, g);
            Console.WriteLine("Khóa công khai yA: " + yA);
            var chuKyValue = ChuKy(g, p, q, HM, xA);
            Console.WriteLine($"Chữ ký số (r, s): {chuKyValue}");
            //Cach xác minh chữ ký
            bool isValid = XacMinh(chuKyValue, q, p, HM, g, yA);
            Console.WriteLine("Xác minh chữ ký: " + (isValid ? "Hợp lệ" : "Không hợp lệ"));
        }
    }
}
