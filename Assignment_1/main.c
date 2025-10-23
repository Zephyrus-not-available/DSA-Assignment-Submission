#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXUSERS 100
#define NAME 30
#define ADDRESS 60

typedef struct {
    int id;
    char name[NAME];
    int age;
    char address[ADDRESS];
} User;

int create_user(User users[], int count);
void read_user(User users[],int count);
void update_user(User users[],int count);
int delete_user(User users[],int count);
int findUserById(User users[], int count, int id);
int validateAge(int age);
void clearInputBuffer();

int main() {
    User users[MAXUSERS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n1. Create User\n");
        printf("2. Read All User\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("0. Exit\n");
        printf("Enter your option:-> ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                count = create_user(users, count);
                break;
            case 2:
                read_user(users,count);
                break;
            case 3:
                update_user(users,count);
                break;
            case 4:
                count = delete_user(users, count);
                break;
            case 0:
                printf("Exiting the program....");
                return 0;
            default:
                printf("Invalid Option.\n");
        }
    }
    return 0;
}

int create_user(User users[], int count) {
    printf("Create User Page\n");
    printf("*****************\n");

    if (count >= MAXUSERS) {
        printf("Max Users Reached!\n");
        return count;
    }

    User newUser;
    newUser.id = count + 1;

    printf("Enter Name: ");
    fgets(newUser.name, NAME, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';

    // Validate name is not empty
    if (strlen(newUser.name) == 0) {
        printf("Error: Name cannot be empty!\n");
        return count;
    }

    printf("Enter Age: ");
    scanf("%d", &newUser.age);
    getchar();

    if (!validateAge(newUser.age)) {
        printf("Error: Age must be greater than 18!\n");
        return count;
    }

    printf("Enter Address: ");
    fgets(newUser.address, ADDRESS, stdin);
    newUser.address[strcspn(newUser.address, "\n")] = '\0';

    users[count] = newUser;
    printf("User added successfully.\n");

    return count + 1;
}

void read_user(User users[],int count){
    printf("Reading All User Page\n");
    printf("*********************\n");

    if(count==0){
        printf("No User Found!\n");
        return;
    }

    printf("\n%-5s %-20s %-5s %-20s\n", "ID", "Name", "Age", "Address");
    for(int i=0;i<count;i++){
        printf("%-5d %-20s %-5d %-20s\n",users[i].id,users[i].name ,users[i].age ,users[i].address );
    }
}

void update_user(User users[],int count){
    printf("Update User Page\n");
    printf("*****************\n");

    if(count==0){
        printf("No User Found!\n");
        return;
    }

    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    getchar();

    int find = findUserById(users, count, id);
    if (find == -1) {
        printf("Error: User ID not found.\n");
        return;
    }

    printf("User ID found going to update.....\n");

    printf("Enter New Name: ");
    fgets(users[find].name, NAME, stdin);
    users[find].name[strcspn(users[find].name, "\n")] = '\0';

    if (strlen(users[find].name) == 0) {
        printf("Error: Name cannot be empty!\n");
        return;
    }

    printf("Enter New Age: ");
    scanf("%d", &users[find].age);
    getchar();

    if (!validateAge(users[find].age)) {
        printf("Error: Age must be greater than 18\n");
        return;
    }

    printf("Enter Address: ");
    fgets(users[find].address, ADDRESS, stdin);
    users[find].address[strcspn(users[find].address, "\n")] = '\0';

    printf("User ID %d. updated successfully.\n",id);
}

int delete_user(User users[],int count){
    printf("Delete User Page\n");
    printf("*****************\n");

    if(count==0){
        printf("No User Found!\n");
        return count;
    }

    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    getchar();

    int find = findUserById(users, count, id);
    if (find == -1) {
        printf("Error: User ID not found.\n");
        return count;
    }

    // Show user info before deletion
    printf("User to delete: %s (Age: %d)\n", users[find].name, users[find].age);

    // Confirm deletion
    char confirm;
    printf("Are you sure you want to delete? (y/n): ");
    scanf("%c", &confirm);
    getchar();

    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion cancelled.\n");
        return count;
    }

    for (int i = find; i < count - 1; i++) {
        users[i] = users[i + 1];
        users[i].id = i + 1;
    }

    printf("User ID %d. deleted successfully.\n",id);
    return count - 1;
}

int findUserById(User users[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (users[i].id == id) {
            return i;
        }
    }
    return -1;
}

int validateAge(int age) {
    return (age >= 18);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}