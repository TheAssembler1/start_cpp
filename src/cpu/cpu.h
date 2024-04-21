#pragma once

#include <cstdint>

namespace CPU {

  struct registers {
    // main register set
    union {
      struct {
        uint8_t f;
        uint8_t a;
      };
      uint16_t af;
    };
    union {
      struct {
        uint8_t c;
        uint8_t b;
      };
      uint16_t bc;
    };
    union {
      struct {
        uint8_t e;
        uint8_t d;
      };
      uint16_t de;
    };
    union {
      struct {
        uint8_t l;
        uint8_t h;
      };
      uint16_t hl;
    };

    // alternate register set
    union {
      struct {
        uint8_t f_p;
        uint8_t a_p;
      };
      uint16_t af_p;
    };
    union {
      struct {
        uint8_t c_p;
        uint8_t b_p;
      };
      uint16_t bc_p;
    };
    union {
      struct {
        uint8_t e_p;
        uint8_t d_p;
      };
      uint16_t de_p;
    };
    union {
      struct {
        uint8_t l_p;
        uint8_t h_p;
      };
      uint16_t hl_p;
    };
    
    // index registers
    uint16_t ix;
    uint16_t iy;

    uint16_t sp;
    uint16_t pc;
  };

}
