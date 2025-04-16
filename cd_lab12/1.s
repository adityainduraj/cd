	.file	"1.c"
	.text
	.globl	initStack
	.type	initStack, @function
initStack:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$-1, 10000(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	initStack, .-initStack
	.section	.rodata
.LC0:
	.string	"Stack Overflow"
	.text
	.globl	push
	.type	push, @function
push:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	10000(%rax), %eax
	cmpl	$99, %eax
	jne	.L3
	movl	$.LC0, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L3:
	movq	-8(%rbp), %rax
	movl	10000(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 10000(%rax)
	movq	-8(%rbp), %rax
	movl	10000(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-8(%rbp), %rdx
	addq	%rax, %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	push, .-push
	.section	.rodata
.LC1:
	.string	"Stack Underflow"
	.text
	.globl	pop
	.type	pop, @function
pop:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	10000(%rax), %eax
	cmpl	$-1, %eax
	jne	.L5
	movl	$.LC1, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L5:
	movq	-8(%rbp), %rax
	movl	10000(%rax), %eax
	leal	-1(%rax), %ecx
	movq	-8(%rbp), %rdx
	movl	%ecx, 10000(%rdx)
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	movq	-8(%rbp), %rdx
	addq	%rdx, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	pop, .-pop
	.globl	isOperator
	.type	isOperator, @function
isOperator:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$43, -4(%rbp)
	je	.L8
	cmpb	$45, -4(%rbp)
	je	.L8
	cmpb	$42, -4(%rbp)
	je	.L8
	cmpb	$47, -4(%rbp)
	je	.L8
	cmpb	$94, -4(%rbp)
	jne	.L9
.L8:
	movl	$1, %eax
	jmp	.L11
.L9:
	movl	$0, %eax
.L11:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	isOperator, .-isOperator
	.section	.rodata
.LC2:
	.string	" "
.LC3:
	.string	"TEMP%d"
.LC4:
	.string	"LOAD %s"
.LC5:
	.string	"ADD %s"
.LC6:
	.string	"STORE %s"
.LC7:
	.string	"SUB %s"
.LC8:
	.string	"MUL %s"
.LC9:
	.string	"DIV %s"
.LC10:
	.string	"EXP %s"
.LC11:
	.string	"Generated Assembly Code:"
	.text
	.globl	generateAssembly
	.type	generateAssembly, @function
generateAssembly:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$20384, %rsp
	movq	%rdi, -20376(%rbp)
	leaq	-10032(%rbp), %rax
	movq	%rax, %rdi
	call	initStack
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movq	-20376(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	strtok
	movq	%rax, -16(%rbp)
	jmp	.L13
.L21:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	isOperator
	testl	%eax, %eax
	je	.L14
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	cmpq	$1, %rax
	jne	.L14
	leaq	-10032(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movq	%rax, %rdx
	leaq	-20368(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	leaq	-10032(%rbp), %rax
	movq	%rax, %rdi
	call	pop
	movq	%rax, %rdx
	leaq	-20256(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	leaq	-20144(%rbp), %rcx
	movl	%eax, %edx
	movl	$.LC3, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$43, %al
	jne	.L15
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20256(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC4, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20368(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC5, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20144(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC6, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	jmp	.L16
.L15:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L17
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20256(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC4, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20368(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC7, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20144(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC6, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	jmp	.L16
.L17:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$42, %al
	jne	.L18
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20256(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC4, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20368(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC8, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20144(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC6, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	jmp	.L16
.L18:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jne	.L19
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20256(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC4, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20368(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC9, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20144(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC6, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	jmp	.L16
.L19:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$94, %al
	jne	.L16
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20256(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC4, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20368(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC10, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	leaq	-20032(%rbp), %rcx
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	leaq	-20144(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC6, %esi
	movq	%rcx, %rdi
	movl	$0, %eax
	call	sprintf
.L16:
	leaq	-20144(%rbp), %rdx
	leaq	-10032(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	push
	jmp	.L20
.L14:
	movq	-16(%rbp), %rdx
	leaq	-10032(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	push
.L20:
	movl	$.LC2, %esi
	movl	$0, %edi
	call	strtok
	movq	%rax, -16(%rbp)
.L13:
	cmpq	$0, -16(%rbp)
	jne	.L21
	movl	$.LC11, %edi
	call	puts
	movl	$0, -20(%rbp)
	jmp	.L22
.L23:
	leaq	-20032(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movq	%rax, %rdi
	call	puts
	addl	$1, -20(%rbp)
.L22:
	movl	-20(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L23
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	generateAssembly, .-generateAssembly
	.section	.rodata
	.align 8
.LC12:
	.string	"Enter a postfix expression (e.g., '3 4 + 5 *'):"
.LC13:
	.string	"\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movl	$.LC12, %edi
	call	puts
	movq	stdin(%rip), %rdx
	leaq	-112(%rbp), %rax
	movl	$100, %esi
	movq	%rax, %rdi
	call	fgets
	leaq	-112(%rbp), %rax
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	strcspn
	movb	$0, -112(%rbp,%rax)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	generateAssembly
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20250110 (Red Hat 14.2.1-7)"
	.section	.note.GNU-stack,"",@progbits
