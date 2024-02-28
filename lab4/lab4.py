import random


def generate_keypair(p, q):
    n = p * q
    phi = (p - 1) * (q - 1)
    e = random.randrange(1, phi)
    g = gcd(e, phi)
    while g != 1:
        e = random.randrange(1, phi)
        g = gcd(e, phi)
    d = multiplicative_inverse(e, phi)
    return (e, n), (d, n)


def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def multiplicative_inverse(e, phi):
    d = extended_gcd(e, phi)[0]
    return d % phi


def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        g, y, x = extended_gcd(b % a, a)
        return g, x - (b // a) * y, y


def encrypt(message, public_key):
    e, n = public_key
    cipher = [pow(ord(char), e, n) for char in message]
    return cipher


def decrypt(cipher, private_key):
    d, n = private_key
    plain = [chr(pow(char, d, n)) for char in cipher]
    return "".join(plain)


def save_key_to_file(key, filename):
    with open(filename, "w") as f:
        f.write(",".join(map(str, key)))


def load_key_from_file(filename):
    with open(filename, "r") as f:
        key = tuple(map(int, f.readline().split(",")))
    return key


def main():
    choice = (
        input(
            "Enter 'g' for key generation, 'e' for encryption, or 'd' for decryption: "
        )
        .strip()
        .lower()
    )
    if choice == "g":
        p = int(input("Enter a prime number (p): "))
        q = int(input("Enter another prime number (q): "))
        public_key, private_key = generate_keypair(p, q)
        save_key_to_file(public_key, "public_key.txt")
        save_key_to_file(private_key, "private_key.txt")
        print("Keys generated and saved successfully.")
    elif choice == "e":
        message = input("Enter message to encrypt: ")
        public_key = load_key_from_file("public_key.txt")
        cipher = encrypt(message, public_key)
        print("Encrypted message:", cipher)
    elif choice == "d":
        cipher = input("Enter cipher to decrypt: ").split(",")
        cipher = list(map(int, cipher))
        private_key = load_key_from_file("private_key.txt")
        plain = decrypt(cipher, private_key)
        print("Decrypted message:", plain)
    else:
        print("Invalid choice.")


if __name__ == "__main__":
    main()
