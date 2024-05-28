# Utilities

## C++ template

Calling `cpinit.sh` from a directory will create 6 directories named task1,...,task6.
(if you really want more, go and change the script).

Within each directory, there will your main source code `src.cc` and a `Makefile`.

The normal operation is as follows:
- create a file `case1.in` (you can name it anything, ending with `.in`)
- write code
- `make`

To run your code against multiple cases, create multiple `.in` files

To test your code (simple output comparison testing):
- create corresponding `.out` files containing expected output
- `make test`

If you want to run your program interactively, then just do `./exec`.

## C++ debug helper

`debug.hh` can be used for easy print style local debugging.

Template for C++ includes this file.
To enable usage, add `cpp` directory to `CPLUS_INCLUDE_PATH`.

## Legacy Compile/run utility

`cp.py` is a convenience CLI utility.
This can be integrated with your text editor
(if it supports executing programs). This way,
shortcuts can be bound to compile/run code
in different languages.

For help, use:
```
python cp.py -h
```

Obviously this requires python installation.

### Vim integration

First add environment variable `CP_UTILS` pointing
to this directory.

For Windows, you can do this:
```
setx CP_UTILS [base-path-for-repo]\cp\util
```

Add one line to your `vimrc`
```
source $CP_UTILS/vim/cp.vim
```

This will bind:
- `<leader>c` to Compile
- `<leader>v` to Run
- `<leader>1` to template loading
  - By default it loads `cpp/template.cc`.
  - More templates can be added using same concept.


***
