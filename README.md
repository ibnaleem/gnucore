# gnucore
A collection of GNU core utilities and custom binaries reimplemented in C for Windows

## Why?
I've coded this project to better understand C and embedded development. I haven't optimised [`coreutils`](http://git.savannah.gnu.org/gitweb/?p=coreutils.git); I've only added my preferences to the binaries (e.g adding a `/` to directory prints).

## How To Use
All binaries are compiled in `bin/`. Simply type `Edit Environmental Variables -> Path -> New -> /path/to/this/directory/bin` 

## My Custom Binaries
Some binaries I've coded that do not exist in coreutils that I think should:
- `cnt` - gets the number of lines in a file, or number of files/directories in a directory:
```bash
$ ./cnt
5 files (0 hidden) - 0 directories (1 hidden)

$ ./cnt cnt.c
131 cnt.c

$ ./cnt src LICENSE
src:
4 files (0 hidden) - 0 directories (1 hidden)

674 LICENSE
```
