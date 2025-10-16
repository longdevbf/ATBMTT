def main():
    M = input("Nhập bản rõ: ").upper()
    K = int(input("Nhập khóa: "))
    table = [[] for _ in range(K)]
    down = True
    index = 0
    for char in M:
        table[index].append(char)
        if down:
            index += 1
            if index == K:
                index = K - 2
                down = False
        else:
            index -= 1
            if index == -1:
                index = 1
                down = True

    # Mã hóa
    ciphertext = ""
    for row in table:
        ciphertext += "".join(row)
    print("Bản mã: ", ciphertext)

if __name__ == "__main__":
    main()