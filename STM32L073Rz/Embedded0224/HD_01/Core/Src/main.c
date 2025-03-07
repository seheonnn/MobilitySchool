typedef unsigned int uint32_t;
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
	volatile uint32_t BRR;
} GPIO_TypeDef;

typedef enum {
	GPIO_HIGH,
	GPIO_LOW
	// GPIO_PIN_RESET = 0U,
  // GPIO_PIN_SET
} GPIO_PinState;

#define GPIO_2BIT_POS_MASK ((uint32_t) 0x00000003U) 
#define GPIO_1BIT_POS_MASK ((uint32_t) 0x00000001U) 
#define GPIO_PIN_8_POS     8
#define GPIO_PIN_4_POS     4

#define PERIPH_BASE (0x40000000UL)
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE (AHBPERIPH_BASE + 0x00001000UL)
#define RCC_GPIOA (*(volatile uint32_t*)(RCC_BASE + 0x0000002CUL))
#define RCC_GPIOB (*(volatile uint32_t*)(RCC_BASE + 0x0000002CUL))

#define GPIOA             ((GPIO_TypeDef *) 0x50000000U)
#define GPIOB 						((GPIO_TypeDef *) 0x50000400U)  

void delay(uint32_t delay_cnt);
void GPIO_Init(GPIO_TypeDef* port, unsigned short pin, GPIO_TypeDef* initVal);
void GPIO_Write_Pin(GPIO_TypeDef* port, unsigned short pin, GPIO_PinState state);
void GPIO_Toggle_Pin(GPIO_TypeDef* port, unsigned short pin);

void delay(uint32_t delay_cnt)
{
		volatile int counter = 0;

		while(counter < delay_cnt) //delay loop
		{
			counter++;
		}
}

void GPIO_Init(GPIO_TypeDef* port, unsigned short pin, GPIO_TypeDef* initVal) {
		port->MODER &= ~(GPIO_2BIT_POS_MASK << (pin * 2U));
		port->MODER |= (0x01 << (pin * 2U));

		port->OTYPER &= ~(GPIO_1BIT_POS_MASK << pin);
		
		port->OSPEEDR &= ~(GPIO_2BIT_POS_MASK << (pin * 2U));
		port->OSPEEDR |= (0x03U << (pin * 2U));

		port->PUPDR &= ~(GPIO_2BIT_POS_MASK << (pin * 2U));
}

void GPIO_Write_Pin(GPIO_TypeDef* port, unsigned short pin, GPIO_PinState state) {
    if (state == GPIO_HIGH) {
        port->ODR |= (1U << pin);
    } else {
        port->ODR &= ~(1U << pin);
    }
}

void GPIO_Toggle_Pin(GPIO_TypeDef* port, unsigned short pin) {
		// port->BSRR = port->ODR ^= (1 << pin);
		// port->BSRR = port->ODR ^= (1 << (pin + 16));
	
	
		// port->BSRR = (port->ODR & (1 << pin)) ? (1 << (pin + 16)) : (1 << pin);
	
		if (port->ODR & (1 << pin)) { 
        port->BRR = (1 << (pin));
    } else {
        port->BSRR = (1 << pin);
    }
}

int main() 
{
    uint32_t position8 = GPIO_PIN_8_POS;
		uint32_t position4 = GPIO_PIN_4_POS;

    RCC_GPIOA |= (1 << 0);  
		RCC_GPIOB |= (1 << 1);  

    GPIO_Init(GPIOA, position8, GPIOA);
		GPIO_Init(GPIOB, position4, GPIOB);
	
		GPIO_Write_Pin(GPIOA, position8, GPIO_HIGH);
		GPIO_Write_Pin(GPIOB, position4, GPIO_LOW);

    while (1) {
			GPIO_Toggle_Pin(GPIOA, position8);
			GPIO_Write_Pin(GPIOB, position4, (GPIOA->ODR & (1 << position8)) ? GPIO_LOW : GPIO_HIGH);
			delay(0x20000);
    }
}