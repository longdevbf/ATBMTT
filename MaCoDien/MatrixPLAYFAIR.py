CHAR = [chr(i) for i in range(65, 91)]
def Encrypt(pairs, matrix) -> str:
    C = ""
    for pair in pairs:
        r1, c1, r2, c2 = -1, -1, -1, -1
        for r in range(5):
            for c in range(5):
                if matrix[r][c] == pair[0]:
                    r1, c1 = r, c
                if matrix[r][c] == pair[1]:
                    r2, c2 = r, c
        if r1 == r2:
            C += matrix[r1][(c1 + 1) % 5]
            C += matrix[r2][(c2 + 1) % 5]
        elif c1 == c2:
            C += matrix[(r1 + 1) % 5][c1]
            C += matrix[(r2 + 1) % 5][c2]
        else:
            C += matrix[r1][c2]
            C += matrix[r2][c1]
    return C


def create_matrix(K) -> list:
    matrix = [['' for _ in range(5)] for _ in range(5)]
    used = set()
    row, col = 0, 0
    for char in K:
        if char not in used:
            used.add(char)
            matrix[row][col] = char
            col += 1
            if col == 5:
                col = 0
                row += 1
    for char in CHAR:
        if char == 'J':
            if 'I' in used:
                continue
        if char not in used:
            used.add(char)
            matrix[row][col] = char
            col += 1
            if col == 5:
                col = 0
                row += 1
    return matrix

def main():
    M = input("Nhập bản rõ: ").upper()
    K = input("Nhập khóa: ").upper()
    matrix = create_matrix(K)
    print("Ma trận:")
    for row in matrix:
        print(' '.join(row))
    M = M.replace(" ", "").replace("J", "I")
    K = K.replace(" ", "").replace("J", "I")
    
    pairs = []
    i = 0
    while i < len(M):
        char1 = M[i]
        if i + 1 < len(M):
            char2 = M[i + 1]
            if char1 == char2:
                pairs.append((char1, 'X'))
                i += 1
            else:
                pairs.append((char1, char2))
                i += 2
        else:
            pairs.append((char1, 'X'))
            i += 1
    C = Encrypt(pairs, matrix)
    print("Bản mã: ", C)




if __name__ == "__main__":
    main()