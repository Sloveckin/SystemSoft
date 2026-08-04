import subprocess as sb

def check_memory_leaks(path_to_file: str) -> None:
    args = ["../clake"]
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
