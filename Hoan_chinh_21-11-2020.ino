#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(12, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
//int value; 
//#define trigPin 8    // Chân Trig nối với chân 8
//#define echoPin 7    // Chân Echo nối với chân 7
//QueueHandle_t queue_1;
//struct Covid {
//  float ss2; // pir
//  float duration;
//  float distance;
//};
//void TaskCambien(void *pvParameter);
//void TaskHienthi(void *pvParameter);
void setup() {
 Serial.begin(9600);
  pinMode(2, INPUT);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) {  while(true){delay(0); }   }
  myDFPlayer.volume(30); 
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//  pinMode(9, OUTPUT);
//   queue_1 = xQueueCreate(5, sizeof(struct Covid));
//  if (queue_1 == NULL)
//  {
//  Serial.println("Queue can not be created");
//  }
//  xTaskCreate(TaskCambien, "Display_task", 128, NULL, 1, NULL);
//    xTaskCreate(TaskHienthi, "Moisture_task", 128, NULL, 2, NULL);
//  vTaskStartScheduler();
}
void loop() {
  myDFPlayer.play(1);
delay(4000); 

}


//void TaskCambien(void * pvParameters) {
//  struct  Covid a;
//  int xStatus;
//
//  for ( ; ; ) {
//  
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(100);
//  digitalWrite(trigPin, LOW);
//  a.duration = pulseIn(echoPin, HIGH);
//  a.distance = (a.duration*.0343)/2;
//  a.ss2 = digitalRead(2);
//    xStatus = xQueueSend(queue_1, &a, 1000 / portTICK_PERIOD_MS);
//    if (xStatus != pdPASS)
//    {
//      Serial.print("dont send");
//    }
//  }
//}
//void TaskHienthi(void * pvParameters) {
//  struct Covid b;
//  int xStatus;
//  for (;;)
//  {
//    xStatus = xQueueReceive(queue_1, &b, 1000 / portTICK_PERIOD_MS);
//    if (xStatus == pdPASS)
//    {
//       if (b.ss2 == HIGH){
//    myDFPlayer.play(1);
//    digitalWrite(13,LOW);
//delay(6000);
//   Serial.println(b.ss2); 
//  }
//  else {
//    Serial.println(b.ss2);
//  } 
//  Serial.print("Distance: ");
//  Serial.println(b.distance);
//  if(b.distance <= 100 )
//  {
//    digitalWrite(9,HIGH);
//    delay(200);
//    digitalWrite(9,LOW);
//    delay(200);
//    }
//    else if(b.distance > 100)
//    {
//          digitalWrite(9,LOW);
//      }
//}
//    delay(500);
//  }
//}
