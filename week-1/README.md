# COMP SCI 537 Discussion Week 1

## Topics:

- Basics of Makefiles
- Intro to Xv6
- Xv6 and GDB

## Makefiles

The *make* utility lets us automate the build process for our C programs.

We define the rules and commands for building the code in a specialized `Makefile`.
In the Makefile, you specify *targets*, the *dependencies* of each target, and the commands to run to build each target.

Format:
```bash
target : dependencies
    commands
```

After writing your makefile, save it with with the name `Makefile` or `makefile`, and run make with the name of the 'target' you wish to build:  
```
make target
```

> Note: Makefile is sensitive to tabs vs. spaces. It requires commands to be indented with exactly ONE TAB.

Simple examples provided in the [GitHub](https://github.com/akshatgit/CS537-Discussion-su21/tree/master/week-1) for this week:

- Simple:
    ```bash
    # .PHONY specifies a "fake target" - target that does not produce compilation outputs.
    .PHONY: all
    all: example-app


    example-lib.o: example-lib.c
        gcc -c example-lib.c -o example-lib.o -O2 -Wall -Werror

    # $<: the first dependency
    # $@: the target name
    example-app.o: example-app.c
        gcc -c $< -o $@ -O2 -Wall -Werror

    # $^: all the dependencies
    example-app: example-app.o example-lib.o
        gcc $^ -o $@ -O2 -Wall -Werror


    # Useful practice: use a `clean` target to automate cleaning
    .PHONY: clean
    clean:
        rm -f *.o example-app
        rm -f core
    ```
- Advanced:
    ```bash
    # This is the advanced version, showing much better automation.

    # Define "variables" to use in our commands
    CC=gcc
    CFLAGS=-O2 -Wall -Werror
    TARGET=example-app

    # Use helper functions to "search" for files here.
    SOURCES=$(wildcard *.c)
    OBJECTS=$(patsubst %.c,%.o,$(SOURCES))


    .PHONY: all
    all: $(TARGET)


    # We can create .o file for each .c file...
    $(OBJECTS): %.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@ $(CLIBS)

    # ...and build the target from .o files.
    $(TARGET): $(OBJECTS)
        $(CC) $(CFLAGS) $^ -o $@ $(CLIBS)


    .PHONY: clean
    clean:
        rm -f *.o $(TARGET)
        rm -f core
    ```

## Intro to Xv6

To get the source code:

```shell
git clone https://github.com/mit-pdos/xv6-public.git 
```

To compile the xv6:

```shell
make
```

Recall an operating system is special software that manages all the hardware, so to run an OS, you need hardware resources like CPUs, memory, storage, etc. To do this, you could either have a real physical machine, or a virtualization software that "fakes" these hardwares. QEMU is an emulator that virtualizes some hardware to run xv6.

To compile the xv6 and run it in QEMU:

```shell
make qemu-nox
```

`-nox` here means no graphical interface, so it won't pop another window for xv6 console but directly show everything in your current terminal. The xv6 doesn't have a `shutdown` command; to quit from xv6, you need to kill the QEMU: press `ctrl-a` then `x`.

After compiling and running xv6 in QEMU, you could play walk around inside xv6 by `ls`.

```console
$ make qemu-nox

iPXE (http://ipxe.org) 00:03.0 CA00 PCI2.10 PnP PMM+1FF8CA10+1FECCA10 CA00
                                                                            


Booting from Hard Disk..xv6...
cpu1: starting 1
cpu0: starting 0
sb: size 1000 nblocks 941 ninodes 200 nlog 30 logstart 2 inodestart 32 bmap8
init: starting sh
$ ls
.              1 1 512
..             1 1 512
README         2 2 2286
cat            2 3 16272
echo           2 4 15128
forktest       2 5 9432
grep           2 6 18492
init           2 7 15712
kill           2 8 15156
ln             2 9 15012
ls             2 10 17640
mkdir          2 11 15256
rm             2 12 15232
sh             2 13 27868
stressfs       2 14 16148
usertests      2 15 67252
wc             2 16 17008
zombie         2 17 14824
console        3 18 0
stressfs0      2 19 10240
stressfs1      2 20 10240
$ echo hello world
hello world
```

To run xv6 with gdb (another advantage of having a virtualization software!): in one window

```shell
make qemu-nox-gdb
```

then in another window:

```shell
gdb
```
You might get the error message blow:

```console
$ gdb
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
warning: File "/dir/xv6/.gdbinit" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load".
To enable execution of this file add
        add-auto-load-safe-path /dir/xv6/.gdbinit
line to your configuration file "/u/c/h/chenhaoy/.gdbinit".
To completely disable this security protection add
        set auto-load safe-path /
line to your configuration file "/u/c/h/chenhaoy/.gdbinit".
For more information about this security protection see the
--Type <RET> for more, q to quit, c to continue without paging--
```

Recent gdb versions will not automatically load `.gdbinit` for security purposes. You could either:

- `echo "add-auto-load-safe-path $(pwd)/.gdbinit" >> ~/.gdbinit`. This enables the autoloading of `.gdbinit` in the current working directory.
- `echo "set auto-load safe-path /" >> ~/.gdbinit`. This enables the autoloading of every `.gdbinit`

After either operation, you should be able to launch gdb. Specify you want to attach to the kernel


Adapted from work by Guanzhou Hu and Chenhao Ye
