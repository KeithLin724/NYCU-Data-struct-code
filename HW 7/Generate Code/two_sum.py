'''
Title:DS HW 7 two sum python
Written By KYLiN
This is a code for check the answer about DS HW 7 using python 3.9
Date: 28/12/2022
'''

import sys


class Solution:

    def __init__(self, dataIn: list[int]) -> None:
        self.__target = int(dataIn[0])
        self.__numberLst = list(map(int, dataIn[1].split(' ')))

    def two_sum_solution(self) -> list[int]:
        """
        We create a hash table that stores the difference between the target and the current number as
        the key and the index of the current number as the value.
        
        We then iterate through the list of numbers and check if the difference between the target and
        the current number is in the hash table. If it is, we return the index of the current number and
        the index of the number that is the difference between the target and the current number.
        
        If the difference between the target and the current number is not in the hash table, we add the
        current number as the key and the index of the current number as the value to the hash table.
           
        If we iterate through the entire list of numbers and the difference between the target and the
        current number is not in the hash table, we return an empty list.
        :return: The indices of the two numbers such that they add up to a specific target.
        """

        hashTable = dict()

        for index, val in enumerate(self.__numberLst):

            if (targetHashNumIndex := hashTable.get(self.__target - val)):
                if targetHashNumIndex == index:
                    continue

                return [targetHashNumIndex, index]

            hashTable.update({val: index})

        return []


def main() -> None:

    if len(sys.argv) < 3:
        print("this input argv less than 3")
        sys.exit(-1)

    inputFile, outputFile = sys.argv[1:]

    dataFileIn = ''
    try:
        with open(file=inputFile, mode='r') as fOpen:
            dataFileIn = fOpen.readlines()

    except FileExistsError:
        print(f'file {inputFile} is not file')
        sys.exit(-1)

    dataFileIn = list(map(lambda x: x.replace('\n', '').strip(), dataFileIn))

    ans = Solution(dataFileIn).two_sum_solution()

    with open(file=outputFile, mode='w') as fOut:
        fOut.write('\n'.join(map(str, ans)))


if __name__ == '__main__':
    main()
