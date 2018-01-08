#include <IOKit/bluetooth/IOBluetoothHIDDriver.h>

#define REPORT_DESCRIPTOR_OVERRIDE_KEY "ReportDescriptorOverride"

class IOBluetoothHIDDriverDescriptorOverride : public IOBluetoothHIDDriver {

	OSDeclareDefaultStructors(IOBluetoothHIDDriverDescriptorOverride)

public:
    virtual IOReturn newReportDescriptor(IOMemoryDescriptor **descriptor) const;
	bool start( IOService * provider );
	virtual bool didTerminate( IOService * provider, IOOptionBits options, bool * defer );
	virtual bool terminate( IOOptionBits options = 0 );

};
