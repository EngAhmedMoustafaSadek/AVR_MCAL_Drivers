
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"

static u8 ADC_BusyFlag;

static void (*ADC_Fptr) (void)= NULLPTR;

void ADC_Init (ADC_VoltRef_type vref, ADC_Prescaler_type scaler)
{
	/* vref */
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/* prescaler */
	
	ADCSRA &=0XF8;
	scaler &=0X07;
	
	ADCSRA = ADCSRA|scaler;
	
	/* enable ADC*/
	SET_BIT(ADCSRA,ADEN);
	
	/* enable ADC interrupt*/
	SET_BIT(ADCSRA,ADIE);

}

u16 ADC_Read(ADC_Channel_type CH)
{
	/* set channel mux*/
	ADMUX&=0XE0;//11100000
	ADMUX|=CH;
	
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/* w8 ADC finish busy wait( blocking )**/
	while(Read_BIT(ADCSRA,ADSC));
	
	/*get read*/
	//u16 adc=ADCL;
	//adc=adc|(ADCH<<8);
	/* IF adle==1*/
	//u16 adc=ADCL>>6;
	//adc=adc|ADCH<<2;
	
	return ADC;
}

void ADC_StartConversion(ADC_Channel_type CH)
{
	if (ADC_BusyFlag==0)
	{
		/* set channel mux*/
		ADMUX&=0XE0;//11100000
		ADMUX|=CH;
		
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_BusyFlag=1;
	}
	
}

u16 ADC_GetRead(void)
{
	
	/*get read*/
	//u16 adc=ADCL;
	//adc=adc|(ADCH<<8);
	/* IF adle==1*/
	//u16 adc=ADCL>>6;
	//adc=adc|ADCH<<2;
	/* w8 ADC finish busy wait( blocking )**/
	while(Read_BIT(ADCSRA,ADSC));
	return ADC;
}

u8 ADC_GetReadPerodic(u16*pdata)
{
	/* perodic ckeck  (polling)*/
	
	if (!Read_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		ADC_BusyFlag=0;
		return 1;
	}
	return 0;
	
}

u16 ADC_GetReadNoblock(void)
{
	return ADC;
}


u16 ADC_VoltRead(ADC_Channel_type CH)
{
	u16 volt;
	u16 adc;
	adc=ADC_Read(CH);
	
	volt=(adc*(u32)5000)/1024;
	return volt;
	
}

void ADC_StartConversion_INT(ADC_Channel_type CH)
{
	if (ADC_BusyFlag==0)
	{
		/* set channel mux*/
		ADMUX&=0XE0;//11100000
		ADMUX|=CH;
		
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_BusyFlag=1;
	}
}
u16 ADC_Read_INT(void)
{
	u16 adc;
	adc=ADC_GetReadNoblock();
	return adc;
	
}
ADC_Channel_type ADC_GetChannel(void)
{
	ADC_Channel_type channel = ADMUX & 0x1F;
	return channel;
}
void ADC_SetInterruptCallBack(void (*LocalPtr)(void))
{
	ADC_Fptr=LocalPtr;
}

ISR (ADC_vect)
{
	ADC_BusyFlag=0;
	if (ADC_Fptr!=NULLPTR)
	{
		ADC_Fptr();
	}
}