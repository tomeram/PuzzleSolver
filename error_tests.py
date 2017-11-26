import os

EXE_PATH = './cmake-build-debug/PuzzleSolver'


def run_prog(input_file, output_file):
    return os.popen(EXE_PATH + ' ' + input_file + ' ' + output_file).read()


def run_with_arguments(input_file, output_file):
    run_prog(input_file, output_file)

    with open(output_file) as f:
        return f.read()


def check_wrong_args():
    output = run_prog('test123', 'test.out')

    if 'Please supply correct input and output file paths:' not in output:
        print 'Fail: check_wrong_args'
        print output
        return False

    return True


def check_empty_file():
    file_name = 'empty_test.txt'

    success = True

    with open(file_name, 'w+') as f:
        output = run_prog(file_name, 'test.out')

        if 'Invalid file format' != output.strip():
            print 'Fail: check_empty_file'
            print output
            success = False

    os.remove(file_name)

    return success


def no_num_elements():
    output = run_prog('tests/no_numelements.txt', 'test.out')

    if 'Invalid file format' != output.strip():
        print 'Fail: no_num_elements'
        print output
        return False

    return True


def invalid_piece():
    output = run_with_arguments('tests/invalid_piece.txt', 'test.out')

    if 'Puzzle ID 1 has wrong data: 1 1 1 -1' != output.strip():
        print 'Fail: invalid_piece'
        print output
        return False

    return True


def invalid_piece_numbers():
    output = run_with_arguments('tests/invalid_numbers.txt', 'test.out')

    if 'Puzzle ID 1 has wrong data: 1 0 0 0 a\nPuzzle ID 2 has wrong data: 2 1 1 a 1' != output.strip():
        print 'Fail: invalid_piece_numbers'
        print output
        return False

    return True


def extra_pieces():
    output = run_with_arguments('tests/extra_pieces.txt', 'test.out')

    if 'Puzzle of size 2 cannot have the following IDs: 3, 4' != output.strip():
        print 'Fail: extra_pieces'
        print output
        return False

    return True


def missing_pieces():
    output = run_with_arguments('tests/missing_pieces.txt', 'test.out')

    if 'Missing puzzle element(s) with the following IDs: 2, 3' != output.strip():
        print 'Fail: missing_pieces'
        print output
        return False

    return True


def duplicate_pieces():
    output = run_with_arguments('tests/duplicate_pieces.txt', 'test.out')

    if 'Puzzle of size 2 has duplicate IDs: 1, 2' != output.strip():
        print 'Fail: duplicate_pieces'
        print output
        return False

    return True


def missing_corners():
    # TODO
    return True


def missing_edges():
    # TODO
    return True


def main():
    success = True

    success = success and check_wrong_args()
    success = success and check_empty_file()
    success = success and no_num_elements()
    success = success and invalid_piece()
    success = success and invalid_piece_numbers()
    success = success and extra_pieces()
    success = success and missing_pieces()
    success = success and duplicate_pieces()
    success = success and missing_corners()
    success = success and missing_edges()

    if success:
        print '\o/ Success!'
    else:
        print ':( Fail!'
    pass


if __name__ == '__main__':
    main()