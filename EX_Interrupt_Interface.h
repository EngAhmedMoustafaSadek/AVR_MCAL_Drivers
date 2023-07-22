

#ifndef EX_INTERRUPT_INTERFACE_H_
#define EX_INTERRUPT_INTERFACE_H_

typedef enum {
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}EX_Interrupt_Source_type;

typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}EX_Interrupt_TriggerEdge_type;

void EX_Interrupt_Init(void);

void EX_Interrupt_Enable(EX_Interrupt_Source_type interrupt);

void EX_Interrupt_Disable(EX_Interrupt_Source_type interrupt);

void EX_Interrupt_TriggerEdge(EX_Interrupt_Source_type interrupt,EX_Interrupt_TriggerEdge_type trigger);


void EX_Interrupt_SetCallBack(EX_Interrupt_Source_type interrupt,void (*LocalPtr)(void));



#endif /* EX_INTERRUPT_INTERFACE_H_ */