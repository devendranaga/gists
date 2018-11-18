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

    fprintf(stderr, "<statvfs> :\n");
    fprintf(stderr, "\t block size %lu\n", vfs_.f_bsize);
    fprintf(stderr, "\t fragment size %lu\n", vfs_.f_frsize);
    fprintf(stderr, "\t blocks %lu\n", vfs_.f_blocks);
    fprintf(stderr, "\t number of free blocks %lu\n", vfs_.f_bfree);
    fprintf(stderr, "\t number of free blocks for unprivileged user %lu\n", vfs_.f_bavail);
    fprintf(stderr, "\t number of inodes %lu\n", vfs_.f_files);
    fprintf(stderr, "\t number of free inodes %lu\n", vfs_.f_ffree);
    fprintf(stderr, "\t number of free inodes for unprivileged user %lu\n", vfs_.f_favail);
    fprintf(stderr, "\t file system id %lu\n", vfs_.f_fsid);
    fprintf(stderr, "\t mount flags %lx\n", vfs_.f_flag);
    fprintf(stderr, "\t filename max len %lu\n", vfs_.f_namemax);

    return 0;
}

