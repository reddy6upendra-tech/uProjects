#include <reg51.h>

#define digit P2

unsigned char sc,mn,hr,t,d=0;

sbit seg1=P1^1;
sbit seg2=P1^2;
sbit seg3=P1^3;
sbit seg4=P1^4;
sbit seg5=P1^5;
sbit seg6=P1^6;
sbit dot=P2^7;

void delay(unsigned int y){
	unsigned int i,j;
	for(i=0;i<y;i++)
		for(j=0;j<300;j++);
}

void hour() interrupt 0
{
	hr++;
	if(hr>=24)
		hr=0;
	delay(200);
}

void min() interrupt 2
{
	mn++;
	if(mn>=60){
		mn=0;
		hr++;
			if(hr>=24)
				hr=0;
	}
	delay(200);
}

void sec() interrupt 3
{
	t++;
	if(t>=20){
		t=0;
		sc++;
		if(sc>=60){
			sc=0;
			mn++;
			if(mn>=60){
				mn=0;
				hr++;
				if(hr>=24)
					hr=0;
			}
		}
	}
	TH1=0x4c;
	TL1=0x00;
}

void display(unsigned char x){
	if(x==0)
		digit=0xc0;
	else if(x==1)
		digit=0xf9;
	else if(x==2)
		digit=0xa4;
	else if(x==3)
		digit=0xb0;
	else if(x==4)
		digit=0x99;
	else if(x==5)
		digit=0x92;
	else if(x==6)
		digit=0x82;
	else if(x==7)
		digit=0xf8;
	else if(x==8)
		digit=0x80;
	else if(x==9)
		digit=0x90;
	d++;
	if(d==2){
		dot=0;
		d=0;
	}
	else
		dot=1;
	delay(1);
}

void main(void){
	seg1=seg2=seg3=seg4=seg5=seg6=dot=0;
	digit=0x00;
	IE=0x8d;
	INT0=1;
	INT1=1;
	TMOD=0x10;
	TH1=0x4c;
	TL1=0x00;
	TR1=1;
	while(1){
		seg6=0;seg1=1;
		display(hr/10);
		seg1=0;seg2=1;
		display(hr%10);
		seg2=0;seg3=1;
		display(mn/10);
		seg3=0;seg4=1;
		display(mn%10);
		seg4=0;seg5=1;
		display(sc/10);
		seg5=0;seg6=1;
		display(sc%10);
	}
}
