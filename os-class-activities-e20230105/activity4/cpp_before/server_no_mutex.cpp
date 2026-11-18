#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int PORT = 9001;
const std::string FILE_NAME = "shared_score.txt";

int update_score(const std::string& name) {
    int score = 0;
    std::ifstream in(FILE_NAME);
    in >> score;                       // 1. READ
    in.close();

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // widen the race window

    score++;                           // 2. MODIFY
    std::ofstream out(FILE_NAME, std::ios::trunc);
    out << score << std::endl;         // 3. WRITE
    std::cout << "[" << name << "] score -> " << score << std::endl;
    return score;
}

void handle_client(int client_fd) {
    char buf[256] = {0};
    ssize_t n = read(client_fd, buf, sizeof(buf) - 1);
    std::string name = (n > 0) ? std::string(buf, n) : "unknown";
    while (!name.empty() && (name.back() == '\n' || name.back() == '\r')) name.pop_back();

    int score = update_score(name);
    std::string reply = "Score is now " + std::to_string(score) + "\n";
    send(client_fd, reply.c_str(), reply.size(), 0);
    close(client_fd);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;   // accept from any machine on the LAN
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    listen(server_fd, 50);
    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) continue;
        std::thread(handle_client, client_fd).detach();   // one thread per client
    }
}
