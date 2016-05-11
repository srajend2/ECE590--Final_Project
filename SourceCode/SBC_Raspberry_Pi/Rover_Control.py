import time, serial, os, sys, tty, termios

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE,BAUD)

#termios is used for POSIX input/output control
fd = sys.stdin.fileno()
old_settings = termios.tcgetattr(fd)
while True:
	tty.setraw(sys.stdin.fileno()) #raw input
	ch = sys.stdin.read(1)         #store the read input character
	termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

        # UNFOLD THE ROVER
	if "u" in ch:
                previous_press = 'u'
                servo_values = "1/155/2/0000/3/0000/4/055/5/150"
                ser.write(servo_values)
		print servo_values

        # FOLD THE ROVER
	if "f" in ch:
                previous_press = 'f'
                servo_values = "1/060/2/0000/3/0000/4/150/5/060"
                ser.write(servo_values)
		print servo_values

        # MOVE IN FORWARD DIRECTION
        if "8" in ch:
                previous_press = '8'
                servo_values = "1/155/2/1124/3/0100/4/055/5/150"
                ser.write(servo_values)
		print servo_values

        # MOVE IN REVERSE DIRECTION
        if "5" in ch:
                previous_press = '5'
                servo_values = "1/155/2/0100/3/1124/4/055/5/150"
                ser.write(servo_values)
		print servo_values

        # TURN LEFT                
        if "4" in ch:
                previous_press = '4'
                servo_values = "1/155/2/1124/3/1124/4/055/5/150"
                ser.write(servo_values)
		print servo_values
        
        # TURN RIGHT
        if "6" in ch:
                previous_press = '6'
                servo_values = "1/155/2/0100/3/0100/4/055/5/150"
                ser.write(servo_values)
		print servo_values

        # STOP THE ROVER        
        if "7" in ch:
                previous_press = '7'
                servo_values = "1/155/2/0000/3/0000/4/055/5/150"
                ser.write(servo_values)
		print servo_values

        # STOP THE PROGRAM        
	if ch in "c":
                print "That's all folks!!"
		break
        
