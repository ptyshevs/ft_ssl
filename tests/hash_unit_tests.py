

empty_input = ('empty_input', '')
fips180_simple = ('fips180_simple', 'abc')
fips180_multiblock256 = ('fips180_multiblock256', 'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq')
fips180_long_a = ('fips180_long_a', 'a' * 1_000)

fips180_multiblock512 = ('fips180_multiblock512', '"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu')

def len_check():
    return [(f'a_len={i}', 'a' * i) for i in range(1, 513)]

def sha256_test_suite():
    return [empty_input, fips180_simple, fips180_multiblock256, fips180_long_a] + len_check()

def md5_test_suite():
    return [empty_input, fips180_simple, fips180_multiblock256, fips180_long_a] + len_check()


if __name__ == '__main__':
    print(dir(__spec__))