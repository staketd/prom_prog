import sys

from PIL import Image
f = open("codegen.hpp", "w")
f.write("""#include <vector>
std::vector<std::vector<int>> map_image_values = {""")
map_imp = Image.open(sys.argv[1])
for col in range(3):
    f.write("\n{")
    for i in range(256):
        if i % 16 == 0:
            f.write("\n\t")
        f.write(str(map_imp.getpixel((i, col))[col]) + ", ")
    f.write("\n},")
f.write("\n};")
f.close()
