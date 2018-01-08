#include <IOKit/IOBufferMemoryDescriptor.h>
#include "IOBluetoothHIDDriverDescriptorOverride.h"

OSDefineMetaClassAndStructors(IOBluetoothHIDDriverDescriptorOverride, IOBluetoothHIDDriver)

IOReturn IOBluetoothHIDDriverDescriptorOverride::newReportDescriptor(IOMemoryDescriptor **desc) const {
    IOLog("IOBluetoothHIDDriverDescriptorOverride::(%s)[%p]newReportDescriptor", getName(), this);

	OSData *reportDescriptor = OSDynamicCast(OSData, getProperty(REPORT_DESCRIPTOR_OVERRIDE_KEY));
	if(reportDescriptor) {
	IOLog("IOBluetoothHIDDriverDescriptorOverride(%s)[%p]::newReportDescriptor - "
			  "Replacing descriptor\n",
			  getName(), this);

		IOBufferMemoryDescriptor *bufferDesc = IOBufferMemoryDescriptor::withBytes(reportDescriptor->getBytesNoCopy(),
																				   reportDescriptor->getLength(),
																				   kIODirectionOutIn);
		if(bufferDesc) {
			*desc = bufferDesc;
			return kIOReturnSuccess;
		} else {
			bufferDesc->release();
			*desc = NULL;
			return kIOReturnNoMemory;
		}
	} else {
		IOLog("IOBluetoothHIDDriverDescriptorOverride(%s)[%p]::newReportDescriptor - "
			  "No %s data in personality, calling IOBluetoothHIDDriver::newReportDescriptor\n",
			  getName(), this, REPORT_DESCRIPTOR_OVERRIDE_KEY);
		return IOBluetoothHIDDriver::newReportDescriptor(desc);
	}
}

bool IOBluetoothHIDDriverDescriptorOverride::start( IOService * provider )
{
	IOLog("IOBluetoothHIDDriverDescriptorOverride::(%s)[%p]start for %s", getName(), this, provider->getName());
	return IOBluetoothHIDDriver::start(provider);
}

bool IOBluetoothHIDDriverDescriptorOverride::didTerminate( IOService * provider, IOOptionBits options, bool * defer )
{
	IOLog("IOBluetoothHIDDriverDescriptorOverride::(%s)[%p]didTerminate for %s", getName(), this, provider->getName());
	return IOBluetoothHIDDriver::didTerminate(provider, options, defer);
}

bool IOBluetoothHIDDriverDescriptorOverride::terminate( IOOptionBits options )
{
	IOLog("IOBluetoothHIDDriverDescriptorOverride::(%s)[%p]terminate", getName(), this);
	return IOBluetoothHIDDriver::terminate(options);
}
