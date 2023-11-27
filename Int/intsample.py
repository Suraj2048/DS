import random

random_numbers = [random.randint(1, 10000) for _ in range(100)]

with open("int.txt", "w") as file:
    for number in random_numbers:
        file.write(f"{number}\n")

print("Random numbers have been written to 'int.txt'.")
