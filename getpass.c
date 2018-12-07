#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "<%s> username\n", argv[0]);
        return -1;
    }

    struct passwd *pw;

    pw = getpwnam(argv[1]);
    if (!pw) {
        return -1;
    }

    printf("name %s\n", pw->pw_name);
    printf("password %s\n", pw->pw_passwd);
    printf("uid %d\n", pw->pw_uid);
    printf("gid %d\n", pw->pw_gid);
    printf("user informatino %s\n", pw->pw_gecos);
    printf("home %s\n", pw->pw_dir);
    printf("shell %s\n", pw->pw_shell);

    return 0;
}


