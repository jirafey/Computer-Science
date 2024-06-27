#!/bin/bash
dir="/sys/module"

if [ $# -eq 0 ]; then # If no parameters provided
    >&2 echo "No parameters provided" # print to stderr
    exit 1
fi
# `-` = left-align
print_columns() { printf "%-20s %-2s %-s\n" "$1" "$2" "$3"; }

for module in "$dir"/*/; do
    module_name=$(basename "$module") # extract filename

    if [ -e "$module/refcnt" ]; then # if refcnt subdir exists
        for sub_dir in "$module/holders" "$module/parameters"; do

        if [ -d "$sub_dir" ]; then # check if directory exists
            num=$(find "$sub_dir" -mindepth 1 | wc -l) # find without itself, count lines
            name=$(find "$sub_dir" -mindepth 1 -exec basename {} \; | sort | paste -sd, -)
            # get all basenames without itself, sort, paste concatenate
	          # -sd, = serial delimiter `,`
            if [ "$num" -gt 0 ]; then # >0 -gt = greater than
                print_columns "$module_name" "$num" "$name"
            else # <=0
                print_columns "$module_name" "0" ""
            fi
        fi
    done
fi
