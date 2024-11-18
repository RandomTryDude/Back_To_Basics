#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For inet_addr
#include <unistd.h>
#include <string.h>

#define PORT 4444

int send_data(const char *buf, int lenbuff , char *filename , int filelen){
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);

    int server = connect(fd, (struct sockaddr*)&address, addrlen);

   send(fd , filename , filelen ,0);
   send(fd, buf, lenbuff, 0); 
  
  

    close(fd);
	 
}

int main(void) {
   
    unsigned char tmpbuf[1024] = {0};
    char buf[1024] = {0};
    size_t buf_index = 0; //
    char filename[] = "test.txt";
	 
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read file content
    size_t size = fread(tmpbuf, 1, sizeof(tmpbuf), file);
    fclose(file);

    if (size == 0) {
        printf("File is empty or nothing was read.\n");
        return 1;
    }




    int current_bit = -1; // Track the current bit (0 or 1)
    int count = 0;        // Count of consecutive bits
    int place = 0;
    for (size_t i = 0; i < size; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            int bit_value = (tmpbuf[i] >> bit) & 1;

            // Print the binary value
            //printf("%d", bit_value);

            // Count consecutive runs
            if (bit_value == current_bit) {
                count++;
            } else {
                if (current_bit != -1) {
                    //printf(" %d", count); // Print the count
                    buf_index += sprintf(&buf[buf_index], "%d", count);
                }
                current_bit = bit_value;
                count = 1; // Reset count
            }
        }
    }

    // Print the last run
    if (count > 0) {
        //printf(" %d", count);
        buf_index += sprintf(&buf[buf_index], "%d", count);
    }

 

    
    int lenbuff = strlen(buf);
    int lenfile = strlen(filename);
    filename[lenfile] = '\0';
    send_data(buf , lenbuff ,filename , lenfile);

    return 0;
}
