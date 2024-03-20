def lcs_length(words_x, words_y):
    curr = [0] * (1 + len(words_y))
    for word_x in words_x:
        prev = curr[:]
        for y_i, word_y in enumerate(words_y):
            if word_x == word_y:
                curr[y_i + 1] = prev[y_i] + 1
            else:
                curr[y_i + 1] = max(curr[y_i], prev[y_i + 1])
    return curr


def LCS_HIRSHBERG(words_x, words_y):
    len_x = len(words_x)
    if len_x == 0:
        return []
    elif len_x == 1:
        if words_x[0] in words_y:
            return [words_x[0]]
        else:
            return []
    else:
        i = len_x // 2
        x_beg, x_end = words_x[:i], words_x[i:]
        l1 = lcs_length(x_beg, words_y)
        l2 = list(reversed(lcs_length(x_end[::-1], words_y[::-1])))
        sum_l = [l1_val + l2_val for l1_val, l2_val in zip(l1, l2)]
        _, j = max((val, idx) for idx, val in enumerate(sum_l))
        y_beg, y_end = words_y[:j], words_y[j:]
        return LCS_HIRSHBERG(x_beg, y_beg) + LCS_HIRSHBERG(x_end, y_end)


words_x = input().split()
words_y = input().split()


result = LCS_HIRSHBERG(words_x, words_y)
print(len(result))
print(" ".join(result))
