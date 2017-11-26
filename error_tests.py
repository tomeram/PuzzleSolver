import os

EXE_PATH = './cmake-build-debug/PuzzleSolver'


def run_with_arguments(input_file, output_file):
    return os.popen(EXE_PATH + ' ' + input_file + ' ' + output_file).read()


def check_wrong_args():
    output = run_with_arguments('test123', '123test')

    if 'Please supply correct input and output file paths:' not in output:
        print 'Fail: wrong path'
        print output
        return False

    return True


def check_empty_file():
    file_name = 'empty_test.txt'

    success = True

    with open(file_name, 'w+') as f:
        output = run_with_arguments(file_name, '123test')

        if 'Invalid file format' != output.strip():
            print 'Fail: empty file'
            print output
            success = False

    os.remove(file_name)

    return success


def no_num_elements():
    output = run_with_arguments('tests/no_numelements.txt', '123test')

    if 'Invalid file format' != output.strip():
        print 'Fail: Missing NumElements'
        print output
        return False

    return True


def invalid_piece():
    output = run_with_arguments('tests/invalid_piece.txt', '123test')

    if 'Puzzle ID 1 has wrong data: 1 1 1 -1' != output.strip():
        print 'Fail: Invalid piece sides'
        print output
        return False

    return True


def invalid_piece_numbers():
    output = run_with_arguments('tests/invalid_numbers.txt', '123test')

    if 'Puzzle ID 2 has wrong data: 2 1 1 a 1' != output.strip():
        print 'Fail: Invalid piece data'
        print output
        return False

    return True


def extra_pieces():
    output = run_with_arguments('tests/extra_pieces.txt', '123test')

    if 'Puzzle of size 2 cannot have the following IDs: 3, 4' != output.strip():
        print 'Fail: extra_pieces'
        print output
        return False

    return True


def missing_pieces():
    output = run_with_arguments('tests/missing_pieces.txt', '123test')

    if 'Missing puzzle element(s) with the following IDs: 2, 3' != output.strip():
        print 'Fail: Invalid Piece'
        print output
        return False

    return True


def duplicate_pieces():
    output = run_with_arguments('tests/duplicate_pieces.txt', '123test')

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