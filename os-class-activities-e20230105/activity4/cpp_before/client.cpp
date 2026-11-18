#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int PORT = 9001;

int main(int argc, char* argv[]) {
    if (argc != 3) { std::cerr << "Usage: " << argv[0] << " <server_ip> <student_name>\n"; return 1; }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);
    if (connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) { perror("connect"); return 1; }

    std::string msg = std::string(argv[2]) + "\n";
    send(fd, msg.c_str(), msg.size(), 0);
    char buf[256] = {0};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) std::cout << argv[2] << ": " << buf;
    close(fd);
}
