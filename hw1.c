/*
  Author: Anthony Garcia
  Email: anthony2018@my.fit.edu
  Course: Data Structures and Algorithms
  Section: 02
  Description: This program saves all the message given to the user and notifies him if their was a message received. This program also lets the user send messages and delete messages.
  Basically the program creates a text-messaging app that lets the user send and receive messages to and from different users.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct message
{
  char message[100];
  int time;
  char from[6];
  struct message *next;

}MESSAGE;


/*
  Description of the function, parameter, and return value (if any)
  - The insert_message function adds the messages to a linked list sorted in asscending order in terms of time.
  insert_message fucntion uses a double pointer of head(Can be bob, alice, carol) to access the linked list, from to save who sended the message in the linked list, 
  uses message to save the message in the linked list, and time to save the time and add it to the linked list.
  - The delete_message function deletes the message from a given linked list at a certain time.
  delete_message fucntion uses a double pointer of head(Can be bob, alice, carol) to access the linked list and uses time to know which message will be deleted
  -The display_conversation function shows all the messages from a given linked list in ascending order.
  display_conversation function uses a double pointer of head(Can be bob, alice, carol) to access the linked list and an integer pointer to change the value of the unread messages to 0
 */

void insert_message(MESSAGE **head, char from[], char message[], int time);
void delete_message(MESSAGE **head, int time);
void display_conversation(MESSAGE **head, int *unread);

int main(int argc, char* argv[]){
  /*
    The variable time is used to save the time of the message. Used for Inserting and Deleting messages.
    The variable action is used to save the command that is wanted, like "OpenApp", "CloseApp", or many others.
    The variable message is used to save the message that wants to be inserted.
    The variable from is for saving the name of the person that sended the message
    The variables named unread_"name" are used to know the amount of messages that aren't or have been read.
    The variable app is used to know if the app is closed or open. (Close is 0 and Open is 1)
    The variable file is used to access the file that was given in the command
   */
  int time;
  char action[30];
  char message[100];
  char from[6];
  int unread_alice = 0;
  int unread_bob = 0;
  int unread_carol = 0;
  bool app = 0;
  MESSAGE *bob, *alice, *carol;
  FILE *file = fopen(argv[argc-1], "r");

  //This loop will let all the commands iterate until the End-Of-File(EOF) is reached.
  while(1){
    //Is used to read a string from the file and save it in the variable action.
    fscanf(file, "%s", action);

    
    //Comparing the commands to received to OpenApp and checking if it was close before
    if ((strcmp(action,"OpenApp") == 0) && (app == 0)){
      //changes the variable app to 1(open) and prints that the app is open and all the unread messages
      app = 1;
      printf("OpenApp\n");
      printf("Alice %d\n", unread_alice);
      printf("Bob %d\n", unread_bob);
      printf("Carol %d\n", unread_carol);
    }
    //Comparing the commands to received to ReceiveMessage and checking if it was close before
    else if((strcmp(action,"ReceiveMessage") == 0) && (app == 0)){
      //reads the time, from where is comming, and the message
      fscanf(file, "%d", &time);
      fscanf(file, "%s", from);
      fscanf(file,"%[^\n]", message);

      //compares the from to each name already given, then inserts the messages and notifies that a message has been received by one of the names.
      if(strcmp(from, "Bob") == 0){
        insert_message(&bob, from, message, time);
        printf("NotifyUser Bob\n");
        unread_bob++;
      }
      else if(strcmp(from, "Alice") == 0){
        insert_message(&alice, from, message, time);
        printf("NotifyUser Alice\n");
        unread_alice++;
      }
      else if(strcmp(from, "Carol") == 0){
        insert_message(&carol, from, message, time);
        printf("NotifyUser Carol\n");
        unread_carol++;
      }
    }
    //Comparing the commands to received to SendMessage and checking if it was open before
    else if((strcmp(action,"SendMessage") == 0) && (app == 1)){
      //reads the time, to where is going (saved in from), and the message.
      fscanf(file, "%d", &time);
      fscanf(file, "%s", from);
      fscanf(file,"%[^\n]", message);

      //the command given from the file(the action wanted, the time given, to where is going, and the message)
      printf("%s %d %s%s\n", action, time, from, message);

      //Compare the variable from to each name so the message can be added accordingly.
      if(strcmp(from, "Bob") == 0){
        //changes the variable from to "me" becuase the user is the one sending the message
        strcpy(from,"me");
        insert_message(&bob, from, message, time);
        display_conversation(&bob, &unread_bob);
      }
      else if(strcmp(from, "Alice") == 0){
        //changes the variable from to "me" becuase the user is the one sending the message
        strcpy(from,"me");
        insert_message(&alice, from, message, time);
        display_conversation(&alice, &unread_alice);
      }
      else if(strcmp(from, "Carol") == 0){
        //changes the variable from to "me" becuase the user is the one sending the message
        strcpy(from,"me");
        insert_message(&carol, from, message, time);
        display_conversation(&carol, &unread_carol);
      }
    }
    //Comparing the commands to received to DeleteMessage and checking if it was open before
    else if((strcmp(action,"DeleteMessage") == 0) && (app == 1)){
      //reads the time and where is the message that we want to delete
      fscanf(file, "%d", &time);
      fscanf(file, "%s", from);

      //prints the action wanted the time and where is the message that it's going to be deleted
      printf("%s %d %s\n",action, time, from);

      //Compare the variable from to each name so the message can be deleted accordingly.
      if(strcmp(from, "Bob") == 0){
        delete_message(&bob, time);
        display_conversation(&bob, &unread_bob);
      }
      else if(strcmp(from, "Alice") == 0){
        delete_message(&alice, time);
        display_conversation(&alice, &unread_alice);
      }
      else if(strcmp(from, "Carol") == 0){
        delete_message(&carol, time);
        display_conversation(&carol, &unread_carol);
      }

    }
    //Comparing the commands to received to DisplayConversation and checking if it was open before
    else if((strcmp(action,"DisplayConversation") == 0) && (app == 1)){
      //reads from where is the conversation that wants to be shown
      fscanf(file, "%s", from);

      //Compare the variable from to each name so the message can be shown accordingly.
      if(strcmp(from, "Bob") == 0){
        printf("DisplayConversation Bob\n");
        display_conversation(&bob, &unread_bob);
      }
      else if(strcmp(from, "Alice") == 0){
        printf("DisplayConversation Alice\n");
        display_conversation(&alice, &unread_alice);
      }
      else if(strcmp(from, "Carol") == 0){
        printf("DisplayConversation Carol\n");
        display_conversation(&carol, &unread_carol);
      }

    }
    //Comparing the commands to received to CloseApp and checking if it was open before
    else if((strcmp(action,"CloseApp") == 0) && (app == 1)){
      //changes the variable app to 0(close) and prints the action wanted
      app = 0;
      printf("CloseApp\n");
    }
    else{
      printf("Command Inserted isn't available\n");
    }

    //checks if we got to the End-Of-File abd breaks the loop if its true
    if(fgetc(file) == EOF)
      break;
  }
  
  //closes the pointer file
  fclose(file);

  return 0;
}


void insert_message(MESSAGE **head, char from[], char message[], int time){
  /*
  The function allocates a dynamic memory to new_node
  then it adds the messages, the time, from where it comes the message, and the next pointer which will be set to NULL by default
  */
  MESSAGE *new_node = (MESSAGE*)malloc(sizeof(MESSAGE));
  strcpy(new_node->message, message);
  new_node->time = time;
  strcpy(new_node->from, from);
  new_node->next = NULL;

  //if the head is empty then make the head equal to the new_node
  if (*head == NULL)
    *head = new_node;
  else{
    //creates a temporary node that point to head
    MESSAGE *temp_node = *head;
    //if head is the only message then it compares the time slot between the new node and the head
    if ((*head)->next == NULL)
    {
      //if the head message was later on then change the head to the new node while the new node will be pointing to the previous head
      if ((*head)->time > time)
      {
        new_node->next = *head;
        *head = new_node;
      }
      //else then make the new node be after the head
      else
        (*head)->next = new_node;
    }
    else{
      //if the head message was later on then change the head to the new node while the new node will be pointing to the previous head
      if (temp_node->time > time)
      {
        new_node->next = *head;
        *head = new_node;
      }
      //if not then the temp_node will move forward until there's no more messages or the value after temp_node is bigger than the time in the new_node
      else{
        while((temp_node->next != NULL) && (temp_node->next->time < time)){
          temp_node = temp_node->next;
        }
        new_node->next = temp_node->next;
        temp_node->next = new_node;
      }
    }
  }
}

void delete_message(MESSAGE **head, int time){
  //create two temporary nodes
  MESSAGE *temp_node = *head;
  MESSAGE *temp_node2 = NULL;
  //if the head is empty do nothing
  if (*head == NULL);
  //check if the head have the same time as the one that wants to be deleted, if it does then erase the head
  else if ((*head)->time == time)
  {
    *head = (*head)->next;
    free(temp_node);
  }
  else{
    //move forward until there's no more messages or the time after temp_node is equal
    while((temp_node->next != NULL) && (temp_node->next->time != time)){
      temp_node = temp_node->next;
    }
    //if the reason of the stop of the loop was that the time was found then the message will be deleted if not it means that the message didn't exist
    if (temp_node->next != NULL)
    {
      temp_node2 = temp_node->next;
      temp_node->next = temp_node->next->next;
      free(temp_node2);
    }
  }
}

void display_conversation(MESSAGE **head, int *unread){
  //makes a temp_node point to head and changes a variable not from this function throught a pointer to 0(Use to check how many unread messages the user has).
  MESSAGE *temp_node = *head;
  *unread = 0;
  //prints all the messages in the linked list
  while(temp_node != NULL){
    printf("%d %s%s\n", temp_node->time, temp_node->from, temp_node->message);
    temp_node = temp_node->next;
  }
}