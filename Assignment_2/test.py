def split(postfix):
    flag = 0
    last_ch = postfix[len(postfix)-1]

    if last_ch == "." or last_ch == "+":
        flag = 1

    i = len(postfix) - 1
    while(flag != 0):
        i -= 1
        if (postfix[i] == "." or postfix[i] == "+"):
            flag += 1
        elif (postfix[i].isalnum()):
            flag -= 1

    postfix = list(postfix)
    cur_op = postfix.pop()
    temp = ''.join(postfix)
    str1 = temp[0:i]
    str2 = temp[-(len(postfix) - i):]

    return ([str1, str2, cur_op])


postfix = input()
x = split(postfix)
print(x)
