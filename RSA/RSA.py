
import Euler, Euclid
def public_key(e: int, n: int) -> tuple:
    """
    Tạo khóa công khai (e, n)
    
    Args:
        e: Số nguyên dương
        n: Tích của hai số nguyên tố p và q
    
    Returns:
        Khóa công khai (e, n)
    """
    return (e, n)

def private_key(d: int, p: int, q: int) -> tuple:
    """
    Tạo khóa riêng (d, n)
    
    Args:
        d: Nghịch đảo modulo của e theo phi(n)
        p: Số nguyên tố p
        q: Số nguyên tố q

    Returns:
        Khóa riêng (d, p, q)
    """
    return (d, p, q)

def encrypt(message: int, public_key: tuple) -> int:
    """
    Mã hóa thông điệp sử dụng khóa công khai
    
    Args:
        message: Thông điệp dưới dạng số nguyên
        public_key: Khóa công khai (e, n)
    
    Returns:
        Thông điệp đã mã hóa
    """
    e, n = public_key
    return pow(message, e, n)

def decrypt(ciphertext: int, private_key: tuple) -> int:
    """
    Giải mã thông điệp sử dụng khóa riêng
    
    Args:
        ciphertext: Thông điệp đã mã hóa dưới dạng số nguyên
        private_key: Khóa riêng (d, p, q)
    
    Returns:
        Thông điệp gốc
    """
    d, p, q = private_key
    n = p * q
    return pow(ciphertext, d, n)

def  main():
    p: int = int(input("Nhập số nguyên tố p: "))
    q: int = int(input("Nhập số nguyên tố q: "))
    e: int = int(input("Nhập số nguyên e: "))
    n: int = p * q
    phi: int = Euler.euler_phi_optimized(n)
    d: int = Euclid.Inverse(e, phi)
    pub_key: tuple = public_key(e, n)
    priv_key: tuple = private_key(d, p, q)
    print(f"Khóa công khai: {pub_key}")
    print(f"Khóa riêng: {priv_key}")
    message: int = int(input("Nhập thông điệp dưới dạng số nguyên: "))
    ciphertext: int = encrypt(message, pub_key)
    print(f"Thông điệp đã mã hóa: {ciphertext}")
    decrypted_message: int = decrypt(ciphertext, priv_key)
    print(f"Thông điệp gốc: {decrypted_message}")

if __name__ == "__main__":
    main()