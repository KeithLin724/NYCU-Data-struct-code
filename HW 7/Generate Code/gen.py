'''
Title:DS Gen Code
Written By KYLiN
This is a code for the DS HW 7 Hash two sum

max and min value in -1e9 <= n <= 1e9
Date: 25/12/2022
'''

import sys
from random import randint, sample

MAX_VAL, MIN_VAL = 1e9, -1e9


def main() -> None:
    if len(sys.argv) < 2:
        print("argv less input")
        exit(-1)

    n, fileName = int(sys.argv[1]), sys.argv[2]

    if n < 2:
        print("list number need bigger 2")
        exit(-1)

    randomLst = set()

    while len(randomLst) != n:
        randomLst.add(randint(MIN_VAL, MAX_VAL))

    randomLst = list(randomLst)

    targetNum = sum(sample(randomLst, k=2))

    with open(file=fileName, mode='w') as fOut:
        fOut.write(str(targetNum) + '\n')
        fOut.write(' '.join(map(str, randomLst)))

    print(f"finish size: {n} , target : {targetNum}")


if __name__ == "__main__":
    main()
