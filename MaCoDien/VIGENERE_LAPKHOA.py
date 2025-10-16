def main():
    CHAR = [chr(i) for i in range(65, 91)]
    M = input("Nhập bản rõ: ")
    K = input("Nhập khóa: ")
    M = M.replace(" ", "").upper()
    K = K.replace(" ", "").upper()
    Khoa_lap = ""
    j = 0
    for i in range(len(M)):
        Khoa_lap += K[j]
        j += 1
        if j == len(K):
            j = 0
    print("Khóa lặp: ", Khoa_lap)

    C = ""
    for i in range(len(M)):
        c = ord(M[i]) + ord(Khoa_lap[i]) - 2*65
        C += CHAR[c % 26]
    print("Bản mã: ", C)
if __name__ == "__main__":
    main()