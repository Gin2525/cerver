#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int sockfd =
        socket(AF_INET, SOCK_STREAM, 0); //アドレス,ソケットタイプ,プロトコル
    if(sockfd < 0) {
        std::cout << "Error socket:" << std::strerror(errno);
        exit(1);
    }

    // アドレス生成
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // ソケット登録
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cout << "Error bind:" << std::strerror(errno);
        exit(1);
    }

    // 受信待ち
    if(listen(sockfd, SOMAXCONN) < 0) {
        std::cout << "Error listen:" << std::strerror(errno);
        close(sockfd);
        exit(1);
    }

    // 接続待ち
    struct sockaddr_in get_addr; //接続相手のソケットアドレス　
    socklen_t len = sizeof(struct sockaddr_in); //接続相手のアドレスサイズ
    //接続待ちソケット,接続相手のソケットアドレスポインタ,接続相手のアドレスサイズ
    int connect = accept(sockfd, (struct sockaddr *)&get_addr, &len);

    if(connect < 0) {
        std::cout << "Error accept:" << std::strerror(errno);
        exit(1);
    }

    // 受信
    char str[12];
    recv(connect, str, 12, 0);
    std::cout <<"accepted:"<< str << std::endl;

    // 送信
    send(connect, str, 12, 0);
    std::cout << "send:" << str << std::endl;

    // ソケットクローズ
    close(connect);
    close(sockfd);
}