#!/bin/bash

# 1. Check if file exists
check_file() {
    echo -n "Enter filename: "
    read fname
    if [ -f "$fname" ]; then
        echo "File '$fname' exists."
    else
        echo "File '$fname' does not exist."
    fi
}

# 2. Read (display) contents of a file
read_file() {
    echo -n "Enter filename to read: "
    read fname
    if [ -f "$fname" ]; then
        echo "Contents of $fname:"
        cat "$fname"
    else
        echo "File not found!"
    fi
}

# 3. Delete a file
delete_file() {
    echo -n "Enter filename to delete: "
    read fname
    if [ -f "$fname" ]; then
        rm "$fname"
        echo "File '$fname' deleted successfully."
    else
        echo "File not found!"
    fi
}

# 4. Display list of files
list_files() {
    echo "Files in current directory:"
    ls
}

# ---------- MAIN PROGRAM ----------

while true
do
    echo "-------------------------------"
    echo "     FILE MANAGEMENT MENU      "
    echo "-------------------------------"
    echo "1. Test if File Exists"
    echo "2. Read a File"
    echo "3. Delete a File"
    echo "4. Display List of Files"
    echo "5. Quit"
    echo "-------------------------------"
    echo -n "Enter your choice [1-5]: "
    read choice

    case $choice in
        1) check_file ;;
        2) read_file ;;
        3) delete_file ;;
        4) list_files ;;
        5) echo "Exiting File Manager... Bye!"
           exit 0 ;;
        *) echo "Invalid choice! Try again." ;;
    esac
done
