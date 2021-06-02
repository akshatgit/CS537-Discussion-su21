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

```
shell> git clone https://github.com/mit-pdos/xv6-public.git 
```

Adapted from work by Guanzhou Hu and Chenhao Ye