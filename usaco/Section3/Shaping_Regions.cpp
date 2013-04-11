/*
ID: fairy tail
PROG: rect1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

//#define maxsize 10010
//#define fin cin
//#define fout cout
 ifstream fin("rect1.in");
 ofstream fout("rect1.out");

struct rect
{
  int x[2],y[2];
  int color;
};

int num[2510];
int n;
queue<rect>v;

void Read()
{
  rect temp;
  fin >> temp.x[1] >> temp.y[1] >> n;
  temp.x[0]=temp.y[0]=0;
  temp.color=0;
  v.push(temp);
  memset(num,0,sizeof(num));
  num[0]=temp.x[1]*temp.y[1];
}

int setrect(int x0, int y0, int x1, int y1)
{
	rect in;
	in.x[0]=x0;
	in.y[0]=y0;
	in.x[1]=x1;
	in.y[1]=y1;
	in.color=0;
	v.push(in);
	return (x1-x0)*(y1-y0);
}

void dfs(int i)
{
  if(i==n)
  	return;
  rect temp;
  fin>>temp.x[0]>>temp.y[0]>>temp.x[1]>>temp.y[1]>>temp.color;
  dfs(i+1);
  int size = v.size();
  int k=0;
  rect now;
  while(k < size)
  {
  	k++;
    now = v.front();
    v.pop();
    if(temp.x[0]>=now.x[1]|| temp.x[1]<=now.x[0] ||
       temp.y[0]>=now.y[1]|| temp.y[1]<=now.y[0])
    {
        v.push(now);//关键
    	continue;
    }
    int ans = (now.x[1]-now.x[0])*(now.y[1]-now.y[0]);
    if(now.x[0]<temp.x[0])
    {
    	ans-=setrect(now.x[0],max(now.y[0],temp.y[0]),temp.x[0],now.y[1]);
    }
    if(temp.y[0]>now.y[0])
    {
    	ans-=setrect(now.x[0],now.y[0],min(now.x[1],temp.x[1]),temp.y[0]);
    }
    if(temp.x[1]<now.x[1])
    {
    	ans-=setrect(temp.x[1],now.y[0],now.x[1],min(now.y[1],temp.y[1]));
    }
    if(now.y[1]>temp.y[1])
    {
    	ans-=setrect(max(now.x[0],temp.x[0]),temp.y[1],now.x[1],now.y[1]);
    }
    num[temp.color]+=ans;
    num[0]-=ans;
  }
}


int main()
{
    Read();
    dfs(0);
    num[1]+=num[0];
    for(int i=1; i<=2500; i++)
    {
    	if(num[i]!=0)
    		fout << i << ' ' << num[i] << endl;
    }
	return 0;
}
/*
先考虑最简单的情况，当前的覆盖矩形完全包含在
待分割矩形中，这种情况的矩形会被切成四块，
按这种形状：  *
			  *
			  *
			  ***********
			  *	  *
			  *	  *
		***********	
				  *
				  *
				  *	
另外的四种情况是，覆盖矩形与待分割矩形部分重合
此时可以看做是按上面情况切割后的矩形被压缩为0后
的情况.
还有采用倒序矩形处理是简化操作的关键。				  
*/