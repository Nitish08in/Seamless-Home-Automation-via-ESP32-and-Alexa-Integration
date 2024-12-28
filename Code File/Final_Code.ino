#define BLYNK_TEMPLATE_ID "TMPL3nua0ELL-"    //Change Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Seamless Home Automation via ESP32 and Alexa"   //Change Blynk Template Name
#define BLYNK_AUTH_TOKEN "uhKHXojln4xlNFu_JN1gJ81DB1t7R6b1"   //Change Blynk AUTH Token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// Wi-Fi credentials
char ssid[] = "WIFI NAME";  //Change WIFI Name
char pass[] = "WIFI PASS";  //Change WIFI Password

// SinricPro credentials
#define APP_KEY "e29fda54-83bf-4d65-8a76-29873e353a07"   //Change Sinric pro app key
#define APP_SECRET "476a392f-b7bd-4b3d-97a1-6eb656848822-469fbc02-0d3a-42cf-9279-c237b1eb5ffd"  //Change Sinric pro app secret

// Device IDs from SinricPro
#define device_ID_1 "67386981ca1dbba89b642d69" // Bulb 1
#define device_ID_2 "673869a0de70d3c324bd1460" // Bulb 2
#define device_ID_3 "673869d9de70d3c324bd14cc" // Fan

// Pin definitions
#define RelayPin1 26   // GPIO5 for Bulb 1 (Alexa controlled)
#define RelayPin2 25    // GPIO4 for Bulb 2 (Alexa controlled)
#define RelayPin3 33   // GPIO14 for Bulb 3 (Blynk controlled)
#define RelayPin4 32   // GPIO12 for Fan (Alexa controlled)
#define DHTPIN 14      // GPIO33 for DHT sensor data pin
#define DHTTYPE DHT11  // DHT11 or DHT22
#define SMOKE_SENSOR_PIN 34  // GPIO34 for MQ-2 smoke sensor

// Blynk virtual pins
#define BLYNK_VPIN_TEMP V5     // Temperature virtual pin
#define BLYNK_VPIN_HUMIDITY V6 // Humidity virtual pin
#define BLYNK_VPIN_SMOKE V7    // Smoke level virtual pin
#define BLYNK_PIN_BULB3 V3
#define BLYNK_PIN_FAN   V4

// OLED display settings
#define SCREEN_WIDTH 128  // OLED display width in pixels
#define SCREEN_HEIGHT 64  // OLED display height in pixels
#define OLED_RESET -1     // Reset pin, set to -1 if sharing Arduino reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

// Blynk timer
BlynkTimer timer;

// SinricPro callback for Alexa-controlled devices
bool onPowerState(const String &deviceId, bool &state) {
  if (deviceId == device_ID_1) {
    digitalWrite(RelayPin1, !state);
  } else if (deviceId == device_ID_2) {
    digitalWrite(RelayPin2, !state);
  } else if (deviceId == device_ID_3) {
    digitalWrite(RelayPin4, !state);
  }
  return true;
}

// Setup SinricPro for Alexa
void setupSinricPro() {
  SinricProSwitch &mySwitch1 = SinricPro[device_ID_1];
  SinricProSwitch &mySwitch2 = SinricPro[device_ID_2];
  SinricProSwitch &mySwitch3 = SinricPro[device_ID_3];

  mySwitch1.onPowerState(onPowerState);
  mySwitch2.onPowerState(onPowerState);
  mySwitch3.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

// Blynk write handlers
BLYNK_WRITE(BLYNK_PIN_BULB3) {
  int state = param.asInt();
  digitalWrite(RelayPin3, state);
}

BLYNK_WRITE(BLYNK_PIN_FAN) {
  int state = param.asInt();
  digitalWrite(RelayPin4, state);
}

// Sensor update function
void updateSensors() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read smoke level
  int smokeLevel = analogRead(SMOKE_SENSOR_PIN);  // Declare smokeLevel here

  // Check if readings are valid
  if (!isnan(temperature) && !isnan(humidity)) {
    Blynk.virtualWrite(BLYNK_VPIN_TEMP, temperature);
    Blynk.virtualWrite(BLYNK_VPIN_HUMIDITY, humidity);

    // Display on OLED
    display.clearDisplay();
    
    // Set normal text size for labels
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE);
    
    // Temperature label
    display.setCursor(0, 0);
    display.print("Temp: ");
    
    // Humidity label
    display.setCursor(0, 20);
    display.print("Hum: ");
    
    // Smoke label
    display.setCursor(0, 40);
    display.print("Smoke: ");

    // Set larger text size for sensor readings
    display.setTextSize(2);  

    // Reduce the gap between label and value
    display.setCursor(40, 0); // Reduced horizontal position to bring closer to the label
    display.print(temperature);
    display.print("C");  // Adding space between value and unit

    display.setCursor(40, 20); // Reduced horizontal position
    display.print(humidity);
    display.print("%");  // Adding space between value and unit

    display.setCursor(40, 40); // Reduced horizontal position
    display.print(smokeLevel);

    display.display();
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  // Debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Smoke Level: ");
  Serial.println(smokeLevel);  // Print smokeLevel here
}

void setup() {
  Serial.begin(115200);

  // Initialize relays
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  // Initialize smoke sensor
  pinMode(SMOKE_SENSOR_PIN, INPUT);

  // Initialize DHT sensor
  dht.begin();

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);  // Pause for 2 seconds
  display.clearDisplay();

  // Setup Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup SinricPro
  setupSinricPro();

  // Set timer to update sensors every 2 seconds
  timer.setInterval(2000L, updateSensors);

  display.setCursor(0, 0);
  display.setTextSize(1);  // Default font size for initial message
  display.print("System Ready");
  display.display();
}

void loop() {
  Blynk.run();
  SinricPro.handle();
  timer.run();
}