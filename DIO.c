#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "DIO_Cfg.h"



void DIO_Init(void)
{
	DIO_Pin_type i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,DIO_PinsStatusArr[i]);
	}
}

static void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	DIO_Port_type port = pin/8;
	u8 pin_num = pin%8;
	
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		
	}
	
}

Bool_t DIO_WritePin(DIO_Pin_type pin, DIO_PinVoltage_type volt)
{
	DIO_Port_type port = pin/8;
	u8 pin_num = pin%8;
	Bool_t func_Status=TRUE;
	if(DIO_PinsStatusArr[pin]==OUTPUT)
	{
		if(volt==HIGH)
		{
			switch(port)
			{
				case PA:
				SET_BIT(PORTA,pin_num);
				break;
				case PB:
				SET_BIT(PORTB,pin_num);
				break;
				case PC:
				SET_BIT(PORTC,pin_num);
				break;
				case PD:
				SET_BIT(PORTD,pin_num);
				break;
			}
		}
		else if(volt==LOW)
		{
			switch(port)
			{
				case PA:
				CLR_BIT(PORTA,pin_num);
				break;
				case PB:
				CLR_BIT(PORTB,pin_num);
				break;
				case PC:
				CLR_BIT(PORTC,pin_num);
				break;
				case PD:
				CLR_BIT(PORTD,pin_num);
				break;
			}
		}
		else
		{
			func_Status = FALSE;
		}
	}
	else
	{
		func_Status = FALSE;
	}
	return func_Status;
	
}

DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_Port_type port = pin/8;
	u8 pin_num = pin%8;
	DIO_PinVoltage_type volt = LOW;
	switch(port)
	{
		case PA:
		volt=Read_BIT(PINA,pin_num);
		break;
		case PB:
		volt=Read_BIT(PINB,pin_num);
		break;
		case PC:
		volt=Read_BIT(PINC,pin_num);
		break;
		case PD:
		volt=Read_BIT(PIND,pin_num);
		break;
	}
	return volt;
	
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	DIO_Port_type port = pin/8;
	u8 pin_num = pin%8;
	
	switch(port)
	{
		case PA:
		Toggle_BIT(PORTA,pin_num);
		break;
		case PB:
		Toggle_BIT(PORTB,pin_num);
		break;
		case PC:
		Toggle_BIT(PORTC,pin_num);
		break;
		case PD:
		Toggle_BIT(PORTD,pin_num);
		break;
	}
	
}

void DIO_WritePort(DIO_Port_type port,u8 data)
{
	switch(port)
	{
		case PA:
		PORTA=data;
		break;
		case PB:
		PORTB=data;
		break;
		case PC:
		PORTC=data;
		break;
		case PD:
		PORTD=data;
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 data=0;
	switch(port)
	{
		case PA:
		data=PINA;
		break;
		case PB:
		data=PINB;
		break;
		case PC:
		data=PINC;
		break;
		case PD:
		data=PIND;
		break;
	}
	return data;
}