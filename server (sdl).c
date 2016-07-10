#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <SDL/SDL.h>
#include "uinput.h"

#define JOY_UP 		(1<<4)
#define JOY_DOWN 	(1<<5)
#define JOY_LEFT 	(1<<6)
#define JOY_RIGHT	(1<<7)
#define JOY_BUTTON0	(1<<8)
#define JOY_BUTTON1 	(1<<9)
#define JOY_BUTTON2 	(1<<10)
#define JOY_BUTTON3 	(1<<11)
#define JOY_BUTTON4 	(1<<12)
#define JOY_BUTTON5	(1<<13)
#define JOY_BUTTON6 	(1<<14)
#define JOY_BUTTON7 	(1<<15)
#define JOY_BUTTON8 	(1<<16)
#define JOY_BUTTON9  	(1<<17)
#define JOY_BUTTON10	(1<<18)

typedef struct
{

	int devid; //device identifier
	float xaxis;
	float yaxis;
	int buttons;

}sdl_packet;

 
int main(int argc, char **argv)
{

	int quit;
	float xaxis,yaxis;
	int id,buttons;
	char *buffer;
	char *temp;
	sdl_packet *packet;
 
	initUinput();

	SDL_Joystick *joystick;
	SDL_Event eventjoy;
	SDL_JoystickEventState(SDL_ENABLE);
	packet=(sdl_packet *)malloc(sizeof(sdl_packet));

	if((SDL_Init( SDL_INIT_VIDEO|SDL_INIT_JOYSTICK )) < 0 )
	{
		printf("No se puede inicializar el joystick\n");
		return 0;
	}

//	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	printf("hay %d joysticks\n", SDL_NumJoysticks());
	joystick = SDL_JoystickOpen(0);
//	joystick = SDL_JoystickOpen(1);

	printf("joystick %d ejes\n", SDL_JoystickNumAxes(joystick));

	/* Main loop */
	quit = 0;

	buffer=(char *)malloc(sizeof(char)*16);
//	temp=(char *)malloc(sizeof(char)*4);

	while (!quit)
	{
	
		while(SDL_PollEvent(&eventjoy))
		{

			switch(eventjoy.type)
			{

			case SDL_JOYAXISMOTION:
//printf("eje\n");
			    if( eventjoy.jaxis.axis == 5){
printf("eje\n");
					if(eventjoy.jaxis.value < -3200){
						packet->buttons&=~JOY_RIGHT;printf("eje\n");
						packet->buttons|=JOY_LEFT;
						packet->xaxis=eventjoy.jaxis.value;
					}else if(eventjoy.jaxis.value > 3200){
						packet->buttons&=~JOY_LEFT;
						packet->buttons|=JOY_RIGHT;
						packet->xaxis=eventjoy.jaxis.value;
					}else{
						packet->buttons&=~JOY_LEFT;
						packet->buttons&=~JOY_RIGHT;
						packet->xaxis=0;
					}
				}
				if( eventjoy.jaxis.axis == 6){
					if(eventjoy.jaxis.value < -3200){
						packet->buttons&=~JOY_DOWN;
						packet->buttons|=JOY_UP;
						packet->yaxis=eventjoy.jaxis.value;
					}else if(eventjoy.jaxis.value > 3200){
						packet->buttons&=~JOY_UP;
						packet->buttons|=JOY_DOWN;
						packet->yaxis=eventjoy.jaxis.value;
					}else{
						packet->buttons&=~JOY_UP;
						packet->buttons&=~JOY_DOWN;
						packet->yaxis=0;
					}
				}
			break;

			case SDL_JOYBUTTONDOWN:
				if(eventjoy.jbutton.button==0)
				{
					packet->buttons|=JOY_BUTTON0;
				}
				else if(eventjoy.jbutton.button==1)
				{
					packet->buttons|=JOY_BUTTON1;
				}
				else if(eventjoy.jbutton.button==2)
				{
					packet->buttons|=JOY_BUTTON2;					
				}
				else if(eventjoy.jbutton.button==3)
				{
					packet->buttons|=JOY_BUTTON3;					
				}
				else if(eventjoy.jbutton.button==4)
				{
					packet->buttons|=JOY_BUTTON4;					
				}
				else if(eventjoy.jbutton.button==5)
				{
					packet->buttons|=JOY_BUTTON5;					
				}
				else if(eventjoy.jbutton.button==6)
				{
					packet->buttons|=JOY_BUTTON6;					
				}
				else if(eventjoy.jbutton.button==7)
				{
					packet->buttons|=JOY_BUTTON7;					
				}
				else if(eventjoy.jbutton.button==8)
				{
					packet->buttons|=JOY_BUTTON8;					
				}
				else if(eventjoy.jbutton.button==9)
				{
					packet->buttons|=JOY_BUTTON9;					
				}
				else if(eventjoy.jbutton.button==10)
				{
					packet->buttons|=JOY_BUTTON10;					
				}
			break;
			case SDL_JOYBUTTONUP:
				if(eventjoy.jbutton.button==0)
				{
					packet->buttons&=~JOY_BUTTON0;					
				}
				else if(eventjoy.jbutton.button==1)
				{
					packet->buttons&=~JOY_BUTTON1;										
				}
				else if(eventjoy.jbutton.button==2)
				{
					packet->buttons&=~JOY_BUTTON2;										
				}
				else if(eventjoy.jbutton.button==3)
				{
					packet->buttons&=~JOY_BUTTON3;										
				}
				else if(eventjoy.jbutton.button==4)
				{
					packet->buttons&=~JOY_BUTTON4;										
				}
				else if(eventjoy.jbutton.button==5)
				{
					packet->buttons&=~JOY_BUTTON5;										
				}
				else if(eventjoy.jbutton.button==6)
				{
					packet->buttons&=~JOY_BUTTON6;										
				}
				else if(eventjoy.jbutton.button==7)
				{
					packet->buttons&=~JOY_BUTTON7;										
				}
				else if(eventjoy.jbutton.button==8)
				{
					packet->buttons&=~JOY_BUTTON8;										
				}
				else if(eventjoy.jbutton.button==9)
				{
					packet->buttons&=~JOY_BUTTON9;										
				}
				else if(eventjoy.jbutton.button==10)
				{
					packet->buttons&=~JOY_BUTTON10;										
				}
			break;
			case SDL_QUIT:
				quit=1;break;
			}
			
			setValues(packet->xaxis,packet->yaxis,packet->buttons);

		}
		 usleep(17);
	
	}
 
	/* Clean and exit */

	closeUinput();
	return EXIT_SUCCESS;
}
