from cs50 import get_int

x = get_int("Number: ")
x = str(x)

if len(x) == 15 and (x[:1] == '34' or '37'):
    print("AMEX\n")
elif (len(x) == 13 or len(x) == 16) and (x[0] == '4'):
    print("VISA\n")
elif x[0:2] in ["51", "52", "53", "54", "55"] and len(x) == 16:
    print("MASTERCARD\n")
else:
    print("INVALID\n")