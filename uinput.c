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

static int readbutton(char *string_button);

static int readbutton(char *string_button)
{

	if(strcmp(string_button,"KEY_UP") == 0)return KEY_UP;
	if(strcmp(string_button,"KEY_DOWN") == 0)return KEY_DOWN;
	if(strcmp(string_button,"KEY_LEFT") == 0)return KEY_LEFT;
	if(strcmp(string_button,"KEY_RIGHT") == 0)return KEY_RIGHT;
	if(strcmp(string_button,"KEY_A") == 0)return KEY_A;
	if(strcmp(string_button,"KEY_B") == 0)return KEY_B;
	if(strcmp(string_button,"KEY_C") == 0)return KEY_C;
	if(strcmp(string_button,"KEY_D") == 0)return KEY_D;
	if(strcmp(string_button,"KEY_E") == 0)return KEY_E;
	if(strcmp(string_button,"KEY_F") == 0)return KEY_F;
	if(strcmp(string_button,"KEY_G") == 0)return KEY_G;
	if(strcmp(string_button,"KEY_H") == 0)return KEY_H;
	if(strcmp(string_button,"KEY_I") == 0)return KEY_I;
	if(strcmp(string_button,"KEY_J") == 0)return KEY_J;
	if(strcmp(string_button,"KEY_K") == 0)return KEY_K;
	if(strcmp(string_button,"KEY_L") == 0)return KEY_L;
	if(strcmp(string_button,"KEY_M") == 0)return KEY_M;
	if(strcmp(string_button,"KEY_N") == 0)return KEY_N;
	if(strcmp(string_button,"KEY_O") == 0)return KEY_O;
	if(strcmp(string_button,"KEY_P") == 0)return KEY_P;
	if(strcmp(string_button,"KEY_Q") == 0)return KEY_Q;
	if(strcmp(string_button,"KEY_R") == 0)return KEY_R;
	if(strcmp(string_button,"KEY_S") == 0)return KEY_S;
	if(strcmp(string_button,"KEY_T") == 0)return KEY_T;
	if(strcmp(string_button,"KEY_U") == 0)return KEY_U;
	if(strcmp(string_button,"KEY_V") == 0)return KEY_V;
	if(strcmp(string_button,"KEY_W") == 0)return KEY_W;
	if(strcmp(string_button,"KEY_X") == 0)return KEY_X;
	if(strcmp(string_button,"KEY_Y") == 0)return KEY_Y;
	if(strcmp(string_button,"KEY_Z") == 0)return KEY_Z;
	if(strcmp(string_button,"KEY_0") == 0)return KEY_0;
	if(strcmp(string_button,"KEY_1") == 0)return KEY_1;
	if(strcmp(string_button,"KEY_2") == 0)return KEY_2;
	if(strcmp(string_button,"KEY_3") == 0)return KEY_3;
	if(strcmp(string_button,"KEY_4") == 0)return KEY_4;
	if(strcmp(string_button,"KEY_5") == 0)return KEY_5;
	if(strcmp(string_button,"KEY_6") == 0)return KEY_6;
	if(strcmp(string_button,"KEY_7") == 0)return KEY_7;
	if(strcmp(string_button,"KEY_8") == 0)return KEY_8;
	if(strcmp(string_button,"KEY_9") == 0)return KEY_9;
	if(strcmp(string_button,"KEY_SPACE") == 0)return KEY_SPACE;
	if(strcmp(string_button,"KEY_LEFTCTRL") == 0)return KEY_LEFTCTRL;
	if(strcmp(string_button,"KEY_RIGHTCTRL") == 0)return KEY_RIGHTCTRL;
	if(strcmp(string_button,"KEY_LEFTALT") == 0)return KEY_LEFTALT;
	if(strcmp(string_button,"KEY_RIGHTALT") == 0)return KEY_RIGHTALT;
	if(strcmp(string_button,"KEY_LEFTSHIFT") == 0)return KEY_LEFTSHIFT;
	if(strcmp(string_button,"KEY_RIGHTSHIFT") == 0)return KEY_RIGHTSHIFT;
	if(strcmp(string_button,"KEY_ESC") == 0)return KEY_ESC;
	if(strcmp(string_button,"KEY_F1") == 0)return KEY_F1;
	if(strcmp(string_button,"KEY_F2") == 0)return KEY_F2;
	if(strcmp(string_button,"KEY_F3") == 0)return KEY_F3;
	if(strcmp(string_button,"KEY_F4") == 0)return KEY_F4;
	if(strcmp(string_button,"KEY_F5") == 0)return KEY_F5;
	if(strcmp(string_button,"KEY_F6") == 0)return KEY_F6;
	if(strcmp(string_button,"KEY_F7") == 0)return KEY_F7;
	if(strcmp(string_button,"KEY_F8") == 0)return KEY_F8;
	if(strcmp(string_button,"KEY_F9") == 0)return KEY_F9;
	if(strcmp(string_button,"KEY_F10") == 0)return KEY_F10;
	if(strcmp(string_button,"KEY_F11") == 0)return KEY_F11;
	if(strcmp(string_button,"KEY_F12") == 0)return KEY_F12;
	if(strcmp(string_button,"KEY_ENTER") == 0)return KEY_ENTER;
	if(strcmp(string_button,"KEY_TAB") == 0)return KEY_TAB;
	if(strcmp(string_button,"KEY_BACKSPACE") == 0)return KEY_BACKSPACE;
	if(strcmp(string_button,"KEY_PAGEUP") == 0)return KEY_PAGEUP;
	if(strcmp(string_button,"KEY_PAGEDOWN") == 0)return KEY_PAGEDOWN;
	if(strcmp(string_button,"KEY_INSERT") == 0)return KEY_INSERT;
	if(strcmp(string_button,"KEY_DELETE") == 0)return KEY_DELETE;
	if(strcmp(string_button,"KEY_COMMA") == 0)return KEY_COMMA;
	if(strcmp(string_button,"KEY_DOT") == 0)return KEY_DOT;
	if(strcmp(string_button,"KEY_SLASH") == 0)return KEY_SLASH;

	return KEY_UP;


}

void initButtonMap()
{

	int i = 0;
	int j = 0;
	
	FILE *fconfig;

	fconfig = fopen("config.txt","r");

	char fline[300];//line of the file readed
	
	char njoybutton[20];//joy button to compare

	char nbutton[20];//name of the button readed

	char sbutton[20];//button readed

	int button = 0;//joy button integer

	int chot = 100;

	while(!feof(fconfig))
	{
	
		fscanf(fconfig,"%s %s",nbutton,sbutton);

		printf("%s %d\n",nbutton,strlen(nbutton));
		printf("%s\n",sbutton);

		sprintf(njoybutton,"JOY%d_BUTTON_%d",i,j);

		printf("%s %d\n",njoybutton,strlen(njoybutton));		

		if(strcmp(nbutton,njoybutton)==0)
		{
			button = readbutton(sbutton);
			printf("%d\n",button);
			printf("\n");
		}//if		
				
		buttonmap[i][j] = button;

		memset(nbutton,0,20);
		memset(sbutton,0,20);
		memset(njoybutton,0,20);

		j++;

		if(j > 14)
		{
			j=0;
			i++;
			if(i > 1)break;
		}//if

		memset(fline,0,300);

	}//while
	
		/*buttonmap[0][0]=KEY_UP;//up
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
		buttonmap[1][14]=KEY_2;//button11*/

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
