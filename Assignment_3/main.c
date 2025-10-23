#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Customer account structure
struct Customer {
    int accID;
    char customerName[50];
    char contactNumber[15];
    double currentBalance;
    struct Customer* nextCustomer;
};

// Financial operation structure
struct Operation {
    int accID;
    char operationType[25];
    double operationAmount;
    double updatedBalance;
    struct Operation* nextOperation;
};

// Global list pointers
struct Customer* customerList = NULL;
struct Operation* operationHistory = NULL;

// Generate unique account ID
int createAccountID() {
    static int idSequence = 1000;
    return idSequence++;
}

// Create new customer account
void openNewAccount() {
    struct Customer* newCustomer = (struct Customer*)malloc(sizeof(struct Customer));

    if (newCustomer == NULL) {
        printf("System Error: Memory allocation failed!\n");
        return;
    }

    printf("\n*** OPEN NEW ACCOUNT ***\n");

    // Assign account ID
    newCustomer->accID = createAccountID();
    printf("Assigned Account ID: %d\n", newCustomer->accID);

    // Collect customer information
    printf("Enter customer full name: ");
    getchar();
    fgets(newCustomer->customerName, 50, stdin);
    newCustomer->customerName[strcspn(newCustomer->customerName, "\n")] = 0;

    printf("Enter mobile number: ");
    fgets(newCustomer->contactNumber, 15, stdin);
    newCustomer->contactNumber[strcspn(newCustomer->contactNumber, "\n")] = 0;

    printf("Enter initial deposit amount: $");
    scanf("%lf", &newCustomer->currentBalance);

    // Add to customer list
    newCustomer->nextCustomer = customerList;
    customerList = newCustomer;

    printf("\nAccount opened successfully!\n");
    printf("Account ID: %d\n", newCustomer->accID);
    printf("Customer: %s\n", newCustomer->customerName);
    printf("Current Balance: $%.2f\n", newCustomer->currentBalance);
}

// Locate customer by account ID
struct Customer* locateCustomer(int accountID) {
    struct Customer* current = customerList;

    while (current != NULL) {
        if (current->accID == accountID) {
            return current;
        }
        current = current->nextCustomer;
    }

    return NULL;
}

// Show customer account details
void showAccountDetails(int accountID) {
    struct Customer* customer = locateCustomer(accountID);

    if (customer == NULL) {
        printf("Account not found in system!\n");
        return;
    }

    printf("\n*** ACCOUNT INFORMATION ***\n");
    printf("Account ID: %d\n", customer->accID);
    printf("Customer Name: %s\n", customer->customerName);
    printf("Contact Number: %s\n", customer->contactNumber);
    printf("Available Balance: $%.2f\n", customer->currentBalance);
}

// Modify customer information
void modifyCustomerInfo() {
    int accountID;
    printf("Enter account ID to modify: ");
    scanf("%d", &accountID);

    struct Customer* customer = locateCustomer(accountID);

    if (customer == NULL) {
        printf("Account not found!\n");
        return;
    }

    printf("\n*** MODIFY ACCOUNT %d ***\n", accountID);
    printf("Current name: %s\n", customer->customerName);
    printf("Enter updated name: ");
    getchar();
    fgets(customer->customerName, 50, stdin);
    customer->customerName[strcspn(customer->customerName, "\n")] = 0;

    printf("Current contact: %s\n", customer->contactNumber);
    printf("Enter updated contact: ");
    fgets(customer->contactNumber, 15, stdin);
    customer->contactNumber[strcspn(customer->contactNumber, "\n")] = 0;

    printf("Account information updated successfully!\n");
}


// Remove customer account
void removeCustomerAccount() {
    int accountID;
    printf("Enter account ID to remove: ");
    scanf("%d", &accountID);

    struct Customer* current = customerList;
    struct Customer* previous = NULL;

    // Find account in list
    while (current != NULL && current->accID != accountID) {
        previous = current;
        current = current->nextCustomer;
    }

    if (current == NULL) {
        printf("Account not found!\n");
        return;
    }

    // Verify zero balance
    if (current->currentBalance > 0) {
        printf("Account has funds! Withdraw $%.2f before deletion.\n", current->currentBalance);
        return;
    }

    // Remove from linked list
    if (previous == NULL) {
        customerList = current->nextCustomer;
    } else {
        previous->nextCustomer = current->nextCustomer;
    }

    free(current);
    printf("Account removed from system!\n");
}

// Record financial operation
void recordOperation(int accountID, char type[], double amount, double newBalance) {
    struct Operation* newRecord = (struct Operation*)malloc(sizeof(struct Operation));

    if (newRecord == NULL) {
        printf("Error: Cannot save operation record!\n");
        return;
    }

    newRecord->accID = accountID;
    strcpy(newRecord->operationType, type);
    newRecord->operationAmount = amount;
    newRecord->updatedBalance = newBalance;

    // Add to operation history
    newRecord->nextOperation = operationHistory;
    operationHistory = newRecord;
}

// Add funds to account
void addFunds() {
    int accountID;
    double amount;

    printf("Enter account ID: ");
    scanf("%d", &accountID);

    struct Customer* customer = locateCustomer(accountID);

    if (customer == NULL) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter deposit amount: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount! Enter positive value.\n");
        return;
    }

    customer->currentBalance += amount;
    recordOperation(accountID, "FUNDS_DEPOSIT", amount, customer->currentBalance);

    printf("Deposit completed!\n");
    printf("Updated balance: $%.2f\n", customer->currentBalance);
}

// Withdraw funds from account
void withdrawFunds() {
    int accountID;
    double amount;

    printf("Enter account ID: ");
    scanf("%d", &accountID);

    struct Customer* customer = locateCustomer(accountID);

    if (customer == NULL) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter withdrawal amount: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount! Enter positive value.\n");
        return;
    }

    if (amount > customer->currentBalance) {
        printf("Insufficient balance! Available: $%.2f\n", customer->currentBalance);
        return;
    }

    customer->currentBalance -= amount;
    recordOperation(accountID, "FUNDS_WITHDRAWAL", -amount, customer->currentBalance);

    printf("Withdrawal completed!\n");
    printf("Remaining balance: $%.2f\n", customer->currentBalance);
}

// Transfer between accounts
void transferBetweenAccounts() {
    int sourceAccount, targetAccount;
    double transferAmount;

    printf("Enter source account ID: ");
    scanf("%d", &sourceAccount);

    struct Customer* source = locateCustomer(sourceAccount);
    if (source == NULL) {
        printf("Source account not found!\n");
        return;
    }

    printf("Enter destination account ID: ");
    scanf("%d", &targetAccount);

    struct Customer* target = locateCustomer(targetAccount);
    if (target == NULL) {
        printf("Destination account not found!\n");
        return;
    }

    if (sourceAccount == targetAccount) {
        printf("Cannot transfer to same account!\n");
        return;
    }

    printf("Enter transfer amount: $");
    scanf("%lf", &transferAmount);

    if (transferAmount <= 0) {
        printf("Invalid transfer amount!\n");
        return;
    }

    if (transferAmount > source->currentBalance) {
        printf("Insufficient funds! Balance: $%.2f\n", source->currentBalance);
        return;
    }

    // Execute transfer
    source->currentBalance -= transferAmount;
    target->currentBalance += transferAmount;

    // Record both operations
    recordOperation(sourceAccount, "TRANSFER_OUTGOING", -transferAmount, source->currentBalance);
    recordOperation(targetAccount, "TRANSFER_INCOMING", transferAmount, target->currentBalance);

    printf("Transfer successful!\n");
    printf("Source account balance: $%.2f\n", source->currentBalance);
    printf("Target account balance: $%.2f\n", target->currentBalance);
}

// Check account balance
void checkAccountBalance() {
    int accountID;

    printf("Enter account ID: ");
    scanf("%d", &accountID);

    struct Customer* customer = locateCustomer(accountID);

    if (customer == NULL) {
        printf("Account not found!\n");
        return;
    }

    printf("\nAccount ID: %d\n", customer->accID);
    printf("Account Holder: %s\n", customer->customerName);
    printf("Current Balance: $%.2f\n", customer->currentBalance);
}

// Display operation history
void showOperationHistory() {
    int accountID;

    printf("Enter account ID: ");
    scanf("%d", &accountID);

    if (locateCustomer(accountID) == NULL) {
        printf("Account not found!\n");
        return;
    }

    printf("\n*** OPERATION HISTORY - Account %d ***\n", accountID);

    struct Operation* current = operationHistory;
    int recordsFound = 0;

    while (current != NULL) {
        if (current->accID == accountID) {
            recordsFound = 1;
            printf("Operation: %-15s | Amount: $%8.2f | Balance: $%8.2f\n",
                   current->operationType, current->operationAmount, current->updatedBalance);
        }
        current = current->nextOperation;
    }

    if (!recordsFound) {
        printf("No operations recorded for this account.\n");
    }
}

// Display all customer accounts
void displayAllCustomers() {
    if (customerList == NULL) {
        printf("No customer accounts found!\n");
        return;
    }

    printf("\n*** ALL CUSTOMER ACCOUNTS ***\n");
    struct Customer* current = customerList;

    while (current != NULL) {
        printf("Account: %d | Customer: %-20s | Balance: $%.2f\n",
               current->accID, current->customerName, current->currentBalance);
        current = current->nextCustomer;
    }
}

// Clean up memory
void cleanupSystem() {
    // Free customer list
    struct Customer* currentCustomer = customerList;
    while (currentCustomer != NULL) {
        struct Customer* nextCustomer = currentCustomer->nextCustomer;
        free(currentCustomer);
        currentCustomer = nextCustomer;
    }

    // Free operation history
    struct Operation* currentOperation = operationHistory;
    while (currentOperation != NULL) {
        struct Operation* nextOperation = currentOperation->nextOperation;
        free(currentOperation);
        currentOperation = nextOperation;
    }
}


// Main system menu
void showMainMenu() {
    printf("\n=== FINANCIAL MANAGEMENT SYSTEM ===\n");
    printf("1.  Open New Account\n");
    printf("2.  Update Account Information\n");
    printf("3.  Close Account\n");
    printf("4.  Deposit Funds\n");
    printf("5.  Withdraw Funds\n");
    printf("6.  Transfer Funds\n");
    printf("7.  Check Account Balance\n");
    printf("8.  View Operation History\n");
    printf("9.  Display All Accounts\n");
    printf("10. Exit System\n");
    printf("Select option (1-10): ");
}

// Application entry point
int main() {
    int userChoice;

    printf("Welcome to Financial Management System!\n");
    printf("Linked list based account management.\n");

    while (1) {
        showMainMenu();
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                openNewAccount();
                break;
            case 2:
                modifyCustomerInfo();
                break;
            case 3:
                removeCustomerAccount();
                break;
            case 4:
                addFunds();
                break;
            case 5:
                withdrawFunds();
                break;
            case 6:
                transferBetweenAccounts();
                break;
            case 7:
                checkAccountBalance();
                break;
            case 8:
                showOperationHistory();
                break;
            case 9:
                displayAllCustomers();
                break;
            case 10:
                printf("Thank you for using our system!\n");
                cleanupSystem();
                return 0;
            default:
                printf("Invalid selection! Choose 1-10.\n");
        }
    }

    return 0;
}