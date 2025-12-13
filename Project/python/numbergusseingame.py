import random
print("Welcome to the Number Guessing Game!")
print("I'm thinking of a number between 1 and 100...")

# Computer generates a random number
secret_number = random.randint(1, 100)

attempts = 0  # count user guesses

while True:
    guess = int(input(" Enter your guess: "))
    attempts += 1

    if guess < secret_number:
        print("Too low! Try again.\n")
    elif guess > secret_number:
        print(" Too high! Try again.\n")
    else:
        print(f" Correct! You guessed it in {attempts} attempts.")
        break
