import io
import os
import subprocess

file_name = 'srm.cpp'
run_number = 0

def compile_run():
    global run_number
    print '\n\n\n\n\n', 'Run round ', run_number
    run_number = run_number + 1
    p = subprocess.Popen(['g++', '-o', 'aaa', 'srm.cpp'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    print 'out: ', out
    print 'err: ', err
    if (err == ''):
        subprocess.check_call('./aaa')

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
