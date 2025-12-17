#!/bin/bash

# Database operations on flat file

DB_FILE="database.txt"

# Create database file if it doesn't exist
create_db() {
    if [ -f "$DB_FILE" ]; then
        echo "Database already exists!"
    else
        touch "$DB_FILE"
        echo "Database created successfully!"
    fi
}

# Insert record
insert_record() {
    echo "Enter ID:"
    read id
    echo "Enter Name:"
    read name
    echo "Enter Age:"
    read age
    echo "Enter City:"
    read city
    
    # Check if ID already exists
    if grep -q "^$id|" "$DB_FILE" 2>/dev/null; then
        echo "Error: Record with ID $id already exists!"
    else
        echo "$id|$name|$age|$city" >> "$DB_FILE"
        echo "Record inserted successfully!"
    fi
}

# Display all records
display_records() {
    if [ ! -f "$DB_FILE" ] || [ ! -s "$DB_FILE" ]; then
        echo "No records found!"
    else
        echo "======================================"
        printf "%-10s %-15s %-10s %-15s\n" "ID" "Name" "Age" "City"
        echo "======================================"
        while IFS='|' read -r id name age city; do
            printf "%-10s %-15s %-10s %-15s\n" "$id" "$name" "$age" "$city"
        done < "$DB_FILE"
        echo "======================================"
    fi
}

# Delete record
delete_record() {
    echo "Enter ID to delete:"
    read id
    
    if [ ! -f "$DB_FILE" ]; then
        echo "Database does not exist!"
        return
    fi
    
    if grep -q "^$id|" "$DB_FILE"; then
        grep -v "^$id|" "$DB_FILE" > temp.txt
        mv temp.txt "$DB_FILE"
        echo "Record deleted successfully!"
    else
        echo "Record with ID $id not found!"
    fi
}

# Update record
update_record() {
    echo "Enter ID to update:"
    read id
    
    if [ ! -f "$DB_FILE" ]; then
        echo "Database does not exist!"
        return
    fi
    
    if grep -q "^$id|" "$DB_FILE"; then
        echo "Enter new Name:"
        read name
        echo "Enter new Age:"
        read age
        echo "Enter new City:"
        read city
        
        grep -v "^$id|" "$DB_FILE" > temp.txt
        echo "$id|$name|$age|$city" >> temp.txt
        mv temp.txt "$DB_FILE"
        echo "Record updated successfully!"
    else
        echo "Record with ID $id not found!"
    fi
}

# Main menu
while true; do
    echo ""
    echo "===== Database Operations Menu ====="
    echo "1. Create Database"
    echo "2. Insert Record"
    echo "3. Display Records"
    echo "4. Delete Record"
    echo "5. Update Record"
    echo "6. Exit"
    echo "===================================="
    echo "Enter your choice:"
    read choice
    
    case $choice in
        1) create_db ;;
        2) insert_record ;;
        3) display_records ;;
        4) delete_record ;;
        5) update_record ;;
        6) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice!" ;;
    esac
done
