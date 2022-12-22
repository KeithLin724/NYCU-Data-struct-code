'''
Title:DS HW 6 Gen Code
Written By KYLiN
This is code for generate the HW 6 test case
Date: 19/12/2022
'''
import sys

from random import randint

MAX_VAL, MIN_VAL = 10**4, -10**4


def main() -> None:
    if len(sys.argv) < 3:
        return

    n = int(sys.argv[1])
    lst = [randint(MIN_VAL, MAX_VAL) for _ in range(n)]
    conA, conB = randint(0, MAX_VAL), randint(1, 10**5)
    with open(sys.argv[2], mode='w') as fOut:
        fOut.write(" ".join(list(map(str, lst))))
        fOut.write('\n')
        fOut.write(" ".join(list(map(str, [conA, conB]))))

    print(f"finish: A:{conA}, B:{conB}")


if __name__ == "__main__":
    main()
