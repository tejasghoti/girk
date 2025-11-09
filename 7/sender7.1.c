#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok(".", 65);   // generate IPC key
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg message;
    printf("Enter message to send: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);

    message.msg_type = 1; // type = 1 for all messages

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Message sent to queue.\n");

    return 0;
}

/*hri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ nano sender7.1.c
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ nano receiver7.1.c
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ gcc sender7.1.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ gcc receiver7.1.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ gcc sender7.1.c -o sender
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ gcc receiver7.1.c -o receiver
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ./sender
Enter message to send: hello hello MF
Message sent to queue.
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ./sender
Enter message to send: hello ji
Message sent to queue.
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x41075bfd 1          shri       666        100          1           

shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ 

*/
