import sys
import serial
from intelhex import IntelHex
import re


    
args = sys.argv[1:]
def Init():
  hex_obj = IntelHex()                     # create empty object
  hex_obj.fromfile(args[0],format='hex')  # load from hex
  #Parse hex file to binary array
  bin_data = hex_obj.tobinarray()
  #print(bin_data)
  x = len(bin_data)
  print("#define APP_SIZE       "+str(x))



def Flash_Task():
  Port = serial.Serial(port = args[1],  baudrate=9600  , timeout = 5, 
                                           parity = serial.PARITY_NONE  , stopbits = serial.STOPBITS_ONE , 
                                           bytesize = serial.EIGHTBITS)
  f = open(args[0],'r')
  EntryPoint=re.findall(r':04000005(........)..',f.read())
  #print(to_bytes(EntryPoint[0])) 
  #bytes = str.encode(EntryPoint[0])
 
  num = int(EntryPoint[0],16)
  #bytes = bytearray(num)
  print(num)
  bytes=num.to_bytes(4, 'big')
  bytes=list(bytes)
  print(bytes)
  #Port.write(num)
  
  
  """
  for i in range(len(bin_data)):
    #bin_data[i].insert(0 , len(data))
    transfer_data = [bin_data[i]]
    Port.write(transfer_data)
    print(str(i)+"  "+str(bin_data[i]))
  """

if __name__=='__main__':
  Init()
  Flash_Task()