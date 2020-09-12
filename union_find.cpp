#include<bits/stdc++.h>
#include<malloc.h>
#include<fstream>
#include<stdio.h>
#define max 1000000
using namespace std;
using namespace std::chrono;
void unio(int,int);
int find(int);
int *arr,*weight,n;

struct node
{
    long from;
    long to,weight;
};

long find_union(long x,long parent[])
{
long temp;
if(parent[x]==x)
{
return x;
}
else
{
temp=find_union(parent[x],parent);
return temp;
}
}

long unio(long from ,long to,long size[],long parent[])
{
long x,y,i;
//cout<<"from and to"<<from<<" "<<to<<endl;
x=find_union(from,parent);
y=find_union(to,parent);
//cout<<"val of x and y"<<x<<" "<<y<<endl;
if(x==y)
return -1;
else
{
if(size[x]>size[y])
{
size[x]=size[x]+size[y];
parent[y]=x;
}
else
{
size[y]=size[x]+size[y];
parent[x]=y;
}
return 1;
}
}

bool comp(struct node a,struct node b)
{
    if(a.weight<b.weight)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

int main()
{
    
    int count1=0;
    ofstream f_out;
    f_out.open("union_find.txt");
    //freopen("outputunion_f.txt", "w", stdout);
    clock_t s_val=clock();
    while(count1<200)
    {
    vector<struct node>v;
     // cout<<"hello"<<endl;
    long vertices,edges; 
    auto start = high_resolution_clock::now();
    char file[256];
    string lines;
    //cout<<":hellworls"<<endl;
    int c=count1;
    sprintf(file,"/home/jayakrishna/aps/py/file_%d.txt",c);
    //cout<<file<<endl;
    ifstream fin;
    fin.open(file);
    getline(fin,lines);
    //cout<<lines<<endl;
    vertices=stoi(lines);
    //cout<<"vertices "<<vertices<<endl;
    getline(fin,lines);
    edges=stoi(lines);
    //cout<<edges<<" ";
    //cout<<"edges "<<edges<<endl;
    long parent[vertices],size[vertices],sum=0;
    for(int i=0;i<vertices;i++)
    {
        parent[i]=i;
        size[i]=1;
    }
    while(getline(fin,lines))
    {
    //cout<<"lines "<<lines<<endl;
    struct node a;
    char temp1[lines.length()+1];
    char temp[lines.length()+1];
    strcpy(temp,lines.c_str());
    strcpy(temp1,lines.c_str());
    //cout<<"temp "<<temp<<endl;
    char * tok=strtok(temp1," ");
    a.from=atoi(tok);
    //cout<<"feo "<<from<<endl;
    tok=strtok(NULL," ");
    a.to=atoi(tok);
    //cout<<"fto "<<to<<endl;
    tok=strtok(NULL," ");
    a.weight=atoi(tok);
    v.push_back(a);
    }
    //cout<<res<<endl;
    //cout<<duration.count()<<endl; 
    fin.close();
    //cout<<"c "<<count1<<endl;
    count1++;
    long edge_count=0,added,mst_weight=0;
    //calling inorder for storing edges based on weights
    sort(v.begin(),v.end(),comp);
        for(auto x:v)
        {
           //cout<<x->from<<" "<<x->to<<" "<<x->weight<<endl;
           added=unio(x.from,x.to,size,parent);
           //cout<<"this is added"<<added<<endl;
           if(added==1)
           {
           // cout<<x->weight<<endl;
      //         cout<<"added"<<endl;
             mst_weight=mst_weight+x.weight;
             edge_count++;
             if(edge_count==vertices-1)
             {
                 break;
             }
            // cout<<" "<<mst_weight<<endl;
           }
        }

    //cout<<mst_weight<<endl;
    //free(root);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double res=((double)clock()-s_val)/CLOCKS_PER_SEC;
    f_out<<duration.count()<<endl;

    }
    
}