#include <stdint.h>

#include "mppktk.h"
#include "random.h"


/**
 * @brief Helper function to create a string of random big integers modulo q.
 * 
 * @param str OUT: Pointer to the string to be filled with random characters.
 * @param len IN: Length of the string
 * @param q IN: Modulus
 */
static inline void RandMod(p_t* str, uint32_t len, p_t q){
   for (uint32_t i = 0; i < len; i++){
        randBytes(str[i], sizeof(p_t));
        str[i] = MOD(str[i], q);
   } 
}



void KeyGen(SK* sk, PK* pk){

    // precomputations
    p_t tp = SUB(p, 1);                // Euler's totient of p
    p_t tp_minus_1 = SUB(tp, 1);       // tp - 1; used in ranges

    // Univariate polynomial f has degree lambda. Randomly choose lambda+1
    // coefficients from GF(tp) = [0, tp - 1].
    RandMod(sk->f, M, tp_minus_1);

    // private -----------------------------------------------------------------

    // Univariate polynomial Ephi has one variable which is the message. It has
    // n + lambda - 1 coefficients randomly chosen form GF(tp) = [0, tp - 1].
    RandMod(sk->Ephi, X, tp_minus_1);


    // R0 is a non-zero even integer randomly chosen from [2, tp - 2].
    while (true) {
        RandMod(sk->R0, 1, tp_minus_1);
        if (EQ(sk->R0, 0) || EQ(sk->R0, 1) || EQ(sk->R0, tp_minus_1)) {
            continue;
        }
        break;
    }   // TODO optimize

    // public ------------------------------------------------------------------

    // Multivariate polynomial b has m + 1 variables (m noise vars and one
    // message var). For each noise variable, there is a corresponding l_i 
    // that determines the degree of the variable in the polynomial. Therefore,
    // there is a total of (n + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1)).
    // b's coefficients are randomly chosen from GF(tp) = [0, tp - 1].
    p_t b[n + 1][num_noise_coef];
    RandMod(b, (n + 1) * num_noise_coef, tp_minus_1);


    // Initialize product polynomial phi. It is the product of the univariate
    // polynomial f and the multivariate polynomial b, therefore, the number of
    // terms will be the product of the number of terms in f and b (before any
    // reductions).
    // Phi will have (n + lambda + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1))
    // terms.
    p_t phi[n + lam + 1][num_noise_coef] = {0};


    // Fill in phi with the product of f and b.
    for (uint32_t i = 0; i < n + 1; i++) {
        for j in range(lam + 1):
            phi[i + j, :] += b[i, :] * f[j]
        //endfor
    //endfor


    // Reduce phi modulo tp.
    phi %= tp


    // T0 is the product of R0 and the first row of b, mod tp, minus phi.
    T0 = ((R0 * b[0]) % tp) // - phi TODO


    // Noise function
    N0 = ((R0 * b[0]) % tp)
    tmp = (Ephi * phi[:,1:-1])  // TODO
    //N0 += (Ephi * phi[:,1:-1] * b) // TODO is this correct?


    // Remove the highest order and constant terms from phi.
    phi = phi[1:n+lam+1, :]


    // Calculate P. It has shape
    // (n + lambda + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1)). TODO
    P = np.zeros((n + lam - 1, num_noise_coef))


    // Fill in P.
    for i in range(n + lam):
        P[i, :] = phi[i, 0] - (Ephi[i] * phi[i, 1:-1] * b[i, :])
    //endfor


    // Reduce P modulo tp.
    P %= tp


    // Public key is a tuple of P, N0, and T0.
    v = (P, N0, T0)

    return s, v
}