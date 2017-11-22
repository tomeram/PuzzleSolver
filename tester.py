import os
import random

SIZE = 10


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


def main():
    x = 6
    y = 6

    with open('./ignored/tester.txt', 'w+') as f:
        f.write('NumElements=' + str(x * y) + '\n')

        i = 0

        for line in generate_puzzle(x, y):
            for elem in line:
                i += 1
                f.write(str(i) + ' ' + str(elem[0]) + ' ' + str(elem[1]) + ' ' + str(elem[2]) + ' ' + str(elem[3]) + '\n')

    # res = os.popen('./cmake-build-debug/PuzzleSolver ./ignored/tester.txt test.out').read()
    # print res

    os.system('./cmake-build-debug/PuzzleSolver ./ignored/tester.txt test.out')


if __name__ == '__main__':
    main()
