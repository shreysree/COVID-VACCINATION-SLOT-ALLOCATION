#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include <ctime>

using namespace std;

//structure for storing details into the priority queue
struct pqueue
{
    long id;
    int category;
}pq[50];

//structure for storing details about the registered people for vaccination
struct node
{
    int disease;
    int age;
    int job;
    long aadhar;
    char name[100];
    char address[100];
    char dose_date[100];
    char blood_group[10];
    char vac_status;  //first vaccination doze status
    char gender;
    long ph;
    int category;  //to assign priority
    int batch;
    int batchcp;
    struct node *left,*right;

    int getaadhar()
    {
        return aadhar;
    }
    int getcategory()
    {
        return category;
    }

}*root,details;

int countno;

void inorder(struct node *root)  //certificate
{

       time_t now = time(0);
       tm *vac_date = localtime(&now);
       system("color 0E");
       cout<<"\n\n\n\n\n\t\t\t\t\t\tCERTIFICATE FOR COVID-19 VACCINATION\n\t\t\t\t\t\t------------------------------------\n\n\t\t\t\t\t\tBeneficiary Details\n\t\t\t\t\t\t-------------------\n";
       cout<<"\t\t\t\t\t\t\tName               : "<<root->name<<endl;
       cout<<"\t\t\t\t\t\t\tAge                : "<<root->age<<endl;
       cout<<"\t\t\t\t\t\t\tGender             : "<<root->gender<<endl;
       cout<<"\t\t\t\t\t\t\tAadhar no.         : "<<root->aadhar<<endl;
       cout<<"\n\t\t\t\t\t\tVaccination Details\n\t\t\t\t\t\t-------------------\n";
       cout<<"\t\t\t\t\t\t\tVaccine name       : COVISHIELD\n";
       if(root->vac_status=='y')
       {
           cout<<"\t\t\t\t\t\t\tDate of Dose 1     : "<<root->dose_date<<endl;
           cout<<"\t\t\t\t\t\t\tDate of Dose 2     : "<<(vac_date->tm_mday)<<"/"<<(1+vac_date->tm_mon)<<"/"<<(1900+vac_date->tm_year)<<endl;

       }
       if(root->vac_status=='n')
       {
           cout<<"\t\t\t\t\t\t\tDate of Dose 1     : "<<(vac_date->tm_mday)<<"/"<<(1+vac_date->tm_mon)<<"/"<<(1900+vac_date->tm_year)<<endl;
           cout<<"\t\t\t\t\t\t\tDue for Dose 2     : "<<(vac_date->tm_mday)<<"/"<<(1+vac_date->tm_mon+1)<<"/"<<(1900+vac_date->tm_year)<<endl;
       }
       cout<<endl<<endl;

}

int size=-1;

int parent(int i)
{
    return (i-1)/2;
}

int right(int i)
{
    return ((2*i)+1);
}

int left(int i)
{
    return ((2*i)+2);
}

void percolateup(int i)
{
    while(i>0 && pq[parent(i)].category > pq[i].category)
    {
        swap(pq[parent(i)],pq[i]);
        i=parent(i);
    }
}

//inserting into the priority queue
void insert1(pqueue p)
{
    size++;
    pq[size]=p;
    percolateup(size);
}

void clr()
{
 system("cls");
}

void percolatedown(int i)
{
    int min,l,r;
    min=i;
    l=left(i);
    r=right(i);

    if(l<=size && pq[l].category < pq[min].category)
    {
        min=l;
    }

    if(r<=size && pq[r].category < pq[min].category)
    {
        min=r;
    }

    if(min!=i)
    {
        swap(pq[i],pq[min]);
        percolatedown(min);
    }
}

//to search a record in the bst to print the certificate
void search(long aadhar1)
{
  struct node *p=root;

  while(p!=NULL)
  {
      if (p->aadhar==aadhar1)
      {
          inorder(p);
          break;

      }
      if(p->aadhar>aadhar1)
      {
          p=p->left;
      }
      else
      {
         p=p->right;
      }
  }

}
struct node*inordersuccessor(struct node* root)
{
    struct node*succ = root;

    while (succ && succ->left!=NULL)
    succ = succ->left;

    return succ;

}

struct node*deletenode(struct node* root, int key)
{
    if(root==NULL)
    {
        return root;
    }

    if(key<root->aadhar)
    root->left=deletenode(root->left,key);

    else if (key>root->aadhar)
    root->right=deletenode(root->right,key);

    else
    {
        if (root->left==NULL && root->right==NULL)
        return NULL;

        else if(root->left==NULL)
        {
            struct node*temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct node*temp=root->left;
            free(root);
            return temp;
        }
        struct node* temp=inordersuccessor(root->right);
        root->aadhar=temp->aadhar;
        root->right=deletenode(root->right,temp->aadhar);
    }
    return root;
}

int b;
int cp;

//inserting the records
int insert()
{
      struct node*p,*q;
      p=root;
      q=NULL;

      while(p!=NULL)
      {
          if(details.aadhar==p->aadhar)
          {
              return 1;
          }
          q=p;
          if(details.aadhar < p->aadhar)
          p=p->left;
          else
          p=p->right;
      }
      struct node*newnode=(struct node*)malloc(sizeof(struct node));
      newnode->aadhar=details.aadhar;
      strcpy(newnode->name,details.name);
      strcpy(newnode->address,details.address);
      strcpy(newnode->blood_group,details.blood_group);
      strcpy(newnode->dose_date,details.dose_date);
      newnode->ph=details.ph;
      newnode->gender=details.gender;
      newnode->vac_status=details.vac_status;
      newnode->job=details.job;
      newnode->disease=details.disease;
      newnode->age=details.age;
      newnode->left=NULL;
      newnode->right=NULL;

      if(q==NULL)
      root=newnode;

      else if(details.aadhar< q->aadhar)
      {
          q->left=newnode;
      }
      else
      {
          q->right=newnode;
      }
      return 0;
}

//getting details about the registered people
void getdetails()
{
    int flag;
    cout<<"\nENTER DETAILS\n-------------\n\n";

    cout<<"Enter aadhar : ";
    cin>>details.aadhar;

    cout<<"Enter name : ";
    cin>>details.name;

    cout<<"Enter address : ";
    fflush(stdin);
    cin>>details.address;

    cout<<"Enter phone number : ";
    cin>>details.ph;
    cout<<"Enter blood group  : ";
    again:
        fflush(stdin);
        cin>>details.blood_group;
       if((strcmp(details.blood_group,"A+")==0)||(strcmp(details.blood_group,"a+")==0)||(strcmp(details.blood_group,"A-")==0)||(strcmp(details.blood_group,"a-")==0)||(strcmp(details.blood_group,"B+")==0)||(strcmp(details.blood_group,"b+")==0)||(strcmp(details.blood_group,"B-")==0)||(strcmp(details.blood_group,"b-")==0)||(strcmp(details.blood_group,"O+")==0)||(strcmp(details.blood_group,"o+")==0)||(strcmp(details.blood_group,"O-")==0)||(strcmp(details.blood_group,"o-")==0)||(strcmp(details.blood_group,"AB+")==0)||(strcmp(details.blood_group,"ab+")==0)||(strcmp(details.blood_group,"AB-")==0)||(strcmp(details.blood_group,"ab-")==0))
       flag=1;
       if(flag==0)
       {
           cout<<"\nInvalid input!Enter a valid Blood Group : ";
           goto again;
        }

    cout<<"Enter first dose status (y/n) : ";
    cin>>details.vac_status;

    while(details.vac_status!='Y' && details.vac_status!='N' && details.vac_status!='y' && details.vac_status!='n')
    {
        cout<<"Re-enter first dose status : ";
        fflush(stdin);
        cin>>details.vac_status;
    }
    if(details.vac_status=='y' || details.vac_status=='Y')
    {
        cout<<"Enter date of first dose (dd/mm/year) : ";
        fflush(stdin);
        cin>>details.dose_date;
    }

    cout<<"Enter gender : ";
    fflush(stdin);
    cin>>details.gender;
    while(details.gender!='F' && details.gender!='M' && details.gender !='f' && details.gender!='m')
    {
        cout<<"Re-enter gender : ";
        cin>>details.gender;
    }

    details.age=0;
    int age1;
    cout<<"Enter age : ";
    cin>>details.age;
    if(details.age>=60)
    {
        age1=1;
    }
    else if(details.age>=45 && details.age<60)
    {
        age1=2;
    }
    else if(details.age>=18 && details.age<45)
    {
        age1=3;
    }
    else
    {
        age1=4;
    }
    while(details.age<=0)
    {
        cout<<"Invalid age!Re-enter: ";
        cin>>details.age;
    }

    details.job=5;
    while(details.job!=1 && details.job!=2)
    {
        cout<<"\n\nOCCUPATION\n----------\n1. Health care workers/front line & govt. workers\n2. Others\nEnter your choice : ";
        cin>>details.job;
    }
    details.disease=5;
    while(details.disease!=1 && details.disease!=2)
    {
        cout<<"\n\nHEALTH CONDITION\n----------------\n1. Health issues eg: diabetes/cancer/heart conditions\n2. No Ailments \nEnter your choice : ";
        cin>>details.disease;
    }
    if(details.job==1)
    {
        details.category=1;
    }
    else if(details.vac_status=='y' || details.vac_status=='n' && age1==1)
    {
        details.category=2;
    }
    else if(details.disease==1 || details.vac_status=='n' && age1==2)
    {
        details.category=3;
    }
    else
    {
        details.category=4;
    }
}

//inserting records into the file
void append()
{
     fstream f;
     f.open("covidlist.dat",ios::binary | ios::app);
     getdetails();
     f.write((char*)&details,sizeof(details));
     f.close();
}


void displaydetails()
{
    int flag;
    cout<<"DETAILS\n-------\n";

    cout<<"Aadhar      :"<<details.aadhar<<"\n";

    cout<<"Name        : "<<details.name<<"\n";

    cout<<"Address     : "<<details.address<<"\n";

    cout<<"Phone number: "<<details.ph<<"\n";

    cout<<"Blood group : "<<details.blood_group<<"\n";


    if(details.vac_status=='y' || details.vac_status=='Y')
    {
        cout<<"Date of first dose (dd/mm/year): "<<details.dose_date<<"\n";
    }

    cout<<"Gender      : "<<details.gender<<"\n";
    cout<<"Category    : "<<details.category<<"\n";
    cout<<"\n";

}

//to display details from the file
void display()
{
     ifstream f;
     f.open("covidlist.dat",ios::binary | ios::in);
     int record=0;
     while(f.read((char*)&details,sizeof(details)))
     {
     cout<<endl;
     record++;
     cout<<"RECORD "<<record<<endl;
     cout<<"--------"<<endl<<endl;
     displaydetails();
     cout<<endl;
     }
     f.close();
     cout<<"\n\n\nTotal no. of records : "<<record<<endl<<endl<<endl<<endl;
}

void display1()
{
    for(int i=0;i<=size;i++)
    {
        cout<<"job"<<i+1<<endl<<pq[i].id<<endl<<"Category : "<<pq[i].category<<endl;
    }
}

//reading records from the file and loading it into the bst
void insertbst()
{
    struct pqueue p;
    int c=0;

    ifstream f("covidlist.dat",ios::binary | ios::in);
    while(f.read((char*)&details,sizeof(details)))
    {
        insert();
        p.id=details.getaadhar();
        p.category=details.getcategory();
        insert1(p);
        details.batch=1;
        c++;
    }
    f.close();
    countno=c;
}
void insertrecords(int n)
{
    clr();
    for(int i=0;i<n;i++)
    {
        append();
        insert();
        clr();
        system("pause");

    }
    insertbst();
    //system("pause");
   // menu();
}

void del()
{
    if(b>=1)
    {
        cout<<"\n";
        search(pq[0].id);

        ifstream fin("covidlist.dat",ios::binary | ios::in);
        ofstream fout("new.dat",ios::app | ios::out);
        struct node n;
        cp++;
        if(cp==5)
        {
            b=countno/5;
            cp=0;
        }
        while(fin.read((char*)&n,sizeof(n)))
        {
             if(pq[0].id==n.getaadhar())
             {
               root=deletenode(root,pq[0].id);
             }
             else
             {
                 if(cp==0)
                    n.batch=0;
                 else
                 {
                     n.batch=1;
                     n.batchcp=cp;
                 }

                 fout.write((char*)&n,sizeof(n));
             }
        }
        countno--;
        fin.close();
        fout.close();
        remove("covidlist.dat");
        rename("new.dat","covidlist.dat");

        swap(pq[0],pq[size]);
        size--;
        percolatedown(0);

    }
    else
    {

            int n1;
            while(countno<5)
            {
                clr();
                system("color 0C");
                cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<setw(120)<<"A BATCH REQUIRES 5 PEOPLE!!!\n\n";
                cout<<setw(140)<<"Enter more number of people who have registered for the vaccination!!\n\n\n\n\n\n";
                system("pause");
                clr();
                char k;
                system("Color 0A");
                //cout<<"\nDo you wish to enter now? (y/n)  ";
                //cin>>k;
                cout<<"\nEnter the no.of people for registeration : ";
                cin>>n1;
                if((n1+countno)>=5)
                {
                     countno+=n1;
                }
            }
            b=1;
            cp=0;
            insertrecords(n1);
        }
    }

void about()
{
    cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\tABOUT\n\t\t\t\t\t-----\n\n\t\t\t\t\tIndia's COVID vaccination program incorporates recommendations of the foremost experts\n\t\t\t\t\tin the field of immunization, public health,disease control and information technology.\n\t\t\t\t\tBased on scientific and epidemiological evidence,the programme gives priority to strengthening\n\t\t\t\t\tthe country's healthcare system by protecting the professionals,health and frontline workers,\n\t\t\t\t\tmanning it,as well as protecting the most vulnerable population groups.\n";
    cout<<"\n\t\t\t\t\tVaccination slots are created based on the following criteria :-\n\t\t\t\t\t\t- First dose vaccination status\n\t\t\t\t\t\t- Domain of work (health care workers/ front line and govt. workers/others)\n\t\t\t\t\t\t- Age (60 years and above/45 years and above /18 years and above)\n\t\t\t\t\t\t- Health conditions (Underlying health issues eg: diabetes,cancer,\n\t\t\t\t\t\t  heart conditions etc./no underlying health issues)"<<endl<<endl;
    cout<<"\t\t\t\t\tThe people who have registered for the vaccine are divided into the following categories :\n\t\t\t\t\t\tCategory 1 Health care, Front Line and government workers\n\t\t\t\t\t\tCategory 2 People whose second dose has become due, people aged 60 and above\n\t\t\t\t\t\tCategory 3 People with underlying health conditions, people aged 45 years and above\n\t\t\t\t\t\tNon-Priority People who do not come under any of the above categories"<<endl<<endl<<endl;
}

void tocount()
{
    int c=0;
    struct node n1;

    ifstream f("covidlist.dat",ios::binary | ios::in);
    while(f.read((char*)&n1,sizeof(n1)))
    {
        b=n1.batch;
        c++;
        cp=n1.batchcp;
    }
    f.close();
    countno=c;
}

//to check the category of the registered person
void checkcategory(int cat)
{
    int count=0;
    ifstream f("covidlist.dat",ios::binary | ios::in);
    while(f.read((char*)&details,sizeof(details)))
    {
        if(cat==details.getcategory())
        {
            count++;
            displaydetails();

        }

    }
    cout<<"\n\n\nTotal no. of records : "<<count<<endl;
    f.close();
}


int main()
{
    int n,i,ch;
    system("color 0A");
    tocount();
    if(b==1)
    {
        insertbst();
        goto menu;
    }

    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<setw(120)<<"Enter the number of people who have registered for the vaccination : ";
    cin>>n;
    while((n+countno)<5)
    {
        clr();
        system("color 0C");
        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<setw(120)<<"A MINIMUM OF 5 PEOPLE REQUIRED!!!\n\n";
        cout<<setw(140)<<"Re-enter the number of people who have registered for the vaccination!!\n\n\n\n\n\n";
        system("pause");
        clr();
        system("Color 0A");
        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<setw(120)<<"Enter the number of people who have registered for the vaccination : ";
        cin>>n;
    }

    b=1;
    countno+=n;
    clr();
    for(i=0;i<n;i++)
    {
        append();
        insert();
        clr();
        system("pause");

    }
    insertbst();
    //system("pause");
    //display();
    system("color 0B");
    menu:
    clr();

    while(1)
    {
        cout<<"\n\n\n\n\n\n\n"<<setw(100)<<"VACCINATION CENTRE";
        cout<<"\n\n\n\n\n\n";
        cout<<setw(100)<<"1. DETAILS REGARDING VACCINATION"<<endl<<endl;
        cout<<setw(108)<<"2. PEOPLE REGISTERED FOR THE VACCINATION"<<endl<<endl;
        cout<<setw(94)<<"3. CATEGORY BASED DIVISION"<<endl<<endl;
        cout<<setw(82)<<"4. VACCINATION"<<endl<<endl;
        cout<<setw(75)<<"5. EXIT"<<"\n\n\n\n\n\n\n";
        cout<<"Please Enter your choice :"<<" ";
        cin>>ch;
        if(ch==5)
        {
            clr();
            exit(0);
        }
        else if(ch==1)
        {
            clr();
            about();
            system("pause");
            clr();
        }
        else if(ch==2)
        {
            clr();
            display();
            system("pause");
            clr();
        }

        else if(ch==3)
        {
             int choice =0;
             clr();
             cout<<"1. CATEGORY 1"<<"\n\n";
             cout<<"2. CATEGORY 2"<<"\n\n";
             cout<<"3. CATEGORY 3"<<"\n\n";
             cout<<"4. CATEGORY 4"<<"\n\n";
             cout<<"Please Enter your choice : ";
             cin>>choice;
             clr();
             checkcategory(choice);
             system("pause");
             clr();

         }

        else if(ch==4)
        {
            clr();
            del();
            system("pause");
            system("color 0B");
            goto menu;

        }
    }
}
