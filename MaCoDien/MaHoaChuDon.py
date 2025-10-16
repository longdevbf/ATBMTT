def main():
    dict_char ={}
    CHAR = [chr(i) for i in range(65, 91)]
    M = input("Nhập bản rõ: ").upper()
    M = M.replace(" ", "")
    k = input("Nhập khóa: ").upper()
    k = k.replace(" ", "")
    print("Ánh xạ:")
    for i in range(len(CHAR)):
        dict_char[CHAR[i]] = k[i] 
        print(f"{CHAR[i]} -> {dict_char[CHAR[i]]}")
    C= ""
    for i in M:
        C+= dict_char[i]
    print("Bản mã: ", C)
if __name__ == "__main__":
    main()