#!/bin/bash
# ==========================================
#   Address Book Management System (1.3)
#   Fields: ID : Name : Phone : Email
# ==========================================

FILE="addressbook.txt"

# ---------- Ensure file exists ----------
if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

# ---------- Function: Display All Records ----------
display_records() {
    echo "----------------------------------------"
    echo "         Address Book Records"
    echo "----------------------------------------"
    if [ ! -s "$FILE" ]; then
        echo "No records found!"
    else
        printf "%-5s %-15s %-15s %-25s\n" "ID" "Name" "Phone" "Email"
        echo "----------------------------------------"
        awk -F':' '{printf "%-5s %-15s %-15s %-25s\n", $1, $2, $3, $4}' "$FILE"
    fi
    echo "----------------------------------------"
}

# ---------- Function: Search Record ----------
search_record() {
    echo "Search by:"
    echo "1. ID"
    echo "2. Name"
    echo "3. Phone"
    echo "4. Email"
    read -p "Enter your choice: " choice

    case $choice in
        1)
            read -p "Enter ID: " key
            result=$(awk -F':' -v key="$key" '$1 == key {print}' "$FILE")
            ;;
        2)
            read -p "Enter Name: " key
            result=$(awk -F':' -v key="$key" 'tolower($2) == tolower(key) {print}' "$FILE")
            ;;
        3)
            read -p "Enter Phone: " key
            result=$(awk -F':' -v key="$key" '$3 == key {print}' "$FILE")
            ;;
        4)
            read -p "Enter Email: " key
            result=$(awk -F':' -v key="$key" 'tolower($4) == tolower(key) {print}' "$FILE")
            ;;
        *)
            echo "Invalid choice!"
            return
            ;;
    esac

    echo "----------------------------------------"
    if [ -n "$result" ]; then
        printf "%-5s %-15s %-15s %-25s\n" "ID" "Name" "Phone" "Email"
        echo "----------------------------------------"
        echo "$result" | awk -F':' '{printf "%-5s %-15s %-15s %-25s\n", $1, $2, $3, $4}'
    else
        echo "Record not found!"
    fi
    echo "----------------------------------------"
}

# ---------- Function: Add Record ----------
add_record() {
    read -p "Enter ID: " id
    if grep -q "^$id:" "$FILE"; then
        echo "Record with ID $id already exists!"
        return
    fi

    read -p "Enter Name: " name
    read -p "Enter Phone: " phone
    read -p "Enter Email: " email

    echo "$id:$name:$phone:$email" >> "$FILE"
    echo "Record added successfully!"
}

# ---------- Function: Remove Record ----------
remove_record() {
    read -p "Enter ID or Name to remove: " key
    if grep -iq "$key" "$FILE"; then
        grep -iv "$key" "$FILE" > temp.txt && mv temp.txt "$FILE"
        echo "Record removed successfully!"
    else
        echo "Record not found!"
    fi
}

# ---------- Function: Edit Record ----------
edit_record() {
    read -p "Enter ID of record to edit: " id

    # Check if record exists
    old_record=$(grep "^$id:" "$FILE")
    if [ -z "$old_record" ]; then
        echo "No record found with ID $id!"
        return
    fi

    echo "Old Record: $old_record"

    # Get new values
    read -p "Enter new Name: " name
    read -p "Enter new Phone: " phone
    read -p "Enter new Email: " email

    new_record="$id:$name:$phone:$email"

    # Create a temp file to rebuild the address book
    > temp.txt  # clear/create temp file

    # Read file line by line
    while IFS= read -r line; do
        if [[ "$line" == "$old_record" ]]; then
            echo "$new_record" >> temp.txt
        else
            echo "$line" >> temp.txt
        fi
    done < "$FILE"

    mv temp.txt "$FILE"
    echo "Record updated successfully!"
}

# ---------- Function: Menu ----------
menu() {
    while true; do
        echo "=============================="
        echo "     ADDRESS BOOK MENU"
        echo "=============================="
        echo "1. Display All Records"
        echo "2. Search Record"
        echo "3. Add Record"
        echo "4. Remove Record"
        echo "5. Edit Record"
        echo "6. Quit"
        echo "=============================="
        read -p "Enter your choice: " choice

        case $choice in
            1) display_records ;;
            2) search_record ;;
            3) add_record ;;
            4) remove_record ;;
            5) edit_record ;;
            6) echo "Exiting Address Book..."; exit 0 ;;
            *) echo "Invalid choice! Please try again." ;;
        esac
    done
}

# ---------- Main Program ----------
menu






/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/1$ ./shellscript1.3.sh
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 1
----------------------------------------
         Address Book Records
----------------------------------------
ID    Name            Phone           Email                    
----------------------------------------
2     jbzjcb          fdbj            bfdhafb                  
3     dmdd,           sjcjbd          sjbf                     
----------------------------------------
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 2
Search by:
1. ID
2. Name
3. Phone
4. Email
Enter your choice: 1
Enter ID: 2
----------------------------------------
ID    Name            Phone           Email                    
----------------------------------------
2     jbzjcb          fdbj            bfdhafb                  
----------------------------------------
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 3
Enter ID: 1
Enter Name: jsdkjfhsk
Enter Phone: 94439875908
Enter Email: ffjksdhjh
Record added successfully!
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 4
Enter ID or Name to remove: 2
Record removed successfully!
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 1
----------------------------------------
         Address Book Records
----------------------------------------
ID    Name            Phone           Email                    
----------------------------------------
3     dmdd,           sjcjbd          sjbf                     
1     jsdkjfhsk       94439875908     ffjksdhjh                
----------------------------------------
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 5
Enter ID of record to edit: 1
Old Record: 1:jsdkjfhsk:94439875908:ffjksdhjh
Enter new Name: jsajfhjk
Enter new Phone: 40458  
Enter new Email: dfjkbsvd
Record updated successfully!
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 1
----------------------------------------
         Address Book Records
----------------------------------------
ID    Name            Phone           Email                    
----------------------------------------
3     dmdd,           sjcjbd          sjbf                     
1     jsajfhjk        40458           dfjkbsvd                 
----------------------------------------
==============================
     ADDRESS BOOK MENU
==============================
1. Display All Records
2. Search Record
3. Add Record
4. Remove Record
5. Edit Record
6. Quit
==============================
Enter your choice: 6
Exiting Address Book...
*/
