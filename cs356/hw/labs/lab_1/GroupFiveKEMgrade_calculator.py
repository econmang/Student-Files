"""
Lab01 Grade Calculator

Kyle Calvert, Evan Conley, Matt Bolenbaugh

April 11, 2018
"""


def main():
    # given values

    homework = [38, 40, 29, 40, 0, 5]
    homework_max = [40, 40, 40, 40, 40, 5]
    homework_weight = 0.2

    quizzes = [10, 10, 9, 2, 10, 10, 10]
    quizzes_max = [10, 10, 10, 10, 10, 10, 10]
    quizzes_weight = 0.2

    tests = [293, 284, 300]
    tests_max = [300, 300, 300]
    tests_weight = 0.6

    # Weighted values stored in variables to be added together to be sent to
    # letter_grade()
    hw_avg = average_weigted(homework, homework_max, homework_weight)
    quiz_avg = average_weigted(quizzes, quizzes_max, quizzes_weight)
    test_avg = average_weigted(tests, tests_max, tests_weight)
    percent = hw_avg + quiz_avg + test_avg

    # Formatting graded output
    print("%d%% Homework Grade: %d%%" % (homework_weight * 100, round(average(homework, homework_max) * 100)))
    print("%d%% Quiz Grade: %d%%" % (quizzes_weight * 100, round(average(quizzes, quizzes_max) * 100)))
    print("%d%% Test Grade: %d%%" % (tests_weight * 100, round(average(tests, tests_max) * 100)))
    print("Final Score: %d%% (%s)" % (round(percent * 100.0), letter_grade(percent)))


def average(score_list, max_list):
    '''Sums total points scored divided by total points available
    returning normalized average score'''
    return sum(score_list) / sum(max_list)


def average_weigted(score_list, max_list, weight):
    '''Takes the average of the two lists and multiplied by the weight'''
    return average(score_list,max_list) * weight


def letter_grade(percent):
    '''
    Takes the average weighted of homework, quizzes, and tests added together
    times it by 100 to be in percent form and returns a letter grade
    '''

    percent = percent * 100
    if percent >= 90:
        return 'A'
    elif percent >= 80:
        return 'B'
    elif percent >= 70:
        return 'C'
    elif percent > 60:
        return 'D'
    elif percent >= 0:
        return 'F'

    return 'error: percent less than 0'


if __name__ == "__main__":
    main()
