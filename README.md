# RELIX ReScript Dialect
**RRD** or **RELIX ReScript Dialect** is a prototype-based, object-oriented dynamic programming language based on the work of
[Thomas Gatzweiler](https://github.com/proty/proty).

## Project Organization
`src` contains two libraries:
  * `librelix` (the virtual machine and runtime environment)
  * `librescript` (the compiler API)

`tools` contains two executables:
  * `irlx` - an interactive compiler (REPL)
  * `rlxc` - command line interface 

`lib` contains loadable modules to extend functionality

## Build Instructions
Can be compiled on Linux or on Windows (tested with MSYS2).

~~~
$ git clone https://github.com/zehlchen/relix.git
~~~

~~~
$ mkdir relix/build && cd relix/build
~~~

~~~
$ cmake .. && make && make install
~~~