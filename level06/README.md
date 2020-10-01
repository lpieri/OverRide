# Level 06

Quand nous lançons le programme, il nous demande un User et un Serial, avec l'User il va générer son propre serial si il match avec le notre serial alors, on sera authentifier et le programme lanceras un shell.

Nous pouvons connaître le bon serial avec gdb, mais le programme à une protection qui détecte s'il est lancé dans gdb.

Nous pouvons contourner cette protection facilement avec une breakpoint. Un fois la protection contourner nous pouvons récuperer le serial génerer par le binaire.

```shell
~ gdb level06
(gdb) disas auth
[...]
	 0x080487b5 <+109>:	call   0x80485f0 <ptrace@plt>
   0x080487ba <+114>:	cmp    $0xffffffff,%eax		<--- si le programme est lancé dans gdb
   0x080487bd <+117>:	jne    0x80487ed <auth+165>
[...]
	 0x08048861 <+281>:	jl     0x804880f <auth+199>
   0x08048863 <+283>:	mov    0xc(%ebp),%eax
   0x08048866 <+286>:	cmp    -0x10(%ebp),%eax		<--- comparaison de notre serial avec celui générer
   0x08048869 <+289>:	je     0x8048872 <auth+298>
   0x0804886b <+291>:	mov    $0x1,%eax
   0x08048870 <+296>:	jmp    0x8048877 <auth+303>
   0x08048872 <+298>:	mov    $0x0,%eax
   0x08048877 <+303>:	leave
   0x08048878 <+304>:	ret
(gdb) b *0x080487ba
Breakpoint 1 at 0x80487ba
(gdb) b *0x08048866
Breakpoint 2 at 0x8048866
(gdb) r
***********************************
*		level06		  *
***********************************
-> Enter Login: BBBBBBBB
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 42
Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax = 0
(gdb) c
Continuing.
Breakpoint 2, 0x08048866 in auth ()
(gdb) x $ebp-0x10
0xffffd268:	0x005f1dad
(gdb) p/d 0x005f1dad
$1 = 6233517
(gdb) quit
~ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: BBBBBBBB
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233517
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

