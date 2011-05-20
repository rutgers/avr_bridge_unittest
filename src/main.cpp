#include "WProgram.h" //include the Arduino library
#include <stdio.h>
#include "avr_ros/ros.h" //main avrRos library
#include "avr_ros/String.h" //std_msg/String library

//sDefine global message objects to use in
//the callback functions and throughout the program
ros::Publisher resp;
std_msgs::String call_msg;
std_msgs::String response_msg;

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

void response(const ros::Msg *msg){
        toggle();

        //make sure that if you are manipulating the raw string,
        //there is enough space in it
        //to handle all of the data
        sprintf(response_msg.data.getRawString(),
                "You sent : %s", call_msg.data.getRawString());
        node.publish(resp, &response_msg);
}


// Since we are hooking into a standard
// arduino sketch, we must define our program in
// terms of the arduino setup and loop functions.

void setup()
{
    Serial.begin(57600);

    pinMode(13, OUTPUT); //set up the LED
    resp = node.advertise("response");
    node.subscribe("call",response, &call_msg);

    call_msg.data.setMaxLength(30);
    response_msg.data.setMaxLength(60);
}

void loop()
{
	node.spin();

    /* Do other work */
    delay(10);
}
