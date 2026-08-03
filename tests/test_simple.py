import subprocess as sb

def test_basic1():
    args = ["../clake", "./files/simple/test1.txt"]
    sb.run(args, check=True)

def test_basic2():
    args = ["../clake", "./files/simple/test2.txt"]
    sb.run(args, check=True)