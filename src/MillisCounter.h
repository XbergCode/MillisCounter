/*  The MillisCounter library contains functions that counts time using the millis() function.
    MillisCounter will keep "accurate" count time even if the code hangs, like with delay(), for() or while() functions.
    MillisCounter will keep on counting even if the millis() rolls over after 49 days.
    Count up shows: Years, Months, Days, Hours, Minutes, Seconds, Total days and Total seconds.
    Count down shows: Years, Days, Hours, Minutes, Seconds, Total days and Total seconds.
    
    //---------------------------------------------------------------------------------------------------------------------                      
    * Note:
      Total seconds is uint32_t and has a max runtime of 136 years.
      Total days is uint16_t = 65.535 days. So max runtime for it is about 179 years.
      To get longer runtime you will need to change almost all uint32_t to uint64_t.
      At least: _totalSeconds, _rolloverSeconds, _totaldays to uint64_t & _years to uint32_t,
      also change a lot of UL to ULL. Do you realy need 584.942.417.355 years runtime.

      In a perfect world this code should be able to run for 136 to 179 years without problem.
    //---------------------------------------------------------------------------------------------------------------------
    
    Keep in mind that the oscillator is not 100.% accurate, and is sensitive to temperature and supply voltage fluctuation.
    A crystal oscillator is about 0.005% accurate. = 86400*0,005=432/100 = ±4.32.sec per day
    A ceramic oscillator is about 0.5% accurate.   = 86400*0,5=43200/100=432/60 = ±7.min & 2.sec per day.
*/
//    FILE: MillisCounter.h
//  AUTHOR: XbergCode
// VERSION: 1.1.0
// PURPOSE: Arduino library to count up and down time using the millis() function.
//     URL: https://github.com/XbergCode/MillisCounter

// History.
// Version: -  Date:       -  Changes:
// 1.1.0    -  18/12/2024  -  Changed from static to non static, added void countUp & countDown, added getCountDownIsDone.
// 1.0.0    -  10/08/2023  -  Initial.


#pragma once

// Include The Arduino Header
#ifdef ARDUINO                                                  // If We Are Using Arduino
#if !defined(ARDUINO_H)                                         // If The Library Has Not Been Included
#include <Arduino.h>                                            // Arduino Library
#endif
#endif

#define MILLISCOUNTER_VERSION    (F("1.1.0\n"))                 // Version

class MillisCounter {
  public:                                                       // Public
    
    // Object Constructor.
    MillisCounter();                                            // Set the object call name

    // Reset & Status.
    void reset(void);                                           // Reset the counter
    bool isRunning(void);                                       // Status of the counter
    
    // Count up.
    void countUp(void);                                         // Call the count up function
    char* getCountUp(void);                                     // Get - Count up (returns: string)
    
    // Count down.
    void countDown(const uint32_t _COUNTSECONDS);               // Call the count down function
    void countDown(const uint8_t _SECONDS, const uint8_t _MINUTES, const uint8_t _HOURS = 0, const uint16_t _DAYS = 0U, const uint8_t _YEARS = 0);
    char* getCountDown(const uint32_t _COUNTSECONDS);           // Get - Count down (returns: string)
    char* getCountDown(const uint8_t _SECONDS, const uint8_t _MINUTES, const uint8_t _HOURS = 0, const uint16_t _DAYS = 0U, const uint8_t _YEARS = 0);
    bool getCountDownIsDone(void) { return _countDownIsDone; }  // Get - Count down is done

    // Get the time.
    const uint8_t   getYears() { return _years; }               // Get - Years
    const uint8_t   getMonths() { return _months; }             // Get - Months
    const uint16_t  getDays() { return _days; }                 // Get - Days
    const uint8_t   getHours() { return _hours; }               // Get - Hours
    const uint8_t   getMinutes() { return _minutes; }           // Get - Minutes
    const uint8_t   getSeconds() { return _seconds; }           // Get - Seconds
    const uint16_t  getTotalDays() { return _totaldays; }       // Get - Total Days
    const uint32_t  getTotalSeconds() {                         // Get - Total Seconds
      return (_totaldays * 86400UL) + (_hours * 3600UL) + (_minutes * 60UL) + _seconds;
    }
      
  private:                                                      // Private
  	
    // C string.
    static char _c_buffer[];                                    // Buffer for the time string
    static const uint8_t _c_bufferSize = 38;                    // Buffer size

    // Time.
    uint8_t  _years     = 0;                                    // Time - Years      (0-136)
    uint8_t  _months    = 0;                                    // Time - Months     (0-11)
    uint16_t _days      = 0U;                                   // Time - Days       (0-364)
    uint8_t  _hours     = 0;                                    // Time - Hours      (0-23)
    uint8_t  _minutes   = 0;                                    // Time - Minutes    (0-59)
    uint8_t  _seconds   = 0;                                    // Time - Seconds    (0-59)
    uint16_t _totaldays = 0U;                                   // Time - Total Days (0-49710)
    
    // Bools to change day and month.
    bool _b_newDay = false;                                     // If its okay to change the day
    bool _b_shortMonth = true;                                  // Short or Long month

    // Start mark, start time, total time, rollover time & status.
    bool _setTheTime = true;                                    // Get the start millis time once per run
    uint32_t _startMillis = 0UL;                                // Save the start millis time
    uint32_t _totalSeconds = 0UL;                               // Save the total seconds
    uint32_t _rolloverSeconds = 0UL;                            // Save the total seconds if millis rollsover's
    uint32_t _lastMILLIS = 0UL;                                 // Monitor Millis Rollover
    bool _counterIsRunning = false;                             // If The Counter Is Running
    bool _countDownIsDone = false;                              // Flag If Count Down Is Done

    // Count down roundTo.
    int64_t roundTo(const int64_t IN);                          // Round Milliseconds
};


// End Of File.
