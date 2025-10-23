# Financial Management System

A comprehensive banking system implemented in C using linked lists for efficient account and transaction management.

## Overview

This Financial Management System provides a complete banking solution with account management, transaction processing, and operation history tracking. The system uses linked lists for dynamic memory management and supports multiple concurrent accounts.

## Features

### Account Management
- **Open New Account**: Create accounts with auto-generated IDs
- **Update Account Information**: Modify customer details
- **Close Account**: Remove accounts (zero balance required)
- **View All Accounts**: Display complete customer list

### Financial Operations
- **Deposit Funds**: Add money to accounts
- **Withdraw Funds**: Remove money with balance validation
- **Transfer Funds**: Move money between accounts
- **Check Balance**: View current account balance

### Transaction Tracking
- **Operation History**: Complete audit trail for each account
- **Real-time Updates**: Instant balance calculations
- **Transaction Records**: Detailed operation logging

## Data Structures

### Customer Account
```c
struct Customer {
    int accID;              // Unique account identifier
    char customerName[50];  // Account holder name
    char contactNumber[15]; // Contact information
    double currentBalance;  // Available funds
    struct Customer* nextCustomer; // Linked list pointer
};
```

### Financial Operation
```c
struct Operation {
    int accID;              // Associated account ID
    char operationType[25]; // Transaction type
    double operationAmount; // Transaction amount
    double updatedBalance;  // Balance after operation
    struct Operation* nextOperation; // Linked list pointer
};
```

## System Architecture

### Linked List Implementation
- **Customer List**: Singly linked list storing all accounts
- **Operation History**: Separate linked list for transaction records
- **Dynamic Memory**: Efficient allocation and deallocation
- **Sequential Access**: Optimized for banking operations

### ID Generation
- Auto-incrementing account IDs starting from 1000
- Thread-safe static counter implementation
- Unique identifier guarantee

## Usage

### Compilation
```bash
gcc -o banking_system banking_system.c
```

### Running the System
```bash
./banking_system
```

### Main Menu Options
```
=== FINANCIAL MANAGEMENT SYSTEM ===
1.  Open New Account
2.  Update Account Information
3.  Close Account
4.  Deposit Funds
5.  Withdraw Funds
6.  Transfer Funds
7.  Check Account Balance
8.  View Operation History
9.  Display All Accounts
10. Exit System
```

## Operation Types

The system tracks these transaction types:
- `FUNDS_DEPOSIT`: Money added to account
- `FUNDS_WITHDRAWAL`: Money removed from account
- `TRANSFER_OUTGOING`: Funds sent to another account
- `TRANSFER_INCOMING`: Funds received from another account

## Business Rules

### Account Management
- Initial deposit required for account opening
- Zero balance required for account closure
- Unique account IDs automatically assigned
- Customer information can be updated

### Transaction Validation
- Positive amount validation for deposits/withdrawals
- Sufficient balance check for withdrawals and transfers
- Same-account transfer prevention
- Real-time balance updates

### Security Features
- Account existence verification for all operations
- Balance validation before transactions
- Complete audit trail maintenance
- Memory cleanup on system exit

## Error Handling

- **Memory Allocation**: Checks for malloc failures
- **Input Validation**: Validates all user inputs
- **Account Verification**: Confirms account existence before operations
- **Balance Checks**: Prevents overdrafts and invalid transactions
- **Data Integrity**: Maintains consistent linked list structures

## Memory Management

### Dynamic Allocation
- Customer accounts allocated as needed
- Operation records created for each transaction
- Efficient linked list traversal

### Cleanup Process
```c
void cleanupSystem() {
    // Free all customer nodes
    // Free all operation nodes
    // Reset global pointers
}
```

## Example Usage Scenarios

### Opening an Account
```
*** OPEN NEW ACCOUNT ***
Assigned Account ID: 1000
Enter customer full name: John Smith
Enter mobile number: 555-0123
Enter initial deposit amount: $500.00

Account opened successfully!
Account ID: 1000
Customer: John Smith
Current Balance: $500.00
```

### Transfer Between Accounts
```
Enter source account ID: 1000
Enter destination account ID: 1001
Enter transfer amount: $200.00

Transfer successful!
Source account balance: $300.00
Target account balance: $700.00
```

### Operation History
```
*** OPERATION HISTORY - Account 1000 ***
Operation: FUNDS_DEPOSIT   | Amount: $  500.00 | Balance: $  500.00
Operation: TRANSFER_OUTGOING | Amount: $ -200.00 | Balance: $  300.00
```

## Advantages

### Linked List Benefits
- **Dynamic Sizing**: No fixed limit on accounts or transactions
- **Efficient Insertions**: O(1) time for new accounts and operations
- **Memory Efficiency**: Only allocates needed memory
- **Flexible Structure**: Easy to extend and modify

### System Reliability
- **Data Persistence**: Maintains integrity during session
- **Error Recovery**: Graceful handling of edge cases
- **Audit Compliance**: Complete transaction history
- **User-Friendly**: Clear prompts and feedback

## Limitations

- **In-Memory Storage**: Data lost on program exit
- **Single Session**: No persistent database
- **Basic Security**: No authentication mechanism
- **Single Thread**: No concurrent access handling

## Extension Possibilities

- File-based persistence
- Interest calculation
- Statement generation
- Multi-currency support
- User authentication
- Graphical interface
- Network connectivity

This system demonstrates robust banking operations using fundamental data structures, providing a solid foundation for financial application development.