import io
import os
import subprocess

file_name = 'srm.cpp'
run_number = 0

def compile_run():
    global run_number
    print '\n\n', 'Run round ', run_number
    run_number = run_number + 1
    p = subprocess.Popen(['g++', '-o', 'aaa', 'srm.cpp'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()

    if (err == ''):
        print 'Compiled successfully & Run...\n'
        subprocess.check_call('./aaa')
    else:
        print 'Error:\n', err

if __name__ == '__main__':
    run_number = 0
    lines = []
    while True:
        try:
            with io.open(file_name, 'r') as f:
                tmp_lines = f.readlines() 
            if len(lines) != len(tmp_lines):
                lines = tmp_lines
                compile_run()
                continue
            diff = False
            for i in range(len(lines)):
                if lines[i] != tmp_lines[i]:
                    diff = True
            if (diff):
                lines = tmp_lines
                compile_run()
                continue
        except Exception as e:
            continue
