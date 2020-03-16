rets = []
progs = []
with open("raw.txt", "r") as f:
    for line in f.read().split("\n"):
        rets.append(line.split(" ")[1])
        progs.append(" ".join(line.split(" ")[2:]))

for i, prog in enumerate(progs):
    prog = prog[1:-1]
    keywords = ["char", "int", "sizeof", "calloc", "printf", "return"]
    for j, keyword in enumerate(keywords):
        prog = prog.replace(keyword, "DUMMY"+str(10000-j))

    prog = prog.replace("main", "test"+str(i))
    for c in ["a", "b", "c", "d", "x", "y", "z", "foo", "bar", ]:
        prog = prog.replace(c, c+str(i))
    for j, keyword in enumerate(keywords):
        prog = prog.replace("DUMMY"+str(10000-j), keyword)

    print(prog)
print("int main(){")

for i, ret in enumerate(rets):
    funcname = "test"+str(i)+"()"
    ifstr = "if ({}!={})".format(funcname, ret)
    print(ifstr)
    print("{")
    print('printf("{} faild (expect:%d actual:%d)\\n",{},{});'.format(
        funcname, funcname, ret))
    print("}")
print("return 0;\n}")
