#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *text = "Hello from Operating Systems class!\n";
    const char *confirm = "File created successfully!\n";

    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, strlen(err));
        return 1;
    }

    if (write(fd, text, strlen(text)) < 0) {
        const char *err = "Error writing to file\n";
        write(2, err, strlen(err));
        close(fd);
        return 1;
    }

    close(fd);

    write(1, confirm, strlen(confirm));
    return 0;
}
