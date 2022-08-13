# DF-Print
A simple library for Arduino that brings a C# style string formatting library

## Current functionality
Right now, it's just a wrapper around `Serial.print`, there's a lot missing if you're expecting comprehensive printf style support.
You can do things like `DF::Println("A formula: {0} + {1} = {2}", var1, var2, var1 + var2);`. The text inside the argument specifiers `{}` is currently ignored, and there is no formatting per se (beyond what `Serial.print()` does internally).

## Planned
- Selectable outputs
 - It would be nice to be able to print text to things other than the serial output, that would enable this library to be more than just a debugging aid
- Unit Tests
 - Once selectable outputs are accomplished, we can then implement some unit tests to ensure this library actually does what it says on the tin
- Argument formatting
 - This is a big topic, but getting at least some of the functionality described at https://docs.microsoft.com/en-us/dotnet/api/system.string.format would be extremely benefitial
- Out of order arguments (i.e. reference the same argument more than once or {2} before {1})
  - This may never happen, as this library is intended for microcontrollers, which typically have very little memory, I worry that this might need more resources than a library like this should need to use.

## Example
    Serial.begin(115200);
    
    String exampleValue1 = "Here is some text";
    int exampleValue2 = random(100);
    float exampleValue3 = 3.14;
    
    // If you define the preprocessor define 'DF_DISABLE_DEBUG_PRINT', then every use of DEBUG_PRINT* will be removed during compilation
    DEBUG_PRINTLN("Hello world");
    DEBUG_PRINTLN("Insert string ->> '{0}' <<- right there", exampleValue1);
    DEBUG_PRINTLN("You can have more than one value inserted: {0} * {1} = {2}", exampleValue2, exampleValue3, exampleValue2 * exampleValue3);
    
    DF::Print("Alternatively, you can call the print function directly if this is something you want to remain in your release build");
