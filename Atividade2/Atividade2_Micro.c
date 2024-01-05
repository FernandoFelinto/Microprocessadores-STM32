// QUESTÃO 1
void q1(void)
{
    Utility_Init();

    RCC->APB1ENR |= RCC_APB1ENR_DACEN; // habilita o clock da interface digital do DAC

    DAC->CR |= DAC_CR_BOFF1; // desabilita o buffer analógico do DAC1
    DAC->CR |= DAC_CR_EN1;   // habilita o canal 1 do DAC

    RCC->AHB1ENR |= (1 << 0);
    GPIOA->MODER |= (0b11 << 8);

    while (1)
    {

        for (int contador = 0; contador < 4095; contador += 1)
        {
            DAC->DHR12R1 = contador;
            Delay_ms(1);
        }

        for (int contador = 4095; contador < 4095; contador -= 1)
        {
            DAC->DHR12R1 = contador;
            Delay_ms(1);
        }
    }
}

// QUESTÃO 2

void q2(void)
{

    const int samples[210] = {1861, 1886, 1911, 1936, 1961, 1986, 2011, 2036, 2061, 2086, 2111, 2136, 2161, 2186, 2211, 2236, 2261, 2286, 2311, 2336, 2361, 2386, 2411, 2436, 2461, 2486, 2511, 2536, 2561, 2586, 2611, 2636, 2661, 2686, 2711, 2736, 2761, 2786, 2811, 2836, 2861, 2886, 2911, 2936, 2961, 2986, 3011, 3036, 3061, 3086, 3111, 3111, 3086, 3061, 3036, 3011, 2986, 2961, 2936, 2911, 2886, 2861, 2836, 2811, 2786, 2761, 2736, 2711, 2686, 2661, 2636, 2611, 2586, 2561, 2536, 2511, 2486, 2461, 2436, 2411, 2386, 2361, 2336, 2311, 2286, 2261, 2236, 2211, 2186, 2161, 2136, 2111, 2086, 2061, 2036, 2011, 1986, 1961, 1936, 1911, 1886, 1861, 1836, 1811, 1786, 1761, 1736, 1711, 1686, 1661, 1636, 1611, 1586, 1561, 1536, 1511, 1486, 1461, 1436, 1411, 1386, 1361, 1336, 1311, 1286, 1261, 1236, 1211, 1186, 1161, 1136, 1111, 1086, 1061, 1036, 1011, 986, 961, 936, 911, 886, 861, 836, 811, 786, 761, 736, 711, 686, 661, 636, 611, 586, 586, 611, 636, 661, 686, 711, 736, 761, 786, 811, 836, 861, 886, 911, 936, 961, 986, 1011, 1036, 1061, 1086, 1111, 1136, 1161, 1186, 1211, 1236, 1261, 1286, 1311, 1336, 1361, 1386, 1411, 1436, 1461, 1486, 1511, 1536, 1561, 1586, 1611, 1636, 1661, 1686, 1711, 1736, 1761, 1786, 1811, 1836};

    RCC->AHB1ENR |= 1; // habilita o clock do GPIOA
    GPIOA->MODER |= (0b11 << 8) | 0b11 << 10;
    ;                        // inicialização do pino PA4 no modo analógico
    RCC->APB1ENR |= 1 << 29; // habilita o clock da interface digital do DAC
    DAC->CR |= 1;            // habilita o canal 1 do DAC
    int contador = 0;        // indexador do array de amostras do sinal
    while (1)
    {
        DAC->DHR12R1 = samples[contador]; // escreve no DAC1
        ++contador;                       // atualiza o indexador
        if (contador == 200)
            contador = 0; // verifica se chegou ao final do array
        Delay_us(10000);  // aguarda para a próxima amostra
    }
}

// QUESTÃO 5

void q5()
{

    Utility_Init(); // inicializa o sistema de clock e funções de temporização
    USART1_Init();  // inicializa a USART1

    const int samples[] = {2481, 2791, 3082, 3334, 3532, 3664, 3720, 3698, 3599, 3428, 3198, 2922, 2618, 2306, 2004, 1733, 1509, 1347, 1257, 1245, 1311, 1452, 1657, 1915, 2209, 2520, 2829, 3116, 3362, 3553, 3675, 3722, 3690, 3581, 3403, 3166, 2885, 2579, 2267, 1968, 1702, 1486, 1332, 1252, 1249, 1325, 1474, 1687, 1950, 2248, 2560, 2867, 3149, 3389, 3572, 3685, 3722, 3680, 3562, 3376, 3133, 2848, 2540, 2228, 1933, 1672, 1463, 1318, 1247, 1254, 1340, 1497, 1718, 1986, 2286, 2599, 2904, 3182, 3416, 3590, 3694, 3721, 3670, 3543, 3348, 3099, 2810, 2501, 2190, 1898, 1643, 1441, 1305, 1244, 1261, 1356, 1522, 1749, 2022, 2325, 2638, 2940, 3214, 3441, 3607, 3702, 3719, 3658, 3522, 3320, 3065, 2772, 2462, 2152, 1864, 1614, 1420, 1293, 1241, 1268, 1373, 1547, 1781, 2059, 2364, 2676, 2976, 3245, 3465, 3623, 3708, 3716, 3645, 3500, 3291, 3030, 2734, 2423, 2115, 1830, 1587, 1400, 1282, 1240, 1277, 1391, 1573, 1813, 2096, 2403, 2715, 3012, 3276, 3489, 3638, 3714, 3711, 3631, 3477, 3260, 2994, 2696, 2383, 2077, 1797, 1560, 1381, 1273, 1241, 1287, 1410, 1600, 1847, 2133, 2442, 2753, 3047, 3305, 3511, 3651, 3718, 3705, 3615, 3453, 3230, 2958, 2657, 2344, 2041, 1765, 1534, 1364, 1264, 1242, 1299, 1430, 1628, 1881, 2171, 2481};
    RCC->AHB1ENR |= 1; // habilita o clock do GPIOA
    GPIOA->MODER |= (0b11 << 8) | 0b11 << 10;
    ;                        // inicialização do pino PA4 no modo analógico
    RCC->APB1ENR |= 1 << 29; // habilita o clock da interface digital do DAC
    DAC->CR |= 1;            // habilita o canal 1 do DAC
    int contador = 0;        // indexador do array de amostras do sinal
    while (1)
    {
        DAC->DHR12R1 = samples[contador]; // escreve no DAC1
        ++contador;                       // atualiza o indexador
        if (contador == 200)
            contador = 0; // verifica se chegou ao final do array
        Delay_us(1);      // aguarda para a próxima amostra
    }
}

/*CONVERTER AUDIO:

import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as sw
import IPython.display as Id


# https://convertio.co/pt/download/578445d763782dc50b112e12b4847eb1a4d108/


# Importando o audio em questão.
taxa_amostragem, audio_data = sw.read('grav_weslley.wav')

# Necessario calcular as componentes par e impar do sinal, pois somadas geram o s(t):

esquerdo = audio_data[:,0] # lado esquerdo
direito = np.flip(esquerdo) # lado direito

componente_par = (esquerdo + direito)/2 # Componente par (even)
componente_impar = (esquerdo - direito)/2 # Componente impar (odd)

# O sinal s(t) de forma literal, seria em um grafico, o eixo y
audio_corrigido = componente_par+componente_impar # sinal s(t)

tempo = np.arange(len(audio_corrigido)) / taxa_amostragem # variavel que mantem os pontos do
# eixo x do grafico


# Array de exemplo
meu_array = audio_corrigido

# Adicionar 32768 a cada elemento do array usando list comprehension
meu_array = [int((x + 32768)/256) for x in meu_array]

# Unir os elementos do array em uma string separada por vírgula
array_formatado = ','.join(map(str, meu_array))

# Escrever a string no arquivo de texto
with open('array.txt', 'w') as arquivo:
    arquivo.write(array_formatado)



Id.Audio(data=audio_corrigido, rate=taxa_amostragem)*/

// CODIGO PARA COLOCAR O VETOR

uint8_t grav_thiago[TAMANHO_VETOR] = {};

// QUESTÃO 6

void q6(void)
{

    Utility_Init(); // inicializa o sistema de clock e funções de temporização

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // habilita o clock do GPIOA
    GPIOA->MODER |= 0b11 << 8;           // inicialização do pino PA4 no modo analógico

    RCC->APB1ENR |= RCC_APB1ENR_DACEN; // habilita o clock da interface digital do DAC
    DAC->CR |= DAC_CR_EN1;             // habilita o canal 1 do DAC

    while (1)
    {

        for (uint32_t contador = 0; contador < 111616; ++contador)
        {
            DAC->DHR8R1 = grav_thiago[contador]; // escreve no DAC1
            Delay_us(22);                        // aguarda a próxima amostra
        }
    }
}

// QUESTÃO 7

void q7()
{
    Utility_Init(); // inicializa o sistema de clock e funções de temporização
    USART1_Init();  // inicializa a USART1

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // habilita o clock do GPIOA
    GPIOA->MODER |= 0b11 << 0;           // pino PA0 como entrada analógica
    GPIOA->MODER |= 0b11 << 2;           // pino PA1 como entrada analógica
    GPIOA->MODER |= 0b01 << 10;
    GPIOA->MODER |= 0b01 << 12;

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // liga o clock do ADC1

    ADC->CCR |= 0b01 << 16;           // prescaler /4
    ADC1->SQR1 = 1 << 20;             // conversão de dois canais
    ADC1->SQR3 = (1 << 5) | (0 << 0); // canais IN_1 e IN_0 (PA1 e PA0)
    ADC1->CR1 = ADC_CR1_SCAN;         // habilita o modo scan
    ADC1->CR2 = ADC_CR2_EOCS;         // sinal EOC ao fim de cada conversão
    ADC1->CR2 |= ADC_CR2_ADON;        // liga o conversor AD
    Delay_ms(1);                      // aguarda o ADC iniciar

    while (1)
    {
        ADC1->CR2 |= ADC_CR2_SWSTART; // inicia a conversão
        while (!(ADC1->SR & ADC_SR_EOC))
            ;                         // aguarda o fim da primeira conversão
        uint16_t leitura1 = ADC1->DR; // faz a leitura do valor convertido
        while (!(ADC1->SR & ADC_SR_EOC))
            ;                         // aguarda o fim da segunda conversão
        uint16_t leitura2 = ADC1->DR; // faz a leitura do valor convertido

        double formulaX = ((leitura1 * 2000) / 4095) + 500;
        double formulaY = ((leitura2 * 2000) / 4095) + 500;

        GPIOA->ODR |= (1 << 5);
        Delay_us(formulaX);
        GPIOA->ODR &= ~(1 << 5);
        GPIOA->ODR |= (1 << 6);
        Delay_us(formulaY);
        GPIOA->ODR &= ~(1 << 6);

        Delay_ms(20);
    }
}

// QUESTÃO 8

void q8(void)
{

    Utility_Init(); // inicializa o sistema de clock e funções de temporização
    USART1_Init();  // inicializa a USART1

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // liga o clock da interface digital do ADC1

    // GPIOA

    RCC->AHB1ENR |= 1;
    GPIOA->MODER |= (0b01 << 12) | (0b01 << 10) | (0b01 << 14);

    ADC->CCR |= 0b01 << 16;      // prescaler /4
    ADC1->SQR1 &= ~(0xF << 20);  // conversão de apenas um canal
    ADC1->SQR3 |= 16;            // seleção do canal a ser convertido (IN_16)
    ADC1->SMPR1 |= (7 << 18);    // tempo de amostragem igual a 480 ciclos de ADCCLK
    ADC->CCR |= ADC_CCR_TSVREFE; // liga o sensor de temperatura
    ADC1->CR2 |= ADC_CR2_ADON;   // liga o conversor AD
    Delay_ms(1);                 // aguarda o ADC iniciar

    uint32_t *p = (uint32_t *)0x1FFF7A2C;         // cria ponteiro para uma posição de memória
    uint32_t Word = p[0];                         // lê o conteúdo da memória
    uint16_t TS_CAL1 = (Word & 0x0000FFFF);       // lê o valor de TS_CAL1
    uint16_t TS_CAL2 = (Word & 0xFFFF0000) >> 16; // lê o valor de TS_CAL2

    while (1)
    {
        uint32_t leitura = 0;

        for (int16_t cont = 0; cont < 1000; ++cont)
        {
            ADC1->CR2 |= ADC_CR2_SWSTART; // inicia a conversão
            while (!(ADC1->SR & ADC_SR_EOC))
                ;                // aguarda o fim da conversão
            leitura += ADC1->DR; // acumula o valor lido
        }

        GPIOA->ODR |= (1 << 7);
        float temperatura = (((float)80 * (((float)leitura / 1000) - TS_CAL1)) / (TS_CAL2 - TS_CAL1)) + 30; // calcula a temperatura pela média
        printf("Temperatura = %.2f °C\n", temperatura);                                                     // imprime o valor da temperatura no monitor
        if (temperatura <= 45)
        {
            printf("a temperatura está dentro da faixa segura de operação\n");
            GPIOA->ODR |= (1 << 6);
        }
        else if (temperatura <= 55)
        {
            printf("a temperatura está dentro da faixa de atenção.\n");
            GPIOA->ODR &= ~(1 << 6);
            Delay_ms(500);
        }

        else
        {
            printf("a temperatura está dentro da faixa de superaquecimento.\n");
            GPIOA->ODR &= ~(1 << 7);
            GPIOA->ODR |= (1 << 6);
            for (int i = 0; i < 8; i++)
            {
                GPIOA->ODR ^= (1 << 5);
                Delay_ms(50);
            }
            Delay_ms(1000);
        }

        Delay_ms(500); // aguarda 500ms para fazer a nova leitura
    }
}

// QUESTÃO 9

void q9()
{
    Utility_Init(); // inicializa o sistema de clock e funções de temporização
    USART1_Init();  // inicializa a USART1

    RCC->AHB1ENR |= (1 << 4);
    GPIOE->MODER &= ~(0b11 << 8);
    GPIOE->PUPDR |= (0b01 << 8);

    RCC->AHB1ENR |= 1;     // habilita o clock do GPIOA
    GPIOA->MODER &= ~0b11; // pino PA0 como entrada analógica

    TIM2_Setup();

    float total = 0;

    printf("inicio\n");

    while (1)
    {
        TIM2->CNT = 0;
        if ((GPIOA->IDR & 1))
        {
            while ((GPIOA->IDR & 1))
                if (TIM2->CNT == 5000000)
                    printf("O pulso e longo demais.\n");

            total = TIM2->CNT / 1000;
            printf("%f\n", total);
        }
    }
}

void p2_q8()
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // liga o clock da interface digital do ADC1
    RCC->AHB1ENR |= 1;
    GPIOA->MODER |= 0B01 << 10 | 0b01 << 12 | 0B01 << 14;
    ADC->CCR |= 0b01 << 16;      // prescaler /4
    ADC1->SQR1 &= ~(0xF << 20);  // conversão de apenas um canal
    ADC1->SQR3 |= 16;            // seleção do canal a ser convertido (IN_16)
    ADC1->SMPR1 |= (7 << 18);    // tempo de amostragem igual a 480 ciclos de ADCCLK
    ADC->CCR |= ADC_CCR_TSVREFE; // liga o sensor de temperatura
    ADC1->CR2 |= ADC_CR2_ADON;   // liga o conversor AD
    Delay_ms(1);                 // aguarda o ADC iniciar

    uint32_t *p = (uint32_t *)0x1FFF7A2C;         // cria ponteiro para uma posição de memória
    uint32_t Word = p[0];                         // lê o conteúdo da memória
    uint16_t TS_CAL1 = (Word & 0x0000FFFF);       // lê o valor de TS_CAL1
    uint16_t TS_CAL2 = (Word & 0xFFFF0000) >> 16; // lê o valor de TS_CAL2

    while (1)
    {
        GPIOA->ODR |= 0b11 << 6;
        GPIOA->ODR &= ~(0b1 << 5);
        ADC1->CR2 |= ADC_CR2_SWSTART; // inicia a conversão
        while (!(ADC1->SR & ADC_SR_EOC))
            ; // aguarda o fim da conversão

        uint32_t media = 0;

        for (int i = 0; i < 50; i++)
        {
            media += ADC1->DR;
        }
        media /= 50;

        uint8_t temperatura = ((80 * (media - TS_CAL1)) / (TS_CAL2 - TS_CAL1)) + 30; // calcula a temperatura

        printf("Temperatura = %d °C", temperatura); // imprime o valor da temperatura no monitor
        if (temperatura <= 45)
        {
            printf(" dentro da faixa\n");
        }

        if (temperatura > 45 && temperatura <= 55)
        {
            printf(" Atenção!!!!\n");
            GPIOA->ODR &= ~(0b1 << 6);
        }

        if (temperatura > 55)
        {
            printf(" SUperaquecendo!!!!\n");
            GPIOA->ODR &= ~(0b11 << 6);
            GPIOA->ODR |= 0B1 << 5;
        }
        Delay_ms(1000); // aguarda 500ms para fazer a nova leitura
    }
}

//-------MAIN-------//
int main(void)
{
    Utility_Init(); // CHAMA A BIBLIOTECA UTILITY
    q8();
}