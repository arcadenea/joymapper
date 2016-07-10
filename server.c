#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
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
#define JOY_BUTTON10	(1<<19)

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

static int joystick_fd[2];

typedef struct
{

	int devid[2]; //device identifier
	float xaxis[2];
	float yaxis[2];
	int buttons[2];

}sdl_packet;

struct js_event {
	        unsigned int time;      /* event timestamp in milliseconds */
	        short value;   /* value */
	        unsigned char type;     /* event type */
	        unsigned char number;   /* axis/button number */
	};

int read_joystick_event(int id, struct js_event *jse)
	{
	        int bytes;
			int i;

	        bytes = read(joystick_fd[id], jse, sizeof(*jse)); 
			
	        if (bytes == -1)
	                return 0;
	
	        if (bytes == sizeof(*jse))
	                return 1;
	
	        printf("Unexpected bytes from joystick:%d\n", bytes);
	
	        return -1;
	} 

void close_joystick()
	{
			int i;

			for(i=0;i<2;i++)
			{
		        close(joystick_fd[i]);
			}
	}

int main(int argc, char **argv)
{

	int quit;
	float xaxis,yaxis;
	int id,buttons;
	char *buffer;
	char *temp;
	sdl_packet *packet;
	int rc;
	struct js_event jse;
 
	initUinput();

	packet=(sdl_packet *)malloc(sizeof(sdl_packet));

	int i;
	const char *devjoy;

//	devjoy = (char*)malloc(14 * sizeof(char));

//	for(i=0;i<2;i++){
//		strcat(devjoy, "/dev/input/js");
//		strcat(devjoy, itoa(i));
		joystick_fd[0] = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
		joystick_fd[1] = open("/dev/input/js1", O_RDONLY | O_NONBLOCK);
//		memset(devjoy, 0, 14);
//	}
	/* Main loop */
	quit = 0;

	buffer=(char *)malloc(sizeof(char)*16);
//	temp=(char *)malloc(sizeof(char)*4);
	
	int idev;

	while (!quit)
	{
		for(idev=0;idev<2;idev++){
			while ((rc = read_joystick_event(idev, &jse) == 1)) {
				jse.type &= ~JS_EVENT_INIT; /* ignore synthetic events */
				if (jse.type == JS_EVENT_AXIS) {
					switch (jse.number) {
					case 6: packet->xaxis[idev] = jse.value;
						break;
					case 7: packet->yaxis[idev] = jse.value;
						break;
					default:
						break;
					}
				} else if (jse.type == JS_EVENT_BUTTON) {
					if (jse.number < 10) {
						switch (jse.number) {
						case 0: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON0;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON0;
								}//jse.value;
						break;
						case 1: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON1;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON1;
								}//jse.value;
							break;
						case 2: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON2;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON2;
								}//jse.value;
						break;
						case 3: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON3;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON3;
								}//jse.value;
							break;
						case 4: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON4;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON4;
								}//jse.value;
						break;
						case 5: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON5;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON5;
								}//jse.value;
							break;
						case 6: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON6;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON6;
								}//jse.value;
						break;
						case 7: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON7;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON7;
								}//jse.value;
							break;
						case 8: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON8;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON8;
								}//jse.value;
						break;
						case 9: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON9;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON9;
								}//jse.value;
							break;
						case 10: if(jse.value)
								{ 
									packet->buttons[idev] |= JOY_BUTTON10;
								}else{
									packet->buttons[idev]&=~JOY_BUTTON10;
								}//jse.value;
						break;
						default:
							break;
						}
					}
				}
			}
			setValues(idev, packet->xaxis[idev],packet->yaxis[idev],packet->buttons[idev]);	
//			packet->buttons=0;
		}

		 usleep(17);
	
	}
 
	/* Clean and exit */

	closeUinput();
	return EXIT_SUCCESS;
}
