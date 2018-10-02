.386
.MODEL FLAT, STDCALL



; ��������� ������� ������� (��������) ����������� ���������� EXTERN, 
; ����� ����� @ ����������� ����� ����� ������������ ����������,
; ����� ��������� ����������� ��� �������� ������� � ���������
EXTERN  GetStdHandle@4: PROC
EXTERN  WriteConsoleA@20: PROC
EXTERN  CharToOemA@8: PROC
EXTERN  ReadConsoleA@20: PROC
EXTERN  ExitProcess@4: PROC; ������� ������ �� ���������
EXTERN  lstrlenA@4: PROC; ������� ����������� ����� ������
EXTERN  wsprintfA: PROC; �.�. ����� ���������� ������� �� �����������,
			; ������������ ����������, �������� �������� ������� ���� 
			; ���������� ���������


.DATA; ������� ������
STRN1 DB "������� ������ �����: ",13,10,0
STRN2 DB "������� ������ �����: ",13,10,0
DESCR DB "��������� �������� ����� ��������������� ����� � ����������������� �������. ����� � ����������.",13,10,0
SRCNUM DB "0123456789ABCDEF",13,10,0
RESBUFF DB "0123456789ABCDEF",13,10,0
; ��������� ������, � ����� ���������
; ����������� �������: 13 � ������� �������, 10 � ������� �� ����� 
; ������, 0 � ����� ������; � �������������� ��������� DB 
; ������������� ������ ������
FMT DB "Result: %d", 0; ������ �� ������� �������� ��� ������� wsprintfA
DIN DD ?; ���������� �����; ��������� DD ����������� ������ �������
; 32 ���� (4 �����), ���� �?� ������������ ��� �������������������� ������
DOUT DD ?; ���������� ������
BUF  DB 200 dup (?); ����� ��� ��������/��������� ����� ������ 200 ������
LENS DD ?; ���������� ��� ���������� ���������� ��������
OFFS1 DD ?
OFFS2 DD ?
COUNT DD ?
I DD ?
NUM1 DD ?
NUM2 DD ?
SYMB DD ?
STR_PTR DD ?

.CODE; ������� ���� 
MAIN PROC; �������� ���������

MOV  EAX, OFFSET DESCR;
PUSH EAX
PUSH EAX
CALL CharToOemA@8;
PUSH -10;
CALL GetStdHandle@4
MOV DIN, EAX;
PUSH -11;
CALL GetStdHandle@4;
MOV DOUT, EAX;

MOV  EAX, OFFSET STRN1;
PUSH EAX
PUSH EAX
CALL CharToOemA@8;
PUSH -10;
CALL GetStdHandle@4
MOV DIN, EAX;
PUSH -11;
CALL GetStdHandle@4;
MOV DOUT, EAX;


MOV  EAX, OFFSET STRN2;
PUSH EAX
PUSH EAX
CALL CharToOemA@8;
PUSH -10;
CALL GetStdHandle@4
MOV DIN, EAX;
PUSH -11;
CALL GetStdHandle@4;
MOV DOUT, EAX;

;----------------------------------------
;---------�������� ���������
PUSH OFFSET DESCR
CALL lstrlenA@4
PUSH 0				;5
PUSH OFFSET LENS    ;4
PUSH EAX			;3
PUSH OFFSET DESCR	;26
PUSH DOUT			;1
CALL WriteConsoleA@20;			������� �������������� ��������� 
	


;--------------------------------------
;���� ������ 1
L_INPUT_LOOP:
	PUSH OFFSET STRN1
	CALL lstrlenA@4
	PUSH 0				;5
	PUSH OFFSET LENS    ;4
	PUSH EAX			;3
	PUSH OFFSET STRN1	;26
	PUSH DOUT			;1
	CALL WriteConsoleA@20;			������� �������������� ��������� 
	
	PUSH 0
	PUSH OFFSET LENS
	PUSH 200
	PUSH OFFSET BUF
	PUSH DIN
	CALL ReadConsoleA@20;			������ ������ � buf, ����� � LENS

	
	;---------------------------------
	;�������������� �������� ��������� ���� � �������� ��������
	MOV esi, OFFSET BUF
	MOV i, 2;				2 ��������� ������� - �������� ������� � ������� �� ����� ������

	L_TOUPPER:
		MOV eax,I
		CMP eax, LENS
		JGE L_TOUPPER_END;	���� �������� ���� �� ������ �� ������� �� �����
		MOV BL, [esi];		���������� ������� ����� � ������� BL
		INC i;				���������� ��������
		INC ESI;			���������� ��������� �� �����
		CMP BL, 'a' ;		
		JL L_TOUPPER;		���� ����� �� ����� � ������� [a-z], �� ������� � ���������
		CMP BL, 'z' ;		����� �������������� � �������� ��������
		JG L_TOUPPER;
		
		SUB BL, 'a'
		ADD BL, 'A' 
		MOV [esi-1], BL;	�.�. ��������� ���������� ����, �� ����� ������ ������� ��� ��������� ������� �����
		JMP L_TOUPPER
	L_TOUPPER_END:


	;------------------------------------
	; �������� ������������ ������.������ �����
	MOV OFFS1, OFFSET BUF
	MOV i,2
	MOV esi, OFFSET BUF
	MOV NUM1, 0
	MOV NUM2, 0
	L_N1_CHECK:
		MOV eax,I
		CMP eax, LENS
		JGE L_N1_CHECK_END;	���� �������� ���� �� �

		MOV BL, [esi]
		INC esi
		INC I
		;---�������� [0-9]
		CMP BL, '9'
		JG L_N1_CHECK_ELSE_A_F
		CMP BL,'0'
		JL L_INPUT_LOOP
		INC NUM1
		JMP L_N1_CHECK

		;---�������� [A-F]
		L_N1_CHECK_ELSE_A_F:
		CMP BL,13
		JE L_INPUT_LOOP

		CMP BL,'A'
		JL L_INPUT_LOOP
		CMP BL,'F'
		JG L_INPUT_LOOP

		INC NUM1
		CMP BL, '9'
		JMP L_N1_CHECK

	L_N1_CHECK_END:
	CMP NUM1, 0
	JE L_INPUT_LOOP



	;----------------------------------------------------------------------
	;������� ������� ����� � ���������� �� (�� ������ BUF � ���������� NUM1)
	MOV esi, OFFS1 
	MOV DI, 16;				�������� ���������
	MOV EAX, 0
	XOR BX,BX
	L2:
		MOV BL, [ESI]
		CMP BL, 13
		JE END_LOOP1;		���� ����� �� ����� �����
		CMP BL, ' '
		JE END_LOOP1;		���� ������ �� ����� �����
	
	
		CMP BL, '9'
		JLE NUMBLOCK
		SUB BL, 7;			���� ������ - �����, �� ��������� �������� ����� 'A' � '9' �� ASKII
		NUMBLOCK:
		SUB BL, '0'; ������� �� ���������� ������� ��� ����
		
		MUL DI; �������� �������� AX �� 10, ��������� � � AX
		ADD AX, BX;
		
		INC ESI		
		JMP L2;				��������� ��������
	END_LOOP1:
	MOV NUM1, eax
L_INPUT_LOOP_END:





;--------------------------------------
;���� ������ 2
L_INPUT2_LOOP:
	PUSH OFFSET STRN2
	CALL lstrlenA@4
	PUSH 0				;5
	PUSH OFFSET LENS    ;4
	PUSH EAX			;3
	PUSH OFFSET STRN2	;26
	PUSH DOUT			;1
	CALL WriteConsoleA@20;			������� �������������� ��������� 
	
	PUSH 0
	PUSH OFFSET LENS
	PUSH 200
	PUSH OFFSET BUF
	PUSH DIN
	CALL ReadConsoleA@20;			������ ������ � buf, ����� � LENS

	
	;---------------------------------
	;�������������� �������� ��������� ���� � �������� ��������
	MOV esi, OFFSET BUF
	MOV i, 2;				2 ��������� ������� - �������� ������� � ������� �� ����� ������

	L_TOUPPER2:
		MOV eax,I
		CMP eax, LENS
		JGE L_TOUPPER2_END;	���� �������� ���� �� ������ �� ������� �� �����
		MOV BL, [esi];		���������� ������� ����� � ������� BL
		INC i;				���������� ��������
		INC ESI;			���������� ��������� �� �����
		CMP BL, 'a' ;		
		JL L_TOUPPER2;		���� ����� �� ����� � ������� [a-z], �� ������� � ���������
		CMP BL, 'z' ;		����� �������������� � �������� ��������
		JG L_TOUPPER2;
		
		SUB BL, 'a'
		ADD BL, 'A' 
		MOV [esi-1], BL;	�.�. ��������� ���������� ����, �� ����� ������ ������� ��� ��������� ������� �����
		JMP L_TOUPPER2
	L_TOUPPER2_END:


	;------------------------------------
	; �������� ������������ ������.������ �����
	MOV OFFS1, OFFSET BUF
	MOV i,2
	MOV esi, OFFSET BUF
	MOV NUM2, 0
	L_N2_CHECK:
		MOV eax,I
		CMP eax, LENS
		JGE L_N2_CHECK_END;	���� �������� ���� �� �

		MOV BL, [esi]
		INC esi
		INC I
		CMP BL, '9'
		;---�������� [0-9]
		CMP BL, '9'
		JG L_N2_CHECK_ELSE_A_F
		CMP BL,'0'
		JL L_INPUT2_LOOP
		INC NUM2
		JMP L_N2_CHECK

		;---�������� [A-F]
		L_N2_CHECK_ELSE_A_F:
		CMP BL,13
		JE L_INPUT2_LOOP

		CMP BL,'A'
		JL L_INPUT2_LOOP
		CMP BL,'F'
		JG L_INPUT2_LOOP

		INC NUM2
		CMP BL, '9'
		JMP L_N2_CHECK

	L_N2_CHECK_END:
	CMP NUM2, 0
	JE L_INPUT2_LOOP



	;----------------------------------------------------------------------
	;������� ������� ����� � ���������� �� (�� ������ BUF � ���������� NUM1)
	MOV esi, OFFS1 
	MOV DI, 16;				�������� ���������
	MOV EAX, 0
	XOR BX,BX
	L2_2:
		MOV BL, [ESI]
		CMP BL, 13
		JE END_LOOP2;		���� ����� �� ����� �����
		CMP BL, ' '
		JE END_LOOP2;		���� ������ �� ����� �����
	
	
		CMP BL, '9'
		JLE NUMBLOCK2
		SUB BL, 7;			���� ������ - �����, �� ��������� �������� ����� 'A' � '9' �� ASKII
		NUMBLOCK2:
		SUB BL, '0'; ������� �� ���������� ������� ��� ����
		
		MUL DI; �������� �������� AX �� 10, ��������� � � AX
		ADD AX, BX;
		
		INC ESI		
		JMP L2_2;				��������� ��������
	END_LOOP2:
	MOV NUM2, eax
L_INPUT2_LOOP_END:


MOV EAX, NUM1
ADD EAX, NUM2
MOV NUM1, EAX

;----------------------------------------------------------------------
;������� ����� ������, ������ � i
MOV i,1
MOV EAX, NUM1
MOV EBX, 10
MOV EDX, 0
Lt_LOOP:
	DIV EBX
	CMP EAX, 0
	JE LT_LOOP_END
	INC i
	MOV EDX,0
	JMP Lt_LOOP
LT_LOOP_END:


;----------------------------------------------------------------------
;������ ����� � BUF
MOV ESI, OFFSET BUF
ADD ESI, I
MOV BL, 13
MOV [ESI], BL
MOV BL, 10
MOV [ESI+1], BL
MOV BL, 0
MOV [ESI+2], BL 
MOV EAX, NUM1
MOV EBX, 10
MOV EDX, 0

L4_LOOP:
	CMP I, 0
	JE L4_LOOP_END
	DEC I
	DEC ESI
	DIV EBX
	ADD EDX, '0'
	MOV [ESI], DL
	MOV EDX,0
	JMP L4_LOOP

L4_LOOP_END:
;------------------------------------------------------------------


PUSH OFFSET BUF
CALL lstrlenA@4
PUSH 0				
PUSH OFFSET LENS    
PUSH EAX			
PUSH OFFSET BUF 	
PUSH DOUT			
CALL WriteConsoleA@20;			 

; ����� �� ��������� 
PUSH 0; ��������: ��� ������
CALL ExitProcess@4
MAIN ENDP
END MAIN

