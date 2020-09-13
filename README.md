# CAN_Receive
Simple arduino program which receives data sent from one computer to and arduino connected to another arduino using a CAN bus which is connected to the computer running this program. 

The data being received consists of:
- The status of three buttons (1 or 0)
- Air Temp(0-255)
- Current Gear (F,R,N)
- ASCII Character
- Current driver(0-7)
- Check value (0x7A)

Depending on the state of the buttons (pressed or not) the corresponding lights on the arduino connected to the computer running this program. The rest of the values will be printed to serial 
