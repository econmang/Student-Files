def has_vowel(word):
    vowels = {'a','e','i','o','u','y'}
    for vowel in vowels:
        if vowel in word:
            return True
    return False

def has_vowel_set(word):
    vowels = {'a','e','i','o','u','y'}
    if vowels.intersection(word):
        return True
    return False


print(has_vowel("car"))
print(has_vowel("hmm"))
print(has_vowel("gypsy"))
print("\n")
print(has_vowel_set("car"))
print(has_vowel_set("hmm"))
print(has_vowel_set("gypsy"))
