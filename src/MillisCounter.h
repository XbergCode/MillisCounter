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
// VERSION: 1.0.0
// PURPOSE: Arduino library to count up and down time using the millis() function.
//     URL: https://github.com/XbergCode/MillisCounter

// History.
// Version: -  Date:       -  Changes:
// 1.0.0    -  10/08/2023  -  Initial.


#pragma once
#define MILLISCOUNTER_VERSION    (F("1.0.0\n"))   // Version

class MillisCounter {
  public:                                         // Public
    
    MillisCounter();                              // Set the class call name

    // Reset & Status
    static void reset(void);                      // Reset The Counter
    static bool isRunning(void);                  // Status Of The Counter
    
    // Count up.
    static char* getCountUp(void);                           // Call the count up function
    // Count down.
    static char* getCountDown(const uint32_t _COUNTSECONDS); // Call the count down function
    static char* getCountDown(const uint8_t _SECONDS, const uint8_t _MINUTES, const uint8_t _HOURS = 0, const uint16_t _DAYS = 0U, const uint8_t _YEARS = 0);
    
    // Get the time.
    static const uint8_t   getYears();            // Get - Years
    static const uint8_t   getMonths();           // Get - Months
    static const uint16_t  getDays();             // Get - Days
    static const uint8_t   getHours();            // Get - Hours
    static const uint8_t   getMinutes();          // Get - Minutes
    static const uint8_t   getSeconds();          // Get - Seconds
    static const uint16_t  getTotalDays();        // Get - Total Days
    static const uint32_t  getTotalSeconds();     // Get - Total Seconds
      
  private:                                        // Private
  	
    // C string.
    static char _c_buffer[];                      // Buffer for the time string
    static const uint8_t _c_bufferSize;           // Buffer size

    // Time.
    static uint8_t  _years;                       // Time - Years      (0-136)
    static uint8_t  _months;                      // Time - Months     (0-11)
    static uint16_t _days;                        // Time - Days       (0-364)
    static uint8_t  _hours;                       // Time - Hours      (0-23)
    static uint8_t  _minutes;                     // Time - Minutes    (0-59)
    static uint8_t  _seconds;                     // Time - Seconds    (0-59)
    static uint16_t _totaldays;                   // Time - Total Days (0-49710)
    
    // Bools to change day and month.
    static bool _b_newDay;                        // If its okay to change the day
    static bool _b_shortMonth;                    // Short or Long month

    // Start mark, start time, total time, rollover time & status.
    static bool _setTheTime;                      // Get the start millis time once per run
    static uint32_t _startMillis;                 // Save the start millis time
    static uint32_t _totalSeconds;                // Save the total seconds
    static uint32_t _rolloverSeconds;             // Save the total seconds if millis rollsover's
    static uint32_t _lastMILLIS;                  // Monitor Millis Rollover
    static bool _counterIsRunning;                // If The Counter Is Running

    // Count down
    static int64_t roundTo(const int64_t IN);     // Round Milliseconds
};

// End Of File.
