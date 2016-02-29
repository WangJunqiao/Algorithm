import io
import os

file_name = 'srm.cpp'
run_number = 0

def compile_run():
    global run_number
    print 'Run round ', run_number
    run_number = run_number + 1
    stream = os.popen("g++ -o aaa srm.cpp")
    output = stream.read()
    print output
    if (len(output) == 0):
        stream = os.popen("./aaa")
        print stream.read()

if __name__ == '__main__':
    run_number = 0
    lines = []
    while True:
        with io.open(file_name, 'r') as f:
            tmp_lines = f.readlines() 
        if len(lines) != len(tmp_lines):
            print 'different rows'
            lines = tmp_lines
            compile_run()
            continue
        diff = False
        for i in range(len(lines)):
            if lines[i] != tmp_lines[i]:
                diff = True
        if (diff):
            print 'different content'
            lines = tmp_lines
            compile_run()
            continue
