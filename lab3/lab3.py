import random
import math


def generate_password(alphabet, length):
    password = "".join(random.choice(alphabet) for _ in range(length))
    return password


def find_length(S, A):
    L = math.log(S, A)
    L = math.ceil(L)
    return L


def main(v: int, t: int, p_power: int):
    V = v * 24 * 60 * 7
    T = t / 7
    P = 10**-p_power

    # Выбираем алфавит
    alphabet = "0123456789abcdefghijklmnopqrstuvwxyz"

    # Вычисляем S
    A = len(alphabet)
    S = abs((V * T) / P)

    L = find_length(S, A)
    password = generate_password(alphabet, L)
    print("Сгенерированный пароль:", password)
    print("Длина:", L)


if __name__ == "__main__":
    V = int(input("Введите V: "))
    T = int(input("Введите T: "))
    P = int(input("Введите степень P: "))
    main(V, T, P)
