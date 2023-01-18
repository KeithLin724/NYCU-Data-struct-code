import sys
from Solution import Solution


def main() -> None:

    if len(sys.argv) < 3:
        print("format error")
        sys.exit()

    solutionTools = Solution()

    solutionTools.read_file(file_name_in=sys.argv[1])
    solutionTools.run_solution(file_name_out=sys.argv[2])

    # solutionTools.read_file(file_name_in="sample_in.txt")
    # solutionTools.run_solution(file_name_out="out_test.txt")


if __name__ == "__main__":
    main()
