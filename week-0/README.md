# COMP SCI 537 Discussion Week 0


## CSL AFS Permission

CSL Linux machines use AFS (Andrew File System). It is a distributed filesystem (that why you see the same content when logging intodifferent CSL machines) with additional access control.

To see the permission of a directory

```shell
fs la /path/to/dir
```

You could also omit `/path/to/dir` to show the permission in the current working directory. You might get output like this:

```console
$ fs la /p/course/cs537-yuvraj/turnin
Access list for /p/course/cs537-yuvraj/turnin is
Normal rights:
  system:administrators rlidwka
  system:anyuser l
  asinha32 rlidwka
  yuvraj rlidwka
```

- `r` (read): allow to read the content of files
- `l` (lookup): allow to list what in a directory
- `i` (insert): allow to create files
- `d` (delete): allow to delete files
- `w` (write): allow to modify the content of a file or `chmod`
- `a` (administer): allow to change access control

Check [this](https://computing.cs.cmu.edu/help-support/afs-acls) out for more how to interpret this output.

You should test all your code in CSL.

## Compilation

For this course, we use `gcc` as the standard compiler.

```shell
gcc -o my-code my-code.c -Wall -Werror
# be careful! DO NOT type "gcc -o my-code.c ..."
```

- `-Wall` flag means `gcc` will show most of the warnings it detects.
-  `-Werror` flag means `gcc` will treat the warnings as errors and reject compiling.

## Sanitizers

Sanitizers are a set of tools to inject some checking instructions during the compilation. These instructions could provide warnings at the runtime.

### Memory Leak

To detect memory leak, use `-fsanitize=address`:

```console
$ gcc -fsanitize=address -o leak leak.c
$ ./leak

=================================================================
==36716==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0xffff9686ca30 in __interceptor_malloc (/lib/aarch64-linux-gnu/libasan.so.5+0xeda30)
    #1 0xaaaace937868 in leak (/dir/leak+0x868)
    #2 0xaaaace937884 in main (/dir/leak+0x884)
    #3 0xffff9663208c in __libc_start_main (/lib/aarch64-linux-gnu/libc.so.6+0x2408c)
    #4 0xaaaace937780  (/dir/leak+0x780)

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
```

Note that compilation with sanitizer flags could significantly slow down your code (typically 3x to 10x); do not include it in your submission Makefile.

### Access Illegal Memory

`-fsanitize=address` could actually be helpful in many memory-related bugs, for example, illegal memory access:

```console
$ gcc -fsanitize=address -o buf_overflow buf_overflow.c
$ ./buf_overflow
0
1
2
3
=================================================================
==37234==ERROR: AddressSanitizer: stack-buffer-overflow on address 0xffffe2598f40 at pc 0xaaaac056bdf4 bp 0xffffe2598ea0 sp 0xffffe2598ec0
READ of size 4 at 0xffffe2598f40 thread T0
    #0 0xaaaac056bdf0 in buf_overflow (/dir/buf_overflow+0xdf0)
    #1 0xaaaac056beac in main (/dir/buf_overflow+0xeac)
    #2 0xffffa5f1808c in __libc_start_main (/lib/aarch64-linux-gnu/libc.so.6+0x2408c)
    #3 0xaaaac056bac0  (/dir/buf_overflow+0xac0)

Address 0xffffe2598f40 is located in stack of thread T0 at offset 48 in frame
    #0 0xaaaac056bba8 in buf_overflow (/dir/buf_overflow+0xba8)

  This frame has 1 object(s):
    [32, 48) 'array' (line 5) <== Memory access at offset 48 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow (/dir/buf_overflow+0xdf0) in buf_overflow
Shadow bytes around the buggy address:
  0x200ffc4b3190: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b31a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b31b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b31c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b31d0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x200ffc4b31e0: 00 00 f1 f1 f1 f1 00 00[f3]f3 00 00 00 00 00 00
  0x200ffc4b31f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b3200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b3210: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b3220: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x200ffc4b3230: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==37234==ABORTING
```

## Valgrind

Valgrind could also be helpful for a memory leak. Different from sanitizers, valgrind does not require special compilation command.

```console
$ gcc -o leak leak.c
$ valgrind ./leak
==38337== Memcheck, a memory error detector
==38337== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==38337== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==38337== Command: ./leak
==38337==
==38337==
==38337== HEAP SUMMARY:
==38337==     in use at exit: 4 bytes in 1 blocks
==38337==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==38337==
==38337== LEAK SUMMARY:
==38337==    definitely lost: 4 bytes in 1 blocks
==38337==    indirectly lost: 0 bytes in 0 blocks
==38337==      possibly lost: 0 bytes in 0 blocks
==38337==    still reachable: 0 bytes in 0 blocks
==38337==         suppressed: 0 bytes in 0 blocks
==38337== Rerun with --leak-check=full to see details of leaked memory
==38337==
==38337== For lists of detected and suppressed errors, rerun with: -s
==38337== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## The Art of Troubleshooting and Asking Questions

There is no stupid question, but some questions are more likely to get help than the others:

- Be informative: Describe the problems with necessary information
    - Do not: "Hey TA, my code doesn't work."
    - Do: "My code is supposed to do X, but it does Y."
- Be concrete: Use gdb to at least locate which line(s) of code goes wrong; typically checking variables' value and track down at which point it has an expected value and you can't understand why it happens.
    - Do not: Send a 200-line source code file to TAs and ask them to debug for you.
    - Do: Use gdb to narrow down the problems.

Also, try the tools we discuss today. They could save you from a lot of trouble.

## Reference Links

- Never forget `man` in your command line :)

- [Cppreference](https://en.cppreference.com/w/c) is primary for C++ reference, but it also has pretty references for C (with examples!).
- [This git tutorial](https://git-scm.com/docs/gittutorial) could be helpful if you are not familiar with git.
