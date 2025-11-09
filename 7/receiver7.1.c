#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>

struct msg {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok(".", 65);
    int msgid = msgget(key, 0666);

    struct msg message;
    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

    // Convert to uppercase
    for(int i=0; message.msg_text[i] != '\0'; i++)
        message.msg_text[i] = toupper(message.msg_text[i]);

    printf("Received Message (Uppercase): %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL); // remove queue
    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ./receiver
Received Message (Uppercase): HELLO HELLO MF

shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ./receiver
Received Message (Uppercase): HELLO JI

shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ./out
*/
