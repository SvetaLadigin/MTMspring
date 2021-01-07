import hw2

import io
import os

from stdout_redirector import stdout_redirector

INPUT_STR_LEN = len('input')


def compare_input_files(input_name):
    return int(input_name[INPUT_STR_LEN:])


def get_input_files():
    input_files = filter(lambda x: 'input' in x, os.listdir('face_tests1'))
    input_files = list(input_files)
    input_files.sort(key=compare_input_files)
    return [os.path.join('face_tests1', x) for x in input_files]


def get_expected_results():
    with open('face_tests1/finalresults.txt', 'r') as results:
        return results.readlines()


def get_faculty_from_result(result):
    return result[len('"Nehshevet" Faculty for this year is '):-4]


def test_inside_contest(input_file, expected_result):
    f = io.BytesIO()
    with stdout_redirector(f):
        hw2.main(input_file)

    result = f.getvalue().decode('utf-8')

    result = get_faculty_from_result(result)
    expected_result = get_faculty_from_result(expected_result)

    if result != expected_result:
        print("{} failed, {} != {}".format(input_file, result, expected_result))
    else:
        print("{} passed".format(input_file))


def main():
    input_files = get_input_files()
    expected_results = get_expected_results()

    for i in range(0, len(input_files)):
        test_inside_contest(input_files[i], expected_results[i])


if __name__ == '__main__':
    main()
