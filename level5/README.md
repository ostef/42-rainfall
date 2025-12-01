addresse de o: 0x080484a4

etat de la stack:
push ebp -> 4 bytes
sub 536, esp -> 536 bytes


argument index du debut du buffer: 4
eip save -> 540 bytes apres le debut du buffer
potentiel argument index du save de eip: 135

```
Starting program: /home/user/level5/level5
%130$x %131$x %132$x %133$x %134$x %135$x
b7fd0ff4 b7e5ee55 b7fed280 0 bffff658 804850f
[Inferior 1 (process 2744) exited with code 01]
(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:	push   %ebp
   0x08048505 <+1>:	mov    %esp,%ebp
   0x08048507 <+3>:	and    $0xfffffff0,%esp
   0x0804850a <+6>:	call   0x80484c2 <n>
=> 0x0804850f <+11>:	leave
   0x08048510 <+12>:	ret
```


