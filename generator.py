import argparse
import random

def generate_random_numbers(n, max_value=10**9):
    """
    Generate n random positive integers.
    max_value controls upper bound of numbers.
    """
    return [random.randint(1, max_value) for _ in range(n)]


def write_to_file(filename, numbers):
    """
    Writes numbers to file in single line space separated format.
    (Good for most sorting problems)
    """
    with open(filename, "w") as f:
        f.write(" ".join(map(str, numbers)))   # Numbers in next line


def main():
    parser = argparse.ArgumentParser(
        description="Generate random positive integers for sorting testcases"
    )

    parser.add_argument(
        "n",
        type=int,
        help="Number of elements to generate"
    )

    parser.add_argument(
        "filename",
        type=str,
        help="Output txt filename"
    )

    parser.add_argument(
        "--max",
        type=int,
        default=10**9,
        help="Maximum value of generated numbers (default: 1e9)"
    )

    args = parser.parse_args()

    numbers = generate_random_numbers(args.n, args.max)
    write_to_file(args.filename, numbers)

    print(f"Generated {args.n} numbers and saved to {args.filename}")


if __name__ == "__main__":
    main()
