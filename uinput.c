#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>

#define JOY_UP 		(1<<4)
#define JOY_DOWN 	(1<<5)
#define JOY_LEFT 	(1<<6)
#define JOY_RIGHT	(1<<7)
#define JOY_BUTTON0	(1<<8)
#define JOY_BUTTON1 	(1<<9)
#define JOY_BUTTON2 	(1<<10)
#define JOY_BUTTON3 	(1<<11)
#define JOY_BUTTON4 	(1<<12)
#define JOY_BUTTON5	    (1<<13)
#define JOY_BUTTON6 	(1<<14)
#define JOY_BUTTON7 	(1<<15)
#define JOY_BUTTON8 	(1<<16)
#define JOY_BUTTON9  	(1<<17)
#define JOY_BUTTON10	(1<<18)
#define JOY_BUTTON11	(1<<19)

int fd[2];

int buttonmap[2][15];

void initButtonMap(){

buttonmap[0][0]=KEY_UP;//up
buttonmap[0][1]=KEY_DOWN;//down
buttonmap[0][2]=KEY_LEFT;//left
buttonmap[0][3]=KEY_RIGHT;//right
buttonmap[0][4]=KEY_LEFTCTRL;//button1
buttonmap[0][5]=KEY_LEFTALT;//button2
buttonmap[0][6]=KEY_SPACE;//button3
buttonmap[0][7]=KEY_LEFTSHIFT;//button4
buttonmap[0][8]=KEY_Z;//button5
buttonmap[0][9]=KEY_X;//button6
buttonmap[0][10]=KEY_C;//button7
buttonmap[0][11]=KEY_1;//start
buttonmap[0][12]=KEY_5;//select
buttonmap[0][13]=KEY_V;//button10
buttonmap[0][14]=KEY_B;//button11

buttonmap[1][0]=KEY_R;//up
buttonmap[1][1]=KEY_F;//down
buttonmap[1][2]=KEY_D;//left
buttonmap[1][3]=KEY_G;//right
buttonmap[1][4]=KEY_A;//button1
buttonmap[1][5]=KEY_S;//button2
buttonmap[1][6]=KEY_Q;//button3
buttonmap[1][7]=KEY_W;//button4
buttonmap[1][8]=KEY_E;//button5
buttonmap[1][9]=KEY_D;//button6
buttonmap[1][10]=KEY_O;//button7
buttonmap[1][11]=KEY_L;//start
buttonmap[1][12]=KEY_P;//select
buttonmap[1][13]=KEY_6;//button10
buttonmap[1][14]=KEY_2;//button11

}


void initUinput()
{


	struct uinput_user_dev uidev[2];

	initButtonMap();

	/*Open device*/
	fd[0] = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if(fd[0] < 0) {

//		exit(EXIT_FAILURE);
		printf("cannot open device\n");
	}

	fd[1] = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if(fd[1] < 0) {

//		exit(EXIT_FAILURE);
		printf("cannot open device\n");
	}

	int i;

	for(i=0;i<2;i++){
		/*Set axis and buttons*/
		if(ioctl(fd[i], UI_SET_EVBIT, EV_KEY) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_EVBIT, EV_ABS) < 0)
			printf("error\n");
	//        die("error: ioctl");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][0]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][1]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][2]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][3]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][4]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][5]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][6]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][7]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][8]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][9]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][10]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][11]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][12]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][13]) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_KEYBIT, buttonmap[i][14]) < 0)
			printf("error\n");

		if(ioctl(fd[i], UI_SET_ABSBIT, ABS_X) < 0)
			printf("error\n");
		if(ioctl(fd[i], UI_SET_ABSBIT, ABS_Y) < 0)
			printf("error\n");
	

	/*Create uinput struct*/
	memset(&uidev[i], 0, sizeof(uinput_user_dev));

	snprintf(uidev[i].name, UINPUT_MAX_NAME_SIZE, "uinput-joymapper");
	uidev[i].id.bustype = BUS_USB;
	uidev[i].id.vendor  = 0x1234;
	uidev[i].id.product = 0xfedc;
	uidev[i].id.version = i;

	/*set axis range*/
	uidev[i].absmin[ABS_X] = -10;
	uidev[i].absmax[ABS_X] =  10;
	uidev[i].absmin[ABS_Y] = -10;
	uidev[i].absmax[ABS_Y] =  10;


	/*create uinput device*/
    if(write(fd[i], &uidev[i], sizeof(uinput_user_dev)) < 0)
        printf("error: write");

    if(ioctl(fd[i], UI_DEV_CREATE) < 0)
        printf("error: ioctl");
	
	}
}


void setValues(int idev, float xaxis, float yaxis, int buttons)
{

    struct input_event ev;

			//axis as axis :)
            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_ABS;
            ev.code = ABS_X;
            ev.value = xaxis;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error1\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_ABS;
            ev.code = ABS_Y;
            ev.value = yaxis;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

			
			//axis as buttons
			memset(&ev, 0, sizeof(struct input_event));
	        ev.type = EV_KEY;
	        ev.code = buttonmap[idev][0];
			if(yaxis < -32766)
			    ev.value = 1;
			else
			    ev.value = 0;
		    if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

			memset(&ev, 0, sizeof(struct input_event));
	        ev.type = EV_KEY;
	        ev.code = buttonmap[idev][1];
			if(yaxis > 32766)
			    ev.value = 1;
			else
			    ev.value = 0;
		    if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

			memset(&ev, 0, sizeof(struct input_event));
	        ev.type = EV_KEY;
	        ev.code = buttonmap[idev][2];
			if(xaxis < -32766)
			    ev.value = 1;
			else
			    ev.value = 0;
		    if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

			memset(&ev, 0, sizeof(struct input_event));
	        ev.type = EV_KEY;
	        ev.code = buttonmap[idev][3];
			if(xaxis > 32766)
			    ev.value = 1;
			else
			    ev.value = 0;
		    if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");
			

			//buttons
            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][4];
			if(buttons&JOY_BUTTON0)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][5];
			if(buttons&JOY_BUTTON1)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][6];
			if(buttons&JOY_BUTTON2)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][7];
			if(buttons&JOY_BUTTON3)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][8];
			if(buttons&JOY_BUTTON4)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][9];
			if(buttons&JOY_BUTTON5)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][10];
			if(buttons&JOY_BUTTON6)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][11];
			if(buttons&JOY_BUTTON7)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][12];
			if(buttons&JOY_BUTTON8)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][13];
			if(buttons&JOY_BUTTON9)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");

            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_KEY;
            ev.code = buttonmap[idev][14];
			if(buttons&JOY_BUTTON10)
	            ev.value = 1;
			else
		        ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");


            memset(&ev, 0, sizeof(struct input_event));
            ev.type = EV_SYN;
            ev.code = 0;
            ev.value = 0;
            if(write(fd[idev], &ev, sizeof(struct input_event)) < 0)
				printf("error\n");



}


void closeUinput()
{

	int i;

	for(i=0;i<2;i++){
	/*Close all*/
    if(ioctl(fd[i], UI_DEV_DESTROY) < 0);
 //       die("error: ioctl");
	
    close(fd[i]);
	}


}
