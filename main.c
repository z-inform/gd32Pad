typedef __UINT32_TYPE__ uint32_t;
#define CLOCK_BASE 0x40021000
#define GPIOC_BASE 0x40011000


int main(void){
    //init system clock BASE = 0x4002 1000
    //HXTAL; CK_HTAL = 00; AHBpresc = 1; APBpresc = 1;

    //init clocking for GPIO_C 
    //APB2 
    *((uint32_t*) CLOCK_BASE + 0x18) |= 1 << 4;
    //PC10 output   CTL = 00; MD = 10; 
    *((uint32_t*) GPIOC_BASE + 0x04) |= 2 << 8;
    *((uint32_t*) GPIOC_BASE + 0x0C) |= 1 << 10;
    while(1){};
}

int Default_Handler(void){
    //init system clock BASE = 0x4002 1000
    //HXTAL; CK_HTAL = 00; AHBpresc = 1; APBpresc = 1;

    //init clocking for GPIO_C 
    //APB2 
    //PC10 output   CTL = 00; MD = 10; 
    *((uint32_t*) GPIOC_BASE + 0x04) |= 2 << 8;
    *((uint32_t*) GPIOC_BASE + 0x0C) |= 1 << 10;
    while(1){};
}

