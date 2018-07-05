def remove_smallest(list_scores):
    list_scores.remove(min(list_scores))
    return list_scores

print(remove_smallest([95,92,67,85]))
print(remove_smallest([76,81,89,67]))
print(remove_smallest([81,75,86,89]))
