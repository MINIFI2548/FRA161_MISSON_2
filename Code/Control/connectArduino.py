# import serial
# import time

# # connect with arduino
# bukhum =  serial.Serial(port='COM10',   baudrate=115200, timeout=.1)

# # send command & echo wiht arduino
# def send_command(mess):
#     print(mess)
#     bukhum.write(mess)
#     time.sleep(0.05)
#     echo = bukhum.read_all()
#     print(echo.decode("utf-8"))
