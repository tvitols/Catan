
import subprocess
import sys

if __name__ == '__main__':

#    with open("/home/tvitols/CatanDev/Catan/testin.txt", "r") as input_file:

 #       with open("/home/tvitols/CatanDev/Catan/testout.txt", "w") as output_file:
            
    with subprocess.Popen("/home/tvitols/CatanDev/Catan/build/Catan", stdin=subprocess.PIPE, stdout=subprocess.PIPE) as p:
        #print(p.stdout.read1().decode('utf-8'))
        out,err = p.communicate(input ="2\n".encode("utf-8"))
        print(out)
        out,err = p.communicate(input = "4\n".encode("utf-8"))
        print(out)
    # output, error = catan_process.communicate()
