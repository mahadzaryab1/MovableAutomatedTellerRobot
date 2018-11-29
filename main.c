const int MAXROW = 4;
const int MAXCOL = 4;

void displayMenu(int balance, int time);
void configureSensors();
int readCard (int *accountColors);
int depositMoney();
int getWithdrawAmount (int accountBalance);
void withdrawMoney(tMotor port, int amountWithdraw);
int getPinEntered(tMotor port, int pinDigit);
int isCorrectPin (int *pin, int *correctPin);

task main ()
{
	int accountNum = 0;
	int timer = 0;
	configureSensors();
	int accountPins[MAXROW][MAXCOL] = {{1,2,3,4}, {5,6,7,8}, {1,3,5,7}, {1, 0, 1, 0}};
	int accountColors[MAXROW] = {(int)colorBlue, (int)colorRed, (int) colorBlack, (int) colorWhite};
	int accountBalance[MAXROW] = {100, 100, 100, 138000};
	string accountNames[MAXROW] = {"Matt", "Carol", "Thomas", "Carol"};

	bool intruder = false;

	while ((!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && !intruder)
	{
		displayBigTextLine(2, "  Welcome to");
		displayBigTextLine(4, "  the ATM");
		wait1Msec(1000);
		displayBigTextLine(8, "  Insert Card");
		displayBigTextLine(10, "  <<<<<<<<<<");
		wait1Msec(500);
		while (SensorValue[S1] == 1  && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && !intruder)
		{
			eraseDisplay();
			int pinEntered[MAXCOL] = {0, 0, 0, 0};

			accountNum = readCard(accountColors);

			displayBigTextLine(3, "Welcome %s", accountNames[accountNum]);
			wait1Msec(1500);
			eraseDisplay();
			displayBigTextLine(3, "Enter Pin: ");
			wait1Msec(2000);
			eraseDisplay();

			int numAttempts = 3;
			bool pinVerified = false;

			while (numAttempts > 0 && !pinVerified && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && SensorValue[S1] == 1)
			{
				for (int digits = 0; digits < MAXCOL; digits ++)
					pinEntered[digits] = getPinEntered(motorA, digits);


				if (isCorrectPin(pinEntered, &accountPins[accountNum][0]))
				{
					pinVerified = true;
					displayBigTextLine(3, "Pin Verifed");
					wait1Msec(2000);
				}

				else
				{
					numAttempts--;
					displayBigTextLine(3, "Incorrect Pin");
					displayBigTextLine(5, "You have %d", numAttempts);
					displayBigTextLine(7, "attempts", numAttempts);
					wait1Msec(2000);

				}

			}

			if (pinVerified)
			{
				time1[T1] = 0;
				while (SensorValue[S1] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)))
				{
					timer = time1[T1]/1000;
					displayMenu(accountBalance[accountNum], timer);
					if (getButtonPress(buttonUp))
					{
						int withdrawAmount = getWithdrawAmount(accountBalance[accountNum]);
						withdrawMoney(motorB, withdrawAmount);
						accountBalance[accountNum] -= withdrawAmount;
					}
					else if (getButtonPress(buttonDown))
					{
						eraseDisplay();
						int amountDeposited = depositMoney();
						accountBalance[accountNum] += amountDeposited;
						displayBigTextLine(3, "Amount Deposited: %d", amountDeposited);
					}
					eraseDisplay();
				}
				displayBigTextLine(2, "Your session");
				displayBigTextLine(4, "today was:");
				displayBigTextLine(6, "%d seconds", timer);
				displayBigTextLine(8, "Good Day %s", accountNames[accountNum]);
				wait1Msec(3000);
				eraseDisplay();
			}

			else
			{
				for (int numBlink = 0; numBlink < 4 ; numBlink ++)
				{
					displayBigTextLine(3, "Intruder Alert!");
					wait1Msec(600);
					eraseDisplay();
					wait1Msec(200);
				}

				intruder = true;
			}
		}
	}

	for (int numBlink = 0; numBlink < 4 ; numBlink ++)
	{
		displayBigTextLine(3, "Shutting Down");
		wait1Msec(1000);
		eraseDisplay();
		wait1Msec(500);
	}
}

void displayMenu(int balance, int time)
{
	displayBigTextLine(2, "Withdraw:UP");
	displayBigTextLine(4, "Deposit:DOWN");
	displayBigTextLine(6, "Exit - Remove");
	displayBigTextLine(8, "  Credit Card");
	displayBigTextLine(10, "Bal:%d", balance);
	displayBigTextLine(12, "Time: %d secs", time);
	wait1Msec(10);
}

void configureSensors()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec (50);
}

int readCard(int *accountColors)
{
	int colorCard = SensorValue[S2];
	int accountNumber = 0;
	for (int index = 0; index < MAXROW; index++)
	{
		if (accountColors[index] == colorCard)
			accountNumber = index;
	}

	return accountNumber;
}

int getWithdrawAmount (int accountBalance)
{

	int amountWithdrawing = 0;
	bool backButtonPressed = false;

	while (!getButtonPress(buttonEnter) && SensorValue[S1] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && !backButtonPressed)
	{

		int change = 0;

		while (getButtonPress(buttonUp))
			change = 10;

		while (getButtonPress(buttonDown))
			if (amountWithdrawing > 10)
			change = -10;

		while (getButtonPress(buttonBack))
			backButtonPressed = true;

		amountWithdrawing += change;

		eraseDisplay();

		displayBigTextLine(3, "Withraw: %.2f", amountWithdrawing);
		displayBigTextLine(5, "Press ENTER");
		displayBigTextLine(7, "to Confirm");
		wait1Msec(100);

		eraseDisplay();
	}

	if (amountWithdrawing <= accountBalance && !backButtonPressed)
		return amountWithdrawing;

	else if (amountWithdrawing > accountBalance)
	{
		displayBigTextLine (3, "Insufficient");
		displayBigTextLine (5, "funds in");
		displayBigTextLine (7, "account");
		wait1Msec(2000);
		eraseDisplay();
	}

	return 0;
}

int depositMoney()
{
	int amountDeposit = 0;
	while (!getButtonPress(buttonEnter) && SensorValue[S1] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)))
	{
		displayBigTextLine(3, "Depositing...");
		wait1Msec(10);
		int change = 0;
		eraseDisplay();

		if (SensorValue[S3] == (int) colorRed)
		{
			displayBigTextLine(3, "$5 Detected...");
			wait1Msec(1000);
			change = 5; // I changed it in main
		}

		if (SensorValue [S3] == (int) colorBlue)
		{
			displayBigTextLine(3, "$10 Detected...");
			wait1Msec(1000);
			change = 10;
		}

		if (SensorValue [S3] == (int) colorGreen)
		{
			displayBigTextLine(3, "$20 Detected...");
			wait1Msec(1000);
			change = 20;
		}

		amountDeposit += change;
		eraseDisplay();

	}
	return amountDeposit;

}

void withdrawMoney(tMotor port, int amountWithdraw)
{
	nMotorEncoder[port] = 0;
	int num10Bills = amountWithdraw/10;

	for(int count = 0; count < num10Bills; count ++)
	{
		motor[port] = -10;

		while (nMotorEncoder[port] > -105*num10Bills)
		{
			displayBigTextLine(3, "Withdraw: $%.2f ", (float) amountWithdraw);
			wait1Msec(10);
			eraseDisplay();
		}

		motor[port] = 0;
	}
}
int isCorrectPin (int *pin, int *correctPin)
{
	bool incorrectPin = false;
	for (int index = 0; index < MAXCOL && !incorrectPin; index ++)
	{
		if (pin[index] != correctPin[index])
			incorrectPin = true;
	}

	return !incorrectPin;
}

int getPinEntered(tMotor port, int pinDigit)
{
	nMotorEncoder[port] = 0;
	bool buttonPressed = getButtonPress(buttonEnter);
	int savedPinValue = 0;
	int pinValue = 0;
	while (!buttonPressed && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)))
	{
		int pinValue = -nMotorEncoder[port]/40;
		motor[port] = 1;
		eraseDisplay();
		motor[port] = -1;
		displayBigTextLine(3, "Pin Digit %d: %d", pinDigit + 1, pinValue);
		wait1Msec(1);

		if (pinValue < 0)
		{
			nMotorEncoder[port] -= 350;
		}

		if (pinValue > 9)
		{
			nMotorEncoder[port] += 400;
		}

		while (getButtonPress(buttonEnter))
		{
			buttonPressed = true;
			savedPinValue = pinValue;
		}
	}
	motor[port] = 0;
	return savedPinValue;
}
