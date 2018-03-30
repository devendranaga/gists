#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
   int ret;

   if (argc != 2) {
       printf("%s <filename>\n", argv[0]);
       return -1;
   }

   ret = chmod(argv[1], S_IRUSR | S_IWUSR | S_IXUSR |
                        S_IRGRP | S_IWGRP | S_IXGRP |
                        S_IROTH | S_IWOTH | S_IXOTH);
   if (ret != 0) {
       printf("failed to chmod [%s] \n", argv[1]);
       return -1;
   }

   return 0;
}
