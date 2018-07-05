'''
Assignment 2: Phone Contacts
Evan Conley and Mark Huff
April 16, 2018
'''

def main():
    '''
    Contacts dictionary is designed such that the keys are tuples
    of names and each value is a list where first position is
    the phone number, second is the email, and third is age.
    '''
        
    #Creation of contacts dictionary to store contact information
    contacts = {}

    #Test cases
    create_contact(contacts, "Katie", "Katz", "katie.katz@nau.edu", 25, "857-294-2758")
    create_contact(contacts,"Jim", "Jones", "jim.jones@nau.edu", 19, "525-866-2749")
    create_contact(contacts,"Sarah", "Sanders", "sarah.sanders@nau.edu", 18, "593-026-2532")
	
    print("Creation of Jim Jones: {}".format("Passed" if contains_contact(contacts,"jim","Jones") else "Failed"))
    print("Creation of Katie Katz: {}".format("Passed" if contains_contact(contacts,"Katie","kaTz") else "Failed"))
    print("Creation of Sarah Sanders: {}".format("Passed" if contains_contact(contacts,"Sarah","Sanders") else "Failed"))
	
    update_contact_age(contacts, "Sarah", "Sanders", 19)
    print("Updating Sarah Sanders age to 19: {}".format("Passed" if get_contact_age(contacts,"sarah", "sanDers") == 19 else "Failed"))
    update_contact_email(contacts, "Jim", "Jones", "jim.jones@gmail.com")
    print("Updating Jim Jones email: {}".format("Passed" if get_contact_email(contacts,"jim","jones") == "jim.jones@gmail.com" else "Failed"))
    update_contact_number(contacts,"Katie", "Katz", "907-536-2946")
    print("Updating Katie Katz's number: {}".format("Passed\n" if get_contact_number(contacts,"Katie", "Katz") == "907-536-2946" else "Failed\n"))
    display(contacts, "Katie", "Katz")
    display(contacts, "George", "Shaw")

def format_name_keys(first, last):
    '''
    Helper function to format names entered to be stored in contact list.
    This will return a tuple of first and last names in lower case.
    '''
    return (first.lower(),last.lower())

def create_contact(contacts, first, last, email, age, phone):
    '''Creates contact with passed information and stores it into the passed in dictionary.'''
    name_tup = format_name_keys(first,last)
    contacts[name_tup] = [phone, email, age]

def update_contact_number(contacts, first, last, number):
    '''Updates the number of the associated contact.'''
    name_tup = format_name_keys(first,last)
    contacts[name_tup][0] = number
	
def update_contact_email(contacts, first, last, email):
    '''Updates email of the associated contact.'''
    name_tup = format_name_keys(first,last)
    contacts[name_tup][1] = email

def update_contact_age(contacts, first, last, age):
    '''Updates the age of the associated contact.'''
    name_tup = format_name_keys(first,last)
    contacts[name_tup][2] = age
	
def get_contact_email(contacts, first, last):
    '''Returns email of associated contact.'''
    name_tup = format_name_keys(first,last)
    return contacts[name_tup][1]

def get_contact_age(contacts, first, last):
    '''Returns age of associated contact.'''
    name_tup = format_name_keys(first,last)
    return contacts[name_tup][2]

def get_contact_number(contacts, first, last):
    '''Returns phone number of associated contact.'''
    name_tup = format_name_keys(first,last)
    return contacts[name_tup][0]

def contains_contact(contacts, first, last):
	'''
    Returns True if contacts dictionary contains
    the passed in name. False if otherwise.
    '''
	name_tup = format_name_keys(first,last)
	if name_tup in contacts:
		return True
	else:
		return False

def display(contacts, first, last):
	'''
    Displays contact information of passed in contact or
    an error message if the dictionary does not contains contact.
    '''
	if contains_contact(contacts, first,last):
		email = get_contact_email(contacts,first, last)
		phone = get_contact_number(contacts,first,last)
		age = get_contact_age(contacts,first,last)
		print(first, last+":")
		print("Age:",age)
		print("Phone:",phone)
		print("Email:",email,"\n")
	else:
		print("ERROR: Contact does Not Exist")

if __name__ == "__main__":
    main()
