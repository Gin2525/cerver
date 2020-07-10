#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::string sa = "adsfa";
    if(sockfd < 0) {
        // error
        std::cout << "Error socket:" << std::strerror(errno);
        exit(1);
    }
    struct sockaddr_in addr; // 接続先の情報用の構造体
    memset(&addr, 0, sizeof(struct sockaddr_in)); // 初期化

    addr.sin_family = AF_INET;
    addr.sin_port = htons(
        1234); //ポート番号,htons()関数は16bitホストバイトオーダーをネットワークバイトオーダーに変換
    addr.sin_addr.s_addr =
        inet_addr("127.0.0.1"); // IPアドレス,inet_addr()関数はアドレスの翻訳

    //ソケット, アドレスポインタ, アドレスサイズ
    connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

    char s_str[] = "HelloWorld!";
    send(sockfd,s_str,12,0);
    std::cout << s_str << std::endl;

    close(sockfd);
    return 0;
}