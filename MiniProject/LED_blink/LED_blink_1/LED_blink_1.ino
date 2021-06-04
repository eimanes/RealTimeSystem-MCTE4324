#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = LED_BUILTIN;
int led_1 = 32;

void setup() {
  // put your setup code here, to run once:
pinMode(led_pin, OUTPUT);
pinMode(led_1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_pin, HIGH);
  digitalWrite(led_1, LOW);
  delay(1000);

  digitalWrite(led_pin, LOW);
  digitalWrite(led_1,HIGH);
  delay(1000);

}
