
.386
.MODEL FLAT

.CODE; сегмент кода
_FUNC@12 PROC

push ebp
mov ebp, esp
mov esi, [esp] + 8
mov al, [esp] + 12
cmp al,10
je if_empty
mov ecx, [esp] + 16
cmp ecx,0
je if_empty

Perebor:
mov bl, [esi]
cmp bl, '0'
jb end2
cmp bl, '9'
ja end2
end1 :
mov al, [esp] + 12
mov[esi], al
end2 :
inc esi
loop Perebor

if_empty:
mov esp, ebp
pop ebp
RET 12
_FUNC@12 ENDP
END