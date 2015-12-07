#include <rtthread.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif
#include "wirish/wirish.h"

int cmd_pinMode(int argc, char** argv)
{
    int pin;
    int mode;
    if(argc == 3) {
        sscanf(argv[1], "%d", &pin);
        if(strcmp(argv[2], "OUTPUT") == 0) {
            mode = OUTPUT;
        }
        else if(strcmp(argv[2], "OUTPUT_OPEN_DRAIN") == 0) {
            mode = OUTPUT_OPEN_DRAIN;
        }
        else if(strcmp(argv[2], "INPUT") == 0) {
            mode = INPUT;
        }
        else if(strcmp(argv[2], "INPUT_ANALOG") == 0) {
            mode = INPUT_ANALOG;
        }
        else if(strcmp(argv[2], "INPUT_PULLUP") == 0) {
            mode = INPUT_PULLUP;
        }
        else if(strcmp(argv[2], "INPUT_PULLDOWN") == 0) {
            mode = INPUT_PULLDOWN;
        }
        else if(strcmp(argv[2], "INPUT_FLOATING") == 0) {
            mode = INPUT_FLOATING;
        }
        else if(strcmp(argv[2], "PWM") == 0) {
            mode = PWM;
        }
        else if(strcmp(argv[2], "PWM_OPEN_DRAIN") == 0) {
            mode = PWM_OPEN_DRAIN;
        }
        else{
            sscanf(argv[2], "%d", &mode);
        }
        pinMode((uint8)pin, (WiringPinMode)mode);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_pinMode, pinMode, pinMode pinNum mode.);

int cmd_digitalRead(int argc, char** argv)
{
    int ret = 0;
    int pin;
    if(argc == 2) {
        sscanf(argv[1], "%d", &pin);
        ret = digitalRead((uint8)pin);
    }
    rt_kprintf("%d\n", ret);

    return ret;
}
MSH_CMD_EXPORT_ALIAS(cmd_digitalRead, digitalRead, digitalRead pinNum.);

int cmd_digitalWrite(int argc, char** argv)
{
    int pin;
    int val;
    if(argc == 3) {
        sscanf(argv[1], "%d", &pin);
        if(strcmp(argv[2], "HIGH") == 0) {
            val = HIGH;
        }
        else if(strcmp(argv[2], "LOW") == 0) {
            val = LOW;
        }
        else {
            sscanf(argv[2], "%d", &val);
        }
        digitalWrite((uint8)pin, (uint8)val);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_digitalWrite, digitalWrite, digitalWrite pinNum HIGH/LOW.);

int cmd_togglePin(int argc, char** argv)
{
    int pin;
    if(argc == 2) {
        sscanf(argv[1], "%d", &pin);
        togglePin((uint8)pin);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_togglePin, togglePin, togglePin pinNum.);

int cmd_analogRead(int argc, char** argv)
{
    int ret = 0;
    int pin;
	if(argc == 2) {
        sscanf(argv[1], "%d", &pin);
	    ret = analogRead((uint8)pin);
	}
    rt_kprintf("%d\n", ret);

	return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_analogRead, analogRead, analogRead pinNum.);

int cmd_pwmWrite(int argc, char** argv)
{
    int pin;
    int duty_cycle;
    if(argc == 3) {
        sscanf(argv[1], "%d", &pin);
        sscanf(argv[2], "%d", &duty_cycle);
        pwmWrite((uint8)pin, (uint16)duty_cycle);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_pwmWrite, pwmWrite, pwmWrite pinNum duty_cycle.);
