'''
Evan Conley
Prof. Vanderburg
CS 356

Problem Number: 1
Problem Statement: Need to create a program that will determine how many unique stencils are needed for a given
                   string stenciled onto a t-shirt.
Assumptions: User can input a string to be stenciled on a t-shirt.
             String may contain alphanumeric and UTF-8 encoded symbols.
             String must be of a reasonable size (i.e. less than 50 characters) to fit on a shirt.
'''


def num_stencils(stencil_string):
    '''Takes as  input the string to be stenciled onto a shirt and returns the number of unique stencils needed for that string.'''
    letter_stencils = []
    for letter in stencil_string:
        letter_stencils.append(letter)
    return len(set(letter_stencils))


def main():
    stencil_input = str(input("Hello! Please enter the string you'd like embroidered on your t-shirt: ")) #input = Potatoes are dope sauce biscuits!
    if len(stencil_input) > 50:
        print("That won't fit on a shirt buddy!")
    else:
        print("To make that T-shirt with the %d characters, we would need %d unique stencils." % (len(stencil_input),num_stencils(stencil_input)))
        # Expected Output: To make that T-shirt with the 33 characters, we would need 15 unique stencils.


if __name__ == '__main__':
    main()
