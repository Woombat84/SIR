# SIR
Sewer fault detection P4 project\
A projct for detecting faults within the sewer.


## Hardware: 
Intel RealSense d435i\
USB 3.0

## Software needed: 
Intel RealSence SDK\
A cpp compiler as visual studio


## Work done:
What works so far is a skeleton setup before any prossecing.\
Depth, IR and RGB are displayed, the IMU data is printed to the console.


## What needs to be done:
Deteced faults.\
Make complimentray filter for IMU data.


## Know errors:
If you get and error regarding a path do the following: 
1. Find Project1.vcxproj
2. Open with notepad or any plain text editor.
3. Locate this:
\
![alt text](https://github.com/Woombat84/SIR/blob/master/Picture/predelete.png "note: their maybe a more path's with in this structur")
4. Delete everhting between </ImportGroup> EXCEPT the two top lines.
5. Save.
⋅⋅⋅The end result should look like this:

![alt text](https://github.com/Woombat84/SIR/blob/master/Picture/deleted.png "End result")
6. Add property sheets in visual studio for openCV and intel.realsense both can be located in the RealSense SDK libaery.  
