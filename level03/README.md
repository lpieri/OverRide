# ~Level 03

Le programme nous demande un password décimal, et va le tester si le mot de passe écrit dans STDIN est le bon le programme lanceras une shell avec l'appel de la fonction `system("/bin/sh")`.

En décompilant le `main` on peut voir que les arguments passés à la fonction `test()` sont notre valeur de STDIN et `0x1337d00d` soit `322424845` en décimal.

La fonction `test` fait un `sub` de `param1` et `param2` puis un switch case du nombre.

Test appeleras la fonction decrypt avec notre nombre uniquement si  `322424845` - notre valeur est égal à `[1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 17, 18, 19, 20, 21]`, sinon il passeras dans decrypt un nombre random.

Nous pouvons donc tester ces 15 possibilité différentes pour que le XOR de la string `Q}|u'sfg~sf{}|a3`  match avec `Congratulations!` et que le shell s'éxecute.

```shell
~ gdb level03
[...]
	 0x080488c6 <+108>:	mov    0x1c(%esp),%eax
   0x080488ca <+112>:	movl   $0x1337d00d,0x4(%esp)
   0x080488d2 <+120>:	mov    %eax,(%esp)
   0x080488d5 <+123>:	call   0x8048747 <test>
[...]
(gdb) p/d 0x1c
$3 = 28
(gdb) p/d 0x1337d00d
$4 = 322424845
~ python -c "exec(\"import os\nr=[1,2,3,4,5,6,7,8,9,16,17,18,19,20,21]\nb=322424845\nfor i in r: os.system('echo Test: '+str(b-i)+'; echo '+str(b-i)+' | ./level03')\")"
```

Le bon mot de passe est donc `322424827` soit `322424845 - 18`. 

```shell
~ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
~ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
~
```