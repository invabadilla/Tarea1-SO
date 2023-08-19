/*
 * Necessary imports for the usage of platform designer variables
 */
#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

/*
 * Definition of variables for the control of the Stopwatch
 */
static unsigned ms_cent = 0;
static unsigned ms_tens = 0;
static unsigned ms_unit = 0;

static unsigned s_tens = 0;
static unsigned s_unit = 0;

static unsigned min_tens = 0;
static unsigned min_unit = 0;

static unsigned ms_segm = 0;
static unsigned s_segm = 0;
static unsigned min_segm = 0;

static unsigned play = 0;
static unsigned start = 0;

static unsigned mode = 0;

/*
 * Definition of functions for the control and initialization of the Stopwatch
 */
 static void initTimer_0();
 static void timer_isr(void *context);
 static unsigned decimalToSegm(unsigned decimal);

 static void initButton_0();
 static void button_0_isr();

 static void initButton_1();
 static void button_1_isr();
 static void startStopwatch(unsigned mode_n);

 /*
 * Main funciton
 */
int main()
{
	initTimer_0();
	initButton_0();
	initButton_1();


	while (1);

	return 0;
}
/*
 * Function that initializes the timer_0 component and its interruption
 */
static void initTimer_0(){
	//Association of the IRQ with the ISR function
	alt_ic_isr_register(
		TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
		TIMER_0_IRQ,
		timer_isr,
		NULL,
		NULL);

	//IRQ Enable for periodic interruptions
	IOWR_ALTERA_AVALON_TIMER_CONTROL(
		TIMER_0_BASE,
		ALTERA_AVALON_TIMER_CONTROL_ITO_MSK
		| ALTERA_AVALON_TIMER_CONTROL_CONT_MSK);
}
/*
 * ISR function that executes each time an interruption is made by timer_0
 */

static void timer_isr(void *context){
	(void) context;

	// Verifies if it is in play mode
	if (play == 1){
		ms_unit += 1;
	}
	// Verifies the ms
	if (ms_unit >= 10){
		ms_unit = 0;
		ms_tens +=1;
		if (ms_tens >= 10){
			ms_tens = 0;
			ms_cent += 1;
			if (ms_cent >= 10){
				ms_cent = 0;
				s_unit +=1;
			}
		}
	}
	// Verifies the s
	if (s_unit >= 10){
		s_unit = 0;
		s_tens +=1;
		if (s_tens >= 6){
			s_tens = 0;
			min_unit +=1;
		}
	}
	// Verifies the min
	if (min_unit >= 10){
		min_unit = 0;
		min_tens +=1;
		if (min_tens >= 10){
			min_tens = 0;
		}
	}
	// Assigns binary numbers depending on their decimal form and the mode that is enable for
	// each segment of the stopwatch
	if (mode == 0 || mode == 2){
		ms_segm = (decimalToSegm(ms_cent) << 7) | decimalToSegm(ms_tens);
	}else{
		ms_segm = (decimalToSegm(0) << 7) | decimalToSegm(0);
	}

	if (mode == 1 || mode == 2){
		s_segm = (decimalToSegm(s_tens) << 7) | decimalToSegm(s_unit);
	}else{
		s_segm = (decimalToSegm(0) << 7) | decimalToSegm(0);
	}

	if (mode == 2){
		min_segm = (decimalToSegm(min_tens) << 7) | decimalToSegm(min_unit);
	}else{
		min_segm = (decimalToSegm(0) << 7) | decimalToSegm(0);
	}
	// Writes the value in the indicated 7 segment
	IOWR_ALTERA_AVALON_PIO_DATA(SEGM_MS_0_BASE, ms_segm);
	IOWR_ALTERA_AVALON_PIO_DATA(SEGM_S_0_BASE, s_segm);
	IOWR_ALTERA_AVALON_PIO_DATA(SEGM_MIN_0_BASE, min_segm);

	//Clean the timer status
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}
/*
 * Assigns binary for the 7 segments numbers depending on their decimal form
 * decimal: decimal number that wants to be transformed
 * return: returns the binary form for its correct display in the 7 segment led
 */
static unsigned decimalToSegm(unsigned decimal){
	if (decimal == 0){return 0b1000000;}
	else if (decimal == 1){return 0b1111001;}
	else if (decimal == 2){return 0b0100100;}
	else if (decimal == 3){return 0b0110000;}
	else if (decimal == 4){return 0b0011001;}
	else if (decimal == 5){return 0b0010010;}
	else if (decimal == 6){return 0b0000010;}
	else if (decimal == 7){return 0b1111000;}
	else if (decimal == 8){return 0b0000000;}
	else if (decimal == 9){return 0b0010000;}
	else{return 0;}
}

/*
 * Function that initializes the button_0 component and its interruption
 */
static void initButton_0(){
	// Enabling interrupts and cleaning the edge
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_0_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_0_BASE, 0x0);
	//Association of the IRQ with the ISR function
	alt_ic_isr_register(
		BUTTON_0_IRQ_INTERRUPT_CONTROLLER_ID,
		BUTTON_0_IRQ,
		button_0_isr,
		NULL,
		NULL);
}

static void button_0_isr(void *context){
	(void) context;
	//Changing from play and pause if the stopwatch has started
	if (start == 1){
		play = !play;
	}
	//Cleaning the edge and preventing spurious interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_0_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_0_BASE);
}

/*
 * Function that initializes the button_1 component and its interruption
 */
static void initButton_1(){
	// Enabling interrupts and cleaning the edge
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_1_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_1_BASE, 0x0);
	//Association of the IRQ with the ISR function
	alt_ic_isr_register(
		BUTTON_1_IRQ_INTERRUPT_CONTROLLER_ID,
		BUTTON_1_IRQ,
		button_1_isr,
		NULL,
		NULL);
}

static void button_1_isr(void *context){
	(void) context;
	//Starting the stopwatch and assigning the mode based on the combination of the switches
	if (start == 0){
		if (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_0_BASE) == 0){
			startStopwatch(0);
		}
		else if (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_0_BASE) == 1){
			startStopwatch(1);
		}
		else {
			startStopwatch(2);
		}
	}
	//Cleaning the edge and preventing spurious interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_1_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_1_BASE);
}
/*
 * Aux function for the start button of the stopwatch
 */
static void startStopwatch(unsigned mode_n){
	mode = mode_n;
	start = 1;
	play = 1;
}
