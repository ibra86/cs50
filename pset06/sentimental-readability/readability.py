from cs50 import get_string
import re

text = get_string("Text: ")

letters = len([c for c in text if c.isalpha()])
words = len(text.split(' '))
sentences = len([c for c in text if c in ['.', '!', '?']])

L = letters/words * 100
S = sentences / words * 100
index = int(round(0.0588 * L - 0.296 * S - 15.8))

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
