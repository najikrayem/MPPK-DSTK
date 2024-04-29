#pragma once

// Use the A configuration
#define CONFIG A


#if CONFIG == A
    #define p           19
    #define m           2
    #define n           2
    #define lam         1
    #define p_t        uint64_t

    uint16_t l[m] = {1, 1};
    #define num_noise_coef 4

    // operations
    #define ADD(a, b)   (a + b)
    #define SUB(a, b)   (a - b)
    #define MUL(a, b)   (a * b)
    #define MOD(a, b)   (a % b)
    #define LT(a, b)    (a < b)
    #define GT(a, b)    LT(b, a)
    #define EQ(a, b)    (a == b)
    #define ODD(a)      (a % 2)


#elif CONFIG == B
    // TODO
#elif CONFIG == C
    // TODO
#elif CONFIG == D
    // TODO
#endif



// Definitions that are common to all configurations
#define M                   lam + 1                 // Number of terms in f
#define X                   n + lam - 1             // Number of terms in Ephi
#define f_len_bytes         M * sizeof(p_t)        // Length of f in bytes