import random
import string


random_characters = [random.choice(string.ascii_lowercase) for _ in range(100000)]

with open("char.txt", "w") as file:
    for character in random_characters:
        file.write(f"{character}\n")

print("Random characters have been written to 'char.txt'.")
