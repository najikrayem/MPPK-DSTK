

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "mppktk_config.h"

// private key
typedef struct {
    // Univariate polynomial f has degree lambda. Randomly choose lambda+1
    // coefficients from GF(tp) = [0, tp - 1].
    p_t f[M];

    // R0 is a non-zero even integer randomly chosen from [2, tp - 2].
    p_t R0;

    // Univariate polynomial Ephi has one variable which is the message. It has
    // n + lambda - 1 coefficients randomly chosen form GF(tp) = [0, tp - 1].
    p_t Ephi[n + lam - 1];

} SK;


// public key
typedef struct {
    // todo
} PK;


/**
 * @brief Generate a private key
 *
 * @param sk OUT: Pointer to the private key
 * @param pk OUT: Pointer to the public key
 */
void KeyGen(SK* sk, PK* pk);


/**
 * @brief Sign a message
 *
 * @param pk IN: Pointer to the public key
 * @param sk IN: Pointer to the private key
 * @param message IN: Pointer to the message
 * @param message_len IN: Length of the message
 * @param signature OUT: Pointer to the signature
 */
void Sign(const PK* pk, const SK* sk, const uint8_t* message, uint64_t message_len, uint8_t* signature);


/**
 * @brief Verify a signature
 *
 * @param pk IN: Pointer to the public key
 * @param message IN: Pointer to the message
 * @param message_len IN: Length of the message
 * @param signature IN: Pointer to the signature
 * @return 1 if the signature is valid, 0 otherwise
 */
bool Verify(const PK* pk, const uint8_t* message, uint64_t message_len, const uint8_t* signature);

