//    FILE: MillisCounter.cpp
//  AUTHOR: XbergCode
// VERSION: 1.1.0
// PURPOSE: Arduino library to count up and down time using the millis() function.
//     URL: https://github.com/XbergCode/MillisCounter

// Headers
#include "MillisCounter.h"

//------------------------------------- Private ------------------------------------------//

//const uint8_t MillisCounter::_c_bufferSize = 38;    // Set the buffer size
char MillisCounter::_c_buffer[_c_bufferSize];       // Buffer for the time string

//----------------------------------------------------------------------------------------//


// Object Constructor
MillisCounter::MillisCounter() {}                   // Object Constructor

// Reset The Counter
void MillisCounter::reset(void) {
  // Reset The Counter
  _counterIsRunning = false;       // The Counter Is Not Running
  _setTheTime       = true;        // Ready To Get The Start Millis Time Again
  _totalSeconds     = 0UL;         // Reset The Total Seconds
  _rolloverSeconds  = 0UL;         // Reset The Rollover Seconds
  _years            = 0;           // Reset The Years
  _months           = 0;           // Reset The Months In Year
  _days             = 0U;          // Reset The Days In Month
  _hours            = 0;           // Reset Hours
  _minutes          = 0;           // Reset Minutes
  _seconds          = 0;           // Reset Seconds
  _totaldays        = 0U;          // Reset Total Days
  _b_newDay         = false;       // Reset The If its okay to change the day bool
  _b_shortMonth     = true;        // Reset The Short or Long month bool
  _countDownIsDone  = false;       // Flag If Count Down Is Done
}

// Counter Running Status
bool MillisCounter::isRunning(void) {
  return _counterIsRunning;              // Return The Counter Running Status
}

// Count Up
void MillisCounter::countUp(void) {                 // Count Up
  // Count Up
  const uint32_t _MILLIS = millis();                       // Get The Millis Once Per Run

  // At the beginning.
  if (_setTheTime) {                                       // Get The Start Millis Time And Reset
    _setTheTime = false;                                   // Run This Function Once Per Run
    _counterIsRunning = true;                              // The Counter Is Running
    _startMillis = _MILLIS;                                // Get The Start Millis
  }

  // Monitor the millis rollover.
  if (_startMillis > _MILLIS) {                            // If Millis Rollover's
    _startMillis = _MILLIS;                                // Get The Start Time - Again
    if (_totalSeconds > 0) _totalSeconds += 1UL;           // Add 1 Second To The Total Time
    _rolloverSeconds = _totalSeconds;                      // Save The Total Seconds
  }

  // Add to the total seconds.
  _totalSeconds = (_MILLIS - _startMillis) / 1000UL;       // Calculate The Time In Total Seconds
  _totalSeconds += _rolloverSeconds;                       // Add The Rollover Seconds

  // Convert total seconds to seconds, minutes, hours and total days.
  _seconds   = _totalSeconds  % 60UL;                      // Calculate The Time In Seconds
  _minutes   = (_totalSeconds / 60UL)   % 60UL;            // Calculate The Time In Minutes
  _hours     = (_totalSeconds / 3600UL) % 24UL;            // Calculate The Time In Hours
  _totaldays = _totalSeconds  / 86400UL;                   // Calculate The Time In Total Days

  // Count days, months and years.

  // Get ready for a new day. (From 13 to 23 hours) Gives Arduino lot of opportunities to change the day.
  if (_hours >= 13 && _hours <= 23 && _b_newDay == false) _b_newDay = true;  // Set the state - Start running

  // One day is up. Add to the day count. (From 0 to 12 hours) Gives Arduino lot of opportunities to change the day.
  if (_hours >= 0 && _hours <= 12 && _b_newDay == true) {  // Days
    _days = _days + 1;                                     // Add to days
    _b_newDay = false;                                     // Set the state - Stop running
  }

  // One year is up. Reset months & days, add to years count.
  if (_months >= 11 && _days >= 30) {                      // Years
    _b_shortMonth = true;                                  // Next month is short
    _days = 0;                                             // Reset days
    _months = 0;                                           // Reset months
    _years = _years + 1;                                   // Add to years count
  }

  // One short month is up. Reset days and add to months count.
  if (_days >= 30 && _b_shortMonth == true) {              // Months - Short
    _b_shortMonth = false;                                 // Next month is long
    _days = 0;                                             // Reset days
    _months = _months + 1;                                 // Add to months count
  }

  // One long month is up. Reset days and add to months count.
  if (_days >= 31 && _b_shortMonth == false) {             // Months - Long
    _b_shortMonth = true;                                  // Next month is short
    _days = 0;                                             // Reset days
    _months = _months + 1;                                 // Add to months count
  }
}

// Max Output String: "100.Y, 10.M, 10.D, 10.h, 10.m, 10.sec" = 37.Characters
// Max Runtime: 136.years, 70.days, 6.hours, 28.min, 15.sec (49710.days)
char* MillisCounter::getCountUp(void) {
  countUp();                                               // Call The countUp

  // Make the time string
  if (_years == 0U) {                                      // Run Time Is Less Than One Year
    if (_seconds == 0U && _minutes == 0U && _hours == 0U && _days == 0U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%lu.milliseconds"), millis() - _startMillis);
    else if (_minutes == 0U && _hours == 0U && _days == 0U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%u.seconds"), _seconds);
    else if (_minutes == 1U && _hours == 0U && _days == 0U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%u.minute, %u.seconds"), _minutes, _seconds);
    else if (_minutes >= 2U && _hours == 0U && _days == 0U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%u.minutes, %u.seconds"), _minutes, _seconds);
    else if (_hours >= 1U && _days == 0U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%u.hours, %u.minutes, %u.seconds"), _hours, _minutes, _seconds);
    else if (_days == 1U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%u.Day, %u.hours, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
    else if (_days >= 2U && _months == 0U)
      sprintf_P(_c_buffer, PSTR("%u.Days, %u.hours, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
    else if (_months >= 1U)
      sprintf_P(_c_buffer, PSTR("%u.M, %u.D, %u.hours, %u.min, %u.sec"), _months, _days, _hours, _minutes, _seconds);
  } else                                                   // Run Time Is More Than One Year
    sprintf_P(_c_buffer, PSTR("%u.Y, %u.M, %u.D, %u.h, %u.m, %u.sec"), _years, _months, _days, _hours, _minutes, _seconds);

  // Return the time string
  return _c_buffer;                                        // Return The Time String
}


// Count Down
// Send:
// _COUNTSECONDS < Total Seconds To Count Down To
void MillisCounter::countDown(const uint32_t _COUNTSECONDS) {
  // Variables 
  const uint32_t _MILLIS = millis();                                  // Get The Millis Once Per Run
  // Count For Millis
  // uint32_t = 4,294,967,295.ms              = 49.days
  // uint64_t = 18,446,744,073,709,551,615.ms = 213,503,982,334.days
  const uint64_t _COUNTFORMILLIS = _COUNTSECONDS * 1000ULL;           // Calculate The Count For X Millis
  // Monitor Millis Rollover
  if (_lastMILLIS > _MILLIS) _setTheTime = true;                      // Millis Did Rollover
  
  // At The Beginning
  if (_setTheTime) {                                                  // Get The Start Millis Time
    _setTheTime = false;                                              // Get The Start Millis Time Once
    _counterIsRunning = true;                                         // If The Counter Is Running
    _startMillis = _MILLIS;                                           // Get The Start Millis Time
    if (_lastMILLIS > _MILLIS) _rolloverSeconds = _totalSeconds;      // Set The Rollover Seconds
    else {                                                            // Reset - Millis Rollover Monitor
      _rolloverSeconds = 0UL;                                         // Reset
      _totalSeconds = 0UL;                                            // Reset
    }
  }
  _lastMILLIS = _MILLIS;                                              // Get The Newest Millis Time
  
  // Calculate The Seconds That Are Left
  const uint32_t _SECONDSLEFT = (roundTo((_COUNTFORMILLIS - (_MILLIS - _startMillis))) / 1000UL) - _rolloverSeconds;
  _totalSeconds++;                                                    // Add To The _totalSeconds
  
  // Time Is Up
  if (_SECONDSLEFT == 0UL || _SECONDSLEFT > _COUNTFORMILLIS) {        // Time Is Up
    //reset();                                                          // Reset
    _countDownIsDone = true;                                          // Flag If Count Down Is Done
  }
  
  // Convert Total Seconds To: Seconds, Minutes, Hours, Days And Years
  _seconds   = _SECONDSLEFT  % 60UL;                                  // Calculate The Seconds
  _minutes   = (_SECONDSLEFT / 60UL)    % 60UL;                       // Calculate The Minutes
  _hours     = (_SECONDSLEFT / 3600UL)  % 24UL;                       // Calculate The Hours
  _totaldays = _SECONDSLEFT  / 86400UL;                               // Calculate The Total Days
  _days      = (_SECONDSLEFT / 86400UL) % 365UL;                      // Calculate The Days
  _years     = _SECONDSLEFT  / 31536000UL;                            // Calculate The Years

  // Count Down Is Done - Set The Time
  if (_countDownIsDone) {                                             // Count Down Is Done - Set The Time
    _seconds   = 0;                                                   // Set The Seconds
    _minutes   = 0;                                                   // Set The Minutes
    _hours     = 0;                                                   // Set The Hours
    _totaldays = 0;                                                   // Set The Total Days
    _days      = 0U;                                                  // Set The Days
    _years     = 0;                                                   // Set The Years
  }
}

// Send With: Seconds, Minutes, Hours, Days & Years
void MillisCounter::countDown(const uint8_t _SECONDS, const uint8_t _MINUTES, const uint8_t _HOURS, const uint16_t _DAYS, const uint8_t _YEARS) {
  countDown((_YEARS*31536000UL) + (_DAYS*86400UL) + (_HOURS*3600UL) + (_MINUTES*60UL) + _SECONDS);
}

// Max Output String: "100.Y, 100.D, 10.hour, 10.min, 10.sec" = 37.Characters
// Max Runtime: 136.years, 70.days, 6.hours, 28.min, 15.sec (49710.days)
char* MillisCounter::getCountDown(const uint32_t _COUNTSECONDS) {
  // Count Down
  const char _LASTSTRING[] = "Done.";                                 // The Last Time String
  countDown(_COUNTSECONDS);                                           // Call The countDown
  
  // Count Down Is Done
  if (_countDownIsDone) {                                             // Count Down Is Done
    strcpy(_c_buffer, _LASTSTRING);                                   // Make The Last String
    return _c_buffer;                                                 // Return The Last String
  }

  // Make The Time String
  if (_years == 0U) {                                                 // Less Than One Year
    if (_days == 0U && _hours == 0U && _minutes == 0U && _seconds <= 1U)
      sprintf_P(_c_buffer, PSTR("%u.second"), _seconds);
    else if (_days == 0U && _hours == 0U && _minutes == 0U && _seconds > 1U)
      sprintf_P(_c_buffer, PSTR("%u.seconds"), _seconds);
    else if (_days == 0U && _hours == 0U && _minutes == 1U)
      sprintf_P(_c_buffer, PSTR("%u.minute, %u.seconds"), _minutes, _seconds);
    else if (_days == 0U && _hours == 0U && _minutes > 1U)
      sprintf_P(_c_buffer, PSTR("%u.minutes, %u.seconds"), _minutes, _seconds);
    else if (_days == 0U && _hours == 1U)
      sprintf_P(_c_buffer, PSTR("%u.hour, %u.minutes, %u.seconds"), _hours, _minutes, _seconds);
    else if (_days == 0U && _hours > 1U)
      sprintf_P(_c_buffer, PSTR("%u.hours, %u.minutes, %u.seconds"), _hours, _minutes, _seconds);
    else if (_days == 1U && _hours >= 0U && _hours <= 1)
      sprintf_P(_c_buffer, PSTR("%u.day, %u.hour, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
    else if (_days == 1U && _hours > 1U)
      sprintf_P(_c_buffer, PSTR("%u.day, %u.hours, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
    else if (_days > 1U && _hours >= 0U && _hours <= 1)
      sprintf_P(_c_buffer, PSTR("%u.days, %u.hour, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
    else if (_days > 1U && _hours > 1U)
      sprintf_P(_c_buffer, PSTR("%u.days, %u.hours, %u.min, %u.sec"), _days, _hours, _minutes, _seconds);
  }
  else if (_years >= 1U && _years < 100U)                             // From One Year To 99 Years
    sprintf_P(_c_buffer, PSTR("%u.Y, %u.D, %u.hours, %u.min, %u.sec"), _years, _days, _hours, _minutes, _seconds);
  else                                                                // More Than 100 Years
    sprintf_P(_c_buffer, PSTR("%u.Y, %u.D, %u.hour, %u.min, %u.sec"), _years, _days, _hours, _minutes, _seconds);
  
  // Return The Time String
  return _c_buffer;                                                   // Return The Time String
}

// Send With: Seconds, Minutes, Hours, Days & Years
char* MillisCounter::getCountDown(const uint8_t _SECONDS, const uint8_t _MINUTES, const uint8_t _HOURS, const uint16_t _DAYS, const uint8_t _YEARS) {
  return getCountDown((_YEARS*31536000UL) + (_DAYS*86400UL) + (_HOURS*3600UL) + (_MINUTES*60UL) + _SECONDS);
}

//------------------------------------- Private ------------------------------------------//

// Round Milliseconds
int64_t MillisCounter::roundTo(const int64_t IN) {
  // Round To Even Integer - Made For Milliseconds Calculator.
  if (IN <= 0LL) return 0;              // Return 0
  const uint32_t _MOD = IN % 1000UL;    // Modulo The Value 
  const int32_t  _DIF = _MOD - 1000UL;  // Get The Difference
  const uint32_t _ABS = abs(_DIF);      // Get The Absolute Value Of The Difference
  // Round Up
  if (_MOD >= 500UL) return IN + _ABS;  // Return The New Value
  // Round Down
  else return IN - _MOD;                // Return The New Value
}


// End Of File.
