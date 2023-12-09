	.file	"stringhe_costanti.c"
	.text
	.globl	str
	.section	.rodata
.LC0:
	.string	"9876543210"
	.section	.data.rel.local,"aw"
	.align 8
	.type	str, @object
	.size	str, 8
str:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"str= %s sizeof(str)= %ld \n"
.LC2:
	.string	"PRIMA str= %s \n"
.LC3:
	.string	"DOPO str= %s \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	str(%rip), %rax
	movl	$8, %edx
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush@PLT
	movq	str(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush@PLT
	movq	str(%rip), %rax
	addq	$1, %rax
	movb	$102, (%rax)
	movq	str(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
