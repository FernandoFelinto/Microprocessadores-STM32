#include "stm32f4xx.h"
#include "Utility.h"

//FUNÇÃO 1
void tempo(uint32_t delay){
	while(delay)--delay;
}
//FUNÇÃO 2
void aula_16_08(void){
	//*****CODIGO DO SEMAFORO*****//
#define LED1_OFF (GPIOA->ODR &= ~(1<<0)) //desliga o led_1 nivel logico baixo
#define LED1_ON (GPIOA->ODR |= (1<<0))	//liga o led_1 nivel logico alto

#define LED2_OFF (GPIOA->ODR &= ~(1<<1)) //desliga o led_2 nivel logico baixo
#define LED2_ON (GPIOA->ODR |= (1<<1))	//liga o led_1 nivel logico alto

#define LED3_OFF (GPIOA->ODR &= ~(1<<2)) //desliga o led_3 nivel logico baixo
#define LED3_ON (GPIOA->ODR |= (1<<2))	//liga o led_1 nivel logico alto

		RCC->AHB1ENR |=1; //LIGA O CLOCK DO GPIOA
		GPIOA->MODER |= 0b01 << 0; // pino PA0 como saida
		GPIOA->MODER |= 0b01 << 2; //pino PA1 como saida
		GPIOA->MODER |= 0b01 << 4;// pino PA2 como saida

		while(1){
			LED1_ON;
			tempo(20000000);
			LED1_OFF;

			LED2_ON;
			tempo(10000000);
			LED2_OFF;

			LED3_ON;
			tempo(20000000);
			LED3_OFF;
		}
}
//FUNÇÃO 3
void aula_18_08(void){
	Utility_Init();//CHAMA A BIBLIOTECA UTILITY

	RCC->AHB1ENR |=1<<2; //LIGA O CLOCK DO GPIOC
	GPIOC->MODER |= 0b01 << 0; //LIGA O PINO PC0

	while(1){
		for(int i=0; i<8;i++){
			GPIOC -> ODR ^= (1<<0);
			Delay_ms(100);
		}
		Delay_ms(1000);
	}
}
//FUNÇÃO 4
void aula_23_08(void){
	Utility_Init();
	RCC->AHB1ENR |=1; //LIGA O CLOCK DO GPIOA
	GPIOA->MODER |= (0b01 << 12);//LIGA O PINO PA6

	while(1){
		int tempo =1000;
		int control=tempo;
		while(control){
			GPIOA->ODR &= ~(1<<6);
			Delay_us(control);
			GPIOA->ODR |= (1<<6);
			Delay_us(tempo-control);
			--control;
		}

		while(control!=tempo){

			GPIOA->ODR &= ~(1<<6);
			Delay_us(control);
			GPIOA->ODR |= (1<<6);
			Delay_us(tempo-control);
			++control;
		}


	}
}
//FUNÇÃO 5
void aula_25_08(void){
// Ta = tensão alta
// Tb = tensão baixa
// T = tensão
	// T= Ta + Tb
// Fpwm = (1/Tpwm)
// duty cicle = (Ta/T) * 100%  ===> Ta = tensão alta
// O percentual do tempo em nivel alto em relação ao periodo
// V media = duty cicle * V maxima ===> voltagem/tensão

}
void aula_30_08(void){
	Utility_Init();
	//pino PA6 como saida
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (0b01 <<12);

	RCC->AHB1ENR |= 1<<4; //liga o clock da porta E
	GPIOE->MODER &= ~(0b11<<8);

	GPIOE->PUPDR |= 0b01<<8; //liga o pull-up em PE4

	while(1){
		int leitura = GPIOE->IDR & (1<<4); //variavel que guarda a leitura do registrador IDR

		if(leitura){
			GPIOA->ODR |= 1<<6;
		}else{
			GPIOA->ODR &= ~(1<<6); //quando aperta o botão k0 o led fica piscando
			Delay_ms(100);
			GPIOA->ODR |= 1<<6;
			Delay_ms(100);
		}
	}
}
void questao1(void){

	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;

		while(1){
			GPIOA -> ODR &= ~(1 << 6);
			Delay_ms(250);
			GPIOA -> ODR |= (1 << 6);
			Delay_ms(250);
		}
}
void questao2(void){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;

		while(1){
			GPIOA -> ODR &= ~(1 << 6);
			Delay_ms(100);
			GPIOA -> ODR |= (1 << 6);
			Delay_ms(1900);
		}
}
void questao3(void){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;

		while(1){
			GPIOA -> ODR &= ~(1 << 6);
			Delay_ms(50);
			GPIOA -> ODR |= (1 << 6);
			Delay_ms(1750/2);

			for(int i = 0;i<2;i++){
				GPIOA -> ODR &= ~(1 << 6);
				Delay_ms(50);
				GPIOA -> ODR |= (1 << 6);
				Delay_ms(50);
			}
			Delay_ms(1750/2);
		}
}
void questao4(void){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;
		int i = 0;

		while(1){
			GPIOA -> ODR &= ~(1 << 6);
			Delay_ms(50);
			GPIOA -> ODR |= (1 << 6);
			Delay_ms(950/i);
			i++;
		}
}
void questao5(void){


		RCC->AHB1ENR |=1<<2; //LIGA O CLOCK DO GPIOC
		GPIOC->MODER |= 0b01 << 0; //LIGA O PINO PC0

		while(1){
			for(int i=0; i<8;i++){
				GPIOC -> ODR ^= (1<<0);
				Delay_ms(50);
			}
			Delay_ms(1000);
		}

}
void questao6(int value){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;
		while(1){
			GPIOA -> ODR &= ~(1 << 6);
			Delay_us(value);
			GPIOA -> ODR |= (1 << 6);
			Delay_us(10000-value);
		}
}
void questao7(void){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;
		int flagForte = 0;
		while(1){
			int j = 1000;
			if(flagForte){
				for(int i = 0; i <= 1000; i++){
					GPIOA -> ODR &= ~(1 << 6);
					Delay_us(i);
					GPIOA -> ODR |= (1 << 6);
					Delay_us(j--);
				}
				flagForte = 0;
			}else{
				j = 0;
				for(int i = 1000; i >= 0; i--){
					GPIOA -> ODR &= ~(1 << 6);
					Delay_us(i);
					GPIOA -> ODR |= (1 << 6);
					Delay_us(j++);
				}
				flagForte = 1;
			}
		}
}
void questao8(void){

}
void questao9(void){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0b01<<12;
		GPIOA -> MODER |= 0b01<<14;

		while(1)
		{

			for(int i = 0; i < 4; i++){
				GPIOA -> ODR |= 1<<6;
				GPIOA -> ODR |= 1<<7;
				Delay_ms(1000);
				GPIOA -> ODR &= ~(1<<6);
				GPIOA -> ODR |= 1<<7;
				Delay_ms(1000);
				GPIOA -> ODR |= 1<<6;
				GPIOA -> ODR &= ~(1<<7);
				Delay_ms(1000);
				GPIOA -> ODR &= ~(1<<6);
				GPIOA -> ODR &= ~(1<<7);
				Delay_ms(1000);
			}

		}
}
void questao10(void){
	RCC -> AHB1ENR |= 0b01;

		GPIOA -> MODER |= 0B01<<12;
		GPIOA -> MODER |= 0B01<<14;
		int flagForte = 0;
		while(1){
			int j = 1000;
			if(flagForte){
				for(int i = 0; i <= 1000; i++){
					GPIOA -> ODR &= ~(1 << 6);
					GPIOA -> ODR |= (1 << 7);
					Delay_us(i);
					GPIOA -> ODR |= (1 << 6);
					GPIOA -> ODR &= ~(1 << 7);
					Delay_us(j--);
				}
				flagForte = 0;
			}else{
				j = 0;
				for(int i = 1000; i >= 0; i--){
					GPIOA -> ODR &= ~(1 << 6);
					GPIOA -> ODR |= (1 << 7);
					Delay_us(i);
					GPIOA -> ODR |= (1 << 6);
					GPIOA -> ODR &= ~(1 << 7);
					Delay_us(j++);
				}
				flagForte = 1;
			}
		}
}
void questao11(void){
	RCC -> AHB1ENR |= 0b01;

			GPIOA -> MODER |= (0B01<<0);
			GPIOA -> MODER |= (0B01<<2);
			GPIOA -> MODER |= (0B01<<4);
			GPIOA -> MODER |= (0B01<<6);
			GPIOA -> MODER |= (0B01<<8);
			GPIOA -> MODER |= (0B01<<10);
			GPIOA -> MODER |= (0B01<<12);
			GPIOA -> MODER |= (0B01<<14);

			for(int i = 0; i <= 255;i ++){
				GPIOA -> ODR = i;
				Delay_ms(100);
			}
}
void questao12(void){
	RCC -> AHB1ENR |= 0b1000;

		GPIOD -> MODER |= 0b0101010101010101;

		int flag = 1;
		while(1){
			if(flag){
				for(int i = 0; i<7; i++){
					GPIOD -> ODR |= 1<<i;
					Delay_ms(100);
					GPIOD -> ODR &= ~(1<<i);

				}
				flag = 0;
			}else{
				for(int i = 7; i>=1; i--){
					GPIOD -> ODR |= (1 << i);
					Delay_ms(100);
					GPIOD -> ODR &= ~(1 << i);

				}
				flag = 1;
			}
		}

}
void questao13(void){
#define LED1_OFF (GPIOA->ODR &= ~(1<<0)) //desliga o led_1 nivel logico baixo
#define LED1_ON (GPIOA->ODR |= (1<<0))	//liga o led_1 nivel logico alto

#define LED2_OFF (GPIOA->ODR &= ~(1<<1)) //desliga o led_2 nivel logico baixo
#define LED2_ON (GPIOA->ODR |= (1<<1))	//liga o led_1 nivel logico alto

#define LED3_OFF (GPIOA->ODR &= ~(1<<2)) //desliga o led_3 nivel logico baixo
#define LED3_ON (GPIOA->ODR |= (1<<2))	//liga o led_1 nivel logico alto

#define LED4_OFF (GPIOA->ODR &= ~(1<<3)) //desliga o led_1 nivel logico baixo
#define LED4_ON (GPIOA->ODR |= (1<<3))	//liga o led_1 nivel logico alto

#define LED5_OFF (GPIOA->ODR &= ~(1<<4)) //desliga o led_2 nivel logico baixo
#define LED5_ON (GPIOA->ODR |= (1<<4))	//liga o led_1 nivel logico alto

#define LED6_OFF (GPIOA->ODR &= ~(1<<5)) //desliga o led_3 nivel logico baixo
#define LED6_ON (GPIOA->ODR |= (1<<5))	//liga o led_1 nivel logico alto

		RCC->AHB1ENR |=1; //LIGA O CLOCK DO GPIOA
		GPIOA->MODER |= 0b01 << 0; // pino PA0 como saida
		GPIOA->MODER |= 0b01 << 2; //pino PA1 como saida
		GPIOA->MODER |= 0b01 << 4;// pino PA2 como saida
		GPIOA->MODER |= 0b01 << 6;
		GPIOA->MODER |= 0b01 << 8;
		GPIOA->MODER |= 0b01 << 10;

		while(1){
			LED1_ON;LED6_ON;
			tempo(20000000);
			LED1_OFF; LED6_OFF;

			LED1_ON;LED5_ON;
			tempo(10000000);
			LED1_OFF; LED5_OFF;

			LED3_ON; LED4_ON;
			tempo(20000000);
			LED3_OFF; LED4_OFF;

			LED2_ON; LED4_ON;
			tempo(10000000);
			LED2_OFF; LED4_OFF;

		}
}
void questao14(void){
	Utility_Init();

	RCC->AHB1ENR = 1;
	GPIOA->MODER = (0b01 << 0) | (0b01 << 2) | (0b01 << 4) | (0b01 << 6) | (0b01 << 8) | (0b01 << 10) | (0b01 << 12) | (0b01 << 14);

	const uint8_t mask[16]={ 0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A
	0b01111100, //B
	0b00111001, //C
	0b01011110, //D
	0b01111001, //E
	0b01110001}; //F

	while(1){
	for(int i = 0; i < 15; i++){
	GPIOA->ODR = mask[i];
	Delay_ms(1000);
	}
	for(int i = 15; i >= 0; i--){
	GPIOA->ODR = mask[i];
	Delay_ms(1000);
	}
	}
}
void questao17(void){
	RCC -> AHB1ENR |= 0b11000;
		GPIOD -> MODER |= 0b01;
		int indo = 1;

		while(1){
			if (indo){
				for(int i = 500; i < 2500; i+=50){

					Delay_ms(20); //evita debounce
					GPIOD -> ODR |= 1;
					Delay_us(i);
					GPIOD -> ODR &= ~(1);
				}
				indo = 0;
			}
			else{
				for(int i = 2600; i > 400; i-=50){

					Delay_ms(20);
					GPIOD -> ODR |= 1;
					Delay_us(i);
					GPIOD -> ODR &= ~(1);
				}
				indo = 1;
			}
		}
}
void questao18(void){
	RCC -> AHB1ENR |= 0b1000;

		GPIOD -> MODER |= 0b010000000101;
		int sentido = 0;
		int flagForte = 0;
		while(1){
			if(sentido){
				GPIOD -> ODR &= ~(1);
				GPIOD -> ODR |= (1<<1);
				for(int k = 0; k<2; k++){
					int j = 1000;
					if(flagForte){
						j = 0;
						for(int i = 1000; i >= 0; i--){
							Delay_ms(2);
							GPIOD -> ODR |= (1 << 5);
							Delay_us(i);
							GPIOD -> ODR &= ~(1 << 5);
							Delay_us(j++);
						}
						flagForte = 0;
					}else{
						for(int i = 0; i <= 1000; i++){
							Delay_ms(2);
							GPIOD -> ODR |= (1 << 5);
							Delay_us(i);
							GPIOD -> ODR &= ~(1 << 5);
							Delay_us(j--);
						}
						flagForte = 1;
					}
				}
				sentido = 0;
			}else{
				GPIOD -> ODR |= (1);
				GPIOD -> ODR &= ~(1<<1);
				for(int k = 0; k<2; k++){
					int j = 1000;
					if(flagForte){
						j = 0;
						for(int i = 1000; i >= 0; i--){
							Delay_ms(2);
							GPIOD -> ODR |= (1 << 5);
							Delay_us(i);
							GPIOD -> ODR &= ~(1 << 5);
							Delay_us(j++);
						}
						flagForte = 0;
					}else{
						for(int i = 0; i <= 1000; i++){
							Delay_ms(2);
							GPIOD -> ODR |= (1 << 5);
							Delay_us(i);
							GPIOD -> ODR &= ~(1 << 5);
							Delay_us(j--);
						}
						flagForte = 1;
					}
				}
				sentido = 1;
			}
		}
}
void questao19(void){
	Utility_Init();
	RCC->AHB1ENR |= 1000;
	GPIOD->MODER |= 0b01;
	GPIOD -> OTYPER |= 1;

	while(1){

	GPIOD->ODR |= 1;
	Delay_ms(500);
	GPIOD->ODR &= ~(1);
	Delay_ms(500);

	}
}
void questao21(void)
{
	Utility_Init();

    // Habilitar o clock para as portas E e A
    RCC->AHB1ENR |= (1 << 4);
    RCC->AHB1ENR |= 1;

    // Configurar os pinos PE4 como entrada e os pinos PA6 e PA7 como saída
    GPIOE->MODER &= ~(0b11 << 8);
    GPIOE->PUPDR |= (0b01 << 8);
    GPIOA->MODER |= (0b01 << 12);

    // Loop infinito
    while (1) {
        // Verificar se o botão K0 foi pressionado
        if (!(GPIOE->IDR & (1 << 4)) == 0) {
        	GPIOA -> ODR |= (1 << 6);
        }
        else{
        	GPIOA -> ODR &= ~(1 << 6);
        }
    }
}

void questao22(void)
{
	Utility_Init();

    // Habilitar o clock para as portas E e A
    RCC->AHB1ENR |= (1 << 4);
    RCC->AHB1ENR |= 1;

    // Configurar os pinos PE4 como entrada e os pinos PA6 e PA7 como saída
    GPIOE->MODER &= ~(0b11 << 8);
    GPIOE->PUPDR |= (0b01 << 8);
    GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);
    GPIOA->MODER |= (0b01 << 12) | (0b01 << 14);

    // Loop infinito
    while (1) {
        // Verificar se o botão K0 foi pressionado
        if (!(GPIOE->IDR & (1 << 4)) == 0) {
        	GPIOA -> ODR |= (1 << 6);
        }
        else{
        	GPIOA -> ODR &= ~(1 << 6);
        }

        // Verificar se o botão K1 foi pressionado
		if (!(GPIOE->IDR & (1 << 3)) == 0) {
			GPIOA -> ODR |= (1 << 7);
		}
		else{
			GPIOA -> ODR &= ~(1 << 7);
		}
    }
}

void questao23(void)
{
	Utility_Init();

    // Habilitar o clock para as portas E e A
    RCC->AHB1ENR |= (1 << 4);
    RCC->AHB1ENR |= 1;

    // Configurar os pinos PE4 como entrada e os pinos PA6 e PA7 como saída
    GPIOE->MODER &= ~(0b11 << 8);
    GPIOE->PUPDR |= (0b01 << 8);
    GPIOA->MODER |= (0b01 << 12);
    GPIOA->MODER &= ~(0b11 << 14);

    // Loop infinito
    while (1) {
        // Verificar se o botão K0 foi pressionado
        if ((GPIOE->IDR & (1 << 4)) == 0) {
            // Esperar um curto intervalo para evitar debounce
            Delay_ms(50);
            // Verificar novamente se o botão K0 continua pressionado
            if ((GPIOE->IDR & (1 << 4)) == 0) {
                // Inverter o estado do LED D2
                GPIOA->ODR ^= (1 << 6);
                // Esperar até que o botão K0 seja liberado
                while ((GPIOE->IDR & (1 << 4)) == 0) {
                    Delay_ms(50);
                }
            }
        }
    }
}

void questao24(void)
{
	Utility_Init();

    // Habilitar o clock para as portas E e A
    RCC->AHB1ENR |= (1 << 4);
    RCC->AHB1ENR |= 1;

    // Configurar os pinos PE4 como entrada e os pinos PA6 e PA7 como saída
    GPIOE->MODER &= ~(0b11 << 8);
    GPIOE->PUPDR |= (0b01 << 8);
    GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);
    GPIOA->MODER |= (0b01 << 12) | (0b01 << 14);

    // Loop infinito
    while (1) {
        // Verificar se o botão K0 foi pressionado
    	if (!(GPIOE->IDR & (1 << 3)) == 0){
    		Delay_us(50);
    		if ((!(GPIOE->IDR & (1 << 3)) == 0) || (!(GPIOE->IDR & (1 << 4)) == 0)) {
    						GPIOA -> ODR |= (1 << 6);
    						GPIOA -> ODR |= (1 << 7);
		}else{
			GPIOA -> ODR &= ~(1 << 7);
			GPIOA -> ODR &= ~(1 << 6);
		}
    }
   }
}

void questao25(void){

	Utility_Init();

	//habilita o clock do GPIOA
	RCC->AHB1ENR |= 1;
	 //habilita o clock do GPIOE
	RCC->AHB1ENR |= 1<<4;

	//configurando PA6 como saída
	GPIOA->MODER |= (0b01 << 12);
	//configurando PA7 como saída
	GPIOA->MODER |= (0b01 << 14);

	//Configurando o pino PE3 como entrada
	GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);

	//Configurando o pino PE4 como entrada
	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->PUPDR |= (0b01 << 8);

	while(1){
			(GPIOA->ODR |= (1 << 6));
			(GPIOA->ODR |= (1 << 7));

			if(!(GPIOE->IDR & (1 << 4)) && !!(GPIOE->IDR & (1 << 3))){
				uint32_t cont = 0;
			while(!(GPIOE->IDR & (1 << 4))){
				Delay_ms(100);
					if(!(GPIOE->IDR & (1 << 3))){
						if(cont<=1000){
							(GPIOA->ODR &= ~(1 << 6));
							(GPIOA->ODR &= ~(1 << 7));
							}
						}
					else{
							(GPIOA->ODR |= (1 << 6));
							(GPIOA->ODR |= (1 << 7));
						}
							cont += 100;
				}
			}
	}
}
void questao26(void){
	Utility_Init();

	RCC -> AHB1ENR |= 0b11000;

	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->PUPDR |= (0b01 << 8);
	GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);
	GPIOD -> MODER |= 0b01;
	int controle = 600;

	while(1){
		if (!(GPIOE->IDR & (1 << 4)) && (controle < 2500)){
				Delay_ms(20);
				GPIOD -> ODR |= 1;
				Delay_us(controle+=50);
				GPIOD -> ODR &= ~(1);
		}
		if(!(GPIOE->IDR & (1 << 3)) && (controle > 300)){

				Delay_ms(20);
				GPIOD -> ODR |= 1;
				Delay_us(controle-=50);
				GPIOD -> ODR &= ~(1);
		}
	}
}
void questao27(void){
// PE3 K1     -    PE4 K0      -     PA0 KUP
Utility_Init();
RCC -> AHB1ENR |= (1 << 0) | (1 << 4);
GPIOA-> MODER |= (0b01 << 0) | (0b01 << 2) | (0b01 << 4) | (0b01 << 6)| (0b01 << 8)| (0b01 << 10)| (0b01 << 12) | (0b01 << 14);

GPIOA -> MODER &= ~(0b11 << 0)  ; // configura PA0 como entrada (sempre que habilitar a entrada)
GPIOA -> PUPDR |= (0b10 << 0) ; // Liga o resistor de pull down em PA0

GPIOE -> MODER &= ~(0b11 << 8)  &  ~(0b11 << 6); // configura PE4 como entrada (sempre que habilitar a entrada)
GPIOE -> PUPDR |= (0b01 << 8)  | (0b01 << 6); // Liga o resistor de pull up em PE4 (para ligar o pull down seria 0b10)

const uint8_t mask[16]={ 0b00111111, //0
0b00000110, //1
0b01011011, //2
0b01001111, //3
0b01100110, //4
0b01101101, //5
0b01111101, //6
0b00000111, //7
0b01111111, //8
0b01101111, //9
0b01110111, //A
0b01111100, //B
0b00111001, //C
0b01011110, //D
0b01111001, //E
0b01110001}; //F

while(1){
int leitura_k0 = GPIOE -> IDR & (1 << 4);
int leitura_k1 = GPIOE -> IDR & (1 << 3);
int leitura_kup = GPIOA -> IDR & (1 << 0);

if(leitura_kup){ // 1
GPIOA->ODR = mask[1] << 1;
}

if(!leitura_k0){ // 2
GPIOA->ODR = mask[2] << 1;
}

if(!leitura_k1){ // 3
GPIOA->ODR = mask[3] << 1;

}



}
}
//-------MAIN-------//
int main(void)
{
	Utility_Init();//CHAMA A BIBLIOTECA UTILITY
	questao18();
}