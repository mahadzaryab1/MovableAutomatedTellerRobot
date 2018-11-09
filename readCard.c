TLegoColors readCard ()
{
	TLegoColors colorCard;
	while (SensorValue[] == 0)
	{}

	wait1MSec(100);	
	colorCard = SensorValue[];

	return colorCard;
}