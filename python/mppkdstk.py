import numpy as np


def PowerMod(base, exp, mod):
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        #endif
        exp = exp // 2
    #endwhile
    return result
#enddef

def KeyGen(m, n, lam, l, p):

    # Euler's totient
    tp = p - 1


    # Univariate polynomial f has degree lambda. Randomly choose lambda+1
    # coefficients from GF(tp) = [0, tp - 1].
    f = np.random.randint(0, tp, size=lam + 1)

    # private ------------------------------------------------------------------

    # Univariate polynomial Ephi has one variable which is the message. It has
    # n + lambda - 1 coefficients randomly chosen form GF(tp) = [0, tp - 1].
    Ephi = np.random.randint(0, tp, size=n + lam - 1)


    # R0 is a non-zero even integer randomly chosen from [2, tp - 2].
    R0 = np.random.randint(1, ((tp - 2) // 2) + 1) * 2

    # Secret key is a tuple of f, R0, and Ephi.
    s = (f, R0, Ephi)

    # public -------------------------------------------------------------------

    # Multivariate polynomial b has m + 1 variables (m noise vars and one
    # message var). For each noise variable, there is a corresponding l_i 
    # that determines the degree of the variable in the polynomial. Therefore,
    # there is a total of (n + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1)).
    # b's coefficients are randomly chosen from GF(tp) = [0, tp - 1].
    num_noise_coef = np.prod([l[i] + 1 for i in range(m)])
    b = np.random.randint(0, tp, size=(n + 1, num_noise_coef))


    # Initialize product polynomial phi. It is the product of the univariate
    # polynomial f and the multivariate polynomial b, therefore, the number of
    # terms will be the product of the number of terms in f and b (before any
    # reductions).
    # Phi will have (n + lambda + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1))
    # terms.
    phi = np.zeros((n + lam + 1, num_noise_coef))


    # Fill in phi with the product of f and b.
    # phi = np.convolve(b.flatten(), f.flatten(), mode='full').reshape(n+lam+1, -1) TODO
    for i in range(n + 1):
        for j in range(lam + 1):
            phi[i + j, :] += b[i, :] * f[j]
        #endfor
    #endfor


    # Reduce phi modulo tp.
    phi %= tp


    # T0 is the product of R0 and the first row of b, mod tp, minus phi.
    T0 = ((R0 * b[0]) % tp) # - phi TODO


    # Noise function
    N0 = ((R0 * b[0]) % tp)
    tmp = (Ephi * phi[:,1:-1])  # TODO
    #N0 += (Ephi * phi[:,1:-1] * b) # TODO is this correct?


    # Remove the highest order and constant terms from phi.
    phi = phi[1:n+lam+1, :]


    # Calculate P. It has shape
    # (n + lambda + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1)). TODO
    P = np.zeros((n + lam - 1, num_noise_coef))


    # Fill in P.
    for i in range(n + lam):
        P[i, :] = phi[i, 0] - (Ephi[i] * phi[i, 1:-1] * b[i, :])
    #endfor


    # Reduce P modulo tp.
    P %= tp


    # Public key is a tuple of P, N0, and T0.
    v = (P, N0, T0)

    return s, v
#enddef


def Sign(v, s, mu, lam, p):

    # Hash the message here TODO

    # Euler's totient
    tp = p - 1

    # Unpack keys
    f, R0, Ephi = s
    P, N0, T0 = v

    # Select random base g from [2, tp - 1].
    g = np.random.randint(2, tp)

    # Solve the f univariate polynomial for the message.
    fmu = np.polyval(f, mu)

    # Solve the Ephi univariate polynomial for the message.
    Ephimu = np.polyval([Ephi, 0], mu) % tp

    a = (R0 * fmu) % tp
    c = (f[0] - fmu) % tp
    e = R0 * T0 * (Ephimu - fmu) % tp

    A = PowerMod(g, a, p)
    C = PowerMod(g, c, p)
    E = PowerMod(g, e, p)

    t = (A * C * E)

    return t

#enddef



def Verify(v, mu, t, m, n, lam, l, p):
    # Euler's totient
    tp = p - 1

    # unpack public key
    P, N0, T0 = v

    # unpack signature
    A, C, E = t

    # generate m random number in range [1, tp - 1]
    r = np.random.randint(1, tp, size=m)


    # initialize the polynomial Pbar. It has shape
    # (n + lambda + 1) * ((l_1 + 1) * (l_2 + 1) * ... * (l_m + 1)). TODO
    num_noise_coef = np.prod([l[i] + 1 for i in range(m)])
    Pbar = np.zeros((n + lam - 1, num_noise_coef))





# Test
p = 19
m = 2
n = 2
lam = 1
l = [1,1]

s, v = KeyGen(m, n, lam, l, p)
