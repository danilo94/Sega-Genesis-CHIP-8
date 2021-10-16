def generate_hex(content):
    begin = "unsigned char game["+str(len(content))+"] = {"
    middle = ""
    end = " };"
    for byte in content:
        middle = middle + str(hex(byte))+","
    
    final = begin+middle+end
    print(final)

def open_file(file_path):
    try:
        f = open(file_path,"rb")
        content = f.read()
        generate_hex(content)
        f.close()
    except Exception as e:
        print(e)
        f.close()



def main():
    file_path = input('Insert CHIP-8 FilePath: ')
    print("Opening file: ",file_path)
    open_file(file_path)
    
 

if __name__ == "__main__":
    main()