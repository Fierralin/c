#include<stdlib.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/types.h>       //pthread_t , pthread_attr_t and so on.
#include<stdio.h>
#include<netinet/in.h>      //structure sockaddr_in
#include<arpa/inet.h>       //Func : htonl; htons; ntohl; ntohs
#include<assert.h>          //Func :assert
#include<string.h>          //Func :memset
#include<unistd.h>          //Func :close,write,read
#define SOCK_PORT 11222
#define BUFFER_LENGTH 1024
#define MAX_CONN_LIMIT 512     //MAX connection limit

#define ERROR -1
#define TRUE 1

#include "memcached.h"

static void Data_handle(void * sock_fd);   //Only can be seen in the file

int
format_request(uint32_t ip_addr, uint16_t port, char * buf, int buf_len);

int main()
{
    int sockfd_server;
    int sockfd;
    int fd_temp;
    struct sockaddr_in s_addr_in;
    struct sockaddr_in s_addr_client;
    int client_length;

    sockfd_server = socket(AF_INET,SOCK_STREAM,0);  //ipv4,TCP
    assert(sockfd_server != -1);

    memset(&s_addr_in,0,sizeof(s_addr_in));
    s_addr_in.sin_family = AF_INET;
    s_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);  //trans addr from uint32_t host byte order to network byte order.
    s_addr_in.sin_port = htons(SOCK_PORT);          //trans port from uint16_t host byte order to network byte order.
    fd_temp = bind(sockfd_server,(struct scokaddr *)(&s_addr_in),sizeof(s_addr_in));
    if(fd_temp == -1)
    {
        fprintf(stderr,"bind error!\n");
        exit(1);
    }

    fd_temp = listen(sockfd_server,MAX_CONN_LIMIT);
    if(fd_temp == -1)
    {
        fprintf(stderr,"listen error!\n");
        exit(1);
    }

    while(1)
    {
        printf("waiting for new connection...\n");
        pthread_t thread_id;
        client_length = sizeof(s_addr_client);

        //Block here. Until server accpets a new connection.
        sockfd = accept(sockfd_server,(struct sockaddr_*)(&s_addr_client),(socklen_t *)(&client_length));
        if(sockfd == -1)
        {
            fprintf(stderr,"Accept error!\n");
            continue;                               //ignore current socket ,continue while loop.
        }
		//char data_recv[BUFFER_LENGTH];
		//int tmpi = recv(sockfd, data_recv, BUFFER_LENGTH, 0);
		//if (tmpi < 0) printf("==========================\n");
		//else printf("Recv data is %s\n",data_recv);
		
        printf("A new connection occurs!\n");
        if(pthread_create(&thread_id,NULL,(void *)(&Data_handle),(void *)(&sockfd)) == -1)
        {
            fprintf(stderr,"pthread_create error!\n");
            break;                                  //break while loop
        }
    }

    //Clear
    int ret = shutdown(sockfd_server,SHUT_WR); //shut down the all or part of a full-duplex connection.
    assert(ret != -1);

    printf("Server shuts down\n");
    return 0;
}

static void Data_handle(void * sock_fd)
{
    int fd = *((int *)sock_fd);
    int i_recvBytes;
    char data_recv[BUFFER_LENGTH];
    const char * data_send = "Server has received your request!\n";

    while(1)
    {
        printf("waiting for request...\n");
        //Reset data.
        memset(data_recv,0,BUFFER_LENGTH);

        //i_recvBytes = read(fd,data_recv,BUFFER_LENGTH);
		i_recvBytes = recv(fd, data_recv, BUFFER_LENGTH, 0);
        if(i_recvBytes == 0)
        {
            printf("Maybe the client has closed\n");
            break;
        }
        if(i_recvBytes == -1) {
            fprintf(stderr,"read error!\n");
            break;
        }
        if(strcmp(data_recv,"quit")==0) {
            printf("Quit command!\n");
            break;                           //Break the while loop.
        }
		data_recv[i_recvBytes] = '\0';
        printf("read from client : |%s|%d|\n|", data_recv, i_recvBytes);
		int tmpi = 0;
		for (; tmpi < i_recvBytes; tmpi++)
			printf("%c", data_recv[tmpi]);
		printf("|-----\n");
		format_request(12334443, 4, data_recv, i_recvBytes);
		tmpi = 0;
		for (; tmpi < i_recvBytes; tmpi++)
			printf("%c", data_recv[tmpi]);
		printf("|-----\n");
		uint32_t ipaddr; uint16_t port;
		format_response(&ipaddr, &port, data_recv, i_recvBytes);
		tmpi = 0;
		for (; tmpi < i_recvBytes; tmpi++)
			printf("%c", data_recv[tmpi]);
		printf("|-----\n");
        if(write(fd,data_send,strlen(data_send)) == -1) break;
    }

    //Clear
    printf("terminating current client_connection...\n");
    close(fd);            //close a file descriptor.
    pthread_exit(NULL);   //terminate calling thread!
}


int
format_request(uint32_t ip_addr, uint16_t port, char * buf, int buf_len)
{
	protocol_binary_request_header * header = (protocol_binary_request_header *)buf;
	client_id * client = &(header->request.opaque);
	uint16_t ip_rank;

	if (buf_len < sizeof(protocol_binary_request_header))
		return ERROR;

	client = &(header->request.opaque);
	/* check if is a request */
	if (header->request.magic == PROTOCOL_BINARY_REQ) {

		header->request.opcode = PROTOCOL_BINARY_CMD_GETK;
		header->request.magic = PROTOCOL_BINARY_RES; /* --------------- */
		//ip_rank = get_rank_from_ip(ip_addr);
		ip_rank = 3; /* --------------- */

		if (ip_rank == 0) {
			return ERROR;
		}

		client->id.src_ip_rank = ip_rank;
		client->id.src_port = port;

		printf("[%d|%d]\n", client->id.src_ip_rank, client->id.src_port); /* --------------- */
		return TRUE;
	}

	return ERROR;
}

int format_response(uint32_t *ip_addr, uint16_t *port, char *buf, int buf_len) {
	protocol_binary_request_header * header = (protocol_binary_request_header *)buf;
	client_id * client = &(header->request.opaque);
	
	if (buf_len < sizeof(protocol_binary_request_header))
		return ERROR;
	
	client = &(header->request.opaque);
	
	if (header->request.magic == PROTOCOL_BINARY_RES) {
		*ip_addr = get_ip_from_rank(client->id.src_ip_rank);
		//ip_addr = 12345678; /* --------------- */
		*port = client->id.src_port;

		printf("port[%d ip|%d]\n", *port, *ip_addr); /* --------------- */
		return TRUE;
	}

	return ERROR;
}

int noname(char *buf) {
	protocol_binary_request_header * header = (protocol_binary_request_header *)buf;
}