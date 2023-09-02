//    FILE: MillisCounter_Down.ino
//  AUTHOR: XbergCode
// VERSION: 1.0.0
// PURPOSE: Arduino library to count up and down time using the millis() function.
//     URL: https://github.com/XbergCode/MillisCounter


// Millis Counter Library
#include <MillisCounter.h>                                    // Millis Counter Library

// Global Time String
//char countDown_Str[38] = "No Time"; // 100.Y, 100.D, 10.hour, 10.min, 10.sec = 37.Characters


void setup() {
  Serial.begin(115200UL);                          // Start The Serial
  delay(500);                                      // Give Serial Time To Wake Up
  Serial.println(F("\nSketch Purpose: Millis Counter."));  // Serial Print Sketch Purpose
  Serial.print(F("Version: ")); Serial.println(MILLISCOUNTER_VERSION);
}

void loop() {
  // Count Down
  //runTheCountDown1();            // Run The Count Down Function
  //runTheCountDown2();            // Run The Count Down Function
  runTheCountDown_Custom();      // Run The Count Down Function - Make Custom Output String

  delay(10);                     // Slow Down A Bit
}


// Count Down Function 1 - Max: 4294967295.sec = 136.years, 70.days, 6.hours, 28.min, 15.sec (49710.days)
void runTheCountDown1() {        // Run The Count Down Function
  // Variables - For Count Down 1
  MillisCounter countDown1;                                    // Set The Call Name
  static bool runTheCounter = true;                            // Start/Stop The Counter
  const uint32_t countSeconds = 10UL;                          // Count Down Time In Seconds
  
  // Call The Count Down Function
  if (runTheCounter) {                                         // If The Counter Is On - Serial Print
    Serial.print(F("Count Time 1: ")); Serial.println(countDown1.getCountDown(countSeconds));
  }

  // Get And Set The Counter Running Status
  //runTheCounter = countDown1.isRunning();                      // Get And Set The Counter Running Status
  
  // Turn The Count Down On/Off
  const uint32_t MILLIS = millis();                            // Get The Millis
  const uint32_t RunTheTimerForX = 1000UL * 15UL;              // Run The Function X Seconds
  static uint32_t RunTheTimer_Wait = MILLIS;                   // Keep Track Of The Time
  if (MILLIS - RunTheTimer_Wait >= RunTheTimerForX) {          // Wait For Timeout
    RunTheTimer_Wait = MILLIS;                                 // Keep Track Of The Time
    if (runTheCounter) {                                       // Counter Is On - Stop The Counter
      runTheCounter = false;                                   // Stop The Counter
      countDown1.reset();                                      // Reset The Timer
      Serial.println(F("Counter Was Turned Off."));            // Serial Print
    }
    else runTheCounter = true;                                 // Counter Is Off - Start The Counter
  }
  
  // Wait 1 Second Between Readings
  delay(1000UL);                                               // Wait 1 Seconds
}

// Count Down Function 2
void runTheCountDown2() {        // Run The Count Down Function
  // Variables - For Count Down 2
  MillisCounter countDown2;                                    // Set The Call Name
  static bool runTheCounter = true;                            // Start/Stop The Counter
  const uint32_t countSeconds = 3671UL;                        // Count Down Time In Seconds = 1.h, 1.m, 11.s
  const uint8_t y = 1, d = 2, h = 3, m = 4, s = 5;             // Time In Years, Days, Hours, Minutes & Seconds
  
  // Call The Count Down Function
  if (runTheCounter) {                                         // If The Counter Is On - Serial Print
    // Send As: Seconds - Max: 4294967295.sec = 136.years, 70.days, 6.hours, 28.min, 15.sec (49710.days)
    Serial.print(F("Count Time 2: ")); Serial.println(countDown2.getCountDown(countSeconds));
    
    // Send As: Minutes & Seconds
    //Serial.print(F("Count Time 2: ")); Serial.println(countDown2.getCountDown(s, m)); // sec, min
    
    // Send As: Hours, Minutes & Seconds
    //Serial.print(F("Count Time 2: ")); Serial.println(countDown2.getCountDown(s, m, h)); // sec, min, hour
    
    // Send As: Days, Hours, Minutes & Seconds
    //Serial.print(F("Count Time 2: ")); Serial.println(countDown2.getCountDown(s, m, h, d)); // sec, min, hour, days
    
    // Send As: Years, Days, Hours, Minutes & Seconds
    //Serial.print(F("Count Time 2: ")); Serial.println(countDown2.getCountDown(s, m, h, d, y)); // sec, min, hour, days, years
  }

  // Get And Set The Counter Running Status
  //runTheCounter = countDown2.isRunning();                      // Get And Set The Counter Running Status
  
  // Turn The Count Down On/Off
  const uint32_t MILLIS = millis();                            // Get The Millis
  const uint32_t RunTheTimerForX = 1000UL * 65UL;              // Run The Function X Seconds
  static uint32_t RunTheTimer_Wait = MILLIS;                   // Keep Track Of The Time
  if (MILLIS - RunTheTimer_Wait >= RunTheTimerForX) {          // Wait For Timeout
    RunTheTimer_Wait = MILLIS;                                 // Keep Track Of The Time
    if (runTheCounter) {                                       // Counter Is On - Stop The Counter
      runTheCounter = false;                                   // Stop The Counter
      countDown2.reset();                                      // Reset The Counter
      Serial.println(F("Counter Was Turned Off."));            // Serial Print
    }
    else runTheCounter = true;                                 // Counter Is Off - Start The Counter
  }

  // Wait 1 Second Between Readings
  delay(1000UL);                                               // Wait 1 Seconds
}

// Count Down Function Custom Output String
void runTheCountDown_Custom() {  // Run The Count Down Function - Make Custom Output String
  // Variables - For Count Down Custom
  MillisCounter countDownC;                                    // Set The Call Name
  static bool runTheCounter = true;                            // Start/Stop The Counter
  const uint32_t countSeconds = 3661UL;                        // Count Down Time In Seconds = 1.h, 1.m, 1.s
  char countDown_Str[38] = "Empty";                            // Local Buffer For The Time String
  
  // Call The Count Down Function
  if (runTheCounter) {                                         // If The Counter Is On - Serial Print
    countDownC.getCountDown(countSeconds);                     // Call The Count Down Function
    // Variables For The Custom String
    const uint8_t  _seconds  = countDownC.getSeconds();        // Get Seconds (0-59)
    const uint8_t  _minutes  = countDownC.getMinutes();        // Get Minutes (0-59)
    const uint8_t  _hours    = countDownC.getHours();          // Get Hours   (0-23)
    const uint16_t _days     = countDownC.getDays();           // Get Days    (0-364)
    const uint8_t  _years    = countDownC.getYears();          // Get Years   (0-136)
    const uint16_t _tDays    = countDownC.getTotalDays();      // Get Total Days (0-49710)
    const uint32_t _tSeconds = countDownC.getTotalSeconds();   // Get The Total Seconds (0-4294967295)
    
    // Make The Time String
    if (_years == 0U) {                                        // Less Than One Year
      if (_days == 0U && _hours == 0U && _minutes == 0U && _seconds == 0U)
        strcpy_P(countDown_Str, PSTR("Done."));
      else if (_days == 0U && _hours == 0U && _minutes == 0U && _seconds == 1U)
        sprintf_P(countDown_Str, PSTR("%u.sec"), _seconds);
      else if (_days == 0U && _hours == 0U && _minutes == 0U && _seconds > 1U)
        sprintf_P(countDown_Str, PSTR("%u.sec's"), _seconds);
      else if (_days == 0U && _hours == 0U && _minutes == 1U)
        sprintf_P(countDown_Str, PSTR("%u.min, %u.sec"), _minutes, _seconds);
      else if (_days == 0U && _hours == 0U && _minutes > 1U)
        sprintf_P(countDown_Str, PSTR("%u.min's, %u.sec"), _minutes, _seconds);
      else if (_days == 0U && _hours == 1U)
        sprintf_P(countDown_Str, PSTR("%u.h, %u.min, %u.sec"), _hours, _minutes, _seconds);
      else if (_days == 0U && _hours > 1U)
        sprintf_P(countDown_Str, PSTR("%u.h's, %u.min, %u.sec"), _hours, _minutes, _seconds);
      else if (_days == 1U && _hours >= 0U && _hours <= 1)
        sprintf_P(countDown_Str, PSTR("%u.d, %u.h, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
      else if (_days == 1U && _hours > 1U)
        sprintf_P(countDown_Str, PSTR("%u.d, %u.h's, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
      else if (_days > 1U && _hours >= 0U && _hours <= 1)
        sprintf_P(countDown_Str, PSTR("%u.d's, %u.h, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
      else if (_days > 1U && _hours > 1U)
        sprintf_P(countDown_Str, PSTR("%u.d's, %u.h's, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
    }
    else if (_years >= 1U && _years < 100U)                    // From One Year To 99 Years
      sprintf_P(countDown_Str, PSTR("%u.Y, %u.D, %u.h's, %u.min, %u.sec"), _years, _days, _hours, _minutes, _seconds);
    else                                                       // More Than 100 Years
      sprintf_P(countDown_Str, PSTR("%u.Y, %u.D, %u.h, %u.min, %u.sec"), _years, _days, _hours, _minutes, _seconds);
    
    // Serial Print The Time
    Serial.print(F("Count Time Custom: ")); Serial.println(countDown_Str);
    Serial.print(F("Count Time. Total Days: ")); Serial.println(_tDays);
    Serial.print(F("Count Time. Total Seconds: ")); Serial.println(_tSeconds);
  }

  // Get And Set The Counter Running Status
  runTheCounter = countDownC.isRunning();                      // Get And Set The Counter Running Status
  
  /*// Turn The Count Down On/Off
  const uint32_t MILLIS = millis();                            // Get The Millis
  const uint32_t RunTheTimerForX = 1000UL * 15UL;              // Run The Function X Seconds
  static uint32_t RunTheTimer_Wait = MILLIS;                   // Keep Track Of The Time
  if (MILLIS - RunTheTimer_Wait >= RunTheTimerForX) {          // Wait For Timeout
    RunTheTimer_Wait = MILLIS;                                 // Keep Track Of The Time
    if (runTheCounter) {                                       // Counter Is On - Stop The Counter
      runTheCounter = false;                                   // Stop The Counter
      countDownC.reset();                                      // Reset The Counter
      Serial.println(F("Counter Was Turned Off."));            // Serial Print
    }
    else runTheCounter = true;                                 // Counter Is Off - Start The Counter
  } // */
  
  // Wait 1 Second Between Readings
  delay(1000UL);                                               // Wait 1 Seconds
}


// End Of File.
