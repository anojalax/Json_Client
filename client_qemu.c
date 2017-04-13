#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <json/json.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
        char* str;
	int fd = 0;
	int MAX_SIZE = 150; 
	struct sockaddr_in demoserverAddr;

	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0)
	{
	    printf("Error : Could not create socket\n");
	    return 1;
	}
	else
	{
	    demoserverAddr.sin_family = AF_INET;
	    demoserverAddr.sin_port = htons(8988);
	    demoserverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	    memset(demoserverAddr.sin_zero, '\0', sizeof(demoserverAddr.sin_zero));
	}

	if (connect(fd, (const struct sockaddr *)&demoserverAddr, sizeof(demoserverAddr)) < 0)
	{
	     printf("ERROR connecting to server\n");
	     return 1;
	}

	/*Creating a json object*/
	json_object *jobj = json_object_new_object();

	/*Creating a json integer*/
	json_object *PinNo = json_object_new_int(10);

	/*Creating a json boolean*/
	json_object *PinValue = json_object_new_boolean(1);

	/*Creating a json boolean*/
	json_object *PinDir = json_object_new_string("input");

	/*Creating a json array*/
	json_object *jarray = json_object_new_array();

	
	/*Adding the above created json strings to the array*/
	json_object_array_add(jarray,PinNo);
	json_object_array_add(jarray,PinValue);
	json_object_array_add(jarray,PinDir);
	
	json_object_object_add(jobj,"Pin Details", jarray);
	/*json_object_object_add(jobj,"Pin Number", PinNo);
	json_object_object_add(jobj,"Pin Direction", PinDir);
	json_object_object_add(jobj,"Pin Value", PinValue);*/	
	//printf("Size of JSON object- %lu\n", sizeof(jobj));
	printf("Size of JSON_TO_STRING- %lu,\n %s\n", sizeof(json_object_to_json_string(jobj)), 	json_object_to_json_string(jobj));
	    /* all previous code until
    printf("Size of string- %lu\n", sizeof(json_object_to_json_string(jobj)))*/

    char temp_buff[MAX_SIZE];

    if (strcpy(temp_buff, json_object_to_json_string(jobj)) == NULL)
    {
        perror("strcpy");
        return EXIT_FAILURE;
    }

    if (write(fd, temp_buff, strlen(temp_buff)) == -1)
    {
        perror("write");
        return EXIT_FAILURE;
    }

    printf("Written data\n");
    return EXIT_SUCCESS;
}
