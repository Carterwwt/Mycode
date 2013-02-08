#include<iostream>
using namespace std;
const int MaxVertexes=20;  //���Ķ�����
const int b=10000;
template <class Type> class Graph ;
struct ArcNode{//����߽��
    friend class Graph <class Type>;
    int adjvex;                     //�ͱߣ��򻡣����������һ���������
    int weight;                     //�ߣ��򻡣��ϵ���Ϣ
    ArcNode *nextarc ;              //ָ����һ���߽���ָ��
ArcNode(int v,int w ) : adjvex( v ),weight(w),nextarc( NULL ){ }
};//���캯��
template <class Type>
struct VertexNode{// ���嶥����
friend class Graph <class Type>;
    Type data;                      //�������Ϣ
    ArcNode *firstarc ;             //ָ�������ö���ı�����
};
template <class Type>class Graph
{
 VertexNode<Type> * VTable;      //�����
    int CurrentNumVertexes;         //��ǰ�Ķ�����
    int CurrentNumArcs;             //��ǰ�ıߣ��򻡣���
public:
 int GetVertexPos( const Type &v );// ȡ����v�������е�λ��
    Graph(Type v[],int num=MaxVertexes); //���캯��
    Type GetValue(int v);            //ȡͼ�ж���v��ֵ���������v�������򷵻ؿ�
    int Getweight(int v1,int v2);   //ȡ�ߣ��򻡣��ϵ�Ȩֵ
    int GetFirstNeighbor(int v);    //ȡͼ�ж���v�ĵ�һ���ڽӵ����š���������ڷ���-1
int GetNextNeighbor(int v1, int v2);  //ȡͼ����һ���ڽӵ�
int Arcs[MaxVertexes][MaxVertexes];//�������¼ÿ���ߵ���Ϣ
    int InVertex(Type &v);          //��ͼ�в�����
    int InsertArc(int v1, int v2,int w);//��ͼ�в���������v1��v2�ı߻򻡣�w����Ϣ
    int NumberOfVertexes( ){return CurrentNumVertexes; } //���ص�ǰ�Ķ�����
    int NumberOfArcs(){ return CurrentNumArcs; }  //���ص�ǰ�ıߣ��򻡣���
 int *dist;                      //���·����������
    int *InDegree;                  //������飬��¼ÿ����������
    int *path;                      //���·��������
 int *s;                         //���·���յ�����
void link();                   //����ڽ�����
   void DFS(const int v,int visited[]);//�����������
   void DFTraverse ();            //��ȱ���
   void TopologicalOrder();       //��������
void ShortestPath(int n,int v);//���·��
};
///////////////////////////////////////////////////////////////////////////////////
template<class Type>int Graph<Type>::
GetVertexPos(const Type &v ){    //���ݶ���v���Ҹö������ڽӱ��е�λ��
 for(int i=0;i<CurrentNumVertexes;i++)
  if(VTable[i].data==v)   return i;
  return -1;
}
template<class Type>Graph<Type>::Graph( Type v[] , int num=MaxVertexes) :
CurrentNumVertexes(0), CurrentNumArcs(0)
{
 Type tail, head;
    int i=0,e,h,t,w,p=0;
 while(p<MaxVertexes){
  for(int j=0;j<MaxVertexes;j++){
   Arcs[p][j]=b;
   if(p==j)  {Arcs[p][j]=0;}
  }
  p++;
 }
 InDegree=new int[MaxVertexes];
    VTable=new VertexNode<Type>[MaxVertexes];//���������
    for(i=0;i<num;i++)             //�����������Ϣ
 {  InVertex(v[i]);            //�ڶ�����в��붥��v[i]
  InDegree[i]=0;
 }
 cout<<"����ߵ�����:";  cin >> e;//����ߵ�����
 cout<<endl;
 for(i=0;i< e;i++){             //���������
  cout<<"�����"<<i+1<<"����:(��ͷ,��β,Ȩֵ)";
  cin>>tail>>head>>w;        //����һ����
  int j=GetVertexPos(head);
  while((t=GetVertexPos(tail))==-1)
   cout<<"����Ķ���(tail)������";
  while((h = GetVertexPos(head ))==-1)
          cout<<"����Ķ���(head)������";
        InsertArc (t,h,w);        //����һ����
     InDegree[j]++;            //����j����ȼ�1
  cout<<endl;
 }
}
template<class Type>Type Graph<Type>::
GetValue(int v){                 //ȡͼ�ж���v��ֵ���������v�����ڣ��򷵻ؿ�
 if(v>=0&&v<CurrentNumVertexes) return VTable[v].data;
 return NULL;
}
template<class Type>int Graph<Type>::
Getweight(int v1,int v2)
{//ȡ���Զ���v1��v2Ϊ���˵�ı��ϵ�Ȩֵ
 if(v1>=0&&v1<CurrentNumVertexes&&v2>=0&&v2<CurrentNumVertexes){
      ArcNode *p=VTable[v1].firstarc;
   while(p!=NULL){
    if(p->adjvex==v2)  {return p->weight;}
    else               {p=p->nextarc;    }
   }
 } return NULL;
}
template<class Type>int Graph<Type>::
GetFirstNeighbor(int v){//���Ҷ���v�ĵ�һ���ڽӶ����λ��
 if(v>=0&&v<CurrentNumVertexes){
       ArcNode *p=VTable[v].firstarc;
    if(p!=NULL)  return p->adjvex;
    }
 return -1;
}
template<class Type>int Graph<Type>::
GetNextNeighbor(int v1,int v2){//���Ҷ���v1����v2֮�����һ���ڽӶ��㣬��������ڷ���-1
 if (v1!=-1){
  ArcNode *p=VTable[v1].firstarc;
  while(p!=NULL){
   if(p->adjvex==v2&&p->nextarc!=NULL)
    return p->nextarc->adjvex;//������һ���ڽӶ������ڽӱ��е�λ��
   else p=p->nextarc;
  }
    }
    return -1;//û�в鵽��һ���ڽӶ��㷵��-1
}

template<class Type>int Graph<Type>::
InsertArc(int v1,int v2,int w)
{//��ͼ�в��뻡<v1,v2>
  if(v1>=0&&v1<CurrentNumVertexes){
   Arcs[v1][v2]=w;
   ArcNode *newnode =new ArcNode(v2,w);
   ArcNode *h=VTable[v1].firstarc;
   if(h!=NULL){
    ArcNode *p=h;
    while(h!=NULL&&h->adjvex<v2){
     p=h;     h=h->nextarc;
    }
    newnode->nextarc=p->nextarc;
    p->nextarc=newnode;
    return 1;
   }
   VTable[v1].firstarc=newnode;
   return 1;
  }
  return -1;
}
template<class Type>int Graph<Type>::
InVertex(Type &v)
{//��ͼ�в��붥�㣬����ɹ��򷵻�1�����򷵻�0
  if(CurrentNumVertexes<MaxVertexes-1){//�������δ��
   VTable[CurrentNumVertexes].data=v;
   VTable[CurrentNumVertexes].firstarc=NULL;
   CurrentNumVertexes++;           return 1;
  }
  return -1;
}
///////////////////////////////////////////////////////////////////////
//������ʵ��Ҫ��ĺ���
//����ڽӱ�
template<class Type>void Graph<Type>::link(){
 cout<<"����ڽӱ�:"<<endl;
 for(int i=0;i<CurrentNumVertexes;i++){
  cout<<GetValue(i);
  int a=GetFirstNeighbor(i);
  if(a!=-1) cout<<"->"<<GetValue(a)<<Getweight(i,a);
  for(int j=a;j!=-1;j=a){
   a=GetNextNeighbor(i,j);
  if(a!=-1) cout<<"->"<<GetValue(a)<<Getweight(i,a);
  }
  cout<<endl;
 }
}
//��������
template<class type>void Graph<type>::
TopologicalOrder()
{
 int m=0;//mΪ����Ķ���������ʼֵΪ0
 for(int i=0;i<CurrentNumVertexes;i++){
  for(int n=0;n<CurrentNumVertexes;n++){
   if(InDegree[n]==0){
    m++;//����Ķ�������1
    cout<<VTable[n].data<<endl;
    InDegree[n]=-1;
    for(int t=0;t<CurrentNumVertexes;t++){
     if(n>=0&&n<CurrentNumVertexes){
      if(t>=0&&t<CurrentNumVertexes){
       if(Arcs[n][t]!=0&&Arcs[n][t]!=b)
                      InDegree[t]--;
      }
     }
                 }
    for(int h=0;h<CurrentNumVertexes;h++){
     cout<<InDegree[h]<<"  ";
    }  cout<<endl;        break;
   }
  }
 }
 if(m<CurrentNumVertexes)  cout<<"AOV�������л�·�����򻷣���"<<endl;
}
//��ȱ���
template<class Type>
void Graph<Type>::
DFS(const int v,int visited[ ])
{
   cout<< VTable[v].data<<"  ";        //���ʶ��� v
    visited[v] =1;                     //����v �����ʱ��
    int w = GetFirstNeighbor (v);
    while (w != -1) {                  //������ w ����
        if (!visited[w]) DFS (w,visited);
        w = GetNextNeighbor(v,w);
    }                              //�ظ���� v �������ڽӶ���
}
template<class Type>
void Graph <Type> ::
DFTraverse ()
{
 int i, n = NumberOfVertexes() ;    //ȡͼ�Ķ������
    int * visited = new int [n];       //������ʱ������ visited
    for ( i = 0; i < n; i++ )
        visited [i] = 0;               //���ʱ������ visited ��ʼ��
    for ( i = 0; i < n; i++ )             //��ͼ�е�ÿһ����������ж�
      if (!visited [i])  DFS (i, visited );
    delete[ ]visited;                   //�ͷ� visited
}
//�����·��
template<class Type>void Graph<Type>::
ShortestPath(int n,int v)
{
 int min,u;
 dist=new int[n];   s=new int[n];   path=new int[n];
 for(int j=0;j<n;j++){
  dist[j]=Arcs[v][j];         s[j]=0;
  if(j!=v&&dist[j]<MaxVertexes) path[j]=v;
  else path[j]=-1;           s[v]=1;
 }
 for(int i=0;i<=n-1;i++){
  min=MaxVertexes;      u=v;
  for(int j=0;j<n;j++)
   if(!s[j]&&dist[j]<min){
    u=j;    min=dist[j];
   }
   s[u]=1;
   for(int w=0;w<n;w++)
     if(!s[w]&&dist[u]+Arcs[u][w]<dist[w])
     {
      dist[w]=dist[u]+Arcs[u][w];
      path[w]=u;
     }
     if(v!=i&&dist[i]!=10000&&v!=path[i])
     cout<<GetValue(v)<<"������"<<GetValue(i)<<"�����·����:"<<GetValue(v)<<GetValue(path[i])<<GetValue(i)<<endl;
                    else if(v!=i&&dist[i]!=10000)
                    cout<<GetValue(v)<<"������"<<GetValue(i)<<"�����·����:"<<GetValue(path[i])<<GetValue(i)<<endl;
  }
       for(int m=0;m<n;m++)
  cout<<GetValue(v)<<"������"<<GetValue(m)<<"�����·��������:"<<dist[m]<<endl;

}
//������
void main(){

 char op;
 do{
  int m,i=0,j=0,w;
     char a[20],c;
  cout<<"�������붥��ĸ���:";   cin>>m;
  for(i=0;i<m;i++){
   cout<<"�������"<<j<<"�����:";
   cin>>a[i]; cout<<endl;  j=j+1;
  }
  Graph<char>G(a,m);
  G.link();
  cout<<"��ȱ���:"<<endl;
  G.DFTraverse();
  cout<<endl;
  cout<<"��������:"<<endl;
  G.TopologicalOrder();
  cout<<endl;
  cout<<"������С·����Դͷ���:"<<endl;
  cin>>c;
  w=G.GetVertexPos(c);
  G.ShortestPath(m,w);
loop:cout<<"�Ǽ�����(Y or N)"<<endl;
  cin>>op;
  if(op=='N'||op=='n')break;
  if(op!='Y'&&op!='y'&&op!='N'&&op!='n')goto loop;
 }while(op=='Y'||op=='y');
}
