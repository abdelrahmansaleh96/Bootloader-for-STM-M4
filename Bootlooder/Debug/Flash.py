from intelhex import IntelHex
hex_obj = IntelHex()                     # create empty object
hex_obj.fromfile('Bootlooder.hex',format='hex')  # load from hex
#Parse hex file to binary array
bin_data = hex_obj.tobinarray()
print(bin_data)
x = len(bin_data)
print("#define APP_SIZE       "+str(x))

