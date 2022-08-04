# C Language Tasks
Has: 11 tasks totally
Dependencies:
  * clang >= 11
  * [xmake](https://xmake.io/#/guide/installation)

---
### Contents
* [Sandbox (Simple console programs)](#0-sandbox-simple-console-programs)
  * [Simple credentials check](#01-simple-credentials-check)
  * [Matrix Trilogy Intro](#02-matrix-trilogy-intro)
  * [Pseudographic arts](#03-pseudographic-arts)
* [Basic DSA (Data Structures and Algorithms)](#1-basic-dsa-data-structures-and-algorithms):
    * [Lists](#11-lists)
    * [Queues](#12-queues)
    * [Stacks](#13-stacks)
    * [Dictionaries and Sets](#14-dictionaries-and-sets)
    * [Graphs (and recursion)](#15-graphs-and-recursion)
* [Object Oriented Programming and Design Patterns](#2-object-oriented-programming-and-design-patterns)
    * [Data Export](#21-data-export)
    * [User Authorization](#22-user-authorization)
    * [VCS (Version Control System)](#23-version-control-system-vcs)
* [Unix, Linux, POSIX](#3-unix-linux-posix)
    * [Creating TCP/IP simple messager](#31-creating-tcpip-simple-messager)
    * [Creating LZ77 simple text archiver](#32-creating-lz77-simple-text-archiver)
    * [User Manager in Unix systems](#33-user-manager-in-unix-systems)



---

### 0. Sandbox (Simple console programs)
#### 0.1. Simple credentials check
  * Location: `c_labs/src/lab1/task1.c`
  * Files: ...
  * Task:
    - Make your program as for username, password credentials and check if they are correct.
    - if correct: print success message
    - if wrong: repeat asking for credentials until corrent or maximum trials reached (3)
  * Implementation brief:
    - implemented using infinite while loop with conditional checks inside of loop
    It's worth mentioning that the comparsion of user credentials are performed with custom string-comparing function
  * Usage:
    -   1. Task 1:
    ```bash
    make lab1_1
    make run lab1_1
    ```
    - 2. Task 2:
    ```bash
    make lab1_2
    make run_l12
    ```
  * Available options:
    - you have no options in your life

+++++++++++++++++
#### 0.2. Matrix Trilogy Intro
  * Location: `c_labs/src/lab1/task2.c`
  * Files:
    - `task2.c` - implementation file
    - `task2.h` - header file containing some declarations
  * Task:
    - Implement matrix of falling down digits and letters.
  * Implementation brief:
    - This implementation is far from ideal and has its cons, i.e.:
    - in the original scene the digits were randomly changing during its journey down the screen
    - unfortunately it is not the case with my implementation
    - though it is possible to implement it has much hassle (regenearting each row randomly with a few symbols updated) to deal with
    - .
    - we used memory manangement facilities of C language and oh boy, LOGIC! (still logic is rather a vague term)
  * Usage:
    - Build:
    ```bash
    make lab2_1
    ```
    - Then run:
    ```bash
    ./bin/lab2_1.bin
    ```
  * Available options:

+++++++++++++++++
#### 0.3. Pseudographic Arts
  * Location: `c_labs/src/lab2/task1.c`
  * Files:
    - `task1.c`
    - `taskart.h` - contains HEX-encoded pseudographics
  * Task:
    - Nothing to see here. Just printing some stolen from the internet console graphics ARTS
  * Implementation brief:
    - We could have using some additional libraries like `ncurses` or somebody's library.
    - It would be easier to create, for example words or predefined pseudo-images 
  * Usage: 
    - Build:
    ```bash
    cd c_labs
    clang src/lab2/task1.c -o bin/lab2_1.bin
    source bin/lab2_1.bin
    ```
  * Available options:
    - You have no available options


---
### 1. Basic DSA (Data Structures and Algorithms)
#### 1.1. Lists
  * Location: `c_labs/src/lab3/lists.c`
  * Files:
    - `lists.c` - implementation
    - `lists.h` - ...
    - `task3_lists.c` - usage example
  * Task:
    - Implement lists and create showcase.
  * Implementation brief:
    - Lists implemented using pure C and STDLIB
  * Usage:
  * Available options:

+++++++++++++++++
#### 1.2. Queues</summary>
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
    
  * Available options:

+++++++++++++++++
#### 1.3. Stacks
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:

+++++++++++++++++
#### 1.4. Dictionaries and Sets
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:

+++++++++++++++++
#### 1.5. Graphs (and recursion)
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:



---
### 2. Object Oriented Programming and Design Patterns

+++++++++++++++++
#### 2.1. Data Export
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:

+++++++++++++++++
#### 2.2. User Authorization
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:

+++++++++++++++++
#### 2.3. Version Control System (VCS)
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:


---
### 3. Unix, Linux, POSIX

+++++++++++++++++
#### 3.1. Creating TCP/IP simple messager
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:

+++++++++++++++++
#### 3.2. Creating LZ77 simple text archiver
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:

+++++++++++++++++
#### 3.3. User Manager in Unix systems
  * Location:
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:
