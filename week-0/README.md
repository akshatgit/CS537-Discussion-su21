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
