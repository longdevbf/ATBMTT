def public_key(p:int, a:int, x:int) -> tuple[int, int]:
    """
    Tính khóa công khai y từ khóa bí mật x và các tham số p, a
    Args:
        p: Số nguyên tố
        a: Số nguyên
        x: Khóa bí mật
    
    Returns:
        Khóa công khai y
    """
    y = pow(a, x, p)
    return (p, a, y)

def encrypt(p:int, k:int, a:int, y:int, m:int) -> tuple[int, int]:
    """
    Mã hóa thông điệp m thành cặp (c1, c2) sử dụng khóa công khai (p, a, y)
    Args:
        p: Số nguyên tố
        a: Số nguyên
        y: Khóa công khai
        m: Thông điệp dưới dạng số nguyên
    
    Returns:
        Cặp (c1, c2) là thông điệp đã mã hóa
    """
    
    c1 = pow(a, k, p)
    c2 = (m * pow(y, k, p)) % p
    return (c1, c2)
def decrypt(p: int, x: int , C: tuple[int, int]) -> int:
    """
    Giải mã cặp (c1, c2) thành thông điệp m sử dụng khóa bí mật x và tham số p
    Args:
        p: Số nguyên tố
        x: Khóa bí mật
        C: Cặp (c1, c2) là thông điệp đã mã hóa
    
    Returns:
        Thông điệp gốc m
    """
    c1, c2 = C
    K = pow(c1, x, p)
    K_inv = pow(K, p-2, p)  # Nghịch đảo modulo của K theo p (theo định lý Fermat nhỏ)
    m = (c2 * K_inv) % p
    return m
def main():
    p:int = int(input("Nhập số nguyên tố p: "))
    a:int = int(input("Nhập số a là căn nguyên thủy của p: "))
    x:int = int(input("Nhập sô nguyên x là khóa bí mật: "))
    m:int = int(input("Nhập số nguyên m là thông điệp cần mã hóa (m < p): "))
    k:int = int(input("Nhập số nguyên k là số ngẫu nhiên (1 < k < p-1 và gcd(k, p-1) = 1): "))
    public = public_key(p, a, x)
    print(f"Khóa công khai: {public}")
    C = encrypt(p, k, a, public[2], m)
    print(f"Thông điệp đã mã hóa: {C}")
    decrypted_m = decrypt(p, x, C)
    print(f"Thông điệp gốc sau khi giải mã: {decrypted_m}")
if __name__ == "__main__":
    main()