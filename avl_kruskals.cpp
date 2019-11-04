#include<iostream>
#include<bits/stdc++.h>
#include <iomanip>
#include<vector>
#include<fstream>
#include<string.h>
#include<stdio.h>
#define maxi 1000000
using namespace std::chrono;
using namespace std;


struct node
{
struct node * left;
struct node * right;
long height;
long weight;
long from;
long to;
};


long flag=0,h,q,copyq;

struct node * newnode(long val,long from, long to)
{
struct node * node= new struct node ();
node->left=NULL;
node->right=NULL;
node->weight=val;
node->height=1;
node->from=from;
node->to=to;
return (node);
}

double count2=0;

////Finding height of nodes
long height_node(struct node * temp)
{
    if(temp==NULL)
    {
        return 0;
    }
    return temp->height;
}


////For single rotation left left
struct node* single_rotateLL(struct node *z)
{
struct node *y,*temp;

y=z->left;

temp=y->right;

y->right=z;

z->left=temp;

z->height=max(height_node(z->left),height_node(z->right))+1;



y->height=max(height_node(y->left),z->height)+1;

return y;
}



////For single rotation right right
struct node* single_rotateRR(struct node *z)
{
struct node *y,*temp;
 
y=z->right;

temp=y->left;

y->left=z;

z->right=temp;

z->height=max(height_node(z->left),height_node(z->right))+1;

y->height=max(height_node(y->right),z->height)+1;




return y;
}



////For Double_rotation left right
struct node* Double_rotationLR(struct node *z)
{

struct node *y,*temp;

y=z->left;

z->left=single_rotateRR(y);

z=single_rotateLL(z);

return z;
}




///////For Double_rotation right left
struct node * Double_rotationRL(struct node *z)
{
    
struct node *y,*temp;

y=z->right;

z->right=single_rotateLL(y);

z=single_rotateRR(z);

return z;
}

long count1=0;

void inorder1(struct node * temp,vector<struct node *>&sort_arr)
{
    
    if(temp!=NULL)
    {
    inorder1(temp->left,sort_arr); 
    //cout<<temp->from<<" "<<temp->to<<" "<<temp->weight<<endl;
    sort_arr.push_back(temp);
    inorder1(temp->right,sort_arr);
    }
    return;
}


double c=0;
struct node *insert(struct node * temp,long val,long from,long to) 
{
    
if(temp==NULL)
{
  temp=newnode(val,from,to);
  if(!temp)
      cout<<"error in allocation";
}
else
{
    if(val<=temp->weight)
    {
       temp->left=insert(temp->left,val,from,to);
       if((height_node(temp->left)-height_node(temp->right))==2)
       {
           
           if(temp->left->weight>=val)
           {
               
               temp=single_rotateLL(temp);
           }
           else
           {
              temp= Double_rotationLR(temp);
           }
           
       }

    }
    else if(val>temp->weight)
    {
        temp->right=insert(temp->right,val,from,to);
         if((height_node(temp->right)-height_node(temp->left))==2)
         {
           if(temp->right->weight<val)
           {
              temp=single_rotateRR(temp);
           }
           else
           {
               temp=Double_rotationRL(temp);
           }
           
         }
    }
}       
       temp->height=max(height_node(temp->left),height_node(temp->right))+1;
       return temp;
}
struct node * find_min(struct node *temp)
{
    struct node * prev;
    while(temp!=NULL)
    {
       prev=temp;
       temp=temp->left; 
    }
    return prev;
    
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

int main()
{
    
    int count1=0;
    ofstream f_out;
    f_out.open("avl.txt");
    //freopen("outputavl.txt", "w", stdout);
   
     clock_t s_val=clock();
    while(count1<200)
    {
    struct node * root=NULL;
     // cout<<"hello"<<endl;
      long vertices,edges,weight,from,to;
      vector<struct node *>sort_arr;
      //cout<<"straswrw><"<<endl;
      
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
    char temp1[lines.length()+1];
    char temp[lines.length()+1];
    strcpy(temp,lines.c_str());
    strcpy(temp1,lines.c_str());
    //cout<<"temp "<<temp<<endl;
    char * tok=strtok(temp1," ");
    from=atoi(tok);
    //cout<<"feo "<<from<<endl;
    tok=strtok(NULL," ");
    to=atoi(tok);
    //cout<<"fto "<<to<<endl;
    tok=strtok(NULL," ");
    weight=atoi(tok);
    //cout<<"fweig "<<weight<<endl;
    //weights should be less than 10000
    root=insert(root,weight,from,to);
    }
    //cout<<res<<endl;
    //cout<<duration.count()<<endl; 
    fin.close();
    //cout<<"c "<<count1<<endl;
    count1++;
    long edge_count=0,added,mst_weight=0;
    //calling inorder for storing edges based on weights
    inorder1(root,sort_arr);
        for(auto x:sort_arr)
        {
           //cout<<x->from<<" "<<x->to<<" "<<x->weight<<endl;
           added=unio(x->from,x->to,size,parent);
           //cout<<"this is added"<<added<<endl;
           if(added==1)
           {
           // cout<<x->weight<<endl;
      //         cout<<"added"<<endl;
             mst_weight=mst_weight+x->weight;
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
    //double res=((double)clock()-s_val)/CLOCKS_PER_SEC;
    f_out<<duration.count()<<endl;

    }
    
}
