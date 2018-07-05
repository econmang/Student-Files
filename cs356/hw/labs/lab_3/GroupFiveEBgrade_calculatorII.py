"""
Lab 3: Grade Calculator (I/O Refactoring)
Author: Evan Conley, Brandon Burton
Date: April 23, 2018
Purpose: Refactoring grade calculator code so that it can utilize file I/O instead of hard code values.
         Should take input read in from an input file. The data from this file should be parsed and
         separated by grade classification/type (determined by String at the beginning in each line).
         From this point, it should find the weighted averages of each section, and output the overall
         grade in the form of a percentage and a letter.
"""

import re
import sys

def main():

    file_name = str(input("Please enter a filename: "))
    try:
        fh = open(file_name, 'r')
        dictionary = {}
        
        file_parser(fh,dictionary)
        for cat in dictionary:
            avg = average(dictionary[cat]['grades'],dictionary[cat]['maxes'])
            dictionary[cat]['avg_grade'] = avg
            w_avg = average_weighted(dictionary[cat]['grades'],dictionary[cat]['maxes'],dictionary[cat]['weight'])
            dictionary[cat]['weighted_avg'] = w_avg
        file_output(dictionary)
        fh.close()
    except IOError:
        print("File does not exist")


def file_parser(fh, dictionary):
    '''Parses through an input file and attempts to clean and collect valid input. Returns dictionary
    of collected inputs'''
    try:
        for line in fh:
            line = re.sub(' +',' ',line).rstrip().lstrip()
            line = line.replace('\n','')
            temp_line = line.split(' ')
            category = temp_line[0].lower()
            if len(temp_line) < 3:
                raise IOError
            weight_to_filter = temp_line[1]
            grades_to_filter = temp_line[2]
            dictionary[category] = {}
            weight = float('%.3f' % (0.01 * float(re.sub('%','',weight_to_filter))))
            if weight < 0.0 or weight > 1.0:
                raise ValueError
            dictionary[category]['weight'] = weight
            grades = grades_to_filter.split(',')
            grades = list(filter(lambda grade: grade.strip(), grades))
            dictionary[category]['maxes'] = []
            dictionary[category]['grades'] = []
            for elt in grades:
                split_elt = elt.split('/')
                dictionary[category]['maxes'].append(int(split_elt[1]))
                dictionary[category]['grades'].append(int(split_elt[0]))
    except ValueError:
        print("Weight/numbers not specified correctly.")
        sys.exit()
    except IOError:
        print("Lines not formatted correctly or are missing arguments.")
        sys.exit()


def average(score_list, max_list):
    '''Sums total points scored divided by total points available
    returning normalized average score'''
    return sum(score_list) / sum(max_list)


def average_weighted(score_list, max_list, weight):
    '''Takes the average of the two lists and multiplied by the weight'''
    return average(score_list,max_list) * weight


def letter_grade(percent):
    '''
    Takes the average weighted of homework, quizzes, and tests added together
    times it by 100 to be in percent form and returns a letter grade
    '''
    percent = percent * 100
    if percent > 100:
        return "A++ (Extra Credit, eh!)"
    elif percent >= 90:
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


def file_output(dictionary):
    '''Outputs the graded dictionary values into an html file.'''
    f_out = open('grades.html','w')
    output = ""
    final_score = 0
    for cat in dictionary:
        output += "<h1>%s Statistics (%.1f)</h1>\n" % (cat.capitalize(), dictionary[cat]['weight']*100)
        output += "<ul>\n<li><b>Average: </b>%.2f</li>\n<li><b>Letter Grade: </b>%s</li>\n" % (dictionary[cat]['avg_grade'],letter_grade(dictionary[cat]['avg_grade']))
        output += "<li><b>Overall Grade Contribution: </b>%.3f</li>\n</ul>\n" % (dictionary[cat]['weighted_avg'])
        final_score += dictionary[cat]['weighted_avg']
    output += "\n<h1>Final Grade: %.2f%% (<b>%s</b>)</h1>" % (final_score*100, letter_grade(final_score))
    f_out.write(output)
    f_out.close()

if __name__ == "__main__":
    main()
