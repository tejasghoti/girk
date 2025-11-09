#!/bin/bash
# ==========================================
#   Address Book Management System
# ==========================================

FILE="address.txt"

# Create file if it does not exist
if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

while true
do
    echo "=============================="
    echo " Address Book Management "
    echo "=============================="
    echo "1. Search Address Book"
    echo "2. Add Address Book Entry"
    echo "3. Remove Address Book Entry"
    echo "4. Quit"
    echo "=============================="
    read -p "Enter your choice: " choice

    case $choice in
        1)
            # ---------- SEARCH ----------
            echo "Search by:"
            echo "1. ID"
            echo "2. Name"
            read -p "Enter your choice: " search_choice

            if [ "$search_choice" -eq 1 ]; then
                read -p "Enter ID to search: " id
                result=$(awk -F';' -v id="$id" '$1 == id {print}' "$FILE")
            elif [ "$search_choice" -eq 2 ]; then
                read -p "Enter Name to search: " name
                result=$(awk -F';' -v name="$name" 'tolower($2) == tolower(name) {print}' "$FILE")
            else
                echo "Invalid search choice!"
                continue
            fi

            echo "----------------------------------------"
            if [ -n "$result" ]; then
                echo "Record(s) found:"
                echo "$result"
            else
                echo "Record not found!!"
            fi
            ;;

        2)
            # ---------- ADD ----------
            read -p "Enter ID: " id
            # Prevent duplicate IDs
            if awk -F';' -v id="$id" '$1 == id {found=1} END {exit !found}' "$FILE"; then
                echo "Error: ID already exists! Try another."
                continue
            fi

            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            echo "$id;$name;$phone" >> "$FILE"
            echo "Record added successfully!"
            ;;

        3)
            # ---------- REMOVE ----------
            read -p "Enter ID to remove: " id
            if awk -F';' -v id="$id" '$1 == id {found=1} END {exit !found}' "$FILE"; then
                awk -F';' -v id="$id" '$1 != id' "$FILE" > temp.txt && mv temp.txt "$FILE"
                echo "Record removed successfully!"
            else
                echo "Record not found!"
            fi
            ;;

        4)
            # ---------- QUIT ----------
            echo "Exiting Address Book..."
            exit 0
            ;;

        *)
            echo "Invalid choice! Please try again."
            ;;
    esac
done


/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL$ cd 1
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/1$ gedit shellscript1.1.sh
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/1$ chmod +x shellscript1.1.sh
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/1$ ./shellscript1.1.sh
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 1
Search by:
1. ID
2. Name
Enter your choice: 1
Enter ID to search: 1
----------------------------------------
Record not found!!
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 1
Search by:
1. ID
2. Name
Enter your choice: 1
Enter ID to search: 1
----------------------------------------
Record not found!!
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 2
Enter ID: 1
Enter Name: sdfgg
Enter Phone: 23445676
Record added successfully!
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 2
Enter ID: 2    
Enter Name: sddfffff
Enter Phone: 23456778
Record added successfully!
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 2
Enter ID: 3
Enter Name: ddff
Enter Phone: 35667
Record added successfully!
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 3
Enter ID to remove: 2
Record removed successfully!
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 1
Search by:
1. ID
2. Name
Enter your choice: 1
Enter ID to search: 1
----------------------------------------
Record(s) found:
1;sdfgg;23445676
==============================
 Address Book Management 
==============================
1. Search Address Book
2. Add Address Book Entry
3. Remove Address Book Entry
4. Quit
==============================
Enter your choice: 4
Exiting Address Book...
*/
