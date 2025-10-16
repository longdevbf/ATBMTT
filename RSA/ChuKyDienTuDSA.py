def main():
    p:int=int(input("Nhập số nguyên tố p: "))
    q:int=int(input("Nhập số nguyên tố q: "))
    h:int= int(input("Nhập giá trị băm h: "))
    g = pow(h, (p-1)//q, p)
    HM:int = int(input("Nhập giá trị băm HM: "))
    xA:int=int(input("Nhập khóa riêng xA: "))
    yA = public_key(xA, p, g)
    print("Khóa công khai yA:", yA)
    chu_ky_value = chu_ky(g, p, q, HM, xA)
    print("Chữ ký số (r, s):", chu_ky_value)
    #Cach xác minh chữ ký
    is_valid = xac_minh(chu_ky_value, q, p, HM, g, yA)
    print("Xác minh chữ ký:", "Hợp lệ" if is_valid else "Không hợp lệ")

def public_key(xA:int, p:int, g: int) -> int:
    """
    Tính khóa công khai y = g^xA mod p
    Args:
        xA: Khóa riêng
        p: Số nguyên tố
        g: Cơ số
    Returns:
        Khóa công khai y
    """
    y = pow(g, xA, p)
    return y

k_used = set()
def chu_ky(g, p, q, h, xA) -> tuple:
    """
    Tạo chữ ký số (r, s)
    Args:
        g: Cơ số
        p: Số nguyên tố
        q: Số nguyên tố
        h: Giá trị băm
        xA: Khóa riêng
    Returns:
        Chữ ký số (r, s)
    """
    k = int(input("Nhập số nguyên k: "))
    if k in k_used:
        print("Lỗi: k đã được sử dụng trước đó. Vui lòng chọn k khác.")
        return
    k_used.add(k)
    r = (pow(g,k,p)) % q
    inv_k = pow(k, q-2, q)
    s = ((h + xA * r) * inv_k) % q
    print(f"r = ({g}^{k} mod {p}) mod {q}:", r)
    print(f"s = (({h} + {xA} * {r}) * {inv_k}) mod {q}:", s)
    return (r, s)


def xac_minh(signature:tuple, q, p, h, g, yA) -> bool:
    print("Xác minh chữ ký...")
    r,s = signature
    w = pow(s, q-2, q)
    print(f"w = {s}^(-1) mod {q}:", w)
    u1 = (h * w) % q
    print(f"u1 = ({h} * {w}) mod {q}:", u1)
    u2 = (r * w) % q
    print(f"u2 = ({r} * {w}) mod {q}:", u2)
    v = ((pow(g, u1, p) * pow(yA, u2, p)) % p) % q
    print(f"v = (({g}^{u1} * yA^{u2}) mod {p}) mod {q}:", v)
    return v == r
if __name__ == "__main__":
    main()