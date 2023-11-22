/*
 * test5.c
 *
 * Created: 01.11.2023 12:54:11
 * Author : stnik
 */ 

#include <avr/io.h>

#define F_CPU 11059200UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define RS 7 // ����� ��������
#define E 6 // ����� ��������
void LCD_cmd(uint8_t cmd) {
	//[]--------------------------------------------------[]
	//| ����������: ������ ����� � ������� ������ ��� |
	//| ������� ���������: cmd - ��� ������� |
	//[]--------------------------------------------------[]
	DDRC = 0xFF; // ��� ������� PORTC �� �����
	DDRD |= ((1<<E)|(1<<RS));// ������� PORTD �� �����
	PORTD &= ~(1<<RS); // ����� �������� ������ RS=0
	PORTC = cmd; // �������� ������� � ���� PORTC
	PORTD |= (1<<E); // \ ������������ ��
	_delay_us(5); // | ������ E ����� 1-0
	PORTD &= ~(1<<E);// / �������� �������
	_delay_ms(100); // �������� ��� ���������� ������
}

void LCD_init(void) {
	//[]--------------------------------------------------[]
	//| ����������: ������������� ��� |
	//[]--------------------------------------------------[]
	DDRC = 0xFF; // ��� ������� PORTC �� �����
	DDRD |= ((1<<E)|(1<<RS)); // ������� PORTD �� �����
	_delay_ms (100); // �������� ��� ������������ ���������� �������
	LCD_cmd(0x30); // \ �����
	LCD_cmd(0x30); // | ����
	LCD_cmd(0x30); // / ������ 0x30
	LCD_cmd(0x38); // 8 ����.����, 2 ������, 5 ? 7 �����
	LCD_cmd(0x0E); // �������� ��� � ������, ��� ��������
	LCD_cmd(0x06); // ��������� �������, ��� ������ ������
	LCD_cmd(0x01); // �������� �����, ������ � ������
}

uint8_t TabCon[] ={0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
	0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,0x50,0x43,0x54,0xA9,
	0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,
	0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,
	0xBC,0xBD,0x6F,0xBE,0x70,0x63,0xBF,0x79,0x5C,0x78,0xE5,0xC0,
0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7};

uint8_t Code(uint8_t symb) {
	//[]------------------------------------------------[]
	//| ����������: ������������� �������� ��������� |
	//| ������� ���������: symb � ������ ASCII |
	//| ������� ���������� ��� ����������� ������� |
	//[]------------------------------------------------[]
	uint8_t a= symb >= 192 ? TabCon[symb-192]: symb;
	return a;
}


void LCD_data(char data)
{
	DDRC = 0xFF; // ��� ������� PORTC �� �����
	DDRD |= ((1<<E)|(1<<RS));// ������� PORTD �� �����
	PORTD |= (1<<RS); // ����� �������� data RS=1
	PORTC = data; // �������� ������� � ���� PORTC
	PORTD |= (1<<E); // \ ������������ ��
	_delay_us(5); // | ������ E ����� 1-0
	PORTD &= ~(1<<E);// / �������� �������
	_delay_ms(1); // �������� ��� ���������� ������
}

void my_f(int16_t a){
	uint8_t flag = 0;
	int16_t b;
	int16_t del = 10000;
				//12345			
	char s;
	char c[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	if (a<0){
		LCD_data('-');
	}
	while (del >= 1){  //k = ����� ����� �����
		b = a/del;
		if (b > 0 & flag ==0){
			flag = 1;
		}
		if (flag == 1){
			s = c[b];
			LCD_data(s); // �������� ������

		}
		a -= b*del;
		del /=10;
		
	}
}

int main(void)
{
    /* Replace with your application code */
	LCD_init();
	
	uint8_t i;
	uint8_t k = 0;
	int8_t u[] = {12, -6, -24, -42, 60};
	char str[] {'Y', '(', 'k', ')', ' ', '=', ' ', 'X'}
	
    while (1) 
    {	
		LCD_cmd((1<<7) |64);
		//my_f(1234);
		for (i = 0; i++; i<8){
		LCD_data(str[i]);}
		
		
		_delay_ms(3000);
		LCD_cmd(1);
		k = (k + 1)%6;
		//for (i = 0; i<5;i++){ 
		//	LCD_cmd((1<<7) |64);
		//	
		//	}
		
    }
}