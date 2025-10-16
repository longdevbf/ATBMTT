# File demo: Cách gọi hàm từ Euler.py

# Cách 1: Import toàn bộ module
import Euler

print("=== CÁCH 1: Import toàn bộ module ===")
n = 20
result = Euler.euler(n)
print(f"Euler.euler({n}) = {result}")

coprime_list = Euler.list_coprime_numbers(n)
print(f"Các số nguyên tố cùng nhau với {n}: {coprime_list}")
print()

# Cách 2: Import các hàm cụ thể
from Euler import euler, list_coprime_numbers, gcd, euler_phi_basic, euler_phi_optimized

print("=== CÁCH 2: Import các hàm cụ thể ===")
n = 15
result = euler(n)
print(f"euler({n}) = {result}")

# Tính GCD
a, b = 24, 18
print(f"GCD({a}, {b}) = {gcd(a, b)}")
print()

# So sánh hai phương pháp
print("=== SO SÁNH HAI PHƯƠNG PHÁP ===")
n = 100
print(f"Phương pháp cơ bản: euler_phi_basic({n}) = {euler_phi_basic(n)}")
print(f"Phương pháp tối ưu: euler_phi_optimized({n}) = {euler_phi_optimized(n)}")
print()

# Ứng dụng trong RSA
print("=== ỨNG DỤNG TRONG RSA ===")
p = 17  # Số nguyên tố p
q = 19  # Số nguyên tố q
n = p * q
phi_n = (p - 1) * (q - 1)  # Công thức cho RSA

print(f"p = {p}, q = {q}")
print(f"n = p × q = {n}")
print(f"φ(n) = (p-1) × (q-1) = {phi_n}")
print(f"Kiểm tra bằng hàm euler: euler({n}) = {euler(n)}")
print(f"Kết quả khớp: {phi_n == euler(n)}")
