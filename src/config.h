#ifndef CONFIG_H
#define CONFIG_H


//#include <tuple>


/* HiRO-HW or just prototyping on devkit (ESP32-S3-Mini-1R8): */
#define USE_DEVKIT_PROTO    1
#define USE_WDT             0
#define USE_SLEEP_MODE      1

/* System-wide config: */
#if defined(USE_WDT) && (USE_WDT == 1)
#define WDT_TIMEOUT         30      // 30 seconds WDT
#endif
#define MAINLOOP_PERIOD     1000UL     // Or, ((WDT_TIMEOUT/1000)/3) as this is in [ms].
#define IDLE_PERIOD_MAX     10000UL     // 10sec of idling before SLEEP invoked.
#define STOP_PERIOD_MAX     5000UL


/* Logging: */
#include <esp_log.h>

#define APP_LOG_LEVEL       ESP_LOG_INFO    // NOTE: set to 'ESP_LOG_VERBOSE' to output EVERYTHING!! (from PlatformIO/Arduino core etc.)


#ifdef USE_DEVKIT_PROTO    
    // Interrupt pin(s):
    #define TRIG_PIN        40                      // NOTE: must function both as IRQ and wakeup-src!!
    #define IRQ_PIN_MASK    (1 << ((TRIG_PIN) - 32))
    #define INT_GPIO_REG    GPIO_IN1_REG            // NOTE: use 'GPIO_IN_REG' if GPIOs are in range 0-31, else 'GPIO_IN1_REG' (for GPIOs 32-63).
#else
    #define TRIG_PIN        2
#endif


#endif  // CONFIG_H
