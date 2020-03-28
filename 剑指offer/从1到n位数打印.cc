void print1ton(int n){
  if(n<=0) return;
  string number(n+1,"");
  for(int i=0;i<10;i++){
    number[0] = i+'0';
    permute(number,n,0);
  }
}
void permute(string &number,int len,int idx){
  if(idx == len-1){
    print(number) //这里不能直接print，需要把前面的0去掉
    return;
  }
  for(int i=0;i<10;i++){
    number[idx+1] = i+'0';
    permute(number,len,idx+1);
  }
}
