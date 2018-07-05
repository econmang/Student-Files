def main():
    state_dict = {"CA":{"Official":"Dave", "Number":8675309}, "OR":{"Official":"Steve","Number":911}}
    state = input("Enter the 2 character code of a state: ")
    try:
        print(state_dict[state]["Official"])
        print(state_dict[state]["Number"])
    except:
        print("Incorrectly specified input.")


if __name__ == "__main__":
    main()
