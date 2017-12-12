import os
import sys

MAC_PATH = './cmake-build-debug/PuzzleSolver'
EXE_PATH = 'cmake-build-debug\PuzzleSolver.exe'


def run_prog(input_file, output_file):
    return os.popen(EXE_PATH + ' ' + input_file + ' ' + output_file).read()


def run_with_arguments(input_file, output_file):
    run_prog(input_file, output_file)

    with open(output_file) as f:
        return f.read()


def check_wrong_args():
    output = run_prog('test123', 'test.out')

    if 'Please supply correct input and output file paths:' not in output:
        print('Fail: check_wrong_args')
        print(output)
        return False

    return True


def check_empty_file():
    file_name = 'empty_test.txt'

    success = True

    with open(file_name, 'w+') as f:
        output = run_prog(file_name, 'test.out')

        if 'Invalid file format' != output.strip():
            print('Fail: check_empty_file')
            print(output)
            success = False

    os.remove(file_name)

    return success


def no_num_elements():
    output = run_prog('tests/no_numelements.txt', 'test.out')

    if 'Invalid file format' != output.strip():
        print('Fail: no_num_elements')
        print(output)
        return False

    return True


def invalid_piece():
    output = run_with_arguments('tests/invalid_piece.txt', 'test.out')

    if 'Puzzle ID 1 has wrong data: 1 1 1 -1' != output.strip():
        print('Fail: invalid_piece')
        print(output)
        return False

    return True


def invalid_piece_numbers():
    output = run_with_arguments('tests/invalid_numbers.txt', 'test.out')

    if 'Puzzle ID 1 has wrong data: 1 0 0 0 a\nPuzzle ID 2 has wrong data: 2 1 1 a 1' != output.strip():
        print('Fail: invalid_piece_numbers')
        print(output)
        return False

    return True


def extra_pieces():
    output = run_with_arguments('tests/extra_pieces.txt', 'test.out')

    if 'Puzzle of size 2 cannot have the following IDs: 3, 4' != output.strip():
        print('Fail: extra_pieces')
        print(output)
        return False

    return True


def missing_pieces():
    output = run_with_arguments('tests/missing_pieces.txt', 'test.out')

    if 'Missing puzzle element(s) with the following IDs: 2, 3' != output.strip():
        print('Fail: missing_pieces')
        print(output)
        return False

    return True


def duplicate_pieces():
    output = run_with_arguments('tests/duplicate_pieces.txt', 'test.out')

    if 'Puzzle of size 2 has duplicate IDs: 1, 2' != output.strip():
        print('Fail: duplicate_pieces')
        print(output)
        return False

    return True


def missing_corners():
    output = run_with_arguments('tests/missing_corners.txt', 'test.out')

    if 'Cannot solve puzzle: wrong number of straight edges\n' \
       'Cannot solve puzzle: missing corner element: TL\n' \
       'Cannot solve puzzle: missing corner element: TR\n' \
       'Cannot solve puzzle: missing corner element: BL\n' \
       'Cannot solve puzzle: missing corner element: BR' != output.strip():
        print('Fail: missing_corners')
        print(output)
        return False

    return True


def missing_edges():
    output = run_with_arguments('tests/missing_edges.txt', 'test.out')

    if 'Cannot solve puzzle: wrong number of straight edges' != output.strip():
        print('Fail: missing_edges')
        print(output)
        return False

    return True


def no_sol():
    output = run_with_arguments('tests/no_sol.txt', 'test.out')

    if 'Cannot solve puzzle: it seems that there is no proper solution' != output.strip():
        print('Fail: no_sol')
        print(output)
        return False

    return True


def main(args):
    global EXE_PATH

    if len(args) > 1 and args[1] == 'mac':
        EXE_PATH = MAC_PATH

    success = True

    success = check_wrong_args() and success
    success = check_empty_file() and success
    success = no_num_elements() and success
    success = invalid_piece() and success
    success = invalid_piece_numbers() and success
    success = extra_pieces() and success
    success = missing_pieces() and success
    success = duplicate_pieces() and success
    success = missing_corners() and success
    success = missing_edges() and success
    success = no_sol() and success

    if success:
        print('\o/ Success!')
    else:
        print(':( Fail!')
    pass


if __name__ == '__main__':
    main(sys.argv)
