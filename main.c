#include <msp430.h> 

int main ( void )
{
    WDTCTL = WDTPW | WDTHOLD;	            // Stop watchdog timer

    // Set DCO to 1MHz
    DCOCTL = 0;                             // Clear DCOCTL
    BCSCTL1 = CALBC1_1MHZ;                  // Set basic clock control register to 1MHz
    DCOCTL = CALDCO_1MHZ;                   // Set digital clock to 1MHz

    // Enable timer A
    TACCTL0 = CCIE;                         // Enable interrupts on TimerA
    TACTL = TASSEL_2 + MC_1 + ID_3;         // Use the sub main clock, enable up mode, and divide by 8
    TACCR0 = 30000;                         // 4.2 Hz (1000000/8)/30000

    P1DIR |= BIT0 | BIT6;                   // Enable output on P0.0, P0.6
    P1OUT |= BIT6;                          // Turn on P0.6

    _BIS_SR(CPUOFF + GIE);                  // Turn off cpu and turn on interrupts

    for ( ;; )
    {
        volatile unsigned int i;            // Don't optimize loop
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   P1OUT ^= BIT0 | BIT6;                    // Flip the lights
}
