Readme for Arduino2PD
Version 0.1
Feb 2th, 2007




To use the Arduino2PD patch, you need to first program the Arduino. 


Programming the Arduino

1. You'll need Thomas Ouellet Fredericks' "Simple Message System" Library for the Arduino. Arduino2PD is basically a practical adaptation of his excellent library and examples. 
http://ciam.dyndns.org/~vitamin/danslchamp/mrtof/SimpleMessageSystem.zip

2. Put the S.M.S. library in "Arduino 05/lib/targets/libraries/"

3. Program the Arduino with the "Arduino_for_PD_input" code included in the Arduino2PD zip archive. 



Using the PD patch

To start reading from the Arduino, click the "start" the toggle at above left.

You may have to change your serial port to suit the port in use.

Patch adapted from Thomas Ouellet Fredericks' "Simple Message Sytem" Examples

Serial writes are possible but not implemented here; see TOF's  S.M.S. code. 

Runs flawlessly on a Macbook and OS 10.4.8; your mileage may vary. 


 