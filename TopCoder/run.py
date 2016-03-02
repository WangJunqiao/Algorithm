import io
import time
import sys
import os
import subprocess


def print_usage():
    print '''
    Usage:
    --src src file : indicate the C++ source file.
    -i input_file_name : indicate input file name.
    -o output_file_name : indicate output file name.
    '''
    exit(0)

def parse_args():
    args = {}
    i = 1
    argc = len(sys.argv)
    while (i < argc):
        if sys.argv[i] == "--src":
            if i + 1 >= argc:
                print_usage()
            args["src_file"] = sys.argv[i + 1]
            i = i + 1
        elif (sys.argv[i] == "-i"):
            if i + 1 >= argc:
                print_usage()
            args["input_file"] = sys.argv[i + 1]
            i = i + 1
        elif (sys.argv[i] == "-o"):
            if i + 1 >= argc:
                print_usage()
            args["output_file"] = sys.argv[i + 1]
            i = i + 1
        else:
            print_usage()
        i = i + 1
    if "src_file" not in args:
        print_usage()
    return args

def compile_run(args, run_number):
    print '\n\n', 'Run #', run_number
    compile_p = subprocess.Popen(['g++', '-o', 'aaa', args['src_file']], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    compile_out, compile_err = compile_p.communicate()

    if (compile_err != ""):
        print 'Compile Error:\n', compile_err
    else:
        run_p = subprocess.Popen(['./aaa'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT) #redirect stderr to stdout, otherwise assign subprocess.PIPE
        if "input_file" in args:
            run_out, run_err = run_p.communicate(open(args["input_file"], 'r').read()) #stderr -> stdout, so stderr always = None
        else:
            run_out, run_err = run_p.communicate()
        print "Run Output:\n", run_out
        #print "Run Error:\n", run_err
        if "output_file" in args:
            std_out = open(args["output_file"]).read()
            if std_out == run_out:
                print "Compare to provided standard output, SAME! Congrats!"
            else:
                print "Compare to provided standard output, DIFFERENT!!!"
                print "Std output:\n", std_out
                print " My output:\n", run_out

if __name__ == '__main__':
    args = parse_args()
    run_number = 0
    content = ""
    while True:
        try:
            time.sleep(0.01)
            tmp_content = io.open(args["src_file"], 'r').read()
            if tmp_content != content:
                content = tmp_content
                run_number += 1
                compile_run(args, run_number)
                continue
        except Exception as e:
            continue
