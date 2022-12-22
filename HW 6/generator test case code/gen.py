'''
Title:DS HW 6 Gen Code
Written By KYLiN
This is code for generate the HW 6 test case
Date: 16/12/2022
'''
import sys

from random import randint

INT_MAX, INT_MIN = 2147483647, -2147483648


def main() -> None:
    if len(sys.argv) < 3:
        return

    n = int(sys.argv[1])
    lst = [randint(INT_MIN, INT_MAX) for _ in range(n)]
    conA, conB = randint(INT_MIN, INT_MAX), randint(1, n - 1)
    with open(sys.argv[2], mode='w') as fOut:
        fOut.write(" ".join(list(map(str, lst))))
        fOut.write('\n')
        fOut.write(" ".join(list(map(str, [conA, conB]))))

    print(f"finish: A:{conA}, B:{conB}")


if __name__ == "__main__":
    main()
