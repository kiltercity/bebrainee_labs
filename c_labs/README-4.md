# BeBrainee Labs
## Contents

1. [Basic DSA](#chapter-1-basic-dsa)
2. [OOP & Design Patterns](#chapter-2-oop--design-patterns)
3. [Unix, Linux, POSIX](#chapter-3-unix-linux-posix)
4. [Resources](#resources)

### Chapter 0. Basics
####  1. Lab 1:
  1. Task 1:
    ```bash
    make lab1_1
    make run lab1_1
    ```
  2. Task 2:
    ```bash
    make lab1_2
    make run_l12
    ```
    
####  2. Lab 2:
   ```bash
   make lab2_1
   ```
   Then run:
   ```bash
   ./bin/lab2_1.bin
   ```

#### 3. Lab 3:
  1. Queues:
  ```bash
  make run_l3_queue
  ```

  2. Stack:
  ```bash
  make run_l3_stack
  ```
  

#### 4. Lab 4:
Hashtables implementation source files are placed at `inlcude/hashtable`
This is not the best way to organize file structure, but still on this stage the best we can have.

The tests are places at : `tests/lab4`

And the tasks solutions are placed at: `src/lab4/`

To run tests use: `make test_lab4`
To run specific task use : `make run_lab4_taskX`, where `X` is the task number.

---
### Chapter 1. Basic DSA
  1. Lists
  2. Queue
  3. Stack
  4. Dictionaries & Sets
  5. Graphs & Recursion

### Chapter 2. OOP & Design Patterns
  1. Data export
  2. User authorization
  3. VCS

### Chapter 3. Unix, Linux, POSIX
  1. TCP/IP Messager
  2. LZ77 Text Archiver
  3. Unix systems users manager


### Resources
#### C Language
1. [Unit Testing Framework for C](https://libcheck.github.io/check/)
2. [Clang - compilation stages](https://freecompilercamp.org/clang-basics/)

#### Makefile
1. [Variables](https://web.mit.edu/gnu/doc/html/make_6.html)
2. [Substitution references](https://www.gnu.org/software/make/manual/make.html#Substitution-Refs)
3. [Substitution refs (stackoverflow)](https://stackoverflow.com/questions/12069457/how-to-change-the-extension-of-each-file-in-a-list-with-multiple-extensions-in-g)
4. [Rules](https://www.gnu.org/software/make/manual/html_node/Rule-Introduction.html)
5. [Automatic variables (used in rules)](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
6. [Expanding variables inside of rules body](https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html)
7. [Default target](https://stackoverflow.com/questions/2057689/how-does-make-app-know-default-target-to-build-if-no-target-is-specified)
8. [Phony targets](https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html)
9. [Expanding variable to multiple rules](https://stackoverflow.com/questions/28804025/how-to-expand-variables-to-multiple-rules-in-makefile)
10. [Static pattern rules](https://www.gnu.org/software/make/manual/html_node/Static-Usage.html#Static-Usage)
11. [Creating custom functions](https://coderwall.com/p/cezf6g/define-your-own-function-in-a-makefile)
12. [Standard functions for file names](https://www.gnu.org/software/make/manual/make.html#Text-Functions)
13. [Suppressing output](https://stackoverflow.com/questions/24005166/gnu-make-silent-by-default)

