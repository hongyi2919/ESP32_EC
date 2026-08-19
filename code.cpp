#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>

#define Ringa  25
#define Record 26
#define Upload 27
#define Do     32
#define Re     33
#define Mi     34
#define Fa     35
#define So     36
#define La     39
#define Si     23
using namespace std;

const char* ssid = "yourSSID";
const char* password = "yourPassword";
const char* apiKey = "yourAPIkey";

int interval = 200;
//int tone[1000];
vector<int>tones;
bool RecordisPressed = false;
bool SoisPressed = false;
bool isLongPressed = false;
unsigned long pressTime = 0, lastHoldTime = 0;
const unsigned long longPressTime = 1000;
const unsigned long holdTime = 500;
//const unsigned long debounceTime = 50;
bool RECORD = false;
int x = 0;

// 蜂鳴器播放函式
void alarmSnd() {
  int tonesize = tones.size();

  for (i = 0; i < tonesize; i++) {
    ledcWriteTone(0, tones[i]);    // 通道 0
    delay(interval);              // 固定長度
  }
  ledcWriteTone(0, 0);        // 播放結束後停音
}

// 上傳資料至 ThingSpeak
void sendData() { 
  int upload = 0;

  HTTPClient http;
  String urlStr = "http://api.thingspeak.com/update?api_key=";
  urlStr += apiKey;
  urlStr += "&field1=";
  urlStr += String(upload);

  http.begin(urlStr);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.printf("HTTP 回應碼: %d 回應本體: %s\n", httpCode, payload.c_str());
  } else {
    Serial.println("HTTP 請求出錯");
  }
  http.end();
}

// 初始化設定
void setup() {
  Serial.begin(115200);
  ledcSetup(0, 2000, 8);
  ledcAttachPin(Ringa, 0);// 通道 0 輸出聲音

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("IP 位址: ");
  Serial.println(WiFi.localIP());

  analogSetAttenuation(ADC_11db);
  analogSetWidth(8);

  pinMode(Ringa, OUTPUT);
  pinMode(Record, INPUT_PULLUP);
  pinMode(Upload, INPUT_PULLUP);
  pinMode(Do, INPUT_PULLUP);
  pinMode(Re, INPUT_PULLUP);
  pinMode(Mi, INPUT_PULLUP);
  pinMode(Fa, INPUT_PULLUP);
  pinMode(So, INPUT_PULLUP);
  pinMode(La, INPUT_PULLUP);
  pinMode(Si, INPUT_PULLUP);
}

// 按鍵偵測
void checkSwitch() {
  if (digitalRead(Record) == LOW && !RecordisPressed) {
    RecordisPressed = true;
    RECORD = if (RECORD) ? false : true;   // 按一次切換錄製狀態
  } else if (digitalRead(Record) == HIGH) {
    RecordisPressed = false;          // 放開按鍵，重置狀態
  }
}

bool FirstTouch[7] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
const int notePins[7] = {Do, Re, Mi, Fa, So, La, Si};
const int noteFreqs[7] = {262, 294, 330, 349, 392, 440, 494}; // Do~Si 頻率
void recordPins()
{
    // 迴圈檢查七個音階按鍵
  for (int i = 0; i < 7; i++)
  {
    if (digitalRead(notePins[i]) == LOW && FirstTouch[i] == HIGH) 
    {   // 按下某個音階鍵
      if (RECORD == 1) {                     // 如果在錄音模式
        tones.push_back(noteFreqs[i]);       // 存對應頻率
      }
    }
    // after touch return LOW,放開後就變 HIGH
    FirstTouch[i] = digitalRead(notePins[i]); 
  }
}
void loop() {
  checkSwitch(); // 檢查 Record 鍵
  recordPins();  // 紀錄music
}
