#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

int lTreeStatus=-1;
char* str;
int constx,consty,rootData=0;
int secondTime=0;
int predecessor=-1;
int searchFlag=-1;

void bound_fill(int x,int y,int f_col,int b_col)
{
	if(getpixel(x,y)!=b_col && getpixel(x,y)!=f_col)
	{
		putpixel(x,y,f_col);
		bound_fill(x+1,y,f_col,b_col);
		bound_fill(x,y+1,f_col,b_col);
		bound_fill(x-1,y,f_col,b_col);
		bound_fill(x,y-1,f_col,b_col);
	}
}

void flood_fill(int x,int y,int f_col,int b_col)
{
	if(getpixel(x,y)==b_col)
	{
		putpixel(x,y,f_col);
		flood_fill(x+1,y,f_col,b_col);
		flood_fill(x,y+1,f_col,b_col);
		flood_fill(x-1,y,f_col,b_col);
		flood_fill(x,y-1,f_col,b_col);
	}
}


int sign(double x)
{
	if(x<0)
		return -1;
	else if(x==0)
		return 0;
	else
		return 1;
}
void BRES(int x1,int y1,int x2,int y2)
{
	double x,y,xd,yd,e,s1,s2,ex_c;
	int i=0;
	if((x1==x2)&&(y1==y2))
		putpixel(x1,y1,WHITE);
	else
	{
		xd=abs(x2-x1);
		yd=abs(y2-y1);

		x=x1;
		y=y1;

		s1=sign(x2-x1);
		s2=sign(y2-y1);

		if(yd>xd)
		{
			ex_c=yd;
			yd=xd;
			xd=ex_c;
			ex_c=1;
		}
		else
			ex_c=0;

		e=2*xd-yd;

		do
		{
			putpixel(x,y,WHITE);
			while(e>=0)
			{
				if(ex_c==1)
					x=x+s1;
				else
					y=y+s2;

				e=e-2*xd;
			}
			if(ex_c==1)
				y=y+s2;
			else
				x=x+s1;

			e=e+2*yd;
			i++;
		}while(i<=xd);
	}
}
void DDA(int x1,int y1,int x2,int y2){

	int i;
	double yd=0,xd=0,x=0,y=0,len=0;

	if(x1==x2 && y1==y2)
		putpixel(x1,y1,WHITE);
	else{
		xd=abs(x2-x1);
		yd=abs(y2-y1);

		if(xd>=yd)
			len=xd;
		else
			len=yd;

		xd=(x2-x1)/len;
		yd=(y2-y1)/len;

		x=x1+0.5*sign(xd);
		y=y1+0.5*sign(yd);


		i=1;
		while(i<=len)
		{
			putpixel(int(x),int(y),WHITE);
			x=x+xd;
			y=y+yd;
			i=i+1;
		}
	}
}


int xfactor(int no)
{
	int xfact=0;
	if(no<10)
		xfact=2;
	else if(no>9 && no<100)
		xfact=6;
	else
		xfact=10;
	return xfact;
}
void newnode_animation(int x,int y,int data)
{

	int newx=constx,newy=consty;
	itoa(data,str,10);

	while(x!=newx)
	{
		if(newx<=(constx*3)+2)
		{
			circle(constx,consty,20);
			outtextxy(constx-xfactor(data),consty-3,str);
		}
		setcolor(BLACK);
		delay(10);
		outtextxy(newx-xfactor(data),newy-3,str);
		circle(newx,newy,20);

		if(x>newx)
		newx+=1;
		else
		newx-=1;

		setcolor(WHITE);
		circle(newx,newy,20);
		outtextxy(newx-xfactor(data),newy-3,str);
	}
	while(y!=newy)
	{
		setcolor(BLACK);
		delay(5);
		outtextxy(newx-xfactor(data),newy-3,str);
		circle(newx,newy,20);

		newy-=1;

		setcolor(WHITE);

		if(newy==getmaxy()-30 || newy==getmaxy()-72)
			DDA(0,getmaxy()-50,getmaxx(),getmaxy()-50);


		circle(newx,newy,20);
		outtextxy(newx-xfactor(data),newy-3,str);
	}
}


class TreeNode
{
    int treeData,x,y;
    TreeNode* left;
    TreeNode* right;

    public:
    friend TreeNode* createNode(int data,TreeNode* left,TreeNode* right);
    friend TreeNode* insertNode(TreeNode* root,int data);
    friend void preorder(TreeNode* root);
    friend void inorder(TreeNode* root);
    friend void postorder(TreeNode* root);
    friend TreeNode* leftmost(TreeNode* root);
    friend void search(TreeNode* root, int data);
    friend int succ(TreeNode* root,TreeNode* n);
    friend TreeNode* deleteNode(TreeNode* root, int data);
};
TreeNode* mainRoot;

TreeNode* createNode(int data,TreeNode* left,TreeNode* right)
{
    TreeNode* newnode=new TreeNode;
    newnode->treeData=data;
    newnode->left=left;
    newnode->right=right;
    return newnode;
}

TreeNode* createTree(TreeNode* root,int *nodes,int size)
{
    for(int i=0;i<size;i++)
    {
	if(nodes[i]==-9999)
		continue;
	root=insertNode(root,nodes[i]);
    }
    return root;
}

TreeNode* insertNode(TreeNode* root, int data)
{
    TreeNode* newnode=createNode(data,NULL,NULL);
    if(root==NULL)
    {
	root=newnode;
	{
		root->x=getmaxx()/2;
		root->y=50;
		rootData=root->treeData;
		setcolor(GREEN);
		circle(root->x,root->y,20);
		setcolor(WHITE);
		if(secondTime==0)
			newnode_animation(root->x,root->y,root->treeData);
		itoa(root->treeData,str,10);
		circle(root->x,root->y,20);
		setcolor(BLACK);
		outtextxy(root->x-(xfactor(root->treeData)),root->y-3,str);
		bound_fill(root->x,root->y,WHITE,WHITE);
		outtextxy(root->x-(xfactor(root->treeData)),root->y-3,str);
		setcolor(WHITE);
	}

	return root;
    }

    TreeNode* temp=root;
    while(temp!=NULL)
	{
		if(temp->treeData>root->treeData)
			lTreeStatus=0;
		else if(temp->treeData<root->treeData)
			lTreeStatus=1;
		else
			lTreeStatus=-1;

		setcolor(GREEN);
		circle(temp->x,temp->y,20);

		if(secondTime==0)
			delay(1000);

		setcolor(WHITE);
		circle(temp->x,temp->y,20);

		if(newnode->treeData<temp->treeData)
		{
			if(temp->left==NULL)
			{
				temp->left=newnode;

				//DESIGNING
				{
					if(temp==root)
					{
						DDA(temp->x-20,temp->y+10,temp->x-60,temp->y+30);
						temp->left->x=temp->x-80;
						temp->left->y=temp->y+40;
					}
					else
					{
						if(lTreeStatus==0)
						{
							DDA(temp->x-5,temp->y+20,temp->x-15,temp->y+45);
							temp->left->x=temp->x-22;
							temp->left->y=temp->y+65;
						}
						else
						{
							DDA(temp->x-15,temp->y+15,temp->x-50,temp->y+50);
							temp->left->x=temp->x-65;
							temp->left->y=temp->y+65;
						}
					}

					setcolor(GREEN);
					circle(temp->left->x,temp->left->y,20);
					setcolor(WHITE);
					if(secondTime==0)
						newnode_animation(temp->left->x,temp->left->y,temp->left->treeData);
					circle(temp->left->x,temp->left->y,20);circle(temp->left->x,temp->left->y,20);
					itoa(temp->left->treeData,str,10);
					outtextxy(temp->left->x-xfactor(temp->left->treeData),temp->left->y-3,str);
				}

				break;
		       }

			temp=temp->left;
		}
		else if(newnode->treeData>temp->treeData)
		{
			if(temp->right==NULL)
			{
				temp->right=newnode;

				//DESIGNING
				{
					if(temp==root)
					{

						lTreeStatus=0;
						BRES(temp->x+20,temp->y+10,temp->x+60,temp->y+30);
						temp->right->x=temp->x+80;
						temp->right->y=temp->y+40;

					}
					else
					{
						if(lTreeStatus==1)
						{
							BRES(temp->x+5,temp->y+20,temp->x+15,temp->y+45);
							temp->right->x=temp->x+22;
							temp->right->y=temp->y+65;
						}
						else
						{
							BRES(temp->x+15,temp->y+15,temp->x+50,temp->y+50);
							temp->right->x=temp->x+65;
							temp->right->y=temp->y+65;
						}
					}

					setcolor(GREEN);
					circle(temp->right->x,temp->right->y,20);
					setcolor(WHITE);
					if(secondTime==0)
						newnode_animation(temp->right->x,temp->right->y,temp->right->treeData);
					circle(temp->right->x,temp->right->y,20);

					itoa(temp->right->treeData,str,10);
					outtextxy(temp->right->x-xfactor(temp->right->treeData),temp->right->y-3,str);
				}

				break;
			}

			temp=temp->right;
		}
		else
		{
			break;
		}
	}
	return root;
}

void color_circle(int x,int y,int data,int color,int bcolor,int tcolor)
{
	setcolor(bcolor);
	outtextxy(x-xfactor(data),y-3,str);
	setcolor(tcolor);
	flood_fill(x,y,color,bcolor);
	itoa(data,str,10);
	outtextxy(x-xfactor(data),y-3,str);
	setcolor(WHITE);
}


TreeNode* leftmost(TreeNode* root)
{
	TreeNode* temp=root;
	while(temp->left!=NULL)
		temp=temp->left;

	return temp;
}

TreeNode* deleteNode(TreeNode* root, int data)
{
	if(root==NULL)
		return NULL;

	if(data<root->treeData)
		root->left=deleteNode(root->left,data);
	else if(data>root->treeData)
		root->right=deleteNode(root->right,data);
	else if(data==root->treeData)
	{
		if(root->left==NULL && root->right==NULL)
		{
			delete root;
			root=NULL;
		}
		else if(root->left==NULL)
		{
			TreeNode* temp=root;
			root=root->right;
			delete temp;
		}
		else if(root->right==NULL)
		{
			TreeNode* temp=root;
			root=root->left;
			delete temp;
		}
		else
		{
			TreeNode* temp=leftmost(root->right);
			root->treeData=temp->treeData;
			root->right=deleteNode(root->right,temp->treeData);
		}
	}
	else
	{
		cout<<"\nNode not found..\n";
	}
	return root;
}


int succ(TreeNode *root, TreeNode* n)
{
	TreeNode* succ=NULL;

	while(n!=NULL)
	{
		if(n->treeData<root->treeData)
		{
			succ=root;
			root=root->left;
		}
		else if(n->treeData>root->treeData)
			root=root->right;
		else
			break;
	}

	if(succ==NULL)
		return -1;
	else
		return succ->treeData;

}

void search(TreeNode *root,int data)
{
	if(root!=NULL)
	{
		search(root->left,data);
		if(root->treeData==data)
		{
			searchFlag=1;
			cout<<"\nSearch Successfull...";
			cout<<"\nInorder \nPredecessor: "<<predecessor;
			cout<<"\n\nInorder \nSuccessor: ";
			if(root->right==NULL)
				cout<<succ(mainRoot,root);
			else
				cout<<leftmost(root->right)->treeData;

			cout<<"\n";

			if(root->treeData==rootData)
				color_circle(root->x,root->y,root->treeData,YELLOW,WHITE,BLACK);
			else
				color_circle(root->x,root->y,root->treeData,YELLOW,BLACK,BLACK);

			delay(1000);

		}
		predecessor=root->treeData;
		search(root->right,data);
	}
}

void preorder(TreeNode *root)
{
	if(root!=NULL)
	{
		cout<<root->treeData<<" ";
		if(root->treeData==rootData)
			color_circle(root->x,root->y,root->treeData,YELLOW,WHITE,BLACK);
		else
			color_circle(root->x,root->y,root->treeData,YELLOW,BLACK,BLACK);

		delay(1000);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(TreeNode *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout<<root->treeData<<" ";
		if(root->treeData==rootData)
			color_circle(root->x,root->y,root->treeData,YELLOW,WHITE,BLACK);
		else
			color_circle(root->x,root->y,root->treeData,YELLOW,BLACK,BLACK);
		delay(1000);
		inorder(root->right);
	}
}
void postorder(TreeNode *root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->treeData<<" ";
		if(root->treeData==rootData)
			color_circle(root->x,root->y,root->treeData,YELLOW,WHITE,BLACK);
		else
			color_circle(root->x,root->y,root->treeData,YELLOW,BLACK,BLACK);
		delay(1000);
	}
}
int main()
{
	TreeNode *root=NULL;
	char tryAgain='y';
	int size,gd=DETECT,gm=DETECT,choice,data;

	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");

	for(int r=350;r>0;r--)
	{
		circle(300,250,r);
		outtextxy(280,250,"WELCOME");
		delay(7);
		cleardevice();
	}

	cout<<"\nEnter the number of NODES: ";
	cin>>size;

	int nodes[50],searchData;
	cout<<"Enter the NODES: ";
	for(int i=0;i<size;i++)
		cin>>nodes[i];

	do{

	clrscr();
	setbkcolor(BLACK);
	cleardevice();

	root=NULL;
	DDA(0,getmaxy()-50,getmaxx(),getmaxy()-50);
	constx=20;
	consty=getmaxy()-25;
	root=createTree(root,nodes,size);

	mainRoot=root;

	outtextxy(getmaxx()-150,15,"Required:");
	circle(getmaxx()-20,20,20);
	flood_fill(getmaxx()-20,20,YELLOW,BLACK);
	outtextxy(getmaxx()-150,60,"Default:");
	circle(getmaxx()-20,65,20);

	cout<<"Menu\n";
	cout<<"1.Insert\n";
	cout<<"2.Delete\n";
	cout<<"3.Preorder\n";
	cout<<"4.Inorder\n";
	cout<<"5.Postorder\n";
	cout<<"6.Search\n";
	cout<<"7.Exit\n";
	cout<<"Enter your choice: ";
	cin>>choice;

	switch(choice)
	{
		case 1:
			cout<<"\nEnter the data \nto be inserted: ";
			cin>>data;
			root=insertNode(root,data);
			nodes[size]=data;
			size++;
			secondTime=1;
			continue;
		case 2:
			cout<<"\nEnter the data \nto be deleted: ";
			cin>>data;
			root=deleteNode(root,data);
			secondTime=1;

			for(int i=0;i<size;i++)
			{
				if(nodes[i]==data)
					nodes[i]=-9999;
			}

			continue;
		case 3:
			cout<<"\nPreorder: \n";
			preorder(root);
		break;
		case 4:
			cout<<"\nInorder: \n";
			inorder(root);
		break;
		case 5:
			cout<<"\nPostorder: \n";
			postorder(root);
		break;
		case 6:
			cout<<"\nEnter the data \nto be searched: ";
			cin>>searchData;
			search(root,searchData);
			if(searchFlag==-1)
				cout<<"\nSearch Failed...\n";
		break;
		case 7:
			closegraph();
			exit(1);
		break;
	}
	cout<<"\nDo you want to \ntry again?(Y/N):";
	cin>>tryAgain;
	secondTime=1;
	}while(tryAgain=='Y'||tryAgain=='y');
	return 0;
}