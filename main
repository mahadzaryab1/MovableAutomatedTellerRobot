const int MAXROW = 3;
const int MAXCOL = 4;

void displayMenu();
void configureSensors();
int readCard (int *accountColors);
int depositMoney(int accountBalance);
int getWithdrawAmount (int accountBalance);
void withdrawMoney(tMotor port, int amountWithdraw);
int getPinEntered(tMotor port, int pinDigit)

task main()
{
	configureSensors();
	int accountPins[MAXROW][MAXCOL] = {{1,2,3,4}, {5,6,7,8}, {1,3,5,7}};
	int accountColors[MAXROW] = {(int)colorBlue, (int)colorRed, (int) colorBlack};
	int accountBalance[MAXROW] = {100, 100, 100};
  string accountNames[MAXROW] = {"Matt", "Carol", "Thomas"}
	
	// Dont start the timer yet, it starts when a user enters the correct pin time1[T1] = 0;
  bool intruder = false;
  
  while ((!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && !intruder)
  {
  	displayBigTextLine(1, "  Welcome to the SUPER ATM");
    displayBigTextLine(3, "Insert Card to get started.");
  	while (SensorValue[TOUCHSENSOR] == 1  && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && !intruder)
    {
    	int pinEntered[MAXCOL] = {0, 0, 0, 0};
      
      int accountNum = readCard(accountColors);
      
      displayBigTextLine(3, "Welcome %s", accountName[accountNum]);
      wait1Msec(1500);
      eraseDisplay();
      displayBigTextLine(3, "Please enter your Pin");
      displayBigTextLine (5, "to confirm your identity");
      wait1Msec(2000);
      eraseDisplay();
      
      int numAttempts = 3;
      bool pinVerified = false;
      
      while (numAttempts > 0 && !pinVerified && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)) && SensorValue[TOUCHSENSOR] == 1) 
      {
        for (int digits = 0; digits < MAXCOL; digits ++)
          pinEntered[digits] = getPinEntered(motorA, digits);
          

        if (isCorrectPin(pinEntered, accountPins[accountNum]))
        {
          pinVerified = true;
          displayBigTextLine(3, "---= Pin Verifed =---");
          wait1Msec(2000);
        }
        
        else 
        {
        	numAttempts--;
        	displayBigTextLine(3, "---= Incorrect Pin =---");
          displayBigTextLine(5, "You have %d attempts remaining", numAttempts);
          wait1Msec(2000);
         
        }
        
      }
      
      if (pinVerified)
      {
        time1[T1] = 0;
				while (SensorValue[TOUCHSENSOR] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown))) 
        {
        	displayMenu();
          if (getButtonPress(buttonUp))
          {
          	getWithdrawAmount(accountBalance[accountNum]);
						withdrawMoney(MOTORPORT, accountBalance[accountNum])
          }
          else if (getButtonPress(buttonDown))
          {
          	accountBalance[accountNum] = depositMoney(accountBalance[accountNum]); 
            displayBigTextLine(3, "Amount Deposited: %d", amountDeposited);
          }
        }
      }
      
      else
      {
      	  for (int numBlink = 0; numBlink > 5 ; numBlink ++)
  				{
            displayBigTextLine(3, "Intruder Alert");
            wait1Msec(600);
            eraseDisplay();
            wait1Msec(200);
  				}
          
        	intruder = true;
      }    
    }
  }
  
  for (int numBlink = 0; numBlink > 5 ; numBlink ++)
  {
  	  displayBigTextLine(3, "Shutting Down");
      wait1Msec(1000);
      eraseDisplay();
      wait1Msec(500);
  }
}

// END OF MAIN
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void displayMenu()
{
	displayBigTextLine(2, "Deposit -   DOWN button");
  displayBigTextLine(4, "Withdraw -    UP button");
  displayBigTextLine(6, "Exit - Pull Credit Card Out");
}

void configureSensors()
{
	SensorType[] = SensorEV3_Touch;
	SensorType[] = SensorEV3_Color;
	wait1Msec(50);
	SensorMode[] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[] = SensorEV3_Color;
	wait1Msec(50);
	SensorMode[] = modeEV3Color_Color;
	wait1Msec (50);
}

int readCard(int *accountColors)
{
	int colorCard = SensorValue[];
	int accountNumber = 0;
	for (int index = 0; index < MAXROW; index++)
	{
		if (accountColors[index] == colorCard)
			accountNumber = index;
	}
	
	return accountNumber;
}

int depositMoney(int accountBalance)
{
	int amountDeposit = 0;
	while (!getButtonPress(buttonEnter) && SensorValue[TOUCHSENSOR] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown))
	{
  	displayBigTextLine(3, "Depositing Money ...");
		int change = 0;
    eraseDisplay();
    
		while (SensorValue[] == (int) colorRed && SensorValue[TOUCHSENSOR] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)))
		{
			displayBigTextLine(3, "$5 Bill Detected ...");
      change = 5; // I changed it in main 
    }
    
		while (SensorValue [] == (int) colorBlue && SensorValue[TOUCHSENSOR] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)))
		{
    	displayBigTextLine(3, "$10 Bill Detected ...");
			change = 10;
		}
    
		while (SensorValue [] == (int) colorGreen && SensorValue[TOUCHSENSOR] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown)))
		{
    	displayBigTextLine(3, "$20 Bill Detected ...");
			change = 20;
		}
    
    eraseDisplay();
    
	}
  
  accountBalance += amountDeposit;
  return accountBalance;
	
}

int getWithdrawAmount (int accountBalance)
{

		int amountWithdrawing = 0;
    bool backButtonPressed = false;

		while (!getButtonPress(buttonEnter) && SensorValue[TOUCHSENSOR] == 1 && (!getButtonPress(buttonUp) || !getButtonPress(buttonDown) && !backButtonPressed)
    {

			int change = 0;

			while (getButtonPress(buttonUp))
				change = 10;

			while (getButtonPress(buttonDown))
				if (change > 10)
					change = -10;
			
    	while (getButtonPress(buttonBack))
          	backButtonPressed = true;
      
			amountWithdrawing += change;
      
      eraseDisplay();
      
      displayBigTextLine("Withrawing: %d", accountBalance);
      displayBigTextLine(5, "Press ENTER to Withdraw");
      wait1Msec(100);
      
      eraseDisplay();
		}

		if (amountWithdrawing <= accountBalance && !backButtonPressed)
			return amountWithdrawing;
      
    else if (amountWithdrawing > accountBalance)
    {
    	displayBigTextLine (3, "Insufficient Funds in Account");
      wait1Msec(2000);
      eraseDisplay();
    }

		return 0;
}

void withdrawMoney(tMotor port, int amountWithdraw)
{
	nMotorEncoder[port] = 0;
	int num10Bills = amountWithdraw/10;

	for(int count = 0; count < num10Bills; count ++){
  	
		motor[port] = 3;

		while (nMotorEncoder[port] < 20){
    displayBigTextLine(3, "Withdrawing $%.2f", (float)amountWithdraw);
    eraseDisplay();
    }

		motor[port] = 0;
	}
}
//Example usage: withdrawMoney(getWithdrawMoney(accountBalance[x]));


int isCorrectPin (int *pin, int *correctPin)
{
	bool incorrectPin = false;
	for (int index = 0; index < MAXCOL && !incorrectPin; index ++){
		if (pin[index] != correctPin[index])
			incorrectPin = true;
	}

	return !incorrectPin;
}

// THE FOLLOWING FUNCTION DOES NOT CURRENTLY WORK (IT WILL BE REPLACED SOON)
int getPinEntered(tMotor port, int pinDigit)
{
	nMotorEncoder[port] = 0;
	bool buttonPressed = getButtonPress(buttonEnter);
	int savedPinValue = 0;
	int pinValue = 0;
	while (nMotorEncoder[port] < 360 && nMotorEncoder[motorA] >= 0 && !buttonPressed)
  {
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
