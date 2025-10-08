#ifndef BITS_HPP
#define BITS_HPP

#include <cstdint>
#include <type_traits>

namespace bits {

using u32 = uint32_t;
using u64 = uint64_t;

// ---- pruebas de bit j ----
inline bool is_on(u64 S, int j) { return (S >> j) & 1ULL; }
inline void turn_on(u64 &S, int j) { S |= (1ULL << j); }
inline void turn_off(u64 &S, int j) { S &= ~(1ULL << j); }
inline void toggle(u64 &S, int j) { S ^= (1ULL << j); }

// ---- básicos ----
inline u64 lsb(u64 x) { return x & -x; }                // mask del bit encendido más bajo
inline u64 clear_lsb(u64 x) { return x & (x - 1); }     // apaga el LSB
inline u64 fill_below_lsb(u64 x) { return x | (x - 1); }// pone a 1 todos los bits por debajo del LSB de x
inline u64 clear_trailing_ones(u64 x){ return x & (x + 1); } // apaga el bloque de unos finales
inline u64 least_zero_mask(u64 x){ return ~x & (x + 1); }    // máscara del cero más bajo

// ---- wrappers seguros de builtins (definidas x=0) ----
inline int ctz(u64 x) { return x ? __builtin_ctzll(x) : 64; }
inline int clz(u64 x) { return x ? __builtin_clzll(x) : 64; }
inline int msb_index(u64 x) { return x ? 63 - __builtin_clzll(x) : -1; }
inline int popcount(u64 x) { return __builtin_popcountll(x); }
inline int parity(u64 x) { return __builtin_parityll(x); }

inline bool is_pow2(u64 x){ return x && !(x & (x - 1)); }

// devuelve máscara con los n bits bajos en 1; n>=0
inline u64 lowbits(int n){ return (n >= 64) ? ~0ULL : ((1ULL << n) - 1); }

// máscara del rango [l, r] (incluyente), 0<=l<=r<64
inline u64 mask_range(int l, int r){
    if (l > r) return 0;
    return lowbits(r + 1) ^ lowbits(l);
}

// potencias de 2 (redondeos)
inline u64 round_down_pow2(u64 x){ return x ? (1ULL << msb_index(x)) : 0; }
inline u64 next_pow2(u64 x){
    if (x <= 1) return 1;
    --x; x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16; x |= x >> 32;
    return x + 1;
}

// redondeo a múltiplos de 2^k
inline u64 round_down_mult_pow2(u64 x, int k){ u64 m = lowbits(k); return x & ~m; }
inline u64 round_up_mult_pow2(u64 x, int k){ u64 m = lowbits(k); return (x + m) & ~m; }

// siguiente combinación con misma popcount (Gosper's hack)
inline u64 next_combination(u64 x){
    u64 c = x & -x, r = x + c;
    return (((r ^ x) >> 2) / c) | r;
}

} // namespace bits

#endif // BITS_HPP
