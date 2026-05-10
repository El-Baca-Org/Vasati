#!/bin/bash

# Apply the merge diff manually to test
sed -i 's/char buffer\[5\];/\/\/char buffer[5];/' src/src-class/Zaman.cpp
