import subprocess as sb

CLAKE_LOCATION = "../clake"

def check_memory_leaks(path_to_file: str) -> None:
    args = [CLAKE_LOCATION]
    args.append(path_to_file)
    sb.run(args, check=True)

def test_basic1():
    check_memory_leaks("./files/simple/test1.txt")

def test_basic2():
    check_memory_leaks("./files/simple/test2.txt")

def test_basic3():
    check_memory_leaks("./files/simple/test3.txt")

def test_basic4():
    check_memory_leaks("./files/simple/test4.txt")

def test_cycle_do():
    check_memory_leaks("./files/cycle/while.txt")

def test_cycle_while():
    check_memory_leaks("./files/cycle/do_while.txt")

def test_cycle_until():
    check_memory_leaks("./files/cycle/do_until.txt")

def test_types_int():
    check_memory_leaks("./files/types/int.txt")

def test_types_uint():
    check_memory_leaks("./files/types/uint.txt")

def test_types_long():
    check_memory_leaks("./files/types/long.txt")

def test_types_ulong():
    check_memory_leaks("./files/types/ulong.txt")

def test_types_bool():
    check_memory_leaks("./files/types/bool.txt")

def test_types_string():
    check_memory_leaks("./files/types/string.txt")

def test_types_array():
    check_memory_leaks("./files/types/array.txt")
