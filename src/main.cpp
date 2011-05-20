#include "WProgram.h" //include the Arduino library
#include <stdio.h>
#include "avr_ros/ros.h" //main avrRos library
#include "avr_ros/String.h" //std_msg/String library
#include "avr_ros/UInt16.h"
#include "avr_ros/Int32.h"
#include "avr_ros/Float32.h"


//sDefine global message objects to use in
//the callback functions and throughout the program
ros::Publisher string_pub;
std_msgs::String string_call_msg;
std_msgs::String string_response_msg;

ros::Publisher    uint16_pub;
std_msgs::UInt16  uint16_call_msg;
std_msgs::UInt16  uint16_response_msg;

ros::Publisher   int32_pub;
std_msgs::Int32  int32_call_msg;
std_msgs::Int32  int32_response_msg;


ros::Publisher     float32_pub;
std_msgs::Float32  float32_call_msg;
std_msgs::Float32  float32_response_msg;



void toggle()
{ //toggle an led to debug the program
    static char t=0;
    if (!t ) {
        digitalWrite(13, HIGH);   // set the LED on
        t = 1;
    } else {
        digitalWrite(13, LOW);    // set the LED off
        t = 0;
    }
}

void string_response(const ros::Msg *msg){
        toggle();

        //make sure that if you are manipulating the raw string,
        //there is enough space in it
        //to handle all of the data
        sprintf(string_response_msg.data.getRawString(),
                "%s", string_call_msg.data.getRawString());
        node.publish(string_pub, &string_response_msg);
}


void uint16_response(const ros::Msg *msg){
        toggle();
        std_msgs::UInt16* call_msg = (std_msgs::UInt16*) msg;
        uint16_response_msg.data = call_msg->data;
        node.publish(uint16_pub, &uint16_response_msg);
}

void int32_response(const ros::Msg *msg){
        toggle();
        std_msgs::Int32* call_msg = (std_msgs::Int32*) msg;
        int32_response_msg.data = call_msg->data;
        node.publish(int32_pub, &int32_response_msg);
}


void float32_response(const ros::Msg *msg){
        toggle();
        std_msgs::Float32* call_msg = (std_msgs::Float32*) msg;
        float32_response_msg.data = call_msg->data;
        node.publish(float32_pub, &float32_response_msg);
}



// Since we are hooking into a standard
// arduino sketch, we must define our program in
// terms of the arduino setup and loop functions.

void setup()
{
    Serial.begin(57600);

    pinMode(13, OUTPUT); //set up the LED
    
    string_pub = node.advertise("string_response");
    node.subscribe("string_call",string_response, &string_call_msg);

    string_call_msg.data.setMaxLength(30);
    string_response_msg.data.setMaxLength(30);
    
    uint16_pub = node.advertise("uint16_response");
    node.subscribe("uin16_call",uint16_response, &uint16_call_msg);

    int32_pub = node.advertise("int32_response");
    node.subscribe("int32_call",int32_response, &int32_call_msg);
    
    float32_pub = node.advertise("float32_response");
    node.subscribe("float32_call",float32_response, &float32_call_msg);

}

void loop()
{
	node.spin();

    /* Do other work */
    delay(10);
}
