from connectArduino import*

""" method for manage command """
# change list of parameter to bytes
def parameter_to_bytes(parameter):
    ans = bytes()
    for p in parameter :
        ans += int(p).to_bytes(2, 'big')
    return ans

# check number or parameter : ture when parameter < size 
def check_number_parameter(parameter, size) : 
    if (len(parameter) < size) : 
        print(f"Your parameters is not fully")
    return (len(parameter) < size)

""" list of command """

def hoget_info() :                # \x00 in byte
    command = int(0).to_bytes(1, 'big')
    send_command(command)

def home() :                    # \x01 in byte
    command = int(1).to_bytes(1, 'big')
    send_command(command)
    # print("Set home")

def go_to(parameter) :          # \x02 in byte
    if check_number_parameter(parameter, 1) : 
        return 0
    command = int(2).to_bytes(1, 'big')
    # command += parameter_to_bytes(parameter[0:1])
    command += int(((parameter[0])) * 3200 / 8).to_bytes(2, 'big')
    send_command(command)
    # print(f"go to {parameter[0]}")

def repeat_go_to(parameter) :   # \x03 in byte
    # parameter[0] = time 
    # parameter[1] = positon
    if check_number_parameter(parameter, 2) : 
        return 0
    command = int(3).to_bytes(1, 'big')
    command += parameter_to_bytes([int(((parameter[0])) * 3200 / 8), parameter[1]])
    send_command(command)
    # print(f"go to {parameter[0]} {parameter[1]} times")

def motor_off() :               # \x04 in byte
    command = int(4).to_bytes(1, 'big')
    send_command(command)

def motor_on() :                # \x05 in byte
    command = int(5).to_bytes(1, 'big')
    send_command(command)

def pen() : 
    command = int(6).to_bytes(1,'big')
    send_command(command)