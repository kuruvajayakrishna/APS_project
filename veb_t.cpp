#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#define maxi 1000000
using namespace std::chrono;
using namespace std;
struct veb
{
    long u,min,max;
    struct veb *summary;
    struct veb **cluster;

};

void * allocate(struct veb * temp,int u)
{
    temp->u=u;
    temp->min=-1;
    temp->max=-1;
    if(u==2)
    {
        temp->summary=NULL;
        temp->cluster=NULL;
    }
    else
    {
       int val=sqrt(u);
       struct veb *new_node=(struct veb *)malloc(sizeof(struct veb ));
       allocate(new_node,val);
       temp->summary=new_node;
       temp->cluster=(struct veb **)malloc(sizeof(struct veb *)*val);
       for(int i=0;i<val;i++)
       {
           temp->cluster[i]=(struct veb *)malloc(sizeof(struct veb));
           allocate(temp->cluster[i],val);
       }
    }

}

void insert_empty_node(struct veb *v,int val)
{
    v->max=val;
    v->min=val;
}

void insert_node(struct veb * temp,int x)
{
if(temp->min==-1)
{
    insert_empty_node(temp,x);
}
else 
{
   // cout<<"hi"<<endl;
if(x<temp->min)
{
    int t_val=temp->min;
    temp->min=x;
    x=t_val;
   // cout<<"hello"<<endl;
}
int k=sqrt(temp->u);
int high=x/k;
int low=x%k;
if(temp->u > 2 )
 {
     //cout<<"hhjassa"<<endl;
     //cout<<temp->cluster[high]<<endl;
  if(temp->cluster[high]->min == -1)
   {
    //cout<<"hello worls"<<endl;
    insert_node(temp->summary,high);
    insert_empty_node(temp->cluster[high],low);
   }
   else
   {
       insert_node(temp->cluster[high],low);
   }
   
 }
}
if(temp->max < x)
{
    temp->max=x;
}
}


int veb_minimum(struct veb * temp) 
{
    return temp->min;
}

int veb_maximum(struct veb *temp) 
{
    return temp->max;
}

int delete_element(struct veb *temp,int x)
{
    int k=sqrt(temp->u);
if (temp->min == temp->max)
    {
    temp->min=-1;
    temp->max=-1;
    }
else if (temp->u ==2)
{

   if (x == 0)
   {
    temp->min=1;
   }
   else
   { 
   temp->min=0;
   }
    temp->max=temp->min;
}  
else
{ 
if (x == temp->min)
{
int first_cluster=veb_minimum(temp->summary);
//cout<<"f_c "<<first_cluster<<endl;
x=first_cluster*k+veb_minimum(temp->cluster[first_cluster]);
//cout<<"x_f_c "<<x<<endl;
temp->min=x;
}
delete_element(temp->cluster[x/k],x%k);
if ((veb_minimum(temp->cluster[x/k]))== -1)
{
 delete_element(temp->summary,x/k);
   if (x == temp->max)
   {
    int summary_max =veb_maximum(temp->summary);
    //cout<<"sum_max "<<summary_max<<endl;
      if(summary_max == -1)
        temp->max=temp->min;
      else 
     { 
     temp->max=summary_max*k+veb_maximum(temp->cluster[summary_max]);
     }
   }
}
else if(x == temp->max)
temp->max =((x/k)*k)+veb_maximum(temp->cluster[x/k]);

}
}
int successor(struct veb *temp,int x ,int u)
{
    int max_low,offset,succ_cluster;
    int high=x/sqrt(u);
    int low=x%(int)sqrt(u);
    if (temp->u == 2)
    { 
     if (x == 0 && temp->max == 1)
     return 1;
     else
     return -1;
    }
    else if (temp->min !=-1 and x < temp->min)
     return temp->min;
    else
    { 
      max_low=veb_maximum(temp->cluster[high]);
      if( max_low !=-1 && low < max_low)
      {
       offset=successor(temp->cluster[high],low,temp->cluster[high]->u);
       return (high*sqrt(u)+offset);
      }
     else
     {
      succ_cluster =successor(temp->summary,high,temp->summary->u); 
      if (succ_cluster == -1)
       {
       return -1;
       }
      else
      { 
       offset=veb_minimum(temp->cluster[succ_cluster]);
       return (succ_cluster*sqrt(u)+offset);
      }
    }
}
}

void print(struct veb *V, int tabs=0)
{
	if(V != NULL)
	{
		for(int i =0; i < tabs; ++i)
			cout<<"		";
		cout<<"SUMMARY: "<<V->u<<" ( "<<V->min<<" , "<<V->max<<" ) "<<endl;
		if(V->u != 2)
			print(V->summary, tabs + 1);
		if(V->u != 2)
		{
			for(int i =0; i <= tabs; ++i)
				cout<<" 	";
			cout<<"CLUSTER: "<<V->u<<endl;
			int k = sqrt(V->u);
			for(int i =0; i < k; ++i)
				print(V->cluster[i], tabs + 1);
		}
	}
	
}

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
parent[x]=temp;
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
  //  cout<<"hi"<<endl;
size[y]=size[x]+size[y];
parent[x]=y;
}
//cout<<"helo"<<endl;
return 1;
}
}

int main()
{
    int count1=0;
    ofstream f_out;
    f_out.open("veb.txt");
    //freopen("outputvb.txt", "w", stdout);
    while(count1<200)
    {
     vector<vector<pair<int,int>>>v(100000);
    int choice,val,u;
    long vertices,edges,v_from,v_to,v_weight,edge_count=0,l=0;
    //cout<<"straswrw><"<<endl;
     struct veb * root=(struct veb *)malloc(sizeof(struct veb));
     allocate(root,65536);
    //cout<<"sasa"<<endl;
    auto start = high_resolution_clock::now();
    clock_t s_val=clock();
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
    char temp1[lines.length()+1];
    char temp[lines.length()+1];
    strcpy(temp,lines.c_str());
    strcpy(temp1,lines.c_str());
    //cout<<"temp "<<temp<<endl;
    char * tok=strtok(temp1," ");
    v_from=atoi(tok);
    //cout<<"feo "<<v_from<<endl;
    tok=strtok(NULL," ");
    v_to=atoi(tok);
    //cout<<"fto "<<v_to<<endl;
    tok=strtok(NULL," ");
    v_weight=atoi(tok);
   // cout<<"fweig "<<v_weight<<endl;
    //weights should be less than 10000
    v[v_weight].push_back({v_from,v_to});
    insert_node(root,v_weight);
    l++;
    }
    while(edge_count<vertices-1)
    {
        int weight=veb_minimum(root);
        while(v[weight].size())
        {
           int v1=v[weight][0].first;
           int v2=v[weight][0].second;
           long response=unio(v1,v2,size,parent);
           //cout<<"response"<<response<<endl;
           if(response!=-1)
            {
             //cout<<weight<<endl;
             sum=sum+weight;
             edge_count++;
            }
           v[weight].erase(v[weight].begin());
           //cout<<"size "<<v[weight].size()<<endl;
        }
       // cout<<"weight "<<weight<<endl;
        delete_element(root,weight);
        //cout<<"edge_cout "<<edge_count<<endl;
    } 
    //cout<<sum<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    //double res=((double)clock()-s_val)/CLOCKS_PER_SEC;
    f_out<<duration.count()<<endl;
    //cout<<res<<endl;
    //cout<<duration.count()<<endl; 
    fin.close();
    //cout<<"c "<<count1<<endl;
    free(root);
    count1++;
    
    }
 f_out.close();
}