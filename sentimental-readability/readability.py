from cs50 import get_string



def main():
    text = get_string("Text: ")

    l = get_letters(text)
    w = get_words(text)
    s = get_sentences(text)

    grade = round(0.0588 * l - 0.296 * s - 15.8)

    print(f"Grade {grade}")

def get_letters(text):
    letters = 0
    for i in text:
        if i.isalpha():
            letters += 1
    return letters

def get_words(text):
    words = 0
    for i in text:
        if i == " ":
            words += 1
    return words + 1

def get_sentences(text):
    sentences = 0
    for i in text:
        if i in ("!", "?", ".")

