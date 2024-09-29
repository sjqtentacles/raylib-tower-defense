#!/bin/bash

# Find all .c and .h files in the current directory
files=$(find . -type f \( -name "*.c" -o -name "*.h" \))

# Create a temporary file to hold the output
temp_file=$(mktemp)

# Loop through each file and print its name followed by its contents
for file in $files
do
    echo "===== $file =====" >> "$temp_file"
    cat "$file" >> "$temp_file"
    echo "" >> "$temp_file"  # Add a blank line between files
done

# Copy the contents of the temporary file to the clipboard (macOS)
cat "$temp_file" | pbcopy

# For Linux, use either xclip or xsel:
# cat "$temp_file" | xclip -selection clipboard
# cat "$temp_file" | xsel --clipboard

# Remove the temporary file
rm "$temp_file"

echo "All .c and .h files' contents have been copied to your clipboard."
