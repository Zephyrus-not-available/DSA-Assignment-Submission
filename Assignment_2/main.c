#include <stdio.h>
#include <string.h>

#define STACK_SIZE 100
#define TAG_SIZE 50
#define LINE_SIZE 256

// Stack to store XML opening tags
char tagStack[STACK_SIZE][TAG_SIZE];
int top = -1;

// Push tag onto stack
void pushTag(const char *tag) {
    if (top < STACK_SIZE - 1) {
        strcpy(tagStack[++top], tag);
    }
}

// Pop tag from stack
char* popTag() {
    if (top >= 0) {
        return tagStack[top--];
    }
    return NULL;
}

int main() {
    FILE *fp = fopen("note.xml", "r");
    if (!fp) {
        printf("Failed to open note.xml\n");
        printf("XML is invalid!\n");
        return 1;
    }

    printf("Checking XML structure...\n");
    char line[LINE_SIZE];
    int isValid = 1;

    while (fgets(line, sizeof(line), fp)) {
        for (int i = 0; line[i] != '\0'; i++) {

            // Opening tag
            if (line[i] == '<' && line[i + 1] != '/' && line[i + 1] != '!' && line[i + 1] != '?') {
                char tag[TAG_SIZE] = "";
                int t = 0;

                i++;
                while (line[i] != '>' && line[i] != ' ' && line[i] != '/' && line[i] != '\0') {
                    tag[t++] = line[i++];
                }
                tag[t] = '\0';

                if (t > 0 && tag[t - 1] != '/') {
                    pushTag(tag);
                }
            }


            if (line[i] == '<' && line[i + 1] == '/') {
                char closing[TAG_SIZE] = "";
                int t = 0;

                i += 2;
                while (line[i] != '>' && line[i] != '\0') {
                    closing[t++] = line[i++];
                }
                closing[t] = '\0';

                char *lastOpened = popTag();

                if (!lastOpened) {
                    printf("Extra closing tag found: </%s>\n", closing);
                    isValid = 0;
                } else if (strcmp(lastOpened, closing) != 0) {
                    printf("Tag mismatch: expected </%s> but found </%s>\n", lastOpened, closing);
                    isValid = 0;
                }
            }
        }
    }

    fclose(fp);

    if (top >= 0 && isValid) {
        isValid = 0;
        printf("Unclosed tags:\n");
        for (int i = 0; i <= top; i++) {
            printf("   - <%s>\n", tagStack[i]);
        }
    }

    if (isValid) {
        printf("XML is valid!\n");
    } else {
        printf("XML is invalid!\n");
    }

    return 0;
}
