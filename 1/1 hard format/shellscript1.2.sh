#!/bin/bash
# ==========================================
#       Phonebook Management System
# ==========================================

FILE="phonebook.txt"

# Create the file if it doesn't exist
if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

while true
do
    echo "=============================="
    echo "      PHONEBOOK MENU"
    echo "=============================="
    echo "1. Add New Entry"
    echo "2. Search by Name or Number"
    echo "3. Sort by Last Name"
    echo "4. Delete Entry"
    echo "5. Quit"
    echo "=============================="
    read -p "Enter your choice: " choice

    case $choice in
        1)
            # ---------- ADD ----------
            read -p "Enter First Name: " fname
            read -p "Enter Last Name: " lname
            read -p "Enter Phone Number: " phone

            # Check if phone number already exists
            if grep -q "$phone" "$FILE"; then
                echo "This phone number already exists in the phonebook!"
            else
                echo -e "${fname}\t${lname}\t${phone}" >> "$FILE"
                echo "New contact added successfully!"
            fi
            ;;

        2)
            # ---------- SEARCH ----------
            read -p "Enter Name or Phone Number to search: " key
            echo "----------------------------------------"
            result=$(grep -i "$key" "$FILE")
            if [ -n "$result" ]; then
                echo -e "Matches found:\n"
                echo -e "First Name\tLast Name\tPhone"
                echo "----------------------------------------"
                echo -e "$result"
            else
                echo "No matching entry found!"
            fi
            ;;

        3)
            # ---------- SORT ----------
            echo "Sorting phonebook by last name..."
            sort -k2,2 "$FILE" > temp.txt && mv temp.txt "$FILE"
            echo "Phonebook sorted successfully!"
            echo -e "\nFirst Name\tLast Name\tPhone"
            echo "----------------------------------------"
            cat "$FILE"
            ;;

        4)
            # ---------- DELETE ----------
            read -p "Enter Phone Number or Name to delete: " key
            if grep -iq "$key" "$FILE"; then
                grep -iv "$key" "$FILE" > temp.txt && mv temp.txt "$FILE"
                echo "Entry deleted successfully!"
            else
                echo "No matching entry found!"
            fi
            ;;

        5)
            # ---------- QUIT ----------
            echo "Exiting Phonebook..."
            exit 0
            ;;

        *)
            echo "Invalid choice! Please try again."
            ;;
    esac
done

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/1$ ./shellscript1.2.sh
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 1
Enter First Name: shfjfkjfsk
Enter Last Name: sjhfdk
Enter Phone Number: 48945809380
New contact added successfully!
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 1
Enter First Name: jkdbkjs
Enter Last Name: hffdk
Enter Phone Number: 432u58530295780
New contact added successfully!
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 1
Enter First Name: jdfgkjfd
Enter Last Name: hdfskjhvljcj
Enter Phone Number: 942385903
New contact added successfully!
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 2
Enter Name or Phone Number to search: jdfgkjfd
----------------------------------------
Matches found:

First Name	Last Name	Phone
----------------------------------------
jdfgkjfd	hdfskjhvljcj	942385903
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 3
Sorting phonebook by last name...
Phonebook sorted successfully!

First Name	Last Name	Phone
----------------------------------------
jdfgkjfd	hdfskjhvljcj	942385903
jkdbkjs	hffdk	432u58530295780
Kunal	Sadigale	1234567890
shfjfkjfsk	sjhfdk	48945809380
Shrivardhan	Yadav	12321233
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 4
Enter Phone Number or Name to delete: Kunal
Entry deleted successfully!
==============================
      PHONEBOOK MENU
==============================
1. Add New Entry
2. Search by Name or Number
3. Sort by Last Name
4. Delete Entry
5. Quit
==============================
Enter your choice: 5
Exiting Phonebook...
*/
