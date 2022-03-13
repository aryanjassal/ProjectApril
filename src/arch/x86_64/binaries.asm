; If I'm being completely honest, all this works on black magic. I don't know
; how the files are imported; just that they are.

%macro include_bin 2
    section .rodata
    global %1

%1:
    incbin %2
    db 0
    %1_size: dq %1_size - %1
%endmacro

include_bin testtxt, "src/arch/x86_64/test.txt"
