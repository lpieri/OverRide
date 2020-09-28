# Level 00

En lancent le binaire pour la premier fois on peut voir qu'il nous demande un `password` sur `STDIN`. Depuis les deux projets précedents on as pris l'habitude de décompiler les binaires et d'analyser l'asm avec gdb.

Lors de la décompilation on observe qu'il y a un appel de la fonction `system("/bin/sh")` mais qu'avant il faut validé la comparaison du ce que `scanf` récupère avec `0x149c` sois `5276` en décimal.

Il ne nous reste plus qu'a quitter gdb, lancer le programme et écrire `5276` dans STDIN.

```shell
~ gdb level00
(gdb) disas main
Dump of assembler code for function main:
[...]
   0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
   0x080484e3 <+79>:	mov    0x1c(%esp),%eax
   0x080484e7 <+83>:	cmp    $0x149c,%eax
   0x080484ec <+88>:	jne    0x804850d <main+121>
   0x080484ee <+90>:	movl   $0x8048639,(%esp)
   0x080484f5 <+97>:	call   0x8048390 <puts@plt>
   0x080484fa <+102>:	movl   $0x8048649,(%esp)
   0x08048501 <+109>:	call   0x80483a0 <system@plt>
   0x08048506 <+114>:	mov    $0x0,%eax
   0x0804850b <+119>:	jmp    0x804851e <main+138>
   0x0804850d <+121>:	movl   $0x8048651,(%esp)
   0x08048514 <+128>:	call   0x8048390 <puts@plt>
   0x08048519 <+133>:	mov    $0x1,%eax
   0x0804851e <+138>:	leave
   0x0804851f <+139>:	ret
End of assembler dump.
(gdb) x/s 0x8048649
0x8048649:	 "/bin/sh"
(gdb) p/d 0x149c
$1 = 5276
(gdb) quit
~ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
$
```

