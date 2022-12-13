# Utilities

## Compile/run utility

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

## C++ debug helper

`debug.hh` can be used for easy print style local debugging.

Template for C++ includes this file.
But you need to add `cpp` directory to `CPLUS_INCLUDE_PATH`.

For Windows, you can do this:
```
setx CPLUS_INCLUDE_PATH [base-path-for-repo]\cp\util\cpp
```

***