#import library 
import time
import serial
from command import *
from connectArduino import*

# connect with arduino
time.sleep(1)

def split_command(command) : 
        # find function name & parameter from command 
        if (not ":" in command) : command += ":"
        function_name, parameter = command.strip().split(':')
        function_name = "".join([c for c in function_name if c.isalpha()]).lower()
        # extrace parameter 
        parameter = [float(p) for p in parameter.split() if (not p.isspace())]
        return (function_name, parameter)

def main():
    while True:
      if(bukhum.in_waiting > 0 ) :
            echo = bukhum.read_all()
            print(echo.decode("utf-8"))
      else:
            # input command from terminal
            command = input("Input command > ")

      # split command 
      func, parameter = split_command(command)

        # Show function name and each paraneter 
      #   print(f'function = {func} all parameter {parameter}')
      #   for i,p in enumerate(parameter) :
      #       print(f'parameter {i+1} : {p} : {type(p)}')
        
      match func : 
            case 'getinfo' : 
                  get_info()
            case 'home' : 
                  home()
            case 'goto' : 
                  go_to(parameter)
            case 'repeatgoto': 
                  repeat_go_to(parameter)
            case 'motoroff':
                  motor_off()
            case 'motoron' :
                  motor_on()
            case 'pen' :
                  pen()
            case _ :
                  print('Not have this command in list')
            # print(parameter_to_bytes(parameter))


main()