	.file	"codegenerator.cpp"
	.intel_syntax noprefix
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.section	.text._ZNSt11char_traitsIcE6lengthEPKc,"axG",@progbits,_ZNSt11char_traitsIcE6lengthEPKc,comdat
	.weak	_ZNSt11char_traitsIcE6lengthEPKc
	.type	_ZNSt11char_traitsIcE6lengthEPKc, @function
_ZNSt11char_traitsIcE6lengthEPKc:
.LFB276:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, -1
	mov	rdx, rax
	mov	eax, 0
	mov	rdi, rdx
	repnz scasb
	mov	rax, rcx
	not	rax
	sub	rax, 1
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE276:
	.size	_ZNSt11char_traitsIcE6lengthEPKc, .-_ZNSt11char_traitsIcE6lengthEPKc
	.section	.text._ZnwmPv,"axG",@progbits,_ZnwmPv,comdat
	.weak	_ZnwmPv
	.type	_ZnwmPv, @function
_ZnwmPv:
.LFB378:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE378:
	.size	_ZnwmPv, .-_ZnwmPv
	.section	.text._ZdlPvS_,"axG",@progbits,_ZdlPvS_,comdat
	.weak	_ZdlPvS_
	.type	_ZdlPvS_, @function
_ZdlPvS_:
.LFB380:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE380:
	.size	_ZdlPvS_, .-_ZdlPvS_
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
	.type	_ZStL13allocator_arg, @object
	.size	_ZStL13allocator_arg, 1
_ZStL13allocator_arg:
	.zero	1
	.type	_ZStL6ignore, @object
	.size	_ZStL6ignore, 1
_ZStL6ignore:
	.zero	1
	.text
	.globl	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
	.type	_Z9pushArrayRSt6vectorIhSaIhEERKS1_, @function
_Z9pushArrayRSt6vectorIhSaIhEERKS1_:
.LFB1983:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1983
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 64
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	rax, QWORD PTR [rbp-64]
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE5beginEv
	mov	QWORD PTR [rbp-32], rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE3endEv
	mov	QWORD PTR [rbp-16], rax
	jmp	.L7
.L8:
	lea	rax, [rbp-32]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv
	movzx	eax, BYTE PTR [rax]
	mov	BYTE PTR [rbp-33], al
	lea	rdx, [rbp-33]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB0:
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv
.L7:
	lea	rdx, [rbp-16]
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_
.LEHE0:
	test	al, al
	jne	.L8
	jmp	.L11
.L10:
	mov	rdi, rax
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1983:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1983:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1983-.LLSDACSB1983
.LLSDACSB1983:
	.uleb128 .LEHB0-.LFB1983
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L10-.LFB1983
	.uleb128 0
	.uleb128 .LEHB1-.LFB1983
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE1983:
	.text
	.size	_Z9pushArrayRSt6vectorIhSaIhEERKS1_, .-_Z9pushArrayRSt6vectorIhSaIhEERKS1_
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED5Ev,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev:
.LFB1986:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1986:
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED1Ev
	.set	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED1Ev,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED2Ev
	.section	.text._ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_,"axG",@progbits,_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_,comdat
	.align 2
	.weak	_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_
	.type	_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_, @function
_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_:
.LFB1990:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1ERKSs
	mov	rcx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax+16]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR [rcx+8], rax
	mov	QWORD PTR [rcx+16], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1990:
	.size	_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_, .-_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_
	.section	.text._ZNSt4pairIKSs15DefinedFunctionED2Ev,"axG",@progbits,_ZNSt4pairIKSs15DefinedFunctionED5Ev,comdat
	.align 2
	.weak	_ZNSt4pairIKSs15DefinedFunctionED2Ev
	.type	_ZNSt4pairIKSs15DefinedFunctionED2Ev, @function
_ZNSt4pairIKSs15DefinedFunctionED2Ev:
.LFB1992:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSsD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1992:
	.size	_ZNSt4pairIKSs15DefinedFunctionED2Ev, .-_ZNSt4pairIKSs15DefinedFunctionED2Ev
	.weak	_ZNSt4pairIKSs15DefinedFunctionED1Ev
	.set	_ZNSt4pairIKSs15DefinedFunctionED1Ev,_ZNSt4pairIKSs15DefinedFunctionED2Ev
	.section	.text._ZN8FunctionC2Ev,"axG",@progbits,_ZN8FunctionC5Ev,comdat
	.align 2
	.weak	_ZN8FunctionC2Ev
	.type	_ZN8FunctionC2Ev, @function
_ZN8FunctionC2Ev:
.LFB1995:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1995
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
.LEHB2:
	call	_ZNSsC1Ev
.LEHE2:
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 16
	mov	rdi, rax
.LEHB3:
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC1Ev
.LEHE3:
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 64
	mov	rdi, rax
.LEHB4:
	call	_ZNSt6vectorI11InstructionSaIS0_EEC1Ev
.LEHE4:
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 88
	mov	rdi, rax
.LEHB5:
	call	_ZNSt6vectorIhSaIhEEC1Ev
.LEHE5:
	jmp	.L24
.L23:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 64
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EED1Ev
	jmp	.L19
.L22:
	mov	rbx, rax
.L19:
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 16
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED1Ev
	jmp	.L20
.L21:
	mov	rbx, rax
.L20:
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
.L24:
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1995:
	.section	.gcc_except_table
.LLSDA1995:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1995-.LLSDACSB1995
.LLSDACSB1995:
	.uleb128 .LEHB2-.LFB1995
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB1995
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L21-.LFB1995
	.uleb128 0
	.uleb128 .LEHB4-.LFB1995
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L22-.LFB1995
	.uleb128 0
	.uleb128 .LEHB5-.LFB1995
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L23-.LFB1995
	.uleb128 0
	.uleb128 .LEHB6-.LFB1995
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE1995:
	.section	.text._ZN8FunctionC2Ev,"axG",@progbits,_ZN8FunctionC5Ev,comdat
	.size	_ZN8FunctionC2Ev, .-_ZN8FunctionC2Ev
	.weak	_ZN8FunctionC1Ev
	.set	_ZN8FunctionC1Ev,_ZN8FunctionC2Ev
	.section	.text._ZN8FunctionD2Ev,"axG",@progbits,_ZN8FunctionD5Ev,comdat
	.align 2
	.weak	_ZN8FunctionD2Ev
	.type	_ZN8FunctionD2Ev, @function
_ZN8FunctionD2Ev:
.LFB1998:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 88
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 64
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EED1Ev
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 16
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED1Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSsD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1998:
	.size	_ZN8FunctionD2Ev, .-_ZN8FunctionD2Ev
	.weak	_ZN8FunctionD1Ev
	.set	_ZN8FunctionD1Ev,_ZN8FunctionD2Ev
	.section	.text._ZNSt4pairISsjEC1ERKS0_,"axG",@progbits,_ZNSt4pairISsjEC1ERKS0_,comdat
	.align 2
	.weak	_ZNSt4pairISsjEC1ERKS0_
	.type	_ZNSt4pairISsjEC1ERKS0_, @function
_ZNSt4pairISsjEC1ERKS0_:
.LFB2003:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1ERKSs
	mov	rax, QWORD PTR [rbp-16]
	mov	edx, DWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+8], edx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2003:
	.size	_ZNSt4pairISsjEC1ERKS0_, .-_ZNSt4pairISsjEC1ERKS0_
	.section	.text._ZNSt4pairISsjED2Ev,"axG",@progbits,_ZNSt4pairISsjED5Ev,comdat
	.align 2
	.weak	_ZNSt4pairISsjED2Ev
	.type	_ZNSt4pairISsjED2Ev, @function
_ZNSt4pairISsjED2Ev:
.LFB2005:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSsD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2005:
	.size	_ZNSt4pairISsjED2Ev, .-_ZNSt4pairISsjED2Ev
	.weak	_ZNSt4pairISsjED1Ev
	.set	_ZNSt4pairISsjED1Ev,_ZNSt4pairISsjED2Ev
	.section	.text._ZNSt4pairIKS_ISsjESsEC1ERKS2_,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC1ERKS2_,comdat
	.align 2
	.weak	_ZNSt4pairIKS_ISsjESsEC1ERKS2_
	.type	_ZNSt4pairIKS_ISsjESsEC1ERKS2_, @function
_ZNSt4pairIKS_ISsjESsEC1ERKS2_:
.LFB2008:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2008
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB7:
	call	_ZNSt4pairISsjEC1ERKS0_
.LEHE7:
	mov	rax, QWORD PTR [rbp-32]
	lea	rdx, [rax+16]
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 16
	mov	rsi, rdx
	mov	rdi, rax
.LEHB8:
	call	_ZNSsC1ERKSs
.LEHE8:
	jmp	.L33
.L32:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt4pairISsjED1Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB9:
	call	_Unwind_Resume
.LEHE9:
.L33:
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2008:
	.section	.gcc_except_table
.LLSDA2008:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2008-.LLSDACSB2008
.LLSDACSB2008:
	.uleb128 .LEHB7-.LFB2008
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB2008
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L32-.LFB2008
	.uleb128 0
	.uleb128 .LEHB9-.LFB2008
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE2008:
	.section	.text._ZNSt4pairIKS_ISsjESsEC1ERKS2_,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC1ERKS2_,comdat
	.size	_ZNSt4pairIKS_ISsjESsEC1ERKS2_, .-_ZNSt4pairIKS_ISsjESsEC1ERKS2_
	.section	.text._ZNSt4pairIKS_ISsjESsED2Ev,"axG",@progbits,_ZNSt4pairIKS_ISsjESsED5Ev,comdat
	.align 2
	.weak	_ZNSt4pairIKS_ISsjESsED2Ev
	.type	_ZNSt4pairIKS_ISsjESsED2Ev, @function
_ZNSt4pairIKS_ISsjESsED2Ev:
.LFB2010:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 16
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt4pairISsjED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2010:
	.size	_ZNSt4pairIKS_ISsjESsED2Ev, .-_ZNSt4pairIKS_ISsjESsED2Ev
	.weak	_ZNSt4pairIKS_ISsjESsED1Ev
	.set	_ZNSt4pairIKS_ISsjESsED1Ev,_ZNSt4pairIKS_ISsjESsED2Ev
	.section	.rodata
.LC0:
	.string	"Defined function '"
.LC1:
	.string	"' at "
.LC2:
	.string	"Function '"
.LC3:
	.string	"' not found."
.LC4:
	.string	"main"
	.text
	.globl	_ZN13CodeGenerator15generateProgramER7ProgramR7VMState
	.type	_ZN13CodeGenerator15generateProgramER7ProgramR7VMState, @function
_ZN13CodeGenerator15generateProgramER7ProgramR7VMState:
.LFB1984:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1984
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 384
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-392], rdi
	mov	QWORD PTR [rbp-400], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-24], rax
	xor	eax, eax
	lea	rax, [rbp-192]
	mov	rdi, rax
.LEHB10:
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC1Ev
.LEHE10:
	mov	rax, QWORD PTR [rbp-392]
	mov	QWORD PTR [rbp-304], rax
	mov	rax, QWORD PTR [rbp-304]
	mov	rdi, rax
	call	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv
	mov	QWORD PTR [rbp-368], rax
	mov	rax, QWORD PTR [rbp-304]
	mov	rdi, rax
	call	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv
	mov	QWORD PTR [rbp-352], rax
	jmp	.L37
.L40:
	lea	rax, [rbp-368]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv
	mov	rdx, rax
	lea	rax, [rbp-256]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB11:
	call	_ZNSt4pairIKSs15DefinedFunctionEC1ERKS2_
.LEHE11:
	lea	rax, [rbp-144]
	mov	rdi, rax
.LEHB12:
	call	_ZN8FunctionC1Ev
.LEHE12:
	lea	rdx, [rbp-256]
	lea	rax, [rbp-144]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB13:
	call	_ZNSsaSERKSs
	mov	eax, DWORD PTR [rbp-248]
	mov	DWORD PTR [rbp-136], eax
	mov	rax, QWORD PTR [rbp-240]
	lea	rdx, [rbp-144]
	add	rdx, 64
	mov	rsi, rax
	mov	rdi, rdx
	call	_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_
	mov	rdx, QWORD PTR [rbp-400]
	lea	rax, [rbp-144]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN13CodeGenerator16generateFunctionER8FunctionRK7VMState
	mov	QWORD PTR [rbp-296], rax
	mov	rbx, QWORD PTR [rbp-296]
	mov	esi, OFFSET FLAT:.LC0
	mov	edi, OFFSET FLAT:_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	lea	rdx, [rbp-256]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E
	mov	esi, OFFSET FLAT:.LC1
	mov	rdi, rax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZNSolsEl
	mov	esi, OFFSET FLAT:_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	mov	rdi, rax
	call	_ZNSolsEPFRSoS_E
.LEHE13:
	lea	rax, [rbp-144]
	add	rax, 16
	mov	QWORD PTR [rbp-288], rax
	mov	rax, QWORD PTR [rbp-288]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv
	mov	QWORD PTR [rbp-336], rax
	mov	rax, QWORD PTR [rbp-288]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv
	mov	QWORD PTR [rbp-320], rax
	jmp	.L38
.L39:
	lea	rax, [rbp-336]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	mov	rdx, rax
	lea	rax, [rbp-224]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB14:
	call	_ZNSt4pairIKS_ISsjESsEC1ERKS2_
.LEHE14:
	lea	rdx, [rbp-224]
	lea	rax, [rbp-192]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB15:
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_
	lea	rdx, [rbp-224]
	add	rdx, 16
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsaSERKSs
.LEHE15:
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSt4pairIKS_ISsjESsED1Ev
	lea	rax, [rbp-336]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv
.L38:
	lea	rdx, [rbp-320]
	lea	rax, [rbp-336]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_
	test	al, al
	jne	.L39
	mov	rax, QWORD PTR [rbp-400]
	lea	rdx, [rax+32]
	lea	rax, [rbp-256]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB16:
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_
.LEHE16:
	mov	rdx, QWORD PTR [rbp-296]
	mov	QWORD PTR [rax], rdx
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZN8FunctionD1Ev
	lea	rax, [rbp-256]
	mov	rdi, rax
	call	_ZNSt4pairIKSs15DefinedFunctionED1Ev
	lea	rax, [rbp-368]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv
.L37:
	lea	rdx, [rbp-352]
	lea	rax, [rbp-368]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_
	test	al, al
	jne	.L40
	lea	rax, [rbp-192]
	mov	QWORD PTR [rbp-280], rax
	mov	rax, QWORD PTR [rbp-280]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv
	mov	QWORD PTR [rbp-352], rax
	mov	rax, QWORD PTR [rbp-280]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv
	mov	QWORD PTR [rbp-336], rax
	jmp	.L41
.L46:
	lea	rax, [rbp-352]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	mov	rdx, rax
	lea	rax, [rbp-144]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB17:
	call	_ZNSt4pairIKS_ISsjESsEC1ERKS2_
.LEHE17:
	lea	rdx, [rbp-144]
	lea	rax, [rbp-320]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB18:
	call	_ZNSsC1ERKSs
.LEHE18:
	mov	eax, DWORD PTR [rbp-136]
	mov	DWORD PTR [rbp-376], eax
	lea	rax, [rbp-144]
	lea	rdx, [rax+16]
	lea	rax, [rbp-256]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB19:
	call	_ZNSsC1ERKSs
.LEHE19:
	mov	rax, QWORD PTR [rbp-400]
	lea	rdx, [rax+32]
	lea	rax, [rbp-256]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB20:
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_
.LEHE20:
	test	rax, rax
	setne	al
	test	al, al
	je	.L42
	mov	rax, QWORD PTR [rbp-400]
	lea	rdx, [rax+32]
	lea	rax, [rbp-256]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB21:
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-272], rax
	mov	rax, QWORD PTR [rbp-400]
	lea	rdx, [rax+32]
	lea	rax, [rbp-320]
	mov	rsi, rax
	mov	rdi, rdx
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_
.LEHE21:
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-264], rax
	mov	rax, QWORD PTR [rbp-272]
	mov	QWORD PTR [rbp-32], rax
	mov	eax, DWORD PTR [rbp-376]
	add	eax, 2
	mov	DWORD PTR [rbp-372], eax
	mov	DWORD PTR [rbp-380], 0
	jmp	.L43
.L44:
	mov	eax, DWORD PTR [rbp-380]
	mov	edx, DWORD PTR [rbp-372]
	add	eax, edx
	movsx	rdx, eax
	mov	rax, QWORD PTR [rbp-264]
	add	rdx, rax
	mov	eax, DWORD PTR [rbp-380]
	cdqe
	movzx	eax, BYTE PTR [rbp-32+rax]
	mov	BYTE PTR [rdx], al
	add	DWORD PTR [rbp-380], 1
.L43:
	cmp	DWORD PTR [rbp-380], 7
	jle	.L44
	lea	rax, [rbp-256]
	mov	rdi, rax
	call	_ZNSsD1Ev
	lea	rax, [rbp-320]
	mov	rdi, rax
	call	_ZNSsD1Ev
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZNSt4pairIKS_ISsjESsED1Ev
	lea	rax, [rbp-352]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv
	jmp	.L41
.L42:
	mov	edi, 8
	call	__cxa_allocate_exception
	mov	rbx, rax
	lea	rax, [rbp-224]
	lea	rdx, [rbp-256]
	mov	esi, OFFSET FLAT:.LC2
	mov	rdi, rax
.LEHB22:
	call	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_
.LEHE22:
	lea	rax, [rbp-224]
	mov	edx, OFFSET FLAT:.LC3
	mov	rsi, rax
	mov	rdi, rbx
.LEHB23:
	call	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_
.LEHE23:
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	edx, OFFSET FLAT:_ZNSsD1Ev
	mov	esi, OFFSET FLAT:_ZTISs
	mov	rdi, rbx
.LEHB24:
	call	__cxa_throw
.LEHE24:
.L41:
	lea	rdx, [rbp-336]
	lea	rax, [rbp-352]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_
	test	al, al
	jne	.L46
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSaIcEC1Ev
	lea	rdx, [rbp-224]
	lea	rax, [rbp-144]
	mov	esi, OFFSET FLAT:.LC4
	mov	rdi, rax
.LEHB25:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE25:
	mov	rax, QWORD PTR [rbp-400]
	lea	rdx, [rax+32]
	lea	rax, [rbp-144]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB26:
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs
.LEHE26:
	mov	rax, QWORD PTR [rax]
	mov	rbx, rax
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZNSsD1Ev
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSaIcED1Ev
	lea	rax, [rbp-192]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED1Ev
	mov	rax, rbx
	mov	rcx, QWORD PTR [rbp-24]
	xor	rcx, QWORD PTR fs:40
	je	.L64
	jmp	.L80
.L70:
	mov	rbx, rax
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSt4pairIKS_ISsjESsED1Ev
	mov	rax, rbx
	jmp	.L49
.L69:
.L49:
	mov	rbx, rax
	jmp	.L50
.L68:
	mov	rbx, rax
.L50:
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZN8FunctionD1Ev
	jmp	.L51
.L67:
	mov	rbx, rax
.L51:
	lea	rax, [rbp-256]
	mov	rdi, rax
	call	_ZNSt4pairIKSs15DefinedFunctionED1Ev
	mov	rax, rbx
	jmp	.L52
.L66:
.L52:
	mov	rbx, rax
	jmp	.L53
.L75:
	mov	rbx, rax
	jmp	.L55
.L77:
	mov	r12, rax
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSsD1Ev
	jmp	.L57
.L76:
	mov	r12, rax
.L57:
	mov	rdi, rbx
	call	__cxa_free_exception
	mov	rbx, r12
	jmp	.L55
.L74:
	mov	rbx, rax
.L55:
	lea	rax, [rbp-256]
	mov	rdi, rax
	call	_ZNSsD1Ev
	jmp	.L58
.L73:
	mov	rbx, rax
.L58:
	lea	rax, [rbp-320]
	mov	rdi, rax
	call	_ZNSsD1Ev
	jmp	.L59
.L72:
	mov	rbx, rax
.L59:
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZNSt4pairIKS_ISsjESsED1Ev
	mov	rax, rbx
	jmp	.L60
.L71:
.L60:
	mov	rbx, rax
	jmp	.L53
.L79:
	mov	rbx, rax
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZNSsD1Ev
	jmp	.L62
.L78:
	mov	rbx, rax
.L62:
	lea	rax, [rbp-224]
	mov	rdi, rax
	call	_ZNSaIcED1Ev
.L53:
	lea	rax, [rbp-192]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEED1Ev
	mov	rax, rbx
	jmp	.L63
.L65:
.L63:
	mov	rdi, rax
.LEHB27:
	call	_Unwind_Resume
.LEHE27:
.L80:
	call	__stack_chk_fail
.L64:
	add	rsp, 384
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1984:
	.section	.gcc_except_table
.LLSDA1984:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1984-.LLSDACSB1984
.LLSDACSB1984:
	.uleb128 .LEHB10-.LFB1984
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L65-.LFB1984
	.uleb128 0
	.uleb128 .LEHB11-.LFB1984
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L66-.LFB1984
	.uleb128 0
	.uleb128 .LEHB12-.LFB1984
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L67-.LFB1984
	.uleb128 0
	.uleb128 .LEHB13-.LFB1984
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L68-.LFB1984
	.uleb128 0
	.uleb128 .LEHB14-.LFB1984
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L69-.LFB1984
	.uleb128 0
	.uleb128 .LEHB15-.LFB1984
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L70-.LFB1984
	.uleb128 0
	.uleb128 .LEHB16-.LFB1984
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L68-.LFB1984
	.uleb128 0
	.uleb128 .LEHB17-.LFB1984
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L71-.LFB1984
	.uleb128 0
	.uleb128 .LEHB18-.LFB1984
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L72-.LFB1984
	.uleb128 0
	.uleb128 .LEHB19-.LFB1984
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L73-.LFB1984
	.uleb128 0
	.uleb128 .LEHB20-.LFB1984
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L74-.LFB1984
	.uleb128 0
	.uleb128 .LEHB21-.LFB1984
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L75-.LFB1984
	.uleb128 0
	.uleb128 .LEHB22-.LFB1984
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L76-.LFB1984
	.uleb128 0
	.uleb128 .LEHB23-.LFB1984
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L77-.LFB1984
	.uleb128 0
	.uleb128 .LEHB24-.LFB1984
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L74-.LFB1984
	.uleb128 0
	.uleb128 .LEHB25-.LFB1984
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L78-.LFB1984
	.uleb128 0
	.uleb128 .LEHB26-.LFB1984
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L79-.LFB1984
	.uleb128 0
	.uleb128 .LEHB27-.LFB1984
	.uleb128 .LEHE27-.LEHB27
	.uleb128 0
	.uleb128 0
.LLSDACSE1984:
	.text
	.size	_ZN13CodeGenerator15generateProgramER7ProgramR7VMState, .-_ZN13CodeGenerator15generateProgramER7ProgramR7VMState
	.section	.text._ZN11InstructionC2ERKS_,"axG",@progbits,_ZN11InstructionC5ERKS_,comdat
	.align 2
	.weak	_ZN11InstructionC2ERKS_
	.type	_ZN11InstructionC2ERKS_, @function
_ZN11InstructionC2ERKS_:
.LFB2014:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax], edx
	mov	rax, QWORD PTR [rbp-16]
	mov	edx, DWORD PTR [rax+4]
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+4], edx
	mov	rax, QWORD PTR [rbp-16]
	lea	rdx, [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 8
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1ERKSs
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2014:
	.size	_ZN11InstructionC2ERKS_, .-_ZN11InstructionC2ERKS_
	.weak	_ZN11InstructionC1ERKS_
	.set	_ZN11InstructionC1ERKS_,_ZN11InstructionC2ERKS_
	.section	.text._ZN11InstructionD2Ev,"axG",@progbits,_ZN11InstructionD5Ev,comdat
	.align 2
	.weak	_ZN11InstructionD2Ev
	.type	_ZN11InstructionD2Ev, @function
_ZN11InstructionD2Ev:
.LFB2017:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 8
	mov	rdi, rax
	call	_ZNSsD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2017:
	.size	_ZN11InstructionD2Ev, .-_ZN11InstructionD2Ev
	.weak	_ZN11InstructionD1Ev
	.set	_ZN11InstructionD1Ev,_ZN11InstructionD2Ev
	.section	.rodata
.LC5:
	.string	"Func '"
.LC6:
	.string	"' size: "
	.text
	.globl	_ZN13CodeGenerator16generateFunctionER8FunctionRK7VMState
	.type	_ZN13CodeGenerator16generateFunctionER8FunctionRK7VMState, @function
_ZN13CodeGenerator16generateFunctionER8FunctionRK7VMState:
.LFB2012:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2012
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 200
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	mov	QWORD PTR [rbp-168], rdi
	mov	QWORD PTR [rbp-176], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-56], rax
	xor	eax, eax
	mov	BYTE PTR [rbp-96], 85
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB28:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE28:
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	test	eax, eax
	jle	.L85
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	sal	eax, 2
	mov	BYTE PTR [rbp-150], al
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhEC1Ev
	mov	BYTE PTR [rbp-64], 72
	mov	BYTE PTR [rbp-63], -125
	mov	BYTE PTR [rbp-62], -20
	movzx	eax, BYTE PTR [rbp-150]
	mov	BYTE PTR [rbp-61], al
	lea	rax, [rbp-64]
	mov	QWORD PTR [rbp-240], rax
	mov	QWORD PTR [rbp-232], 4
	lea	rdi, [rbp-128]
	mov	rax, QWORD PTR [rbp-240]
	mov	rdx, QWORD PTR [rbp-232]
	mov	rcx, rax
	mov	rbx, rdx
	mov	rsi, rcx
	lea	rax, [rbp-96]
	mov	rcx, rdi
	mov	rdi, rax
.LEHB29:
	call	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
.LEHE29:
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB30:
	call	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
.LEHE30:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	cmp	eax, 3
	jle	.L86
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhEC1Ev
	mov	QWORD PTR [rbp-224], OFFSET FLAT:._84
	mov	QWORD PTR [rbp-216], 4
	lea	rdi, [rbp-128]
	mov	rax, QWORD PTR [rbp-224]
	mov	rdx, QWORD PTR [rbp-216]
	mov	rcx, rax
	mov	rbx, rdx
	mov	rsi, rcx
	lea	rax, [rbp-96]
	mov	rcx, rdi
	mov	rdi, rax
.LEHB31:
	call	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
.LEHE31:
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB32:
	call	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
.LEHE32:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
.L86:
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	cmp	eax, 2
	jle	.L87
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhEC1Ev
	mov	QWORD PTR [rbp-208], OFFSET FLAT:._85
	mov	QWORD PTR [rbp-200], 4
	lea	rdi, [rbp-128]
	mov	rax, QWORD PTR [rbp-208]
	mov	rdx, QWORD PTR [rbp-200]
	mov	rcx, rax
	mov	rbx, rdx
	mov	rsi, rcx
	lea	rax, [rbp-96]
	mov	rcx, rdi
	mov	rdi, rax
.LEHB33:
	call	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
.LEHE33:
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB34:
	call	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
.LEHE34:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
.L87:
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	cmp	eax, 1
	jle	.L88
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhEC1Ev
	mov	QWORD PTR [rbp-192], OFFSET FLAT:._86
	mov	QWORD PTR [rbp-184], 4
	lea	rdi, [rbp-128]
	mov	rax, QWORD PTR [rbp-192]
	mov	rdx, QWORD PTR [rbp-184]
	mov	rcx, rax
	mov	rbx, rdx
	mov	rsi, rcx
	lea	rax, [rbp-96]
	mov	rcx, rdi
	mov	rdi, rax
.LEHB35:
	call	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
.LEHE35:
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB36:
	call	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
.LEHE36:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
.L88:
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	test	eax, eax
	jle	.L89
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhEC1Ev
	mov	r14d, OFFSET FLAT:._87
	mov	r15d, 4
	lea	rdi, [rbp-128]
	mov	rcx, r14
	mov	rbx, r15
	mov	rax, r14
	mov	rdx, r15
	mov	rsi, rcx
	lea	rax, [rbp-96]
	mov	rcx, rdi
	mov	rdi, rax
.LEHB37:
	call	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
.LEHE37:
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB38:
	call	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
.LEHE38:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
.L89:
.L85:
	mov	rax, QWORD PTR [rbp-168]
	add	rax, 64
	mov	QWORD PTR [rbp-120], rax
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE5beginEv
	mov	QWORD PTR [rbp-144], rax
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE3endEv
	mov	QWORD PTR [rbp-128], rax
	jmp	.L90
.L91:
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	mov	rdx, rax
	lea	rax, [rbp-96]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB39:
	call	_ZN11InstructionC1ERKS_
.LEHE39:
	lea	rdx, [rbp-96]
	mov	rcx, QWORD PTR [rbp-176]
	mov	rax, QWORD PTR [rbp-168]
	mov	rsi, rcx
	mov	rdi, rax
.LEHB40:
	call	_ZN13CodeGenerator12generateCodeER8FunctionRK7VMStateRK11Instruction
.LEHE40:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZN11InstructionD1Ev
	lea	rax, [rbp-144]
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv
.L90:
	lea	rdx, [rbp-128]
	lea	rax, [rbp-144]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB41:
	call	_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_
.LEHE41:
	test	al, al
	jne	.L91
	mov	BYTE PTR [rbp-96], 88
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB42:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE42:
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	test	eax, eax
	jle	.L92
	mov	rax, QWORD PTR [rbp-168]
	mov	eax, DWORD PTR [rax+8]
	sal	eax, 2
	mov	BYTE PTR [rbp-149], al
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhEC1Ev
	mov	BYTE PTR [rbp-64], 72
	mov	BYTE PTR [rbp-63], -125
	mov	BYTE PTR [rbp-62], -60
	movzx	eax, BYTE PTR [rbp-149]
	mov	BYTE PTR [rbp-61], al
	lea	rax, [rbp-64]
	mov	r12, rax
	mov	r13d, 4
	lea	rdi, [rbp-128]
	mov	rcx, r12
	mov	rbx, r13
	mov	rax, r12
	mov	rdx, r13
	mov	rsi, rcx
	lea	rax, [rbp-96]
	mov	rcx, rdi
	mov	rdi, rax
.LEHB43:
	call	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
.LEHE43:
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB44:
	call	_Z9pushArrayRSt6vectorIhSaIhEERKS1_
.LEHE44:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
.L92:
	mov	BYTE PTR [rbp-96], 93
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB45:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE45:
	mov	BYTE PTR [rbp-96], -61
	mov	rax, QWORD PTR [rbp-168]
	lea	rdx, [rax+88]
	lea	rax, [rbp-96]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB46:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE46:
	mov	rax, QWORD PTR [rbp-168]
	add	rax, 88
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE4dataEv
	mov	QWORD PTR [rbp-112], rax
	mov	rax, QWORD PTR [rbp-168]
	add	rax, 88
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	DWORD PTR [rbp-148], eax
	mov	rbx, QWORD PTR [rbp-168]
	mov	esi, OFFSET FLAT:.LC5
	mov	edi, OFFSET FLAT:_ZSt4cout
.LEHB47:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E
	mov	esi, OFFSET FLAT:.LC6
	mov	rdi, rax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	edx, DWORD PTR [rbp-148]
	mov	esi, edx
	mov	rdi, rax
	call	_ZNSolsEi
	mov	esi, OFFSET FLAT:_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	mov	rdi, rax
	call	_ZNSolsEPFRSoS_E
	mov	eax, DWORD PTR [rbp-148]
	cdqe
	mov	r9d, 0
	mov	r8d, -1
	mov	ecx, 34
	mov	edx, 6
	mov	rsi, rax
	mov	edi, 0
	call	mmap
	mov	QWORD PTR [rbp-104], rax
	mov	eax, DWORD PTR [rbp-148]
	movsx	rdx, eax
	mov	rcx, QWORD PTR [rbp-112]
	mov	rax, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	memcpy
	mov	rax, QWORD PTR [rbp-104]
	mov	rcx, QWORD PTR [rbp-56]
	xor	rcx, QWORD PTR fs:40
	je	.L112
	jmp	.L131
.L113:
	mov	rdi, rax
	call	_Unwind_Resume
.L115:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	mov	rax, rbx
	jmp	.L96
.L114:
.L96:
	mov	rbx, rax
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, rbx
	mov	rdi, rax
	call	_Unwind_Resume
.L117:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	jmp	.L98
.L116:
	mov	rbx, rax
.L98:
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, rbx
	mov	rdi, rax
	call	_Unwind_Resume
.L119:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	jmp	.L100
.L118:
	mov	rbx, rax
.L100:
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, rbx
	mov	rdi, rax
	call	_Unwind_Resume
.L121:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	jmp	.L102
.L120:
	mov	rbx, rax
.L102:
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, rbx
	mov	rdi, rax
	call	_Unwind_Resume
.L123:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	jmp	.L104
.L122:
	mov	rbx, rax
.L104:
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, rbx
	mov	rdi, rax
	call	_Unwind_Resume
.L125:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZN11InstructionD1Ev
	mov	rax, rbx
	jmp	.L106
.L124:
.L106:
	mov	rdi, rax
	call	_Unwind_Resume
.L126:
	mov	rdi, rax
	call	_Unwind_Resume
.L128:
	mov	rbx, rax
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEED1Ev
	mov	rax, rbx
	jmp	.L109
.L127:
.L109:
	mov	rbx, rax
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSaIhED1Ev
	mov	rax, rbx
	mov	rdi, rax
	call	_Unwind_Resume
.L129:
	mov	rdi, rax
	call	_Unwind_Resume
.L130:
	mov	rdi, rax
	call	_Unwind_Resume
.LEHE47:
.L131:
	call	__stack_chk_fail
.L112:
	add	rsp, 200
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2012:
	.section	.gcc_except_table
.LLSDA2012:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2012-.LLSDACSB2012
.LLSDACSB2012:
	.uleb128 .LEHB28-.LFB2012
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L113-.LFB2012
	.uleb128 0
	.uleb128 .LEHB29-.LFB2012
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L114-.LFB2012
	.uleb128 0
	.uleb128 .LEHB30-.LFB2012
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L115-.LFB2012
	.uleb128 0
	.uleb128 .LEHB31-.LFB2012
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L116-.LFB2012
	.uleb128 0
	.uleb128 .LEHB32-.LFB2012
	.uleb128 .LEHE32-.LEHB32
	.uleb128 .L117-.LFB2012
	.uleb128 0
	.uleb128 .LEHB33-.LFB2012
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L118-.LFB2012
	.uleb128 0
	.uleb128 .LEHB34-.LFB2012
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L119-.LFB2012
	.uleb128 0
	.uleb128 .LEHB35-.LFB2012
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L120-.LFB2012
	.uleb128 0
	.uleb128 .LEHB36-.LFB2012
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L121-.LFB2012
	.uleb128 0
	.uleb128 .LEHB37-.LFB2012
	.uleb128 .LEHE37-.LEHB37
	.uleb128 .L122-.LFB2012
	.uleb128 0
	.uleb128 .LEHB38-.LFB2012
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L123-.LFB2012
	.uleb128 0
	.uleb128 .LEHB39-.LFB2012
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L124-.LFB2012
	.uleb128 0
	.uleb128 .LEHB40-.LFB2012
	.uleb128 .LEHE40-.LEHB40
	.uleb128 .L125-.LFB2012
	.uleb128 0
	.uleb128 .LEHB41-.LFB2012
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L124-.LFB2012
	.uleb128 0
	.uleb128 .LEHB42-.LFB2012
	.uleb128 .LEHE42-.LEHB42
	.uleb128 .L126-.LFB2012
	.uleb128 0
	.uleb128 .LEHB43-.LFB2012
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L127-.LFB2012
	.uleb128 0
	.uleb128 .LEHB44-.LFB2012
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L128-.LFB2012
	.uleb128 0
	.uleb128 .LEHB45-.LFB2012
	.uleb128 .LEHE45-.LEHB45
	.uleb128 .L129-.LFB2012
	.uleb128 0
	.uleb128 .LEHB46-.LFB2012
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L130-.LFB2012
	.uleb128 0
	.uleb128 .LEHB47-.LFB2012
	.uleb128 .LEHE47-.LEHB47
	.uleb128 0
	.uleb128 0
.LLSDACSE2012:
	.text
	.size	_ZN13CodeGenerator16generateFunctionER8FunctionRK7VMState, .-_ZN13CodeGenerator16generateFunctionER8FunctionRK7VMState
	.section	.text._ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE,"axG",@progbits,_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE,comdat
	.weak	_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE
	.type	_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE, @function
_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE:
.LFB2021:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2021:
	.size	_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE, .-_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE
	.section	.text._ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE,"axG",@progbits,_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE,comdat
	.weak	_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE
	.type	_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE, @function
_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE:
.LFB2022:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2022:
	.size	_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE, .-_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE
	.section	.text._ZNSt4pairISsmEC1IRSsmvEEOT_OT0_,"axG",@progbits,_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_,comdat
	.align 2
	.weak	_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_
	.type	_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_, @function
_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_:
.LFB2025:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1ERKSs
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2025:
	.size	_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_, .-_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_
	.section	.text._ZNSt4pairISsmED2Ev,"axG",@progbits,_ZNSt4pairISsmED5Ev,comdat
	.align 2
	.weak	_ZNSt4pairISsmED2Ev
	.type	_ZNSt4pairISsmED2Ev, @function
_ZNSt4pairISsmED2Ev:
.LFB2027:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSsD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2027:
	.size	_ZNSt4pairISsmED2Ev, .-_ZNSt4pairISsmED2Ev
	.weak	_ZNSt4pairISsmED1Ev
	.set	_ZNSt4pairISsmED1Ev,_ZNSt4pairISsmED2Ev
	.section	.text._ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_,"axG",@progbits,_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_,comdat
	.weak	_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_
	.type	_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_, @function
_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_:
.LFB2020:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt7forwardIRSsEOT_RNSt16remove_referenceIS1_E4typeE
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairISsmEC1IRSsmvEEOT_OT0_
	mov	rax, QWORD PTR [rbp-24]
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2020:
	.size	_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_, .-_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_
	.section	.text._ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE,"axG",@progbits,_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE,comdat
	.weak	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	.type	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE, @function
_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE:
.LFB2033:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2033:
	.size	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE, .-_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	.section	.text._ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E,"axG",@progbits,_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E,comdat
	.align 2
	.weak	_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E
	.type	_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E, @function
_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E:
.LFB2035:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1EOSs
	mov	rax, QWORD PTR [rbp-16]
	add	rax, 8
	mov	rdi, rax
	call	_ZSt7forwardImEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rax, QWORD PTR [rax]
	mov	edx, eax
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+8], edx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2035:
	.size	_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E, .-_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E
	.section	.rodata
.LC7:
	.string	"Calling '"
	.text
	.globl	_ZN13CodeGenerator12generateCodeER8FunctionRK7VMStateRK11Instruction
	.type	_ZN13CodeGenerator12generateCodeER8FunctionRK7VMStateRK11Instruction, @function
_ZN13CodeGenerator12generateCodeER8FunctionRK7VMStateRK11Instruction:
.LFB2019:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2019
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 232
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-216], rdi
	mov	QWORD PTR [rbp-224], rsi
	mov	QWORD PTR [rbp-232], rdx
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-24], rax
	xor	eax, eax
	mov	rax, QWORD PTR [rbp-216]
	add	rax, 88
	mov	QWORD PTR [rbp-152], rax
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax]
	cmp	eax, 8
	ja	.L257
	mov	eax, eax
	mov	rax, QWORD PTR .L147[0+rax*8]
	jmp	rax
	.section	.rodata
	.align 8
	.align 4
.L147:
	.quad	.L146
	.quad	.L148
	.quad	.L148
	.quad	.L148
	.quad	.L148
	.quad	.L149
	.quad	.L150
	.quad	.L151
	.quad	.L152
	.text
.L146:
	mov	BYTE PTR [rbp-208], 104
	lea	rdx, [rbp-208]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB48:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE48:
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax+4]
	mov	DWORD PTR [rbp-96], eax
	lea	rdx, [rbp-96]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB49:
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-96]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-96]
	lea	rdx, [rax+2]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-96]
	lea	rdx, [rax+3]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
.LEHE49:
	jmp	.L153
.L148:
	mov	BYTE PTR [rbp-207], 91
	lea	rdx, [rbp-207]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB50:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE50:
	mov	BYTE PTR [rbp-206], 88
	lea	rdx, [rbp-206]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB51:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE51:
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax]
	cmp	eax, 2
	je	.L155
	cmp	eax, 2
	jg	.L156
	cmp	eax, 1
	je	.L157
	jmp	.L160
.L156:
	cmp	eax, 3
	je	.L158
	cmp	eax, 4
	je	.L159
	jmp	.L160
.L157:
	mov	BYTE PTR [rbp-205], 1
	lea	rdx, [rbp-205]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB52:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE52:
	mov	BYTE PTR [rbp-204], -40
	lea	rdx, [rbp-204]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB53:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE53:
	jmp	.L160
.L155:
	mov	BYTE PTR [rbp-203], 41
	lea	rdx, [rbp-203]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB54:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE54:
	mov	BYTE PTR [rbp-202], -40
	lea	rdx, [rbp-202]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB55:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE55:
	jmp	.L160
.L158:
	mov	BYTE PTR [rbp-201], 15
	lea	rdx, [rbp-201]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB56:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE56:
	mov	BYTE PTR [rbp-200], -81
	lea	rdx, [rbp-200]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB57:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE57:
	mov	BYTE PTR [rbp-199], -61
	lea	rdx, [rbp-199]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB58:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE58:
	jmp	.L160
.L159:
	mov	BYTE PTR [rbp-198], -9
	lea	rdx, [rbp-198]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB59:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE59:
	mov	BYTE PTR [rbp-197], -5
	lea	rdx, [rbp-197]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB60:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE60:
	nop
.L160:
	mov	BYTE PTR [rbp-196], 80
	lea	rdx, [rbp-196]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB61:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE61:
	jmp	.L153
.L149:
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax+4]
	cdqe
	lea	rdx, [0+rax*4]
	mov	rax, QWORD PTR [rbp-224]
	add	rax, rdx
	mov	QWORD PTR [rbp-144], rax
	mov	rax, QWORD PTR [rbp-144]
	mov	QWORD PTR [rbp-64], rax
	mov	BYTE PTR [rbp-195], -95
	lea	rdx, [rbp-195]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB62:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE62:
	lea	rdx, [rbp-64]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB63:
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+2]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+3]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+4]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+5]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+6]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-64]
	lea	rdx, [rax+7]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
.LEHE63:
	mov	BYTE PTR [rbp-194], 80
	lea	rdx, [rbp-194]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB64:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE64:
	jmp	.L153
.L150:
	mov	BYTE PTR [rbp-193], 88
	lea	rdx, [rbp-193]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB65:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE65:
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax+4]
	cdqe
	lea	rdx, [0+rax*4]
	mov	rax, QWORD PTR [rbp-224]
	add	rax, rdx
	mov	QWORD PTR [rbp-136], rax
	mov	rax, QWORD PTR [rbp-136]
	mov	QWORD PTR [rbp-48], rax
	mov	BYTE PTR [rbp-192], -93
	lea	rdx, [rbp-192]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB66:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE66:
	lea	rdx, [rbp-48]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB67:
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+2]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+3]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+4]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+5]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+6]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-48]
	lea	rdx, [rax+7]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
.LEHE67:
	jmp	.L153
.L151:
	mov	QWORD PTR [rbp-160], 0
	mov	rax, QWORD PTR [rbp-232]
	lea	rdx, [rax+8]
	mov	rax, QWORD PTR [rbp-224]
	add	rax, 32
	mov	rsi, rdx
	mov	rdi, rax
.LEHB68:
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_
	test	rax, rax
	setne	al
	test	al, al
	je	.L161
	mov	rax, QWORD PTR [rbp-232]
	lea	rdx, [rax+8]
	mov	rax, QWORD PTR [rbp-224]
	add	rax, 32
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_
.LEHE68:
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-160], rax
	jmp	.L162
.L161:
	mov	rax, QWORD PTR [rbp-232]
	lea	rbx, [rax+8]
	mov	rax, QWORD PTR [rbp-152]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	QWORD PTR [rbp-168], rax
	mov	rcx, QWORD PTR [rbp-216]
	lea	rax, [rbp-128]
	lea	rdx, [rbp-168]
	mov	rsi, rcx
	mov	rdi, rax
.LEHB69:
	call	_ZSt9make_pairIRSsmESt4pairINSt17__decay_and_stripIT_E6__typeENS2_IT0_E6__typeEEOS3_OS6_
.LEHE69:
	lea	rdx, [rbp-128]
	lea	rax, [rbp-112]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt4pairISsjEC1ISsmvEEOS_IT_T0_E
	mov	rax, QWORD PTR [rbp-216]
	lea	rdx, [rax+16]
	lea	rax, [rbp-112]
	mov	rsi, rax
	mov	rdi, rdx
.LEHB70:
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZNSsaSERKSs
.LEHE70:
	lea	rax, [rbp-112]
	mov	rdi, rax
	call	_ZNSt4pairISsjED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSt4pairISsmED1Ev
.L162:
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax+4]
	mov	DWORD PTR [rbp-172], eax
	mov	rax, QWORD PTR [rbp-232]
	lea	rcx, [rax+8]
	lea	rax, [rbp-112]
	mov	edx, OFFSET FLAT:.LC1
	mov	rsi, rcx
	mov	rdi, rax
.LEHB71:
	call	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_
.LEHE71:
	mov	esi, OFFSET FLAT:.LC7
	mov	edi, OFFSET FLAT:_ZSt4cout
.LEHB72:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	lea	rdx, [rbp-112]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E
	mov	rdx, QWORD PTR [rbp-160]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSolsEl
	mov	esi, OFFSET FLAT:_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	mov	rdi, rax
	call	_ZNSolsEPFRSoS_E
.LEHE72:
	lea	rax, [rbp-112]
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	rax, QWORD PTR [rbp-160]
	mov	QWORD PTR [rbp-32], rax
	mov	BYTE PTR [rbp-191], 72
	lea	rdx, [rbp-191]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB73:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE73:
	mov	BYTE PTR [rbp-190], -72
	lea	rdx, [rbp-190]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB74:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE74:
	lea	rdx, [rbp-32]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB75:
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+2]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+3]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+4]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+5]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+6]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-32]
	lea	rdx, [rax+7]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
.LEHE75:
	cmp	DWORD PTR [rbp-172], 3
	jle	.L163
	mov	BYTE PTR [rbp-189], 89
	lea	rdx, [rbp-189]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB76:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE76:
.L163:
	cmp	DWORD PTR [rbp-172], 2
	jle	.L164
	mov	BYTE PTR [rbp-188], 90
	lea	rdx, [rbp-188]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB77:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE77:
.L164:
	cmp	DWORD PTR [rbp-172], 1
	jle	.L165
	mov	BYTE PTR [rbp-187], 94
	lea	rdx, [rbp-187]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB78:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE78:
.L165:
	cmp	DWORD PTR [rbp-172], 0
	jle	.L166
	mov	BYTE PTR [rbp-186], 95
	lea	rdx, [rbp-186]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB79:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE79:
.L166:
	mov	BYTE PTR [rbp-185], -1
	lea	rdx, [rbp-185]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB80:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE80:
	mov	BYTE PTR [rbp-184], -48
	lea	rdx, [rbp-184]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB81:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE81:
	mov	BYTE PTR [rbp-183], 80
	lea	rdx, [rbp-183]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB82:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE82:
	jmp	.L153
.L152:
	mov	rax, QWORD PTR [rbp-232]
	mov	eax, DWORD PTR [rax+4]
	not	eax
	sal	eax, 2
	mov	DWORD PTR [rbp-80], eax
	mov	BYTE PTR [rbp-182], 72
	lea	rdx, [rbp-182]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB83:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE83:
	mov	BYTE PTR [rbp-181], -57
	lea	rdx, [rbp-181]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB84:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE84:
	mov	BYTE PTR [rbp-180], -64
	lea	rdx, [rbp-180]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB85:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE85:
	lea	rdx, [rbp-80]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB86:
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-80]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-80]
	lea	rdx, [rax+2]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
	lea	rax, [rbp-80]
	lea	rdx, [rax+3]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE9push_backERKh
.LEHE86:
	mov	BYTE PTR [rbp-179], 72
	lea	rdx, [rbp-179]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB87:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE87:
	mov	BYTE PTR [rbp-178], 1
	lea	rdx, [rbp-178]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB88:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE88:
	mov	BYTE PTR [rbp-177], -24
	lea	rdx, [rbp-177]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB89:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE89:
	mov	BYTE PTR [rbp-176], 72
	lea	rdx, [rbp-176]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB90:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE90:
	mov	BYTE PTR [rbp-175], -117
	lea	rdx, [rbp-175]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB91:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE91:
	mov	BYTE PTR [rbp-174], 0
	lea	rdx, [rbp-174]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB92:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE92:
	mov	BYTE PTR [rbp-173], 80
	lea	rdx, [rbp-173]
	mov	rax, QWORD PTR [rbp-152]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB93:
	call	_ZNSt6vectorIhSaIhEE9push_backEOh
.LEHE93:
	jmp	.L153
.L257:
	nop
.L153:
	mov	rax, QWORD PTR [rbp-24]
	xor	rax, QWORD PTR fs:40
	je	.L211
	jmp	.L256
.L212:
	jmp	.L168
.L214:
	jmp	.L168
.L215:
	jmp	.L168
.L216:
	jmp	.L168
.L217:
	jmp	.L168
.L218:
	jmp	.L168
.L219:
	jmp	.L168
.L220:
	jmp	.L168
.L221:
	jmp	.L168
.L222:
	jmp	.L168
.L223:
	jmp	.L168
.L224:
	jmp	.L168
.L225:
	jmp	.L168
.L226:
	jmp	.L168
.L228:
	jmp	.L168
.L227:
	jmp	.L168
.L229:
	jmp	.L168
.L231:
	jmp	.L168
.L230:
	jmp	.L168
.L234:
	mov	rbx, rax
	lea	rax, [rbp-112]
	mov	rdi, rax
	call	_ZNSt4pairISsjED1Ev
	lea	rax, [rbp-128]
	mov	rdi, rax
	call	_ZNSt4pairISsmED1Ev
	mov	rax, rbx
	jmp	.L168
.L233:
	jmp	.L168
.L235:
	mov	rbx, rax
	lea	rax, [rbp-112]
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	rax, rbx
	jmp	.L168
.L236:
	jmp	.L168
.L237:
	jmp	.L168
.L238:
	jmp	.L168
.L239:
	jmp	.L168
.L240:
	jmp	.L168
.L241:
	jmp	.L168
.L242:
	jmp	.L168
.L243:
	jmp	.L168
.L244:
	jmp	.L168
.L232:
	jmp	.L168
.L245:
	jmp	.L168
.L247:
	jmp	.L168
.L248:
	jmp	.L168
.L249:
	jmp	.L168
.L250:
	jmp	.L168
.L251:
	jmp	.L168
.L252:
	jmp	.L168
.L253:
	jmp	.L168
.L254:
	jmp	.L168
.L255:
	jmp	.L168
.L246:
	jmp	.L168
.L213:
.L168:
	mov	rdi, rax
.LEHB94:
	call	_Unwind_Resume
.LEHE94:
.L256:
	call	__stack_chk_fail
.L211:
	add	rsp, 232
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2019:
	.section	.gcc_except_table
.LLSDA2019:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2019-.LLSDACSB2019
.LLSDACSB2019:
	.uleb128 .LEHB48-.LFB2019
	.uleb128 .LEHE48-.LEHB48
	.uleb128 .L212-.LFB2019
	.uleb128 0
	.uleb128 .LEHB49-.LFB2019
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L213-.LFB2019
	.uleb128 0
	.uleb128 .LEHB50-.LFB2019
	.uleb128 .LEHE50-.LEHB50
	.uleb128 .L214-.LFB2019
	.uleb128 0
	.uleb128 .LEHB51-.LFB2019
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L215-.LFB2019
	.uleb128 0
	.uleb128 .LEHB52-.LFB2019
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L216-.LFB2019
	.uleb128 0
	.uleb128 .LEHB53-.LFB2019
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L217-.LFB2019
	.uleb128 0
	.uleb128 .LEHB54-.LFB2019
	.uleb128 .LEHE54-.LEHB54
	.uleb128 .L218-.LFB2019
	.uleb128 0
	.uleb128 .LEHB55-.LFB2019
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L219-.LFB2019
	.uleb128 0
	.uleb128 .LEHB56-.LFB2019
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L220-.LFB2019
	.uleb128 0
	.uleb128 .LEHB57-.LFB2019
	.uleb128 .LEHE57-.LEHB57
	.uleb128 .L221-.LFB2019
	.uleb128 0
	.uleb128 .LEHB58-.LFB2019
	.uleb128 .LEHE58-.LEHB58
	.uleb128 .L222-.LFB2019
	.uleb128 0
	.uleb128 .LEHB59-.LFB2019
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L223-.LFB2019
	.uleb128 0
	.uleb128 .LEHB60-.LFB2019
	.uleb128 .LEHE60-.LEHB60
	.uleb128 .L224-.LFB2019
	.uleb128 0
	.uleb128 .LEHB61-.LFB2019
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L225-.LFB2019
	.uleb128 0
	.uleb128 .LEHB62-.LFB2019
	.uleb128 .LEHE62-.LEHB62
	.uleb128 .L226-.LFB2019
	.uleb128 0
	.uleb128 .LEHB63-.LFB2019
	.uleb128 .LEHE63-.LEHB63
	.uleb128 .L227-.LFB2019
	.uleb128 0
	.uleb128 .LEHB64-.LFB2019
	.uleb128 .LEHE64-.LEHB64
	.uleb128 .L228-.LFB2019
	.uleb128 0
	.uleb128 .LEHB65-.LFB2019
	.uleb128 .LEHE65-.LEHB65
	.uleb128 .L229-.LFB2019
	.uleb128 0
	.uleb128 .LEHB66-.LFB2019
	.uleb128 .LEHE66-.LEHB66
	.uleb128 .L231-.LFB2019
	.uleb128 0
	.uleb128 .LEHB67-.LFB2019
	.uleb128 .LEHE67-.LEHB67
	.uleb128 .L230-.LFB2019
	.uleb128 0
	.uleb128 .LEHB68-.LFB2019
	.uleb128 .LEHE68-.LEHB68
	.uleb128 .L232-.LFB2019
	.uleb128 0
	.uleb128 .LEHB69-.LFB2019
	.uleb128 .LEHE69-.LEHB69
	.uleb128 .L233-.LFB2019
	.uleb128 0
	.uleb128 .LEHB70-.LFB2019
	.uleb128 .LEHE70-.LEHB70
	.uleb128 .L234-.LFB2019
	.uleb128 0
	.uleb128 .LEHB71-.LFB2019
	.uleb128 .LEHE71-.LEHB71
	.uleb128 .L232-.LFB2019
	.uleb128 0
	.uleb128 .LEHB72-.LFB2019
	.uleb128 .LEHE72-.LEHB72
	.uleb128 .L235-.LFB2019
	.uleb128 0
	.uleb128 .LEHB73-.LFB2019
	.uleb128 .LEHE73-.LEHB73
	.uleb128 .L236-.LFB2019
	.uleb128 0
	.uleb128 .LEHB74-.LFB2019
	.uleb128 .LEHE74-.LEHB74
	.uleb128 .L237-.LFB2019
	.uleb128 0
	.uleb128 .LEHB75-.LFB2019
	.uleb128 .LEHE75-.LEHB75
	.uleb128 .L232-.LFB2019
	.uleb128 0
	.uleb128 .LEHB76-.LFB2019
	.uleb128 .LEHE76-.LEHB76
	.uleb128 .L238-.LFB2019
	.uleb128 0
	.uleb128 .LEHB77-.LFB2019
	.uleb128 .LEHE77-.LEHB77
	.uleb128 .L239-.LFB2019
	.uleb128 0
	.uleb128 .LEHB78-.LFB2019
	.uleb128 .LEHE78-.LEHB78
	.uleb128 .L240-.LFB2019
	.uleb128 0
	.uleb128 .LEHB79-.LFB2019
	.uleb128 .LEHE79-.LEHB79
	.uleb128 .L241-.LFB2019
	.uleb128 0
	.uleb128 .LEHB80-.LFB2019
	.uleb128 .LEHE80-.LEHB80
	.uleb128 .L242-.LFB2019
	.uleb128 0
	.uleb128 .LEHB81-.LFB2019
	.uleb128 .LEHE81-.LEHB81
	.uleb128 .L243-.LFB2019
	.uleb128 0
	.uleb128 .LEHB82-.LFB2019
	.uleb128 .LEHE82-.LEHB82
	.uleb128 .L244-.LFB2019
	.uleb128 0
	.uleb128 .LEHB83-.LFB2019
	.uleb128 .LEHE83-.LEHB83
	.uleb128 .L245-.LFB2019
	.uleb128 0
	.uleb128 .LEHB84-.LFB2019
	.uleb128 .LEHE84-.LEHB84
	.uleb128 .L247-.LFB2019
	.uleb128 0
	.uleb128 .LEHB85-.LFB2019
	.uleb128 .LEHE85-.LEHB85
	.uleb128 .L248-.LFB2019
	.uleb128 0
	.uleb128 .LEHB86-.LFB2019
	.uleb128 .LEHE86-.LEHB86
	.uleb128 .L246-.LFB2019
	.uleb128 0
	.uleb128 .LEHB87-.LFB2019
	.uleb128 .LEHE87-.LEHB87
	.uleb128 .L249-.LFB2019
	.uleb128 0
	.uleb128 .LEHB88-.LFB2019
	.uleb128 .LEHE88-.LEHB88
	.uleb128 .L250-.LFB2019
	.uleb128 0
	.uleb128 .LEHB89-.LFB2019
	.uleb128 .LEHE89-.LEHB89
	.uleb128 .L251-.LFB2019
	.uleb128 0
	.uleb128 .LEHB90-.LFB2019
	.uleb128 .LEHE90-.LEHB90
	.uleb128 .L252-.LFB2019
	.uleb128 0
	.uleb128 .LEHB91-.LFB2019
	.uleb128 .LEHE91-.LEHB91
	.uleb128 .L253-.LFB2019
	.uleb128 0
	.uleb128 .LEHB92-.LFB2019
	.uleb128 .LEHE92-.LEHB92
	.uleb128 .L254-.LFB2019
	.uleb128 0
	.uleb128 .LEHB93-.LFB2019
	.uleb128 .LEHE93-.LEHB93
	.uleb128 .L255-.LFB2019
	.uleb128 0
	.uleb128 .LEHB94-.LFB2019
	.uleb128 .LEHE94-.LEHB94
	.uleb128 0
	.uleb128 0
.LLSDACSE2019:
	.text
	.size	_ZN13CodeGenerator12generateCodeER8FunctionRK7VMStateRK11Instruction, .-_ZN13CodeGenerator12generateCodeER8FunctionRK7VMStateRK11Instruction
	.section	.text._ZNKSt6vectorIhSaIhEE5beginEv,"axG",@progbits,_ZNKSt6vectorIhSaIhEE5beginEv,comdat
	.align 2
	.weak	_ZNKSt6vectorIhSaIhEE5beginEv
	.type	_ZNKSt6vectorIhSaIhEE5beginEv, @function
_ZNKSt6vectorIhSaIhEE5beginEv:
.LFB2091:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-8], rax
	lea	rdx, [rbp-8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC1ERKS2_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2091:
	.size	_ZNKSt6vectorIhSaIhEE5beginEv, .-_ZNKSt6vectorIhSaIhEE5beginEv
	.section	.text._ZNKSt6vectorIhSaIhEE3endEv,"axG",@progbits,_ZNKSt6vectorIhSaIhEE3endEv,comdat
	.align 2
	.weak	_ZNKSt6vectorIhSaIhEE3endEv
	.type	_ZNKSt6vectorIhSaIhEE3endEv, @function
_ZNKSt6vectorIhSaIhEE3endEv:
.LFB2092:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR [rbp-8], rax
	lea	rdx, [rbp-8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC1ERKS2_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2092:
	.size	_ZNKSt6vectorIhSaIhEE3endEv, .-_ZNKSt6vectorIhSaIhEE3endEv
	.section	.text._ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_,"axG",@progbits,_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_,comdat
	.weak	_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_
	.type	_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_, @function
_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_:
.LFB2093:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv
	mov	rbx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	setne	al
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2093:
	.size	_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_, .-_ZN9__gnu_cxxneIPKhSt6vectorIhSaIhEEEEbRKNS_17__normal_iteratorIT_T0_EESB_
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv
	.type	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv, @function
_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv:
.LFB2094:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2094:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv, .-_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEppEv
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv:
.LFB2095:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2095:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEdeEv
	.section	.text._ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB2097:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2097:
	.size	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNSt6vectorIhSaIhEE9push_backERKh,"axG",@progbits,_ZNSt6vectorIhSaIhEE9push_backERKh,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE9push_backERKh
	.type	_ZNSt6vectorIhSaIhEE9push_backERKh, @function
_ZNSt6vectorIhSaIhEE9push_backERKh:
.LFB2096:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	cmp	rdx, rax
	je	.L271
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	jmp	.L270
.L271:
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_
.L270:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2096:
	.size	_ZNSt6vectorIhSaIhEE9push_backERKh, .-_ZNSt6vectorIhSaIhEE9push_backERKh
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC5Ev,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev:
.LFB2099:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2099:
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC1Ev
	.set	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC1Ev,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEC2Ev
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED5Ev,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev:
.LFB2103:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2103:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED1Ev
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED1Ev,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED2Ev
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED5Ev,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev:
.LFB2105:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2105
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2105:
	.section	.gcc_except_table
.LLSDA2105:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2105-.LLSDACSB2105
.LLSDACSB2105:
.LLSDACSE2105:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED5Ev,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED1Ev
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED1Ev,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EED2Ev
	.section	.text._ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv,"axG",@progbits,_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv,comdat
	.align 2
	.weak	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv
	.type	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv, @function
_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv:
.LFB2107:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2107:
	.size	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv, .-_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE5beginEv
	.section	.text._ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv,"axG",@progbits,_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv,comdat
	.align 2
	.weak	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv
	.type	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv, @function
_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv:
.LFB2108:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2108:
	.size	_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv, .-_ZNSt3mapISs15DefinedFunctionSt4lessISsESaISt4pairIKSsS0_EEE3endEv
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_:
.LFB2109:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rax]
	cmp	rdx, rax
	setne	al
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2109:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEneERKS4_
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv:
.LFB2110:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
	call	_ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2110:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv, .-_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEppEv
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv:
.LFB2111:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2111:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEdeEv
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EEC2Ev,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EEC5Ev,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EEC2Ev
	.type	_ZNSt6vectorI11InstructionSaIS0_EEC2Ev, @function
_ZNSt6vectorI11InstructionSaIS0_EEC2Ev:
.LFB2116:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2116:
	.size	_ZNSt6vectorI11InstructionSaIS0_EEC2Ev, .-_ZNSt6vectorI11InstructionSaIS0_EEC2Ev
	.weak	_ZNSt6vectorI11InstructionSaIS0_EEC1Ev
	.set	_ZNSt6vectorI11InstructionSaIS0_EEC1Ev,_ZNSt6vectorI11InstructionSaIS0_EEC2Ev
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EED2Ev,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EED5Ev,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EED2Ev
	.type	_ZNSt6vectorI11InstructionSaIS0_EED2Ev, @function
_ZNSt6vectorI11InstructionSaIS0_EED2Ev:
.LFB2119:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2119
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2119:
	.section	.gcc_except_table
.LLSDA2119:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2119-.LLSDACSB2119
.LLSDACSB2119:
.LLSDACSE2119:
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EED2Ev,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EED5Ev,comdat
	.size	_ZNSt6vectorI11InstructionSaIS0_EED2Ev, .-_ZNSt6vectorI11InstructionSaIS0_EED2Ev
	.weak	_ZNSt6vectorI11InstructionSaIS0_EED1Ev
	.set	_ZNSt6vectorI11InstructionSaIS0_EED1Ev,_ZNSt6vectorI11InstructionSaIS0_EED2Ev
	.section	.text._ZNSt6vectorIhSaIhEEC2Ev,"axG",@progbits,_ZNSt6vectorIhSaIhEEC5Ev,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEEC2Ev
	.type	_ZNSt6vectorIhSaIhEEC2Ev, @function
_ZNSt6vectorIhSaIhEEC2Ev:
.LFB2122:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEEC2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2122:
	.size	_ZNSt6vectorIhSaIhEEC2Ev, .-_ZNSt6vectorIhSaIhEEC2Ev
	.weak	_ZNSt6vectorIhSaIhEEC1Ev
	.set	_ZNSt6vectorIhSaIhEEC1Ev,_ZNSt6vectorIhSaIhEEC2Ev
	.section	.text._ZNSt6vectorIhSaIhEED2Ev,"axG",@progbits,_ZNSt6vectorIhSaIhEED5Ev,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEED2Ev
	.type	_ZNSt6vectorIhSaIhEED2Ev, @function
_ZNSt6vectorIhSaIhEED2Ev:
.LFB2125:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2125
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2125:
	.section	.gcc_except_table
.LLSDA2125:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2125-.LLSDACSB2125
.LLSDACSB2125:
.LLSDACSE2125:
	.section	.text._ZNSt6vectorIhSaIhEED2Ev,"axG",@progbits,_ZNSt6vectorIhSaIhEED5Ev,comdat
	.size	_ZNSt6vectorIhSaIhEED2Ev, .-_ZNSt6vectorIhSaIhEED2Ev
	.weak	_ZNSt6vectorIhSaIhEED1Ev
	.set	_ZNSt6vectorIhSaIhEED1Ev,_ZNSt6vectorIhSaIhEED2Ev
	.section	.text._ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv,"axG",@progbits,_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv,comdat
	.weak	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv
	.type	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv, @function
_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv:
.LFB2129:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2129:
	.size	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv, .-_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv
	.section	.text._ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv,"axG",@progbits,_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv,comdat
	.weak	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv
	.type	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv, @function
_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv:
.LFB2130:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	eax, 1
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2130:
	.size	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv, .-_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_
	.type	_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_, @function
_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_:
.LFB2128:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 32
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	rax, QWORD PTR [rbp-64]
	cmp	rax, QWORD PTR [rbp-56]
	je	.L299
	call	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE27_S_propagate_on_copy_assignEv
	test	al, al
	je	.L300
	call	_ZN9__gnu_cxx14__alloc_traitsISaI11InstructionEE15_S_always_equalEv
	xor	eax, 1
	test	al, al
	je	.L301
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZStneI11InstructionEbRKSaIT_ES4_
	test	al, al
	je	.L301
	mov	eax, 1
	jmp	.L302
.L301:
	mov	eax, 0
.L302:
	test	al, al
	je	.L303
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE5clearEv
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+16], 0
.L303:
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_
.L300:
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv
	mov	QWORD PTR [rbp-48], rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv
	cmp	rax, QWORD PTR [rbp-48]
	setb	al
	test	al, al
	je	.L304
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE3endEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-48]
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rdx, QWORD PTR [rbp-48]
	sal	rdx, 4
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+16], rdx
	jmp	.L305
.L304:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv
	cmp	rax, QWORD PTR [rbp-48]
	setae	al
	test	al, al
	je	.L306
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE3endEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE5beginEv
	mov	r14, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE3endEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv
	mov	rdx, r14
	mov	rsi, r13
	mov	rdi, rax
	call	_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_
	mov	rdx, r12
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E
	jmp	.L305
.L306:
	mov	rax, QWORD PTR [rbp-56]
	mov	rbx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-64]
	mov	r12, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv
	sal	rax, 4
	lea	rcx, [r12+rax]
	mov	rax, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rax]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	r12, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-64]
	mov	rbx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-64]
	mov	r14, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv
	sal	rax, 4
	add	rax, r14
	mov	rcx, r13
	mov	rdx, r12
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E
.L305:
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rdx, QWORD PTR [rbp-48]
	sal	rdx, 4
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+8], rdx
.L299:
	mov	rax, QWORD PTR [rbp-56]
	add	rsp, 32
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2128:
	.size	_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_, .-_ZNSt6vectorI11InstructionSaIS0_EEaSERKS2_
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv:
.LFB2136:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2136:
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE5beginEv
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv:
.LFB2137:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2137:
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_:
.LFB2138:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rax]
	cmp	rdx, rax
	setne	al
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2138:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEneERKS4_
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv:
.LFB2139:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
	call	_ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2139:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv, .-_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv:
.LFB2140:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2140:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	.section	.text._ZNSt11_Tuple_implILm1EIEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm1EIEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EIEEC2Ev
	.type	_ZNSt11_Tuple_implILm1EIEEC2Ev, @function
_ZNSt11_Tuple_implILm1EIEEC2Ev:
.LFB2145:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2145:
	.size	_ZNSt11_Tuple_implILm1EIEEC2Ev, .-_ZNSt11_Tuple_implILm1EIEEC2Ev
	.weak	_ZNSt11_Tuple_implILm1EJEEC2Ev
	.set	_ZNSt11_Tuple_implILm1EJEEC2Ev,_ZNSt11_Tuple_implILm1EIEEC2Ev
	.weak	_ZNSt11_Tuple_implILm1EIEEC1Ev
	.set	_ZNSt11_Tuple_implILm1EIEEC1Ev,_ZNSt11_Tuple_implILm1EIEEC2Ev
	.weak	_ZNSt11_Tuple_implILm1EJEEC1Ev
	.set	_ZNSt11_Tuple_implILm1EJEEC1Ev,_ZNSt11_Tuple_implILm1EIEEC1Ev
	.section	.text._ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_,"axG",@progbits,_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC5ES3_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_
	.type	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_, @function
_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_:
.LFB2148:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2148:
	.size	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_, .-_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_
	.weak	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC1ES3_
	.set	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC1ES3_,_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_
	.section	.text._ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC5ES3_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_
	.type	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_, @function
_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_:
.LFB2150:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm1EIEEC2Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2150:
	.size	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_, .-_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_
	.weak	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC2ES3_
	.set	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC2ES3_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_
	.weak	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC1ES3_
	.set	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC1ES3_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_
	.weak	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC1ES3_
	.set	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC1ES3_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC1ES3_
	.section	.text._ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_,"axG",@progbits,_ZNSt5tupleIIRKSt4pairISsjEEEC5ES3_,comdat
	.align 2
	.weak	_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_
	.type	_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_, @function
_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_:
.LFB2152:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2ES3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2152:
	.size	_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_, .-_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_
	.weak	_ZNSt5tupleIJRKSt4pairISsjEEEC2ES3_
	.set	_ZNSt5tupleIJRKSt4pairISsjEEEC2ES3_,_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_
	.weak	_ZNSt5tupleIIRKSt4pairISsjEEEC1ES3_
	.set	_ZNSt5tupleIIRKSt4pairISsjEEEC1ES3_,_ZNSt5tupleIIRKSt4pairISsjEEEC2ES3_
	.weak	_ZNSt5tupleIJRKSt4pairISsjEEEC1ES3_
	.set	_ZNSt5tupleIJRKSt4pairISsjEEEC1ES3_,_ZNSt5tupleIIRKSt4pairISsjEEEC1ES3_
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_:
.LFB2141:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2141
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 104
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-120], rdi
	mov	QWORD PTR [rbp-128], rsi
	mov	rdx, QWORD PTR [rbp-128]
	mov	rax, QWORD PTR [rbp-120]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB95:
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_
.LEHE95:
	mov	QWORD PTR [rbp-96], rax
	mov	ebx, 0
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv
	mov	QWORD PTR [rbp-80], rax
	mov	r12d, 1
	lea	rdx, [rbp-80]
	lea	rax, [rbp-96]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_
	test	al, al
	jne	.L323
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
.LEHB96:
	call	_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv
	mov	ebx, 1
	mov	rcx, QWORD PTR [rbp-128]
	lea	rax, [rbp-98]
	mov	rdx, r13
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
.LEHE96:
	test	al, al
	je	.L324
.L323:
	mov	eax, 1
	jmp	.L325
.L324:
	mov	eax, 0
.L325:
	test	bl, bl
	test	r12b, r12b
	test	al, al
	je	.L328
	mov	rdx, QWORD PTR [rbp-128]
	lea	rax, [rbp-64]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIRKSt4pairISsjEEEC1ES3_
	lea	rdx, [rbp-96]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC1ERKSt17_Rb_tree_iteratorIS3_E
	mov	rax, QWORD PTR [rbp-120]
	lea	rcx, [rbp-97]
	lea	rdx, [rbp-64]
	mov	rsi, QWORD PTR [rbp-48]
	mov	r8, rcx
	mov	rcx, rdx
	mov	edx, OFFSET FLAT:_ZStL19piecewise_construct
	mov	rdi, rax
.LEHB97:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
.LEHE97:
	mov	QWORD PTR [rbp-96], rax
.L328:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	add	rax, 16
	jmp	.L338
.L336:
	test	bl, bl
	test	r12b, r12b
	nop
	jmp	.L333
.L337:
	jmp	.L333
.L335:
.L333:
	mov	rdi, rax
.LEHB98:
	call	_Unwind_Resume
.LEHE98:
.L338:
	add	rsp, 104
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2141:
	.section	.gcc_except_table
.LLSDA2141:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2141-.LLSDACSB2141
.LLSDACSB2141:
	.uleb128 .LEHB95-.LFB2141
	.uleb128 .LEHE95-.LEHB95
	.uleb128 .L335-.LFB2141
	.uleb128 0
	.uleb128 .LEHB96-.LFB2141
	.uleb128 .LEHE96-.LEHB96
	.uleb128 .L336-.LFB2141
	.uleb128 0
	.uleb128 .LEHB97-.LFB2141
	.uleb128 .LEHE97-.LEHB97
	.uleb128 .L337-.LFB2141
	.uleb128 0
	.uleb128 .LEHB98-.LFB2141
	.uleb128 .LEHE98-.LEHB98
	.uleb128 0
	.uleb128 0
.LLSDACSE2141:
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_,comdat
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixERS4_
	.section	.text._ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_,"axG",@progbits,_ZNSt10_Head_baseILm0ERKSsLb0EEC5ES1_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_
	.type	_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_, @function
_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_:
.LFB2158:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2158:
	.size	_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_, .-_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_
	.weak	_ZNSt10_Head_baseILm0ERKSsLb0EEC1ES1_
	.set	_ZNSt10_Head_baseILm0ERKSsLb0EEC1ES1_,_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_
	.section	.text._ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSsEEC5ES1_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_
	.type	_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_, @function
_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_:
.LFB2160:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm1EIEEC2Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2160:
	.size	_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_, .-_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_
	.weak	_ZNSt11_Tuple_implILm0EJRKSsEEC2ES1_
	.set	_ZNSt11_Tuple_implILm0EJRKSsEEC2ES1_,_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_
	.weak	_ZNSt11_Tuple_implILm0EIRKSsEEC1ES1_
	.set	_ZNSt11_Tuple_implILm0EIRKSsEEC1ES1_,_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_
	.weak	_ZNSt11_Tuple_implILm0EJRKSsEEC1ES1_
	.set	_ZNSt11_Tuple_implILm0EJRKSsEEC1ES1_,_ZNSt11_Tuple_implILm0EIRKSsEEC1ES1_
	.section	.text._ZNSt5tupleIIRKSsEEC2ES1_,"axG",@progbits,_ZNSt5tupleIIRKSsEEC5ES1_,comdat
	.align 2
	.weak	_ZNSt5tupleIIRKSsEEC2ES1_
	.type	_ZNSt5tupleIIRKSsEEC2ES1_, @function
_ZNSt5tupleIIRKSsEEC2ES1_:
.LFB2162:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSsEEC2ES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2162:
	.size	_ZNSt5tupleIIRKSsEEC2ES1_, .-_ZNSt5tupleIIRKSsEEC2ES1_
	.weak	_ZNSt5tupleIJRKSsEEC2ES1_
	.set	_ZNSt5tupleIJRKSsEEC2ES1_,_ZNSt5tupleIIRKSsEEC2ES1_
	.weak	_ZNSt5tupleIIRKSsEEC1ES1_
	.set	_ZNSt5tupleIIRKSsEEC1ES1_,_ZNSt5tupleIIRKSsEEC2ES1_
	.weak	_ZNSt5tupleIJRKSsEEC1ES1_
	.set	_ZNSt5tupleIJRKSsEEC1ES1_,_ZNSt5tupleIIRKSsEEC1ES1_
	.section	.text._ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_,"axG",@progbits,_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_,comdat
	.align 2
	.weak	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_
	.type	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_, @function
_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_:
.LFB2154:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2154
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 104
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-120], rdi
	mov	QWORD PTR [rbp-128], rsi
	mov	rdx, QWORD PTR [rbp-128]
	mov	rax, QWORD PTR [rbp-120]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB99:
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
.LEHE99:
	mov	QWORD PTR [rbp-96], rax
	mov	ebx, 0
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	mov	QWORD PTR [rbp-80], rax
	mov	r12d, 1
	lea	rdx, [rbp-80]
	lea	rax, [rbp-96]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_
	test	al, al
	jne	.L343
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
.LEHB100:
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv
	mov	ebx, 1
	mov	rcx, QWORD PTR [rbp-128]
	lea	rax, [rbp-98]
	mov	rdx, r13
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE100:
	test	al, al
	je	.L344
.L343:
	mov	eax, 1
	jmp	.L345
.L344:
	mov	eax, 0
.L345:
	test	bl, bl
	test	r12b, r12b
	test	al, al
	je	.L348
	mov	rdx, QWORD PTR [rbp-128]
	lea	rax, [rbp-64]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIRKSsEEC1ES1_
	lea	rdx, [rbp-96]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1ERKSt17_Rb_tree_iteratorIS2_E
	mov	rax, QWORD PTR [rbp-120]
	lea	rcx, [rbp-97]
	lea	rdx, [rbp-64]
	mov	rsi, QWORD PTR [rbp-48]
	mov	r8, rcx
	mov	rcx, rdx
	mov	edx, OFFSET FLAT:_ZStL19piecewise_construct
	mov	rdi, rax
.LEHB101:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
.LEHE101:
	mov	QWORD PTR [rbp-96], rax
.L348:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv
	add	rax, 8
	jmp	.L358
.L356:
	test	bl, bl
	test	r12b, r12b
	nop
	jmp	.L353
.L357:
	jmp	.L353
.L355:
.L353:
	mov	rdi, rax
.LEHB102:
	call	_Unwind_Resume
.LEHE102:
.L358:
	add	rsp, 104
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2154:
	.section	.gcc_except_table
.LLSDA2154:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2154-.LLSDACSB2154
.LLSDACSB2154:
	.uleb128 .LEHB99-.LFB2154
	.uleb128 .LEHE99-.LEHB99
	.uleb128 .L355-.LFB2154
	.uleb128 0
	.uleb128 .LEHB100-.LFB2154
	.uleb128 .LEHE100-.LEHB100
	.uleb128 .L356-.LFB2154
	.uleb128 0
	.uleb128 .LEHB101-.LFB2154
	.uleb128 .LEHE101-.LEHB101
	.uleb128 .L357-.LFB2154
	.uleb128 0
	.uleb128 .LEHB102-.LFB2154
	.uleb128 .LEHE102-.LEHB102
	.uleb128 0
	.uleb128 0
.LLSDACSE2154:
	.section	.text._ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_,"axG",@progbits,_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_,comdat
	.size	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_, .-_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixERS3_
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_,comdat
	.align 2
	.weak	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_
	.type	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_, @function
_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_:
.LFB2164:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2164
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	mov	QWORD PTR [rbp-32], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB103:
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_
.LEHE103:
	mov	QWORD PTR [rbp-16], rax
	lea	rdx, [rbp-32]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_
	test	al, al
	je	.L360
	mov	eax, 0
	jmp	.L365
.L360:
	mov	eax, 1
	jmp	.L365
.L364:
	mov	rdi, rax
.LEHB104:
	call	_Unwind_Resume
.LEHE104:
.L365:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2164:
	.section	.gcc_except_table
.LLSDA2164:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2164-.LLSDACSB2164
.LLSDACSB2164:
	.uleb128 .LEHB103-.LFB2164
	.uleb128 .LEHE103-.LEHB103
	.uleb128 .L364-.LFB2164
	.uleb128 0
	.uleb128 .LEHB104-.LFB2164
	.uleb128 .LEHE104-.LEHB104
	.uleb128 0
	.uleb128 0
.LLSDACSE2164:
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_,comdat
	.size	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_, .-_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE5countERS3_
	.section	.text._ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_,comdat
	.weak	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_
	.type	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_, @function
_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_:
.LFB2165:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2165
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZNSt11char_traitsIcE6lengthEPKc
	mov	QWORD PTR [rbp-24], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
.LEHB105:
	call	_ZNSsC1Ev
.LEHE105:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSs4sizeEv
	mov	rdx, QWORD PTR [rbp-24]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB106:
	call	_ZNSs7reserveEm
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-48]
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSs6appendEPKcm
	mov	rdx, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSs6appendERKSs
.LEHE106:
	jmp	.L370
.L369:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB107:
	call	_Unwind_Resume
.LEHE107:
.L370:
	mov	rax, QWORD PTR [rbp-40]
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2165:
	.section	.gcc_except_table
.LLSDA2165:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2165-.LLSDACSB2165
.LLSDACSB2165:
	.uleb128 .LEHB105-.LFB2165
	.uleb128 .LEHE105-.LEHB105
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB106-.LFB2165
	.uleb128 .LEHE106-.LEHB106
	.uleb128 .L369-.LFB2165
	.uleb128 0
	.uleb128 .LEHB107-.LFB2165
	.uleb128 .LEHE107-.LEHB107
	.uleb128 0
	.uleb128 0
.LLSDACSE2165:
	.section	.text._ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_,comdat
	.size	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_, .-_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_
	.section	.text._ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_,"axG",@progbits,_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_,comdat
	.weak	_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_
	.type	_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_, @function
_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_:
.LFB2167:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2167:
	.size	_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_, .-_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_
	.section	.text._ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_,comdat
	.weak	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_
	.type	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_, @function
_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_:
.LFB2166:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSs6appendEPKc
	mov	rdi, rax
	call	_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1EOSs
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2166:
	.size	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_, .-_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EOS6_PKS3_
	.section	.text._ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs,"axG",@progbits,_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs,comdat
	.align 2
	.weak	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs
	.type	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs, @function
_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs:
.LFB2174:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2174
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 104
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-120], rdi
	mov	QWORD PTR [rbp-128], rsi
	mov	rdx, QWORD PTR [rbp-128]
	mov	rax, QWORD PTR [rbp-120]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB108:
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
.LEHE108:
	mov	QWORD PTR [rbp-96], rax
	mov	ebx, 0
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
	call	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	mov	QWORD PTR [rbp-80], rax
	mov	r12d, 1
	lea	rdx, [rbp-80]
	lea	rax, [rbp-96]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_
	test	al, al
	jne	.L376
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
.LEHB109:
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv
	mov	ebx, 1
	mov	rcx, QWORD PTR [rbp-128]
	lea	rax, [rbp-98]
	mov	rdx, r13
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE109:
	test	al, al
	je	.L377
.L376:
	mov	eax, 1
	jmp	.L378
.L377:
	mov	eax, 0
.L378:
	test	bl, bl
	test	r12b, r12b
	test	al, al
	je	.L381
	mov	rax, QWORD PTR [rbp-128]
	mov	rdi, rax
	call	_ZSt4moveIRSsEONSt16remove_referenceIT_E4typeEOS2_
	mov	rdx, rax
	lea	rax, [rbp-64]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_
	lea	rdx, [rbp-96]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1ERKSt17_Rb_tree_iteratorIS2_E
	mov	rax, QWORD PTR [rbp-120]
	lea	rcx, [rbp-97]
	lea	rdx, [rbp-64]
	mov	rsi, QWORD PTR [rbp-48]
	mov	r8, rcx
	mov	rcx, rdx
	mov	edx, OFFSET FLAT:_ZStL19piecewise_construct
	mov	rdi, rax
.LEHB110:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
.LEHE110:
	mov	QWORD PTR [rbp-96], rax
.L381:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv
	add	rax, 8
	jmp	.L391
.L389:
	test	bl, bl
	test	r12b, r12b
	nop
	jmp	.L386
.L390:
	jmp	.L386
.L388:
.L386:
	mov	rdi, rax
.LEHB111:
	call	_Unwind_Resume
.LEHE111:
.L391:
	add	rsp, 104
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2174:
	.section	.gcc_except_table
.LLSDA2174:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2174-.LLSDACSB2174
.LLSDACSB2174:
	.uleb128 .LEHB108-.LFB2174
	.uleb128 .LEHE108-.LEHB108
	.uleb128 .L388-.LFB2174
	.uleb128 0
	.uleb128 .LEHB109-.LFB2174
	.uleb128 .LEHE109-.LEHB109
	.uleb128 .L389-.LFB2174
	.uleb128 0
	.uleb128 .LEHB110-.LFB2174
	.uleb128 .LEHE110-.LEHB110
	.uleb128 .L390-.LFB2174
	.uleb128 0
	.uleb128 .LEHB111-.LFB2174
	.uleb128 .LEHE111-.LEHB111
	.uleb128 0
	.uleb128 0
.LLSDACSE2174:
	.section	.text._ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs,"axG",@progbits,_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs,comdat
	.size	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs, .-_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEEixEOSs
	.section	.text._ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_,"axG",@progbits,_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_,comdat
	.weak	_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_
	.type	_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_, @function
_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_:
.LFB2176:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2176:
	.size	_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_, .-_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_
	.section	.text._ZNSt6vectorIhSaIhEE9push_backEOh,"axG",@progbits,_ZNSt6vectorIhSaIhEE9push_backEOh,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE9push_backEOh
	.type	_ZNSt6vectorIhSaIhEE9push_backEOh, @function
_ZNSt6vectorIhSaIhEE9push_backEOh:
.LFB2175:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt4moveIRhEONSt16remove_referenceIT_E4typeEOS2_
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2175:
	.size	_ZNSt6vectorIhSaIhEE9push_backEOh, .-_ZNSt6vectorIhSaIhEE9push_backEOh
	.section	.text._ZNSaIhEC2Ev,"axG",@progbits,_ZNSaIhEC5Ev,comdat
	.align 2
	.weak	_ZNSaIhEC2Ev
	.type	_ZNSaIhEC2Ev, @function
_ZNSaIhEC2Ev:
.LFB2178:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhEC2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2178:
	.size	_ZNSaIhEC2Ev, .-_ZNSaIhEC2Ev
	.weak	_ZNSaIhEC1Ev
	.set	_ZNSaIhEC1Ev,_ZNSaIhEC2Ev
	.section	.text._ZNSaIhED2Ev,"axG",@progbits,_ZNSaIhED5Ev,comdat
	.align 2
	.weak	_ZNSaIhED2Ev
	.type	_ZNSaIhED2Ev, @function
_ZNSaIhED2Ev:
.LFB2181:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2181:
	.size	_ZNSaIhED2Ev, .-_ZNSaIhED2Ev
	.weak	_ZNSaIhED1Ev
	.set	_ZNSaIhED1Ev,_ZNSaIhED2Ev
	.section	.text._ZNKSt16initializer_listIhE5beginEv,"axG",@progbits,_ZNKSt16initializer_listIhE5beginEv,comdat
	.align 2
	.weak	_ZNKSt16initializer_listIhE5beginEv
	.type	_ZNKSt16initializer_listIhE5beginEv, @function
_ZNKSt16initializer_listIhE5beginEv:
.LFB2184:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2184:
	.size	_ZNKSt16initializer_listIhE5beginEv, .-_ZNKSt16initializer_listIhE5beginEv
	.section	.text._ZNKSt16initializer_listIhE4sizeEv,"axG",@progbits,_ZNKSt16initializer_listIhE4sizeEv,comdat
	.align 2
	.weak	_ZNKSt16initializer_listIhE4sizeEv
	.type	_ZNKSt16initializer_listIhE4sizeEv, @function
_ZNKSt16initializer_listIhE4sizeEv:
.LFB2186:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2186:
	.size	_ZNKSt16initializer_listIhE4sizeEv, .-_ZNKSt16initializer_listIhE4sizeEv
	.section	.text._ZNKSt16initializer_listIhE3endEv,"axG",@progbits,_ZNKSt16initializer_listIhE3endEv,comdat
	.align 2
	.weak	_ZNKSt16initializer_listIhE3endEv
	.type	_ZNKSt16initializer_listIhE3endEv, @function
_ZNKSt16initializer_listIhE3endEv:
.LFB2185:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNKSt16initializer_listIhE5beginEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNKSt16initializer_listIhE4sizeEv
	add	rax, rbx
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2185:
	.size	_ZNKSt16initializer_listIhE3endEv, .-_ZNKSt16initializer_listIhE3endEv
	.section	.text._ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_,"axG",@progbits,_ZNSt6vectorIhSaIhEEC5ESt16initializer_listIhERKS0_,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_
	.type	_ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_, @function
_ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_:
.LFB2187:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2187
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 64
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-40], rdi
	mov	rax, rsi
	mov	rsi, rdx
	mov	rdx, rsi
	mov	QWORD PTR [rbp-64], rax
	mov	QWORD PTR [rbp-56], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB112:
	call	_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_
.LEHE112:
	lea	rax, [rbp-64]
	mov	rdi, rax
	call	_ZNKSt16initializer_listIhE3endEv
	mov	rbx, rax
	lea	rax, [rbp-64]
	mov	rdi, rax
	call	_ZNKSt16initializer_listIhE5beginEv
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	BYTE PTR [rsp], r12b
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
.LEHB113:
	call	_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag
.LEHE113:
	jmp	.L407
.L406:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEED2Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB114:
	call	_Unwind_Resume
.LEHE114:
.L407:
	add	rsp, 64
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2187:
	.section	.gcc_except_table
.LLSDA2187:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2187-.LLSDACSB2187
.LLSDACSB2187:
	.uleb128 .LEHB112-.LFB2187
	.uleb128 .LEHE112-.LEHB112
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB113-.LFB2187
	.uleb128 .LEHE113-.LEHB113
	.uleb128 .L406-.LFB2187
	.uleb128 0
	.uleb128 .LEHB114-.LFB2187
	.uleb128 .LEHE114-.LEHB114
	.uleb128 0
	.uleb128 0
.LLSDACSE2187:
	.section	.text._ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_,"axG",@progbits,_ZNSt6vectorIhSaIhEEC5ESt16initializer_listIhERKS0_,comdat
	.size	_ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_, .-_ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_
	.weak	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_
	.set	_ZNSt6vectorIhSaIhEEC1ESt16initializer_listIhERKS0_,_ZNSt6vectorIhSaIhEEC2ESt16initializer_listIhERKS0_
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE5beginEv,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE5beginEv,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EE5beginEv
	.type	_ZNSt6vectorI11InstructionSaIS0_EE5beginEv, @function
_ZNSt6vectorI11InstructionSaIS0_EE5beginEv:
.LFB2189:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rdx, QWORD PTR [rbp-24]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS2_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2189:
	.size	_ZNSt6vectorI11InstructionSaIS0_EE5beginEv, .-_ZNSt6vectorI11InstructionSaIS0_EE5beginEv
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE3endEv,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE3endEv,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EE3endEv
	.type	_ZNSt6vectorI11InstructionSaIS0_EE3endEv, @function
_ZNSt6vectorI11InstructionSaIS0_EE3endEv:
.LFB2190:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	lea	rdx, [rax+8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS2_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2190:
	.size	_ZNSt6vectorI11InstructionSaIS0_EE3endEv, .-_ZNSt6vectorI11InstructionSaIS0_EE3endEv
	.section	.text._ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_,"axG",@progbits,_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_,comdat
	.weak	_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_
	.type	_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_, @function
_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_:
.LFB2191:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	mov	rbx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	setne	al
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2191:
	.size	_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_, .-_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv
	.type	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv, @function
_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv:
.LFB2192:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	lea	rdx, [rax+16]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2192:
	.size	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv, .-_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv:
.LFB2193:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2193:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv, .-_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	.section	.text._ZNSt6vectorIhSaIhEE4dataEv,"axG",@progbits,_ZNSt6vectorIhSaIhEE4dataEv,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE4dataEv
	.type	_ZNSt6vectorIhSaIhEE4dataEv, @function
_ZNSt6vectorIhSaIhEE4dataEv:
.LFB2194:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2194
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE5frontEv
	mov	rdi, rax
	call	_ZSt11__addressofIhEPT_RS0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2194:
	.section	.gcc_except_table
.LLSDA2194:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2194-.LLSDACSB2194
.LLSDACSB2194:
.LLSDACSE2194:
	.section	.text._ZNSt6vectorIhSaIhEE4dataEv,"axG",@progbits,_ZNSt6vectorIhSaIhEE4dataEv,comdat
	.size	_ZNSt6vectorIhSaIhEE4dataEv, .-_ZNSt6vectorIhSaIhEE4dataEv
	.section	.text._ZNKSt6vectorIhSaIhEE4sizeEv,"axG",@progbits,_ZNKSt6vectorIhSaIhEE4sizeEv,comdat
	.align 2
	.weak	_ZNKSt6vectorIhSaIhEE4sizeEv
	.type	_ZNKSt6vectorIhSaIhEE4sizeEv, @function
_ZNKSt6vectorIhSaIhEE4sizeEv:
.LFB2195:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2195:
	.size	_ZNKSt6vectorIhSaIhEE4sizeEv, .-_ZNKSt6vectorIhSaIhEE4sizeEv
	.section	.rodata
.LC8:
	.string	"map::at"
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_,comdat
	.align 2
	.weak	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_
	.type	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_, @function
_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_:
.LFB2196:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2196
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 72
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-88], rdi
	mov	QWORD PTR [rbp-96], rsi
	mov	rdx, QWORD PTR [rbp-96]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB115:
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
.LEHE115:
	mov	QWORD PTR [rbp-64], rax
	mov	ebx, 0
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	mov	QWORD PTR [rbp-48], rax
	mov	r12d, 1
	lea	rdx, [rbp-48]
	lea	rax, [rbp-64]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_
	test	al, al
	jne	.L423
	lea	rax, [rbp-64]
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
.LEHB116:
	call	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv
	mov	ebx, 1
	mov	rcx, QWORD PTR [rbp-96]
	lea	rax, [rbp-65]
	mov	rdx, r13
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE116:
	test	al, al
	je	.L424
.L423:
	mov	eax, 1
	jmp	.L425
.L424:
	mov	eax, 0
.L425:
	test	bl, bl
	test	r12b, r12b
	test	al, al
	je	.L428
	mov	edi, OFFSET FLAT:.LC8
.LEHB117:
	call	_ZSt20__throw_out_of_rangePKc
.LEHE117:
.L428:
	lea	rax, [rbp-64]
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv
	add	rax, 8
	jmp	.L436
.L435:
	test	bl, bl
	test	r12b, r12b
	nop
	jmp	.L433
.L434:
.L433:
	mov	rdi, rax
.LEHB118:
	call	_Unwind_Resume
.LEHE118:
.L436:
	add	rsp, 72
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2196:
	.section	.gcc_except_table
.LLSDA2196:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2196-.LLSDACSB2196
.LLSDACSB2196:
	.uleb128 .LEHB115-.LFB2196
	.uleb128 .LEHE115-.LEHB115
	.uleb128 .L434-.LFB2196
	.uleb128 0
	.uleb128 .LEHB116-.LFB2196
	.uleb128 .LEHE116-.LEHB116
	.uleb128 .L435-.LFB2196
	.uleb128 0
	.uleb128 .LEHB117-.LFB2196
	.uleb128 .LEHE117-.LEHB117
	.uleb128 .L434-.LFB2196
	.uleb128 0
	.uleb128 .LEHB118-.LFB2196
	.uleb128 .LEHE118-.LEHB118
	.uleb128 0
	.uleb128 0
.LLSDACSE2196:
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_,comdat
	.size	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_, .-_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE2atERS3_
	.section	.text._ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_,"axG",@progbits,_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_,comdat
	.weak	_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_
	.type	_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_, @function
_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_:
.LFB2198:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2198:
	.size	_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_, .-_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_:
.LFB2197:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2197
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 104
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-120], rdi
	mov	QWORD PTR [rbp-128], rsi
	mov	rdx, QWORD PTR [rbp-128]
	mov	rax, QWORD PTR [rbp-120]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB119:
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_
.LEHE119:
	mov	QWORD PTR [rbp-96], rax
	mov	ebx, 0
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
	call	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE3endEv
	mov	QWORD PTR [rbp-80], rax
	mov	r12d, 1
	lea	rdx, [rbp-80]
	lea	rax, [rbp-96]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_
	test	al, al
	jne	.L440
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-120]
	mov	rdi, rax
.LEHB120:
	call	_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv
	mov	ebx, 1
	mov	rcx, QWORD PTR [rbp-128]
	lea	rax, [rbp-98]
	mov	rdx, r13
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
.LEHE120:
	test	al, al
	je	.L441
.L440:
	mov	eax, 1
	jmp	.L442
.L441:
	mov	eax, 0
.L442:
	test	bl, bl
	test	r12b, r12b
	test	al, al
	je	.L445
	mov	rax, QWORD PTR [rbp-128]
	mov	rdi, rax
	call	_ZSt4moveIRSt4pairISsjEEONSt16remove_referenceIT_E4typeEOS4_
	mov	rdx, rax
	lea	rax, [rbp-64]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_
	lea	rdx, [rbp-96]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC1ERKSt17_Rb_tree_iteratorIS3_E
	mov	rax, QWORD PTR [rbp-120]
	lea	rcx, [rbp-97]
	lea	rdx, [rbp-64]
	mov	rsi, QWORD PTR [rbp-48]
	mov	r8, rcx
	mov	rcx, rdx
	mov	edx, OFFSET FLAT:_ZStL19piecewise_construct
	mov	rdi, rax
.LEHB121:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
.LEHE121:
	mov	QWORD PTR [rbp-96], rax
.L445:
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEdeEv
	add	rax, 16
	jmp	.L455
.L453:
	test	bl, bl
	test	r12b, r12b
	nop
	jmp	.L450
.L454:
	jmp	.L450
.L452:
.L450:
	mov	rdi, rax
.LEHB122:
	call	_Unwind_Resume
.LEHE122:
.L455:
	add	rsp, 104
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2197:
	.section	.gcc_except_table
.LLSDA2197:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2197-.LLSDACSB2197
.LLSDACSB2197:
	.uleb128 .LEHB119-.LFB2197
	.uleb128 .LEHE119-.LEHB119
	.uleb128 .L452-.LFB2197
	.uleb128 0
	.uleb128 .LEHB120-.LFB2197
	.uleb128 .LEHE120-.LEHB120
	.uleb128 .L453-.LFB2197
	.uleb128 0
	.uleb128 .LEHB121-.LFB2197
	.uleb128 .LEHE121-.LEHB121
	.uleb128 .L454-.LFB2197
	.uleb128 0
	.uleb128 .LEHB122-.LFB2197
	.uleb128 .LEHE122-.LEHB122
	.uleb128 0
	.uleb128 0
.LLSDACSE2197:
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_,comdat
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEEixEOS1_
	.section	.text._ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_,comdat
	.weak	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_
	.type	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_, @function
_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_:
.LFB2199:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2199
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB123:
	call	_ZNSsC1ERKSs
.LEHE123:
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB124:
	call	_ZNSs6appendEPKc
.LEHE124:
	jmp	.L460
.L459:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSsD1Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB125:
	call	_Unwind_Resume
.LEHE125:
.L460:
	mov	rax, QWORD PTR [rbp-24]
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2199:
	.section	.gcc_except_table
.LLSDA2199:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2199-.LLSDACSB2199
.LLSDACSB2199:
	.uleb128 .LEHB123-.LFB2199
	.uleb128 .LEHE123-.LEHB123
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB124-.LFB2199
	.uleb128 .LEHE124-.LEHB124
	.uleb128 .L459-.LFB2199
	.uleb128 0
	.uleb128 .LEHB125-.LFB2199
	.uleb128 .LEHE125-.LEHB125
	.uleb128 0
	.uleb128 0
.LLSDACSE2199:
	.section	.text._ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_,comdat
	.size	_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_, .-_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_PKS3_
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC5ERKS2_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_
	.type	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_, @function
_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_:
.LFB2239:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2239:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_, .-_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC1ERKS2_
	.set	_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC1ERKS2_,_ZN9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEEC2ERKS2_
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv:
.LFB2241:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2241:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPKhSt6vectorIhSaIhEEE4baseEv
	.section	.text._ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_
	.type	_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_, @function
_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_:
.LFB2242:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2242:
	.size	_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_, .-_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_
	.weak	_ZNSt16allocator_traitsISaIhEE9constructIhJRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_
	.set	_ZNSt16allocator_traitsISaIhEE9constructIhJRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_,_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_
	.section	.rodata
.LC9:
	.string	"vector::_M_emplace_back_aux"
	.section	.text._ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_,"axG",@progbits,_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_
	.type	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_, @function
_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_:
.LFB2243:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2243
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	rax, QWORD PTR [rbp-56]
	mov	edx, OFFSET FLAT:.LC9
	mov	esi, 1
	mov	rdi, rax
.LEHB126:
	call	_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc
	mov	QWORD PTR [rbp-32], rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm
.LEHE126:
	mov	QWORD PTR [rbp-24], rax
	mov	rax, QWORD PTR [rbp-24]
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	rdx, QWORD PTR [rbp-24]
	lea	rcx, [rax+rdx]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
.LEHB127:
	call	_ZNSt16allocator_traitsISaIhEE9constructIhIRKhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS5_
	mov	QWORD PTR [rbp-40], 0
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rdx, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_
.LEHE127:
	mov	QWORD PTR [rbp-40], rax
	add	QWORD PTR [rbp-40], 1
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rsi, rcx
	mov	rdi, rax
.LEHB128:
	call	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
.LEHE128:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-24]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], rdx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+16], rdx
	jmp	.L472
.L471:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB129:
	call	_Unwind_Resume
.LEHE129:
.L470:
	mov	rdi, rax
	call	__cxa_begin_catch
	cmp	QWORD PTR [rbp-40], 0
	jne	.L468
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	rdx, QWORD PTR [rbp-24]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB130:
	call	_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_
	jmp	.L469
.L468:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
.L469:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-32]
	mov	rcx, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
	call	__cxa_rethrow
.LEHE130:
.L472:
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2243:
	.section	.gcc_except_table
	.align 4
.LLSDA2243:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2243-.LLSDATTD2243
.LLSDATTD2243:
	.byte	0x1
	.uleb128 .LLSDACSE2243-.LLSDACSB2243
.LLSDACSB2243:
	.uleb128 .LEHB126-.LFB2243
	.uleb128 .LEHE126-.LEHB126
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB127-.LFB2243
	.uleb128 .LEHE127-.LEHB127
	.uleb128 .L470-.LFB2243
	.uleb128 0x1
	.uleb128 .LEHB128-.LFB2243
	.uleb128 .LEHE128-.LEHB128
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB129-.LFB2243
	.uleb128 .LEHE129-.LEHB129
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB130-.LFB2243
	.uleb128 .LEHE130-.LEHB130
	.uleb128 .L471-.LFB2243
	.uleb128 0
.LLSDACSE2243:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2243:
	.section	.text._ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_,"axG",@progbits,_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_,comdat
	.size	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_, .-_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_
	.weak	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIJRKhEEEvDpOT_
	.set	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIJRKhEEEvDpOT_,_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIRKhEEEvDpOT_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC5Ev,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev:
.LFB2245:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2245:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC1Ev
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC1Ev,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EEC2Ev
	.section	.text._ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev,"axG",@progbits,_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED5Ev,comdat
	.align 2
	.weak	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev
	.type	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev, @function
_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev:
.LFB2248:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2248:
	.size	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev, .-_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev
	.weak	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED1Ev
	.set	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED1Ev,_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEED2Ev
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E:
.LFB2250:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	jmp	.L477
.L478:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-8], rax
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rbp-32], rax
.L477:
	cmp	QWORD PTR [rbp-32], 0
	jne	.L478
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2250:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_eraseEPSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv:
.LFB2251:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2251:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv:
.LFB2252:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+24]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2252:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv, .-_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE5beginEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv:
.LFB2253:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	lea	rdx, [rax+8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2253:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv, .-_ZNSt8_Rb_treeISsSt4pairIKSs15DefinedFunctionESt10_Select1stIS3_ESt4lessISsESaIS3_EE3endEv
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev:
.LFB2259:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSaI11InstructionED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2259:
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD1Ev
	.set	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD1Ev,_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD2Ev
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EEC5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev:
.LFB2261:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2261:
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EEC1Ev
	.set	_ZNSt12_Vector_baseI11InstructionSaIS0_EEC1Ev,_ZNSt12_Vector_baseI11InstructionSaIS0_EEC2Ev
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EED5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev:
.LFB2264:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2264
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2264:
	.section	.gcc_except_table
.LLSDA2264:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2264-.LLSDACSB2264
.LLSDACSB2264:
.LLSDACSE2264:
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EED5Ev,comdat
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EED1Ev
	.set	_ZNSt12_Vector_baseI11InstructionSaIS0_EED1Ev,_ZNSt12_Vector_baseI11InstructionSaIS0_EED2Ev
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv:
.LFB2266:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2266:
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	.section	.text._ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E,"axG",@progbits,_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E,comdat
	.weak	_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E
	.type	_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E, @function
_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E:
.LFB2267:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt8_DestroyIP11InstructionEvT_S2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2267:
	.size	_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E, .-_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E
	.section	.text._ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev
	.type	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev, @function
_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev:
.LFB2270:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSaIhED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2270:
	.size	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev, .-_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev
	.weak	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD1Ev
	.set	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD1Ev,_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD2Ev
	.section	.text._ZNSt12_Vector_baseIhSaIhEEC2Ev,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEEC5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEEC2Ev
	.type	_ZNSt12_Vector_baseIhSaIhEEC2Ev, @function
_ZNSt12_Vector_baseIhSaIhEEC2Ev:
.LFB2272:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2272:
	.size	_ZNSt12_Vector_baseIhSaIhEEC2Ev, .-_ZNSt12_Vector_baseIhSaIhEEC2Ev
	.weak	_ZNSt12_Vector_baseIhSaIhEEC1Ev
	.set	_ZNSt12_Vector_baseIhSaIhEEC1Ev,_ZNSt12_Vector_baseIhSaIhEEC2Ev
	.section	.text._ZNSt12_Vector_baseIhSaIhEED2Ev,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEED5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEED2Ev
	.type	_ZNSt12_Vector_baseIhSaIhEED2Ev, @function
_ZNSt12_Vector_baseIhSaIhEED2Ev:
.LFB2275:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2275
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2275:
	.section	.gcc_except_table
.LLSDA2275:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2275-.LLSDACSB2275
.LLSDACSB2275:
.LLSDACSE2275:
	.section	.text._ZNSt12_Vector_baseIhSaIhEED2Ev,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEED5Ev,comdat
	.size	_ZNSt12_Vector_baseIhSaIhEED2Ev, .-_ZNSt12_Vector_baseIhSaIhEED2Ev
	.weak	_ZNSt12_Vector_baseIhSaIhEED1Ev
	.set	_ZNSt12_Vector_baseIhSaIhEED1Ev,_ZNSt12_Vector_baseIhSaIhEED2Ev
	.section	.text._ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	.type	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv, @function
_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv:
.LFB2277:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2277:
	.size	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv, .-_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	.section	.text._ZSt8_DestroyIPhhEvT_S1_RSaIT0_E,"axG",@progbits,_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E,comdat
	.weak	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
	.type	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E, @function
_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E:
.LFB2278:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt8_DestroyIPhEvT_S1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2278:
	.size	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E, .-_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
	.section	.text._ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv,"axG",@progbits,_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv,comdat
	.align 2
	.weak	_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	.type	_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv, @function
_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv:
.LFB2279:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2279:
	.size	_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv, .-_ZNKSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	.section	.text._ZStneI11InstructionEbRKSaIT_ES4_,"axG",@progbits,_ZStneI11InstructionEbRKSaIT_ES4_,comdat
	.weak	_ZStneI11InstructionEbRKSaIT_ES4_
	.type	_ZStneI11InstructionEbRKSaIT_ES4_, @function
_ZStneI11InstructionEbRKSaIT_ES4_:
.LFB2280:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2280:
	.size	_ZStneI11InstructionEbRKSaIT_ES4_, .-_ZStneI11InstructionEbRKSaIT_ES4_
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE5clearEv,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE5clearEv,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EE5clearEv
	.type	_ZNSt6vectorI11InstructionSaIS0_EE5clearEv, @function
_ZNSt6vectorI11InstructionSaIS0_EE5clearEv:
.LFB2281:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2281
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2281:
	.section	.gcc_except_table
.LLSDA2281:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2281-.LLSDACSB2281
.LLSDACSB2281:
.LLSDACSE2281:
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE5clearEv,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE5clearEv,comdat
	.size	_ZNSt6vectorI11InstructionSaIS0_EE5clearEv, .-_ZNSt6vectorI11InstructionSaIS0_EE5clearEv
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m:
.LFB2282:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	cmp	QWORD PTR [rbp-16], 0
	je	.L506
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m
.L506:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2282:
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m
	.section	.text._ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_,"axG",@progbits,_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_,comdat
	.weak	_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_
	.type	_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_, @function
_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_:
.LFB2283:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	BYTE PTR [rsp], cl
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2283:
	.size	_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_, .-_ZSt15__alloc_on_copyISaI11InstructionEEvRT_RKS2_
	.section	.text._ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv,"axG",@progbits,_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv,comdat
	.align 2
	.weak	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv
	.type	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv, @function
_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv:
.LFB2284:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2284:
	.size	_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv, .-_ZNKSt6vectorI11InstructionSaIS0_EE4sizeEv
	.section	.text._ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv,"axG",@progbits,_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv,comdat
	.align 2
	.weak	_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv
	.type	_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv, @function
_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv:
.LFB2285:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2285:
	.size	_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv, .-_ZNKSt6vectorI11InstructionSaIS0_EE8capacityEv
	.section	.text._ZNKSt6vectorI11InstructionSaIS0_EE5beginEv,"axG",@progbits,_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv,comdat
	.align 2
	.weak	_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv
	.type	_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv, @function
_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv:
.LFB2286:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-8], rax
	lea	rdx, [rbp-8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS3_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2286:
	.size	_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv, .-_ZNKSt6vectorI11InstructionSaIS0_EE5beginEv
	.section	.text._ZNKSt6vectorI11InstructionSaIS0_EE3endEv,"axG",@progbits,_ZNKSt6vectorI11InstructionSaIS0_EE3endEv,comdat
	.align 2
	.weak	_ZNKSt6vectorI11InstructionSaIS0_EE3endEv
	.type	_ZNKSt6vectorI11InstructionSaIS0_EE3endEv, @function
_ZNKSt6vectorI11InstructionSaIS0_EE3endEv:
.LFB2287:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR [rbp-8], rax
	lea	rdx, [rbp-8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS3_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2287:
	.size	_ZNKSt6vectorI11InstructionSaIS0_EE3endEv, .-_ZNKSt6vectorI11InstructionSaIS0_EE3endEv
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_
	.type	_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_, @function
_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_:
.LFB2288:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2288
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 72
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-64], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB131:
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm
.LEHE131:
	mov	QWORD PTR [rbp-24], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rcx, rax
	mov	rdx, QWORD PTR [rbp-24]
	mov	rsi, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
.LEHB132:
	call	_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E
.LEHE132:
	mov	rax, QWORD PTR [rbp-24]
	jmp	.L523
.L522:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB133:
	call	_Unwind_Resume
.LEHE133:
.L521:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rcx, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE13_M_deallocateEPS0_m
.LEHB134:
	call	__cxa_rethrow
.LEHE134:
.L523:
	add	rsp, 72
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2288:
	.section	.gcc_except_table
	.align 4
.LLSDA2288:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2288-.LLSDATTD2288
.LLSDATTD2288:
	.byte	0x1
	.uleb128 .LLSDACSE2288-.LLSDACSB2288
.LLSDACSB2288:
	.uleb128 .LEHB131-.LFB2288
	.uleb128 .LEHE131-.LEHB131
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB132-.LFB2288
	.uleb128 .LEHE132-.LEHB132
	.uleb128 .L521-.LFB2288
	.uleb128 0x1
	.uleb128 .LEHB133-.LFB2288
	.uleb128 .LEHE133-.LEHB133
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB134-.LFB2288
	.uleb128 .LEHE134-.LEHB134
	.uleb128 .L522-.LFB2288
	.uleb128 0
.LLSDACSE2288:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2288:
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_,comdat
	.size	_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_, .-_ZNSt6vectorI11InstructionSaIS0_EE20_M_allocate_and_copyIN9__gnu_cxx17__normal_iteratorIPKS0_S2_EEEEPS0_mT_SA_
	.section	.text._ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_,"axG",@progbits,_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_,comdat
	.weak	_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_
	.type	_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_, @function
_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_:
.LFB2289:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-32], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-64], rdx
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_
	mov	rdx, QWORD PTR [rbp-64]
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2289:
	.size	_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_, .-_ZSt4copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET0_T_SC_SB_
	.section	.text._ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E,"axG",@progbits,_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E,comdat
	.weak	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E
	.type	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E, @function
_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E:
.LFB2290:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2290:
	.size	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E, .-_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEES2_EvT_S8_RSaIT0_E
	.section	.text._ZSt4copyIP11InstructionS1_ET0_T_S3_S2_,"axG",@progbits,_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_,comdat
	.weak	_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_
	.type	_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_, @function
_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_:
.LFB2291:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_
	mov	rdx, QWORD PTR [rbp-40]
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2291:
	.size	_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_, .-_ZSt4copyIP11InstructionS1_ET0_T_S3_S2_
	.section	.text._ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E,"axG",@progbits,_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E,comdat
	.weak	_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E
	.type	_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E, @function
_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E:
.LFB2292:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	QWORD PTR [rbp-32], rcx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2292:
	.size	_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E, .-_ZSt22__uninitialized_copy_aIP11InstructionS1_S0_ET0_T_S3_S2_RSaIT1_E
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv:
.LFB2297:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+24]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2297:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv:
.LFB2298:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	lea	rdx, [rax+8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2298:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE3endEv
	.section	.text._ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_,"axG",@progbits,_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_,comdat
	.align 2
	.weak	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_
	.type	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_, @function
_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_:
.LFB2299:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2299:
	.size	_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_, .-_ZNSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE11lower_boundERS4_
	.section	.text._ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv,"axG",@progbits,_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv,comdat
	.align 2
	.weak	_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv
	.type	_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv, @function
_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv:
.LFB2300:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv
	mov	eax, ebx
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2300:
	.size	_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv, .-_ZNKSt3mapISt4pairISsjESsSt4lessIS1_ESaIS0_IKS1_SsEEE8key_compEv
	.section	.text._ZStltISsjEbRKSt4pairIT_T0_ES5_,"axG",@progbits,_ZStltISsjEbRKSt4pairIT_T0_ES5_,comdat
	.weak	_ZStltISsjEbRKSt4pairIT_T0_ES5_
	.type	_ZStltISsjEbRKSt4pairIT_T0_ES5_, @function
_ZStltISsjEbRKSt4pairIT_T0_ES5_:
.LFB2302:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_
	test	al, al
	jne	.L540
	mov	rdx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_
	xor	eax, 1
	test	al, al
	je	.L541
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, DWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-16]
	mov	eax, DWORD PTR [rax+8]
	cmp	edx, eax
	jae	.L541
.L540:
	mov	eax, 1
	jmp	.L542
.L541:
	mov	eax, 0
.L542:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2302:
	.size	_ZStltISsjEbRKSt4pairIT_T0_ES5_, .-_ZStltISsjEbRKSt4pairIT_T0_ES5_
	.section	.text._ZNKSt4lessISt4pairISsjEEclERKS1_S4_,"axG",@progbits,_ZNKSt4lessISt4pairISsjEEclERKS1_S4_,comdat
	.align 2
	.weak	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	.type	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_, @function
_ZNKSt4lessISt4pairISsjEEclERKS1_S4_:
.LFB2301:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZStltISsjEbRKSt4pairIT_T0_ES5_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2301:
	.size	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_, .-_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_:
.LFB2303:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rax]
	cmp	rdx, rax
	sete	al
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2303:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_
	.section	.text._ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E,"axG",@progbits,_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC5ERKSt17_Rb_tree_iteratorIS3_E,comdat
	.align 2
	.weak	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E
	.type	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E, @function
_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E:
.LFB2305:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2305:
	.size	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E, .-_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E
	.weak	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC1ERKSt17_Rb_tree_iteratorIS3_E
	.set	_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC1ERKSt17_Rb_tree_iteratorIS3_E,_ZNSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEEC2ERKSt17_Rb_tree_iteratorIS3_E
	.section	.text._ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB2308:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2308:
	.size	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE,"axG",@progbits,_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE,comdat
	.weak	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	.type	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE, @function
_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE:
.LFB2309:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2309:
	.size	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE, .-_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	.weak	_ZSt7forwardISt5tupleIJRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	.set	_ZSt7forwardISt5tupleIJRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE,_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	.section	.text._ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB2310:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2310:
	.size	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	.weak	_ZSt7forwardISt5tupleIJEEEOT_RNSt16remove_referenceIS2_E4typeE
	.set	_ZSt7forwardISt5tupleIJEEEOT_RNSt16remove_referenceIS2_E4typeE,_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_:
.LFB2307:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2307
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 80
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rsi, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB135:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
.LEHE135:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
.LEHB136:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_
	mov	QWORD PTR [rbp-32], rax
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	test	rax, rax
	je	.L556
	mov	rdx, QWORD PTR [rbp-24]
	mov	rsi, QWORD PTR [rbp-32]
	mov	rcx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E
	jmp	.L564
.L556:
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
.LEHE136:
	mov	rdx, QWORD PTR [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-48]
	jmp	.L564
.L562:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB137:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
.LEHE137:
	jmp	.L565
.L563:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB138:
	call	_Unwind_Resume
.LEHE138:
.L565:
.LEHB139:
	call	__cxa_rethrow
.LEHE139:
.L564:
	add	rsp, 80
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2307:
	.section	.gcc_except_table
	.align 4
.LLSDA2307:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2307-.LLSDATTD2307
.LLSDATTD2307:
	.byte	0x1
	.uleb128 .LLSDACSE2307-.LLSDACSB2307
.LLSDACSB2307:
	.uleb128 .LEHB135-.LFB2307
	.uleb128 .LEHE135-.LEHB135
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB136-.LFB2307
	.uleb128 .LEHE136-.LEHB136
	.uleb128 .L562-.LFB2307
	.uleb128 0x3
	.uleb128 .LEHB137-.LFB2307
	.uleb128 .LEHE137-.LEHB137
	.uleb128 .L563-.LFB2307
	.uleb128 0
	.uleb128 .LEHB138-.LFB2307
	.uleb128 .LEHE138-.LEHB138
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB139-.LFB2307
	.uleb128 .LEHE139-.LEHB139
	.uleb128 .L563-.LFB2307
	.uleb128 0
.LLSDACSE2307:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT2307:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS2_EESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS2_EESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.section	.text._ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_,"axG",@progbits,_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_,comdat
	.align 2
	.weak	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
	.type	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_, @function
_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_:
.LFB2311:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2311:
	.size	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_, .-_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv,comdat
	.align 2
	.weak	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv
	.type	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv, @function
_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv:
.LFB2312:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv
	mov	eax, ebx
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2312:
	.size	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv, .-_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE8key_compEv
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv:
.LFB2313:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2313:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEdeEv
	.section	.text._ZNKSt4lessISsEclERKSsS2_,"axG",@progbits,_ZNKSt4lessISsEclERKSsS2_,comdat
	.align 2
	.weak	_ZNKSt4lessISsEclERKSsS2_
	.type	_ZNKSt4lessISsEclERKSsS2_, @function
_ZNKSt4lessISsEclERKSsS2_:
.LFB2314:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2314:
	.size	_ZNKSt4lessISsEclERKSsS2_, .-_ZNKSt4lessISsEclERKSsS2_
	.section	.text._ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv,"axG",@progbits,_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv,comdat
	.align 2
	.weak	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	.type	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv, @function
_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv:
.LFB2315:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2315:
	.size	_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv, .-_ZNSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	.section	.text._ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_,"axG",@progbits,_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_,comdat
	.align 2
	.weak	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_
	.type	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_, @function
_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_:
.LFB2316:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rax]
	cmp	rdx, rax
	sete	al
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2316:
	.size	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_, .-_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_
	.section	.text._ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E,"axG",@progbits,_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC5ERKSt17_Rb_tree_iteratorIS2_E,comdat
	.align 2
	.weak	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E
	.type	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E, @function
_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E:
.LFB2318:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2318:
	.size	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E, .-_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E
	.weak	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1ERKSt17_Rb_tree_iteratorIS2_E
	.set	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1ERKSt17_Rb_tree_iteratorIS2_E,_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2ERKSt17_Rb_tree_iteratorIS2_E
	.section	.text._ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE,"axG",@progbits,_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE,comdat
	.weak	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	.type	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE, @function
_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE:
.LFB2321:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2321:
	.size	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE, .-_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	.weak	_ZSt7forwardISt5tupleIJRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	.set	_ZSt7forwardISt5tupleIJRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE,_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_:
.LFB2320:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2320
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 80
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rsi, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB140:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
.LEHE140:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
.LEHB141:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_
	mov	QWORD PTR [rbp-32], rax
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	test	rax, rax
	je	.L582
	mov	rdx, QWORD PTR [rbp-24]
	mov	rsi, QWORD PTR [rbp-32]
	mov	rcx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E
	jmp	.L590
.L582:
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E
.LEHE141:
	mov	rdx, QWORD PTR [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-48]
	jmp	.L590
.L588:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB142:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E
.LEHE142:
	jmp	.L591
.L589:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB143:
	call	_Unwind_Resume
.LEHE143:
.L591:
.LEHB144:
	call	__cxa_rethrow
.LEHE144:
.L590:
	add	rsp, 80
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2320:
	.section	.gcc_except_table
	.align 4
.LLSDA2320:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2320-.LLSDATTD2320
.LLSDATTD2320:
	.byte	0x1
	.uleb128 .LLSDACSE2320-.LLSDACSB2320
.LLSDACSB2320:
	.uleb128 .LEHB140-.LFB2320
	.uleb128 .LEHE140-.LEHB140
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB141-.LFB2320
	.uleb128 .LEHE141-.LEHB141
	.uleb128 .L588-.LFB2320
	.uleb128 0x3
	.uleb128 .LEHB142-.LFB2320
	.uleb128 .LEHE142-.LEHB142
	.uleb128 .L589-.LFB2320
	.uleb128 0
	.uleb128 .LEHB143-.LFB2320
	.uleb128 .LEHE143-.LEHB143
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB144-.LFB2320
	.uleb128 .LEHE144-.LEHB144
	.uleb128 .L589-.LFB2320
	.uleb128 0
.LLSDACSE2320:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT2320:
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESD_IJEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.set	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESD_IJEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv:
.LFB2322:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	lea	rdx, [rax+8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1EPKSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2322:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_:
.LFB2323:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2323
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	mov	rsi, rax
	mov	rdx, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, rdx
	mov	rdx, rbx
	mov	rdi, rax
.LEHB145:
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_
.LEHE145:
	mov	QWORD PTR [rbp-48], rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	mov	QWORD PTR [rbp-32], rax
	mov	ebx, 1
	lea	rdx, [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_
	test	al, al
	jne	.L595
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
.LEHB146:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rbp-64]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE146:
	test	al, al
	je	.L596
.L595:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	jmp	.L605
.L596:
	mov	rax, QWORD PTR [rbp-48]
.L605:
	test	bl, bl
	jmp	.L606
.L604:
	test	bl, bl
	nop
	jmp	.L602
.L603:
.L602:
	mov	rdi, rax
.LEHB147:
	call	_Unwind_Resume
.LEHE147:
.L606:
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2323:
	.section	.gcc_except_table
.LLSDA2323:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2323-.LLSDACSB2323
.LLSDACSB2323:
	.uleb128 .LEHB145-.LFB2323
	.uleb128 .LEHE145-.LEHB145
	.uleb128 .L603-.LFB2323
	.uleb128 0
	.uleb128 .LEHB146-.LFB2323
	.uleb128 .LEHE146-.LEHB146
	.uleb128 .L604-.LFB2323
	.uleb128 0
	.uleb128 .LEHB147-.LFB2323
	.uleb128 .LEHE147-.LEHB147
	.uleb128 0
	.uleb128 0
.LLSDACSE2323:
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_,comdat
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4findERS1_
	.section	.text._ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_,"axG",@progbits,_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_,comdat
	.align 2
	.weak	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_
	.type	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_, @function
_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_:
.LFB2324:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rax]
	cmp	rdx, rax
	sete	al
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2324:
	.size	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_, .-_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEeqERKS3_
	.section	.text._ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_,"axG",@progbits,_ZNSt10_Head_baseILm0EOSsLb0EEC5ISsvEEOT_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_
	.type	_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_, @function
_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_:
.LFB2336:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2336:
	.size	_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_, .-_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_
	.weak	_ZNSt10_Head_baseILm0EOSsLb0EEC1ISsvEEOT_
	.set	_ZNSt10_Head_baseILm0EOSsLb0EEC1ISsvEEOT_,_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_
	.section	.text._ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSsEEC5ISsIEvEEOT_DpOT0_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_
	.type	_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_, @function
_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_:
.LFB2338:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm1EIEEC2Ev
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2338:
	.size	_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_, .-_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EJOSsEEC2ISsJEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EJOSsEEC2ISsJEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EIOSsEEC1ISsIEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EIOSsEEC1ISsIEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EJOSsEEC1ISsJEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EJOSsEEC1ISsJEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EIOSsEEC1ISsIEvEEOT_DpOT0_
	.section	.text._ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_,"axG",@progbits,_ZNSt5tupleIIOSsEEC5IISsEvEEDpOT_,comdat
	.align 2
	.weak	_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_
	.type	_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_, @function
_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_:
.LFB2340:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSsEEC2ISsIEvEEOT_DpOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2340:
	.size	_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_, .-_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_
	.weak	_ZNSt5tupleIJOSsEEC2IJSsEvEEDpOT_
	.set	_ZNSt5tupleIJOSsEEC2IJSsEvEEDpOT_,_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_
	.weak	_ZNSt5tupleIIOSsEEC1IISsEvEEDpOT_
	.set	_ZNSt5tupleIIOSsEEC1IISsEvEEDpOT_,_ZNSt5tupleIIOSsEEC2IISsEvEEDpOT_
	.weak	_ZNSt5tupleIJOSsEEC1IJSsEvEEDpOT_
	.set	_ZNSt5tupleIJOSsEEC1IJSsEvEEDpOT_,_ZNSt5tupleIIOSsEEC1IISsEvEEDpOT_
	.section	.text._ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_
	.type	_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_, @function
_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_:
.LFB2344:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2344:
	.size	_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_, .-_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_
	.weak	_ZNSt11_Tuple_implILm0EJOSsEE7_M_tailERS1_
	.set	_ZNSt11_Tuple_implILm0EJOSsEE7_M_tailERS1_,_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_
	.section	.text._ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_,"axG",@progbits,_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_,comdat
	.weak	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	.type	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_, @function
_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_:
.LFB2345:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2345:
	.size	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_, .-_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	.weak	_ZSt4moveIRSt11_Tuple_implILm1EJEEEONSt16remove_referenceIT_E4typeEOS4_
	.set	_ZSt4moveIRSt11_Tuple_implILm1EJEEEONSt16remove_referenceIT_E4typeEOS4_,_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	.section	.text._ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_,"axG",@progbits,_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_,comdat
	.weak	_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_
	.type	_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_, @function
_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_:
.LFB2347:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2347:
	.size	_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_, .-_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_
	.section	.text._ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_
	.type	_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_, @function
_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_:
.LFB2346:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0EOSsLb0EE7_M_headERS1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2346:
	.size	_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_, .-_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_
	.weak	_ZNSt11_Tuple_implILm0EJOSsEE7_M_headERS1_
	.set	_ZNSt11_Tuple_implILm0EJOSsEE7_M_headERS1_,_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_
	.section	.text._ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE,"axG",@progbits,_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE,comdat
	.weak	_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE
	.type	_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE, @function
_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE:
.LFB2348:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2348:
	.size	_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE, .-_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE
	.section	.text._ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSsEEC5EOS1_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_
	.type	_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_, @function
_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_:
.LFB2349:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSsEE7_M_tailERS1_
	mov	rdi, rax
	call	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_
	mov	rdi, rax
	call	_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0EOSsLb0EEC2ISsvEEOT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2349:
	.size	_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_, .-_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_
	.weak	_ZNSt11_Tuple_implILm0EJOSsEEC2EOS1_
	.set	_ZNSt11_Tuple_implILm0EJOSsEEC2EOS1_,_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_
	.weak	_ZNSt11_Tuple_implILm0EIOSsEEC1EOS1_
	.set	_ZNSt11_Tuple_implILm0EIOSsEEC1EOS1_,_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_
	.weak	_ZNSt11_Tuple_implILm0EJOSsEEC1EOS1_
	.set	_ZNSt11_Tuple_implILm0EJOSsEEC1EOS1_,_ZNSt11_Tuple_implILm0EIOSsEEC1EOS1_
	.section	.text._ZNSt5tupleIIOSsEEC2EOS1_,"axG",@progbits,_ZNSt5tupleIIOSsEEC5EOS1_,comdat
	.align 2
	.weak	_ZNSt5tupleIIOSsEEC2EOS1_
	.type	_ZNSt5tupleIIOSsEEC2EOS1_, @function
_ZNSt5tupleIIOSsEEC2EOS1_:
.LFB2351:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSsEEC2EOS1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2351:
	.size	_ZNSt5tupleIIOSsEEC2EOS1_, .-_ZNSt5tupleIIOSsEEC2EOS1_
	.weak	_ZNSt5tupleIJOSsEEC2EOS1_
	.set	_ZNSt5tupleIJOSsEEC2EOS1_,_ZNSt5tupleIIOSsEEC2EOS1_
	.weak	_ZNSt5tupleIIOSsEEC1EOS1_
	.set	_ZNSt5tupleIIOSsEEC1EOS1_,_ZNSt5tupleIIOSsEEC2EOS1_
	.weak	_ZNSt5tupleIJOSsEEC1EOS1_
	.set	_ZNSt5tupleIJOSsEEC1EOS1_,_ZNSt5tupleIIOSsEEC1EOS1_
	.section	.text._ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_,"axG",@progbits,_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_,comdat
	.weak	_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_
	.type	_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_, @function
_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_:
.LFB2332:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISsEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIOSsEEC1IISsEvEEDpOT_
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2332:
	.size	_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_, .-_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_
	.weak	_ZSt16forward_as_tupleIJSsEESt5tupleIJDpOT_EES3_
	.set	_ZSt16forward_as_tupleIJSsEESt5tupleIJDpOT_EES3_,_ZSt16forward_as_tupleIISsEESt5tupleIIDpOT_EES3_
	.section	.text._ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB2354:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2354:
	.size	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	.weak	_ZSt7forwardISt5tupleIJOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	.set	_ZSt7forwardISt5tupleIJOSsEEEOT_RNSt16remove_referenceIS3_E4typeE,_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_:
.LFB2353:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2353
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 80
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rsi, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB148:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
.LEHE148:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
.LEHB149:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_
	mov	QWORD PTR [rbp-32], rax
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	test	rax, rax
	je	.L629
	mov	rdx, QWORD PTR [rbp-24]
	mov	rsi, QWORD PTR [rbp-32]
	mov	rcx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E
	jmp	.L637
.L629:
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E
.LEHE149:
	mov	rdx, QWORD PTR [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-48]
	jmp	.L637
.L635:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB150:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E
.LEHE150:
	jmp	.L638
.L636:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB151:
	call	_Unwind_Resume
.LEHE151:
.L638:
.LEHB152:
	call	__cxa_rethrow
.LEHE152:
.L637:
	add	rsp, 80
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2353:
	.section	.gcc_except_table
	.align 4
.LLSDA2353:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2353-.LLSDATTD2353
.LLSDATTD2353:
	.byte	0x1
	.uleb128 .LLSDACSE2353-.LLSDACSB2353
.LLSDACSB2353:
	.uleb128 .LEHB148-.LFB2353
	.uleb128 .LEHE148-.LEHB148
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB149-.LFB2353
	.uleb128 .LEHE149-.LEHB149
	.uleb128 .L635-.LFB2353
	.uleb128 0x3
	.uleb128 .LEHB150-.LFB2353
	.uleb128 .LEHE150-.LEHB150
	.uleb128 .L636-.LFB2353
	.uleb128 0
	.uleb128 .LEHB151-.LFB2353
	.uleb128 .LEHE151-.LEHB151
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB152-.LFB2353
	.uleb128 .LEHE152-.LEHB152
	.uleb128 .L636-.LFB2353
	.uleb128 0
.LLSDACSE2353:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT2353:
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESD_IJEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.set	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOSsEESD_IJEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEESt17_Rb_tree_iteratorIS2_ESt23_Rb_tree_const_iteratorIS2_EDpOT_
	.section	.text._ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE,"axG",@progbits,_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE,comdat
	.weak	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	.type	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE, @function
_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE:
.LFB2356:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2356:
	.size	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE, .-_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	.section	.text._ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_,"axG",@progbits,_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_
	.type	_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_, @function
_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_:
.LFB2355:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	cmp	rdx, rax
	je	.L642
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	jmp	.L641
.L642:
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_
.L641:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2355:
	.size	_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_, .-_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_
	.weak	_ZNSt6vectorIhSaIhEE12emplace_backIJhEEEvDpOT_
	.set	_ZNSt6vectorIhSaIhEE12emplace_backIJhEEEvDpOT_,_ZNSt6vectorIhSaIhEE12emplace_backIIhEEEvDpOT_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhEC2Ev,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhEC5Ev,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhEC2Ev
	.type	_ZN9__gnu_cxx13new_allocatorIhEC2Ev, @function
_ZN9__gnu_cxx13new_allocatorIhEC2Ev:
.LFB2358:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2358:
	.size	_ZN9__gnu_cxx13new_allocatorIhEC2Ev, .-_ZN9__gnu_cxx13new_allocatorIhEC2Ev
	.weak	_ZN9__gnu_cxx13new_allocatorIhEC1Ev
	.set	_ZN9__gnu_cxx13new_allocatorIhEC1Ev,_ZN9__gnu_cxx13new_allocatorIhEC2Ev
	.section	.text._ZN9__gnu_cxx13new_allocatorIhED2Ev,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhED5Ev,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhED2Ev
	.type	_ZN9__gnu_cxx13new_allocatorIhED2Ev, @function
_ZN9__gnu_cxx13new_allocatorIhED2Ev:
.LFB2361:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2361:
	.size	_ZN9__gnu_cxx13new_allocatorIhED2Ev, .-_ZN9__gnu_cxx13new_allocatorIhED2Ev
	.weak	_ZN9__gnu_cxx13new_allocatorIhED1Ev
	.set	_ZN9__gnu_cxx13new_allocatorIhED1Ev,_ZN9__gnu_cxx13new_allocatorIhED2Ev
	.section	.text._ZNSt12_Vector_baseIhSaIhEEC2ERKS0_,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEEC5ERKS0_,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_
	.type	_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_, @function
_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_:
.LFB2364:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC1ERKS0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2364:
	.size	_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_, .-_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_
	.weak	_ZNSt12_Vector_baseIhSaIhEEC1ERKS0_
	.set	_ZNSt12_Vector_baseIhSaIhEEC1ERKS0_,_ZNSt12_Vector_baseIhSaIhEEC2ERKS0_
	.section	.text._ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag,"axG",@progbits,_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag
	.type	_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag, @function
_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag:
.LFB2366:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm
	mov	rdx, QWORD PTR [rbp-24]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	QWORD PTR [rax+16], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax]
	mov	rsi, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E
	mov	rdx, QWORD PTR [rbp-24]
	mov	QWORD PTR [rdx+8], rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2366:
	.size	_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag, .-_ZNSt6vectorIhSaIhEE19_M_range_initializeIPKhEEvT_S5_St20forward_iterator_tag
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC5ERKS2_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_
	.type	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_, @function
_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_:
.LFB2368:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2368:
	.size	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_, .-_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_
	.weak	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS2_
	.set	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS2_,_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS2_
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv:
.LFB2370:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2370:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv, .-_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	.section	.text._ZNSt6vectorIhSaIhEE5frontEv,"axG",@progbits,_ZNSt6vectorIhSaIhEE5frontEv,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE5frontEv
	.type	_ZNSt6vectorIhSaIhEE5frontEv, @function
_ZNSt6vectorIhSaIhEE5frontEv:
.LFB2371:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt6vectorIhSaIhEE5beginEv
	mov	QWORD PTR [rbp-16], rax
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2371:
	.size	_ZNSt6vectorIhSaIhEE5frontEv, .-_ZNSt6vectorIhSaIhEE5frontEv
	.section	.text._ZSt11__addressofIhEPT_RS0_,"axG",@progbits,_ZSt11__addressofIhEPT_RS0_,comdat
	.weak	_ZSt11__addressofIhEPT_RS0_
	.type	_ZSt11__addressofIhEPT_RS0_, @function
_ZSt11__addressofIhEPT_RS0_:
.LFB2372:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2372:
	.size	_ZSt11__addressofIhEPT_RS0_, .-_ZSt11__addressofIhEPT_RS0_
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_,comdat
	.align 2
	.weak	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
	.type	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_, @function
_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_:
.LFB2373:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2373:
	.size	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_, .-_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE11lower_boundERS3_
	.section	.text._ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv,"axG",@progbits,_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv,comdat
	.align 2
	.weak	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv
	.type	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv, @function
_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv:
.LFB2374:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2374:
	.size	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv, .-_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEEdeEv
	.section	.text._ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv,"axG",@progbits,_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv,comdat
	.align 2
	.weak	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	.type	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv, @function
_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv:
.LFB2375:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2375:
	.size	_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv, .-_ZNKSt3mapISslSt4lessISsESaISt4pairIKSslEEE3endEv
	.section	.text._ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB2377:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2377:
	.size	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_,"axG",@progbits,_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC5IS1_vEEOT_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_
	.type	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_, @function
_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_:
.LFB2381:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2381:
	.size	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_, .-_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_
	.weak	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC1IS1_vEEOT_
	.set	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC1IS1_vEEOT_,_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_
	.section	.text._ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC5IS1_IEvEEOT_DpOT0_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_
	.type	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_, @function
_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_:
.LFB2383:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm1EIEEC2Ev
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2383:
	.size	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_, .-_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC2IS1_JEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC2IS1_JEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC1IS1_IEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC1IS1_IEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC1IS1_JEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC1IS1_JEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC1IS1_IEvEEOT_DpOT0_
	.section	.text._ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_,"axG",@progbits,_ZNSt5tupleIIOSt4pairISsjEEEC5IIS1_EvEEDpOT_,comdat
	.align 2
	.weak	_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_
	.type	_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_, @function
_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_:
.LFB2385:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2IS1_IEvEEOT_DpOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2385:
	.size	_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_, .-_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_
	.weak	_ZNSt5tupleIJOSt4pairISsjEEEC2IJS1_EvEEDpOT_
	.set	_ZNSt5tupleIJOSt4pairISsjEEEC2IJS1_EvEEDpOT_,_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_
	.weak	_ZNSt5tupleIIOSt4pairISsjEEEC1IIS1_EvEEDpOT_
	.set	_ZNSt5tupleIIOSt4pairISsjEEEC1IIS1_EvEEDpOT_,_ZNSt5tupleIIOSt4pairISsjEEEC2IIS1_EvEEDpOT_
	.weak	_ZNSt5tupleIJOSt4pairISsjEEEC1IJS1_EvEEDpOT_
	.set	_ZNSt5tupleIJOSt4pairISsjEEEC1IJS1_EvEEDpOT_,_ZNSt5tupleIIOSt4pairISsjEEEC1IIS1_EvEEDpOT_
	.section	.text._ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_
	.type	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_, @function
_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_:
.LFB2389:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2389:
	.size	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_, .-_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_
	.weak	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEE7_M_tailERS3_
	.set	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEE7_M_tailERS3_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_
	.section	.text._ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_,"axG",@progbits,_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_,comdat
	.weak	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_
	.type	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_, @function
_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_:
.LFB2391:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2391:
	.size	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_, .-_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_
	.section	.text._ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_
	.type	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_, @function
_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_:
.LFB2390:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EE7_M_headERS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2390:
	.size	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_, .-_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_
	.weak	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEE7_M_headERS3_
	.set	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEE7_M_headERS3_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_
	.section	.text._ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB2392:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2392:
	.size	_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC5EOS3_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_
	.type	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_, @function
_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_:
.LFB2393:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_tailERS3_
	mov	rdi, rax
	call	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_
	mov	rdi, rax
	call	_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0EOSt4pairISsjELb0EEC2IS1_vEEOT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2393:
	.size	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_, .-_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_
	.weak	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC2EOS3_
	.set	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC2EOS3_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_
	.weak	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC1EOS3_
	.set	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC1EOS3_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_
	.weak	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC1EOS3_
	.set	_ZNSt11_Tuple_implILm0EJOSt4pairISsjEEEC1EOS3_,_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC1EOS3_
	.section	.text._ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_,"axG",@progbits,_ZNSt5tupleIIOSt4pairISsjEEEC5EOS3_,comdat
	.align 2
	.weak	_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_
	.type	_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_, @function
_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_:
.LFB2395:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEEC2EOS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2395:
	.size	_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_, .-_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_
	.weak	_ZNSt5tupleIJOSt4pairISsjEEEC2EOS3_
	.set	_ZNSt5tupleIJOSt4pairISsjEEEC2EOS3_,_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_
	.weak	_ZNSt5tupleIIOSt4pairISsjEEEC1EOS3_
	.set	_ZNSt5tupleIIOSt4pairISsjEEEC1EOS3_,_ZNSt5tupleIIOSt4pairISsjEEEC2EOS3_
	.weak	_ZNSt5tupleIJOSt4pairISsjEEEC1EOS3_
	.set	_ZNSt5tupleIJOSt4pairISsjEEEC1EOS3_,_ZNSt5tupleIIOSt4pairISsjEEEC1EOS3_
	.section	.text._ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_,"axG",@progbits,_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_,comdat
	.weak	_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_
	.type	_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_, @function
_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_:
.LFB2376:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardISt4pairISsjEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIOSt4pairISsjEEEC1IIS1_EvEEDpOT_
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2376:
	.size	_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_, .-_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_
	.weak	_ZSt16forward_as_tupleIJSt4pairISsjEEESt5tupleIJDpOT_EES5_
	.set	_ZSt16forward_as_tupleIJSt4pairISsjEEESt5tupleIJDpOT_EES5_,_ZSt16forward_as_tupleIISt4pairISsjEEESt5tupleIIDpOT_EES5_
	.section	.text._ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE,"axG",@progbits,_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE,comdat
	.weak	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	.type	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE, @function
_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE:
.LFB2398:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2398:
	.size	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE, .-_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	.weak	_ZSt7forwardISt5tupleIJOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	.set	_ZSt7forwardISt5tupleIJOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE,_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_:
.LFB2397:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2397
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 80
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rsi, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB153:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
.LEHE153:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
.LEHB154:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_
	mov	QWORD PTR [rbp-32], rax
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	test	rax, rax
	je	.L682
	mov	rdx, QWORD PTR [rbp-24]
	mov	rsi, QWORD PTR [rbp-32]
	mov	rcx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E
	jmp	.L690
.L682:
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
.LEHE154:
	mov	rdx, QWORD PTR [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-48]
	jmp	.L690
.L688:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB155:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
.LEHE155:
	jmp	.L691
.L689:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB156:
	call	_Unwind_Resume
.LEHE156:
.L691:
.LEHB157:
	call	__cxa_rethrow
.LEHE157:
.L690:
	add	rsp, 80
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2397:
	.section	.gcc_except_table
	.align 4
.LLSDA2397:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2397-.LLSDATTD2397
.LLSDATTD2397:
	.byte	0x1
	.uleb128 .LLSDACSE2397-.LLSDACSB2397
.LLSDACSB2397:
	.uleb128 .LEHB153-.LFB2397
	.uleb128 .LEHE153-.LEHB153
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB154-.LFB2397
	.uleb128 .LEHE154-.LEHB154
	.uleb128 .L688-.LFB2397
	.uleb128 0x3
	.uleb128 .LEHB155-.LFB2397
	.uleb128 .LEHE155-.LEHB155
	.uleb128 .L689-.LFB2397
	.uleb128 0
	.uleb128 .LEHB156-.LFB2397
	.uleb128 .LEHE156-.LEHB156
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB157-.LFB2397
	.uleb128 .LEHE157-.LEHB157
	.uleb128 .L689-.LFB2397
	.uleb128 0
.LLSDACSE2397:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT2397:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOS1_EESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJOS1_EESE_IJEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE22_M_emplace_hint_uniqueIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEESt17_Rb_tree_iteratorIS3_ESt23_Rb_tree_const_iteratorIS3_EDpOT_
	.section	.text._ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_
	.type	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_, @function
_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_:
.LFB2419:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2419:
	.size	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_, .-_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_
	.weak	_ZNSt16allocator_traitsISaIhEE12_S_constructIhJRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_
	.set	_ZNSt16allocator_traitsISaIhEE12_S_constructIhJRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_,_ZNSt16allocator_traitsISaIhEE12_S_constructIhIRKhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS7_DpOS8_
	.section	.text._ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc,"axG",@progbits,_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc,comdat
	.align 2
	.weak	_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc
	.type	_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc, @function
_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc:
.LFB2420:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE8max_sizeEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	sub	rbx, rax
	mov	rdx, rbx
	mov	rax, QWORD PTR [rbp-48]
	cmp	rdx, rax
	setb	al
	test	al, al
	je	.L694
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt20__throw_length_errorPKc
.L694:
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	QWORD PTR [rbp-32], rax
	lea	rdx, [rbp-48]
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt3maxImERKT_S2_S2_
	mov	rax, QWORD PTR [rax]
	add	rax, rbx
	mov	QWORD PTR [rbp-24], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	cmp	rax, QWORD PTR [rbp-24]
	ja	.L695
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE8max_sizeEv
	cmp	rax, QWORD PTR [rbp-24]
	jae	.L696
.L695:
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE8max_sizeEv
	jmp	.L697
.L696:
	mov	rax, QWORD PTR [rbp-24]
.L697:
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2420:
	.size	_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc, .-_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc
	.section	.text._ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm
	.type	_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm, @function
_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm:
.LFB2421:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	cmp	QWORD PTR [rbp-16], 0
	je	.L700
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rbp-16]
	mov	edx, 0
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv
	jmp	.L701
.L700:
	mov	eax, 0
.L701:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2421:
	.size	_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm, .-_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm
	.section	.text._ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_,"axG",@progbits,_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_,comdat
	.weak	_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_
	.type	_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_, @function
_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_:
.LFB2422:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_
	mov	rcx, QWORD PTR [rbp-48]
	mov	rdx, QWORD PTR [rbp-40]
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2422:
	.size	_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_, .-_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_
	.section	.text._ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_
	.type	_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_, @function
_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_:
.LFB2423:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2423:
	.size	_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_, .-_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_
	.section	.text._ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
	.type	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm, @function
_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm:
.LFB2424:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	cmp	QWORD PTR [rbp-16], 0
	je	.L706
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm
.L706:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2424:
	.size	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm, .-_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC5Ev,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev:
.LFB2426:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+16], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+24], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+32], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+40], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2426:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC1Ev
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC1Ev,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EEC2Ev
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED5Ev,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev:
.LFB2429:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2429:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED1Ev
	.set	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED1Ev,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEED2Ev
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base:
.LFB2431:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+24]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2431:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base:
.LFB2432:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2432:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E:
.LFB2433:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2433:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC5EPSt13_Rb_tree_nodeIS3_E,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E:
.LFB2435:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2435:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E, .-_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC1EPSt13_Rb_tree_nodeIS3_E
	.set	_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC1EPSt13_Rb_tree_nodeIS3_E,_ZNSt17_Rb_tree_iteratorISt4pairIKSs15DefinedFunctionEEC2EPSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev:
.LFB2438:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSaI11InstructionEC2Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+16], 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2438:
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC1Ev
	.set	_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC1Ev,_ZNSt12_Vector_baseI11InstructionSaIS0_EE12_Vector_implC2Ev
	.section	.text._ZNSaI11InstructionED2Ev,"axG",@progbits,_ZNSaI11InstructionED5Ev,comdat
	.align 2
	.weak	_ZNSaI11InstructionED2Ev
	.type	_ZNSaI11InstructionED2Ev, @function
_ZNSaI11InstructionED2Ev:
.LFB2441:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2441:
	.size	_ZNSaI11InstructionED2Ev, .-_ZNSaI11InstructionED2Ev
	.weak	_ZNSaI11InstructionED1Ev
	.set	_ZNSaI11InstructionED1Ev,_ZNSaI11InstructionED2Ev
	.section	.text._ZSt8_DestroyIP11InstructionEvT_S2_,"axG",@progbits,_ZSt8_DestroyIP11InstructionEvT_S2_,comdat
	.weak	_ZSt8_DestroyIP11InstructionEvT_S2_
	.type	_ZSt8_DestroyIP11InstructionEvT_S2_, @function
_ZSt8_DestroyIP11InstructionEvT_S2_:
.LFB2443:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2443:
	.size	_ZSt8_DestroyIP11InstructionEvT_S2_, .-_ZSt8_DestroyIP11InstructionEvT_S2_
	.section	.text._ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev
	.type	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev, @function
_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev:
.LFB2445:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSaIhEC2Ev
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+16], 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2445:
	.size	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev, .-_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev
	.weak	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC1Ev
	.set	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC1Ev,_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2Ev
	.section	.text._ZSt8_DestroyIPhEvT_S1_,"axG",@progbits,_ZSt8_DestroyIPhEvT_S1_,comdat
	.weak	_ZSt8_DestroyIPhEvT_S1_
	.type	_ZSt8_DestroyIPhEvT_S1_, @function
_ZSt8_DestroyIPhEvT_S1_:
.LFB2447:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2447:
	.size	_ZSt8_DestroyIPhEvT_S1_, .-_ZSt8_DestroyIPhEvT_S1_
	.section	.text._ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_,"axG",@progbits,_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_,comdat
	.align 2
	.weak	_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_
	.type	_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_, @function
_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_:
.LFB2448:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseI11InstructionSaIS0_EE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt8_DestroyIP11InstructionS0_EvT_S2_RSaIT0_E
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2448:
	.size	_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_, .-_ZNSt6vectorI11InstructionSaIS0_EE15_M_erase_at_endEPS0_
	.section	.text._ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m
	.type	_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m, @function
_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m:
.LFB2449:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2449:
	.size	_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m, .-_ZN9__gnu_cxx13new_allocatorI11InstructionE10deallocateEPS1_m
	.section	.text._ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE,"axG",@progbits,_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE,comdat
	.weak	_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE
	.type	_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE, @function
_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE:
.LFB2450:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2450:
	.size	_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE, .-_ZSt18__do_alloc_on_copyISaI11InstructionEEvRT_RKS2_St17integral_constantIbLb0EE
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC5ERKS3_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_
	.type	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_, @function
_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_:
.LFB2452:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2452:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_, .-_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS3_
	.set	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS3_,_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEC2ERKS3_
	.section	.text._ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm,"axG",@progbits,_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm
	.type	_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm, @function
_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm:
.LFB2454:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	cmp	QWORD PTR [rbp-16], 0
	je	.L728
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rbp-16]
	mov	edx, 0
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv
	jmp	.L729
.L728:
	mov	eax, 0
.L729:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2454:
	.size	_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm, .-_ZNSt12_Vector_baseI11InstructionSaIS0_EE11_M_allocateEm
	.section	.text._ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E,"axG",@progbits,_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E,comdat
	.weak	_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E
	.type	_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E, @function
_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E:
.LFB2455:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	QWORD PTR [rbp-8], rcx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2455:
	.size	_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E, .-_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_S2_ET0_T_SB_SA_RSaIT1_E
	.section	.text._ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_,"axG",@progbits,_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_,comdat
	.weak	_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_
	.type	_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_, @function
_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_:
.LFB2456:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2456:
	.size	_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_, .-_ZSt12__miter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Miter_baseIT_E13iterator_typeESA_
	.section	.text._ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_,"axG",@progbits,_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_,comdat
	.weak	_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_
	.type	_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_, @function
_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_:
.LFB2457:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 64
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-48], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-80], rdx
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_
	mov	rdx, r12
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_
	mov	QWORD PTR [rbp-24], rax
	lea	rdx, [rbp-24]
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEC1ERKS2_
	mov	rax, QWORD PTR [rbp-32]
	add	rsp, 64
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2457:
	.size	_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_, .-_ZSt14__copy_move_a2ILb0EN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEENS1_IPS2_S7_EEET1_T0_SC_SB_
	.section	.text._ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_,"axG",@progbits,_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_,comdat
	.weak	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_
	.type	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_, @function
_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_:
.LFB2458:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2458:
	.size	_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_, .-_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEEvT_S8_
	.section	.text._ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_,"axG",@progbits,_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_,comdat
	.weak	_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_
	.type	_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_, @function
_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_:
.LFB2459:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2459:
	.size	_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_, .-_ZSt12__miter_baseIP11InstructionENSt11_Miter_baseIT_E13iterator_typeES3_
	.section	.text._ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_,"axG",@progbits,_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_,comdat
	.weak	_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_
	.type	_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_, @function
_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_:
.LFB2460:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 32
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_
	mov	rdx, r12
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_
	add	rsp, 32
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2460:
	.size	_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_, .-_ZSt14__copy_move_a2ILb0EP11InstructionS1_ET1_T0_S3_S2_
	.section	.text._ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_,"axG",@progbits,_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_,comdat
	.weak	_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_
	.type	_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_, @function
_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_:
.LFB2461:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2461:
	.size	_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_, .-_ZSt18uninitialized_copyIP11InstructionS1_ET0_T_S3_S2_
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC5EPSt13_Rb_tree_nodeIS3_E,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E:
.LFB2465:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2465:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E, .-_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	.set	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E,_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC2EPSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_:
.LFB2467:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv
	mov	rsi, rax
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, rdx
	mov	rdx, rbx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2467:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11lower_boundERS2_
	.section	.text._ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv,"axG",@progbits,_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv
	.type	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv, @function
_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv:
.LFB2468:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2468:
	.size	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv, .-_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8key_compEv
	.section	.text._ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_,"axG",@progbits,_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_,comdat
	.weak	_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_
	.type	_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_, @function
_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_:
.LFB2469:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSs7compareERKSs
	shr	eax, 31
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2469:
	.size	_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_, .-_ZStltIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_:
.LFB2470:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2470
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
.LEHB158:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv
.LEHE158:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv
	mov	rsi, QWORD PTR [rbp-40]
	mov	r8, r13
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB159:
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
.LEHE159:
	mov	rax, QWORD PTR [rbp-40]
	jmp	.L757
.L756:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB160:
	call	_Unwind_Resume
.LEHE160:
.L755:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB161:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E
	call	__cxa_rethrow
.LEHE161:
.L757:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2470:
	.section	.gcc_except_table
	.align 4
.LLSDA2470:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2470-.LLSDATTD2470
.LLSDATTD2470:
	.byte	0x1
	.uleb128 .LLSDACSE2470-.LLSDACSB2470
.LLSDACSB2470:
	.uleb128 .LEHB158-.LFB2470
	.uleb128 .LEHE158-.LEHB158
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB159-.LFB2470
	.uleb128 .LEHE159-.LEHB159
	.uleb128 .L755-.LFB2470
	.uleb128 0x1
	.uleb128 .LEHB160-.LFB2470
	.uleb128 .LEHE160-.LEHB160
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB161-.LFB2470
	.uleb128 .LEHE161-.LEHB161
	.uleb128 .L756-.LFB2470
	.uleb128 0
.LLSDACSE2470:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2470:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJRS2_EESE_IJEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJRS2_EESE_IJEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS2_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.section	.text._ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB2473:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2473:
	.size	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_,"axG",@progbits,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC5IRS1_vEERKS1_OT_,comdat
	.align 2
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_
	.type	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_, @function
_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_:
.LFB2474:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2474:
	.size	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_, .-_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	.set	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEERKS1_OT_
	.section	.text._ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_,"axG",@progbits,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC5IRS1_S4_vEEOT_OT0_,comdat
	.align 2
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_
	.type	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_, @function
_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_:
.LFB2477:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2477:
	.size	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_, .-_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	.set	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_S4_vEEOT_OT0_
	.section	.text._ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_,"axG",@progbits,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC5IRS1_vEEOT_RKS1_,comdat
	.align 2
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_
	.type	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_, @function
_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_:
.LFB2480:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt18_Rb_tree_node_baseEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2480:
	.size	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_, .-_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEEOT_RKS1_
	.set	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEEOT_RKS1_,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRS1_vEEOT_RKS1_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_:
.LFB2471:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2471
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 104
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-88], rdi
	mov	QWORD PTR [rbp-96], rsi
	mov	QWORD PTR [rbp-104], rdx
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv
	mov	QWORD PTR [rbp-80], rax
	mov	rbx, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv
	cmp	rbx, rax
	sete	al
	test	al, al
	je	.L764
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv
	test	rax, rax
	je	.L765
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
.LEHB162:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	test	al, al
	je	.L765
	mov	eax, 1
	jmp	.L766
.L765:
	mov	eax, 0
.L766:
	test	al, al
	je	.L767
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv
	mov	rdx, rax
	mov	QWORD PTR [rbp-40], 0
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L767:
	mov	rdx, QWORD PTR [rbp-104]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_
	jmp	.L786
.L764:
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rcx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
.LEHE162:
	test	al, al
	je	.L769
	mov	rax, QWORD PTR [rbp-80]
	mov	QWORD PTR [rbp-64], rax
	mov	rbx, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	sete	al
	test	al, al
	je	.L770
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv
	mov	rcx, rax
	lea	rax, [rbp-32]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L770:
	lea	rax, [rbp-64]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
.LEHB163:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	test	al, al
	je	.L772
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
	test	rax, rax
	sete	al
	test	al, al
	je	.L773
	mov	QWORD PTR [rbp-40], 0
	lea	rdx, [rbp-64]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L773:
	lea	rdx, [rbp-80]
	lea	rcx, [rbp-80]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L772:
	mov	rdx, QWORD PTR [rbp-104]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_
.LEHE163:
	jmp	.L786
.L769:
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
.LEHB164:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
.LEHE164:
	test	al, al
	je	.L774
	mov	rax, QWORD PTR [rbp-80]
	mov	QWORD PTR [rbp-48], rax
	mov	rbx, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	sete	al
	test	al, al
	je	.L775
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv
	mov	rdx, rax
	mov	QWORD PTR [rbp-40], 0
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L775:
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEppEv
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
.LEHB165:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rcx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	test	al, al
	je	.L777
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
	test	rax, rax
	sete	al
	test	al, al
	je	.L778
	mov	QWORD PTR [rbp-40], 0
	lea	rdx, [rbp-80]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L778:
	lea	rdx, [rbp-48]
	lea	rcx, [rbp-48]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L777:
	mov	rdx, QWORD PTR [rbp-104]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_
.LEHE165:
	jmp	.L786
.L774:
	mov	QWORD PTR [rbp-40], 0
	lea	rdx, [rbp-40]
	lea	rcx, [rbp-80]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEEOT_RKS1_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L786
.L784:
	jmp	.L781
.L785:
	jmp	.L781
.L783:
.L781:
	mov	rdi, rax
.LEHB166:
	call	_Unwind_Resume
.LEHE166:
.L786:
	add	rsp, 104
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2471:
	.section	.gcc_except_table
.LLSDA2471:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2471-.LLSDACSB2471
.LLSDACSB2471:
	.uleb128 .LEHB162-.LFB2471
	.uleb128 .LEHE162-.LEHB162
	.uleb128 .L783-.LFB2471
	.uleb128 0
	.uleb128 .LEHB163-.LFB2471
	.uleb128 .LEHE163-.LEHB163
	.uleb128 .L784-.LFB2471
	.uleb128 0
	.uleb128 .LEHB164-.LFB2471
	.uleb128 .LEHE164-.LEHB164
	.uleb128 .L783-.LFB2471
	.uleb128 0
	.uleb128 .LEHB165-.LFB2471
	.uleb128 .LEHE165-.LEHB165
	.uleb128 .L785-.LFB2471
	.uleb128 0
	.uleb128 .LEHB166-.LFB2471
	.uleb128 .LEHE166-.LEHB166
	.uleb128 0
	.uleb128 0
.LLSDACSE2471:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS3_ERS2_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E,comdat
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E:
.LFB2482:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E
	mov	rdx, rax
	lea	rax, [rbp-1]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2482:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E:
.LFB2483:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 72
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	cmp	QWORD PTR [rbp-64], 0
	jne	.L790
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv
	cmp	rax, QWORD PTR [rbp-72]
	je	.L790
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	test	al, al
	je	.L791
.L790:
	mov	eax, 1
	jmp	.L792
.L791:
	mov	eax, 0
.L792:
	mov	BYTE PTR [rbp-33], al
	mov	rax, QWORD PTR [rbp-56]
	lea	rcx, [rax+8]
	movzx	eax, BYTE PTR [rbp-33]
	mov	rdx, QWORD PTR [rbp-72]
	mov	rsi, QWORD PTR [rbp-80]
	mov	edi, eax
	call	_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+40]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+40], rdx
	mov	rdx, QWORD PTR [rbp-80]
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-32]
	add	rsp, 72
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2483:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSB_PSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_:
.LFB2484:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	mov	rsi, rax
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, rdx
	mov	rdx, rbx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2484:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv:
.LFB2485:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2485:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8key_compEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv:
.LFB2486:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	lea	rdx, [rax+8]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2486:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE3endEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_:
.LFB2487:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2487
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
.LEHB167:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv
.LEHE167:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv
	mov	rsi, QWORD PTR [rbp-40]
	mov	r8, r13
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB168:
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
.LEHE168:
	mov	rax, QWORD PTR [rbp-40]
	jmp	.L806
.L805:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB169:
	call	_Unwind_Resume
.LEHE169:
.L804:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB170:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E
	call	__cxa_rethrow
.LEHE170:
.L806:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2487:
	.section	.gcc_except_table
	.align 4
.LLSDA2487:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2487-.LLSDATTD2487
.LLSDATTD2487:
	.byte	0x1
	.uleb128 .LLSDACSE2487-.LLSDACSB2487
.LLSDACSB2487:
	.uleb128 .LEHB167-.LFB2487
	.uleb128 .LEHE167-.LEHB167
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB168-.LFB2487
	.uleb128 .LEHE168-.LEHB168
	.uleb128 .L804-.LFB2487
	.uleb128 0x1
	.uleb128 .LEHB169-.LFB2487
	.uleb128 .LEHE169-.LEHB169
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB170-.LFB2487
	.uleb128 .LEHE170-.LEHB170
	.uleb128 .L805-.LFB2487
	.uleb128 0
.LLSDACSE2487:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2487:
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESD_IJEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.set	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESD_IJEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIRS1_EESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_:
.LFB2488:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2488
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 104
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-88], rdi
	mov	QWORD PTR [rbp-96], rsi
	mov	QWORD PTR [rbp-104], rdx
	lea	rax, [rbp-96]
	mov	rdi, rax
	call	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv
	mov	QWORD PTR [rbp-80], rax
	mov	rbx, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	cmp	rbx, rax
	sete	al
	test	al, al
	je	.L808
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv
	test	rax, rax
	je	.L809
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
.LEHB171:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
	test	al, al
	je	.L809
	mov	eax, 1
	jmp	.L810
.L809:
	mov	eax, 0
.L810:
	test	al, al
	je	.L811
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv
	mov	rdx, rax
	mov	QWORD PTR [rbp-40], 0
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L811:
	mov	rdx, QWORD PTR [rbp-104]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_
	jmp	.L830
.L808:
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rcx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE171:
	test	al, al
	je	.L813
	mov	rax, QWORD PTR [rbp-80]
	mov	QWORD PTR [rbp-64], rax
	mov	rbx, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	sete	al
	test	al, al
	je	.L814
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv
	mov	rcx, rax
	lea	rax, [rbp-32]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L814:
	lea	rax, [rbp-64]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
.LEHB172:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
	test	al, al
	je	.L816
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base
	test	rax, rax
	sete	al
	test	al, al
	je	.L817
	mov	QWORD PTR [rbp-40], 0
	lea	rdx, [rbp-64]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L817:
	lea	rdx, [rbp-80]
	lea	rcx, [rbp-80]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L816:
	mov	rdx, QWORD PTR [rbp-104]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_
.LEHE172:
	jmp	.L830
.L813:
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
.LEHB173:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE173:
	test	al, al
	je	.L818
	mov	rax, QWORD PTR [rbp-80]
	mov	QWORD PTR [rbp-48], rax
	mov	rbx, QWORD PTR [rbp-80]
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	sete	al
	test	al, al
	je	.L819
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv
	mov	rdx, rax
	mov	QWORD PTR [rbp-40], 0
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L819:
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
.LEHB174:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rcx, QWORD PTR [rbp-104]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
	test	al, al
	je	.L821
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base
	test	rax, rax
	sete	al
	test	al, al
	je	.L822
	mov	QWORD PTR [rbp-40], 0
	lea	rdx, [rbp-80]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEERKS1_OT_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L822:
	lea	rdx, [rbp-48]
	lea	rcx, [rbp-48]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_S4_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L821:
	mov	rdx, QWORD PTR [rbp-104]
	mov	rax, QWORD PTR [rbp-88]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_
.LEHE174:
	jmp	.L830
.L818:
	mov	QWORD PTR [rbp-40], 0
	lea	rdx, [rbp-40]
	lea	rcx, [rbp-80]
	lea	rax, [rbp-32]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEEOT_RKS1_
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	jmp	.L830
.L828:
	jmp	.L825
.L829:
	jmp	.L825
.L827:
.L825:
	mov	rdi, rax
.LEHB175:
	call	_Unwind_Resume
.LEHE175:
.L830:
	add	rsp, 104
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2488:
	.section	.gcc_except_table
.LLSDA2488:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2488-.LLSDACSB2488
.LLSDACSB2488:
	.uleb128 .LEHB171-.LFB2488
	.uleb128 .LEHE171-.LEHB171
	.uleb128 .L827-.LFB2488
	.uleb128 0
	.uleb128 .LEHB172-.LFB2488
	.uleb128 .LEHE172-.LEHB172
	.uleb128 .L828-.LFB2488
	.uleb128 0
	.uleb128 .LEHB173-.LFB2488
	.uleb128 .LEHE173-.LEHB173
	.uleb128 .L827-.LFB2488
	.uleb128 0
	.uleb128 .LEHB174-.LFB2488
	.uleb128 .LEHE174-.LEHB174
	.uleb128 .L829-.LFB2488
	.uleb128 0
	.uleb128 .LEHB175-.LFB2488
	.uleb128 .LEHE175-.LEHB175
	.uleb128 0
	.uleb128 0
.LLSDACSE2488:
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_,comdat
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE29_M_get_insert_hint_unique_posESt23_Rb_tree_const_iteratorIS2_ERS1_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E:
.LFB2489:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E
	mov	rdx, rax
	lea	rax, [rbp-1]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2489:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E:
.LFB2490:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 72
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	cmp	QWORD PTR [rbp-64], 0
	jne	.L834
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	cmp	rax, QWORD PTR [rbp-72]
	je	.L834
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
	test	al, al
	je	.L835
.L834:
	mov	eax, 1
	jmp	.L836
.L835:
	mov	eax, 0
.L836:
	mov	BYTE PTR [rbp-33], al
	mov	rax, QWORD PTR [rbp-56]
	lea	rcx, [rax+8]
	movzx	eax, BYTE PTR [rbp-33]
	mov	rdx, QWORD PTR [rbp-72]
	mov	rsi, QWORD PTR [rbp-80]
	mov	edi, eax
	call	_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+40]
	lea	rdx, [rax+1]
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+40], rdx
	mov	rdx, QWORD PTR [rbp-80]
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-32]
	add	rsp, 72
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2490:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_insert_nodeEPSt18_Rb_tree_node_baseSA_PSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E:
.LFB2491:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2491:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC5EPSt13_Rb_tree_nodeIS2_E,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E:
.LFB2493:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2493:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E, .-_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	.set	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E,_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC2EPSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC5EPKSt13_Rb_tree_nodeIS2_E,comdat
	.align 2
	.weak	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E, @function
_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E:
.LFB2496:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2496:
	.size	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E, .-_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E
	.weak	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1EPKSt13_Rb_tree_nodeIS2_E
	.set	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1EPKSt13_Rb_tree_nodeIS2_E,_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC2EPKSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv:
.LFB2498:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2498:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv:
.LFB2499:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 8
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2499:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_:
.LFB2500:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	jmp	.L846
.L848:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
	xor	eax, 1
	test	al, al
	je	.L847
	mov	rax, QWORD PTR [rbp-32]
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-32], rax
	jmp	.L846
.L847:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-32], rax
.L846:
	cmp	QWORD PTR [rbp-32], 0
	jne	.L848
	mov	rdx, QWORD PTR [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt23_Rb_tree_const_iteratorISt4pairIKSslEEC1EPKSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2500:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base:
.LFB2501:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	lea	rax, [rbp-1]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2501:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_:
.LFB2502:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2502
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
.LEHB176:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv
.LEHE176:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv
	mov	rsi, QWORD PTR [rbp-40]
	mov	r8, r13
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB177:
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
.LEHE177:
	mov	rax, QWORD PTR [rbp-40]
	jmp	.L858
.L857:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB178:
	call	_Unwind_Resume
.LEHE178:
.L856:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB179:
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E
	call	__cxa_rethrow
.LEHE179:
.L858:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2502:
	.section	.gcc_except_table
	.align 4
.LLSDA2502:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2502-.LLSDATTD2502
.LLSDATTD2502:
	.byte	0x1
	.uleb128 .LLSDACSE2502-.LLSDACSB2502
.LLSDACSB2502:
	.uleb128 .LEHB176-.LFB2502
	.uleb128 .LEHE176-.LEHB176
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB177-.LFB2502
	.uleb128 .LEHE177-.LEHB177
	.uleb128 .L856-.LFB2502
	.uleb128 0x1
	.uleb128 .LEHB178-.LFB2502
	.uleb128 .LEHE178-.LEHB178
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB179-.LFB2502
	.uleb128 .LEHE179-.LEHB179
	.uleb128 .L857-.LFB2502
	.uleb128 0
.LLSDACSE2502:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2502:
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJOSsEESD_IJEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.set	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJOSsEESD_IJEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOSsEESD_IIEEEEEPSt13_Rb_tree_nodeIS2_EDpOT_
	.section	.text._ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_
	.type	_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_, @function
_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_:
.LFB2503:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2503:
	.size	_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_, .-_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_
	.weak	_ZNSt16allocator_traitsISaIhEE9constructIhJhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_
	.set	_ZNSt16allocator_traitsISaIhEE9constructIhJhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_,_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_
	.section	.text._ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_,"axG",@progbits,_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_
	.type	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_, @function
_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_:
.LFB2504:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2504
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	rax, QWORD PTR [rbp-56]
	mov	edx, OFFSET FLAT:.LC9
	mov	esi, 1
	mov	rdi, rax
.LEHB180:
	call	_ZNKSt6vectorIhSaIhEE12_M_check_lenEmPKc
	mov	QWORD PTR [rbp-32], rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE11_M_allocateEm
.LEHE180:
	mov	QWORD PTR [rbp-24], rax
	mov	rax, QWORD PTR [rbp-24]
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	rdx, QWORD PTR [rbp-24]
	lea	rcx, [rax+rdx]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, rbx
	mov	rsi, rcx
	mov	rdi, rax
.LEHB181:
	call	_ZNSt16allocator_traitsISaIhEE9constructIhIhEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS0_PT_DpOS3_
	mov	QWORD PTR [rbp-40], 0
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rdx, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt34__uninitialized_move_if_noexcept_aIPhS0_SaIhEET0_T_S3_S2_RT1_
.LEHE181:
	mov	QWORD PTR [rbp-40], rax
	add	QWORD PTR [rbp-40], 1
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	mov	rsi, rcx
	mov	rdi, rax
.LEHB182:
	call	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
.LEHE182:
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+16]
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax]
	sub	rdx, rax
	mov	rax, rdx
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-24]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], rdx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rax+16], rdx
	jmp	.L867
.L866:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB183:
	call	_Unwind_Resume
.LEHE183:
.L865:
	mov	rdi, rax
	call	__cxa_begin_catch
	cmp	QWORD PTR [rbp-40], 0
	jne	.L863
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNKSt6vectorIhSaIhEE4sizeEv
	mov	rdx, QWORD PTR [rbp-24]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB184:
	call	_ZNSt16allocator_traitsISaIhEE7destroyIhEEvRS0_PT_
	jmp	.L864
.L863:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt8_DestroyIPhhEvT_S1_RSaIT0_E
.L864:
	mov	rax, QWORD PTR [rbp-56]
	mov	rdx, QWORD PTR [rbp-32]
	mov	rcx, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt12_Vector_baseIhSaIhEE13_M_deallocateEPhm
	call	__cxa_rethrow
.LEHE184:
.L867:
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2504:
	.section	.gcc_except_table
	.align 4
.LLSDA2504:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2504-.LLSDATTD2504
.LLSDATTD2504:
	.byte	0x1
	.uleb128 .LLSDACSE2504-.LLSDACSB2504
.LLSDACSB2504:
	.uleb128 .LEHB180-.LFB2504
	.uleb128 .LEHE180-.LEHB180
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB181-.LFB2504
	.uleb128 .LEHE181-.LEHB181
	.uleb128 .L865-.LFB2504
	.uleb128 0x1
	.uleb128 .LEHB182-.LFB2504
	.uleb128 .LEHE182-.LEHB182
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB183-.LFB2504
	.uleb128 .LEHE183-.LEHB183
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB184-.LFB2504
	.uleb128 .LEHE184-.LEHB184
	.uleb128 .L866-.LFB2504
	.uleb128 0
.LLSDACSE2504:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2504:
	.section	.text._ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_,"axG",@progbits,_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_,comdat
	.size	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_, .-_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_
	.weak	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIJhEEEvDpOT_
	.set	_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIJhEEEvDpOT_,_ZNSt6vectorIhSaIhEE19_M_emplace_back_auxIIhEEEvDpOT_
	.section	.text._ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_,"axG",@progbits,_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC5ERKS0_,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_
	.type	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_, @function
_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_:
.LFB2506:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSaIhEC2ERKS_
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+16], 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2506:
	.size	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_, .-_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_
	.weak	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC1ERKS0_
	.set	_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC1ERKS0_,_ZNSt12_Vector_baseIhSaIhEE12_Vector_implC2ERKS0_
	.section	.text._ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_,"axG",@progbits,_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_,comdat
	.weak	_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_
	.type	_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_, @function
_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_:
.LFB2508:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	lea	rax, [rbp-40]
	mov	rdi, rax
	call	_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-48]
	mov	BYTE PTR [rsp], bl
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2508:
	.size	_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_, .-_ZSt8distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_
	.section	.text._ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E,"axG",@progbits,_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E,comdat
	.weak	_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E
	.type	_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E, @function
_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E:
.LFB2509:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	QWORD PTR [rbp-32], rcx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2509:
	.size	_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E, .-_ZSt22__uninitialized_copy_aIPKhPhhET0_T_S4_S3_RSaIT1_E
	.section	.text._ZNSt6vectorIhSaIhEE5beginEv,"axG",@progbits,_ZNSt6vectorIhSaIhEE5beginEv,comdat
	.align 2
	.weak	_ZNSt6vectorIhSaIhEE5beginEv
	.type	_ZNSt6vectorIhSaIhEE5beginEv, @function
_ZNSt6vectorIhSaIhEE5beginEv:
.LFB2510:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rdx, QWORD PTR [rbp-24]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC1ERKS1_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2510:
	.size	_ZNSt6vectorIhSaIhEE5beginEv, .-_ZNSt6vectorIhSaIhEE5beginEv
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv:
.LFB2511:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2511:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEdeEv
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_:
.LFB2512:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	mov	rsi, rax
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, rdx
	mov	rdx, rbx
	mov	rdi, rax
	call	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2512:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11lower_boundERS1_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_:
.LFB2513:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2513
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
.LEHB185:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv
.LEHE185:
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv
	mov	rsi, QWORD PTR [rbp-40]
	mov	r8, r13
	mov	rcx, r12
	mov	rdx, rbx
	mov	rdi, rax
.LEHB186:
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
.LEHE186:
	mov	rax, QWORD PTR [rbp-40]
	jmp	.L885
.L884:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB187:
	call	_Unwind_Resume
.LEHE187:
.L883:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB188:
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E
	call	__cxa_rethrow
.LEHE188:
.L885:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2513:
	.section	.gcc_except_table
	.align 4
.LLSDA2513:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2513-.LLSDATTD2513
.LLSDATTD2513:
	.byte	0x1
	.uleb128 .LLSDACSE2513-.LLSDACSB2513
.LLSDACSB2513:
	.uleb128 .LEHB185-.LFB2513
	.uleb128 .LEHE185-.LEHB185
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB186-.LFB2513
	.uleb128 .LEHE186-.LEHB186
	.uleb128 .L883-.LFB2513
	.uleb128 0x1
	.uleb128 .LEHB187-.LFB2513
	.uleb128 .LEHE187-.LEHB187
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB188-.LFB2513
	.uleb128 .LEHE188-.LEHB188
	.uleb128 .L884-.LFB2513
	.uleb128 0
.LLSDACSE2513:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2513:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJOS1_EESE_IJEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.set	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIJRKSt21piecewise_construct_tSt5tupleIJOS1_EESE_IJEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_create_nodeIIRKSt21piecewise_construct_tSt5tupleIIOS1_EESE_IIEEEEEPSt13_Rb_tree_nodeIS3_EDpOT_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_
	.type	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_, @function
_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_:
.LFB2516:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKhEOT_RNSt16remove_referenceIS2_E4typeE
	movzx	ebx, BYTE PTR [rax]
	mov	rax, QWORD PTR [rbp-32]
	mov	rsi, rax
	mov	edi, 1
	call	_ZnwmPv
	test	rax, rax
	je	.L886
	mov	BYTE PTR [rax], bl
.L886:
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2516:
	.size	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_, .-_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_
	.weak	_ZN9__gnu_cxx13new_allocatorIhE9constructIhJRKhEEEvPT_DpOT0_
	.set	_ZN9__gnu_cxx13new_allocatorIhE9constructIhJRKhEEEvPT_DpOT0_,_ZN9__gnu_cxx13new_allocatorIhE9constructIhIRKhEEEvPT_DpOT0_
	.section	.text._ZNKSt6vectorIhSaIhEE8max_sizeEv,"axG",@progbits,_ZNKSt6vectorIhSaIhEE8max_sizeEv,comdat
	.align 2
	.weak	_ZNKSt6vectorIhSaIhEE8max_sizeEv
	.type	_ZNKSt6vectorIhSaIhEE8max_sizeEv, @function
_ZNKSt6vectorIhSaIhEE8max_sizeEv:
.LFB2517:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2517
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2517:
	.section	.gcc_except_table
.LLSDA2517:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2517-.LLSDACSB2517
.LLSDACSB2517:
.LLSDACSE2517:
	.section	.text._ZNKSt6vectorIhSaIhEE8max_sizeEv,"axG",@progbits,_ZNKSt6vectorIhSaIhEE8max_sizeEv,comdat
	.size	_ZNKSt6vectorIhSaIhEE8max_sizeEv, .-_ZNKSt6vectorIhSaIhEE8max_sizeEv
	.section	.text._ZSt3maxImERKT_S2_S2_,"axG",@progbits,_ZSt3maxImERKT_S2_S2_,comdat
	.weak	_ZSt3maxImERKT_S2_S2_
	.type	_ZSt3maxImERKT_S2_S2_, @function
_ZSt3maxImERKT_S2_S2_:
.LFB2518:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rax]
	cmp	rdx, rax
	jae	.L892
	mov	rax, QWORD PTR [rbp-16]
	jmp	.L893
.L892:
	mov	rax, QWORD PTR [rbp-8]
.L893:
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2518:
	.size	_ZSt3maxImERKT_S2_S2_, .-_ZSt3maxImERKT_S2_S2_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv
	.type	_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv, @function
_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv:
.LFB2519:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv
	cmp	rax, QWORD PTR [rbp-16]
	setb	al
	test	al, al
	je	.L895
	call	_ZSt17__throw_bad_allocv
.L895:
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_Znwm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2519:
	.size	_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv, .-_ZN9__gnu_cxx13new_allocatorIhE8allocateEmPKv
	.section	.text._ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_,"axG",@progbits,_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_,comdat
	.weak	_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_
	.type	_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_, @function
_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_:
.LFB2520:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rdx, QWORD PTR [rbp-24]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt13move_iteratorIPhEC1ES0_
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2520:
	.size	_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_, .-_ZSt32__make_move_if_noexcept_iteratorIPhSt13move_iteratorIS0_EET0_T_
	.section	.text._ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E,"axG",@progbits,_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E,comdat
	.weak	_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E
	.type	_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E, @function
_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E:
.LFB2521:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	QWORD PTR [rbp-8], rcx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2521:
	.size	_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E, .-_ZSt22__uninitialized_copy_aISt13move_iteratorIPhES1_hET0_T_S4_S3_RSaIT1_E
	.section	.text._ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_
	.type	_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_, @function
_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_:
.LFB2522:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2522:
	.size	_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_, .-_ZNSt16allocator_traitsISaIhEE10_S_destroyIhEENSt9enable_ifIXsrNS1_16__destroy_helperIT_EE5valueEvE4typeERS0_PS5_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm
	.type	_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm, @function
_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm:
.LFB2523:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2523:
	.size	_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm, .-_ZN9__gnu_cxx13new_allocatorIhE10deallocateEPhm
	.section	.text._ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev,"axG",@progbits,_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC5Ev,comdat
	.align 2
	.weak	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev
	.type	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev, @function
_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev:
.LFB2525:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2525:
	.size	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev, .-_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev
	.weak	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC1Ev
	.set	_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC1Ev,_ZNSaISt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEEC2Ev
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv:
.LFB2527:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+16], 0
	mov	rax, QWORD PTR [rbp-8]
	lea	rdx, [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+24], rdx
	mov	rax, QWORD PTR [rbp-8]
	lea	rdx, [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+32], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2527:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE13_Rb_tree_implIS7_Lb1EE13_M_initializeEv
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv:
.LFB2528:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2528:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE21_M_get_Node_allocatorEv
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED5Ev,comdat
	.align 2
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev
	.type	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev, @function
_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev:
.LFB2531:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	mov	rdi, rax
	call	_ZNSt4pairIKS_ISsjESsED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2531:
	.size	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev, .-_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED1Ev
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED1Ev,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED2Ev
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_:
.LFB2529:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2529:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE7destroyIS6_EEvPT_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E:
.LFB2533:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rbp-16]
	mov	edx, 1
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2533:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNSaI11InstructionEC2Ev,"axG",@progbits,_ZNSaI11InstructionEC5Ev,comdat
	.align 2
	.weak	_ZNSaI11InstructionEC2Ev
	.type	_ZNSaI11InstructionEC2Ev, @function
_ZNSaI11InstructionEC2Ev:
.LFB2535:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2535:
	.size	_ZNSaI11InstructionEC2Ev, .-_ZNSaI11InstructionEC2Ev
	.weak	_ZNSaI11InstructionEC1Ev
	.set	_ZNSaI11InstructionEC1Ev,_ZNSaI11InstructionEC2Ev
	.section	.text._ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorI11InstructionED5Ev,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev
	.type	_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev, @function
_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev:
.LFB2538:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2538:
	.size	_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev, .-_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev
	.weak	_ZN9__gnu_cxx13new_allocatorI11InstructionED1Ev
	.set	_ZN9__gnu_cxx13new_allocatorI11InstructionED1Ev,_ZN9__gnu_cxx13new_allocatorI11InstructionED2Ev
	.section	.text._ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_,"axG",@progbits,_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_,comdat
	.weak	_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_
	.type	_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_, @function
_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_:
.LFB2540:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	jmp	.L915
.L916:
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZSt11__addressofI11InstructionEPT_RS1_
	mov	rdi, rax
	call	_ZSt8_DestroyI11InstructionEvPT_
	add	QWORD PTR [rbp-8], 16
.L915:
	mov	rax, QWORD PTR [rbp-8]
	cmp	rax, QWORD PTR [rbp-16]
	jne	.L916
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2540:
	.size	_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_, .-_ZNSt12_Destroy_auxILb0EE9__destroyIP11InstructionEEvT_S4_
	.section	.text._ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_,"axG",@progbits,_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_,comdat
	.weak	_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_
	.type	_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_, @function
_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_:
.LFB2541:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2541:
	.size	_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_, .-_ZNSt12_Destroy_auxILb1EE9__destroyIPhEEvT_S3_
	.section	.text._ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv
	.type	_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv, @function
_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv:
.LFB2542:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv
	cmp	rax, QWORD PTR [rbp-16]
	setb	al
	test	al, al
	je	.L919
	call	_ZSt17__throw_bad_allocv
.L919:
	mov	rax, QWORD PTR [rbp-16]
	sal	rax, 4
	mov	rdi, rax
	call	_Znwm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2542:
	.size	_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv, .-_ZN9__gnu_cxx13new_allocatorI11InstructionE8allocateEmPKv
	.section	.text._ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_,"axG",@progbits,_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_,comdat
	.weak	_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_
	.type	_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_, @function
_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_:
.LFB2543:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2543:
	.size	_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_, .-_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEPS2_ET0_T_SB_SA_
	.section	.text._ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_,"axG",@progbits,_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_,comdat
	.weak	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_
	.type	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_, @function
_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_:
.LFB2544:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-16], rdi
	mov	rax, QWORD PTR [rbp-16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2544:
	.size	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_, .-_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb0EE7_S_baseES8_
	.section	.text._ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_,"axG",@progbits,_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_,comdat
	.weak	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_
	.type	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_, @function
_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_:
.LFB2545:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2545:
	.size	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_, .-_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeESA_
	.section	.text._ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_,"axG",@progbits,_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_,comdat
	.weak	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_
	.type	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_, @function
_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_:
.LFB2546:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2546:
	.size	_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_, .-_ZSt12__niter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEEENSt11_Niter_baseIT_E13iterator_typeES9_
	.section	.text._ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_,"axG",@progbits,_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_,comdat
	.weak	_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_
	.type	_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_, @function
_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_:
.LFB2547:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	BYTE PTR [rbp-1], 0
	mov	rdx, QWORD PTR [rbp-40]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2547:
	.size	_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_, .-_ZSt13__copy_move_aILb0EPK11InstructionPS0_ET1_T0_S5_S4_
	.section	.text._ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_,"axG",@progbits,_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_,comdat
	.weak	_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_
	.type	_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_, @function
_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_:
.LFB2548:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	jmp	.L932
.L933:
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	mov	rdi, rax
	call	_ZSt11__addressofI11InstructionEPT_RS1_
	mov	rdi, rax
	call	_ZSt8_DestroyI11InstructionEvPT_
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEEppEv
.L932:
	lea	rdx, [rbp-32]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxxneIP11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESB_
	test	al, al
	jne	.L933
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2548:
	.size	_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_, .-_ZNSt12_Destroy_auxILb0EE9__destroyIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS4_SaIS4_EEEEEEvT_SA_
	.section	.text._ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_,"axG",@progbits,_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_,comdat
	.weak	_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_
	.type	_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_, @function
_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_:
.LFB2549:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2549:
	.size	_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_, .-_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_
	.section	.text._ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_,"axG",@progbits,_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_,comdat
	.weak	_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_
	.type	_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_, @function
_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_:
.LFB2550:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIP11InstructionLb0EE7_S_baseES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2550:
	.size	_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_, .-_ZSt12__niter_baseIP11InstructionENSt11_Niter_baseIT_E13iterator_typeES3_
	.section	.text._ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_,"axG",@progbits,_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_,comdat
	.weak	_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_
	.type	_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_, @function
_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_:
.LFB2551:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	BYTE PTR [rbp-1], 0
	mov	rdx, QWORD PTR [rbp-40]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2551:
	.size	_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_, .-_ZSt13__copy_move_aILb0EP11InstructionS1_ET1_T0_S3_S2_
	.section	.text._ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_,"axG",@progbits,_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_,comdat
	.weak	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_
	.type	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_, @function
_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_:
.LFB2552:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2552
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rbp-24], rax
	jmp	.L941
.L942:
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt11__addressofI11InstructionEPT_RS1_
	mov	rdx, QWORD PTR [rbp-40]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB189:
	call	_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_
.LEHE189:
	add	QWORD PTR [rbp-40], 16
	add	QWORD PTR [rbp-24], 16
.L941:
	mov	rax, QWORD PTR [rbp-40]
	cmp	rax, QWORD PTR [rbp-48]
	jne	.L942
	mov	rax, QWORD PTR [rbp-24]
	jmp	.L948
.L947:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB190:
	call	_Unwind_Resume
.LEHE190:
.L946:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB191:
	call	_ZSt8_DestroyIP11InstructionEvT_S2_
	call	__cxa_rethrow
.LEHE191:
.L948:
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2552:
	.section	.gcc_except_table
	.align 4
.LLSDA2552:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2552-.LLSDATTD2552
.LLSDATTD2552:
	.byte	0x1
	.uleb128 .LLSDACSE2552-.LLSDACSB2552
.LLSDACSB2552:
	.uleb128 .LEHB189-.LFB2552
	.uleb128 .LEHE189-.LEHB189
	.uleb128 .L946-.LFB2552
	.uleb128 0x1
	.uleb128 .LEHB190-.LFB2552
	.uleb128 .LEHE190-.LEHB190
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB191-.LFB2552
	.uleb128 .LEHE191-.LEHB191
	.uleb128 .L947-.LFB2552
	.uleb128 0
.LLSDACSE2552:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2552:
	.section	.text._ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_,"axG",@progbits,_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_,comdat
	.size	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_, .-_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIP11InstructionS3_EET0_T_S5_S4_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv:
.LFB2553:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 8
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2553:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_:
.LFB2554:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	jmp	.L952
.L954:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	xor	eax, 1
	test	al, al
	je	.L953
	mov	rax, QWORD PTR [rbp-32]
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-32], rax
	jmp	.L952
.L953:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-32], rax
.L952:
	cmp	QWORD PTR [rbp-32], 0
	jne	.L954
	mov	rdx, QWORD PTR [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2554:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS3_ESC_RS2_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv:
.LFB2556:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 0
	mov	esi, 1
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2556:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_get_nodeEv
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_:
.LFB2557:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2557:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJRS3_EESC_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJRS3_EESC_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.section	.text._ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv,"axG",@progbits,_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv,comdat
	.align 2
	.weak	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv
	.type	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv, @function
_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv:
.LFB2558:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2558:
	.size	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv, .-_ZNKSt23_Rb_tree_const_iteratorISt4pairIKS0_ISsjESsEE13_M_const_castEv
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv:
.LFB2559:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2559:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE12_M_rightmostEv
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base:
.LFB2560:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base
	mov	rdx, rax
	lea	rax, [rbp-1]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2560:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	.section	.text._ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv,"axG",@progbits,_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv
	.type	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv, @function
_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv:
.LFB2561:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+40]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2561:
	.size	_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv, .-_ZNKSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE4sizeEv
	.section	.text._ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE,"axG",@progbits,_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE,comdat
	.weak	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE
	.type	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE, @function
_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE:
.LFB2564:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2564:
	.size	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE, .-_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE
	.section	.text._ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_,"axG",@progbits,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC5IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_,comdat
	.align 2
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_
	.type	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_, @function
_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_:
.LFB2565:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEOT_RNSt16remove_referenceIS8_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2565:
	.size	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_, .-_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_
	.set	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_:
.LFB2562:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2562
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 80
	mov	QWORD PTR [rbp-72], rdi
	mov	QWORD PTR [rbp-80], rsi
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_M_beginEv
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_M_endEv
	mov	QWORD PTR [rbp-32], rax
	mov	BYTE PTR [rbp-49], 1
	jmp	.L971
.L974:
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rbp-32], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt13_Rb_tree_nodeIS3_E
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rcx, QWORD PTR [rbp-80]
	mov	rsi, rcx
	mov	rdi, rax
.LEHB192:
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
	mov	BYTE PTR [rbp-49], al
	cmp	BYTE PTR [rbp-49], 0
	je	.L972
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE7_S_leftEPSt18_Rb_tree_node_base
	jmp	.L973
.L972:
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_rightEPSt18_Rb_tree_node_base
.L973:
	mov	QWORD PTR [rbp-40], rax
.L971:
	mov	rax, QWORD PTR [rbp-40]
	test	rax, rax
	jne	.L974
	mov	rdx, QWORD PTR [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEC1EPSt13_Rb_tree_nodeIS3_E
	cmp	BYTE PTR [rbp-49], 0
	je	.L975
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE5beginEv
	mov	QWORD PTR [rbp-16], rax
	lea	rdx, [rbp-16]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEeqERKS4_
	test	al, al
	je	.L976
	lea	rdx, [rbp-32]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rbp-8]
	jmp	.L982
.L976:
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv
.L975:
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdx, QWORD PTR [rbp-80]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISt4pairISsjEEclERKS1_S4_
.LEHE192:
	test	al, al
	je	.L978
	lea	rdx, [rbp-32]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKS_ISsjESsEESA_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rbp-8]
	jmp	.L982
.L978:
	mov	QWORD PTR [rbp-24], 0
	lea	rdx, [rbp-24]
	lea	rcx, [rbp-48]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEEOT_RKS1_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rbp-8]
	jmp	.L982
.L981:
	mov	rdi, rax
.LEHB193:
	call	_Unwind_Resume
.LEHE193:
.L982:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2562:
	.section	.gcc_except_table
.LLSDA2562:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2562-.LLSDACSB2562
.LLSDACSB2562:
	.uleb128 .LEHB192-.LFB2562
	.uleb128 .LEHE192-.LEHB192
	.uleb128 .L981-.LFB2562
	.uleb128 0
	.uleb128 .LEHB193-.LFB2562
	.uleb128 .LEHE193-.LEHB193
	.uleb128 0
	.uleb128 0
.LLSDACSE2562:
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_,comdat
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE24_M_get_insert_unique_posERS2_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv:
.LFB2567:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 24
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2567:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE11_M_leftmostEv
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv:
.LFB2568:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2568:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv, .-_ZNSt17_Rb_tree_iteratorISt4pairIKS0_ISsjESsEEmmEv
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E,comdat
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E:
.LFB2569:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2569:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt13_Rb_tree_nodeIS3_E
	.section	.text._ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_,"axG",@progbits,_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_,comdat
	.align 2
	.weak	_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_
	.type	_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_, @function
_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_:
.LFB2570:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2570:
	.size	_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_, .-_ZNKSt10_Select1stISt4pairIKS0_ISsjESsEEclERKS3_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv:
.LFB2571:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2571:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv:
.LFB2572:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 8
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2572:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_:
.LFB2573:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	jmp	.L996
.L998:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rbp-48]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
	xor	eax, 1
	test	al, al
	je	.L997
	mov	rax, QWORD PTR [rbp-32]
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-32], rax
	jmp	.L996
.L997:
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base
	mov	QWORD PTR [rbp-32], rax
.L996:
	cmp	QWORD PTR [rbp-32], 0
	jne	.L998
	mov	rdx, QWORD PTR [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2573:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv:
.LFB2574:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 0
	mov	esi, 1
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2574:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_get_nodeEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv:
.LFB2575:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2575:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE21_M_get_Node_allocatorEv
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_:
.LFB2576:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2576:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_JRKSt21piecewise_construct_tSt5tupleIJRS2_EESB_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_JRKSt21piecewise_construct_tSt5tupleIJRS2_EESB_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E:
.LFB2577:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rcx, QWORD PTR [rbp-16]
	mov	edx, 1
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2577:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv,"axG",@progbits,_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv,comdat
	.align 2
	.weak	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv
	.type	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv, @function
_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv:
.LFB2578:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2578:
	.size	_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv, .-_ZNKSt23_Rb_tree_const_iteratorISt4pairIKSslEE13_M_const_castEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv:
.LFB2579:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2579:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE12_M_rightmostEv
	.section	.text._ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv,"axG",@progbits,_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv,comdat
	.align 2
	.weak	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv
	.type	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv, @function
_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv:
.LFB2580:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+40]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2580:
	.size	_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv, .-_ZNKSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE4sizeEv
	.section	.text._ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE,"axG",@progbits,_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE,comdat
	.weak	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE
	.type	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE, @function
_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE:
.LFB2583:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2583:
	.size	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE, .-_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE
	.section	.text._ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_,"axG",@progbits,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC5IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_,comdat
	.align 2
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_
	.type	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_, @function
_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_:
.LFB2584:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIRPSt13_Rb_tree_nodeISt4pairIKSslEEEOT_RNSt16remove_referenceIS7_E4typeE
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2584:
	.size	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_, .-_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_
	.weak	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_
	.set	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_,_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC2IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_:
.LFB2581:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2581
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 80
	mov	QWORD PTR [rbp-72], rdi
	mov	QWORD PTR [rbp-80], rsi
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_M_beginEv
	mov	QWORD PTR [rbp-40], rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_M_endEv
	mov	QWORD PTR [rbp-32], rax
	mov	BYTE PTR [rbp-49], 1
	jmp	.L1016
.L1019:
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rbp-32], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rcx, QWORD PTR [rbp-80]
	mov	rsi, rcx
	mov	rdi, rax
.LEHB194:
	call	_ZNKSt4lessISsEclERKSsS2_
	mov	BYTE PTR [rbp-49], al
	cmp	BYTE PTR [rbp-49], 0
	je	.L1017
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base
	jmp	.L1018
.L1017:
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base
.L1018:
	mov	QWORD PTR [rbp-40], rax
.L1016:
	mov	rax, QWORD PTR [rbp-40]
	test	rax, rax
	jne	.L1019
	mov	rdx, QWORD PTR [rbp-32]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	cmp	BYTE PTR [rbp-49], 0
	je	.L1020
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv
	mov	QWORD PTR [rbp-16], rax
	lea	rdx, [rbp-16]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNKSt17_Rb_tree_iteratorISt4pairIKSslEEeqERKS3_
	test	al, al
	je	.L1021
	lea	rdx, [rbp-32]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rbp-8]
	jmp	.L1027
.L1021:
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv
.L1020:
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base
	mov	rcx, rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdx, QWORD PTR [rbp-80]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNKSt4lessISsEclERKSsS2_
.LEHE194:
	test	al, al
	je	.L1023
	lea	rdx, [rbp-32]
	lea	rcx, [rbp-40]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRPSt13_Rb_tree_nodeIS_IKSslEES9_vEEOT_OT0_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rbp-8]
	jmp	.L1027
.L1023:
	mov	QWORD PTR [rbp-24], 0
	lea	rdx, [rbp-24]
	lea	rcx, [rbp-48]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIPSt18_Rb_tree_node_baseS1_EC1IRS1_vEEOT_RKS1_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rbp-8]
	jmp	.L1027
.L1026:
	mov	rdi, rax
.LEHB195:
	call	_Unwind_Resume
.LEHE195:
.L1027:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2581:
	.section	.gcc_except_table
.LLSDA2581:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2581-.LLSDACSB2581
.LLSDACSB2581:
	.uleb128 .LEHB194-.LFB2581
	.uleb128 .LEHE194-.LEHB194
	.uleb128 .L1026-.LFB2581
	.uleb128 0
	.uleb128 .LEHB195-.LFB2581
	.uleb128 .LEHE195-.LEHB195
	.uleb128 0
	.uleb128 0
.LLSDACSE2581:
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_,comdat
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE24_M_get_insert_unique_posERS1_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv:
.LFB2586:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 24
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2586:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE11_M_leftmostEv
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv:
.LFB2587:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2587:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv, .-_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEmmEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base:
.LFB2588:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+24]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2588:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base
	.section	.text._ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv,"axG",@progbits,_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv,comdat
	.align 2
	.weak	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv
	.type	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv, @function
_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv:
.LFB2589:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
	call	_ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2589:
	.size	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv, .-_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEppEv
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E:
.LFB2590:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2590:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E
	.section	.text._ZNKSt10_Select1stISt4pairIKSslEEclERKS2_,"axG",@progbits,_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_,comdat
	.align 2
	.weak	_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_
	.type	_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_, @function
_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_:
.LFB2591:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2591:
	.size	_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_, .-_ZNKSt10_Select1stISt4pairIKSslEEclERKS2_
	.section	.text._ZNSt4pairIKSslED2Ev,"axG",@progbits,_ZNSt4pairIKSslED5Ev,comdat
	.align 2
	.weak	_ZNSt4pairIKSslED2Ev
	.type	_ZNSt4pairIKSslED2Ev, @function
_ZNSt4pairIKSslED2Ev:
.LFB2595:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSsD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2595:
	.size	_ZNSt4pairIKSslED2Ev, .-_ZNSt4pairIKSslED2Ev
	.weak	_ZNSt4pairIKSslED1Ev
	.set	_ZNSt4pairIKSslED1Ev,_ZNSt4pairIKSslED2Ev
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKSslEED5Ev,comdat
	.align 2
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev
	.type	_ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev, @function
_ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev:
.LFB2597:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	mov	rdi, rax
	call	_ZNSt4pairIKSslED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2597:
	.size	_ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev, .-_ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEED1Ev
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEED1Ev,_ZNSt13_Rb_tree_nodeISt4pairIKSslEED2Ev
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_:
.LFB2592:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt13_Rb_tree_nodeISt4pairIKSslEED1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2592:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE7destroyIS5_EEvPT_
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base:
.LFB2599:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2599:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base:
.LFB2600:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+24]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2600:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base:
.LFB2601:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2601:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_:
.LFB2602:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2602:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_JRKSt21piecewise_construct_tSt5tupleIJOSsEESB_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_JRKSt21piecewise_construct_tSt5tupleIJOSsEESB_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE9constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS5_PT_DpOSF_
	.section	.text._ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_
	.type	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_, @function
_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_:
.LFB2603:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2603:
	.size	_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_, .-_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_
	.weak	_ZNSt16allocator_traitsISaIhEE12_S_constructIhJhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_
	.set	_ZNSt16allocator_traitsISaIhEE12_S_constructIhJhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_,_ZNSt16allocator_traitsISaIhEE12_S_constructIhIhEEENSt9enable_ifIXsrNS1_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS0_PS5_DpOS6_
	.section	.text._ZNSaIhEC2ERKS_,"axG",@progbits,_ZNSaIhEC5ERKS_,comdat
	.align 2
	.weak	_ZNSaIhEC2ERKS_
	.type	_ZNSaIhEC2ERKS_, @function
_ZNSaIhEC2ERKS_:
.LFB2605:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2605:
	.size	_ZNSaIhEC2ERKS_, .-_ZNSaIhEC2ERKS_
	.weak	_ZNSaIhEC1ERKS_
	.set	_ZNSaIhEC1ERKS_,_ZNSaIhEC2ERKS_
	.section	.text._ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_,"axG",@progbits,_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_,comdat
	.weak	_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_
	.type	_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_, @function
_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_:
.LFB2607:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2607:
	.size	_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_, .-_ZSt19__iterator_categoryIPKhENSt15iterator_traitsIT_E17iterator_categoryERKS3_
	.section	.text._ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag,"axG",@progbits,_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag,comdat
	.weak	_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag
	.type	_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag, @function
_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag:
.LFB2608:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	sub	rdx, rax
	mov	rax, rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2608:
	.size	_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag, .-_ZSt10__distanceIPKhENSt15iterator_traitsIT_E15difference_typeES3_S3_St26random_access_iterator_tag
	.section	.text._ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_,"axG",@progbits,_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_,comdat
	.weak	_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_
	.type	_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_, @function
_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_:
.LFB2609:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2609:
	.size	_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_, .-_ZSt18uninitialized_copyIPKhPhET0_T_S4_S3_
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC5ERKS1_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_
	.type	_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_, @function
_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_:
.LFB2611:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2611:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_, .-_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC1ERKS1_
	.set	_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC1ERKS1_,_ZN9__gnu_cxx17__normal_iteratorIPhSt6vectorIhSaIhEEEC2ERKS1_
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_:
.LFB2613:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2613:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJOS2_EESC_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJOS2_EESC_IJEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEEDTcl12_S_constructfp_fp0_spcl7forwardIT0_Efp1_EEERS6_PT_DpOSG_
	.section	.text._ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_
	.type	_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_, @function
_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_:
.LFB2616:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2616:
	.size	_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_, .-_ZNSt16allocator_traitsISaIhEE8max_sizeERKS0_
	.section	.text._ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv,"axG",@progbits,_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv,comdat
	.align 2
	.weak	_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	.type	_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv, @function
_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv:
.LFB2617:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2617:
	.size	_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv, .-_ZNKSt12_Vector_baseIhSaIhEE19_M_get_Tp_allocatorEv
	.section	.text._ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv,"axG",@progbits,_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv
	.type	_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv, @function
_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv:
.LFB2618:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, -1
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2618:
	.size	_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv, .-_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv
	.section	.text._ZNSt13move_iteratorIPhEC2ES0_,"axG",@progbits,_ZNSt13move_iteratorIPhEC5ES0_,comdat
	.align 2
	.weak	_ZNSt13move_iteratorIPhEC2ES0_
	.type	_ZNSt13move_iteratorIPhEC2ES0_, @function
_ZNSt13move_iteratorIPhEC2ES0_:
.LFB2620:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2620:
	.size	_ZNSt13move_iteratorIPhEC2ES0_, .-_ZNSt13move_iteratorIPhEC2ES0_
	.weak	_ZNSt13move_iteratorIPhEC1ES0_
	.set	_ZNSt13move_iteratorIPhEC1ES0_,_ZNSt13move_iteratorIPhEC2ES0_
	.section	.text._ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_,"axG",@progbits,_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_,comdat
	.weak	_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_
	.type	_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_, @function
_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_:
.LFB2622:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2622:
	.size	_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_, .-_ZSt18uninitialized_copyISt13move_iteratorIPhES1_ET0_T_S4_S3_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_
	.type	_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_, @function
_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_:
.LFB2623:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2623:
	.size	_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_, .-_ZN9__gnu_cxx13new_allocatorIhE7destroyIhEEvPT_
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC5Ev,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev:
.LFB2625:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2625:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC1Ev
	.set	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC1Ev,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEEC2Ev
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m:
.LFB2627:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2627:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE10deallocateEPS6_m
	.section	.text._ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorI11InstructionEC5Ev,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev
	.type	_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev, @function
_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev:
.LFB2629:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2629:
	.size	_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev, .-_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev
	.weak	_ZN9__gnu_cxx13new_allocatorI11InstructionEC1Ev
	.set	_ZN9__gnu_cxx13new_allocatorI11InstructionEC1Ev,_ZN9__gnu_cxx13new_allocatorI11InstructionEC2Ev
	.section	.text._ZSt11__addressofI11InstructionEPT_RS1_,"axG",@progbits,_ZSt11__addressofI11InstructionEPT_RS1_,comdat
	.weak	_ZSt11__addressofI11InstructionEPT_RS1_
	.type	_ZSt11__addressofI11InstructionEPT_RS1_, @function
_ZSt11__addressofI11InstructionEPT_RS1_:
.LFB2631:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2631:
	.size	_ZSt11__addressofI11InstructionEPT_RS1_, .-_ZSt11__addressofI11InstructionEPT_RS1_
	.section	.text._ZSt8_DestroyI11InstructionEvPT_,"axG",@progbits,_ZSt8_DestroyI11InstructionEvPT_,comdat
	.weak	_ZSt8_DestroyI11InstructionEvPT_
	.type	_ZSt8_DestroyI11InstructionEvPT_, @function
_ZSt8_DestroyI11InstructionEvPT_:
.LFB2632:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZN11InstructionD1Ev
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2632:
	.size	_ZSt8_DestroyI11InstructionEvPT_, .-_ZSt8_DestroyI11InstructionEvPT_
	.section	.text._ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv,"axG",@progbits,_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv
	.type	_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv, @function
_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv:
.LFB2633:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	movabs	rax, 1152921504606846975
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2633:
	.size	_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv, .-_ZNK9__gnu_cxx13new_allocatorI11InstructionE8max_sizeEv
	.section	.text._ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_,"axG",@progbits,_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_,comdat
	.weak	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_
	.type	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_, @function
_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_:
.LFB2634:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2634
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 56
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-48], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rbp-24], rax
	jmp	.L1081
.L1082:
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt11__addressofI11InstructionEPT_RS1_
	mov	rsi, rbx
	mov	rdi, rax
.LEHB196:
	call	_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv
	add	QWORD PTR [rbp-24], 16
.L1081:
	lea	rdx, [rbp-64]
	lea	rax, [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_
.LEHE196:
	test	al, al
	jne	.L1082
	mov	rax, QWORD PTR [rbp-24]
	jmp	.L1088
.L1087:
	mov	rbx, rax
	call	__cxa_end_catch
	mov	rax, rbx
	mov	rdi, rax
.LEHB197:
	call	_Unwind_Resume
.LEHE197:
.L1086:
	mov	rdi, rax
	call	__cxa_begin_catch
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-56]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB198:
	call	_ZSt8_DestroyIP11InstructionEvT_S2_
	call	__cxa_rethrow
.LEHE198:
.L1088:
	add	rsp, 56
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2634:
	.section	.gcc_except_table
	.align 4
.LLSDA2634:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT2634-.LLSDATTD2634
.LLSDATTD2634:
	.byte	0x1
	.uleb128 .LLSDACSE2634-.LLSDACSB2634
.LLSDACSB2634:
	.uleb128 .LEHB196-.LFB2634
	.uleb128 .LEHE196-.LEHB196
	.uleb128 .L1086-.LFB2634
	.uleb128 0x1
	.uleb128 .LEHB197-.LFB2634
	.uleb128 .LEHE197-.LEHB197
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB198-.LFB2634
	.uleb128 .LEHE198-.LEHB198
	.uleb128 .L1087-.LFB2634
	.uleb128 0
.LLSDACSE2634:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT2634:
	.section	.text._ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_,"axG",@progbits,_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_,comdat
	.size	_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_, .-_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS4_SaIS4_EEEEPS4_EET0_T_SD_SC_
	.section	.text._ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_,"axG",@progbits,_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_,comdat
	.weak	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_
	.type	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_, @function
_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_:
.LFB2635:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	mov	rax, QWORD PTR [rax]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2635:
	.size	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_, .-_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES8_
	.section	.text._ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_,"axG",@progbits,_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_,comdat
	.weak	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_
	.type	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_, @function
_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_:
.LFB2636:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	mov	rax, QWORD PTR [rax]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2636:
	.size	_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_, .-_ZNSt10_Iter_baseIN9__gnu_cxx17__normal_iteratorIP11InstructionSt6vectorIS2_SaIS2_EEEELb1EE7_S_baseES7_
	.section	.text._ZN11InstructionaSERKS_,"axG",@progbits,_ZN11InstructionaSERKS_,comdat
	.align 2
	.weak	_ZN11InstructionaSERKS_
	.type	_ZN11InstructionaSERKS_, @function
_ZN11InstructionaSERKS_:
.LFB2638:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax], edx
	mov	rax, QWORD PTR [rbp-16]
	mov	edx, DWORD PTR [rax+4]
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+4], edx
	mov	rax, QWORD PTR [rbp-16]
	lea	rdx, [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 8
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsaSERKSs
	mov	rax, QWORD PTR [rbp-8]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2638:
	.size	_ZN11InstructionaSERKS_, .-_ZN11InstructionaSERKS_
	.section	.text._ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_,"axG",@progbits,_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_,comdat
	.weak	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_
	.type	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_, @function
_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_:
.LFB2637:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	mov	QWORD PTR [rbp-8], rax
	jmp	.L1096
.L1097:
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN11InstructionaSERKS_
	add	QWORD PTR [rbp-24], 16
	add	QWORD PTR [rbp-40], 16
	sub	QWORD PTR [rbp-8], 1
.L1096:
	cmp	QWORD PTR [rbp-8], 0
	jg	.L1097
	mov	rax, QWORD PTR [rbp-40]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2637:
	.size	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_, .-_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIPK11InstructionPS3_EET0_T_S8_S7_
	.section	.text._ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_,"axG",@progbits,_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_,comdat
	.weak	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_
	.type	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_, @function
_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_:
.LFB2639:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	sub	rdx, rax
	mov	rax, rdx
	sar	rax, 4
	mov	QWORD PTR [rbp-8], rax
	jmp	.L1100
.L1101:
	mov	rdx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZN11InstructionaSERKS_
	add	QWORD PTR [rbp-24], 16
	add	QWORD PTR [rbp-40], 16
	sub	QWORD PTR [rbp-8], 1
.L1100:
	cmp	QWORD PTR [rbp-8], 0
	jg	.L1101
	mov	rax, QWORD PTR [rbp-40]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2639:
	.size	_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_, .-_ZNSt11__copy_moveILb0ELb0ESt26random_access_iterator_tagE8__copy_mIP11InstructionS4_EET0_T_S6_S5_
	.section	.text._ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB2641:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2641:
	.size	_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_,"axG",@progbits,_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_,comdat
	.weak	_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_
	.type	_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_, @function
_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_:
.LFB2640:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2640
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 24
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardIR11InstructionEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r13, rax
	mov	r12, QWORD PTR [rbp-40]
	mov	rsi, r12
	mov	edi, 16
	call	_ZnwmPv
	mov	rbx, rax
	test	rbx, rbx
	je	.L1106
	mov	rsi, r13
	mov	rdi, rbx
.LEHB199:
	call	_ZN11InstructionC1ERKS_
.LEHE199:
	jmp	.L1105
.L1106:
	jmp	.L1105
.L1109:
	mov	r13, rax
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZdlPvS_
	mov	rax, r13
	mov	rdi, rax
.LEHB200:
	call	_Unwind_Resume
.LEHE200:
.L1105:
	add	rsp, 24
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2640:
	.section	.gcc_except_table
.LLSDA2640:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2640-.LLSDACSB2640
.LLSDACSB2640:
	.uleb128 .LEHB199-.LFB2640
	.uleb128 .LEHE199-.LEHB199
	.uleb128 .L1109-.LFB2640
	.uleb128 0
	.uleb128 .LEHB200-.LFB2640
	.uleb128 .LEHE200-.LEHB200
	.uleb128 0
	.uleb128 0
.LLSDACSE2640:
	.section	.text._ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_,"axG",@progbits,_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_,comdat
	.size	_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_, .-_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_
	.weak	_ZSt10_ConstructI11InstructionJRS0_EEvPT_DpOT0_
	.set	_ZSt10_ConstructI11InstructionJRS0_EEvPT_DpOT0_,_ZSt10_ConstructI11InstructionIRS0_EEvPT_DpOT0_
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv:
.LFB2644:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv
	cmp	rax, QWORD PTR [rbp-16]
	setb	al
	test	al, al
	je	.L1111
	call	_ZSt17__throw_bad_allocv
.L1111:
	mov	rax, QWORD PTR [rbp-16]
	sal	rax, 3
	lea	rdx, [0+rax*8]
	sub	rdx, rax
	mov	rax, rdx
	mov	rdi, rax
	call	_Znwm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2644:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8allocateEmPKv
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_:
.LFB2645:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2645:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_JRKSt21piecewise_construct_tSt5tupleIJRS3_EESC_IJEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_JRKSt21piecewise_construct_tSt5tupleIJRS3_EESC_IJEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.section	.text._ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base:
.LFB2646:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	add	rax, 32
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2646:
	.size	_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISt4pairISsjES0_IKS1_SsESt10_Select1stIS3_ESt4lessIS1_ESaIS3_EE8_S_valueEPKSt18_Rb_tree_node_base
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base,comdat
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base:
.LFB2647:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+16]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2647:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv:
.LFB2648:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv
	cmp	rax, QWORD PTR [rbp-16]
	setb	al
	test	al, al
	je	.L1119
	call	_ZSt17__throw_bad_allocv
.L1119:
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, rdx
	add	rax, rax
	add	rax, rdx
	sal	rax, 4
	mov	rdi, rax
	call	_Znwm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2648:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8allocateEmPKv
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_:
.LFB2649:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2649:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_JRKSt21piecewise_construct_tSt5tupleIJRS2_EESB_IJEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_JRKSt21piecewise_construct_tSt5tupleIJRS2_EESB_IJEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIRS2_EESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m:
.LFB2650:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZdlPv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2650:
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE10deallocateEPS5_m
	.section	.text._ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv,"axG",@progbits,_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv,comdat
	.align 2
	.weak	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv
	.type	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv, @function
_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv:
.LFB2651:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+24]
	lea	rax, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt17_Rb_tree_iteratorISt4pairIKSslEEC1EPSt13_Rb_tree_nodeIS2_E
	mov	rax, QWORD PTR [rbp-16]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2651:
	.size	_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv, .-_ZNSt8_Rb_treeISsSt4pairIKSslESt10_Select1stIS2_ESt4lessISsESaIS2_EE5beginEv
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_:
.LFB2652:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2652:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_JRKSt21piecewise_construct_tSt5tupleIJOSsEESB_IJEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_JRKSt21piecewise_construct_tSt5tupleIJOSsEESB_IJEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKSslEEEE12_S_constructIS4_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEENSt9enable_ifIXsrNS6_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS5_PSH_DpOSI_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_
	.type	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_, @function
_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_:
.LFB2653:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIhEOT_RNSt16remove_referenceIS0_E4typeE
	movzx	ebx, BYTE PTR [rax]
	mov	rax, QWORD PTR [rbp-32]
	mov	rsi, rax
	mov	edi, 1
	call	_ZnwmPv
	test	rax, rax
	je	.L1126
	mov	BYTE PTR [rax], bl
.L1126:
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2653:
	.size	_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_, .-_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_
	.weak	_ZN9__gnu_cxx13new_allocatorIhE9constructIhJhEEEvPT_DpOT0_
	.set	_ZN9__gnu_cxx13new_allocatorIhE9constructIhJhEEEvPT_DpOT0_,_ZN9__gnu_cxx13new_allocatorIhE9constructIhIhEEEvPT_DpOT0_
	.section	.text._ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorIhEC5ERKS1_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_
	.type	_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_, @function
_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_:
.LFB2655:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2655:
	.size	_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_, .-_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_
	.weak	_ZN9__gnu_cxx13new_allocatorIhEC1ERKS1_
	.set	_ZN9__gnu_cxx13new_allocatorIhEC1ERKS1_,_ZN9__gnu_cxx13new_allocatorIhEC2ERKS1_
	.section	.text._ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_,"axG",@progbits,_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_,comdat
	.weak	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_
	.type	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_, @function
_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_:
.LFB2657:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt4copyIPKhPhET0_T_S4_S3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2657:
	.size	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_, .-_ZNSt20__uninitialized_copyILb1EE13__uninit_copyIPKhPhEET0_T_S6_S5_
	.section	.text._ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_,"axG",@progbits,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_,comdat
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.type	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_, @function
_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_:
.LFB2658:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	mov	QWORD PTR [rbp-56], r8
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rsi, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	r8, r12
	mov	rcx, rbx
	mov	rdi, rax
	call	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2658:
	.size	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_, .-_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.weak	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_JRKSt21piecewise_construct_tSt5tupleIJOS2_EESC_IJEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.set	_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_JRKSt21piecewise_construct_tSt5tupleIJOS2_EESC_IJEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_JDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_,_ZNSt16allocator_traitsISaISt13_Rb_tree_nodeISt4pairIKS1_ISsjESsEEEE12_S_constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOS2_EESC_IIEEEEENSt9enable_ifIXsrNS7_18__construct_helperIT_IDpT0_EEE5valueEvE4typeERS6_PSI_DpOSJ_
	.section	.text._ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_,"axG",@progbits,_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_,comdat
	.weak	_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_
	.type	_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_, @function
_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_:
.LFB2669:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx13new_allocatorIhE8max_sizeEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2669:
	.size	_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_, .-_ZNSt16allocator_traitsISaIhEE11_S_max_sizeIKS0_EENSt9enable_ifIXsrNS1_16__maxsize_helperIT_EE5valueEmE4typeERS6_
	.section	.text._ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_,"axG",@progbits,_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_,comdat
	.weak	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_
	.type	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_, @function
_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_:
.LFB2670:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2670:
	.size	_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_, .-_ZNSt20__uninitialized_copyILb1EE13__uninit_copyISt13move_iteratorIPhES3_EET0_T_S6_S5_
	.section	.text._ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_,"axG",@progbits,_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_,comdat
	.weak	_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_
	.type	_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_, @function
_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_:
.LFB2671:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	mov	rbx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	mov	rax, QWORD PTR [rax]
	cmp	rbx, rax
	setne	al
	add	rsp, 24
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2671:
	.size	_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_, .-_ZN9__gnu_cxxneIPK11InstructionSt6vectorIS1_SaIS1_EEEEbRKNS_17__normal_iteratorIT_T0_EESC_
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv
	.type	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv, @function
_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv:
.LFB2672:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	lea	rdx, [rax+16]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2672:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv, .-_ZN9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEppEv
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv:
.LFB2673:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2673:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEEdeEv
	.section	.text._ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB2675:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2675:
	.size	_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_,"axG",@progbits,_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_,comdat
	.weak	_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_
	.type	_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_, @function
_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_:
.LFB2674:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2674
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r13
	push	r12
	push	rbx
	sub	rsp, 24
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardIRK11InstructionEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r13, rax
	mov	r12, QWORD PTR [rbp-40]
	mov	rsi, r12
	mov	edi, 16
	call	_ZnwmPv
	mov	rbx, rax
	test	rbx, rbx
	je	.L1146
	mov	rsi, r13
	mov	rdi, rbx
.LEHB201:
	call	_ZN11InstructionC1ERKS_
.LEHE201:
	jmp	.L1145
.L1146:
	jmp	.L1145
.L1149:
	mov	r13, rax
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZdlPvS_
	mov	rax, r13
	mov	rdi, rax
.LEHB202:
	call	_Unwind_Resume
.LEHE202:
.L1145:
	add	rsp, 24
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2674:
	.section	.gcc_except_table
.LLSDA2674:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2674-.LLSDACSB2674
.LLSDACSB2674:
	.uleb128 .LEHB201-.LFB2674
	.uleb128 .LEHE201-.LEHB201
	.uleb128 .L1149-.LFB2674
	.uleb128 0
	.uleb128 .LEHB202-.LFB2674
	.uleb128 .LEHE202-.LEHB202
	.uleb128 0
	.uleb128 0
.LLSDACSE2674:
	.section	.text._ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_,"axG",@progbits,_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_,comdat
	.size	_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_, .-_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_
	.weak	_ZSt10_ConstructI11InstructionJRKS0_EEvPT_DpOT0_
	.set	_ZSt10_ConstructI11InstructionJRKS0_EEvPT_DpOT0_,_ZSt10_ConstructI11InstructionIRKS0_EEvPT_DpOT0_
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv:
.LFB2676:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2676:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPK11InstructionSt6vectorIS1_SaIS1_EEE4baseEv
	.section	.text._ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv,"axG",@progbits,_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv
	.type	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv, @function
_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv:
.LFB2677:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	movabs	rax, 329406144173384850
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2677:
	.size	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv, .-_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE8max_sizeEv
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_:
.LFB2678:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2678
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	mov	r14, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r15, rax
	mov	r12, QWORD PTR [rbp-64]
	mov	rsi, r12
	mov	edi, 56
	call	_ZnwmPv
	mov	rbx, rax
	test	rbx, rbx
	je	.L1155
	mov	rcx, r15
	mov	rdx, r14
	mov	rsi, r13
	mov	rdi, rbx
.LEHB203:
	call	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
.LEHE203:
	jmp	.L1154
.L1155:
	jmp	.L1154
.L1158:
	mov	r13, rax
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZdlPvS_
	mov	rax, r13
	mov	rdi, rax
.LEHB204:
	call	_Unwind_Resume
.LEHE204:
.L1154:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2678:
	.section	.gcc_except_table
.LLSDA2678:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2678-.LLSDACSB2678
.LLSDACSB2678:
	.uleb128 .LEHB203-.LFB2678
	.uleb128 .LEHE203-.LEHB203
	.uleb128 .L1158-.LFB2678
	.uleb128 0
	.uleb128 .LEHB204-.LFB2678
	.uleb128 .LEHE204-.LEHB204
	.uleb128 0
	.uleb128 0
.LLSDACSE2678:
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_,comdat
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_JRKSt21piecewise_construct_tSt5tupleIJRS4_EESC_IJEEEEEvPT_DpOT0_
	.set	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_JRKSt21piecewise_construct_tSt5tupleIJRS4_EESC_IJEEEEEvPT_DpOT0_,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIRS4_EESC_IIEEEEEvPT_DpOT0_
	.section	.text._ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv,"axG",@progbits,_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv
	.type	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv, @function
_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv:
.LFB2679:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	movabs	rax, 384307168202282325
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2679:
	.size	_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv, .-_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE8max_sizeEv
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_:
.LFB2680:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2680
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	r14, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r15, rax
	mov	r12, QWORD PTR [rbp-64]
	mov	rsi, r12
	mov	edi, 48
	call	_ZnwmPv
	mov	rbx, rax
	test	rbx, rbx
	je	.L1162
	mov	rcx, r15
	mov	rdx, r14
	mov	rsi, r13
	mov	rdi, rbx
.LEHB205:
	call	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
.LEHE205:
	jmp	.L1161
.L1162:
	jmp	.L1161
.L1165:
	mov	r13, rax
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZdlPvS_
	mov	rax, r13
	mov	rdi, rax
.LEHB206:
	call	_Unwind_Resume
.LEHE206:
.L1161:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2680:
	.section	.gcc_except_table
.LLSDA2680:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2680-.LLSDACSB2680
.LLSDACSB2680:
	.uleb128 .LEHB205-.LFB2680
	.uleb128 .LEHE205-.LEHB205
	.uleb128 .L1165-.LFB2680
	.uleb128 0
	.uleb128 .LEHB206-.LFB2680
	.uleb128 .LEHE206-.LEHB206
	.uleb128 0
	.uleb128 0
.LLSDACSE2680:
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_,comdat
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJRS3_EESB_IJEEEEEvPT_DpOT0_
	.set	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJRS3_EESB_IJEEEEEvPT_DpOT0_,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIRS3_EESB_IIEEEEEvPT_DpOT0_
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_:
.LFB2681:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2681
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r14, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r15, rax
	mov	r12, QWORD PTR [rbp-64]
	mov	rsi, r12
	mov	edi, 48
	call	_ZnwmPv
	mov	rbx, rax
	test	rbx, rbx
	je	.L1167
	mov	rcx, r15
	mov	rdx, r14
	mov	rsi, r13
	mov	rdi, rbx
.LEHB207:
	call	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
.LEHE207:
	jmp	.L1166
.L1167:
	jmp	.L1166
.L1170:
	mov	r13, rax
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZdlPvS_
	mov	rax, r13
	mov	rdi, rax
.LEHB208:
	call	_Unwind_Resume
.LEHE208:
.L1166:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2681:
	.section	.gcc_except_table
.LLSDA2681:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2681-.LLSDACSB2681
.LLSDACSB2681:
	.uleb128 .LEHB207-.LFB2681
	.uleb128 .LEHE207-.LEHB207
	.uleb128 .L1170-.LFB2681
	.uleb128 0
	.uleb128 .LEHB208-.LFB2681
	.uleb128 .LEHE208-.LEHB208
	.uleb128 0
	.uleb128 0
.LLSDACSE2681:
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_,comdat
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJOSsEESB_IJEEEEEvPT_DpOT0_
	.set	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_JRKSt21piecewise_construct_tSt5tupleIJOSsEESB_IJEEEEEvPT_DpOT0_,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKSslEEE9constructIS5_IRKSt21piecewise_construct_tSt5tupleIIOSsEESB_IIEEEEEvPT_DpOT0_
	.section	.text._ZSt4copyIPKhPhET0_T_S4_S3_,"axG",@progbits,_ZSt4copyIPKhPhET0_T_S4_S3_,comdat
	.weak	_ZSt4copyIPKhPhET0_T_S4_S3_
	.type	_ZSt4copyIPKhPhET0_T_S4_S3_, @function
_ZSt4copyIPKhPhET0_T_S4_S3_:
.LFB2682:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_
	mov	rdx, QWORD PTR [rbp-40]
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2682:
	.size	_ZSt4copyIPKhPhET0_T_S4_S3_, .-_ZSt4copyIPKhPhET0_T_S4_S3_
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_
	.type	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_, @function
_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_:
.LFB2683:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2683
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 56
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	mov	QWORD PTR [rbp-80], rcx
	mov	QWORD PTR [rbp-88], r8
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	r13, rax
	mov	rax, QWORD PTR [rbp-80]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	mov	r14, rax
	mov	rax, QWORD PTR [rbp-88]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	r15, rax
	mov	r12, QWORD PTR [rbp-64]
	mov	rsi, r12
	mov	edi, 56
	call	_ZnwmPv
	mov	rbx, rax
	test	rbx, rbx
	je	.L1174
	mov	rcx, r15
	mov	rdx, r14
	mov	rsi, r13
	mov	rdi, rbx
.LEHB209:
	call	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
.LEHE209:
	jmp	.L1173
.L1174:
	jmp	.L1173
.L1177:
	mov	r13, rax
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZdlPvS_
	mov	rax, r13
	mov	rdi, rax
.LEHB210:
	call	_Unwind_Resume
.LEHE210:
.L1173:
	add	rsp, 56
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2683:
	.section	.gcc_except_table
.LLSDA2683:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2683-.LLSDACSB2683
.LLSDACSB2683:
	.uleb128 .LEHB209-.LFB2683
	.uleb128 .LEHE209-.LEHB209
	.uleb128 .L1177-.LFB2683
	.uleb128 0
	.uleb128 .LEHB210-.LFB2683
	.uleb128 .LEHE210-.LEHB210
	.uleb128 0
	.uleb128 0
.LLSDACSE2683:
	.section	.text._ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_,"axG",@progbits,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_,comdat
	.size	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_, .-_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_
	.weak	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_JRKSt21piecewise_construct_tSt5tupleIJOS3_EESC_IJEEEEEvPT_DpOT0_
	.set	_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_JRKSt21piecewise_construct_tSt5tupleIJOS3_EESC_IJEEEEEvPT_DpOT0_,_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKS2_ISsjESsEEE9constructIS6_IRKSt21piecewise_construct_tSt5tupleIIOS3_EESC_IIEEEEEvPT_DpOT0_
	.section	.text._ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_,"axG",@progbits,_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_,comdat
	.weak	_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_
	.type	_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_, @function
_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_:
.LFB2692:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-32], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_
	mov	rdx, QWORD PTR [rbp-40]
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2692:
	.size	_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_, .-_ZSt4copyISt13move_iteratorIPhES1_ET0_T_S4_S3_
	.section	.text._ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_
	.type	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_, @function
_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_:
.LFB2696:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2696:
	.size	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_, .-_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_
	.weak	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEE7_M_tailERS4_
	.set	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEE7_M_tailERS4_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_
	.section	.text._ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_,"axG",@progbits,_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_,comdat
	.weak	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_
	.type	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_, @function
_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_:
.LFB2698:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2698:
	.size	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_, .-_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_
	.section	.text._ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_
	.type	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_, @function
_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_:
.LFB2697:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EE7_M_headERS4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2697:
	.size	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_, .-_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_
	.weak	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEE7_M_headERS4_
	.set	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEE7_M_headERS4_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_
	.section	.text._ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE,"axG",@progbits,_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE,comdat
	.weak	_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE
	.type	_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE, @function
_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE:
.LFB2699:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2699:
	.size	_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE, .-_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE
	.section	.text._ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC5EOS4_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_
	.type	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_, @function
_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_:
.LFB2700:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_tailERS4_
	mov	rdi, rax
	call	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_
	mov	rdi, rax
	call	_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0ERKSt4pairISsjELb0EEC2ES3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2700:
	.size	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_, .-_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_
	.weak	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC2EOS4_
	.set	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC2EOS4_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_
	.weak	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC1EOS4_
	.set	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC1EOS4_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_
	.weak	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC1EOS4_
	.set	_ZNSt11_Tuple_implILm0EJRKSt4pairISsjEEEC1EOS4_,_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC1EOS4_
	.section	.text._ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_,"axG",@progbits,_ZNSt5tupleIIRKSt4pairISsjEEEC5EOS4_,comdat
	.align 2
	.weak	_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_
	.type	_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_, @function
_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_:
.LFB2702:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEEC2EOS4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2702:
	.size	_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_, .-_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_
	.weak	_ZNSt5tupleIJRKSt4pairISsjEEEC2EOS4_
	.set	_ZNSt5tupleIJRKSt4pairISsjEEEC2EOS4_,_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_
	.weak	_ZNSt5tupleIIRKSt4pairISsjEEEC1EOS4_
	.set	_ZNSt5tupleIIRKSt4pairISsjEEEC1EOS4_,_ZNSt5tupleIIRKSt4pairISsjEEEC2EOS4_
	.weak	_ZNSt5tupleIJRKSt4pairISsjEEEC1EOS4_
	.set	_ZNSt5tupleIJRKSt4pairISsjEEEC1EOS4_,_ZNSt5tupleIIRKSt4pairISsjEEEC1EOS4_
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC5IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_,comdat
	.align 2
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
	.type	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_, @function
_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_:
.LFB2704:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2704
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 64
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	QWORD PTR [rbp-64], rcx
	mov	rax, QWORD PTR [rbp-40]
	mov	DWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+16], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+24], 0
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSt4pairISsjEEEEOT_RNSt16remove_referenceIS6_E4typeE
	mov	rdx, rax
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIRKSt4pairISsjEEEC1EOS4_
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rax, QWORD PTR [rbp-40]
	lea	rdx, [rax+32]
	lea	rax, [rbp-32]
	mov	BYTE PTR [rsp+8], r12b
	mov	BYTE PTR [rsp], bl
	mov	rsi, rax
	mov	rdi, rdx
.LEHB211:
	call	_ZNSt4pairIKS_ISsjESsEC1IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
.LEHE211:
	jmp	.L1193
.L1192:
	mov	rdi, rax
.LEHB212:
	call	_Unwind_Resume
.LEHE212:
.L1193:
	add	rsp, 64
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2704:
	.section	.gcc_except_table
.LLSDA2704:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2704-.LLSDACSB2704
.LLSDACSB2704:
	.uleb128 .LEHB211-.LFB2704
	.uleb128 .LEHE211-.LEHB211
	.uleb128 .L1192-.LFB2704
	.uleb128 0
	.uleb128 .LEHB212-.LFB2704
	.uleb128 .LEHE212-.LEHB212
	.uleb128 0
	.uleb128 0
.LLSDACSE2704:
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC5IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_,comdat
	.size	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_, .-_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IJRKSt21piecewise_construct_tSt5tupleIJRS2_EES9_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IJRKSt21piecewise_construct_tSt5tupleIJRS2_EES9_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IJRKSt21piecewise_construct_tSt5tupleIJRS2_EES9_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IJRKSt21piecewise_construct_tSt5tupleIJRS2_EES9_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS2_EES9_IIEEEEEDpOT_
	.section	.text._ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_
	.type	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_, @function
_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_:
.LFB2709:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2709:
	.size	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_, .-_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_
	.weak	_ZNSt11_Tuple_implILm0EJRKSsEE7_M_tailERS2_
	.set	_ZNSt11_Tuple_implILm0EJRKSsEE7_M_tailERS2_,_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_
	.section	.text._ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_,"axG",@progbits,_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_,comdat
	.weak	_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_
	.type	_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_, @function
_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_:
.LFB2711:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2711:
	.size	_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_, .-_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_
	.section	.text._ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_,comdat
	.weak	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_
	.type	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_, @function
_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_:
.LFB2710:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0ERKSsLb0EE7_M_headERS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2710:
	.size	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_, .-_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_
	.weak	_ZNSt11_Tuple_implILm0EJRKSsEE7_M_headERS2_
	.set	_ZNSt11_Tuple_implILm0EJRKSsEE7_M_headERS2_,_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_
	.section	.text._ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB2712:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2712:
	.size	_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_,"axG",@progbits,_ZNSt11_Tuple_implILm0EIRKSsEEC5EOS2_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_
	.type	_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_, @function
_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_:
.LFB2713:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_tailERS2_
	mov	rdi, rax
	call	_ZSt4moveIRSt11_Tuple_implILm1EIEEEONSt16remove_referenceIT_E4typeEOS4_
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_
	mov	rdi, rax
	call	_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt10_Head_baseILm0ERKSsLb0EEC2ES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2713:
	.size	_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_, .-_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_
	.weak	_ZNSt11_Tuple_implILm0EJRKSsEEC2EOS2_
	.set	_ZNSt11_Tuple_implILm0EJRKSsEEC2EOS2_,_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_
	.weak	_ZNSt11_Tuple_implILm0EIRKSsEEC1EOS2_
	.set	_ZNSt11_Tuple_implILm0EIRKSsEEC1EOS2_,_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_
	.weak	_ZNSt11_Tuple_implILm0EJRKSsEEC1EOS2_
	.set	_ZNSt11_Tuple_implILm0EJRKSsEEC1EOS2_,_ZNSt11_Tuple_implILm0EIRKSsEEC1EOS2_
	.section	.text._ZNSt5tupleIIRKSsEEC2EOS2_,"axG",@progbits,_ZNSt5tupleIIRKSsEEC5EOS2_,comdat
	.align 2
	.weak	_ZNSt5tupleIIRKSsEEC2EOS2_
	.type	_ZNSt5tupleIIRKSsEEC2EOS2_, @function
_ZNSt5tupleIIRKSsEEC2EOS2_:
.LFB2715:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSsEEC2EOS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2715:
	.size	_ZNSt5tupleIIRKSsEEC2EOS2_, .-_ZNSt5tupleIIRKSsEEC2EOS2_
	.weak	_ZNSt5tupleIJRKSsEEC2EOS2_
	.set	_ZNSt5tupleIJRKSsEEC2EOS2_,_ZNSt5tupleIIRKSsEEC2EOS2_
	.weak	_ZNSt5tupleIIRKSsEEC1EOS2_
	.set	_ZNSt5tupleIIRKSsEEC1EOS2_,_ZNSt5tupleIIRKSsEEC2EOS2_
	.weak	_ZNSt5tupleIJRKSsEEC1EOS2_
	.set	_ZNSt5tupleIJRKSsEEC1EOS2_,_ZNSt5tupleIIRKSsEEC1EOS2_
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC5IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_,comdat
	.align 2
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
	.type	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_, @function
_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_:
.LFB2717:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2717
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 64
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	QWORD PTR [rbp-64], rcx
	mov	rax, QWORD PTR [rbp-40]
	mov	DWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+16], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+24], 0
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIRKSsEEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	rdx, rax
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIRKSsEEC1EOS2_
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rax, QWORD PTR [rbp-40]
	lea	rdx, [rax+32]
	lea	rax, [rbp-32]
	mov	BYTE PTR [rsp+8], r12b
	mov	BYTE PTR [rsp], bl
	mov	rsi, rax
	mov	rdi, rdx
.LEHB213:
	call	_ZNSt4pairIKSslEC1IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
.LEHE213:
	jmp	.L1207
.L1206:
	mov	rdi, rax
.LEHB214:
	call	_Unwind_Resume
.LEHE214:
.L1207:
	add	rsp, 64
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2717:
	.section	.gcc_except_table
.LLSDA2717:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2717-.LLSDACSB2717
.LLSDACSB2717:
	.uleb128 .LEHB213-.LFB2717
	.uleb128 .LEHE213-.LEHB213
	.uleb128 .L1206-.LFB2717
	.uleb128 0
	.uleb128 .LEHB214-.LFB2717
	.uleb128 .LEHE214-.LEHB214
	.uleb128 0
	.uleb128 0
.LLSDACSE2717:
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC5IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_,comdat
	.size	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_, .-_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IJRKSt21piecewise_construct_tSt5tupleIJRS1_EES8_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IJRKSt21piecewise_construct_tSt5tupleIJRS1_EES8_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IJRKSt21piecewise_construct_tSt5tupleIJRS1_EES8_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IJRKSt21piecewise_construct_tSt5tupleIJRS1_EES8_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIRS1_EES8_IIEEEEEDpOT_
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC5IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_,comdat
	.align 2
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
	.type	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_, @function
_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_:
.LFB2720:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2720
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 64
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	QWORD PTR [rbp-64], rcx
	mov	rax, QWORD PTR [rbp-40]
	mov	DWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+16], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+24], 0
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSsEEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIOSsEEC1EOS1_
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rax, QWORD PTR [rbp-40]
	lea	rdx, [rax+32]
	lea	rax, [rbp-32]
	mov	BYTE PTR [rsp+8], r12b
	mov	BYTE PTR [rsp], bl
	mov	rsi, rax
	mov	rdi, rdx
.LEHB215:
	call	_ZNSt4pairIKSslEC1IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
.LEHE215:
	jmp	.L1211
.L1210:
	mov	rdi, rax
.LEHB216:
	call	_Unwind_Resume
.LEHE216:
.L1211:
	add	rsp, 64
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2720:
	.section	.gcc_except_table
.LLSDA2720:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2720-.LLSDACSB2720
.LLSDACSB2720:
	.uleb128 .LEHB215-.LFB2720
	.uleb128 .LEHE215-.LEHB215
	.uleb128 .L1210-.LFB2720
	.uleb128 0
	.uleb128 .LEHB216-.LFB2720
	.uleb128 .LEHE216-.LEHB216
	.uleb128 0
	.uleb128 0
.LLSDACSE2720:
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC5IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_,comdat
	.size	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_, .-_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IJRKSt21piecewise_construct_tSt5tupleIJOSsEES8_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IJRKSt21piecewise_construct_tSt5tupleIJOSsEES8_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC2IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IJRKSt21piecewise_construct_tSt5tupleIJOSsEES8_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IJRKSt21piecewise_construct_tSt5tupleIJOSsEES8_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKSslEEC1IIRKSt21piecewise_construct_tSt5tupleIIOSsEES8_IIEEEEEDpOT_
	.section	.text._ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_,"axG",@progbits,_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_,comdat
	.weak	_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_
	.type	_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_, @function
_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_:
.LFB2722:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2722:
	.size	_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_, .-_ZSt12__miter_baseIPKhENSt11_Miter_baseIT_E13iterator_typeES3_
	.section	.text._ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_,"axG",@progbits,_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_,comdat
	.weak	_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_
	.type	_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_, @function
_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_:
.LFB2723:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 32
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_
	mov	rdx, r12
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_
	add	rsp, 32
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2723:
	.size	_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_, .-_ZSt14__copy_move_a2ILb0EPKhPhET1_T0_S4_S3_
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC5IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_,comdat
	.align 2
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
	.type	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_, @function
_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_:
.LFB2725:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2725
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 64
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	QWORD PTR [rbp-64], rcx
	mov	rax, QWORD PTR [rbp-40]
	mov	DWORD PTR [rax], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+16], 0
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+24], 0
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIEEEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	_ZSt7forwardISt5tupleIIOSt4pairISsjEEEEOT_RNSt16remove_referenceIS5_E4typeE
	mov	rdx, rax
	lea	rax, [rbp-32]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt5tupleIIOSt4pairISsjEEEC1EOS3_
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	_ZSt7forwardIRKSt21piecewise_construct_tEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rax, QWORD PTR [rbp-40]
	lea	rdx, [rax+32]
	lea	rax, [rbp-32]
	mov	BYTE PTR [rsp+8], r12b
	mov	BYTE PTR [rsp], bl
	mov	rsi, rax
	mov	rdi, rdx
.LEHB217:
	call	_ZNSt4pairIKS_ISsjESsEC1IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
.LEHE217:
	jmp	.L1219
.L1218:
	mov	rdi, rax
.LEHB218:
	call	_Unwind_Resume
.LEHE218:
.L1219:
	add	rsp, 64
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2725:
	.section	.gcc_except_table
.LLSDA2725:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2725-.LLSDACSB2725
.LLSDACSB2725:
	.uleb128 .LEHB217-.LFB2725
	.uleb128 .LEHE217-.LEHB217
	.uleb128 .L1218-.LFB2725
	.uleb128 0
	.uleb128 .LEHB218-.LFB2725
	.uleb128 .LEHE218-.LEHB218
	.uleb128 0
	.uleb128 0
.LLSDACSE2725:
	.section	.text._ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_,"axG",@progbits,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC5IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_,comdat
	.size	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_, .-_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IJRKSt21piecewise_construct_tSt5tupleIJOS1_EES9_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IJRKSt21piecewise_construct_tSt5tupleIJOS1_EES9_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC2IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
	.weak	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IJRKSt21piecewise_construct_tSt5tupleIJOS1_EES9_IJEEEEEDpOT_
	.set	_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IJRKSt21piecewise_construct_tSt5tupleIJOS1_EES9_IJEEEEEDpOT_,_ZNSt13_Rb_tree_nodeISt4pairIKS0_ISsjESsEEC1IIRKSt21piecewise_construct_tSt5tupleIIOS1_EES9_IIEEEEEDpOT_
	.section	.text._ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_,"axG",@progbits,_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_,comdat
	.weak	_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_
	.type	_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_, @function
_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_:
.LFB2727:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2727:
	.size	_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_, .-_ZSt12__miter_baseISt13move_iteratorIPhEENSt11_Miter_baseIT_E13iterator_typeES4_
	.section	.text._ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_,"axG",@progbits,_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_,comdat
	.weak	_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_
	.type	_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_, @function
_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_:
.LFB2728:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 32
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_
	mov	r12, rax
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_
	mov	rdx, r12
	mov	rsi, rbx
	mov	rdi, rax
	call	_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_
	add	rsp, 32
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2728:
	.size	_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_, .-_ZSt14__copy_move_a2ILb1EPhS0_ET1_T0_S2_S1_
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,comdat
	.align 2
	.weak	_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.type	_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE, @function
_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE:
.LFB2730:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2730
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	lea	rdx, [rbp+24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	BYTE PTR [rsp+8], r9b
	mov	BYTE PTR [rsp], r8b
	mov	rsi, rcx
	mov	rdi, rax
.LEHB219:
	call	_ZNSt4pairIKS_ISsjESsEC1IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
.LEHE219:
	jmp	.L1227
.L1226:
	mov	rdi, rax
.LEHB220:
	call	_Unwind_Resume
.LEHE220:
.L1227:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2730:
	.section	.gcc_except_table
.LLSDA2730:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2730-.LLSDACSB2730
.LLSDACSB2730:
	.uleb128 .LEHB219-.LFB2730
	.uleb128 .LEHE219-.LEHB219
	.uleb128 .L1226-.LFB2730
	.uleb128 0
	.uleb128 .LEHB220-.LFB2730
	.uleb128 .LEHE220-.LEHB220
	.uleb128 0
	.uleb128 0
.LLSDACSE2730:
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,comdat
	.size	_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE, .-_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.weak	_ZNSt4pairIKS_ISsjESsEC2IJRS1_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE
	.set	_ZNSt4pairIKS_ISsjESsEC2IJRS1_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE,_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.set	_ZNSt4pairIKS_ISsjESsEC1IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,_ZNSt4pairIKS_ISsjESsEC2IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IJRS1_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE
	.set	_ZNSt4pairIKS_ISsjESsEC1IJRS1_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE,_ZNSt4pairIKS_ISsjESsEC1IIRS1_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.section	.text._ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKSslEC5IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,comdat
	.align 2
	.weak	_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.type	_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE, @function
_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE:
.LFB2733:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2733
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	lea	rdx, [rbp+24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	BYTE PTR [rsp+8], r9b
	mov	BYTE PTR [rsp], r8b
	mov	rsi, rcx
	mov	rdi, rax
.LEHB221:
	call	_ZNSt4pairIKSslEC1IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
.LEHE221:
	jmp	.L1231
.L1230:
	mov	rdi, rax
.LEHB222:
	call	_Unwind_Resume
.LEHE222:
.L1231:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2733:
	.section	.gcc_except_table
.LLSDA2733:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2733-.LLSDACSB2733
.LLSDACSB2733:
	.uleb128 .LEHB221-.LFB2733
	.uleb128 .LEHE221-.LEHB221
	.uleb128 .L1230-.LFB2733
	.uleb128 0
	.uleb128 .LEHB222-.LFB2733
	.uleb128 .LEHE222-.LEHB222
	.uleb128 0
	.uleb128 0
.LLSDACSE2733:
	.section	.text._ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKSslEC5IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,comdat
	.size	_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE, .-_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.weak	_ZNSt4pairIKSslEC2IJRS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE
	.set	_ZNSt4pairIKSslEC2IJRS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE,_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.weak	_ZNSt4pairIKSslEC1IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.set	_ZNSt4pairIKSslEC1IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,_ZNSt4pairIKSslEC2IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.weak	_ZNSt4pairIKSslEC1IJRS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE
	.set	_ZNSt4pairIKSslEC1IJRS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE,_ZNSt4pairIKSslEC1IIRS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.section	.text._ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKSslEC5IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,comdat
	.align 2
	.weak	_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.type	_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE, @function
_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE:
.LFB2736:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	lea	rdx, [rbp+24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	BYTE PTR [rsp+8], r9b
	mov	BYTE PTR [rsp], r8b
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt4pairIKSslEC1IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2736:
	.size	_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE, .-_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.weak	_ZNSt4pairIKSslEC2IJOSsEJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE
	.set	_ZNSt4pairIKSslEC2IJOSsEJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE,_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.weak	_ZNSt4pairIKSslEC1IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.set	_ZNSt4pairIKSslEC1IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE,_ZNSt4pairIKSslEC2IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.weak	_ZNSt4pairIKSslEC1IJOSsEJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE
	.set	_ZNSt4pairIKSslEC1IJOSsEJEEESt21piecewise_construct_tSt5tupleIJDpT_EES5_IJDpT0_EE,_ZNSt4pairIKSslEC1IIOSsEIEEESt21piecewise_construct_tSt5tupleIIDpT_EES5_IIDpT0_EE
	.section	.text._ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_,"axG",@progbits,_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_,comdat
	.weak	_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_
	.type	_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_, @function
_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_:
.LFB2738:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2738:
	.size	_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_, .-_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_
	.section	.text._ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_,"axG",@progbits,_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_,comdat
	.weak	_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_
	.type	_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_, @function
_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_:
.LFB2739:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIPKhLb0EE7_S_baseES1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2739:
	.size	_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_, .-_ZSt12__niter_baseIPKhENSt11_Niter_baseIT_E13iterator_typeES3_
	.section	.text._ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_,"axG",@progbits,_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_,comdat
	.weak	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_
	.type	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_, @function
_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_:
.LFB2740:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2740:
	.size	_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_, .-_ZSt12__niter_baseIPhENSt11_Niter_baseIT_E13iterator_typeES2_
	.section	.text._ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_,"axG",@progbits,_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_,comdat
	.weak	_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_
	.type	_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_, @function
_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_:
.LFB2741:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	BYTE PTR [rbp-1], 1
	mov	rdx, QWORD PTR [rbp-40]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2741:
	.size	_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_, .-_ZSt13__copy_move_aILb0EPKhPhET1_T0_S4_S3_
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,comdat
	.align 2
	.weak	_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.type	_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE, @function
_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE:
.LFB2743:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2743
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	lea	rdx, [rbp+24]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	BYTE PTR [rsp+8], r9b
	mov	BYTE PTR [rsp], r8b
	mov	rsi, rcx
	mov	rdi, rax
.LEHB223:
	call	_ZNSt4pairIKS_ISsjESsEC1IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
.LEHE223:
	jmp	.L1244
.L1243:
	mov	rdi, rax
.LEHB224:
	call	_Unwind_Resume
.LEHE224:
.L1244:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2743:
	.section	.gcc_except_table
.LLSDA2743:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2743-.LLSDACSB2743
.LLSDACSB2743:
	.uleb128 .LEHB223-.LFB2743
	.uleb128 .LEHE223-.LEHB223
	.uleb128 .L1243-.LFB2743
	.uleb128 0
	.uleb128 .LEHB224-.LFB2743
	.uleb128 .LEHE224-.LEHB224
	.uleb128 0
	.uleb128 0
.LLSDACSE2743:
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,comdat
	.size	_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE, .-_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.weak	_ZNSt4pairIKS_ISsjESsEC2IJOS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE
	.set	_ZNSt4pairIKS_ISsjESsEC2IJOS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE,_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.set	_ZNSt4pairIKS_ISsjESsEC1IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE,_ZNSt4pairIKS_ISsjESsEC2IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IJOS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE
	.set	_ZNSt4pairIKS_ISsjESsEC1IJOS0_EJEEESt21piecewise_construct_tSt5tupleIJDpT_EES6_IJDpT0_EE,_ZNSt4pairIKS_ISsjESsEC1IIOS0_EIEEESt21piecewise_construct_tSt5tupleIIDpT_EES6_IIDpT0_EE
	.section	.text._ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_,"axG",@progbits,_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_,comdat
	.weak	_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_
	.type	_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_, @function
_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_:
.LFB2745:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], rdi
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	_ZNKSt13move_iteratorIPhE4baseEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2745:
	.size	_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_, .-_ZNSt10_Iter_baseISt13move_iteratorIPhELb1EE7_S_baseES2_
	.section	.text._ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_,"axG",@progbits,_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_,comdat
	.weak	_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_
	.type	_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_, @function
_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_:
.LFB2746:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	BYTE PTR [rbp-1], 1
	mov	rdx, QWORD PTR [rbp-40]
	mov	rcx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2746:
	.size	_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_, .-_ZSt13__copy_move_aILb1EPhS0_ET1_T0_S2_S1_
	.section	.text._ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE
	.type	_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE, @function
_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE:
.LFB2749:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSt4pairISsjEEE7_M_headERS4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2749:
	.size	_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE, .-_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE
	.weak	_ZSt12__get_helperILm0ERKSt4pairISsjEJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS5_DpT1_EE
	.set	_ZSt12__get_helperILm0ERKSt4pairISsjEJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS5_DpT1_EE,_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE
	.section	.text._ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_,"axG",@progbits,_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_,comdat
	.weak	_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_
	.type	_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_, @function
_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_:
.LFB2748:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZSt12__get_helperILm0ERKSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS5_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2748:
	.size	_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_, .-_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_
	.weak	_ZSt3getILm0EJRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS9_
	.set	_ZSt3getILm0EJRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS9_,_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,comdat
	.align 2
	.weak	_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.type	_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE, @function
_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE:
.LFB2750:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2750
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt3getILm0EIRKSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS9_
	mov	rdi, rax
	call	_ZSt7forwardIRKSt4pairISsjEEOT_RNSt16remove_referenceIS4_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
.LEHB225:
	call	_ZNSt4pairISsjEC1ERKS0_
.LEHE225:
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 16
	mov	rdi, rax
.LEHB226:
	call	_ZNSsC1Ev
.LEHE226:
	jmp	.L1256
.L1255:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt4pairISsjED1Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB227:
	call	_Unwind_Resume
.LEHE227:
.L1256:
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2750:
	.section	.gcc_except_table
.LLSDA2750:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2750-.LLSDACSB2750
.LLSDACSB2750:
	.uleb128 .LEHB225-.LFB2750
	.uleb128 .LEHE225-.LEHB225
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB226-.LFB2750
	.uleb128 .LEHE226-.LEHB226
	.uleb128 .L1255-.LFB2750
	.uleb128 0
	.uleb128 .LEHB227-.LFB2750
	.uleb128 .LEHE227-.LEHB227
	.uleb128 0
	.uleb128 0
.LLSDACSE2750:
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,comdat
	.size	_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE, .-_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.weak	_ZNSt4pairIKS_ISsjESsEC2IJRS1_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE
	.set	_ZNSt4pairIKS_ISsjESsEC2IJRS1_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE,_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.set	_ZNSt4pairIKS_ISsjESsEC1IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,_ZNSt4pairIKS_ISsjESsEC2IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IJRS1_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE
	.set	_ZNSt4pairIKS_ISsjESsEC1IJRS1_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE,_ZNSt4pairIKS_ISsjESsEC1IIRS1_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.section	.text._ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE
	.type	_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE, @function
_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE:
.LFB2754:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIRKSsEE7_M_headERS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2754:
	.size	_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE, .-_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE
	.weak	_ZSt12__get_helperILm0ERKSsJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS3_DpT1_EE
	.set	_ZSt12__get_helperILm0ERKSsJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS3_DpT1_EE,_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE
	.section	.text._ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_,"axG",@progbits,_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_,comdat
	.weak	_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_
	.type	_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_, @function
_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_:
.LFB2753:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZSt12__get_helperILm0ERKSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS3_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2753:
	.size	_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_, .-_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_
	.weak	_ZSt3getILm0EJRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS7_
	.set	_ZSt3getILm0EJRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS7_,_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_
	.section	.text._ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE,"axG",@progbits,_ZNSt4pairIKSslEC5IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE,comdat
	.align 2
	.weak	_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.type	_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE, @function
_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE:
.LFB2755:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt3getILm0EIRKSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS7_
	mov	rdi, rax
	call	_ZSt7forwardIRKSsEOT_RNSt16remove_referenceIS2_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1ERKSs
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2755:
	.size	_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE, .-_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.weak	_ZNSt4pairIKSslEC2IJRS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE
	.set	_ZNSt4pairIKSslEC2IJRS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE,_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.weak	_ZNSt4pairIKSslEC1IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.set	_ZNSt4pairIKSslEC1IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE,_ZNSt4pairIKSslEC2IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.weak	_ZNSt4pairIKSslEC1IJRS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE
	.set	_ZNSt4pairIKSslEC1IJRS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE,_ZNSt4pairIKSslEC1IIRS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.section	.text._ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE
	.type	_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE, @function
_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE:
.LFB2759:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSsEE7_M_headERS1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2759:
	.size	_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE, .-_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE
	.weak	_ZSt12__get_helperILm0EOSsJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS2_DpT1_EE
	.set	_ZSt12__get_helperILm0EOSsJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS2_DpT1_EE,_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE
	.section	.text._ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_,"axG",@progbits,_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_,comdat
	.weak	_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_
	.type	_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_, @function
_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_:
.LFB2758:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZSt12__get_helperILm0EOSsIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS2_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2758:
	.size	_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_, .-_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_
	.weak	_ZSt3getILm0EJOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS6_
	.set	_ZSt3getILm0EJOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS6_,_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_
	.section	.text._ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE,"axG",@progbits,_ZNSt4pairIKSslEC5IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE,comdat
	.align 2
	.weak	_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.type	_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE, @function
_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE:
.LFB2760:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	QWORD PTR [rbp-24], rdx
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZSt3getILm0EIOSsEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS6_
	mov	rdi, rax
	call	_ZSt7forwardIOSsEOT_RNSt16remove_referenceIS1_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1EOSs
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2760:
	.size	_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE, .-_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.weak	_ZNSt4pairIKSslEC2IJOSsEJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE
	.set	_ZNSt4pairIKSslEC2IJOSsEJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE,_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.weak	_ZNSt4pairIKSslEC1IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.set	_ZNSt4pairIKSslEC1IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE,_ZNSt4pairIKSslEC2IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.weak	_ZNSt4pairIKSslEC1IJOSsEJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE
	.set	_ZNSt4pairIKSslEC1IJOSsEJLm0EEJEJEEERSt5tupleIJDpT_EERS4_IJDpT1_EESt12_Index_tupleIJXspT0_EEESD_IJXspT2_EEE,_ZNSt4pairIKSslEC1IIOSsEILm0EEIEIEEERSt5tupleIIDpT_EERS4_IIDpT1_EESt12_Index_tupleIIXspT0_EEESD_IIXspT2_EEE
	.section	.text._ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_,"axG",@progbits,_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_,comdat
	.weak	_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_
	.type	_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_, @function
_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_:
.LFB2762:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2762:
	.size	_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_, .-_ZNSt10_Iter_baseIPhLb0EE7_S_baseES0_
	.section	.text._ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_,"axG",@progbits,_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_,comdat
	.weak	_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_
	.type	_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_, @function
_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_:
.LFB2763:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	sub	rdx, rax
	mov	rax, rdx
	mov	QWORD PTR [rbp-8], rax
	cmp	QWORD PTR [rbp-8], 0
	je	.L1270
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rcx
	mov	rdi, rax
	call	memmove
.L1270:
	mov	rdx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-40]
	add	rax, rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2763:
	.size	_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_, .-_ZNSt11__copy_moveILb0ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_
	.section	.text._ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE
	.type	_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE, @function
_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE:
.LFB2766:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZNSt11_Tuple_implILm0EIOSt4pairISsjEEE7_M_headERS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2766:
	.size	_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE, .-_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE
	.weak	_ZSt12__get_helperILm0EOSt4pairISsjEJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS4_DpT1_EE
	.set	_ZSt12__get_helperILm0EOSt4pairISsjEJEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EJS4_DpT1_EE,_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE
	.section	.text._ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_,"axG",@progbits,_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_,comdat
	.weak	_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_
	.type	_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_, @function
_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_:
.LFB2765:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	_ZSt12__get_helperILm0EOSt4pairISsjEIEENSt9__add_refIT0_E4typeERSt11_Tuple_implIXT_EIS4_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2765:
	.size	_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_, .-_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_
	.weak	_ZSt3getILm0EJOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS8_
	.set	_ZSt3getILm0EJOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEE4typeERS8_,_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_
	.section	.text._ZNSt4pairISsjEC2EOS0_,"axG",@progbits,_ZNSt4pairISsjEC5EOS0_,comdat
	.align 2
	.weak	_ZNSt4pairISsjEC2EOS0_
	.type	_ZNSt4pairISsjEC2EOS0_, @function
_ZNSt4pairISsjEC2EOS0_:
.LFB2768:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSsC1EOSs
	mov	rax, QWORD PTR [rbp-16]
	mov	edx, DWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax+8], edx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2768:
	.size	_ZNSt4pairISsjEC2EOS0_, .-_ZNSt4pairISsjEC2EOS0_
	.weak	_ZNSt4pairISsjEC1EOS0_
	.set	_ZNSt4pairISsjEC1EOS0_,_ZNSt4pairISsjEC2EOS0_
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,comdat
	.align 2
	.weak	_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.type	_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE, @function
_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE:
.LFB2770:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2770
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	_ZSt3getILm0EIOSt4pairISsjEEENSt9__add_refINSt13tuple_elementIXT_ESt5tupleIIDpT0_EEE4typeEE4typeERS8_
	mov	rdi, rax
	call	_ZSt7forwardIOSt4pairISsjEEOT_RNSt16remove_referenceIS3_E4typeE
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
	call	_ZNSt4pairISsjEC1EOS0_
	mov	rax, QWORD PTR [rbp-24]
	add	rax, 16
	mov	rdi, rax
.LEHB228:
	call	_ZNSsC1Ev
.LEHE228:
	jmp	.L1280
.L1279:
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdi, rax
	call	_ZNSt4pairISsjED1Ev
	mov	rax, rbx
	mov	rdi, rax
.LEHB229:
	call	_Unwind_Resume
.LEHE229:
.L1280:
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2770:
	.section	.gcc_except_table
.LLSDA2770:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2770-.LLSDACSB2770
.LLSDACSB2770:
	.uleb128 .LEHB228-.LFB2770
	.uleb128 .LEHE228-.LEHB228
	.uleb128 .L1279-.LFB2770
	.uleb128 0
	.uleb128 .LEHB229-.LFB2770
	.uleb128 .LEHE229-.LEHB229
	.uleb128 0
	.uleb128 0
.LLSDACSE2770:
	.section	.text._ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,"axG",@progbits,_ZNSt4pairIKS_ISsjESsEC5IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,comdat
	.size	_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE, .-_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.weak	_ZNSt4pairIKS_ISsjESsEC2IJOS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE
	.set	_ZNSt4pairIKS_ISsjESsEC2IJOS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE,_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.set	_ZNSt4pairIKS_ISsjESsEC1IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE,_ZNSt4pairIKS_ISsjESsEC2IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.weak	_ZNSt4pairIKS_ISsjESsEC1IJOS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE
	.set	_ZNSt4pairIKS_ISsjESsEC1IJOS0_EJLm0EEJEJEEERSt5tupleIJDpT_EERS5_IJDpT1_EESt12_Index_tupleIJXspT0_EEESE_IJXspT2_EEE,_ZNSt4pairIKS_ISsjESsEC1IIOS0_EILm0EEIEIEEERSt5tupleIIDpT_EERS5_IIDpT1_EESt12_Index_tupleIIXspT0_EEESE_IIXspT2_EEE
	.section	.text._ZNKSt13move_iteratorIPhE4baseEv,"axG",@progbits,_ZNKSt13move_iteratorIPhE4baseEv,comdat
	.align 2
	.weak	_ZNKSt13move_iteratorIPhE4baseEv
	.type	_ZNKSt13move_iteratorIPhE4baseEv, @function
_ZNKSt13move_iteratorIPhE4baseEv:
.LFB2772:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR [rbp-8], rdi
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2772:
	.size	_ZNKSt13move_iteratorIPhE4baseEv, .-_ZNKSt13move_iteratorIPhE4baseEv
	.section	.text._ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_,"axG",@progbits,_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_,comdat
	.weak	_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_
	.type	_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_, @function
_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_:
.LFB2773:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	sub	rdx, rax
	mov	rax, rdx
	mov	QWORD PTR [rbp-8], rax
	cmp	QWORD PTR [rbp-8], 0
	je	.L1284
	mov	rax, QWORD PTR [rbp-8]
	mov	rdx, rax
	mov	rcx, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rcx
	mov	rdi, rax
	call	memmove
.L1284:
	mov	rdx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-40]
	add	rax, rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2773:
	.size	_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_, .-_ZNSt11__copy_moveILb1ELb1ESt26random_access_iterator_tagE8__copy_mIhEEPT_PKS3_S6_S4_
	.weak	_ZTSSs
	.section	.rodata._ZTSSs,"aG",@progbits,_ZTSSs,comdat
	.type	_ZTSSs, @object
	.size	_ZTSSs, 3
_ZTSSs:
	.string	"Ss"
	.weak	_ZTISs
	.section	.rodata._ZTISs,"aG",@progbits,_ZTISs,comdat
	.align 16
	.type	_ZTISs, @object
	.size	_ZTISs, 16
_ZTISs:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSSs
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2774:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	DWORD PTR [rbp-4], edi
	mov	DWORD PTR [rbp-8], esi
	cmp	DWORD PTR [rbp-4], 1
	jne	.L1286
	cmp	DWORD PTR [rbp-8], 65535
	jne	.L1286
	mov	edi, OFFSET FLAT:_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	mov	edx, OFFSET FLAT:__dso_handle
	mov	esi, OFFSET FLAT:_ZStL8__ioinit
	mov	edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
	call	__cxa_atexit
.L1286:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2774:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.section	.rodata
	.align 4
	.type	_ZL10NUM_LOCALS, @object
	.size	_ZL10NUM_LOCALS, 4
_ZL10NUM_LOCALS:
	.long	8
	.type	_ZL12ENABLE_DEBUG, @object
	.size	_ZL12ENABLE_DEBUG, 1
_ZL12ENABLE_DEBUG:
	.byte	1
	.type	._84, @object
	.size	._84, 4
._84:
	.byte	72
	.byte	-119
	.byte	77
	.byte	-16
	.type	._85, @object
	.size	._85, 4
._85:
	.byte	72
	.byte	-119
	.byte	85
	.byte	-12
	.type	._86, @object
	.size	._86, 4
._86:
	.byte	72
	.byte	-119
	.byte	117
	.byte	-8
	.type	._87, @object
	.size	._87, 4
._87:
	.byte	72
	.byte	-119
	.byte	125
	.byte	-4
	.text
	.type	_GLOBAL__sub_I__Z9pushArrayRSt6vectorIhSaIhEERKS1_, @function
_GLOBAL__sub_I__Z9pushArrayRSt6vectorIhSaIhEERKS1_:
.LFB2775:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	esi, 65535
	mov	edi, 1
	call	_Z41__static_initialization_and_destruction_0ii
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2775:
	.size	_GLOBAL__sub_I__Z9pushArrayRSt6vectorIhSaIhEERKS1_, .-_GLOBAL__sub_I__Z9pushArrayRSt6vectorIhSaIhEERKS1_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z9pushArrayRSt6vectorIhSaIhEERKS1_
	.section	.rodata
	.align 8
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, @object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 8
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.quad	_ZL28__gthrw___pthread_key_createPjPFvPvE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu/Linaro 4.8.1-10ubuntu9) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
