import random
import string

# Function to generate a random string of a given length
def generate_random_string(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

# Generate 500 random strings of length 10 and store them in a list
random_strings = [generate_random_string(10) for _ in range(100000)]

# Write the random strings to a file named "strings.txt"
with open("strings.txt", "w") as file:
    for s in random_strings:
        file.write(f"{s}\n")

print("Random strings have been written to 'strings.txt'.")
