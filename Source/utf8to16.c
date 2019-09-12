#include <stdio.h>

int main(void){
	int x,z,y,a1,a2,a,b,c,d,flag;			//z=Unicode,x=variable for input,a-b-c-d=temporary variables for byte management
	x=getchar();
	while(x!=EOF){					//Don't stop until the end of the file
		flag=0; 				//Indication if character is encoded in UTF-8
		if (x<=0x7F){				//1-byte-encoded: 0xxxxxxx
			flag=1;
			z=x;
		}
		else if(x>=0xC0 && x<=0xDF){		//2-byte-encoded: 110xxxxx 10xxxxxx	,	where x are unicode bits
			flag=1;				//Always getting bytes form left to right...
			a=x&31;
			a<<=6;
			
			x=getchar();
			b=x&63;
			
			z=a|b;
		}
		else if(x>=0xE0 && x<=0xEF){		//3-byte-encoded: 1110xxxx 10xxxxxx 10xxxxxx
			flag=1;
			a=x&15;
			a<<=12;
				
			x=getchar();
			b=x&63;
			b<<=6;

			x=getchar();
			c=x&63;

			z=a|b|c;	
		}
		else if(x>=0xF0 && x<=0xF7){		//4-byte-encoded: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			flag=1;			
			a=x&7;
			a<<=18;

			x=getchar();
			b=x&0x3F;
			b<<=12;

			x=getchar();
			c=x&63;
			c<<=6;

			x=getchar();
			d=x&63;

			z=a|b|c|d;
		}
		if(!flag){				//Error:false input text file
			printf("\n TEXT NOT IN UTF-8");
			break;
		}
	
	///////////////////////////////////////////Start of UTF-16 encoding///////////////////////////////////////////////////

	

		if((z<=0xD7FF)||(z>=0xE000 && z<=0xFFFF)){//Encoding using 2 bytes,Unicode exists in [0x0000,0xD7FF] and [0xE000,0xFFFF].
			putchar (z >> 8);
			putchar (z & 255);
		}
		else if(z>=0x10000 && z<=0x10FFFF){	//Encoding using 4 bytes,Unicode exists in [0x010000,0x10FFFF].
			z-=0x010000;
			a1=(z>>10)+0xD800;		//a1=high surrogate,exists in [0xD800,0xDBFF].
			a2=(z&1023)+0xDC00;		//a2=low surrogate,exists in [0xDC00,0xDFFF].
			putchar(a1>>8);			//Creating the surrogate pair...
			putchar(a1&255);
			putchar(a2>>8);
			putchar(a2&255);
		}

	x=getchar();					//Moving to next character	
	}

return 0;	
}








		
	
