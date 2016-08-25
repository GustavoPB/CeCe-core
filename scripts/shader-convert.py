#!/usr/bin/env python

# ######################################################################### #
# Georgiev Lab (c) 2015-2016                                                #
# ######################################################################### #
# Department of Cybernetics                                                 #
# Faculty of Applied Sciences                                               #
# University of West Bohemia in Pilsen                                      #
# ######################################################################### #
#                                                                           #
# This file is part of CeCe.                                                #
#                                                                           #
# CeCe is free software: you can redistribute it and/or modify              #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation, either version 3 of the License, or         #
# (at your option) any later version.                                       #
#                                                                           #
# CeCe is distributed in the hope that it will be useful,                   #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with CeCe.  If not, see <http://www.gnu.org/licenses/>.             #
#                                                                           #
# ######################################################################### #

import sys
import hashlib
import datetime

# ######################################################################### #

def convert(fOut, symbol, code):
    """
    Convert code into C/C++ array sequence.
    """
    valueCounter = 0;

    fOut.write("#include \"cece/core/StaticArray.hpp\"\n")
    fOut.write("\n");
    fOut.write("// " + datetime.datetime.now().isoformat() + "\n");
    fOut.write("// #" + str(hashlib.md5(code).hexdigest()) + "\n");
    fOut.write("static const cece::StaticArray<unsigned char, " + str(len(code) + 1) + "> " + symbol + " = {{\n  ")

    for c in code:
        fOut.write("0x{:02x}, ".format(ord(c)))

        valueCounter = valueCounter + 1;
        if valueCounter >= 8:
            valueCounter = 0
            fOut.write("\n  ")

    fOut.write("0x00\n}};\n")


# ######################################################################### #

def splitShaders(filename):
    """
    Split source with multiple shaders into separate ones.
    """
    id = -1
    shaders = ["", ""]

    with open(filename) as f:
        lines = f.readlines()

        for line in lines:
            if line.startswith("[VertexShader]"):
                id = 0
            elif line.startswith("[FragmentShader]"):
                id = 1
            elif line.startswith("["):
                id = -1
            elif id != -1:
                shaders[id] = shaders[id] + line

    return shaders

# ######################################################################### #

if __name__ == "__main__":
    # Parse parameters
    if len(sys.argv) < 4:
        raise Exception("not enough arguments: <shader-file> <out-dir> <name>")

    (_, inFilename, outDir, name) = sys.argv

    sources = splitShaders(inFilename);

    outFilename = outDir + "/vs." + name + ".hpp"
    with open(outFilename, "w") as f:
        print("Vertex shader: " + outFilename)
        convert(f, "g_vertexShader", sources[0])

    outFilename = outDir + "/fs." + name + ".hpp"
    with open(outFilename, "w") as f:
        print("Fragment shader: " + outFilename)
        convert(f, "g_fragmentShader", sources[1])

# ######################################################################### #
