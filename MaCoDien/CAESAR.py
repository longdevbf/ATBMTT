def main():
       # ANSI color codes
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    CYAN = '\033[96m'
    RESET = '\033[0m'
    print(f"{CYAN}=== Chương trình mã hóa Caesar ==={RESET}")
    CHAR = [chr(i) for i in range(65, 91)]
    M = input(f"{YELLOW}Nhập bản rõ: {RESET}").upper()
    M.replace(" ", "")
    k = int(input(f"{YELLOW}Nhập khóa: {RESET}"))
    print(f"{CYAN}Ánh xạ:{RESET}")
    for i in M:
        if i in CHAR:
            idx = (CHAR.index(i) + k) % 26
            print(f"{i} -> {CHAR[idx]}")
        else:
            print(f"{i} -> {i}")

    print(f"{CYAN}Bản mã: {RESET}", end="")
    for i in M:
        if i in CHAR:
            idx = (CHAR.index(i) + k) % 26
            print(f"{CHAR[idx]}", end="")
        else:
            print(f"{i}", end="")
    print()
if __name__ == "__main__":
    main()
