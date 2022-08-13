#include <DF-Print.h>

void setup()
{
	Serial.begin(115200);

	String exampleValue1 = "Here is some text";
	int exampleValue2 = random(100);
	float exampleValue3 = 3.14;

	// If you define the preprocessor define 'DF_DISABLE_DEBUG_PRINT', then every use of DEBUG_PRINT* will be removed during compilation
	DEBUG_PRINTLN("Hello world");
	DEBUG_PRINTLN("Insert string ->> '{0}' <<- right there", exampleValue1);
	DEBUG_PRINTLN("You can have more than one value inserted: {0} * {1} = {2}", exampleValue2, exampleValue3, exampleValue2 * exampleValue3);

	DF::Print("Alternatively, you can call the print function directly if this is something you want to remain in your release build");
}

void loop()
{
}