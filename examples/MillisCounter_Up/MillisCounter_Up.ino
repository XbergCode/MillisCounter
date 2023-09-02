//    FILE: MillisCounter_Up.ino
//  AUTHOR: XbergCode
// VERSION: 1.0.0
// PURPOSE: Arduino library to count up and down time using the millis() function.
//     URL: https://github.com/XbergCode/MillisCounter


// Millis Counter Library
#include <MillisCounter.h>                                    // Millis Counter Library
MillisCounter countUp;                                        // Set The Call Name

// Global Time String
//char countUp_Str[38] = "No Time"; // 100.Y, 10.M, 10.D, 10.h, 10.m, 10.sec = 37.Characters


void setup() {
  Serial.begin(115200UL);                          // Start The Serial
  delay(500);                                      // Give Serial Time To Wake Up
  Serial.println(F("\nSketch Purpose: Millis Counter."));  // Serial Print Sketch Purpose
  Serial.print(F("Version: ")); Serial.println(MILLISCOUNTER_VERSION);
  
  // Run Count Up Timer
  bool runTheCounter = true;                       // Bool For The Counter Status
  countUp.getCountUp();                            // Run The Counter
  delay(412UL);                                    // Delay For Some Time
  Serial.println(countUp.getCountUp());            // Print The Count Up Time
  countUp.reset();                                 // Reset The Counter
  runTheCounter = countUp.isRunning();             // Get And Set The Counter Running Status
  Serial.print(F("Counter Bool State: "));         // Serial Print Counter State
  if (runTheCounter) Serial.println(F("On."));     // Counter Is On
  else Serial.println(F("Off."));                  // Counter Is Off
}

void loop() {
  // Count Up
  //runTheCountUp1();              // Run The Count Up Function
  //runTheCountUp2();              // Run The Count Up Function
  runTheCountUp_Custom();        // Get The Count Up Time - Make Custom Output String

  delay(10);                     // Slow Down A Bit
}


// Count Up Function 1 - Max: 4294967295.sec = 136.years, 70.days, 6.hours, 28.min, 15.sec (49710.days)
void runTheCountUp1() {          // Run The Count Up Function
  // Local Variables
  MillisCounter countUp1;                                      // Set The Call Name
  const uint32_t MILLIS = millis();                            // Get The Millis Once Per Run
  char countUp_Str[38] = "Empty";                              // Local Buffer For The Time String
  
  // Simulate Something Turning On / Off
  const uint32_t RunTheTimerForX = 1000UL * 10UL;              // Run The Function Every X Seconds
  static uint32_t RunTheTimer_Wait = MILLIS;                   // Keep Track Of The Time
  static bool runTheCounter = true;                            // Start/Stop The Counter
  
  // Simulate Something Turning On / Off
  if (MILLIS - RunTheTimer_Wait >= RunTheTimerForX) {          // Wait For Timeout
    RunTheTimer_Wait = MILLIS;                                 // Keep Track Of The Time
    
    // Stop The Counter < "Like if some light turns off"
    if (runTheCounter) {                                       // Counter Is On - Stop The Counter
      countUp1.reset();                                        // Reset The Counter
      runTheCounter = false;                                   // Stop The Counter
      //runTheCounter = countUp1.isRunning();                    // Get And Set The Counter Running Status
      Serial.println(F("Counter Was Turned Off."));            // Serial Print
    }
    
    // Start The Counter < "Like if some light turns on"
    else runTheCounter = true;                                 // Counter Is Off - Start The Counter
  }
  
  // Get And Print The Time
  const uint32_t Function_Time = 1000UL;                       // Run The Function Every X Seconds
  static uint32_t Function_Wait = 0UL;                         // Keep Track Of The Time
  if (MILLIS - Function_Wait >= Function_Time) {               // Wait For Timeout
    Function_Wait = MILLIS;                                    // Keep Track Of The Time
    if (runTheCounter) {                                       // If The Counter Is On
      strcpy(countUp_Str, countUp1.getCountUp());              // Make The Time String
      // Serial Print The Time
      Serial.print(F("Run Time 1: ")); Serial.println(countUp_Str);
    }
  }
}

// Count Up Function 2
void runTheCountUp2() {          // Run The Count Up Function
  // Local Variables
  MillisCounter countUp2;                                      // Set The Call Name
  const uint32_t MILLIS = millis();                            // Get The Millis Once Per Run
  char countUp_Str[38] = "Empty";                              // Local Buffer For The Time String
  
  // Simulate Something Turning On / Off
  const uint32_t RunTheTimerForX = 1000UL * 12UL;              // Run The Function Every X Seconds
  static uint32_t RunTheTimer_Wait = MILLIS;                   // Keep Track Of The Time
  static bool runTheCounter = true;                            // Start/Stop The Counter
  
  // Simulate Something Turning On / Off
  if (MILLIS - RunTheTimer_Wait >= RunTheTimerForX) {          // Wait For Timeout
    RunTheTimer_Wait = MILLIS;                                 // Keep Track Of The Time
    
    // Stop The Counter < "Like if some light turns off"
    if (runTheCounter) {                                       // Counter Is On - Stop The Counter
      countUp2.reset();                                        // Reset The Counter
      runTheCounter = false;                                   // Stop The Counter
      //runTheCounter = countUp2.isRunning();                    // Get And Set The Counter Running Status
      Serial.println(F("Counter Was Turned Off."));            // Serial Print
    }
    
    // Start The Counter < "Like if some light turns on"
    else runTheCounter = true;                                 // Counter Is Off - Start The Counter
  }

  // Get And Print The Time
  const uint32_t Function_Time = 1000UL;                       // Run The Function Every X Seconds
  static uint32_t Function_Wait = 0UL;                         // Keep Track Of The Time
  if (MILLIS - Function_Wait >= Function_Time) {               // Wait For Timeout
    Function_Wait = MILLIS;                                    // Keep Track Of The Time
    if (runTheCounter) {                                       // If The Counter Is On
      strcpy(countUp_Str, countUp2.getCountUp());              // Make The Time String
      const uint32_t _tSeconds = countUp2.getTotalSeconds();   // Get The Total Seconds (0-4294967295)
      // Serial Print The Time
      Serial.print(F("Run Time 2: ")); Serial.println(countUp_Str);
      Serial.print(F("Run Time 2 Total Seconds: ")); Serial.println(_tSeconds);
    }
  }
}

// Count Up Function Custom Output String
void runTheCountUp_Custom() {    // Run The Count Up Function
  // Local Variables
  MillisCounter countUpCustom;                                 // Set The Call Name
  const uint32_t MILLIS = millis();                            // Get The Millis Once Per Run
  char countUp_Str[38] = "Empty";                              // Local Buffer For The Time String
  
  // Simulate Something Turning On / Off
  const uint32_t RunTheTimerForX = 1000UL * 13UL;              // Run The Function Every X Seconds
  static uint32_t RunTheTimer_Wait = MILLIS;                   // Keep Track Of The Time
  static bool runTheCounter = true;                            // Start/Stop The Counter
  
  // Simulate Something Turning On / Off
  if (MILLIS - RunTheTimer_Wait >= RunTheTimerForX) {          // Wait For Timeout
    RunTheTimer_Wait = MILLIS;                                 // Keep Track Of The Time
    
    // Stop The Counter < "Like if some light turns off"
    if (runTheCounter) {                                       // Counter Is On - Stop The Counter
      countUpCustom.reset();                                   // Reset The Counter
      runTheCounter = false;                                   // Stop The Counter
      //runTheCounter = countUpCustom.isRunning();               // Get And Set The Counter Running Status
      Serial.println(F("Counter Was Turned Off."));            // Serial Print
    }
    
    // Start The Counter < "Like if some light turns on"
    else runTheCounter = true;                                 // Counter Is Off - Start The Counter
  }
  
  // Get And Print The Time
  const uint32_t Function_Time = 1000UL;                       // Run The Function Every X Seconds
  static uint32_t Function_Wait = 0UL;                         // Keep Track Of The Time
  if (MILLIS - Function_Wait >= Function_Time) {               // Wait For Timeout
    Function_Wait = MILLIS;                                    // Keep Track Of The Time
    if (runTheCounter) {                                       // If The Counter Is On
      // Call The Count Up Function
      countUpCustom.getCountUp();                              // Call The Count Up Function
      // Variables For The Custom String
      const uint8_t  _seconds  = countUpCustom.getSeconds();     // Get Seconds (0-59)
      const uint8_t  _minutes  = countUpCustom.getMinutes();     // Get Minutes (0-59)
      const uint8_t  _hours    = countUpCustom.getHours();       // Get Hours   (0-23)
      const uint8_t  _days     = countUpCustom.getDays();        // Get Days    (0-31)
      const uint8_t  _months   = countUpCustom.getMonths();      // Get Months  (0-11)
      const uint8_t  _years    = countUpCustom.getYears();       // Get Years   (0-136)
      const uint16_t _tDays    = countUpCustom.getTotalDays();   // Get Total Days (0-49710)
      const uint32_t _tSeconds = countUpCustom.getTotalSeconds();// Get The Total Seconds (0-4294967295)
      
      // Make The Time String
      if (_years == 0U) {                                      // Run Time Is Less Than One Year
        if (_seconds == 0U && _minutes == 0U && _hours == 0U && _days == 0U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.sec"), _seconds);
        else if (_minutes == 0U && _hours == 0U && _days == 0U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.sec's"), _seconds);
        else if (_minutes == 1U && _hours == 0U && _days == 0U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.min, %u.sec"), _minutes, _seconds);
        else if (_minutes >= 2U && _hours == 0U && _days == 0U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.min's, %u.sec"), _minutes, _seconds);
        else if (_hours >= 1U && _days == 0U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.h, %u.min, %u.sec"), _hours, _minutes, _seconds);
        else if (_days == 1U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.D, %u.h, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
        else if (_days >= 2U && _months == 0U)
          sprintf_P(countUp_Str, PSTR("%u.D's, %u.h, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
        else if (_months >= 1U)
          sprintf_P(countUp_Str, PSTR("%u.M, %u.D, %u.h, %u.min, %u.sec"), _months, _days, _hours, _minutes, _seconds);
      } else                                                   // Run Time Is More Than One Year
        sprintf_P(countUp_Str, PSTR("%u.Y, %u.M, %u.D, %u.h, %u.m, %u.sec"), _years, _months, _days, _hours, _minutes, _seconds);
      
      // Serial Print The Time
      Serial.print(F("Run Time Custom: ")); Serial.println(countUp_Str);
      Serial.print(F("Run Time. Total Days: ")); Serial.println(_tDays);
      Serial.print(F("Run Time. Total Seconds: ")); Serial.println(_tSeconds);
    }
  }
}


// End Of File.
