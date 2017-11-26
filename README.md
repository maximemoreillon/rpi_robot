# rpi_robot

This is a .c program for a robot controlled by a raspberry pi.
The robot has two pairs of motorized wheels and steers by creating a speed differential between the left and right pairs.
An ultrasonic sensor is mounted on a servo, located at the front of the robot, which allows it to scan for obstacles.
The raspberry is equipped with a wifi adapter and creates an access point.
It responds to UDP packets received on this network and controls the motors accordignly.
Conversely, it broadcasts the scan results of the ultrasonic sensor on the network.
This was made to allow the robot to be controlled using a Nintendo DS running a custom software.

The code for the UDP communication was made by Silver Moon (m00n.silv3r@gmail.com).
