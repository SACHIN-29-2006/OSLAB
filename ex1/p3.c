#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
   pid_t p2,p3,p4;
   printf("p1 (Root process)\n");
   printf("pid : %d\n",getpid());
   printf("parent pid : %d\n \n",getppid());
   p2=fork();
   if(p2<0)
   {
      perror("first fork failed");
      return 1;
   }
   else if(p2==0)
   {
      printf("p2 (child of p1)\n");
      printf("pid : %d\n",getpid());
      printf("parent pid : %d\n \n",getppid());
      p3=fork();
      if(p3<0)
      {
	 perror("second fork failed");
	 return 1;
      }
      else if(p3==0)
      {
	 printf("p3 (child of p2)\n");
	 printf("pid : %d\n",getpid());
	 printf("parent pid : %d\n",getppid());
      }
      else
      {
	 wait(NULL);
      }
   }
   else
   {
      wait(NULL);
      p4=fork();
      if(p4<0)
      {
	 perror("third fork failed");
	 return 1;
      }
      else if(p4==0)
      {
	 printf("p4 (child of p1)\n");
	 printf("pid : %d\n",getpid());
	 printf("parent pid : %d\n",getppid());
      }
      else
      {
	 wait(NULL);
      }
   }
   return 0;
}
