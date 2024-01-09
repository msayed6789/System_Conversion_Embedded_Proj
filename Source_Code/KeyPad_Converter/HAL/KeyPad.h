/*
 * KeyPad.h
 *
 * Created: 12/11/2022 8:40:49 PM
 *  Author: M.Sayed
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO_Interface.h"
/*************************config**********************/

#define FIRST_OUTPUt PINB0
#define FIRST_INPUT  PINC0

#define COL   4
#define ROW   4

#define  NO_KEY  'N'

static u8 KeysArray[ROW][COL]={{'7','8','9','A'},
                               {'4','5','6','B'},
						       {'1','2','3','C'},
						       {'c','0','=','D'}};		
							
/*******************************************************/						

u8 KEYPAD_GetKey(void);








#endif /* KEYPAD_H_ */