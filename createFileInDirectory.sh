#!/bin/bash

directory_path=$1

if [ ! -d "$directory_path" ]; then
    echo "Directory does not exist. Creating directory: $directory_path"
    mkdir -p "$directory_path"
fi

directory_name=$(basename "$directory_path")

file_path="$directory_path/$directory_name _file.txt"
touch "$file_path"

echo "File created: $file_path"

