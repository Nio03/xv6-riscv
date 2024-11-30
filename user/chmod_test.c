#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void test_file_creation_and_opening()
{
    printf("Test: File Creation and Opening\n");

    int fd = open("testfile", O_CREATE | O_RDWR);
    if (fd < 0)
    {
        printf("Error: Failed to create and open file testfile\n");
        exit(1);
    }
    printf("Success: Created and opened file testfile with fd=%d\n", fd);

    close(fd);
}

void test_file_write_and_read()
{
    printf("Test: File Write and Read\n");

    int fd = open("testfile", O_RDWR);
    if (fd < 0)
    {
        printf("Error: Failed to open file testfile\n");
        exit(1);
    }

    char *write_data = "Hello, xv6!";
    if (write(fd, write_data, strlen(write_data)) != strlen(write_data))
    {
        printf("Error: Failed to write to file testfile\n");
        close(fd);
        exit(1);
    }
    printf("Success: Wrote to file testfile\n");

    // Mover manualmente el offset al inicio
    close(fd);
    fd = open("testfile", O_RDONLY); // Reabrir el archivo en modo lectura

    char read_data[20];
    memset(read_data, 0, sizeof(read_data));
    if (read(fd, read_data, sizeof(read_data)) < 0)
    {
        printf("Error: Failed to read from file testfile\n");
        close(fd);
        exit(1);
    }

    printf("Success: Read from file testfile: '%s'\n", read_data);
    close(fd);
}

void test_file_open_with_wrong_mode()
{
    printf("Test: File Open with Wrong Mode\n");

    int fd = open("testfile", O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Failed to open file testfile\n");
        exit(1);
    }

    char *write_data = "This should fail.";
    if (write(fd, write_data, strlen(write_data)) >= 0)
    {
        printf("Error: Write succeeded on read-only file testfile\n");
        close(fd);
        exit(1);
    }
    printf("Success: Write failed as expected on read-only file testfile\n");

    close(fd);
}

void test_file_close()
{
    printf("Test: File Close\n");

    int fd = open("testfile", O_RDWR);
    if (fd < 0)
    {
        printf("Error: Failed to open file testfile\n");
        exit(1);
    }

    close(fd);
    if (write(fd, "This should fail.", 17) >= 0)
    {
        printf("Error: Write succeeded on closed file\n");
        exit(1);
    }
    printf("Success: Write failed as expected on closed file\n");
}

int main(int argc, char *argv[])
{
    printf("Starting File System Tests\n");

    test_file_creation_and_opening();
    test_file_write_and_read();
    test_file_open_with_wrong_mode();
    test_file_close();

    printf("All tests completed successfully.\n");
    exit(0);
}
