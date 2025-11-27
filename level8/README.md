## Le programme
Le programme est une boucle infinie qui prend dans stdin une commande {auth ;reset;service;login}:
* Dans la command auth, le programme alloue 4 bytes pour la variable auth, et si la chaine apres "auth " est plus petite que 31 il la copie dans auth. Remarque: on n'alloue pas assez de memoire pour le strcpy, il y a donc un buffer overrun.
* Dans la commande reset, le programme free auth. Cependant, il ne remet pas la variable a NULL.
* Dans la commande service, le programme duplique la chaine apres "service".
* Dans la commande login, si au 32 eme byte du contenu de auth les 4 bytes ne sont pas 0, le programme execute /bin/sh, sinon il affiche "Password:"

## La faille
La faille reside dans le fait que lorsqu'on alloue de la memoire pour service, le buffer sera alloue juste apres auth (16 bytes apres).

Il suffit donc d'appeler auth une premiere fois pour que la variable soit allouée, puis la command service avec 16 bytes pour atteindre le 32 eme byte de auth, ensuite on ecrit un dernier byte. De cette maniere, la condition dans la commande login sera vraie et /bin/sh sera execute.
