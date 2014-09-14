#define _USE_MATH_DEFINES

#include <myo/myo.hpp>
#include <myo/cxx/Quaternion.hpp>
#include <myouse/MyouseListener.h>
#include <Windows.h>
#include <math.h>

static const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
static const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
static const double X_SCALE_FACTOR = 65535.0 / (SCREEN_WIDTH - 1);
static const double Y_SCALE_FACTOR = 65535.0 / (SCREEN_HEIGHT - 1);
static const double X_SPEED = 1;
static const double Y_SPEED = SCREEN_WIDTH * 1.0 / SCREEN_HEIGHT;
static const int DRAG_THRESHOLD = 10;
static const double SCROLL_THRESHOLD = M_PI / 24;
static const double SCROLL_SPEED = 10;

myouse::MyouseListener::MyouseListener()
	: myo(0), xDir(), isEnabled(false),
	isScrolling(false), leftDown(false), rightDown(false), middleDown(false),
	rawRoll(0), rawPitch(0), rawYaw(0),
	rollOffset(0), pitchOffset(0), yawOffset(0),
	lastX(0), lastY(0)
{
}

myouse::MyouseListener::~MyouseListener()
{
}

void myouse::MyouseListener::onPair(myo::Myo * myo, uint64_t timestamp,
	myo::FirmwareVersion firmwareVersion)
{
	std::cout << "Myo paired." << std::endl;
}

void myouse::MyouseListener::onUnpair(myo::Myo * myo, uint64_t timestamp)
{
	std::cout << "Myo unpaired." << std::endl;
	isEnabled = false;
	isScrolling = false;
	leftDown = false;
	rightDown = false;
	middleDown = false;
	rawRoll = 0;
	rawPitch = 0;
	rawYaw = 0;
	rollOffset = 0;
	pitchOffset = 0;
	yawOffset = 0;
	lastX = 0;
	lastY = 0;
}

void myouse::MyouseListener::onConnect(myo::Myo * myo, uint64_t timestamp,
	myo::FirmwareVersion firmwareVersion)
{
	std::cout << "Myo connected." << std::endl;
	this->myo = myo;
}

void myouse::MyouseListener::onDisconnect(myo::Myo * myo, uint64_t timestamp)
{
	std::cout << "Myo disconnected." << std::endl;
	this->myo = 0;
}

void myouse::MyouseListener::onArmRecognized(myo::Myo * myo, uint64_t timestamp,
	myo::Arm arm, myo::XDirection xDirection)
{
	std::cout << "Arm recognized." << std::endl;
	xDir = xDirection;
}

void myouse::MyouseListener::onArmLost(myo::Myo * myo, uint64_t timestamp)
{
	std::cout << "Arm lost." << std::endl;
}

void myouse::MyouseListener::onPose(myo::Myo * myo, uint64_t timestamp,
	myo::Pose pose)
{
	std::cout << "Pose: " << pose << std::endl;
	switch (pose.type())
	{
	case myo::Pose::rest:
		unclickLeft();
		unclickRight();
		unclickMiddle();
		isScrolling = false;
		break;
	case myo::Pose::fist:
		clickLeft();
		break;
	case myo::Pose::waveIn:
		clickMiddle();
		break;
	case myo::Pose::waveOut:
		isScrolling = true;
		break;
	case myo::Pose::fingersSpread:
		clickRight();
		break;
	case myo::Pose::thumbToPinky:
		isEnabled = !isEnabled;
		myo->vibrate(myo::Myo::vibrationMedium);
		if (isEnabled)
		{
			std::cout << "Myouse enabled." << std::endl;
			rollOffset = rawRoll;
			pitchOffset = rawPitch;
			yawOffset = rawYaw;
		}
		else
		{
			std::cout << "Myouse disabled." << std::endl;
		}
		break;
	default:
		break;
	}
}

void myouse::MyouseListener::onOrientationData(myo::Myo * myo, uint64_t timestamp,
	const myo::Quaternion<float> & rotation)
{
	using std::atan2;
	using std::asin;
	using std::sin;

	double newRoll = atan2(2.0f * (rotation.w() * rotation.x() + rotation.y() * rotation.z()),
		1.0f - 2.0f * (rotation.x() * rotation.x() + rotation.y() * rotation.y()));
	double newPitch = asin(2.0f * (rotation.w() * rotation.y() - rotation.z() * rotation.x()));
	double newYaw = atan2(2.0f * (rotation.w() * rotation.z() + rotation.x() * rotation.y()),
		1.0f - 2.0f * (rotation.y() * rotation.y() + rotation.z() * rotation.z()));

	double roll = newRoll - rollOffset;
	double pitch = newPitch - pitchOffset;
	double yaw = newYaw - yawOffset;

	if (xDir == myo::xDirectionTowardElbow) pitch *= -1;

	if (isScrolling)
	{
		if (pitch > SCROLL_THRESHOLD
			|| pitch < -SCROLL_THRESHOLD)
		{
			scroll(-pitch * SCROLL_SPEED / SCROLL_THRESHOLD);
		}
	}
	else
	{
		//moveMouse(SCREEN_WIDTH * (0.5 - X_SPEED * sin(yaw)),
		//	SCREEN_HEIGHT * (0.5 + Y_SPEED * sin(pitch)));

		int x = SCREEN_WIDTH * (0.5 - X_SPEED * yaw);
		int y = SCREEN_HEIGHT * (0.5 + Y_SPEED * pitch);

		bool dragging = leftDown || rightDown || middleDown;
		float dist = sqrt((x - lastX) * (x - lastX) + (y - lastY) * (y - lastY));

		if (!dragging || dist > DRAG_THRESHOLD)
		{
			moveMouse(SCREEN_WIDTH * (0.5 - X_SPEED * yaw),
				SCREEN_HEIGHT * (0.5 + Y_SPEED * pitch));

			lastX = x;
			lastY = y;
		}
	}

	rawRoll = newRoll;
	rawPitch = newPitch;
	rawYaw = newYaw;
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

void myouse::MyouseListener::moveMouse(long x, long y)
{
	if (!isEnabled) return;

	MOUSEINPUT mouseInput = { x * X_SCALE_FACTOR, y * Y_SCALE_FACTOR, 0,
		MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));
}

void myouse::MyouseListener::clickLeft()
{
	if (!isEnabled || leftDown) return;

	MOUSEINPUT mouseInput = { 0, 0, 0,
		MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));

	myo->vibrate(myo::Myo::vibrationShort);

	leftDown = true;
}

void myouse::MyouseListener::unclickLeft()
{
	if (!isEnabled || !leftDown) return;

	MOUSEINPUT mouseInput = { 0, 0, 0,
		MOUSEEVENTF_LEFTUP | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));

	myo->vibrate(myo::Myo::vibrationShort);

	leftDown = false;
}

void myouse::MyouseListener::clickRight()
{
	if (!isEnabled || rightDown) return;

	MOUSEINPUT mouseInput = { 0, 0, 0,
		MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));

	myo->vibrate(myo::Myo::vibrationShort);

	rightDown = true;
}

void myouse::MyouseListener::unclickRight()
{
	if (!isEnabled || !rightDown) return;

	MOUSEINPUT mouseInput = { 0, 0, 0,
		MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));

	myo->vibrate(myo::Myo::vibrationShort);

	rightDown = false;
}

void myouse::MyouseListener::clickMiddle()
{
	if (!isEnabled || middleDown) return;

	MOUSEINPUT mouseInput = { 0, 0, 0,
		MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));

	myo->vibrate(myo::Myo::vibrationShort);

	middleDown = true;
}

void myouse::MyouseListener::unclickMiddle()
{
	if (!isEnabled || !middleDown) return;

	MOUSEINPUT mouseInput = { 0, 0, 0,
		MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_VIRTUALDESK,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));

	myo->vibrate(myo::Myo::vibrationShort);

	middleDown = false;
}

void myouse::MyouseListener::scroll(int speed)
{
	if (!isEnabled || !isScrolling) return;

	MOUSEINPUT mouseInput = { 0, 0, speed,
		MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_WHEEL,
		0, GetMessageExtraInfo() };

	INPUT input = { INPUT_MOUSE, mouseInput };

	SendInput(1, &input, sizeof(INPUT));
}