import math

def gcd(a, b):
    """
    Tính ước chung lớn nhất (Greatest Common Divisor) của hai số a và b
    Sử dụng thuật toán Euclid
    """
    while b != 0:
        a, b = b, a % b
    return a

def euler_phi_basic(n):
    """
    Tính hàm Euler phi(n) - đếm số lượng số nguyên dương nhỏ hơn n và nguyên tố cùng nhau với n
    Phương pháp cơ bản: kiểm tra từng số từ 1 đến n-1
    
    Args:
        n: Số nguyên dươn
    
    Returns:
        Số lượng các số nguyên tố cùng nhau với n
    """
    if n == 1:
        return 1
    
    count = 0
    for i in range(1, n):
        if gcd(i, n) == 1:
            count += 1
    return count

def euler_phi_optimized(n):
    """
    Tính hàm Euler phi(n) - phương pháp tối ưu
    Sử dụng công thức: phi(n) = n * ∏(1 - 1/p) với p là các ước nguyên tố của n
    
    Args:
        n: Số nguyên dương
    
    Returns:
        Số lượng các số nguyên tố cùng nhau với n
    """
    if n == 1:
        return 1
    
    result = n
    p = 2
    
    # Tìm tất cả các ước nguyên tố của n
    while p * p <= n:
        # Nếu p là ước nguyên tố của n
        if n % p == 0:
            # Loại bỏ tất cả các ước p khỏi n
            while n % p == 0:
                n //= p
            # Áp dụng công thức: result = result * (1 - 1/p) = result * (p-1) / p
            result -= result // p
        p += 1
    
    # Nếu n > 1, thì n là một số nguyên tố
    if n > 1:
        result -= result // n
    
    return result

def list_coprime_numbers(n):
    """
    Liệt kê tất cả các số nguyên tố cùng nhau với n
    
    Args:
        n: Số nguyên dương
    
    Returns:
        Danh sách các số nguyên tố cùng nhau với n
    """
    coprime_list = []
    for i in range(1, n):
        if gcd(i, n) == 1:
            coprime_list.append(i)
    return coprime_list

# Hàm chính để tính Euler phi (mặc định dùng phương pháp tối ưu)
def euler(n):
    """
    Tính hàm Euler phi(n)
    
    Args:
        n: Số nguyên dương
    
    Returns:
        Số lượng các số nguyên tố cùng nhau với n
    """
    return euler_phi_optimized(n)


