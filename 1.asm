.386
.MODEL FLAT, STDCALL



; прототипы внешних функций (процедур) описываются директивой EXTERN, 
; после знака @ указывается общая длина передаваемых параметров,
; после двоеточия указывается тип внешнего объекта – процедура
EXTERN  GetStdHandle@4: PROC
EXTERN  WriteConsoleA@20: PROC
EXTERN  CharToOemA@8: PROC
EXTERN  ReadConsoleA@20: PROC
EXTERN  ExitProcess@4: PROC; функция выхода из программы
EXTERN  lstrlenA@4: PROC; функция определения длины строки
EXTERN  wsprintfA: PROC; т.к. число параметров функции не фиксировано,
			; используется соглашение, согласно которому очищает стек 
			; вызывающая процедура


.DATA; сегмент данных
STRN1 DB "Введите первое число: ",13,10,0
STRN2 DB "Введите второе число: ",13,10,0
DESCR DB "Программа сложения целых неотрицательных чисел в шестнадцатеричной системе. Вывод в десятичной.",13,10,0
SRCNUM DB "0123456789ABCDEF",13,10,0
RESBUFF DB "0123456789ABCDEF",13,10,0
; выводимая строка, в конце добавлены
; управляющие символы: 13 – возврат каретки, 10 – переход на новую 
; строку, 0 – конец строки; с использованием директивы DB 
; резервируется массив байтов
FMT DB "Result: %d", 0; строка со списком форматов для функции wsprintfA
DIN DD ?; дескриптор ввода; директива DD резервирует память объемом
; 32 бита (4 байта), знак «?» используется для неинициализированных данных
DOUT DD ?; дескриптор вывода
BUF  DB 200 dup (?); буфер для вводимых/выводимых строк длиной 200 байтов
LENS DD ?; переменная для количества выведенных символов
OFFS1 DD ?
OFFS2 DD ?
COUNT DD ?
I DD ?
NUM1 DD ?
NUM2 DD ?
SYMB DD ?
STR_PTR DD ?

.CODE; сегмент кода 
MAIN PROC; описание процедуры

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
;---------описание программы
PUSH OFFSET DESCR
CALL lstrlenA@4
PUSH 0				;5
PUSH OFFSET LENS    ;4
PUSH EAX			;3
PUSH OFFSET DESCR	;26
PUSH DOUT			;1
CALL WriteConsoleA@20;			выводим информационное сообщение 
	


;--------------------------------------
;Ввод строки 1
L_INPUT_LOOP:
	PUSH OFFSET STRN1
	CALL lstrlenA@4
	PUSH 0				;5
	PUSH OFFSET LENS    ;4
	PUSH EAX			;3
	PUSH OFFSET STRN1	;26
	PUSH DOUT			;1
	CALL WriteConsoleA@20;			выводим информационное сообщение 
	
	PUSH 0
	PUSH OFFSET LENS
	PUSH 200
	PUSH OFFSET BUF
	PUSH DIN
	CALL ReadConsoleA@20;			чтение строки в buf, длина в LENS

	
	;---------------------------------
	;Преобразование строчных латинских букв к верхнему регистру
	MOV esi, OFFSET BUF
	MOV i, 2;				2 последних символа - смещение каретки и переход на новую строку

	L_TOUPPER:
		MOV eax,I
		CMP eax, LENS
		JGE L_TOUPPER_END;	если завершён цикл по строке то выходим из цикла
		MOV BL, [esi];		перемещаем текущую букву в регистр BL
		INC i;				увеличение счётчика
		INC ESI;			увеличение указателя на букву
		CMP BL, 'a' ;		
		JL L_TOUPPER;		если буква не лежит в отрезке [a-z], то переход к следующей
		CMP BL, 'z' ;		иначе преобразование к верхнему регистру
		JG L_TOUPPER;
		
		SUB BL, 'a'
		ADD BL, 'A' 
		MOV [esi-1], BL;	т.к. указатель увеличился выше, то нужно отнять единицу для установки текущей буквы
		JMP L_TOUPPER
	L_TOUPPER_END:


	;------------------------------------
	; проверка корректности строки.первое число
	MOV OFFS1, OFFSET BUF
	MOV i,2
	MOV esi, OFFSET BUF
	MOV NUM1, 0
	MOV NUM2, 0
	L_N1_CHECK:
		MOV eax,I
		CMP eax, LENS
		JGE L_N1_CHECK_END;	если завершён цикл по с

		MOV BL, [esi]
		INC esi
		INC I
		;---интервал [0-9]
		CMP BL, '9'
		JG L_N1_CHECK_ELSE_A_F
		CMP BL,'0'
		JL L_INPUT_LOOP
		INC NUM1
		JMP L_N1_CHECK

		;---интервал [A-F]
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
	;Перевод первого числа в десятичную СС (из строки BUF в переменную NUM1)
	MOV esi, OFFS1 
	MOV DI, 16;				исходное основание
	MOV EAX, 0
	XOR BX,BX
	L2:
		MOV BL, [ESI]
		CMP BL, 13
		JE END_LOOP1;		если ентер то конец цикла
		CMP BL, ' '
		JE END_LOOP1;		если пробел то конец цикла
	
	
		CMP BL, '9'
		JLE NUMBLOCK
		SUB BL, 7;			если символ - буква, то прибаляем смещение между 'A' и '9' по ASKII
		NUMBLOCK:
		SUB BL, '0'; вычесть из введенного символа код нуля
		
		MUL DI; умножить значение AX на 10, результат – в AX
		ADD AX, BX;
		
		INC ESI		
		JMP L2;				следующая итерацыя
	END_LOOP1:
	MOV NUM1, eax
L_INPUT_LOOP_END:





;--------------------------------------
;Ввод строки 2
L_INPUT2_LOOP:
	PUSH OFFSET STRN2
	CALL lstrlenA@4
	PUSH 0				;5
	PUSH OFFSET LENS    ;4
	PUSH EAX			;3
	PUSH OFFSET STRN2	;26
	PUSH DOUT			;1
	CALL WriteConsoleA@20;			выводим информационное сообщение 
	
	PUSH 0
	PUSH OFFSET LENS
	PUSH 200
	PUSH OFFSET BUF
	PUSH DIN
	CALL ReadConsoleA@20;			чтение строки в buf, длина в LENS

	
	;---------------------------------
	;Преобразование строчных латинских букв к верхнему регистру
	MOV esi, OFFSET BUF
	MOV i, 2;				2 последних символа - смещение каретки и переход на новую строку

	L_TOUPPER2:
		MOV eax,I
		CMP eax, LENS
		JGE L_TOUPPER2_END;	если завершён цикл по строке то выходим из цикла
		MOV BL, [esi];		перемещаем текущую букву в регистр BL
		INC i;				увеличение счётчика
		INC ESI;			увеличение указателя на букву
		CMP BL, 'a' ;		
		JL L_TOUPPER2;		если буква не лежит в отрезке [a-z], то переход к следующей
		CMP BL, 'z' ;		иначе преобразование к верхнему регистру
		JG L_TOUPPER2;
		
		SUB BL, 'a'
		ADD BL, 'A' 
		MOV [esi-1], BL;	т.к. указатель увеличился выше, то нужно отнять единицу для установки текущей буквы
		JMP L_TOUPPER2
	L_TOUPPER2_END:


	;------------------------------------
	; проверка корректности строки.первое число
	MOV OFFS1, OFFSET BUF
	MOV i,2
	MOV esi, OFFSET BUF
	MOV NUM2, 0
	L_N2_CHECK:
		MOV eax,I
		CMP eax, LENS
		JGE L_N2_CHECK_END;	если завершён цикл по с

		MOV BL, [esi]
		INC esi
		INC I
		CMP BL, '9'
		;---интервал [0-9]
		CMP BL, '9'
		JG L_N2_CHECK_ELSE_A_F
		CMP BL,'0'
		JL L_INPUT2_LOOP
		INC NUM2
		JMP L_N2_CHECK

		;---интервал [A-F]
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
	;Перевод второго числа в десятичную СС (из строки BUF в переменную NUM1)
	MOV esi, OFFS1 
	MOV DI, 16;				исходное основание
	MOV EAX, 0
	XOR BX,BX
	L2_2:
		MOV BL, [ESI]
		CMP BL, 13
		JE END_LOOP2;		если ентер то конец цикла
		CMP BL, ' '
		JE END_LOOP2;		если пробел то конец цикла
	
	
		CMP BL, '9'
		JLE NUMBLOCK2
		SUB BL, 7;			если символ - буква, то прибаляем смещение между 'A' и '9' по ASKII
		NUMBLOCK2:
		SUB BL, '0'; вычесть из введенного символа код нуля
		
		MUL DI; умножить значение AX на 10, результат – в AX
		ADD AX, BX;
		
		INC ESI		
		JMP L2_2;				следующая итерацыя
	END_LOOP2:
	MOV NUM2, eax
L_INPUT2_LOOP_END:


MOV EAX, NUM1
ADD EAX, NUM2
MOV NUM1, EAX

;----------------------------------------------------------------------
;подсчёт числа знаков, запись в i
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
;запись числа в BUF
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

; выход из программы 
PUSH 0; параметр: код выхода
CALL ExitProcess@4
MAIN ENDP
END MAIN

