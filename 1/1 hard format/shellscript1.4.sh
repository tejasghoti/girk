#!/bin/bash
# ==============================================
#   FILE MANAGEMENT PROGRAM  (Q.1.4)
#   Features:
#   1. Test if file exists
#   2. Read a file
#   3. Delete a file
#   4. Display list of files
# ==============================================

# ---------- Function: Test if file exists ----------
test_file() {
    read -p "Enter filename to test: " fname
    if [ -f "$fname" ]; then
        echo "✅ File '$fname' exists."
    else
        echo "❌ File '$fname' does NOT exist."
    fi
}

# ---------- Function: Read file ----------
read_file() {
    read -p "Enter filename to read: " fname
    if [ -f "$fname" ]; then
        echo "---------------------------------"
        echo "📘 Contents of '$fname':"
        echo "---------------------------------"
        cat "$fname"
        echo "---------------------------------"
    else
        echo "❌ File '$fname' not found!"
    fi
}

# ---------- Function: Delete file ----------
delete_file() {
    read -p "Enter filename to delete: " fname
    if [ -f "$fname" ]; then
        rm "$fname"
        echo "🗑️  File '$fname' deleted successfully."
    else
        echo "❌ File '$fname' not found!"
    fi
}

# ---------- Function: Display all files ----------
list_files() {
    echo "---------------------------------"
    echo "📂 Files in Current Directory:"
    echo "---------------------------------"
    ls -1   # -1 = one file per line
    echo "---------------------------------"
}

# ---------- Function: Menu ----------
menu() {
    while true
    do
        echo "=============================="
        echo "     FILE MANAGEMENT MENU"
        echo "=============================="
        echo "1. Test if file exists"
        echo "2. Read a file"
        echo "3. Delete a file"
        echo "4. Display list of files"
        echo "5. Quit"
        echo "=============================="
        read -p "Enter your choice: " choice

        case $choice in
            1) test_file ;;
            2) read_file ;;
            3) delete_file ;;
            4) list_files ;;
            5) echo "Exiting program..."; exit 0 ;;
            *) echo "Invalid choice! Please try again." ;;
        esac
    done
}

# ---------- Main Program ----------
menu



/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/1$ ./shellscript1.4.sh
==============================
     FILE MANAGEMENT MENU
==============================
1. Test if file exists
2. Read a file
3. Delete a file
4. Display list of files
5. Quit
==============================
Enter your choice: 1
Enter filename to test: shellscript1.1.sh
✅ File 'shellscript1.1.sh' exists.
==============================
     FILE MANAGEMENT MENU
==============================
1. Test if file exists
2. Read a file
3. Delete a file
4. Display list of files
5. Quit
==============================
Enter your choice: 2
Enter filename to read: addressbook.txt
---------------------------------
📘 Contents of 'addressbook.txt':
---------------------------------
3:dmdd,:sjcjbd:sjbf
1:jsajfhjk:40458:dfjkbsvd
---------------------------------
==============================
     FILE MANAGEMENT MENU
==============================
1. Test if file exists
2. Read a file
3. Delete a file
4. Display list of files
5. Quit
==============================
Enter your choice: 3
Enter filename to delete: addressbook.txt
🗑️  File 'addressbook.txt' deleted successfully.
==============================
     FILE MANAGEMENT MENU
==============================
1. Test if file exists
2. Read a file
3. Delete a file
4. Display list of files
5. Quit
==============================
Enter your choice: 4
---------------------------------
📂 Files in Current Directory:
---------------------------------
address2.txt
address.txt
phonebbok.txt
phonebook.txt
shellscript1.1.sh
shellscript1.2.sh
shellscript1.3.sh
shellscript1.4.sh
---------------------------------
==============================
     FILE MANAGEMENT MENU
==============================
1. Test if file exists
2. Read a file
3. Delete a file
4. Display list of files
5. Quit
==============================
Enter your choice: 5
Exiting program...
*/
