def reverse(string):
    if len(string) == 2:
        newStr = string[1] + string[0]
        return newStr
    half = (len(string)/2)
    res = reverse(string[half:]) + reverse(string[:half])
    return res

print reverse("hola, com estas?")
