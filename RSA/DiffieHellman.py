def public_key(q, a, x):
    """
    Tính khóa công khai từ khóa riêng và các tham số q, a
    Args:
        q: Số nguyên tố
        a: Số nguyên
        x: Khóa riêng
    
    Returns:
        Khóa công khai
    """
    return pow(a, x, q)
def shared_secret(q, y, x):
    """
    Tính khóa chia sẻ từ khóa công khai của đối tác và khóa riêng của mình
    Args:
        q: Số nguyên tố
        y: Khóa công khai của đối tác
        x: Khóa riêng của mình
    
    Returns:
        Khóa chia sẻ
    """
    return pow(y, x, q)
def main():
    q: int = int(input("Nhập số nguyên tố q: "))
    a: int = int(input("Nhập số nguyên a: "))
    xA: int = int(input("Nhập số khóa riêng của A: "))
    xB: int = int(input("Nhập số khóa riêng của B: "))
    yA: int = public_key(q, a, xA)
    yB: int = public_key(q, a, xB)
    print(f"Khóa công khai của A: {yA}")
    print(f"Khóa công khai của B: {yB}")
    sA: int = shared_secret(q, yB, xA)
    sB: int = shared_secret(q, yA, xB)
    print(f"Khóa phiên của A: {sA}")
    print(f"Khóa phiên của B: {sB}")
if __name__ == "__main__":
    main()