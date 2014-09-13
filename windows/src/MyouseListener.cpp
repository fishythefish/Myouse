#include <MyouseListener.h>

myouse::MyouseListener::MyouseListener()
{
}

myouse::MyouseListener::~MyouseListener()
{
}

void myouse::MyouseListener::onPair(myo::Myo * myo, uint64_t timestamp,
	myo::FirmwareVersion firmwareVersion)
{
}

void myouse::MyouseListener::onUnpair(myo::Myo * myo, uint64_t timestamp)
{
}

void myouse::MyouseListener::onConnect(myo::Myo * myo, uint64_t timestamp,
	myo::FirmwareVersion firmwareVersion)
{
}

void myouse::MyouseListener::onDisconnect(myo::Myo * myo, uint64_t timestamp)
{
}

void myouse::MyouseListener::onArmRecognized(myo::Myo * myo, uint64_t timestamp,
	myo::Arm arm, myo::XDirection xDirection)
{
}

void myouse::MyouseListener::onArmLost(myo::Myo * myo, uint64_t timestamp)
{
}

void myouse::MyouseListener::onPose(myo::Myo * myo, uint64_t timestamp)
{
}

void myouse::MyouseListener::onOrientationData(myo::Myo * myo, uint64_t timestamp,
	const myo::Quaternion<float> & rotation)
{
}

void myouse::MyouseListener::onAccelerometerData(myo::Myo * myo, uint64_t timestamp,
	const myo::Vector3<float> & accel)
{
}

void myouse::MyouseListener::onGyroscopeData(myo::Myo * myo, uint64_t timestamp,
	const myo::Vector3<float> & gyro)
{
}

void myouse::MyouseListener::onRssi(myo::Myo * myo, uint64_t timestamp,
	int8_t rssi)
{
}

void myouse::MyouseListener::onOpaqueEvent(libmyo_event_t)
{
}