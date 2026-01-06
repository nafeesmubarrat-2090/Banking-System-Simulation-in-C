#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

struct Account {
    int accNo; // user acc no
    char owner[100]; // full name
    char pass[50];   // simple password
    float balance;   // balance added to struct
};

// Function headers
void makeNewAcc();
void showAcc();
void addMoney();
void takeMoney();
void removeAcc();
void showAll();
void seeHistory();

int doesAccExist(int number);
void buildFileName(char *out, int number);
void addToLog(int number, const char *what, float howMuch);
int checkPassword(int number);

int main() {
    int pick;
    do {
        printf("\n--- MENU ---\n");
        printf("1. New Account\n2. View\n3. Deposit\n4. Withdraw\n5. List\n6. Delete\n7. History\n8. Exit\nPick: ");
        scanf("%d", &pick);

        switch (pick) {
            case 1: makeNewAcc(); break;
            case 2: showAcc(); break;
            case 3: addMoney(); break;
            case 4: takeMoney(); break;
            case 5: showAll(); break;
            case 6: removeAcc(); break;
            case 7: seeHistory(); break;
            case 8: printf("bye\n"); break;
            default: printf("try again\n");
        }
    } while (pick != 8);

    return 0;
}

void buildFileName(char *out, int number) {
    sprintf(out, "account_%d.txt", number);
}

int doesAccExist(int number) {
    char path[50];
    buildFileName(path, number);
    FILE *f = fopen(path, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

int checkPassword(int number) {
    struct Account me;
    char path[50], input[50];
    buildFileName(path, number);
    FILE *f = fopen(path, "r");
    if (!f) return 0;
   fscanf(f, "%d\n%[^\n]\n%s\n%f", &me.accNo, me.owner, me.pass, &me.balance);
    fclose(f);

    printf("pass: ");
    scanf(" %s", input);
    return strcmp(me.pass, input) == 0;
}

void addToLog(int number, const char *what, float howMuch) {
    char path[50];
    sprintf(path, "history_%d.txt", number);
    FILE *f = fopen(path, "a");
    if (f) {
        fprintf(f, "%s: %.2f\n", what, howMuch);
        fclose(f);
    }
}

void makeNewAcc() {
    struct Account me;
    printf("Acc #: ");
    scanf("%d", &me.accNo);

    if (doesAccExist(me.accNo)) {
        printf("already made\n");
        return;
    }

    printf("Name: ");
    scanf(" %[^\n]", me.owner);

    printf("Pass: ");
    scanf(" %s", me.pass);

    printf("Starting Bal: ");
    scanf("%f", &me.balance);

    char path[50];
    buildFileName(path, me.accNo);
    FILE *f = fopen(path, "w");
    fprintf(f, "%d\n%s\n%s\n%.2f\n", me.accNo, me.owner, me.pass, me.balance);
    fclose(f);

    addToLog(me.accNo, "Created", me.balance);
    printf("Done.\n");
}

void showAcc() {
    int num;
    printf("Acc #: ");
    scanf("%d", &num);

    if (!doesAccExist(num)) {
        printf("Nope.\n");
        return;
    }
    if (!checkPassword(num)) {
        printf("Wrong.\n");
        return;
    }

    char path[50];
    buildFileName(path, num);
    FILE *f = fopen(path, "r");
    struct Account me;
    fscanf(f, "%d\n%[^\n]\n%s\n%f", &me.accNo, me.owner, me.pass, &me.balance);
    fclose(f);

    printf("\n-- Info --\n");
    printf("No: %d\n", me.accNo);
    printf("Name: %s\n", me.owner);
    printf("Money: %.2f\n", me.balance);
}

void addMoney() {
    int num;
    float amt;
    printf("Acc #: ");
    scanf("%d", &num);

    if (!doesAccExist(num)) {
        printf("Not there.\n");
        return;
    }
    if (!checkPassword(num)) {
        printf("Bad pass.\n");
        return;
    }

    char path[50];
    buildFileName(path, num);
    FILE *f = fopen(path, "r");
    struct Account me;
    fscanf(f, "%d\n%[^\n]\n%s\n%f", &me.accNo, me.owner, me.pass, &me.balance);
    fclose(f);

    printf("Add: ");
    scanf("%f", &amt);
    if (amt <= 0) {
        printf("Nah\n");
        return;
    }

    me.balance += amt;

    f = fopen(path, "w");
    fprintf(f, "%d\n%s\n%s\n%.2f\n", me.accNo, me.owner, me.pass, me.balance);
    fclose(f);

    addToLog(num, "+", amt);
    printf("Done. New: %.2f\n", me.balance);
}

void takeMoney() {
    int num;
    float amt;
    printf("Acc #: ");
    scanf("%d", &num);

    if (!doesAccExist(num)) {
        printf("No acc.\n");
        return;
    }
    if (!checkPassword(num)) {
        printf("Wrong pass\n");
        return;
    }

    char path[50];
    buildFileName(path, num);
    FILE *f = fopen(path, "r");
    struct Account me;
    fscanf(f, "%d\n%[^\n]\n%s\n%f", &me.accNo, me.owner, me.pass, &me.balance);
    fclose(f);

    printf("Take: ");
    scanf("%f", &amt);

    if (amt > me.balance) {
        printf("Not enough\n");
        return;
    }

    me.balance -= amt;

    f = fopen(path, "w");
    fprintf(f, "%d\n%s\n%s\n%.2f\n", me.accNo, me.owner, me.pass, me.balance);
    fclose(f);

    addToLog(num, "-", amt);
    printf("Done. Left: %.2f\n", me.balance);
}

void removeAcc() {
    int num;
    printf("Which #: ");
    scanf("%d", &num);

    if (!doesAccExist(num)) {
        printf("No such.\n");
        return;
    }
    if (!checkPassword(num)) {
        printf("No pass match\n");
        return;
    }

    char a[50], c[50];
    buildFileName(a, num);
    sprintf(c, "history_%d.txt", num);

    remove(a);
    remove(c);
    printf("Gone.\n");
}

void showAll() {
    struct dirent *d;
    DIR *dir = opendir(".");
    if (!dir) {
        printf("fail\n");
        return;
    }

    printf("\n-- All --\n");
    while ((d = readdir(dir)) != NULL) {
        if (strncmp(d->d_name, "account_", 8) == 0 && strstr(d->d_name, ".txt")) {
            FILE *f = fopen(d->d_name, "r");
            struct Account me;
            fscanf(f, "%d\n%[^\n]\n%s\n%f", &me.accNo, me.owner, me.pass, &me.balance);
            fclose(f);
            printf("%d | %s | %.2f\n", me.accNo, me.owner, me.balance);
        }
    }
    closedir(dir);
}

void seeHistory() {
    int num;
    printf("Acc #: ");
    scanf("%d", &num);

    if (!doesAccExist(num)) {
        printf("no acc\n");
        return;
    }
    if (!checkPassword(num)) {
        printf("no match\n");
        return;
    }

    char path[50];
    sprintf(path, "history_%d.txt", num);
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("No history\n");
        return;
    }

    printf("-- Log --\n");
    char line[200];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);
}
