extern puts
extern printf
extern strlen

section .data
filename: db "./input.dat",0
inputlen: dd 2263
fmtstr: db "Key: %d",0xa,0
new: db '0',0
rec: times 255 db 0
subst: db "enx pdlomivtsuwjkabrgfzc.hyq", 0
        ; " .bcdefghipklmaonqrstujwxyzv"
table: db "aqbrcwdee fugthyiijokplfmhn.ogpdqarssltkumvjwnxbyzzv c.x", 0

section .text
global main

; TODO: define functions and helper functions
num:
    sub bl, 0x30
    jmp back
    
lit:
    sub bl, 0x57
    jmp back

repl:
    mov bl, byte[subst+edx]
    mov [rec+edi], bl
    inc edx
    jmp retur

lit2:
    sub bl, 0x41
    jmp retcv
    
num2:
    sub bl,0x18
    jmp retcv

main:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    sub esp, 2300
    
    ; fd = open("./input.dat", O_RDONLY);
    mov eax, 5
    mov ebx, filename
    xor ecx, ecx
    xor edx, edx
    int 0x80
    
	; read(fd, ebp-2300, inputlen);
	mov ebx, eax
	mov eax, 3
	lea ecx, [ebp-2300]
	mov edx, [inputlen]
	int 0x80

	; close(fd);
	mov eax, 6
	int 0x80

	; all input.dat contents are now in ecx (address on stack)

; TASK 1: Simple XOR between two byte streams
        push ecx
        call strlen
        pop ecx
        
        xor edx, edx
        
xor_string:        
        mov bl, byte [ecx+edx+22]
        xor byte [ecx+edx], bl
        add edx, 1
        cmp edx,eax
        jne xor_string
        
        
        pusha
	push ecx
	call puts
        add esp, 4
        popa

        add ecx, eax
        add ecx, eax
        inc ecx
        inc ecx
        
        
        
; TASK 2: Rolling XOR

        push ecx
        call strlen
        pop ecx
       
        mov edx,1
rolling_xor:        
        mov edi, edx
        mov bl, byte [ecx+edx]
            rec_xor:
            mov bh, byte [ecx+edi-1]
            xor bl,bh
            dec edi
            cmp edi, 0
            jne rec_xor
        mov [ecx+edx], bl
        add edx, 1
        cmp edx,eax
        jne rolling_xor
        

        pusha
        push ecx
        call puts
        add esp, 4
        popa

        add ecx, eax
        inc ecx
; TASK 3: XORing strings represented as hex strings

        push ecx
        call strlen
        pop ecx
        
        xor edi, edi
        shl eax,1
        inc eax
        
to_hex:
        xor ebx, ebx
        xor edx, edx
        
        mov bl, byte [ecx+edi]
        cmp bl, 0x3a
        jl num
        jg lit
        
    back:
        mov [ecx+edi], bl 
               
        inc edi
        cmp edi, eax
        jne to_hex
        
        
shr eax,1
xor edi, edi
concatenate1:
        mov bh, byte [ecx+2*edi]
        mov bl, byte [ecx+2*edi+1]
        shl bh, 4
        or bl, bh
        
        mov [ecx+edi], bl
        
        inc edi
        cmp edi, eax
        jne concatenate1
        
        
 xor edi, edi
concatenate2:
        mov bh, byte [ecx+2*edi+71]
        mov bl, byte [ecx+2*edi+72]
        shl bh, 4
        or bl, bh
        
        mov [ecx+71+edi], bl
        
        inc edi
        cmp edi, eax
        jne concatenate2

xor edi, edi    
shr eax, 1
mov edi, eax
shl eax,1
fill1:
    mov byte [ecx+edi],0
    mov byte [ecx+edi+71], 0
    inc edi
    cmp edi, eax
    jl fill1
    
        
        
shr eax,1
xor edi, edi
xor_hex_strings:        
        mov bl, byte [ecx+edi+71]
        xor byte [ecx+edi], bl
        add edi, 1
        cmp edi,eax
        jne xor_hex_strings
shl eax, 1



        pusha
        push ecx
        call puts
        add esp, 4
        popa

   
        add ecx, eax
        add ecx, eax
        inc ecx
        inc ecx
        
; TASK 4: decoding a base32-encoded string
	; TODO: compute address on stack for string 6

        push ecx
        call strlen
        pop ecx
        
	; TODO: implement and apply base32decode
	;push addr_str6
	;call base32decode
xor ebx, ebx
xor edi, edi
to5bit:
        mov bl, byte [ecx+edi]
        cmp bl,0x3a
        jl num2
        jg lit2
        retcv:
        mov [ecx+edi], bl
        inc edi
        cmp edi,eax
        jne to5bit
        
        
        push eax
        xor edx, edx
        mov ebx, 5
        div ebx
        pop eax
        
        inc edx
        mov edi, 1
pad:
        push eax
        sub eax, edi
        mov byte [ecx+eax], 0
        pop eax
        inc edi
        cmp edi, edx
        jne pad
        
xor edx, edx
xor edi, edi
xor ebx, ebx
decode:
        mov bl, byte [ecx+edi]
        shl bl, 3
        mov bh, byte [ecx+edi+1]
        shr bh, 2
        or bl, bh
        mov [ecx+edx], bl
        inc edx
        
        mov bl, byte [ecx+edi+1]
        shl bl, 6
        mov bh, byte [ecx+edi+2]
        shl bh, 1
        or bl,bh
        mov bh, byte [ecx+edi+3]
        shr bh, 4
        or bl, bh
        mov [ecx+edx], bl
        inc edx
        
        mov bl, byte [ecx+edi+3]
        shl bl, 4
        mov bh, byte [ecx+edi+4]
        shr bh, 1
        or bl, bh
        mov [ecx+edx], bl
        inc edx

        mov bl, byte [ecx+edi+4]
        shl bl, 7
        mov bh, byte [ecx+edi+5]
        shl bh, 2
        or bl, bh
        mov bh, byte [ecx+edi+6]
        shr bh, 3
        or bl, bh
        mov [ecx+edx], bl
        inc edx
        
        mov bl, byte [ecx+edi+6]
        shl bl, 5
        mov bh, byte [ecx+edi+7]
        or bl, bh
        mov [ecx+edx], bl
        inc edx
        
        add edi, 8
        cmp edi, eax
        jne decode
        

        
                       
        
	; Print the fourth string
        pusha
	push ecx
	call puts
	add esp, 4
        popa

        add ecx, eax
        inc ecx
        
; TASK 5: Find the single-byte key used in a XOR encoding
        push ecx
        call strlen
        pop ecx

        xor ebx, ebx
        xor edx, edx
        mov bl,142

bruteforce_singlebyte_xor:
        xor byte [ecx+edx], bl
        inc edx
        cmp edx,eax
        jnz bruteforce_singlebyte_xor
        

        pusha
        push ecx
        call puts
        add esp, 4
        popa

        pusha
        push ebx
        push fmtstr
        call printf
        add esp, 8
        popa

        add ecx, eax
        inc ecx
; TASK 6: Break substitution cipher

        push ecx
        call strlen
        pop ecx
        
xor edi, edi
xor edx, edx
recurenta:
        mov dl, byte [ecx+edi]
        add byte [rec+edx],1
        inc edi
        cmp edi, eax
        jne recurenta
        
xor edi, edi
xor edx, edx
xor ebx, ebx
subs:
        mov bl, byte [rec+edi]
        cmp bl,0
        jne repl
        retur:
        inc edi
        cmp edi, 255
        jne subs
        

xor edi, edi
xor edx, edx   
   
replace:
        mov dl, byte [ecx+edi]
        mov dl, byte [rec+edx]  
        mov [ecx+edi], dl
        inc edi
        cmp edi, eax
        jne replace
        
        pusha
        push ecx
        call puts
        add esp, 4
        popa

	push table
	call puts
	add esp, 4

	; Phew, finally done
    xor eax, eax
    leave
    ret
