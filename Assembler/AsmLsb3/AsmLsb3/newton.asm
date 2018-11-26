.386
.MODEL FLAT

.DATA
	x0 DD 2.0		; ��������� �������� 
	F DD ?			; �������� ������� � ����� x0
	DEFF DD ?		; �������� ����������� ������� � ����� x0
	eps DD ?		; �������� �������
	v DD 2.0		; ��������� ��� ������
.CODE 
_newton@8 PROC
push ebp
mov ebp,esp
mov eax,[EBP]+8
mov eps,eax
xor edx,edx
iteration:
	call func	; ��������� �������� ������� � ����� x0
	fld F		; ������ � ���� ������� ST(0)=F
	fabs
	fld eps		; ������ � ���� �������� ������� ST(0)=eps, ST(1)=F
	fcompp		; ���������� �������� 
	fstsw ax
	sahf
	jnc exit	; ��������� �� ����� exit
	call iter	; ��������� ��������� x
	inc edx		;����������� ������� �� 1
	jmp iteration 
exit:
	mov ecx,[ebp]+12
	mov eax,x0
	mov [ecx], eax
	mov eax, edx
pop ebp
ret 8
_newton@8 ENDP

;���������� �������� ������� � ����� x0
Func PROC
fld x0 ; ST(0)=x0
fld1 ; ST(0)=1, ST(1)=x0
fpatan ; ���������� ����������� x0 ������������� ST(0), ��������� ST(0)=arctan(x0)
fstp F ; ��������� �������� ������� � ������ ������ F
ret
func ENDP


;���������� �������� ����������� ������� � ����� x0
defFunc PROC
fld1			; ST(0)=1
fld x0			; ST(0)=x0, ST(1)=1.0
fld x0			; ST(0)=x0, ST(1)=x0, ST(2)=1.0
fmulp			; ST(0)=x0^2,ST(1)=1.0
fadd st, st(1)	; ST(0)=x0^2+1,ST(1)=1.0
fdivp st(1),st
fstp DEFF		; c�������� ��������� ����������� ������� � ������ ������ DEFF
ret
defFunc ENDP

;���������� ������������ �� ����� ��������
iter PROC
call defFunc
fld x0			; ST(0)=x0
fld DEFF		; ST(0)=DEFF, ST(1)=x0
fld v			; ST(0)=v, ST(1)=DEFF, ST(2)=x0
fmul st(1),st	; ST(0)=v, ST(1)=v*DEFF, ST(2)=x0
fld F			; ST(0)=F, ST(1)=v, ST(2)=v*DEFF, ST(3)=x0
fsub st(1),st	; ST(0)=F, ST(1)=v-F, ST(2)=v*DEFF, ST(3)=x0
fmulp st(1),st	; ST(0)=F(v-F), ST(1)=v*DEFF, ST(2)=x0
fdivrp st(1),st ; ST(0)=(v-F)/v*DEFF, ST(1)=x0
fsubp st(1),st	; ST(0)= x0 - (v-F)/v*DEFF
fstp x0
ret
iter ENDP
END