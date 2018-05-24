/**  
  Copyright © 2015 Odzhan. All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.*/
  
#ifndef B2s_H
#define B2s_H

#include <stdint.h>

#include "macros.h"

#define BLAKE2s_CBLOCK        64
#define BLAKE2s_DIGEST_LENGTH 32
#define BLAKE2s_LBLOCK        BLAKE2s_DIGEST_LENGTH/4
#define BLAKE2s_MAXKEY        32

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef union blake_st_t {
  uint8_t  b[BLAKE2s_DIGEST_LENGTH];
  uint32_t w[BLAKE2s_DIGEST_LENGTH/4];
  uint64_t q[BLAKE2s_DIGEST_LENGTH/8];
} blake_st;

typedef union blake_blk_t {
  uint8_t  b[BLAKE2s_CBLOCK];
  uint32_t w[BLAKE2s_CBLOCK/4];
  uint64_t q[BLAKE2s_CBLOCK/8];
} blake_blk;

typedef union blake_len_t {
  uint8_t  b[8];
  uint32_t w[2];
  uint64_t q;
} blake_len;

#pragma pack(push, 1)
typedef struct _b2s_ctx {
  blake_st  s;
  blake_st  b2s_iv;
  blake_blk x;
  blake_len len;
  uint32_t  idx;
  uint32_t  outlen;
  uint16_t  v_idx[8];
  uint64_t  sigma[10];
} b2s_ctx;
#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

  void b2s_init (b2s_ctx*, uint32_t, void*, uint32_t);
  void b2s_update (b2s_ctx*, void*, uint32_t);
  void b2s_final (void*, b2s_ctx*);
  
  void b2s_initx (b2s_ctx*, uint32_t, void*, uint32_t);
  void b2s_updatex (b2s_ctx*, void*, uint32_t);
  void b2s_finalx (void*, b2s_ctx*);
  
#ifdef __cplusplus
}
#endif

#endif