#!/bin/bash

FILE="phonebbok.txt"

if [! -f "$FILE"];then
    touch "$FILE"
fi

while true
do
    echo "Select your choice: "
    echo "1. add"
    echo "2. search"
    echo "3. sort"
    echo "4. delete"
    echo "5. exit"
    read choice
    
    case $choice in
        1)
            #add record
            echo "Enter first name: "
            read fname
            echo "Enter last name: "
            read lname
            echo "Enter phone number: "
            read phone
            echo -e "$fname\t$lname\t$phone" >> "$FILE"
            echo "record added successfully"
            ;;

        2)
            #search record
            echo "Enter record to search: "
            read search
            grep -i "$search" "$FILE"
            ;;
        
        3) 
            #sort by last name
            echo "Sorting by last name"
            sort -k2 "$FILE" > temp.txt
            mv temp.txt "$FILE"
            echo "Sorted successfully"
            ;;

        4)
            echo "Enter record to remove "
            read remove
            grep -i -v "$remove" "$FILE" > temp.txt
            mv temp.txt "$FILE"
            ;;

        5)
            echo "Exit Successful !"
            exit 0
            ;;
        
        *)
            echo "try again invalid choice"
            ;;
    esac
done
