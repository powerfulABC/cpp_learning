
main.o:     file format elf64-x86-64

Contents of section .text:
 0000 f30f1efa 554889e5 4883ec10 897dfc8b  ....UH..H....}..
 0010 45fc89c6 488d0500 00000048 89c7b800  E...H......H....
 0020 000000e8 00000000 90c9c3f3 0f1efa55  ...............U
 0030 4889e548 83ec10c7 45fc0100 00008b15  H..H....E.......
 0040 00000000 8b050000 000001c2 8b45fc01  .............E..
 0050 d089c7e8 00000000 b8000000 00c9c3    ............... 
Contents of section .data:
 0000 0a000000 01000000                    ........        
Contents of section .rodata:
 0000 73756d20 69732025 640a00             sum is %d..     
Contents of section .comment:
 0000 00474343 3a202855 62756e74 75203131  .GCC: (Ubuntu 11
 0010 2e342e30 2d317562 756e7475 317e3232  .4.0-1ubuntu1~22
 0020 2e303429 2031312e 342e3000           .04) 11.4.0.    
Contents of section .note.gnu.property:
 0000 04000000 10000000 05000000 474e5500  ............GNU.
 0010 020000c0 04000000 03000000 00000000  ................
Contents of section .eh_frame:
 0000 14000000 00000000 017a5200 01781001  .........zR..x..
 0010 1b0c0708 90010000 1c000000 1c000000  ................
 0020 00000000 2b000000 00450e10 8602430d  ....+....E....C.
 0030 06620c07 08000000 1c000000 3c000000  .b..........<...
 0040 00000000 34000000 00450e10 8602430d  ....4....E....C.
 0050 066b0c07 08000000                    .k......        

Disassembly of section .text:

0000000000000000 <func>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	89 7d fc             	mov    %edi,-0x4(%rbp)
   f:	8b 45 fc             	mov    -0x4(%rbp),%eax
  12:	89 c6                	mov    %eax,%esi
  14:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 1b <func+0x1b>
  1b:	48 89 c7             	mov    %rax,%rdi
  1e:	b8 00 00 00 00       	mov    $0x0,%eax
  23:	e8 00 00 00 00       	call   28 <func+0x28>
  28:	90                   	nop
  29:	c9                   	leave  
  2a:	c3                   	ret    

000000000000002b <main>:
  2b:	f3 0f 1e fa          	endbr64 
  2f:	55                   	push   %rbp
  30:	48 89 e5             	mov    %rsp,%rbp
  33:	48 83 ec 10          	sub    $0x10,%rsp
  37:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  3e:	8b 15 00 00 00 00    	mov    0x0(%rip),%edx        # 44 <main+0x19>
  44:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 4a <main+0x1f>
  4a:	01 c2                	add    %eax,%edx
  4c:	8b 45 fc             	mov    -0x4(%rbp),%eax
  4f:	01 d0                	add    %edx,%eax
  51:	89 c7                	mov    %eax,%edi
  53:	e8 00 00 00 00       	call   58 <main+0x2d>
  58:	b8 00 00 00 00       	mov    $0x0,%eax
  5d:	c9                   	leave  
  5e:	c3                   	ret    
