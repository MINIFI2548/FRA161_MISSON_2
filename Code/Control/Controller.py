#import library 
import time
import serial 

# connect with arduino
# bukhum =  serial.Serial(port='COM6',   baudrate=115200, timeout=.1)
time.sleep(1)

# send command & echo wiht arduino
def send_command(mess):
    print(mess)
    # bukhum.write(mess)
    # time.sleep(0.05)
    # data = bukhum.readline()
    # return   data
    pass

def get_info() : # \x00 in byte
    send_command(bytes('\x00', 'utf-8'))

def split_command(command) : 
        # find function name & parameter from command 
        if (not ":" in command) : command += ":"
        function_name, parameter = command.strip().split(':')
        function_name = "".join([c for c in function_name if c.isalpha()]).lower()
        # extrace parameter 
        parameter = [int(p) for p in parameter.split() if (not p.isspace())]
        return (function_name, parameter)

def main():
    while True:
        # input command from terminal
        command = input("Input command > ")

        # split command 
        func, parameter = split_command(command)

        # Show function name and each paraneter 
        print(f'function = {func} all parameter {parameter}')
        for i,p in enumerate(parameter) :
            print(f'parameter {i+1} : {p} : {type(p)}')
        
        """ match command :
            case 'getinfo' :
                get_info()
            case _ :
                print("NOPE") """
        # echo   = send_command(command)
        # print(echo)

main()