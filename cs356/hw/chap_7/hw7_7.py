# Magic Square Validator

def check_magic(square):
    side_length = len(square[0])
    sums = []
    for column in range(side_length):
        sums.append(sum(row[column] for row in square))
    sums.extend([sum(lines) for lines in square])
    diag = 0
    for i in range(0,side_length):
        diag += square[i][i]
    sums.append(diag)

    if len(set(sums)) > 1:
        return False
    return True

num_square = [[11,18,25,2,9],[10,12,19,21,3],[4,6,13,20,22],[23,5,7,14,16],[17,24,1,8,15]]
print(check_magic(num_square))
