
#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;
std_msgs::Float32 encoder_msg;
ros::Publisher pub("encoder", &encoder_msg);


int encoder_pin = 2;            
int CANAL_A = 2;
int CANAL_B = 3;

void counter() {
  if (digitalRead(CANAL_A) == HIGH) {
    if (digitalRead(CANAL_B) == LOW) {
      pulses++;
    } else {
      pulses--;
    }
  } else {
    if (digitalRead(CANAL_B) == LOW) {
      pulses--;
    } else {
      pulses++;
    }
  }
}


oid setup(){
  nh.initNode();
  broadcaster.init(nh);

  Serial.begin(9600); 
  pinMode(encoder_pin, INPUT); 
  pinMode(CANAL_A, INPUT);
  pinMode(CANAL_B, INPUT);

  attachInterrupt(0, counter, RISING); 
}


void loop(){
  encoder_msg.data = counter();
  pub.publish( &encoder_msg );
  nh.spinOnce();
  delay(500);
}
