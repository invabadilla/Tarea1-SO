#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

static unsigned ms_tens = 0;
static unsigned ms_unit = 0;
static unsigned ms_cent = 0;


static unsigned s_tens = 0;
static unsigned s_unit = 0;
static unsigned min_tens = 0;
static unsigned min_unit = 0;

static unsigned ms_segm = 0;
static unsigned s_segm = 0;
static unsigned min_segm = 0;

static unsigned play = 0;

static unsigned mode = 0;

/*static unsigned segments[10] = {
    0b1000000, // 0
    0b1111001, // 1
    0b0100100, // 2
    0b0110000, // 3
    0b0011001, // 4
    0b0010010, // 5
    0b0000010, // 6
    0b1111000, // 7
    0b0000000, // 8
    0b0010000  // 9
};

static unsigned decimalToSegm(unsigned decimal){
	if (decimal >= 0 && decimal <= 99){
		unsigned i_t = decimal / 10;
		unsigned tens = segments[i_t];
		unsigned unit = segments[5];

		unsigned segm = (tens << 7) | unit;

		return segm;

	}

	return 0;
}*/

static unsigned decimalToSegm(unsigned decimal){
	if (decimal == 0){
		return 0b1000000;
	}
	else if (decimal == 1){
		return 0b1111001;
	}
	else if (decimal == 2){
		return 0b0100100;
	}
	else if (decimal == 3){
		return 0b0110000;
	}
	else if (decimal == 4){
		return 0b0011001;
	}
	else if (decimal == 5){
		return 0b0010010;
	}
	else if (decimal == 6){
		return 0b0000010;
	}
	else if (decimal == 7){
		return 0b1111000;
	}
	else if (decimal == 8){
		return 0b0000000;
	}
	else if (decimal == 9){
		return 0b0010000;
	}
	else{
		return 0;
	}


}


static void timer_isr(void *context){
	//No usamos esto
	(void) context;
	if (play == 1){
		ms_unit += 1;
	}

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

	if (s_unit >= 10){
		s_unit = 0;
		s_tens +=1;
		if (s_tens >= 6){
			s_tens = 0;
			min_unit +=1;
		}
	}

	if (min_unit >= 10){
		min_unit = 0;
		min_tens +=1;
		if (min_tens >= 10){
			min_tens = 0;
		}
	}
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

	IOWR_ALTERA_AVALON_PIO_DATA(SEGM_MS_0_BASE, ms_segm);
	IOWR_ALTERA_AVALON_PIO_DATA(SEGM_S_0_BASE, s_segm);
	IOWR_ALTERA_AVALON_PIO_DATA(SEGM_MIN_0_BASE, min_segm);

	//Limpiamos statis.TO
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}

static void button_isr(void *context){
	//No usamos esto
	(void) context;
	play = !play;

	if (play == 1){
		if (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_0_BASE) == 0){
			mode = 0;
		}
		else if (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_0_BASE) == 1){
			mode = 1;
		}
		else {
			mode = 2;
		}
	}

	//Limpiamos statis.TO
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_0_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_0_BASE);
}


int main()
{ 
	//Asociamos la señal de IRQ con el ISR
	alt_ic_isr_register(
		TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
		TIMER_0_IRQ,
		timer_isr,
		NULL,
		NULL);

	//Habilitamos IRQs periódicas generadas por el timer
	IOWR_ALTERA_AVALON_TIMER_CONTROL(
		TIMER_0_BASE,
		ALTERA_AVALON_TIMER_CONTROL_ITO_MSK
		| ALTERA_AVALON_TIMER_CONTROL_CONT_MSK);

	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_0_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_0_BASE, 0x0);

	alt_ic_isr_register(
		BUTTON_0_IRQ_INTERRUPT_CONTROLLER_ID,
		BUTTON_0_IRQ,
		button_isr,
		NULL,
		NULL);

	while (1);
}
