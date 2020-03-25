/*
 * avr_chatter.cpp
 *
 * Created: 1/17/2020 7:02:19 PM
 *  Author: abdelrhman
 */ 

#include "ros.h"
#include "ros_lib/std_msgs/String.h"
#include "ros_lib/std_msgs/UInt32.h"

// Include C headers (ie, non C++ headers) in this block
extern "C"
{
	#define F_CPU 12000000UL
	#include <util/delay.h>
}

// Needed for AVR to use virtual functions
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

ros::NodeHandle nh;

std_msgs::String str_msg;
std_msgs::UInt32 uint_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Publisher chatter1("chatter1", &uint_msg);


const char hello[]  = "hello ros";

int main()
{
  uint32_t lasttime = 0UL;
  // Initialize ROS
  nh.initNode();
  nh.advertise(chatter);
  nh.advertise(chatter1);


  while(1)
  {
    // Send the message every second
    if(avr_time_now() - lasttime > 1000)
    {
	    str_msg.data = hello;
		uint_msg.data = avr_time_now();
	    chatter.publish(&str_msg);
		chatter1.publish(&uint_msg);
	    lasttime = avr_time_now();
    }
    nh.spinOnce();

  }

  return 0;
}
