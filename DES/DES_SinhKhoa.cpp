#include <bits/stdc++.h>
using namespace std;

string round_keys[16];

string PhepDichBit(const string &STR, int SoBit)
{
  string str;

  if (STR.empty())
    return str;

  if (SoBit == 1)
  {
    for (int i = 0; i < (int)STR.length() - 1; i++)
    {
      str += STR[i + 1];
    }
    str += STR[0];
  }
  else
  {
    for (int i = 1; i < (int)STR.length() - 1; i++)
    {
      str += STR[i + 1];
    }
    str += STR[0];
    str += STR[1];
  }

  return str;
}

void SinhKhoa(string key)
{
  // PC_1: Lưu lại 56 bit từ 64 bit của khóa ban đầu loại 8 bit parity bit
  int pc1[56] = {
      57, 49, 41, 33, 25, 17, 9,
      1, 58, 50, 42, 34, 26, 18,
      10, 2, 59, 51, 43, 35, 27,
      19, 11, 3, 60, 52, 44, 36,
      63, 55, 47, 39, 31, 23, 15,
      7, 62, 54, 46, 38, 30, 22,
      14, 6, 61, 53, 45, 37, 29,
      21, 13, 5, 28, 20, 12, 4};

  // PC_2
  int pc2[48] = {
      14, 17, 11, 24, 1, 5,
      3, 28, 15, 6, 21, 10,
      23, 19, 12, 4, 26, 8,
      16, 7, 27, 20, 13, 2,
      41, 52, 31, 37, 47, 55,
      30, 40, 51, 45, 33, 48,
      44, 49, 39, 56, 34, 53,
      46, 42, 50, 36, 29, 32};

  // Nén khóa bằng bảng PC_1
  string perm_key = "";
  for (int i = 0; i < 56; i++)
  {
    perm_key += key[pc1[i] - 1];
  }

  // Chia perm_key làm 2 phần
  string C = perm_key.substr(0, 28);
  string D = perm_key.substr(28, 28);

  // Sinh 16 key
  for (int i = 0; i < 16; i++)
  {
    // Vị trí 1,2,9,16 dịch 1, còn lại dịch 2
    if (i == 0 || i == 1 || i == 8 || i == 15)
    {
      C = PhepDichBit(C, 1);
      D = PhepDichBit(D, 1);
    }
    else
    {
      C = PhepDichBit(C, 2);
      D = PhepDichBit(D, 2);
    }

    // Kết hợp C và D
    string combined_key = C + D;
    string round_key = "";

    // Hoán vị key kết hợp bằng bảng vị trí PC_2, lấy 48 bit
    for (int j = 0; j < 48; j++)
    {
      round_key += combined_key[pc2[j] - 1];
    }

    round_keys[i] = round_key;
    cout << "Key " << i + 1 << ": " << round_keys[i] << endl;
  }
}

int main()
{
  string key =
      "10101010101110110000100100011000001001110011"
      "01101100110011011101";

  SinhKhoa(key);
}
