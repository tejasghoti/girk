#!/bin/bash

FILE="address2.txt"

# create file if not exists
if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

# show menu
show_menu() {
    echo "------------------------------"
    echo "        ADDRESS BOOK MENU     "
    echo "------------------------------"
    echo "1. Search Address Book"
    echo "2. Add Entry"
    echo "3. Remove Entry"
    echo "4. Edit Entry"
    echo "5. Display All Records"
    echo "6. Quit"
    echo "------------------------------"
}

# search
search_entry() {
    echo -n "Enter record to search: "
    read search
    if grep -i "$search" "$FILE"; then
        :
    else
        echo "Record not found!!"
    fi
}

# add entry
add_entry() {
    echo -n "Enter ID: "
    read id
    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone: "
    read phone
    echo "$id:$name:$phone" >> "$FILE"
    echo "Entry added successfully."
}

# remove entry
remove_entry() {
    echo -n "Enter record to remove: "
    read remove
    grep -i -v "$remove" "$FILE" > temp.txt
    mv temp.txt "$FILE"
    echo "Entry removed successfully."
}

# edit entry
edit_entry() {
    echo -n "Enter ID or Name to edit: "
    read edit
    line=$(grep -i "$edit" "$FILE")

    if [ -z "$line" ]; then
        echo "Record not found!"
        return
    fi

    echo "Old Record: $line"

    echo -n "Enter New ID: "
    read new_id
    echo -n "Enter New Name: "
    read new_name
    echo -n "Enter New Phone: "
    read new_phone

    # delete old record
    grep -i -v "$edit" "$FILE" > temp.txt

    # add updated record
    echo "$new_id:$new_name:$new_phone" >> temp.txt

    mv temp.txt "$FILE"

    echo "Record updated successfully."
}

# display all records
display_all() {
    echo "Displaying all records:"
    cat "$FILE"
}

while true; do
    show_menu
    echo -n "Enter your choice [1-6]: "
    read choice

    case $choice in
        1) search_entry ;;
        2) add_entry ;;
        3) remove_entry ;;
        4) edit_entry ;;
        5) display_all ;;
        6) echo "Exiting Address Book... Bye!"
           exit 0 ;;
        *) echo "Invalid choice! Try again." ;;
    esac
done
