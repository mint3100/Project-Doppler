/*
Project doppler
* 2024.07.08 By Mint
*/

// 트리거 핀과 에코 핀은 장치에 따라 수동으로 변경해주셔야 합니다.
const int trigPin = 9;
const int echoPin = 10;
const float speedOfSound = 343.0; // 343 m/s
const float frequency = 40000; // 40 kHz 속도로 신호 발송

long duration;
float distance;
float previousDistance = 0;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // cm -> m 단위 변환

  unsigned long currentTime = millis();
  if (previousTime != 0) {
    float timeDiff = (currentTime - previousTime) / 1000.0; // s 단위변환
    float distanceDiff = distance - previousDistance;
    float relativeSpeed = distanceDiff / timeDiff; // m/s 단위변환
    
    float deltaFrequency = (relativeSpeed * 2 * frequency) / speedOfSound;
    
    Serial.print(relativeSpeed);
    Serial.print(",");
    Serial.println(deltaFrequency);
  }

  previousDistance = distance;
  previousTime = currentTime;

  delay(100);
}
