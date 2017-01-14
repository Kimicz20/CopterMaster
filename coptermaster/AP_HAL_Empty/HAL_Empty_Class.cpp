
#include "../AP_HAL/AP_HAL.h"
//#if CONFIG_HAL_BOARD == HAL_BOARD_EMPTY

#include <assert.h>

#include "HAL_Empty_Class.h"
#include "AP_HAL_Empty_Private.h"

using namespace Empty;

//static EmptyUARTDriver uartADriver;
//static EmptyUARTDriver uartBDriver;
//static EmptyUARTDriver uartCDriver;
static EmptySemaphore  i2cSemaphore;
static EmptyI2CDriver  i2cDriver(&i2cSemaphore);
static EmptySPIDeviceManager spiDeviceManager;
static EmptyAnalogIn analogIn;
static EmptyStorage storageDriver;
static EmptyGPIO gpioDriver;
static EmptyRCInput rcinDriver;
static EmptyRCOutput rcoutDriver;
static EmptyScheduler schedulerInstance;
static EmptyUtil utilInstance;


HAL_Empty::HAL_Empty() :
    AP_HAL::HAL(
        //&uartADriver,
        //&uartBDriver,
        //&uartCDriver,
		NULL,
		NULL,
		NULL,
        NULL,            /* no uartD */
        NULL,            /* no uartE */
        &i2cDriver,
        NULL, /* only one i2c */
        NULL, /* only one i2c */
        &spiDeviceManager,
        &analogIn,
        &storageDriver,
        //&uartADriver, 
		NULL,
        &gpioDriver,
        &rcinDriver,
        &rcoutDriver,
        &schedulerInstance,
        &utilInstance),
    _member(new EmptyPrivateMember(123))
{}

void HAL_Empty::run(int argc, char* const argv[], Callbacks* callbacks) const
{
	 
    assert(callbacks);

    /* initialize all drivers and private members here.
     * up to the programmer to do this in the correct order.
     * Scheduler should likely come first. */
    scheduler->init(NULL);  
    //uartA->begin(115200);
    _member->init();

    //callbacks->setup();
	copter.setup();
    scheduler->system_initialized();
	cout << "setup OK" << endl;
	for (;;) { 
		//copter.delay(1000);
		//callbacks->loop();
		cout << "loop" << endl;
		copter.loop();
		cout
			<< (int)copter.channel_roll->control_in << endl
			<< (int)copter.channel_yaw->control_in << endl
			<< (int)copter.channel_pitch->control_in << endl
			<< (int)copter.channel_throttle->control_in << endl;
		cout << PSTR("END")<<endl;
		if (hal.scheduler->millis()>50000) 
			break;
	}
	system("pause");
	return;
}

const AP_HAL::HAL& AP_HAL::get_HAL() {
    static const HAL_Empty hal;
    return hal;
}

//#endif
