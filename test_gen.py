import os
import argparse
import random
import string

def generate_word(length=5):
    """Генерирует случайное слово заданной длины."""
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def generate_test(m, n):
    """Генерирует тест из двух последовательностей слов."""
    sequence_m = ' '.join(generate_word() for _ in range(m))
    sequence_n = ' '.join(generate_word() for _ in range(n))
    return f"{sequence_m}\n{sequence_n}\n"

def main():
    parser = argparse.ArgumentParser(description='Генератор тестов.')
    parser.add_argument('path', type=str, help='Путь до папки для сохранения тестов')
    parser.add_argument('tests_count', type=int, help='Количество тестов для генерации')
    parser.add_argument('m', type=int, help='Количество слов в первой последовательности')
    parser.add_argument('n', type=int, help='Количество слов во второй последовательности')
    
    args = parser.parse_args()

    if not os.path.exists(args.path):
        os.makedirs(args.path)

    for i in range(args.tests_count):
        test_content = generate_test(args.m, args.n)
        with open(os.path.join(args.path, f"test_{i+1}.txt"), 'w') as file:
            file.write(test_content)

if __name__ == "__main__":
    main()
