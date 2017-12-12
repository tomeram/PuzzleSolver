import os
import sys
import random

MAC_PATH = './cmake-build-debug/PuzzleSolver'
EXE_PATH = 'cmake-build-debug\PuzzleSolver.exe'


def random_side():
    values = [-1, 0, 1]

    return random.choice(values)


def generate_puzzle(x, y):
    res = []

    for i in range(0, x):
        res.append([])

        for j in range(0, y):
            l = 0 if j == 0 else -res[i][j - 1][2]
            t = 0 if i == 0 else -res[i - 1][j][3]
            r = random_side() if j < y - 1 else 0
            b = random_side() if i < x - 1 else 0

            res[i].append((l, t, r, b))

    for line in res:
        random.shuffle(line)

    random.shuffle(res)

    return res


def validateSolution(inFile, outFile):
    input = ''
    output = ''

    with open(inFile) as f:
        input = f.read()

    with open(outFile) as f:
        output = f.read()

    pieces = {}

    for line in input.split('\n')[1:]:
        line = line.split()

        if len(line) > 0:
            pieces[line[0]] = line[1:]

    seen = set()
    matrix = []
    lines = output.split('\n')

    for i in range(len(lines)):
        matrix.append([])
        cols = lines[i].split()
        for j in range(len(cols)):
            id = cols[j]
            matrix[i].append(id)

            if id in seen:
                print('Error: Duplicate piece - ' + str(id))
                exit(1)

            seen.add(id)

            if i == 0 and pieces[matrix[i][j]][1] != '0':
                print('Error: ' + str(i) + ', ' + str(j))
                exit(1)
            elif i > 0:
                if int(pieces[matrix[i][j]][1]) + int(pieces[matrix[i-1][j]][3]) != 0:
                    print('Error: ' + str(i) + ', ' + str(j))
                    exit(1)

            if j > 0:
                if int(pieces[matrix[i][j]][0]) + int(pieces[matrix[i][j-1]][2]) != 0:
                    print('Error: ' + str(i) + ', ' + str(j))
                    exit(1)
    print('Success!!!')


def main(args):
    global EXE_PATH

    if len(args) > 1 and args[1] == 'mac':
        EXE_PATH = MAC_PATH

    for i in range(10):
        x = 2
        y = 2

        with open('./ignored/tester.txt', 'w+') as f:
            f.write('NumElements=' + str(x * y) + '\n')

            i = 0

            for line in generate_puzzle(x, y):
                for elem in line:
                    i += 1
                    f.write(str(i) + ' ' + str(elem[0]) + ' ' + str(elem[1]) + ' ' + str(elem[2]) + ' ' + str(elem[3]) + '\n')

        print(os.popen(EXE_PATH + ' ./ignored/tester.txt ./ignored/test.out').read())

        validateSolution('./ignored/tester.txt', './ignored/test.out')


if __name__ == '__main__':
    main(sys.argv)
