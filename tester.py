import os
import sys
import time
import random

MAC_PATH = './cmake-build-debug/PuzzleSolver'
EXE_PATH = 'cmake-build-debug\PuzzleSolver.exe'


class Piece:
    def __init__(self, l, t, r, b, id):
        self.id = id
        self.sides = [l, t, r, b]
        self.rotation = 0

    def rotate(self, deg=None):
        if deg == 90:
            self.rotation = 3
        elif deg == 180:
            self.rotation = 2
        elif deg == 270:
            self.rotation = 1
        elif deg is None:
            self.rotation = 0
        else:
            print('error')

    def left(self):
        return self.sides[self.rotation]

    def top(self):
        return self.sides[(self.rotation + 1) % 4]

    def right(self):
        return self.sides[(self.rotation + 2) % 4]

    def bottom(self):
        return self.sides[(self.rotation + 3) % 4]


def rotate_piece(piece):
    n = random.randrange(0, 3)
    return piece[-n:] + piece[:-n]


def random_side():
    values = [-1, 0, 1]

    return random.choice(values)


def generate_puzzle(x, y, rotate):
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
        if rotate:
            for piece in line:
                rotate_piece(piece)

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
            l = int(line[1])
            t = int(line[2])
            r = int(line[3])
            b = int(line[4])

            pieces[line[0]] = Piece(l, t, r, b, line[0])

    seen = set()
    matrix = []
    lines = output.split('\n')

    for row in range(len(lines)):
        matrix.append([])
        cols = lines[row].split()

        colsIter = iter(range(len(cols)))
        col = -1

        for j in colsIter:
            col += 1
            id = cols[j]
            matrix[row].append(id)

            if id in seen:
                print('Error: Duplicate piece - ' + str(id))
                exit(1)

            seen.add(id)
            piece = pieces[id]

            if j + 1 < len(cols) and '[' in cols[j + 1]:
                s = cols[j + 1].index('[') + 1
                e = cols[j + 1].index(']')
                piece.rotate(int(cols[j + 1][s:e]))

                next(colsIter)

            if row == 0 and piece.top() != 0:
                print('Error: ' + str(row) + ', ' + str(col))
                exit(1)
            elif row > 0:
                if int(piece.top()) + int(pieces[matrix[row-1][col]].bottom()) != 0:
                    print('Error: ' + str(row) + ', ' + str(col))
                    exit(1)

            if j > 0:
                if int(piece.left()) + int(pieces[matrix[row][col-1]].right()) != 0:
                    print('Error: ' + str(row) + ', ' + str(col))
                    exit(1)
    print('Success!!!')


def main(args):
    global EXE_PATH
    rotation = False

    if len(args) > 1:
        for arg in args:
            if arg == 'mac':
                EXE_PATH = MAC_PATH
            elif arg == 'rotate':
                rotation = True

    for j in range(1, 2):
        x = 3
        y = 6

        with open('./ignored/tester.txt', 'w+') as f:
            f.write('NumElements=' + str(x * y) + '\n')

            i = 0

            for line in generate_puzzle(x, y, rotation):
                for elem in line:
                    i += 1
                    f.write(str(i) + ' ' + str(elem[0]) + ' ' + str(elem[1]) + ' ' + str(elem[2]) + ' ' + str(elem[3]) + '\n')

        start = time.time()
        rotate = '' if not rotation else ' -rotate'

        print(os.popen(EXE_PATH + ' ./ignored/tester.txt ./ignored/test.out' + rotate).read())
        end = time.time()
        print('Test ' + str(j))
        print('Elapsed time: ' + str(end - start))

        try:
            validateSolution('./ignored/tester.txt', './ignored/test.out')
        except:
            print('Failed :(')
            return


if __name__ == '__main__':
    main(sys.argv)
