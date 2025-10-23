# User Management System

A simple C program for managing user data with CRUD (Create, Read, Update, Delete) operations.

## Features

- **Create User**: Add new users with automatic ID generation
- **Read Users**: Display all users in a formatted table
- **Update User**: Modify existing user information by ID
- **Delete User**: Remove users by ID with confirmation prompt
- **Data Validation**: Ensures name is not empty and age is 18+

## Data Structure

The program uses a `User` structure with the following fields:
- `id`: Auto-generated unique identifier
- `name`: User's name (max 30 characters)
- `age`: User's age (must be 18 or older)
- `address`: User's address (max 60 characters)

## Usage

### Compilation
```bash
gcc -o user_management user_management.c
```

### Running the Program
```bash
./user_management
```

### Menu Options
1. **Create User**: Add a new user to the system
2. **Read All User**: Display all existing users
3. **Update User**: Modify an existing user's information
4. **Delete User**: Remove a user from the system
0. **Exit**: Terminate the program

## Input Validation

- **Name**: Cannot be empty
- **Age**: Must be 18 or greater
- **ID**: Must exist in the system for update/delete operations
- **Deletion**: Requires confirmation ('y' or 'Y')

## Limitations

- Maximum of 100 users (`MAXUSERS`)
- Data is stored in memory only (not persistent)
- Simple sequential ID generation
- No search or filtering capabilities beyond ID lookup

## Functions

- `create_user()`: Add new user with validation
- `read_user()`: Display all users in table format
- `update_user()`: Modify existing user data
- `delete_user()`: Remove user with confirmation
- `findUserById()`: Helper function to locate users by ID
- `validateAge()`: Age validation helper function
- `clearInputBuffer()`: Input buffer management

## Example Usage

```
1. Create User
2. Read All User
3. Update User
4. Delete User
0. Exit
Enter your option:-> 1
Create User Page
*****************
Enter Name: John Doe
Enter Age: 25
Enter Address: 123 Main Street, City
User added successfully.
```

## Error Handling

- Prevents empty names
- Validates age requirements
- Checks for valid user IDs during updates/deletes
- Handles maximum user limit
- Provides clear error messages