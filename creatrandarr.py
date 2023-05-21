import numpy as np
import random
import sys



if __name__ == "__main__":

    #num = int(sys.argv[1])
    size = int(sys.argv[1])
    ran = int(sys.argv[2])
    file_name = sys.argv[3]

    #print('num = ', num)
    #print('size = ', size)
    #print('ran = ', ran)
    #print('file_name = ', file_name)
    

    with open(file_name, "w") as f:

        #for i in range(num):

        arr = [random.randint(1, ran) for i in range(size)]
        
        
        for j in range(size):
            f.write(str(arr[j]) + " ")
            #print(arr)

        f.write("\n")
    

