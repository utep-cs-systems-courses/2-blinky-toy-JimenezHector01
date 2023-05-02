#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

int main() {
  configureClocks();
  
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;

  buzzer_init();

  or_sr(0x18);
}

void switch_interrupt_handler(){
  char p2val = P2IN;
  
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);

  if(p2val & SW1){
    P1OUT &= ~LED_GREEN;
  }else{
    P1OUT |= LED_GREEN;
    market();
  }

  if(p2val & SW2){
    P1OUT &= ~LED_RED;
  }else{
    P1OUT |= LED_RED;
    buzzer_set_period(2000);
  }
    
  
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void market(){
  buzzer_set_period(1000);
}

int secondCount = 0;
int market[] = {1960, 1960, 1960, 1750, 1650, 1750, 0};
int note = 0;
int count = 0;
void __interrupt_vec(WDT_VECTOR) WDT()
{
  secondCount ++;
  if(count < 2){
    if(secondCount == 125){
      buzzer_set_period(market[note]);
      note++;
    }
    if(secondCount == 250){
      buzzer_init();
    }
  }else{
    if(secondCount == 64){
      buzzer_set_period(market[note]);
      note++;
    }
    if(secondCount == 125){
      buzzer_init();
    }
    if(count > 6){
      count = 0;
    }
  }
}
