#!/bin/bash

# Check if clang is available
if command -v clang &> /dev/null; then
 compiler="clang++"
else
 # Use g++ if clang is not found
 compiler="g++"
fi

# Find all .cpp files in the current directory ONLY
for file in *.cpp; do
 # Extract the number from the filename using a regular expression
 if [[ "$file" =~ ^([0-9]+).*\. ]]; then 
  number="${BASH_REMATCH[1]}"
 else
  echo "Skipping file: $file (Could not extract number)"
  continue
 fi

 # Compile the file with -Wall and std=c++20
 echo "Compiling $file to ${number}task..."
 "$compiler" -Wall -std=c++20 -o "${number}task" "$file"

 # Check if compilation was successful
 if [ $? -ne 0 ]; then
  echo "Error: Compilation of $file failed."
  exit 1
 fi
done

echo "All files compiled successfully!"
