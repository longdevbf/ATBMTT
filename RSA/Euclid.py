def gcd(a: int, b: int) -> int:
    """
    Tính ước số chung lớn nhất (GCD) của hai số nguyên a và b
    Sử dụng thuật toán Euclid
    
    Args:
        a: Số nguyên dương
        b: Số nguyên dương
    
    Returns:
        GCD của a và b
    """
    if a < 0 or b < 0:
        raise ValueError("Cả hai số phải là số nguyên dương")
    
    if a == 0:
        return b
    if b == 0:
        return a
    return gcd(b, a % b)
def eclid_extended(a: int, m: int, x: int, y:int ) -> list:
    """
    Tính toán ước số chung lớn nhất (GCD) của a và m, đồng thời tìm x và y sao cho ax + my = GCD(a, m)
    
    Args:
        a: Số nguyên dương
        m: Số nguyên dương
        x: Biến để lưu giá trị x
        y: Biến để lưu giá trị y
    
    Returns:
        Danh sách chứa GCD, x, y
    """
    if m == 0:
        return [a, 1, 0]
    
    gcd, x1, y1 = eclid_extended(m, a % m, x, y)
    
    x = y1
    y = x1 - (a // m) * y1

    return [gcd, x, y]
def Inverse(a: int, m: int) -> int:
    """
    Tính nghịch đảo modulo của a theo m
    Sử dụng thuật toán Euclid mở rộng
    
    Args:
        a: Số nguyên dương
        m: Số nguyên dương
    
    Returns:
        Nghịch đảo của a theo m
    """
    gcd, x, _ = eclid_extended(a, m, 0, 0)
    
    if gcd != 1:
        raise ValueError(f"{a} và {m} không có nghịch đảo modulo")
    
    return (x % m + m) % m