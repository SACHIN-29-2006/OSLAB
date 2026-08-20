#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
   pid_t m1,m2,w1,w2,w3;
   printf("p (Root process)\n");
   printf("PID : %d\n",getpid());
   printf("Parent PID : %d\n\n",getppid());
   m2=fork();
   if(m2<0)
   {
      perror("First fork failed");
      return 1;
   }
   else if(m2==0)
   {
      printf("m2(Child of p)\n");
      printf("PID : %d\n",getpid());
      printf("Parent PID : %d\n\n",getppid());
      w3=fork();
      if(w3<0)
      {
	 perror("Second fork failed");
	 return 1;
      }
      else if(w3==0)
      {
	 printf("w3(child of m2)\n");
	 printf("PID : %d\n",getpid());
	 printf("Parent PID : %d\n\n",getppid());
      }
      else
      {
	 wait(NULL);
      }
   }
   else
   {
      wait(NULL);
      m1=fork();
      if(m1<0)
      {
	 perror("Third fork failed");
	 return 1;
      }
      else if(m1==0)
      {
	 printf("m1(child of p)\n");
	 printf("PID : %d\n",getpid());
	 printf("Parent PID : %d\n\n",getppid());
	 w1=fork();
	 if(w1<0)
	 {
	    perror("Fourth fork failed");
	    return 1;
	 }
	 else if(w1==0)
	 {
	    printf("w1(child of m1)\n");
	    printf("PID : %d\n",getpid());
	    printf("Parent PID : %d\n\n",getppid());
	 }
	 else
	 {
	    wait(NULL);
	 }
      }
      else
      {
	 wait(NULL);
         w2=fork();
         if(w2<0)
         {
	    perror("Fifth fork failed");
	    return 1;
         }
         else if(w2==0)
         {  
	    printf("w2(child of m1)\n");
	    printf("PID : %d\n",getpid());
	    printf("Parent PID:%d\n\n",getppid());
         }
         else
         {
	    wait(NULL);
	 } 
      }
      return 0;
   }
}
