
#include <xc.h>
#include <avr/interrupt.h>

extern int data;


void ADC_init(char channel, char ref, char prescaler, char isInterrupt, char isAutoT){
     // ADC Init
    ADMUX = (channel<<0)|(ref<<6);
    ADCSRA = (prescaler << 0) | (isInterrupt << 3)| (isAutoT << 5)| (1<<ADEN);
}
void ADC_startConv(){
    ADCSRA |= (1 << ADSC); // Start Conversion
}
void ADC_readData(int *pData){
    //Reading Data
    *pData = ADCL;
    *pData |= (ADCH << 8);
}
void smpl_ADC_init(char channel, char ref){
       ADMUX = (channel<<0)|(ref<<6);
        ADCSRA = (7 << 0) | (1 << ADIE)| (1<<ADEN);
}
ISR(ADC_vect) {
    // ADC Interrupt

    ADC_readData(&data);
    
    data *= 4.9; // in mV  // 1.5V >> 1500mV

    data /= 10; // in C
    ADC_startConv();
}
// ADLAR changing the sequence of adding data in adcl and adch
// ADEN  bit for enabling adc
// ADATE auto triggering the adc conversion either by external interrupt or timer flags
// ADIF adc  interrupt flag bit turns one after adc finishes adding the data in the registers 
//ADIE adc interrupt enable
// ADPS prescaler frequency of adc