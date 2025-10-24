#include <bits/stdc++.h>
using namespace std;

/* ======= BẢNG DES ======= */
static const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
static const int IP_1[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
static const int E_table[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
static const int P_function[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};
static const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
static const int PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
static const int S_box[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

/* ======= HÀM TIỆN ÍCH ======= */
string trimHex(const string &in)
{ // bỏ khoảng trắng và đưa về HOA
    string s;
    for (size_t i = 0; i < in.size(); ++i)
    {
        char c = in[i];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            continue;
        if (c >= 'a' && c <= 'z')
            c = char(c - 'a' + 'A');
        s.push_back(c);
    }
    return s;
}

string HexToBin(const string &hex)
{ // 1 hex -> 4 bit
    string s = trimHex(hex);
    string out;
    out.reserve(s.size() * 4);
    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        int v = 0;
        if (c >= '0' && c <= '9')
            v = c - '0';
        else if (c >= 'A' && c <= 'F')
            v = 10 + (c - 'A');
        else
        { /* ký tự lạ -> coi như 0 */
            v = 0;
        }
        // push 4 bit
        for (int b = 3; b >= 0; --b)
            out.push_back(((v >> b) & 1) + '0');
    }
    return out;
}

string BinToHex(const string &bin)
{
    // pad trái bội số của 4
    string s = bin;
    int r = (int)s.size() % 4;
    if (r)
        s = string(4 - r, '0') + s;
    static const char LUT[] = "0123456789ABCDEF";
    string h;
    h.reserve(s.size() / 4);
    for (size_t i = 0; i < s.size(); i += 4)
    {
        int v = (s[i] - '0') * 8 + (s[i + 1] - '0') * 4 + (s[i + 2] - '0') * 2 + (s[i + 3] - '0');
        h.push_back(LUT[v]);
    }
    return h;
}

string permute(const string &in, const int *tbl, int outLen)
{
    string out;
    out.resize(outLen);
    for (int i = 0; i < outLen; i++)
        out[i] = in[tbl[i] - 1];
    return out;
}
string shl28(const string &s, int k)
{
    int n = (int)s.size();
    k %= n;
    return s.substr(k) + s.substr(0, k);
}
string xorb(const string &a, const string &b)
{
    string r;
    r.resize(b.size());
    for (size_t i = 0; i < b.size(); ++i)
        r[i] = (a[i] != b[i]) ? '1' : '0';
    return r;
}
string sboxes32(const string &in48)
{
    string out;
    out.reserve(32);
    for (int j = 0; j < 8; j++)
    {
        string six = in48.substr(j * 6, 6);
        int row = (six[0] - '0') * 2 + (six[5] - '0');
        int col = (six[1] - '0') * 8 + (six[2] - '0') * 4 + (six[3] - '0') * 2 + (six[4] - '0');
        int val = S_box[j][row][col];
        // 4 bit
        string b = "0000";
        for (int t = 0; t < 4; t++)
        {
            b[3 - t] = char((val >> t & 1) + '0');
        }
        out += b;
    }
    return out;
}

/* ======= TOÀN CỤC ======= */
string round_keys[16];

/* ======= PHẦN 1: SINH KHÓA (LOG THEO ĐỀ) ======= */
void SinhKhoa_TheoTungBuoc(const string &K64_bin)
{
    // 1) PC1
    string K56 = permute(K64_bin, PC1, 56);
    string C0 = K56.substr(0, 28), D0 = K56.substr(28, 28);
    cout << "PHAN 1: SINH KHOA Ki tu khoa K (input)\n";
    cout << "1) Tinh hoan vi PC1 doi voi khoa K\n";
    cout << "Input : K = (HEX) " << BinToHex(K64_bin) << "\n";
    cout << "Output: C0 = " << C0 << "\n";
    cout << "        D0 = " << D0 << "\n\n";

    // 2) Ci, Di + 3) Ki
    cout << "2) Tinh cac gia tri dich vong Ci, Di & 3) K_i qua PC2\n";
    string C = C0, D = D0;
    for (int i = 0; i < 16; i++)
    {
        int s = (i == 0 || i == 1 || i == 8 || i == 15) ? 1 : 2;
        C = shl28(C, s);
        D = shl28(D, s);
        cout << "   i=" << (i + 1) << ": Ci=" << C << " ; Di=" << D << "\n";
        string CD = C + D;
        string Ki = permute(CD, PC2, 48);
        round_keys[i] = Ki;
        cout << "   --> Ki = " << Ki << "\n";
    }
    cout << "\n";
}

/* ======= PHẦN 2: MÃ HÓA (LOG THEO ĐỀ) ======= */
string MaHoa_DES_TheoTungBuoc(const string &M64_bin)
{
    cout << "PHAN 2: MA HOA\n";
    // 4) IP
    string perm = permute(M64_bin, IP, 64);
    string L = perm.substr(0, 32), R = perm.substr(32, 32);
    cout << "4) IP doi voi ban tin M\n";
    cout << "Input : M = (HEX) " << BinToHex(M64_bin) << "\n";
    cout << "Output: L0 = " << L << "\n";
    cout << "        R0 = " << R << "\n\n";

    // ===== Chi tiết vòng 1 =====
    cout << "===== CHI TIET VONG LAP THU NHAT =====\n";
    string ER0 = permute(R, E_table, 48);
    cout << "5) Mo rong E[R0]\n";
    cout << "Output: ER0 = " << ER0 << "\n";

    string A = xorb(ER0, round_keys[0]);
    cout << "6) XOR ER0 voi K1\n";
    cout << "Input : K1 = " << round_keys[0] << "\n";
    cout << "Output: A  = " << A << "\n";

    string SB = sboxes32(A);
    cout << "7) S-box: B=S(A) = " << SB << "\n";

    string F = permute(SB, P_function, 32);
    cout << "8) Hoan vi P doi voi SB\n";
    cout << "Output: F = " << F << "\n";

    string L1 = R;
    string R1 = xorb(L, F);
    cout << "===== THUC HIEN VONG 1 =====\n";
    cout << "Output: L1 = " << L1 << "\n";
    cout << "        R1 = " << R1 << "\n\n";

    // Vòng 2..16 (theo cùng khuôn)
    cout << "===== THUC HIEN VONG i, i=2..16 =====\n";
    L = L1;
    R = R1;
    for (int i = 2; i <= 16; i++)
    {
        string ER = permute(R, E_table, 48);
        string AX = xorb(ER, round_keys[i - 1]);
        string SBx = sboxes32(AX);
        string Fx = permute(SBx, P_function, 32);
        string Li = R;
        string Ri = xorb(L, Fx);
        L = Li;
        R = Ri;
        cout << "i=" << i << " => L" << i << "=" << L << " ; R" << i << "=" << R << "\n";
    }
    cout << "\n";

    // 11) IP^-1
    string preOut = R + L; // swap cuối
    string Cbin = permute(preOut, IP_1, 64);
    cout << "11) IP^-1\n";
    cout << "Output: C (bin) = " << Cbin << "\n";
    cout << "        C (HEX) = " << BinToHex(Cbin) << "\n\n";
    return Cbin;
}

/* ======= MAIN: NHẬP HEX ======= */
int main()
{
    // Nhập 2 dòng: K_hex và M_hex (16 hex mỗi dòng). VD:
    // 133457799BBCDFF1
    // 0123456789ABCDEF
    string K_hex, M_hex;
    cout << "Nhap K (hex 16 ky tu): ";
    getline(cin, K_hex);
    cout << "Nhap M (hex 16 ky tu): ";
    getline(cin, M_hex);

    K_hex = trimHex(K_hex);
    M_hex = trimHex(M_hex);

    // Chuyển sang nhị phân 64 bit
    string K_bin = HexToBin(K_hex);
    string M_bin = HexToBin(M_hex);

    // Cắt/đệm cho đúng 64 bit nếu người dùng nhập thiếu/thừa
    if ((int)K_bin.size() < 64)
        K_bin = string(64 - K_bin.size(), '0') + K_bin;
    if ((int)M_bin.size() < 64)
        M_bin = string(64 - M_bin.size(), '0') + M_bin;
    if ((int)K_bin.size() > 64)
        K_bin = K_bin.substr(K_bin.size() - 64, 64);
    if ((int)M_bin.size() > 64)
        M_bin = M_bin.substr(M_bin.size() - 64, 64);

    // PHẦN 1: sinh khóa với log
    SinhKhoa_TheoTungBuoc(K_bin);

    // PHẦN 2: mã hóa với log
    MaHoa_DES_TheoTungBuoc(M_bin);

    return 0;
}
