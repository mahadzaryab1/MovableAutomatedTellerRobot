const int PIN_SIZE = 4;

int getPinEntered(tMotor port, int pinDigit);

task main(){
	int pin[PIN_SIZE] = {0, 0, 0, 0};
	int correctPin[PIN_SIZE] = {2, 3, 4, 5};

	for (int digits = 0; digits < PIN_SIZE; digits ++){
		pin[digits] = getPinEntered(motorA, digits);

	}

	bool incorrectPin = false;
	for (int index = 0; index < PIN_SIZE && !incorrectPin; index ++){
		if (pin[index] != correctPin[index])
			incorrectPin = true;
	}

	eraseDisplay();

	if (!incorrectPin){
		displayBigTextLine(3, "Correct Pin!");
		wait1Msec(10000);
	}
	else{
		displayBigTextLine(3, "Nope!");
		wait1Msec(10000);
	}
}

int getPinEntered(tMotor port, int pinDigit){
	nMotorEncoder[port] = 0;
	bool buttonPressed = getButtonPress(buttonEnter);
	int savedPinValue = 0;
	int pinValue = 0;
	while (nMotorEncoder[port] < 360 && nMotorEncoder[motorA] >= 0 && !buttonPressed){
		int pinValue = nMotorEncoder[port]/11;
		motor[port] = 1;
		eraseDisplay();
		motor[port] = -1;
		displayBigTextLine(3, "Pin Digit %d: %d", pinDigit, nMotorEncoder[port] / 11);
		wait1Msec(1);
		if (nMotorEncoder[port] < 0){
			nMotorEncoder[port] = 1100;
		}
		if (nMotorEncoder[port] > 1100) {
			nMotorEncoder[port] = 0;
		}
		while (getButtonPress(buttonEnter)){
			buttonPressed = true;
			savedPinValue = pinValue;
		}
	}
	return savedPinValue;
}
