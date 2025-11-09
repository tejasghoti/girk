#!/bin/bash

FILE="addess.txt"

if [! -f "$FILE"];then
    touch "$FILE"
fi

while true
do
    echo "Select your choice: "
    echo "1. search"
    echo "2. add"
    echo "3. remove"
    echo "4. exit"
    read choice
    
    case $choice in
        1)
            echo "Enter record to search: "
            read search
            if  grep -i "$search" "$FILE" ; then
                :
            else
                echo "Record not found!!"
            fi
            ;;

        2)
            echo "Enter id: "
            read id
            echo "Enter name: "
            read name
            echo "Enter phone: "
            read phone
            if grep -i "$id" "$FILE" ; then
                echo "record already exists"
                :
            else 
                echo "$id;$name;$phone" >> "$FILE"
                echo "Record added successfully"
            fi
            ;;
        
        3)
            echo "Enter record to remove "
            read remove
            grep -i -v "$remove" "$FILE" > temp.txt
            mv temp.txt "$FILE"
            ;;

        4)
            echo "Exit Successful !"
            exit 0
            ;;
        
        *)
            echo "try again invalid choice"
            ;;
    esac
done
