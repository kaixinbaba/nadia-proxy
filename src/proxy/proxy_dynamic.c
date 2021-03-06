#include "proxy_dynamic.h"

static void request_dynamic(char *host, char *port, SDI *sdi);
static void select_server(char *host, char *port, DPS *dps);

static void do_round_robin(char *host, char *port, DPS *dps);
static void do_weighted_round_robin(char *host, char *port, DPS *dps);
static void do_ip_hash(char *host, char *port, DPS *dps);

void serve_dynamic(SDI *sdi){
    char host[MAXLINE], port[MAXLINE];
    select_server(host,port,sdi->dps);
    request_dynamic(host,port,sdi);
}

static void select_server(char *host, char *port, DPS *dps){
    switch (dps->proxyStrategy){
        case(ROUND_ROBIN):
            do_round_robin(host,port,dps);
            break;
        case(WEIGHTED_ROUND_ROBIN):
            do_weighted_round_robin(host,port,dps);
            break;
        case(IP_HASH):
            do_ip_hash(host,port,dps);
            break;
        default:
            do_round_robin(host,port,dps);
    }
}

static void do_round_robin(char *host, char *port, DPS *dps){
    int index;
    index = round_robin(&(dps->count),dps->size);

    DPI *info = (dps->proxyInfos)[index];
    strcpy(host,info->host);
    strcpy(port,info->port);
}

static void do_weighted_round_robin(char *host, char *port, DPS *dps){
    //todo
}

static void do_ip_hash(char *host, char *port, DPS *dps){
    int index;
    index = ip_hash(host,dps->size);
    DPI *info = (dps->proxyInfos)[index];
    strcpy(host,info->host);
    strcpy(port,info->port);
}

static void request_dynamic(char *host, char *port, SDI *sdi){
    // rio_t rio;
    int proxyClientfd;
    char buf[MAXLINE];

    proxyClientfd = Open_clientfd(host, port);

    sprintf(buf, "%s %s %s\r\n",sdi->method,sdi->uri,sdi->version); 
    Rio_writen(proxyClientfd, buf, strlen(buf));
    Rio_readlineb(sdi->rio, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) { 
        Rio_readlineb(sdi->rio, buf, MAXLINE);
    }
    Close(proxyClientfd);
}