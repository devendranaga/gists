#!/usr/bin/python

# make ci happy and compile all the files to make users happy with no mistakes

import glob
import os

os.chdir('../')

exceptions = ['lib.c', 'md_list.c', 'hash_Test.c', 'cipher_list.c', 'dlopen.c']

for file in glob.glob('*.c'):
    print(file)
    if file not in exceptions:
        x = os.system('gcc ' + file + ' -ldl -rdynamic -pthread -lm -lseccomp')
        if x != 0:
            exit(1)

x = os.system('gcc lib.c dlopen.c -ldl -rdynamic')
if x != 0:
    exit(1)

exit(0)
