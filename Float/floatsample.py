import random

# Generate 500 random floating-point numbers between 0 and 1000 and store them in a list
random_numbers = [random.uniform(0, 1000) for _ in range(100000)]

# Write the random floating-point numbers to a file named "input.txt"
with open("float.txt", "w") as file:
    for number in random_numbers:
        file.write(f"{number:.5f}\n")

print("Random floating-point numbers between 0 and 1000 have been written to 'float.txt'.")
