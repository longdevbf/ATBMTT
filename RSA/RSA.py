
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
        Khóa riêng (d, n)
    """
    return (d, p ,q)

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

# def  main():
    # p: int = int(input("Nhập số nguyên tố p: "))
    # q: int = int(input("Nhập số nguyên tố q: "))
    # e: int = int(input("Nhập số nguyên e: "))
    # n: int = p * q
    # phi: int = Euler.euler_phi_optimized(2923)
    # d: int = Euclid.Inverse(5, phi)
    # pub_key: tuple = public_key(e, n)
    # priv_key: tuple = private_key(d, p, q)
    # print(f"Khóa công khai: {pub_key}")
    # print(f"Khóa riêng: {priv_key}")
    # message: int = int(input("Nhập thông điệp dưới dạng số nguyên: "))
    # ciphertext: int = encrypt(76, (5,2923))
    # print(f"Thông điệp đã mã hóa: {ciphertext}")
    # decrypted_message: int = decrypt(863, (d, 71, 19))
    # print(f"Thông điệp gốc: {decrypted_message}")
    

def BaiToan1():
    p = 43
    q = 47
    e = 53
    #a KHóa công khai của An: PU = {e, n} 
    n = p * q
    PU = public_key(e, n)
    print("Khóa công khai của An:", PU)
    #b Khóa riêng của An: PR = {d, n}
    phi = Euler.euler_phi_optimized(n)
    d = Euclid.Inverse(e, phi)
    PR = private_key(d, p, q) 
    print("Khóa riêng của An:", PR)
    #c Mã hóa thông điệp m = 67
    m = 67
    ciphertext = encrypt(m, PU)
    print("Thông điệp đã mã hóa:", ciphertext)
    decrypted_message = decrypt(ciphertext, PR)
    print("Thông điệp gốc:", decrypted_message)
    "e. Việc mã hóa ở câu c là thực hiện nhiệm vụ bảo mật"
def BaiToan2():
    p = 43
    q = 47
    e = 53
    n = p * q
    #a,b giống bài 1
    #c Cách người gửi (Ba) mã hóa thông điệp để gửi cho An:
    PU_An = public_key(e, n)
    m = 67
    ciphertext = encrypt(m, PU_An)
    print("Thông điệp đã mã hóa mà Ba gửi cho An:", ciphertext)
    #d Cách An giải mã thông điệp mà Ba gửi đến:
    phi = Euler.euler_phi_optimized(n)
    d = Euclid.Inverse(e, phi)
    PR_An = private_key(d, p, q)
    decrypted_message = decrypt(ciphertext, PR_An)
    print("Thông điệp gốc mà An nhận được từ Ba:", decrypted_message)
    "e. Việc mã hóa ở câu c là thực hiện nhiệm vụ bảo mật"
if __name__ == "__main__":
    BaiToan1()
    BaiToan2()