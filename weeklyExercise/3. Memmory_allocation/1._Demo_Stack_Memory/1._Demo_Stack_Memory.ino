/* Generate stack overflow */

//Use only core one for demo
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

//Task: Perform some mundane task
void testTask(void *parameter) {
  while(1) {
    int a = 1;
    int b[100];

    //Do something with array so it is not optimized out by the compiler
    for (int i = 0; i < 100; i++) {
      b[i] = a + 1;
    }
    Serial.println(b[0]);
  }
}
void setup() {

  //configure serial
  Serial.begin(115200);

  //Wait a momment to start (so we dont miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---------FreeRTOS Memory Demo-----");

  //Start the only other task
  xTaskCreatePinnedToCore(testTask,
                           "Test Task",
                           1024,
                           NULL,
                           1,
                           NULL,
                           app_cpu);

  //Delete "s3etup and loop" task
  vTaskDelete(NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}
