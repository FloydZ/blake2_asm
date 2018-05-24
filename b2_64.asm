bits 64

b2s_iv:
    dd 0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A
    dd 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19

b2s_idx16:
    dw 0xC840, 0xD951, 0xEA62, 0xFB73 
    dw 0xFA50, 0xCB61, 0xD872, 0xE943

b2s_sigma64:
    dq 0xfedcba9876543210, 0x357b20c16df984ae 
    dq 0x491763eadf250c8b, 0x8f04a562ebcd1397 
    dq 0xd386cb1efa427509, 0x91ef57d438b0a6c2 
    dq 0xb8293670a4def15c, 0xa2684f05931ce7bd 
    dq 0x5a417d2c803b9ef6, 0x0dc3e9bf5167482a

struc b2s_ctx
  state  resb 32
  buffer resb 64
  len    resd 2
  index  resd 1
  outlen resd 1
endstruc

%define a r8
%define b r9
%define c r10
%define d r11

%define t0 rdx
%define x1 r13

;void b2b_g(uint64_t *x, uint16_t idx, 
;    uint64_t x0, uint64_t x1) 
b2s_g:
;TODO Super kacke
    mov     a, rsi
    mov     b, rsi
    mov     c, rsi
    mov     d, rsi
    
    sar     a, 0
    sar     b, 4
    sar     c, 8
    sar     d, 12
    
    lea     a, [rdi+a*4]
    lea     b, [rdi+b*4]
    lea     c, [rdi+c*4]
    lea     d, [rdi+d*4]

    ;Save x1
    mov     x1, rcx

    ; load ecx with rotate values
    mov     ecx, 07080C10h
    ; x[a] = PLUS(x[a],x[b]) + x0; 
    add     t0, [b]
q_l1:
    mov     bl, 1
q_l2:
    ; also x[c] = PLUS(x[c],x[d]);
    add    t0, [a]
    mov    [a], t0
    ; x[d] = ROTATE(XOR(x[d],x[a]),cl);
    ; also x[b] = ROTATE(XOR(x[b],x[c]),cl);
    xor     t0, [d]
    ror     t0, cl
    mov     [d], t0
    xchg    cl, ch
    xchg    c, a
    xchg    d, b
    inc     ebx
    jpo     q_l2
    ; x[a] = PLUS(x[a],x[b]) + x1; 
    add     t0, x1     ; x1
    ; --------------------------------------------
    shr    ecx, 16
    jnz    q_l1

    ret

; void b2s_compress (b2s_ctx *ctx, int last)
_b2s_compressx:
;Save that shit
    mov     r8, rdi
    mov     r9, rsi

    ; create space for v + m
    sub     rsp, 124
    mov     rdi, rsp   

    mov     rsi, rdi
    mov     rax, b2s_iv 
b2t_l1:                      ; first is ctx->state
    mov     ecx, 32
                             ; then b2s_iv
    rep     movsb
    cmc                      ; complement
    xchg    rsi, rax
    jc      b2t_l1            ; continue if carry
    



; void b2s_init (b2s_ctx *ctx, uint32_t outlen, 
;   void *key, uint32_t keylen, uint32_t rnds)
_b2s_initx:
    ;   rdi = [ctx]
    ;   rsi = outlen
    ;   rdx = [key]   
    ;   rcx = keylen
    ;   R8  = rnds
    
    ret


; void b2s_update (b2s_ctx *ctx, 
;   void *input, uint32_t len)
_b2s_updatex:
    ;   rdi = [ctx]
    ;   rsi = [key]   
    ;   rdx = len
