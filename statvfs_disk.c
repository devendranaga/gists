#include <stdio.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct statvfs vfs_;
    int ret;

    if (argc != 2) {
        fprintf(stderr, "<%s> filename\n", argv[0]);
        return -1;
    }

    ret = statvfs(argv[1], &vfs_);
    if (ret != 0) {
        fprintf(stderr, "failed to statvfs [%s] error : %s\n",
                            argv[1], strerror(errno));
        return -1;
    }

    double total_disk = (vfs_.f_blocks * vfs_.f_frsize * 1.0) / (1024 * 1024 * 1024);
    double available = (vfs_.f_bfree * vfs_.f_frsize * 1.0) / (1024 * 1024 * 1024);

    fprintf(stderr, "total %f GB available %f GB used %f GB\n", total_disk, available, total_disk - available);
    fprintf(stderr, "used disk size [%s] %f\n", argv[1], ((total_disk - available) / total_disk) * 100);
    fprintf(stderr, "free disk size [%s] %f\n", argv[1], ((available) / total_disk) * 100);
    return 0;
}

