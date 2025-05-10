#include <stdio.h>

// Funcoes auxiliares

int mdc(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int inverso_modular(int a, int n, int *inv) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = a;
    while (novo_r != 0) {
        int q = r / novo_r;
        int temp;

        temp = novo_t;
        novo_t = t - q * novo_t;
        t = temp;

        temp = novo_r;
        novo_r = r - q * novo_r;
        r = temp;
    }
    if (r > 1) return 0;
    if (t < 0) t += n;
    *inv = t;
    return 1;
}

int potencia_modular(int base, int expoente, int mod) {
    int resultado = 1;
    base %= mod;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        expoente /= 2;
    }
    return resultado;
}

int phi(int n) {
    int resultado = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            resultado -= resultado / i;
        }
    }
    if (n > 1) resultado -= resultado / n;
    return resultado;
}

int main() {
    int H, G, n, x, n1;

    printf("---------- VALORES DE ENTRADA ----------\n");
    printf("Informe H, G, n, x e n1 (separados por espaco): ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    // Passo 1
    printf("\nETAPA 1 - Verificando se G e n sao coprimos usando o Algoritmo de Euclides...\n");
    int a1 = G, b1 = n;
    int passo = 1;

    printf("Aplicando o Algoritmo de Euclides para G = %d e n = %d:\n", G, n);
    while (b1 != 0) {
        int resto = a1 % b1;
        printf("Passo %d: %d mod %d = %d\n", passo++, a1, b1, resto);
        a1 = b1;
        b1 = resto;
    }

    if (a1 != 1) {
        printf("MDC(G, n) = %d. G e n nao sao coprimos. Divisao modular nao permitida.\n", a1);
        return 1;
    } else {
        printf("MDC(G, n) = 1. G e n sao coprimos. Podemos continuar.\n");
    }

    // Passo 2
    int r1 = n, r2 = G;
    int t1 = 0, t2 = 1;

    printf("\nETAPA 2 - Queremos encontrar um numero t tal que %d * t congruente a 1 mod %d\n", G, n);
    printf("Vamos usar o Algoritmo Estendido de Euclides:\n\n");

    int passo_estendido = 1;
    while (r2 != 0) {
        int q = r1 / r2;
        int r = r1 - q * r2;
        int t = t1 - q * t2;

        printf("Passo %d:\n", passo_estendido++);
        printf("Quociente = %d\n", q);
        printf("Novo resto = %d - %d * %d = %d\n", r1, q, r2, r);
        printf("Novo t = %d - %d * %d = %d\n\n", t1, q, t2, t);

        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
    }

    if (r1 != 1) {
        printf("Como o MDC != 1, nao existe inverso modular.\n");
        return 1;
    }

    if (t1 < 0) t1 += n;

    int G_inv = t1;
    printf("O inverso modular de %d em Z%d e: %d\n", G, n, G_inv);

    // Passo 3
    printf("\nETAPA 3 - Calculando a = H * G^-1 mod n...\n");
    int a = (H * G_inv) % n;
    printf("a = (%d * %d) mod %d = %d\n", H, G_inv, n, a);

    // Passo 4
    printf("\nETAPA 4 - Verificando se a e n1 sao coprimos...\n");

    int mdc_a_n1 = mdc(a, n1);
    printf("Calculando o MDC entre a = %d e n1 = %d...\n", a, n1);
    printf("MDC(%d, %d) = %d\n", a, n1, mdc_a_n1);

    if (mdc_a_n1 != 1) {
        printf("Como o MDC e diferente de 1, isso significa que a e n1 possuem divisores em comum maiores que 1.\n");
        printf("Portanto, a e n1 NAO sao coprimos.\n");
        printf("Isso pode interferir nas propriedades da exponenciacao modular.\n");
    } else {
        printf("Como o MDC e igual a 1, isso significa que o unico divisor comum entre a e n1 e o numero 1.\n");
        printf("Portanto, a e n1 SAO coprimos.\n");
    }

    // Passo 5 - Determinando o expoente x1
    printf("\nETAPA 5 - Determinando o expoente x1 usando Matematica Discreta 2...\n");
    printf("Precisamos verificar se n1 = %d e primo para decidir qual teorema aplicar:\n", n1);

    int x1; // Definicao unica de x1
    if (eh_primo(n1)) {
        printf("n1 = %d E um numero primo.\n", n1);
        printf("Neste caso, podemos aplicar o Pequeno Teorema de Fermat:\n");
        x1 = n1 - 1;
    } else {
        printf("n1 = %d NAO e primo.\n", n1);
        printf("Neste caso, aplicamos o Teorema de Euler-Fermat:\n");
        x1 = phi(n1);
    }

    // Passo 6 ou 7 - Determinar x1 usando Fermat ou Euler
    printf("\nETAPA 6 ou 7 - Determinando x1 com base no resultado da etapa anterior...\n");

    if (eh_primo(n1)) {
        printf("Como n1 = %d e primo, aplicamos o Pequeno Teorema de Fermat.\n", n1);
        x1 = n1 - 1;
        printf("Segundo Fermat, x1 = n1 - 1 = %d\n", x1);
    } else {
        printf("Como n1 = %d NAO e primo, aplicamos o Teorema de Euler.\n", n1);
        x1 = phi(n1);
        printf("Segundo Euler, x1 = phi(n1) = %d\n", x1);
    }

    // Passo 8 - Decompor x como x = x1 * q + r
    printf("\nETAPA 8 - Decompondo o expoente x = %d na forma x = x1 * q + r\n", x);
    int q = x / x1;
    int r = x % x1;
    printf("q = %d / %d = %d\n", x, x1, q);
    printf("r = %d %% %d = %d\n", x, x1, r);
    printf("Portanto, x = %d * %d + %d\n", x1, q, r);

    // Passo 9 - Reescrevendo a^x mod n1 usando a propriedade modular
    printf("\nETAPA 9 - Reescrevendo a^x mod n1 usando a forma:\n");
    printf("a^x congruente a ((a^x1)^q mod n1) * (a^r mod n1)) mod n1\n");
    printf("%d^%d congruente a ((%d^%d)^%d mod %d) * (%d^%d mod %d)) mod %d\n",a,x,a,x1,q,n1,a,r,n1,n1);

    // Passo 10 - Calculos intermediarios
    printf("\nETAPA 10 - Calculando os valores intermediarios...\n");

    int x2 = potencia_modular(a, x1, n1);
    printf("x2 = a^x1 mod n1 = %d^%d mod %d = %d\n", a, x1, n1, x2);

    int x2_q = potencia_modular(x2, q, n1);
    printf("x2^q mod n1 = %d^%d mod %d = %d\n", x2, q, n1, x2_q);

    int a_r = potencia_modular(a, r, n1);
    printf("a^r mod n1 = %d^%d mod %d = %d\n", a, r, n1, a_r);

    // Passo 11 - Resultado final
    printf("\nETAPA 11 - Calculando o resultado final da congruencia modular...\n");
    int resultado_final = (x2_q * a_r) % n1;
    printf("Resultado final: ((%d * %d) mod %d) = %d\n", x2_q, a_r, n1, resultado_final);

    return 0;
}