[![Arduino CI](https://github.com/XbergCode/MillisCounter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/XbergCode/MillisCounter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/XbergCode/MillisCounter/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/XbergCode/MillisCounter/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/XbergCode/MillisCounter/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/github/license/XbergCode/MillisCounter)](https://github.com/XbergCode/MillisCounter/blob/master/LICENSE)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/XbergCode/MillisCounter)](https://github.com/XbergCode/MillisCounter/releases)
![code size:](https://img.shields.io/github/languages/code-size/XbergCode/MillisCounter)


# MillisCounter

Arduino library to count up and down time using the millis() function.  
Max runtime is "limited" to 136 to 179.years. See Note* in "MillisCounter.h" for more info. Lines 9 to 15.


## Description

The MillisCounter library contains functions that counts time using the millis() function.  
MillisCounter will keep "accurate" count time even if the code hangs, like with delay(), for() or while() functions.  
MillisCounter will keep on counting even if the millis() rolls over after 49 days.

> [!NOTE]  
> 
> getCountUp() shows: years, months, days, hours, minutes, seconds, milliseconds, total days and total seconds.  
> getCountUp() ⬅️ *only shows milliseconds the first 999.ms of the run time.* ❗  
>
> getCountDown() shows: years, days, hours, minutes, seconds, total days and total seconds.  
> getCountDown() ⬅️ *does not have months.* ❗  

Based on 365-day calendar year.

Keep in mind that the oscillator is not 100.% accurate, and is sensitive to temperature and supply voltage fluctuation.  
A crystal oscillator is about 0.005% accurate.  
A ceramic oscillator is about 0.5% accurate.  


## Interface

The following functions are implemented:

* void reset(); ⬅️ Reset's the counter.

* bool isRunning(); ⬅️ Return's the counter status.

* char* getCountUp(); ⬅️ Outputs C string. Max output string: "100.Y, 10.M, 10.D, 10.h, 10.m, 10.sec"

* char* getCountDown(const uint32_t _COUNTSECONDS); ⬅️ Outputs C string. Max output string: "100.Y, 100.D, 10.hour, 10.min, 10.sec"

* char* getCountDown(const uint8_t _SECONDS, const uint8_t _MINUTES, const uint8_t _HOURS, const uint16_t _DAYS, const uint8_t _YEARS); ⬅️ Send count down time in: seconds, minutes, hours, days & years 

* const uint8_t  getYears();

* const uint8_t  getMonths(); ⬅️ Only for getCountUp() ❕

* const uint16_t  getDays();

* const uint8_t  getHours();

* const uint8_t  getMinutes();

* const uint8_t  getSeconds();

* const uint16_t getTotalDays();

* const uint32_t getTotalSeconds();


## Outputs

### Outputs from: getCountUp()

0.milliseconds  
1.seconds  
2.seconds  
...  
1.minute, 1.seconds  
...  
2.minutes, 2.seconds  
...  
1.hours, 1.minutes, 1.seconds  
...  
1.Day, 1.hours, 1.min, 1.sec  
...  
2.Days, 1.hours, 1.min, 1.sec  
...  
1.M, 1.D, 1.hours, 1.min, 1.sec  
...  
1.Y, 1.M, 1.D, 1.h, 1.m, 1.sec  

-------------------------------------------------------------------------------------

### Outputs from: getCountDown()

100.Y, 50.D, 10.hour, 10.min, 10.sec ⬅️ From 100 to 136.years  
...  
1.Y, 50.D, 1.hours, 1.min, 1.sec ⬅️ From 1 to 99.years  
...  
2.days, 2.hours, 1.min, 1.sec  
...  
2.days, 1.hour, 1.min, 1.sec  
...  
1.day, 2.hours, 1.min, 1.sec  
...  
1.day, 1.hour, 1.min, 1.sec  
...  
2.hours, 1.minutes, 1.seconds  
...  
1.hour, 1.minutes, 1.seconds  
...  
2.minutes, 2.seconds  
...  
1.minute, 1.seconds  
...  
2.seconds  
1.second  
Done.

-------------------------------------------------------------------------------------

### Outputs from: getCountUp() & getCountDown() - Custom string.

<br>

> *You do something that suits your task.*

<br>

#### Custom getCountUp() example.

0.sec  
1.sec's  
2.sec's  
3.sec's  
...  
1.min, 1.sec  
...  
2.min's, 1.sec  
...  
1.h, 1.min, 1.sec  
...  
1.D, 1.h, 1.min, 1.sec  
...  
2.D's, 1.h, 1.min, 1.sec  
...  
1.M, 1.D, 1.h, 1.min, 1.sec  
...  
1.Y, 1.M, 1.D, 1.h, 1.m, 1.sec

-------------------------------------------------------------------------------------

#### Custom getCountDown() example.

100.Y, 50.D, 1.h, 1.min, 1.sec  
...  
2.d's, 2.h's, 1.min, 1.sec  
...  
2.d's, 1.h, 1.min, 1.sec  
...  
1.d, 2.h's, 1.min, 1.sec  
...  
1.d, 1.h, 1.min, 1.sec  
...  
2.h's, 1.min, 1.sec  
...  
1.h, 1.min, 1.sec  
...  
2.min's, 1.sec  
...  
1.min, 1.sec  
...  
3.sec's  
2.sec's  
1.sec  
Done.

-------------------------------------------------------------------------------------


## Operation

See examples.


## Performance

Most time is spend at converting total seconds to seconds, minutes, hours, days, total days and years.
