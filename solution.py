import random
import datetime
from statistics import mean 

#######    https://habr.com/ru/post/346930/    #######
# Поменял / на //, иначе при тестах есть ошибки, k должeн быть целым
def quickselect_median(l, pivot_fn=random.choice):
    if len(l) % 2 == 1:
        return quickselect(l, len(l) // 2, pivot_fn)
    else:
        return 0.5 * (quickselect(l, len(l) // 2 - 1, pivot_fn) +
                      quickselect(l, len(l) // 2, pivot_fn))


def quickselect(l, k, pivot_fn):
    """
    Выбираем k-тый элемент в списке l (с нулевой базой)
    :param l: список числовых данных
    :param k: индекс
    :param pivot_fn: функция выбора pivot, по умолчанию выбирает случайно
    :return: k-тый элемент l
    """
    if len(l) == 1:
        assert k == 0
        return l[0]

    pivot = pivot_fn(l)

    lows = [el for el in l if el < pivot]
    highs = [el for el in l if el > pivot]
    pivots = [el for el in l if el == pivot]

    if k < len(lows):
        return quickselect(lows, k, pivot_fn)
    elif k < len(lows) + len(pivots):
        # Нам повезло и мы угадали медиану
        return pivots[0]
    else:
        return quickselect(highs, k - len(lows) - len(pivots), pivot_fn)
#######    https://habr.com/ru/post/346930/    #######


def more_than(a, b): return a > b
def less_than(a, b): return a < b

def longest_sequence(lst:list, predicate=less_than):
    counter = 1
    max_len = 1
    index_of_last = 0

    prev_max = 0
    for i in range(1, len(lst)):
        if predicate(numbers[i - 1], numbers[i]):
            counter += 1
            if max_len < counter:
                max_len = counter
                if max_len > prev_max:
                    prev_max = max_len
                    index_of_last = i
        else:
            counter = 1
    
    # (Length of sequence, Position in file)
    return (max_len, index_of_last - max_len + 2)


begin_time = datetime.datetime.now()

with open('10m.txt', 'r') as fp:
    numbers = [int(line) for line in fp.readlines()]

longest = longest_sequence(numbers)
print("Increasing seq length:", longest[0], "(Starts at", longest[1], "string)")
longest = longest_sequence(numbers, predicate=more_than)
print("Decreasing seq length:", longest[0], "(Starts at", longest[1], "string)")
print("Average:", mean(numbers))
print("Minimum:", min(numbers))
print("Maximum:", max(numbers))
print("Median:", quickselect_median(numbers))

end_time = datetime.datetime.now()
print("\nTime elapsed: ", (end_time - begin_time).seconds, 's', sep='')