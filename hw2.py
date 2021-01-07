import sys
import Techniovision


STAFF_WINNER_EXTRA_SCORE = 20


def _is_inside_contest_line(line_params):
    return line_params[0] == 'inside' and line_params[1] == 'contest'


def _is_staff_choice_line(line_params):
    return line_params[0] == 'staff' and line_params[1] == 'choice'


def _is_techniovision_line(line_params):
    return line_params[0] == 'techniovision'


__study_program_to_faculty = None
__faculty_to_study_programs = None
__faculty_winner_program = None


def _reset():
    global __faculty_to_study_programs
    global __study_program_to_faculty
    global __faculty_winner_program
    __study_program_to_faculty = None
    __faculty_to_study_programs = None
    __faculty_winner_program = None


def get_faculty_for_study_program(study_program, lines):
    global __faculty_winner_program

    if __faculty_winner_program is None:
        _initialize_faculty_study_programs(lines)

    if study_program not in __study_program_to_faculty:
        return None
    return __study_program_to_faculty[study_program]


def _initialize_faculty_study_programs(lines):
    global __study_program_to_faculty
    global __faculty_to_study_programs

    if __faculty_to_study_programs is not None and\
            __study_program_to_faculty is not None:
        return

    __study_program_to_faculty = {}
    __faculty_to_study_programs = {}

    for line in lines:
        line_params = line.split()
        if not _is_staff_choice_line(line_params):
            continue
        faculty = line_params[-1]
        __faculty_to_study_programs[faculty] = line_params[2:-1]
        for study_program in __faculty_to_study_programs[faculty]:
            __study_program_to_faculty[study_program] = faculty


def _initialize_contest_per_faculty(lines):
    global __faculty_to_study_programs

    if __faculty_to_study_programs is None:
        _initialize_faculty_study_programs(lines)

    contest_per_faculty = {}
    for faculty in __faculty_to_study_programs:
        study_programs = __faculty_to_study_programs[faculty]
        scores = [STAFF_WINNER_EXTRA_SCORE] + [0] * len(study_programs)
        contest_per_faculty[faculty] = dict(zip(study_programs, scores))

    return contest_per_faculty


def calculate_faculty_winner_programs(file_name):
    with open(file_name, 'r') as input_file:
        lines = input_file.readlines()

    contest_per_faculty = _initialize_contest_per_faculty(lines)
    student_that_voted = {}

    for line in lines:
        line_params = line.split()
        if not _is_inside_contest_line(line_params):
            continue

        student_id, study_program, faculty = line_params[2:]
        if student_id in student_that_voted:
            continue

        student_that_voted[student_id] = True

        if faculty in contest_per_faculty and study_program in contest_per_faculty[faculty]:
            contest_per_faculty[faculty][study_program] += 1

    faculty_winner_program = {}
    for faculty in contest_per_faculty:
        faculty_winner_program[faculty] = max(contest_per_faculty[faculty],
                                              key=lambda x: contest_per_faculty[faculty][x])

    return faculty_winner_program


def get_faculty_winner_programs(file_name):
    global __faculty_winner_program

    if __faculty_winner_program is not None:
        return __faculty_winner_program

    __faculty_winner_program = calculate_faculty_winner_programs(file_name)
    return __faculty_winner_program


def inside_contest(faculty, file_name):
    faculty_winner_program = get_faculty_winner_programs(file_name)
    if faculty not in faculty_winner_program:
        return None
    return faculty_winner_program[faculty]


def techniovision_winning_faculty(file_name):
    _reset()

    tech_object = Techniovision.TechniovisionCreate()
    with open(file_name, 'r') as input_file:
        lines = input_file.readlines()
    for line in lines:
        line_params = line.split()
        if not _is_techniovision_line(line_params):
            continue
        student_id, voting_program, student_faculty = line_params[1:]
        voting_faculty = get_faculty_for_study_program(voting_program, lines)
        if voting_faculty is None:
            continue
        if inside_contest(voting_faculty, file_name) != voting_program:
            continue
        Techniovision.TechniovisionStudentVotes(tech_object, int(student_id), student_faculty, voting_faculty)

    Techniovision.TechniovisionWinningFaculty(tech_object)
    Techniovision.TechniovisionDestroy(tech_object)


def main(input_path):
    techniovision_winning_faculty(input_path)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        main('input.txt')
    elif len(sys.argv) > 1:
        main(sys.argv[1])
