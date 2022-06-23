# TODO
while True:
    x = input("Height: ")
    try:
        x = int(x)
    except ValueError:
        continue

    if x < 9 and x > 0:
        break
    else:
        continue

for i in range(1, x + 1):
    print(" " * (x - i), end="")
    print("#" * i, end="  ")
    print("#" * i)



