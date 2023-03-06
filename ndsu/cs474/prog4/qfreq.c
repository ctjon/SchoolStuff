int spawn(){
  int fd[2],pid;

  pipe(fd);
  if ((pid = fork()) == -1) perror("fork"),exit(1);
  close(pid ? 0 : 1);
  dup(fd[(pid ? 0 : 1)]);
  close(fd[0]);
  close(fd[1]);
  return pid;
}

int main(){ 
  if (spawn()) execlp("sort","sort","-n","-r",0L);
  if (spawn()) execlp("uniq","uniq","-c",0L);
  if (spawn()) execlp("sort","sort",0L);
  execlp("prep","prep",0L);
  exit(0);
}
