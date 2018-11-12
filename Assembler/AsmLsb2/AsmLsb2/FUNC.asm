
.386
.MODEL FLAT

.CODE; сегмент кода
_FUNC@12 PROC
push ebp
mov ebp, esp
mov ecx, [esp] + 16
mov esi, [esp] + 8
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
mov esp, ebp
pop ebp
RET 12
_FUNC@12 ENDP
END