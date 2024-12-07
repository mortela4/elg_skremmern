/**
 * @file main.cpp
 * 
 * @brief Demonstrate WiFi mesh. 
 */


#include <Arduino.h>

#include <errno.h>
#if defined(USE_WDT) && (USE_WDT == 1)
#include <esp_task_wdt.h>
#endif

#include "esp_pm.h"

// Local headers:
#include "config.h"
#include "lamp.h"
//#include "painlessMesh.h"


#define   MESH_PREFIX     "ELG_"
#define   MESH_PASSWORD   "skremmern"
#define   MESH_PORT       5555
#define   MAX_NODES       6                 // Maximum 6 nodes in the mesh network.
#define   LAMP_CMD        "LIGHTS_ON"


//Scheduler     userScheduler; // to control your personal task
//painlessMesh  mesh;
WarnLamp      warnLamp;

// Prototype
// void receivedCallback( uint32_t from, String &msg );

// size_t edgeRouterID = 0;    // Send BROADCAST!


// Send message(=CMD) to ALL nodes if  
// Task lampControlTask(10000, TASK_FOREVER, []() 
// {
//     if (0 == digitalRead(TRIG_PIN) && !warnLamp.IsOn())
//     {
//         const String lampCmd = LAMP_CMD;

//         warnLamp.TurnOn();
//         //delay(1000);

//         if (edgeRouterID == 0)                  // If we don't know the edge-router's ID yet (or it doesn't send its ID at all)
//             mesh.sendBroadcast(lampCmd);
//         else
//             mesh.sendSingle(edgeRouterID, lampCmd);

//         Serial.println("LAMP_CMD sent ...");
//     }

//     delay(100);
// });


void setup() 
{
  Serial.begin(115200);
  pinMode(TRIG_PIN, INPUT_PULLUP);

  warnLamp.Init();
  
//   //mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // Log 'everything'. Set before init() so that you can see startup messages
//   mesh.setDebugMsgTypes( ERROR );

//   mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, MAX_NODES );   
//   mesh.onReceive(&receivedCallback);

  // Add the task to the your scheduler
//   userScheduler.addTask(lampControlTask);
//   lampControlTask.enable();

  /* Configure the wake up source(s): */
  gpio_wakeup_enable((gpio_num_t)TRIG_PIN, GPIO_INTR_HIGH_LEVEL);      // TODO: what level does pin use???
  esp_sleep_enable_gpio_wakeup();
}


void loop() 
{
  // it will run the user scheduler as well
  //mesh.update();
  (void)esp_light_sleep_start();
  
  // Woken UP - so play sound:
  // TODO: play sound here!
  
  // Then, turn lamp ON:
  warnLamp.TurnOn();
  delay(150000UL);   // Wait 2min. 30sec.
  warnLamp.TurnOff();
}


// void receivedCallback( uint32_t from, String &msg ) 
// {
//     Serial.printf("MESH: Received from NODE(MAC): %u - msg=%s\n", from, msg.c_str());

//     if (msg.equals(LAMP_CMD))
//     {
//         Serial.println("Turning lamp ON!");
//         warnLamp.TurnOn();
//     }
// }

