#include <Arduino_FreeRTOS.h>
#include <croutine.h>
#include <event_groups.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOSVariant.h>
#include <list.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <portmacro.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <StackMacros.h>
#include <task.h>
#include <timers.h>

void TaskBlink(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);          // turn the LED on (HIGH is the voltage level)
    vTaskDelay(1000 / portTICK_PERIOD_MS);    // wait for one second
    digitalWrite(LED_BUILTIN, LOW);           // turn the LED off by making the voltage LOW
    vTaskDelay(1000000 / portTICK_PERIOD_MS); // wait for one second
  }
}

void TaskAnalogRead(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
    vTaskDelay(1); // one tick delay (15ms) in between reads for stability
  }
}

void setup()
{
  xTaskCreate(TaskBlink, (const portCHAR *)"Blink", 128, NULL, 2, NULL);
  xTaskCreate(TaskAnalogRead, (const portCHAR *)"AnalogRead", 128, NULL, 1, NULL);
}

void loop()
{
  // Empty. Things are done in Tasks.
}
