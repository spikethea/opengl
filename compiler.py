import os
import subprocess
from xml.etree.ElementInclude import include

file_name = "app"
include_dir = "dependencies/include"
lib_dir = "dependencies/lib"
lib = "-lglfw3 -lglew32s -lopengl32 -lgdi32"
preprocessor = "-DGLEW_STATIC"

def main():
    # path exists check
    isExist = os.path.exists(f"main.cpp")
    print(isExist)
    # compile
    subprocess.call(f"g++ {preprocessor} -c main.cpp -I {include_dir}")
    # link
    subprocess.call(f"g++ *.o -o {file_name} -L {lib_dir} {lib}")

if "__main__" == __name__:
    main()