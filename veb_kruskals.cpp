#include<iostream>
#include<vector>
#include<math.h>
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

void insert_node(struct veb * temp,int x,int u)
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
int k=sqrt(u);
int high=x/k;
int low=x%k;
if(temp->u > 2 )
 {
     //cout<<"hhjassa"<<endl;
     //cout<<temp->cluster[high]<<endl;
  if(temp->cluster[high]->min == -1)
   {
    //cout<<"hello worls"<<endl;
    insert_empty_node(temp->cluster[high],low);
    insert_node(temp->summary,high,k);
   }
   else
   {
       insert_node(temp->cluster[high],low,k);
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

int delete_element(struct veb *temp,int x,int u)
{
    int high=x/sqrt(u);
    int low=x%(int)sqrt(u);
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
   temp->max=temp->min;
   }
}  
else
{ 
    int first_cluster,summary_max;
if (x == temp->min)
{
first_cluster=veb_minimum(temp->summary);
x=first_cluster*sqrt(u)+veb_minimum(temp->cluster[first_cluster]);
temp->min=x;
}
delete_element(temp->cluster[high],low,temp->cluster[high]->u);
if ((veb_minimum(temp->cluster[high]))== -1)
{
 delete_element(temp->summary,high,temp->summary->u);
   if (x == temp->max)
   {
    summary_max =veb_maximum(temp->summary);
      if(summary_max == -1)
        temp->max=temp->min;
      else 
     { 
     temp->max=summary_max*sqrt(u)+veb_maximum(temp->cluster[summary_max]);
     }
   }
}
else if(x == temp->max)
temp->max =(high*sqrt(u)+veb_maximum(temp->cluster[high]));

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
cout<<"from and to"<<from<<" "<<to<<endl;
x=find_union(from,parent);
y=find_union(to,parent);
cout<<"val of x and y"<<x<<" "<<y<<endl;
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
    cout<<"hi"<<endl;
size[y]=size[x]+size[y];
parent[x]=y;
}
cout<<"helo"<<endl;
return 1;
}
}


int main()
{
    int choice,val,u;
    cout<<"enter size of universe"<<endl;
    cin>>u;
    struct veb * root=(struct veb *)malloc(sizeof(struct veb));
    allocate(root,u);
   // insert_node(root,0,u);
    long vertices,edges,v_from,v_to,v_weight,edge_count=0;
    cin>>vertices>>edges;
    long parent[vertices],size[vertices],sum=0;
    for(int i=0;i<vertices;i++)
    {
        parent[i]=i;
        size[i]=1;
    }
    //weights should be less than 10000
    vector<vector<pair<int,int>>>v(10000);
    for(int i=0;i<edges;i++)
    {
        cin>>v_from>>v_to>>v_weight;
        v[v_weight].push_back({v_from,v_to});
        insert_node(root,v_weight,u);
    }
    while(edge_count<=vertices-1)
    {
        int weight=veb_minimum(root);
        while(v[weight].size())
        {
           int v1=v[weight][0].first;
           int v2=v[weight][0].second;
           long response=unio(v1,v2,size,parent);
           cout<<"response"<<response<<endl;
           if(response!=-1)
            {
             sum=sum+weight;
             edge_count++;
            }
           v[weight].erase(v[weight].begin());
           cout<<"size "<<v[weight].size()<<endl;
        }
        cout<<"weight "<<weight<<endl;
        delete_element(root,weight,u);
        cout<<"edge_cout "<<edge_count<<endl;
    } 
    cout<<"min_spanning cost "<<sum<<endl;
    /*
while(1)
{
    
    cout<<"enter choice 1)insert 2)min 3)max 4)delete 5)successor 6)predecessor 7)exit"<<endl;
    cin>>choice;
    switch(choice)
    {
        case 1:
        cout<<"enter element"<<endl;
        cin>>val;
        insert_node(root,val,u);
        break;
        case 2:
        cout<<veb_minimum(root)<<endl;
        break;
        case 3:
        cout<<veb_maximum(root)<<endl;
        break;
        case 4:
        cin>>val;
        delete_element(root,val,u);
        break;
        case 5:
        cout<<"enter element to which you want successor "<<endl;
        cin>>val;
        cout<<successor(root,val,u)<<endl;
        break;
        case 7:
        //print(root,0);
        break;
    }

}*/
}