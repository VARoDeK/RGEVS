#include<windows.h>
#include<process.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<time.h>
#include<dir.h>
#include<math.h>

using namespace std;
COORD coord={0,0};
void gotoxy(int,int);
void clrscr();
void delay(int);
void set_window_size();
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
const short name_size=50;/*Use to insert line. Just to make the appearance of the output, good.*/
const short password_size=50;
short masterflag=0;
char master_password[18]={"squirrelANDrabbit"};
char path_name[50];
char folder_path[50];
char year[5];
char xborderstyle=220;
char yborderstyle=219;
char global_password[password_size+1]; //used for storing any password.

inline void box();
inline void ani();



void create_path_name(char[]/*year*/,char[]/*filename*/);
void create_folder_path(char[]);//year
inline void line()
{cout<<" ------------------------------------------------------------------------------";}

   /* When we type character in place of integer,
   the stream fails and sometimes an infinite loop runs.
   This function will check the stream and will
   accept only when integer is typed.*/
long double only_number_input(char a[],short,short); // 'a' is the statement which is typed to tell the user to give input. for ex- a[]="Enter your roll no:. and x,y are the coordinates ".
void input_year(char a[],short,short);// 'a' is the statement which is typed to tell the user to give input. for ex- a[]="Enter your roll no:. and x,y are the coordinates ".
void error(char a[],char b[]);//use to display errors, 'a' defines error and 'b' defines comments.
short user_interface();
short master_control_interface();
inline void all_border();
void delete_records_of_year();


/*-------------------------------------------------------------------------*/
struct adno
{
long double adno;
} adno_global;
short input_adno(long double/*admission no*/,char[]/*year*/);
short check_adno(long double/*admission no*/,char[]/*year*/);
short delete_adno(long double/*admission no*/,char[]/*year*/);
void display_adno();

/*-------------------------------------------------------------------------*/
struct voting_status
{
 char year[24];
};
void show_voting_status();
inline void votestat_border();
void voting_status_input(char[]);
int check_voting_status(char[]);
void delete_voting_status();

inline void voting_border(short);
void voting();
short vote(char fil[],short sid, short no_of_cand, short size_of_cand); //return 0 if not done, 1 if done

/*-------------------------------------------------------------------------*/
struct candidate
{
 char year[5];         //year of election.
 char name[name_size+1];        //name of the candidate.
 char post_name[name_size+1];   //name of the post.
 char section[2];         // section in which the student is.

 short post_id;  //unique id for every post.
 short stud_id;  //unique id for every student of a particular post.
 short standard; //standard in which the student studies.

 long double admission_no;   //admission no of the student.
 long no_of_votes;    // no of votes of the student.
 }cand_global;
 void candidate_initializer(candidate &);
 void candidate_registeration_form();// candidate fills the form.
 void register_registeration_form();// form finally saved in database.
 void delete_registeration_form();//delete a particular record.
 void display_registeration_form();
 inline void display_registeration_form_border();
 void display_candidate_records();//display records of candidates.
 void delete_candidate_record(short);
 void modify_candidate_record(short);

/*-------------------------------------------------------------------------*/
struct post_id
{
 short id;
 char post[name_size+1];
 }post_global;

void posts_interface(); //interface to show options for show posts, add, modify
short no_of_posts();
inline void post_border();//border for posts_interface
void display_posts();
void add_post();
void modify_post();
void delete_post();
short input_folder_record();
short delete_folder_record(short id);//id is name of folder keeping record of a particular post.
void show_folder_record();
/*-------------------------------------------------------------------------*/
struct password
{
 char open_pass[password_size+1];
 char mod_pass[password_size+1];
 char vote_pass[password_size+1];
  int open_size;
  int mod_size;
  int vote_size;
 }pass_global;

char* password_input();
short check_pass(char a[], int x);//x=1,open, x=2,modify, x=3,vote, return 1= correct password
short add_passwords();
short modify_passwords();
void display_passwords();
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

int main()
{
clrscr();
short flag=4,flag2=0,help_desk=0; //it should be non zero if directory is not made my mkdir;
ofstream fout;

/*-------------------------------------------------------------------------*/
fout.open("c:\\RGEVS\\oooo.DAT");
if(!fout)
{fout.close();
    flag=mkdir("c:\\RGEVS");

  if(flag!=0)
  {
   cout<<"\n\n\tERROR: RGEVS not able to form directory in C drive.";
   getch(); rmdir("c:\\RGEVS");
   exit(0);}

}

else
{fout.close(); remove("c:\\RGEVS\\oooo.DAT");}

/*-------------------------------------------------------------------------*/

flag=4;

flag=mkdir("c:\\RGEVS\\oooo");

if(flag!=0)
{
 cout<<"\n\n\tERROR: RGEVS not able to form directory inside RGEVS folder in C drive.";
 getch(); rmdir("c:\\RGEVS\\oooo");
 exit(0);}

rmdir("c:\\RGEVS\\oooo");
/*-------------------------------------------------------------------------*/
set_window_size();
cout<<"\n\n\n\n\n\t\tMaximize window \n\n\tPress any key.";
getch();
/*-------------------------------------------------------------------------*/
ofstream fout4;
fout4.open("c:\\RGEVS\\VOTESTAT.DAT",ios::app|ios::binary);
fout4.close();
/*--------------------------------------------------------------------------*/
clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();
 gotoxy(6,6);
 cout<<"Enter anything if running this software for fist time on this system.";
 gotoxy(4,12);
 cout<<"Input Password to Open: ";
 password_input();
 if(strcmp(global_password,"squirrelANDrabbit")==0)
 {
  masterflag=23;
  goto m_interface;
 }
 masterflag=0;
 flag=check_pass(global_password,1);
 if(flag!=1)
 {
  gotoxy(33,14);
  cout<<"WRONG PASSWORD";
  getch();
  exit(0);
 }

 u_interface:
     flag=user_interface();
      if(flag==1)
      {
       register_registeration_form();
       goto u_interface;
      }

      else if(flag==2)
      {
       delete_records_of_year();
       goto u_interface;
      }

      else if(flag==3)
      {
       voting();
       goto u_interface;
      }

      else if(flag==4)
      {
       display_candidate_records();
       goto u_interface;
      }

      else if(flag==5)
      {
       modify_passwords();
       goto u_interface;
      }

      else if(flag==6)
      {
          clrscr();
       box();
       ani();
       goto u_interface;
      }

      else if(flag==7)
      {
       display_posts();
       goto u_interface;
      }

      else if(flag==8)
      {
        clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();
      gotoxy(4,12);
 cout<<"Input Password to Modify: ";
 password_input();
 flag2=check_pass(global_password,2);
 if(flag2!=1)
 {
  gotoxy(33,14);
  cout<<"WRONG PASSWORD";
  getch();
  goto u_interface;
 }
 posts_interface();
 goto u_interface;
      }

      else if(flag==0)
        exit(0);
     else
        goto u_interface;







 m_interface:
     flag=master_control_interface();
      if(flag==1)
      {
       register_registeration_form();
       goto m_interface;
      }

      else if(flag==2)
      {
       delete_records_of_year();
       goto m_interface;
      }

      else if(flag==3)
      {
       voting();
       goto m_interface;
      }

      else if(flag==4)
      {
       display_candidate_records();
       goto m_interface;
      }

      else if(flag==5)
      {
       modify_passwords();
       goto m_interface;
      }

      else if(flag==7)
      {
       display_posts();
       goto m_interface;
      }

      else if(flag==8)
      {
      posts_interface();
      goto m_interface;
      }

      else if(flag==9)
      {
       display_passwords();
       goto m_interface;
      }

      else if(flag==10)
      {
       show_voting_status();
       goto m_interface;
      }

      else if(flag==11)
      {
       delete_voting_status();
       goto m_interface;
      }

      else if(flag==12)
      {
          clrscr();
          gotoxy(19,3);
          cout<<"Ryan Ghaziabad Electronic Voting System.";
          gotoxy(1,4);
          line();
          gotoxy(1,22);
          line();
          gotoxy(4,23);
          cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
          all_border();
          input_year("Enter the year for which you want to see record: ",4,12);
       show_folder_record();
       goto m_interface;
      }

      else if(flag==13)
      {
       display_adno();
       goto m_interface;
      }

      else if(flag==0)
        exit(0);
     else
        goto m_interface;







getch();
 return 0;
}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

long double only_number_input(char a[],short x, short y)
{
 long double b;

 start:
 gotoxy(x,y);
 cout<<"                                                          ";
 gotoxy(x,y);
 cout<<a;
 cin>>b;

 if(!cin)
 {
  cin.clear();
  cin.ignore(9999,'\n');
  gotoxy(x,y+2);
  cout<<"The value should be Numeral";
  goto start;
  }

  gotoxy(x,y+2);
  cout<<"                              ";
return b;
}
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

inline void all_border()
{
short i;
::xborderstyle=220;
   ::yborderstyle=219;
 for(i=1; i<=80; i++)
 {
  gotoxy(i,1);
  cout<<::xborderstyle;
  gotoxy(i,24);
  cout<<::xborderstyle;
  if(kbhit())
  getch();
  }

 for(i=2; i<=24; i++)
 {
  gotoxy(1,i);
  cout<<::yborderstyle;
  gotoxy(80,i);
  cout<<::yborderstyle;
  if(kbhit())
  getch();
  }
 }

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void candidate_registeration_form()// year of election.
{
 char ch;
 char cname[name_size+1];
 short i,flag,pid,n;
 ifstream fin;

start1:
    candidate_initializer(cand_global);
clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(26,5);
 cout<<"Candidate Registration form.";
 gotoxy(1,6);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 input_year("Enter the year of election: ",4,8);
 flag=check_voting_status(::year);
 if(flag==1)
 {
  gotoxy(4,14);
  cout<<"VOTING FOR THE YEAR IS ALREADY DONE!";
  gotoxy(20,18);
  cout<<"Press any key.";
  getch();
  return;
 }

 strcpy(cand_global.year,::year);

 create_folder_path(::year);
 mkdir(folder_path);


 idinput:
 pid=only_number_input("Enter Post ID (ID of post for which you are standing): ",4,10);
  n=no_of_posts();

 fin.open("c:\\RGEVS\\POST_ID.DAT");

 if(!fin)
 {
  if(masterflag!=0)
        error("Could not open c:\\RGEVS\\POST_ID.DAT", "While reading the file to fill candidate form.");
  else
  error("Could not Identify Post","Or you have not saved any record for posts.");
  fin.close();
  return;
 }

  for(i=0;i<n;i++)
  {
   if(kbhit())
    getch();
   fin.read((char*)&post_global,sizeof(post_global));
   if(pid==post_global.id)
   break;
  }
  fin.close();
  if(i==n)
  {
    gotoxy(10,12);
    cout<<"Post ID invalid.";
    goto idinput;
  }
  cand_global.post_id=pid;
  strcpy(cand_global.post_name,post_global.post);

  naminput:
  gotoxy(4,12);
  cout<<"                                       ";
  gotoxy(4,12);
  cout<<"Enter Candidate name: ";
  cout.flush();
  cin.ignore();
  for(i=0;i<name_size;i++)
  {if(kbhit())
        getch();
    cand_global.name[i]='\0';}
   cin.getline(cand_global.name,name_size,'\n');
   if(cand_global.name[0]=='\0')
    goto naminput;

   for(i=0; cand_global.name[i]!='\0';i++)
   {
    if(isalpha(cand_global.name[i]) || cand_global.name[i]=='.' || cand_global.name[i]==' ')
    continue;
    else
    goto naminput;
   }
    if(isalpha(cand_global.name[0]))
    {if(islower(cand_global.name[0]))
            cand_global.name[0]=toupper(cand_global.name[0]);}

     strcpy(cname,cand_global.name);


  stdinput:
    cand_global.standard=only_number_input("Enter the class in which you are studying: ",4,14);
    if(cand_global.standard<1 || cand_global.standard>12)
      { gotoxy(10,16);
        cout<<"Input a valid class.";
        goto stdinput;}

  secinput:
  gotoxy(4,16);
  cout<<"                                                     ";
  gotoxy(4,16);
  cout<<"Enter your section: ";
  cin>>cand_global.section;
   if(!isalpha(cand_global.section[0]))
   { gotoxy(10,18);
        cout<<"Enter a valid section.";
        goto secinput;}
   if(islower(cand_global.section[0]))
            cand_global.section[0]=toupper(cand_global.section[0]);


    adnoimput:
   gotoxy(4,18);
  cout<<"                                                     ";
  cand_global.admission_no=only_number_input("Enter Admission Number: ",4,18);
  if(cand_global.admission_no-floor(cand_global.admission_no)!=0 || cand_global.admission_no<1)
  {
    gotoxy(10,20);
    cout<<"Enter a valid admission number.";
    goto adnoimput;
  }

  flag=check_adno(cand_global.admission_no,year);
  if(flag==1)
  {
   gotoxy(10,20);
    cout<<"Number already used.";
    goto adnoimput;
  }

  if(flag==0||flag==-1)
  {
   flag=input_adno(cand_global.admission_no,::year);
   if(flag==0)
    return;
  }

      strcpy(cand_global.name,cname);


cand_global.no_of_votes=0;
cand_global.stud_id=-14;
 }

/*-------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------*/


void candidate_initializer(candidate &c)
{
 short i,j;
 j=name_size+1;

 for(i=0; i<j; i++)
 {
  if(kbhit())
  getch();
  c.name[i]='\0';
  c.post_name[i]='\0';}

 c.section[0]='\0'; c.section[1]='\0';

 c.post_id=-1;
 c.stud_id=-1;
 c.standard=-1;

 c.admission_no=-1;
 c.no_of_votes=0;
 }


/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
short user_interface()
{
 short i,j=5 ,flag;
 char pointer=175;//16,
char point=249,ch;

start:
 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 gotoxy(32,5);
 cout<<point<<" Fill a new form.";
 gotoxy(32,7);
 cout<<point<<" Start voting.";
 gotoxy(32,9);
 cout<<point<<" View previous records/forms.";
 gotoxy(32,11);
 cout<<point<<" Delete all the forms/ records of a year.";
 gotoxy(32,13);
 cout<<point<<" Modify Passwords.";
 gotoxy(32,15);
 cout<<point<<" Help Desk.";
 gotoxy(32,17);
 cout<<point<<" Show Posts in the council.";
 gotoxy(32,19);
 cout<<point<<" Add / Modify / Delete Posts in council.";
 gotoxy(32,21);
 cout<<point<<" Exit.";
 all_border();

 i=30;

cursor:
  gotoxy(i,j);
  cout<<pointer<<"\b";
   re:
   ch=getch();
   if(ch==72 && j>5)
   {
    gotoxy(i,j);
    cout<<" ";
    j-=2;
    goto cursor;
    }

   else if(ch==72 && j==5)
   {
    gotoxy(i,j);
    cout<<" ";
    j=21;
    goto cursor;
    }

   else if(ch==80 && j<21)
   {
    gotoxy(i,j);
    cout<<" ";
    j+=2;
    goto cursor;
    }

   else if(ch==80 && j==21)
   {
    gotoxy(i,j);
    cout<<" ";
    j=5;
    goto cursor;
    }

   else if(ch==13)
   {
    if(j==5)
        return 1; //fill a new form

    else if(j==7) //start voting
      return 3;

    else if(j==9) //view previous records/forms
      return 4;

    else if(j==11)//delete records of a year
        return 2;

    else if(j==13) //modify passwords
      return 5;

    else if(j==15) //help desk
      return 6;

    else if(j==17) //show posts in council
      return 7;

    else if(j==19) //add/modify post in council
      return 8;

    else if(j==21) //exit
      return 0;//exit

    else return -1; //error
   }
   else goto re;
 }


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


short master_control_interface()
{
 short i,j=8,flag;
 char pointer=175;//16,
char point=249,ch;

start:
 clrscr();

 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";

 gotoxy(1,4);
 line();

 gotoxy(33,5);
 cout<<"MASTER CONTROL";

 gotoxy(1,6);
 line();

 gotoxy(1,22);
 line();

 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";

 gotoxy(22,8);
 cout<<point<<" Fill a new form.";
 gotoxy(22,9);
 cout<<point<<" Start voting.";
 gotoxy(22,10);
 cout<<point<<" View all previous records/forms.";
 gotoxy(22,11);
 cout<<point<<" Delete all the forms/ records of a year.";
 gotoxy(22,12);
 cout<<point<<" Modify Passwords.";
 gotoxy(22,13);
 cout<<point<<" Show/Display Passwords.";
 gotoxy(22,14);
 cout<<point<<" Show years for which voting is done.";
 gotoxy(22,15);
 cout<<point<<" Delete the record for year for which voting is done.";
 gotoxy(22,16);
 cout<<point<<" Show Posts in the council.";
 gotoxy(22,17);
 cout<<point<<" Add / Modify Posts in council.";
 gotoxy(22,18);
 cout<<point<<" Show records in a folder.";
 gotoxy(22,19);
 cout<<point<<" Show admission numbers.";
 gotoxy(22,20);
 cout<<point<<" Exit.";
 all_border();

 i=20;

cursor:
  gotoxy(i,j);
  cout<<pointer<<"\b";
   re:
   ch=getch();
   if(ch==72 && j>8)
   {
    gotoxy(i,j);
    cout<<" ";
    j-=1;
    goto cursor;
    }

   else if(ch==72 && j==8)
   {
    gotoxy(i,j);
    cout<<" ";
    j=20;
    goto cursor;
    }

   else if(ch==80 && j<20)
   {
    gotoxy(i,j);
    cout<<" ";
    j+=1;
    goto cursor;
    }

   else if(ch==80 && j==20)
   {
    gotoxy(i,j);
    cout<<" ";
    j=8;
    goto cursor;
    }


   else if(ch==13)
   {
    if(j==8)
        return 1; //fill a new form

    else if(j==9) //start voting
      return 3;

    else if(j==10) //view previous records/forms
      return 4;

    else if(j==11) //view previous records/forms
      return 2;

    else if(j==12) //modify passwords
      return 5;

    else if(j==16) //show posts in council
      return 7;

    else if(j==17) //add/modify post in council
      return 8;

    else if(j==13) //display passwords
      return 9;

    else if(j==14) //show years for which voting is done
      return 10;

    else if(j==15) //delete record for year for which voting is done
      return 11;

    else if(j==18) //show records in a folder of particular year
      return 12;

    else if(j==19) //show records in a folder of admission number.
      return 13;

      else if(j==20) //exit
      return 0; //to exit

    else return -1; //error
   }
   else goto re;
 }


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void create_path_name(char year[]/*year*/,char name[]/*filename*/)
{
 short i;
 for(i=0;i <50; i++)
 {
  if(kbhit())
  getch();
  path_name[i]='\0';
 }

 char f[12]="c:\\RGEVS\\";
 char ext[5]=".DAT"; char g[3]="\\";

 strcat(path_name,f);
 strcat(path_name,year);
 strcat(path_name,g);
 strcat(path_name,name);
 strcat(path_name,ext);
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void create_folder_path(char year[])//year
{
short i;
 char f[12]="c:\\RGEVS\\";

 for(i=0;i <50; i++)
 {
  if(kbhit())
  getch();
  folder_path[i]='\0';}

 strcat(folder_path,f);
 strcat(folder_path,year);
}



/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void input_year(char a[],short x, short y)
{
 int i,j=0;

 start:
     j=0;

 gotoxy(x,y);
 cout<<"                                                                  ";
 gotoxy(x,y);
 cout<<a;
 for(i=0;i<5;i++)
 { if(kbhit())
   getch();
   ::year[i]='\0';}

 cin>>::year;

 year[4]='\0';
 for(i=0;i<4;i++)
 {
   if(kbhit())
  getch();
   if(!isdigit(year[i]))
   {i=-1;
    gotoxy(x,y+2);
    cout<<"                                                                           ";
    gotoxy(x,y+2);
    cout<<"The value should be numeral.";
    goto start;}
   j*=10;
   j+=(::year[i]-48);
  }

 if(j<2016 || j>9999)
 {
  gotoxy(x,y+2);
  cout<<"The value should not be less than 2016 and more than 9999.";
  goto start;
 }

 gotoxy(x,y+2);
    cout<<"                                                           ";

}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void error(char a[],char b[])
{
 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 gotoxy(4,6);
 cout<<"ERROR: ";
 cout<<a;
 gotoxy(4,8);
 cout<<"Comment: "<<b;
 gotoxy(15,21);
 cout<<"Prss Enter Key";
 all_border();
 getch();
 }

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/



char* password_input()
{
 char ch;
 int i,j;
 j=password_size-1;
 for(i=0; i<password_size; i++)
  global_password[i]='\0';

i=0;
 for(;;)
 {
  ch=getch();

  if(i>=j)
    break;

  if(ch==8 && i>0)
  {
   cout<<"\b \b";
   i--;
   continue;
   }

  if(ch==8 && i==0)
  {
   continue;
   }

  if(ch==13)
  {
   global_password[i]='\0';
   break;
   }

   global_password[i]=ch;
   i++;
   cout<<"*";
  }
return global_password;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

short check_pass(char a[], int x)//x=1,open, x=2,modify, x=3,vote, return 1= correct password
{
 ifstream fin;
 int flag;
re:
 fin.open("c:\\RGEVS\\TEMP.DAT",ios::binary);
 fin.seekg(0,ios::end);
  if(!fin || fin.tellg()==0)
  {
   fin.close();
   flag=add_passwords();
   return flag;
   }
 fin.seekg(0,ios::beg);
 fin.read((char*)&pass_global,sizeof(pass_global));
 fin.close();

  if(x==1)
  {
   if(strlen(a)==pass_global.open_size)
   {
    if(strcmp(a,pass_global.open_pass)==0)
    return 1;
    else return 0;
    }
   else return 0;
   }


  if(x==2)
  {
   if(strlen(a)==pass_global.mod_size)
   {
    if(strcmp(a,pass_global.mod_pass)==0)
    return 1;
    else return 0;
    }
   else return 0;
   }


  if(x==3)
  {
   if(strlen(a)==pass_global.vote_size)
   {
    if(strcmp(a,pass_global.vote_pass)==0)
    return 1;
    else return 0;
    }
   else return 0;
   }
 return 0;
 }

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


short add_passwords()
{
 char p[password_size+1],ch;
 clrscr();
 gotoxy(33,3);
 cout<<"FEED PASSWORDS";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();

 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 open:
 gotoxy(3,6);
 cout<<"Feed Password to open software: ";
  password_input();
  strcpy(p,global_password);
 gotoxy(3,7);
 cout<<"Confirm Password to open software: ";
  password_input();

  if(!strcmp(p,global_password))
  {
   strcpy(pass_global.open_pass,global_password);
   pass_global.open_size=strlen(global_password);  }

 else
 {
  gotoxy(6,8);
  cout<<"Mismatch; Re-enter";
  gotoxy(3,7);
  cout<<"                                                                             ";
  gotoxy(3,6);
  cout<<"                                                                             ";
  goto open;
 }
gotoxy(1,8);
line();
all_border();

modify:
 gotoxy(3,10);
 cout<<"Feed Password to Modify posts/passwords: ";
  password_input();
  strcpy(p,global_password);
 gotoxy(3,11);
 cout<<"Confirm Password to modify: ";
  password_input();

  if(!strcmp(p,global_password))
  {
   strcpy(pass_global.mod_pass,global_password);
   pass_global.mod_size=strlen(global_password) ; }

 else
 {
     gotoxy(6,12);
  cout<<"Mismatch; Re-enter";
  gotoxy(3,11);
  cout<<"                                                                             ";
  gotoxy(3,10);
  cout<<"                                                                             ";
  goto modify;
 }

gotoxy(1,12);
line();
all_border();

vote:
 gotoxy(3,14);
 cout<<"Feed Password to start/stop Voting: ";
  password_input();
  strcpy(p,global_password);
 gotoxy(3,15);
 cout<<"Confirm Password to start/stop Voting: ";
  password_input();

  if(!strcmp(p,global_password))
  {
   strcpy(pass_global.vote_pass,global_password);
   pass_global.vote_size=strlen(global_password);  }

 else
 {
     gotoxy(6,16);
  cout<<"Mismatch; Re-enter";
  gotoxy(3,15);
  cout<<"                                                                             ";
  gotoxy(3,14);
  cout<<"                                                                             ";
  goto vote;
 }

 ofstream fout;
 fout.open("c:\\RGEVS\\TEMP.DAT",ios::binary);
 if(!fout)
 {
     if(masterflag!=0)
        error("Could not open TEMP.DAT, used to store passwords.","In add passwords.");
     else
        error("Could not feed password"," " );
        fout.close();
        return 0;//not saved.
 }
 fout.write((char*)&pass_global,sizeof(pass_global));
 fout.close();
 clrscr();
 gotoxy(33,3);
 cout<<"FEED PASSWORDS";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();
 gotoxy(24,6);
 cout<<"PASSWORDS SUCESSFULY SAVED.";
 gotoxy(10,10);
 cout<<"Press Esc to return.";
 re:
     ch=getch();
     if(ch==27)
       return -11;//pass saved
     else goto re;
 return -11;//pass saved
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void display_passwords()
{

 char ch;
 ifstream fin;
fin.open("c:\\RGEVS\\TEMP.DAT",ios::binary);
if(!fin)
 {
     fin.close();
     if(masterflag!=0)
        error("Could not open TEMP.DAT, used to store passwords.","In display passwords.");
     else
        error("Could not Display password"," " );
        return;
 }
fin.read((char*)&pass_global,sizeof(pass_global));
fin.close();

clrscr();
 gotoxy(31,3);
 cout<<"DISPLAY  PASSWORDS";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();

 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

gotoxy(4,6);
cout<<"Opening password:        "<<pass_global.open_pass;
gotoxy(4,8);
cout<<"Modification password:   "<<pass_global.mod_pass;
gotoxy(4,10);
cout<<"Voting password:         "<<pass_global.vote_pass;

gotoxy(8,16);
cout<<"Press Esc key to exit.";
re:
    ch=getch();
    if(ch==27)
        return;
    else
        goto re;
 }

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


short modify_passwords()
{
char p[password_size+1],ch;
ifstream fin;
fin.open("c:\\RGEVS\\TEMP.DAT",ios::binary);
if(!fin)
{
    fin.close();
     if(masterflag!=0)
        error("Could not open TEMP.DAT, used to store passwords.","In Modify passwords, while reading.");
     else
        error("Could not Modify password"," " );
        return -3;//file not open
 }
fin.read((char*)&pass_global,sizeof(pass_global));
fin.close();

 clrscr();
 gotoxy(33,3);
 cout<<"MODFY PASSWORDS";
 gotoxy(2,4);
 cout<<"    (Press enter when asks for old password if you don't want to modify)";
 gotoxy(1,5);
 line();
 gotoxy(1,22);
 line();

 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();




 open:
 gotoxy(3,7);
 cout<<"Enter old Password to Open: ";
  password_input();
 if(global_password[0]=='\0')
   goto modify;
 if(!strcmp(pass_global.open_pass,global_password))
 {
  gotoxy(3,7);
    cout<<"                                                                             ";
 }
 else
 {
  gotoxy(3,7);
    cout<<"                                                                             ";
 goto open;
  }
  reopen:
 gotoxy(3,7);
 cout<<"Feed NEW Password to open software: ";
  password_input();
  strcpy(p,global_password);
 gotoxy(3,8);
 cout<<"Confirm NEW Password to open software: ";
  password_input();

  if(!strcmp(p,global_password))
  {
   strcpy(pass_global.open_pass,global_password);
   pass_global.open_size=strlen(global_password);  }

 else
 {
  gotoxy(6,9);
  cout<<"Mismatch; Re-enter";
  gotoxy(3,8);
  cout<<"                                                                             ";
  gotoxy(3,7);
  cout<<"                                                                             ";
  goto reopen;
 }





modify:
gotoxy(1,9);
line();
all_border();
    gotoxy(3,11);
 cout<<"Enter old Password to Modify: ";
  password_input();
 if(global_password[0]=='\0')
   goto vote;
 if(!strcmp(pass_global.mod_pass,global_password))
 {
  gotoxy(3,11);
    cout<<"                                                                             ";
 }
 else
 {
  gotoxy(3,11);
    cout<<"                                                                             ";
 goto vote;
  }
  remodify:
 gotoxy(3,11);
 cout<<"Feed NEW Password to Modify posts/passwords: ";
  password_input();
  strcpy(p,global_password);
 gotoxy(3,12);
 cout<<"Confirm NEW Password to modify: ";
  password_input();

  if(!strcmp(p,global_password))
  {
   strcpy(pass_global.mod_pass,global_password);
   pass_global.mod_size=strlen(global_password) ; }

 else
 {
     gotoxy(6,13);
  cout<<"Mismatch; Re-enter";
  gotoxy(3,12);
  cout<<"                                                                             ";
  gotoxy(3,11);
  cout<<"                                                                             ";
  goto remodify;
 }



vote:
gotoxy(1,13);
line();
all_border();

gotoxy(3,15);
 cout<<"Enter old Password to Vote: ";
  password_input();
 if(global_password[0]=='\0')
   goto feed;
 if(!strcmp(pass_global.vote_pass,global_password))
 {
  gotoxy(3,15);
    cout<<"                                                                             ";
 }
 else
 {
  gotoxy(3,15);
    cout<<"                                                                             ";
 goto feed;
  }
  revote:
 gotoxy(3,15);
 cout<<"Feed NEW Password to start/stop Voting: ";
  password_input();
  strcpy(p,global_password);
 gotoxy(3,16);
 cout<<"Confirm NEW Password to start/stop Voting: ";
  password_input();

  if(!strcmp(p,global_password))
  {
   strcpy(pass_global.vote_pass,global_password);
   pass_global.vote_size=strlen(global_password);  }

 else
 {
     gotoxy(6,17);
  cout<<"Mismatch; Re-enter";
  gotoxy(3,16);
  cout<<"                                                                             ";
  gotoxy(3,15);
  cout<<"                                                                             ";
  goto revote;
 }

 feed:
 ofstream fout;
 fout.open("c:\\RGEVS\\TEMP.DAT",ios::binary);
 if(!fout)
 {
     fout.close();
     if(masterflag!=0)
        error("Could not open TEMP.DAT, used to store passwords.","In modify passwords.");
     else
        error("Could not modify password"," " );
        return 0;//not saved.
 }
 fout.write((char*)&pass_global,sizeof(pass_global));
 fout.close();
 clrscr();
 gotoxy(33,3);
 cout<<"MODFY PASSWORDS";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();
 gotoxy(24,6);
 cout<<"PASSWORD(s) SUCESSFULY MODIFIED.";
 gotoxy(10,10);
 cout<<"Press Esc to return.";
 re:
     ch=getch();
     if(ch==27)
       return -12;//pass modified
     else goto re;
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/



inline void post_border()
{
 int i,j;
 ::xborderstyle=220;
   ::yborderstyle=219;
 for(i=1; i<=80; i++)
 {
  for(j=1; j<=23; j+=2)
  {
      if(kbhit())
  getch();
   gotoxy(i,j);
   cout<<::xborderstyle;
   if(kbhit())
   getch();
   }
  }

 for(j=2;j<=23; j++)
 {
  if(kbhit())
  getch();
  gotoxy(1,j);
  cout<<::yborderstyle;
  gotoxy(80,j);
  cout<<::yborderstyle;
  if(kbhit())
  getch();
  }

 for(j=6;j<=23;j++)
 {
     if(kbhit())
  getch();
  gotoxy(8,j);
  cout<<::yborderstyle;
  gotoxy(18,j);
  cout<<::yborderstyle;
  if(kbhit())
  getch();
  }

 gotoxy(32,2);
 cout<<"LIST OF POST ID's";
 gotoxy(10,4);
 cout<<"Use arrow keys to turn pages.";
 gotoxy(50,4);
 cout<<"Press Esc to go back";
 gotoxy(2,6);
 cout<<"Sr.no.";
 gotoxy(10,6);
 cout<<"POST ID";
 gotoxy(30,6);
 cout<<"NAME OF POST";
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

short no_of_posts()
{
 short n=0;
 ifstream fin;
 post_id p;

 fin.open("c:\\RGEVS\\POST_ID.DAT",ios::binary);
 if(!fin)
 {
     fin.close();

 if(masterflag!=0)
    error("Error in opening file- c:\\RGEVS\\POST_ID.DAT ;", "While counting no of Posts.");
 else
    error("Error in opening file in which Post IDs and names are saved.","May be the file does not exist.");


 return -4; //value means the problem defined above.
 }

 fin.seekg(0,ios::end);
 n=fin.tellg()/sizeof(p);
 fin.close();
 return n;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void posts_interface()
{
short i,j=10,flag;
 char pointer=175;//16,
char point=249,ch;

start:
 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 gotoxy(32,10);
 cout<<point<<" Show Post names and their ID's.";
 gotoxy(32,12);
 cout<<point<<" Add a Post name.";
 gotoxy(32,14);
 cout<<point<<" Modify a Post name.";
 gotoxy(32,16);
 cout<<point<<" Delete a Post name.";
 gotoxy(32,18);
 cout<<point<<" Go to Previous menu.";
 gotoxy(1,22);
 line();

 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 i=30;
 cursor:
  gotoxy(i,j);
  cout<<pointer<<"\b";
   re:
   ch=getch();
   if(ch==72 && j>10)
   {
    gotoxy(i,j);
    cout<<" ";
    j-=2;
    goto cursor;
    }

   else if(ch==72 && j==10)
   {
    gotoxy(i,j);
    cout<<" ";
    j=18;
    goto cursor;
    }

   else if(ch==80 && j<18)
   {
    gotoxy(i,j);
    cout<<" ";
    j+=2;
    goto cursor;
    }

   else if(ch==80 && j==18)
   {
    gotoxy(i,j);
    cout<<" ";
    j=10;
    goto cursor;
    }

   else if(ch==13)
    {
        if(j==10)
        {
         display_posts();
         goto start;
         }


        else if(j==12)
         {
           add_post();
           goto start;
         }

        else if(j==14)
        {
          modify_post();
          goto start;
        }

        else if(j==16)
         {
             delete_post();
             goto start;
         }

        else if(j==18)
                return ;

        else
        return ;//value for wrong value of j
    }

   else goto re;
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void display_posts()
{
ifstream fin;
short n,i, n1,u,v,j;
char ch;
 n=no_of_posts();

 if(n==-4)
    return;
 if(n==0)
 {
  if(masterflag!=0)
    {error("No contents inside POST_ID.DAT",""); return;}
  else
    {error("No list available.","No records to display.");return;}
   }

   fin.open("c:\\RGEVS\\POST_ID.DAT",ios::binary|ios::in);
  if(!fin)
  {
      fin.close();
   if(masterflag!=0)
        {error("Could not open POST_ID.DAT.","While reading it to display posts.");return;}
   else
    {error("Could not display post.","Technical issue."); return;}
  }

  if(n%8==0)
  n1=n/8;
  else
  n1=n/8+1;
      j=sizeof(post_global);
  fin.seekg(0,ios::beg);

  u=1;//defines page number
  sh:
  clrscr();
  post_border();
  i=(u-1)*8;

  for(v=8; v<=22 && i<n; v+=2,i++)
  {
      if(kbhit())
  getch();
   post_global.id=0;
   post_global.post[0]='\0';
   fin.read((char*)&::post_global,j);
   gotoxy(3,v);
   cout<<i+1;
   gotoxy(10,v);
   cout<<post_global.id;
   gotoxy(20,v);
   cout<<post_global.post;
   }

  reta:
ch=getch();
if(ch==75 && u>1)
{
 u--;
 i=(u-1)*8;
 fin.seekg(0,ios::beg);
 for(v=0;v<i; v++)
 {
     if(kbhit())
  getch();
   fin.read((char*)&::post_global,j);}

 goto sh;
 }

else if(ch==77 && u<n1)
{
 u++;
 goto sh;
 }
else if(ch==27)
{
 fin.close();
 return;
 }
else goto reta;
 }


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void add_post()
{

 ofstream fout;
 short n,i;
 char ch;



 start1:
     n=0;
     clrscr();
 gotoxy(34,3);
 cout<<"ADD  POST(s)";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 start:
     gotoxy(4,6);
     cout<<"                                                     ";
     gotoxy(4,6);
     cout<<"Enter The name of Post: ";
      for(i=0;i<name_size; i++)
       post_global.post[i]='\0';
     cin.getline(post_global.post,name_size,'\n');
     if(post_global.post[0]=='\0')
        goto start;
     gotoxy(6,8);
     cout<<"Do you want to save (press Y or N)?      Press Esc to exit.";
      re:
          ch=getch();
          if(ch=='Y' || ch=='y')
            goto feed;
          else if(ch=='N'||ch=='n')
          {
           gotoxy(6,8);
           cout<<"                                                             ";
           goto start;
          }

          else if(ch==27)
            return;
          else
            goto re;
feed:

    fout.open("c:\\RGEVS\\POST_ID.DAT",ios::app|ios::binary);
    if(!fout)
    {
        fout.close();
     if(masterflag!=0)
     error("Could not open c:\\RGEVS\\POST_ID.DAT","While adding a post name.");
     else
        error("Could not save record.","Technical issues.");
        return;
    }

    fout.seekp(0,ios::end);
    n=fout.tellp()/sizeof(post_global);
    fout.seekp(0,ios::beg);
    post_global.id=n+1;
    fout.write((char*)&post_global,sizeof(post_global));
    fout.close();
    gotoxy(25,12);
    cout<<"Record successfully ADDED.";
ch=0;
  gotoxy(4,18);
  cout<<"Do you want to ADD another record (Press Y or N)?    Press N to exit.";
  re1:
  ch=getch();
      if(ch=='Y' || ch=='y')
            goto start1;
          else if(ch=='N'||ch=='n')
           return;
          else
            goto re1;

}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void modify_post()
{

 ifstream fin;
 ofstream fout;

 post_id po;
 short n,i,j,k;
  k=sizeof(post_global);
 char ch;
 n=no_of_posts();
 if(n==-4)
    return;

 start1:
     clrscr();
 gotoxy(33,3);
 cout<<"MODIFY POST(s)";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 start:
     gotoxy(4,6);
     cout<<"                                                     ";
     gotoxy(4,6);
     cout<<"Enter The Post ID you want to modify: ";
     cin>>j;

     fin.open("c:\\RGEVS\\POST_ID.DAT",ios::binary);
    if(!fin)
    {
        fin.close();
     if(masterflag!=0)
     error("Could not open c:\\RGEVS\\POST_ID.DAT","While searching to modify a post name.");
     else
        error("Could not modify the record.","Technical issues.");
    return;
    }

    fin.seekg(0,ios::beg);

    for(i=0;i<n;i++)
    {
     if(kbhit())
      getch();
     fin.read((char*)&post_global,k);
     if(j==post_global.id)
     break;
     }


     if(i==n)
     {
         fin.close();
      gotoxy(32,8);
      cout<<"RECORD NOT FOUND";
      gotoxy(10,10);
      cout<<"Press Esc to exit.";
      gotoxy(10,11);
      cout<<"Press enter to MODIFY another record.";
       re2:
           ch=getch();
           if(ch==27)
            {return;}
           else if(ch==13)
            {goto start;}
           else goto re2;
     }

     gotoxy(4,6);
     cout<<"                                                     ";

     reenter:
     gotoxy(4,8);
     cout<<"                                                                        ";
     gotoxy(6,10);
     cout<<"                                                           ";
     gotoxy(4,6);
     cout<<"Old Record: "<<post_global.post;
     gotoxy(4,8);
     cout<<"Enter the new name of Post: ";
      for(i=0;i<name_size; i++)
      {
          if(kbhit())
       getch();
       post_global.post[i]='\0';}
      cin.getline(post_global.post,name_size,'\n');
      if(post_global.post[0]=='\0')
        goto reenter;


     gotoxy(6,10);
     cout<<"Do you want to save (press Y or N)?      Press Esc to exit.";
      re:
          ch=getch();
          if(ch=='Y' || ch=='y')
            goto feed;
          else if(ch=='N'||ch=='n')
           goto reenter;
          else if(ch==27)
            {fin.close();return;}
          else
            goto re;
feed:

     fout.open("c:\\RGEVS\\A.DAT",ios::binary);
    if(!fin)
    {
        fout.close();
        fin.close();
     if(masterflag!=0)
     error("Could not open c:\\RGEVS\\A.DAT","While writing to modify a post name.");
     else
        error("Could not modify the record.","Technical issues.");
    return;
    }

  fin.seekg(0,ios::beg);

  for(i=0;i<n;i++)
  {
   fin.read((char*)&po,k);
   if(po.id!=post_global.id)
    fout.write((char*)&po,k);

   if(po.id==post_global.id)
    fout.write((char*)&post_global,k);
  }

  fin.close();
  fout.close();

  remove("c:\\RGEVS\\POST_ID.DAT");
 rename("c:\\RGEVS\\A.DAT","c:\\RGEVS\\POST_ID.DAT");

gotoxy(25,12);
    cout<<"Record successfully MODIFIED.";
ch=0;
  gotoxy(4,18);
  cout<<"Do you want to MODIFY another record (Press Y or N)?    Press N to exit.";
  re1:
  ch=getch();
      if(ch=='Y' || ch=='y')
            goto start1;
          else if(ch=='N'||ch=='n')
           return;
          else
            goto re1;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void delete_post()
{
 ifstream fin;
 ofstream fout;

 short n,i,j,k,id;
 char name[name_size+1],point= 249;

 char ch;


 start1:
     k=sizeof(post_global);
     n=no_of_posts();
 if(n==-4)
    return;
     clrscr();
 gotoxy(33,3);
 cout<<"DELETE POST(s)";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

start:
     gotoxy(4,6);
     cout<<"                                                     ";
     gotoxy(4,6);
     cout<<"Enter The Post ID you want to Delete: ";
     cin>>j;
     fin.open("c:\\RGEVS\\POST_ID.DAT",ios::binary|ios::in);
    if(!fin)
    {
        fin.close();
     if(masterflag!=0)
     error("Could not open c:\\RGEVS\\POST_ID.DAT","While searching to delete a post name.");
     else
        error("Could not search the record.","Technical issues.");
        return;
    }


          fin.seekg(0,ios::beg);

    for(i=0;i<n;i++)
    {
        if(kbhit())
       getch();
     fin.read((char*)&post_global,k);
     if(j==post_global.id)
     break;
     }

    fin.close();
     if(i==n)
     {
      gotoxy(32,8);
      cout<<"RECORD NOT FOUND";
      gotoxy(10,10);
      cout<<"Press Esc to exit.";
      gotoxy(10,11);
      cout<<"Press enter to DELETE another record.";
       re2:
           ch=getch();
           if(ch==27)
            {return;}
           else if(ch==13)
           {
            gotoxy(32,8);
      cout<<"                     ";
      gotoxy(10,10);
      cout<<"                      ";
      gotoxy(10,11);
      cout<<"                                               ";
      goto start;
           }

           else goto re2;
     }


   gotoxy(4,6);
   cout<<"                                                                 ";
   gotoxy(4,6);
   cout<<"Post Name: "<<post_global.post;
   gotoxy(4,8);
   cout<<"Are you sure you want to delete this record (Press Y or N)?";
   gotoxy(4,10);
   cout<<point<<" This will change the ID of each post name coming after to deleted record.";
   gotoxy(4,11);
   cout<<point<<" May be Modifying post name helps you.";
   gotoxy(4,14);
   cout<<"Press Esc to return to previous menu.";
    re3:
        ch=getch();
        if(ch=='Y'||ch=='y')
            goto feed;
        else if(ch=='N'||ch=='n')
            goto start1;
        else if(ch==27)
            return;
        else goto re3;

feed:
    strcpy(name,post_global.post);
    id=post_global.id;

fin.open("c:\\RGEVS\\POST_ID.DAT",ios::binary|ios::in);
      fin.seekg(0,ios::beg);
    if(!fin)
    {
        fin.close();
     if(masterflag!=0)
     error("Could not open c:\\RGEVS\\POST_ID.DAT","While reading to delete a post name.");
     else
        error("Could not delete the record.","Technical issues.");
        return;
    }
fout.open("c:\\RGEVS\\T.DAT",ios::binary|ios::out);
if(!fout)
    {
        fout.close();
     if(masterflag!=0)
     error("Could not open c:\\RGEVS\\T.DAT","While writing to delete a post name.");
     else
        error("Could not delete the  record.","Technical issues.");
        return;
    }
for(i=0,j=1;i<n;i++)
{
    if(kbhit())
  getch();
 fin.read((char*)&post_global,k);
 if(id!=post_global.id)
   {
    post_global.id=j;
    fout.write((char*)&post_global,k);
    j++;
   }
}
fin.close();
fout.close();
remove("c:\\RGEVS\\POST_ID.DAT");
rename("c:\\RGEVS\\T.DAT","c:\\RGEVS\\POST_ID.DAT");
gotoxy(25,16);
    cout<<"Record successfully DELETED.";
ch=0;
  gotoxy(4,20);
  cout<<"Do you want to DELETE another record (Press Y or N)?    Press N to exit.";
  re1:
  ch=getch();
      if(ch=='Y' || ch=='y')
            goto start1;
          else if(ch=='N'||ch=='n')
           return;
          else
            goto re1;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
inline void votestat_border()
{
 int i,j;
 ::xborderstyle=220;
   ::yborderstyle=219;
 for(i=10;i<=70;i++)
 {
  for(j=1;j<=23;j+=2)
  {
   gotoxy(i,j);
   cout<<::xborderstyle;
   }
  }

  for(i=2;i<=23;i++)
  {
   gotoxy(10,i);
   cout<<::yborderstyle;
   gotoxy(19,i);
   cout<<::yborderstyle;
   gotoxy(70,i);
   cout<<::yborderstyle;
   }

 gotoxy(12,2);
 cout<<"SR. NO";
 gotoxy(30,2);
 cout<<"NAME";

 }

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

int check_voting_status(char a[])
{
 ifstream fin;
 voting_status s;
 int n,i;
 fin.open("c:\\RGEVS\\VOTESTAT.DAT",ios::binary);
 if(!fin)
 {
     fin.close();
     if(masterflag!=0)
  error("Could not open c:\\RGEVS\\VOTESTAT.DAT","While checking voting status");
  return 0;
  }
 fin.seekg(0,ios::end);
 n=fin.tellg()/sizeof(s);
 fin.seekg(0,ios::beg);
 for(i=0; i<n; i++)
 {
  fin.read((char*)&s,sizeof(s));
  if(strcmpi(a,s.year)==0)
  {
   fin.close();
   return 1;
   }
  }
 fin.close();
 return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void delete_voting_status()
{
 ofstream fout;
 ifstream fin;
 voting_status s;
 int n,i;
 clrscr();
 all_border();
 input_year("Enter year to be deleted: ",4,10);

 fin.open("c:\\RGEVS\\VOTESTAT.DAT",ios::binary);
 if(!fin)
 {fin.close();if(masterflag!=0)
    error("Could not open c;\\RGEVS\\VOTESTAT.DAT","While Deleting record.");return;}

 fout.open("c:\\RGEVS\\TEMP1.DAT",ios::binary);
 if(!fout)
 {fout.close(); error("Could not open c;\\RGEVS\\TEMP1.DAT","While Deleting record.");return;}


 fin.seekg(0,ios::end);
 n=fin.tellg()/sizeof(s) ;
 fin.seekg(0,ios::beg);

 for(i=0; i<n; i++)
 {
  fin.read((char*)&s,sizeof(s));
  if(strcmpi(s.year,::year)!=0)
  {
   fout.write((char*)&s,sizeof(s));
   }
  }
  fin.close();
  fout.close();
 remove("c:\\RGEVS\\VOTESTAT.DAT");
 rename("c:\\RGEVS\\TEMP1.DAT","c:\\RGEVS\\VOTESTAT.DAT");
return;
 }

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void voting_status_input(char a[]/*year*/)
{
 ofstream fout;
 voting_status s;
  strcpy(s.year,a);
 fout.open("c:\\RGEVS\\VOTESTAT.DAT",ios::binary|ios::app);
 if(!fout)
 {
  fout.close();
  if(masterflag!=0)
  error("Could not open C:\\RGEVS\\VOTESTAT.DAT","While input.");
  return;
 }

 fout.write((char*)&s,sizeof(s));
 fout.close();
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void show_voting_status()
{
ifstream fin;
short n,i, n1,u,v,j;
voting_status s;
char ch;

  fin.open("c:\\RGEVS\\VOTESTAT.DAT",ios::binary|ios::in);
  if(!fin)
  {
      fin.close();

   if(masterflag!=0)
        {error("Could not VOTESTAT.DAT.","While reading it to display list of years for which voting is done.");return;}
   else
    {error("Could not display post.","Technical issue."); return;}
  }

  fin.seekg(0,ios::end);
  n=fin.tellg()/sizeof(s);
  fin.seekg(0,ios::beg);

 if(n==0)
 {
  if(masterflag!=0)
    {error("No contents inside VOTESTAT.DAT",""); fin.close(); return;}
  else
    {error("No list available.","No records to display.");fin.close();return;}
   }


  if(n%10==0)
  n1=n/10;
  else
  n1=n/10+1;
      j=sizeof(s);
  fin.seekg(0,ios::beg);

  u=1;//defines page number
  sh:
  clrscr();
  votestat_border();
  i=(u-1)*10;

  for(v=4; v<=22 && i<n; v+=2,i++)
  {
      if(kbhit())
  getch();
   post_global.id=0;
   post_global.post[0]='\0';
   fin.read((char*)&s,j);
   gotoxy(12,v);
   cout<<i+1;
   gotoxy(21,v);
   cout<<s.year;
   }

  reta:
ch=getch();
if(ch==75 && u>1)
{
 u--;
 i=(u-1)*8;
 fin.seekg(0,ios::beg);
 for(v=0;v<i; v++)
 {
     if(kbhit())
  getch();
   fin.read((char*)&s,j);}

 goto sh;
 }

else if(ch==77 && u<n1)
{
 u++;
 goto sh;
 }
else if(ch==27)
{
 fin.close();
 return;
 }
else goto reta;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

short input_folder_record() //return 0 if could not save record.
{
 ofstream fout1;
 char fol[7]="RVSREC";
 create_path_name(::year,fol);

 fout1.open(path_name,ios::app|ios::binary);
 /*if(!fout1.is_open())
 {
 fout1.close();
   if(masterflag!=0)
   error(path_name,"Could not open while writing for folder record.");

   return 0;
 }
 else
 {
     error("could not save record.","Technical Issue");
     return 0;
 }
*/
fout1.write((char*)&post_global,sizeof(post_global));
fout1.close();
return 1;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

short delete_folder_record(short id)
{
ofstream fout;
ifstream fin;
char path_name2[50];
 char fol[7]="RVSREC";
char te[2]="T";

 create_path_name(::year,fol);
 strcpy(path_name2,path_name);
  create_path_name(::year,te);

 fin.open(path_name2,ios::binary);
/* if(!fin)
 {
 fin.close();
   if(masterflag!=0)
   error(path_name2,"Could not open while deleting records from folder record.");

   return 0;
 }
 else
 {
     error("could not save record.","Technical Issue");
     return 0;
 }*/



 fout.open(path_name,ios::binary);
 /*if(!fout)
 {
 fout.close();
   if(masterflag!=0)
   error(path_name,"Could not open while deleting records from folder record.");

   return 0;
 }
 else
 {
     error("could not save record.","Technical Issue");
     return 0;
 }*/

short n,i,j;
j=sizeof(post_global);
fin.seekg(0,ios::end);
n=fin.tellg()/j;
fin.seekg(0,ios::beg);


for(i=0;i<n;i++)
{
 if(kbhit())
        getch();
 fin.read((char*)&post_global,j);
 if(post_global.id!=id)
    fout.write((char*)&post_global,j);
}

fout.close();
fin.close();

remove(path_name2);
rename(path_name,path_name2);
return 1;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void show_folder_record()
{
ifstream fin;
 char fol[7]="RVSREC";
 create_path_name(::year,fol);

 fin.open(path_name,ios::binary);
 /*if(!fin)
 {
 fin.close();

   if(masterflag!=0)
   error(path_name,"Could not open while showing records from folder record.");

  else
     error("could not show record.","Technical Issue");
     return ;
 }*/

 short n,i,j;
j=sizeof(post_global);
fin.seekg(0,ios::end);
n=fin.tellg()/j;
fin.seekg(0,ios::beg);
clrscr();

for(i=0; i<n; i++)
{
     fin.read((char*)&post_global,j);
  cout<<"\nFolder name: "<<post_global.id;
  cout<<"\nPost name: "<<post_global.post;
  cout<<"\n\tPress Enter key.\n";
  getch();
}
cout<<"\nNo more records to display.";
getch();
fin.close();
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void display_registeration_form()
{
 display_registeration_form_border();
 gotoxy(22,8);
 cout<<cand_global.year;
 gotoxy(22,10);
 cout<<cand_global.post_name;
 gotoxy(22,12);
 cout<<cand_global.name;
 gotoxy(22,14);
 cout<<cand_global.standard;
 gotoxy(22,16);
 cout<<cand_global.section;
 gotoxy(22,18);
 cout<<cand_global.admission_no;
 gotoxy(22,20);
 cout<<cand_global.no_of_votes;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

inline void display_registeration_form_border()
{
    short i;
    clrscr();
gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(3,5);
 cout<<"Candidate ";//print stud ID (15,5) and comment from (20,5)
 gotoxy(50,5);
 cout<<"Press Esc to exit.";
 gotoxy(1,6);
 line();
 gotoxy(1,22);
 line();

 ::xborderstyle=220;
   ::yborderstyle=219;

 for(i=2;i<80;i++)
 {
  gotoxy(i,7);
  cout<<::xborderstyle;
  gotoxy(i,9);
  cout<<::xborderstyle;
  gotoxy(i,11);
  cout<<::xborderstyle;
  gotoxy(i,13);
  cout<<::xborderstyle;
  gotoxy(i,15);
  cout<<::xborderstyle;
  gotoxy(i,17);
  cout<<::xborderstyle;
  gotoxy(i,19);
  cout<<::xborderstyle;
  gotoxy(i,21);
  cout<<::xborderstyle;
 }
 gotoxy(3,8);
 cout<<"Year: ";
 gotoxy(3,10);
 cout<<"Post Name: ";
 gotoxy(3,12);
 cout<<"Candidate Name: ";
 gotoxy(3,14);
 cout<<"Class: ";
 gotoxy(3,16);
 cout<<"Section: ";
 gotoxy(3,18);
 cout<<"Admission no: ";
 gotoxy(3,20);
 cout<<"No. of votes: ";
 all_border();

 for(i=8;i<=21;i++)
 {
  gotoxy(20,i)   ;
  cout<<::yborderstyle;
 }

}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void register_registeration_form()
{
 char ch,nam[4];
 short n,flag=1,k,i,j;

 reform:
 candidate_registeration_form();
 display_registeration_form();
 if(cand_global.stud_id!=-14)
 {
  return;
 }
 gotoxy(4,23);
 cout<<"Press D to discard.  Press enter to save.";
  re:
  ch=getch();
  if(ch=='D'||ch=='d')
  {
    delete_adno(cand_global.admission_no,cand_global.year);
    return;
  }
  else if(ch==13)
    goto save;
  else
    goto re;

  save:
      strcpy(::year,cand_global.year);
      create_folder_path(::year);
      mkdir(folder_path);
      cout.flush();
      cin.ignore();
k=cand_global.post_id;

for(i=0;k!=0;i++)
{
 if(kbhit())
        ch=getch();

 nam[i]=(k%10)+48;
 k=k/10;
}
nam[i]='\0';

 create_path_name(::year,nam);

 ofstream fout;

 fout.open(path_name,ios::binary|ios::app);
 if(!fout)
 {
  fout.close();
  if(masterflag!=0)

   error(path_name,"Could not open file while writing candidate form.");
  else
      error("Could not save form.","Technical issues.");
      return;
 }

 j=sizeof(cand_global);
 fout.seekp(0,ios::end);
 n=fout.tellp()/j;
 fout.seekp(0,ios::beg);

 if(n==5)
 {
  fout.close();
 flag=delete_adno(cand_global.admission_no,cand_global.year);
  clrscr();
  all_border();
  gotoxy(4,14);
  cout<<"Not more than 5 candidates allowed for one post.";
  gotoxy(20,18);
  cout<<"Press any key.";
  getch();
  return;
 }

 cand_global.stud_id=n+1;
flag=4;

 if(n==0)
 {
     fout.close();
   flag=input_folder_record();
   create_path_name(::year,nam);
   fout.open(path_name,ios::binary|ios::app);
 if(!fout)
 {
  fout.close();
  if(masterflag!=0)
   error(path_name,"Could not open file while writing candidate form.");
  else
   error("Could not save form.","Technical issues.");
   return;
 }

 fout.seekp(0,ios::end);
 n=fout.tellp()/j;
 fout.seekp(0,ios::beg);
 }


  if(flag!=0)
  {
      fout.write((char*)&cand_global,j);
 fout.close();

   clrscr();
   gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";

   all_border();
   gotoxy(4,10);
   cout<<"FORM SUCCESSFULY SAVED.";
   gotoxy(20,20);
   cout<<"Press any key.";
   getch();
   return;
  }

  else
  {
   fout.close();
 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";

   all_border();
   gotoxy(4,10);
   cout<<"FORM NOT SAVED.";
   gotoxy(20,20);
   cout<<"Press any key.";
   getch();
   return;
  }
  return;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


void display_candidate_records()
{
char path_name2[50];
char nam[4],ch;
 char fol[7]="RVSREC";


ifstream fin1,fin2;
short no_of_post=-1, size_of_post,no_of_cand,size_of_cand;
short i,j,u,v,flagvot,k,l;

size_of_post=sizeof(post_global);
size_of_cand=sizeof(cand_global);

clrscr();

 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,6);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 input_year("Enter the year for which you want to see record: ",4,10);

 flagvot=check_voting_status(::year);

 if(flagvot==1)
 {
  gotoxy(25,12);
  cout<<"VOTING FOR THIS  YEAR IS DONE.";
  gotoxy(4,14);
  cout<<"Enter voting password to display this record: ";
  password_input();
  flagvot=check_pass(global_password,3);
  if(flagvot!=1)
  {
   gotoxy(32,18);
   cout<<"Wrong Password.";
   getch();
   return;
  }
  flagvot=1;
 }

  create_path_name(::year,fol);
  strcpy(path_name2,path_name);
/*  if(!fin)
  {
   if(masterflag!=0)
   {

    error(path_name,"Could not open while displaying student records.");
    return;
   }
   else
   {
     error("No records to display.","");
     return;
   }
  }*/

 u=0;
 i=0;
read_post:
      fin1.open(path_name2,ios::binary|ios::in);
      fin1.seekg(0,ios::end);
      no_of_post=fin1.tellg()/size_of_post;

      no_of_post-=1;
      fin1.seekg(0,ios::beg);

      if(no_of_post==-1)
      {
       clrscr();
       all_border();
       gotoxy(4,10);
       cout<<"No records to display for this year.";
       gotoxy(10,16);
       cout<<"Press any key.";
       getch();
       return;
      }

    for(u=0; u<=i; u++)
     fin1.read((char*)&post_global,size_of_post);
    fin1.close();

    k=post_global.id;

     for(u=0;k!=0;u++)
     {
     nam[u]=(k%10)+48;
     k=k/10;
     }

    nam[u]='\0';
    create_path_name(::year,nam);
 j=0;
    fin2.open(path_name,ios::binary);

    if(!fin2)
    {
     fin2.close();
     if(masterflag!=0)
            error(path_name,"Could not open while displaying records.");
     else
        error("Could not display records.","Technical issue.");
    }

      fin2.seekg(0,ios::end);
      no_of_cand=fin2.tellg()/size_of_cand;
      no_of_cand-=1;
      fin2.seekg(0,ios::beg);

      if(ch==75)
      {
       fin2.seekg(-size_of_cand,ios::end);
       j=no_of_cand;
      }




   dispcand:
     fin2.read((char*)&cand_global,size_of_cand);
     clrscr();
      display_registeration_form();
      if(cand_global.stud_id!=-14)
      {
      gotoxy(15,5)   ;
      cout<<cand_global.stud_id;
      }

      if(flagvot==0)
      {
       gotoxy(4,23);
      cout<<"Press A to modify, D to delete records. Use arrow keys to surf records";
      }

      else
      {
       gotoxy(4,23);
      cout<<"Use arrow keys to surf records.";
      }


     retake:
          ch=getch();
          if(ch==75 && j>0)
          {
              j--;
           fin2.seekg(-(2*size_of_cand),ios::cur);
            goto dispcand;
           }

          else if(ch==77 && j<no_of_cand)
          {
              j++;
              goto dispcand;
          }


          else if(ch==75 && j==0)
          {
           if(i>0)
           {
            fin2.close();
           i--;
           goto read_post;
           }
          }

          else if(ch==77 && j==no_of_cand)
          {
           if(i<no_of_post)
           {
            i++;
           fin2.close();
           goto read_post;
           }
          }

          else if(ch=='D'||ch=='d')
          {
           if(flagvot==0)
           {
            clrscr();
            all_border();
            gotoxy(4,10);
            cout<<"Are you sure you want to delete this record (Press Y or N)?: ";
             retake1:
                 ch=getch();
                 if(ch=='N' || ch=='n')
                  {
                   fin2.seekg(-size_of_cand,ios::cur);
                   goto dispcand;
                  }

                 else if(ch=='Y' || ch=='y')
                 {
                  fin2.close();
                  delete_candidate_record(cand_global.stud_id);
                  if(no_of_cand==1 && i==0)
                    goto read_post;

                  else if(no_of_cand==1 && i>0)
                  {
                   i--;
                   goto read_post;
                  }

                  no_of_cand-=1;
                  fin2.open(path_name,ios::binary);
                  for(l=0;l<j-1;l++)
                    fin2.read((char*)&cand_global,size_of_cand);
                    j=l;
                  goto dispcand;
                 }

                 else goto retake1;
           }
          }


          else if(ch=='A'||ch=='a')
          {
           if(flagvot==0)
           {
            clrscr();
            all_border();
            gotoxy(4,10);
            cout<<"Are you sure you want to modify this record (Press Y or N)?: ";
             retake2:
                 ch=getch();
                 if(ch=='N' || ch=='n')
                  {
                   fin2.seekg(-size_of_cand,ios::cur);
                   goto dispcand;
                  }

                 else if(ch=='Y' || ch=='y')
                 {
                  fin2.close();
                  modify_candidate_record(cand_global.stud_id);
                  fin2.open(path_name,ios::binary);
                  for(l=0;l<j;l++)
                    fin2.read((char*)&cand_global,size_of_cand);
                  goto dispcand;
                 }

                 else goto retake2;
           }
          }



          else if(ch==27)
          {
           fin2.close();
           return;
          }

          else
          {ch=0; goto retake;}

goto retake;

}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void delete_candidate_record(short sid)
{
  char path_name2[50];
  char path_name3[50];
 char te[2]="P";
 strcpy(path_name2,::path_name);
 ifstream fin;
 ofstream fout;
 create_path_name(::year,te);
 strcpy(path_name3,::path_name);

 fin.open(path_name2,ios::binary);
 if(!fin)
 {
   fin.close();
   if(masterflag!=0)
    error(path_name2,"Could not open while reading to delete candidate record.");
   else
    error("could not delete record.","Technical issue.");
   strcpy(::path_name,path_name2);
   return;
 }


 fout.open(path_name3,ios::binary);
 if(!fin)
 {
   fout.close();
   if(masterflag!=0)
    error(path_name3,"Could not open while deleting candidate record.");
   else
    error("could not delete record.","Technical issue.");
   strcpy(::path_name,path_name2);
   return;
 }


 short n,j,i,k,flag=1;
 long double ano=0;
 k=sizeof(cand_global);
 fin.seekg(0,ios::end);
 n=fin.tellg()/k;
 fin.seekg(0,ios::beg);

 for(i=0,j=0;i<n;i++)
 {
  if(kbhit())
        getch();
  fin.read((char*)&cand_global,k);
  if(cand_global.stud_id==sid)
    ano=cand_global.admission_no;

  if(cand_global.stud_id!=sid)
  {
    j++;
    cand_global.stud_id=j;
    fout.write((char*)&cand_global,k);
   }
 }


 fout.close();
 fin.close();

 if(n==1)
  flag=delete_folder_record(cand_global.post_id);

  if(flag==1)
  {
      flag=delete_adno(ano,cand_global.year);
      if(flag==0)
        goto x;
   remove(path_name2);
  rename(path_name3,path_name2);
  strcpy(::path_name,path_name2);
 clrscr();
 gotoxy(4,10);
 cout<<"Candidate record successfully deleted.";
 gotoxy(10,16);
 cout<<"Press any key.";
 all_border();
 getch();
 return;
  }

  else goto x;

  x:
   remove(path_name3);
  strcpy(::path_name,path_name2);
 clrscr();
 gotoxy(4,10);
 cout<<"Candidate record NOT deleted.";
 gotoxy(10,16);
 cout<<"Press any key.";
 all_border();
 getch();
 return;





}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void modify_candidate_record(short sid)
{
    candidate c;
     short n,j,i,ano;

 char path_name2[50];
 char path_name3[50];
 char te[2]="T";
 char ch;
 short flag=0;
 strcpy(path_name2,::path_name);
 ifstream fin;
 ofstream fout;
 create_path_name(::year,te);
  strcpy(path_name3,::path_name);

 fin.open(path_name2,ios::binary);
 if(!fin)
 {
   fin.close();
   if(masterflag!=0)
    error(path_name2,"Could not open while reading to modify candidate record.");
   else
    error("could not modify record.","Technical issue.");
   strcpy(::path_name,path_name2);
   return;
 }


 fout.open(path_name3,ios::binary);
 if(!fout)
 {
   fout.close();
   if(masterflag!=0)
    error(path_name3,"Could not open while deleting candidate record.");
   else
    error("could not delete record.","Technical issue.");
   strcpy(::path_name,path_name2);
   return;
 }

 reform:
 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(26,5);
 cout<<"Candidate Registration form.";
 gotoxy(1,6);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 all_border();

 gotoxy(4,8);
 cout<<"Enter the year of election: "<<cand_global.year;

 gotoxy(4,10);
 cout<<"Enter Post ID (ID of post for which you are standing): "<<cand_global.stud_id;

naminput:
gotoxy(4,12);
  cout<<"                                                    ";
  gotoxy(4,12);
  cout<<"Enter Candidate name: ";
  cout.flush();
  cin.ignore();
  for(i=0;i<name_size;i++)
  {if(kbhit())
        getch();
    cand_global.name[i]='\0';}
   cin.getline(cand_global.name,name_size,'\n');
   if(cand_global.name[0]=='\0')
    goto naminput;


  stdinput:
    cand_global.standard=only_number_input("Enter the class in which you are studying: ",4,14);
    if(cand_global.standard<1 || cand_global.standard>12)
      { gotoxy(10,16);
        cout<<"Input a valid class.";
        goto stdinput;}

  secinput:
  gotoxy(4,16);
  cout<<"                                                     ";
  gotoxy(4,16);
  cout<<"Enter your section: ";
  cin>>cand_global.section;
   if(!isalpha(cand_global.section[0]))
   { gotoxy(10,18);
        cout<<"Enter a valid section.";
        goto secinput;}
   if(islower(cand_global.section[0]))
            cand_global.section[0]=toupper(cand_global.section[0]);

ano=cand_global.admission_no;
   adnoimput:
   gotoxy(4,18);
  cout<<"                                                     ";

  cand_global.admission_no=only_number_input("Enter Admission Number: ",4,18);
  if(cand_global.admission_no-floor(cand_global.admission_no)!=0 || cand_global.admission_no<1)
  {
    gotoxy(10,20);
    cout<<"Enter a valid admission number.";
    goto adnoimput;
  }

  if(cand_global.admission_no==ano)
  {
       goto y;
  }

  flag=check_adno(cand_global.admission_no,year);
  if(flag==1)
  {
   gotoxy(10,20);
    cout<<"Number already used.";
    goto adnoimput;
  }


 if(flag==-1)
 {
  return;
 }
y:
cand_global.no_of_votes=0;
cand_global.stud_id=sid;


 display_registeration_form();

 if(cand_global.stud_id!=-14)
 {
  gotoxy(15,5)   ;
  cout<<cand_global.stud_id;
 }
 gotoxy(4,23);
 cout<<"Press D to discard.  Press enter to Modify.";
  re:
  ch=getch();
  if(ch=='D'||ch=='d')
  {
   strcpy(path_name,path_name2);
   return;
  }
  else if(ch==13)
    goto modify;
  else
    goto re;


modify:

 j=sizeof(cand_global);
 fin.seekg(0,ios::end);
 n=fin.tellg()/j;
 fin.seekg(0,ios::beg);

 for(i=0;i<n;i++)
 {
  if(kbhit())
        getch();
  fin.read((char*)&c,j);
  if(c.stud_id!=sid)
    fout.write((char*)&c,j);

  if(c.stud_id==sid)
   {
    fout.write((char*)&cand_global,j);
    ano=c.admission_no;
   }
 }

 fout.close();
 fin.close();

 flag=delete_adno(ano,cand_global.year);
 if(flag==0)
 {
  remove(path_name3);
  strcpy(path_name,path_name2);
  goto x;
 }

 flag=input_adno(cand_global.admission_no,cand_global.year);
 if(flag==0)
 {
  remove(path_name3);
    strcpy(path_name,path_name2);
  goto x;
 }



 remove(path_name2);
 rename(path_name3,path_name2);

 strcpy(::path_name,path_name2);

 clrscr();
 gotoxy(4,10);
 cout<<"Candidate record successfully Modified.";
 gotoxy(10,16);
 cout<<"Press any key.";
 all_border();
 getch();
 return;


 x:
     clrscr();
 gotoxy(4,10);
 cout<<"Candidate record NOT Modified.";
 gotoxy(10,16);
 cout<<"Press any key.";
 all_border();
 getch();
 return;

}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


short input_adno(long double no/*admission no*/,char yr[]/*year*/) //return 1 if saved. 0 if not saved.
{
 ofstream fout;
 char admission[5]="adno";
 create_path_name(yr,admission);

 adno_global.adno=no;

 fout.open(path_name,ios::app|ios::binary);
 if(!fout)
 {
        fout.close();
  if(masterflag!=0)
  error(path_name,"Could not open this file while saving admission number.");
  else
    error("Could not save record.","Technical Issue.");
  return 0;
 }

 fout.write((char*)&adno_global,sizeof(adno_global));
 fout.close();
 return 1;
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

short check_adno(long double no, char yr[]) //return 1 if found.0 if not found,-1 if not open file.
{
 ifstream fin;
 ofstream fout;
 char admission[5]="adno";
 create_path_name(yr,admission);

      fout.open(path_name,ios::app|ios::binary);
      fout.close();

 fin.open(path_name,ios::binary);
 if(!fin)
 {
        fin.close();

  if(masterflag!=0)
  error(path_name,"Could not open this file while checking admission number.");
  else
    error("Could not check record.","Technical Issue.");
  return -1;
 }

 short n,i,j;
 j=sizeof(adno_global);
 fin.seekg(0,ios::end);
 n=fin.tellg()/j;
 fin.seekg(0,ios::beg);

 for(i=0;i<n; i++)
 {
  fin.read((char*)&adno_global,j);
  if(adno_global.adno==no)
  {
   fin.close() ;
   return 1;
  }
 }

 fin.close();
 return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


short delete_adno(long double no/*admission no*/,char yr[]/*year*/)//return 0 if not deleted, 1 if deleted.
{
ifstream fin;
ofstream fout;
 char admission[5]="adno";
 char te[2]="G";
 char path_name2[50];

 create_path_name(yr,admission);
 strcpy(path_name2,path_name);
 create_path_name(yr,te);

 fin.open(path_name2,ios::binary);
 if(!fin)
 {
        fin.close();
  if(masterflag!=0)
  error(path_name2,"Could not open this file while deleting admission number.");
  else
    error("Could not delete record.","Technical Issue.");
  return 0;
 }


 fout.open(path_name,ios::app|ios::binary);
 if(!fout)
 {
        fout.close();
  if(masterflag!=0)
  error(path_name,"Could not open this file while deleting admission number.");
  else
    error("Could not delete record.","Technical Issue.");
  return 0;
 }


 short i,j,n;
 j=sizeof(adno_global);

 fin.seekg(0,ios::end);
 n=fin.tellg()/j;
 fin.seekg(0,ios::beg);

 for(i=0; i<n; i++)
 {
  if(kbhit())
        getch();
   fin.read((char*)&adno_global,j);

  if(adno_global.adno!=no)
    fout.write((char*)&adno_global,j);
 }

 fin.close();
 fout.close();

 remove(path_name2);
 rename(path_name,path_name2);
 return 1;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void display_adno()
{

    clrscr();
    all_border();

  input_year("Enter the year for which you want to see record: ",4,10);
  clrscr();
  char admission[5]="adno";
  create_path_name(year,admission);

  ifstream fin;
  fin.open(path_name,ios::binary);
  long n;
  short j=sizeof(adno_global),i;

  fin.seekg(0,ios::end);
  n=fin.tellg()/j;
  fin.seekg(0,ios::beg);

  for(i=0; i<n; i++)
  {
   fin.read((char*)&adno_global,j);
   cout<<adno_global.adno<<endl;
   getch();
  }

  cout<<"\n\n\tNo more records to display.";
  getch();
  fin.close();
}


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void delete_records_of_year()
{
clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 gotoxy(4,6);
all_border();

short flag;
char ch,l[2]="L";
input_year("Enter the year of which you want to delete the record: ",4,10);

create_path_name(::year,l);
ofstream fout;
fout.open(path_name);
if(!fout)
{
 gotoxy(4,12);
 cout<<"No record exist for this year.";
 gotoxy(10,18);
 cout<<"Press any key";
 getch();
 return;
}
fout.close();
remove(path_name);

flag=check_voting_status(::year);

if(flag==1)
{
 gotoxy(4,12);
 cout<<"VOTING FOR THIS YEAR IS DONE. CANNOT DELETE THE RECORD.";
 gotoxy(10,18);
 cout<<"Press any key";
 getch();
 return;
}

gotoxy(4,12);
cout<<"Are you sure you want to delete all records of "<<::year<<" (Press Y or N): ";
re:
    ch=getche();
    if(ch=='Y'||ch=='y')
        goto check;

    else if(ch=='N'||ch=='n')
        return;
    else
    {
     cout<<"\b \b";
     return;
    }



check:
 gotoxy(4,14);
 cout<<"Enter modification password: ";
 password_input();
 flag=check_pass(global_password,2);
 if(flag!=1)
 {gotoxy(20,16);
 cout<<"WRONG PASSWORD";
 getch();
 return;}

short i,j;
int size_of_post=sizeof(post_global);
int no_of_post;
char fol[7]="RVSREC";
char path_name2[50];
char nam[4];


create_path_name(::year,fol);
strcpy(path_name2,::path_name);
ifstream fin;

fin.open(path_name2,ios::binary);
fin.seekg(0,ios::end);
no_of_post=fin.tellg()/size_of_post;
fin.seekg(0,ios::beg);

for(i=0; i<no_of_post; i++)
{
 fin.read((char*)&post_global,size_of_post);
 for(j=0;post_global.id!=0;j++)
     {
     nam[j]=(post_global.id%10)+48;
     post_global.id=post_global.id/10;
     }

    nam[j]='\0';
create_path_name(::year,nam);
remove(path_name);
}

fin.close();

char ano[5]="adno";
create_path_name(::year,ano);
remove(path_name);
remove(path_name2);

create_path_name(::year,fol);
fout.open(path_name);
fout.close();
remove(path_name);

create_folder_path(::year);
rmdir(folder_path);

gotoxy(29,6);
cout<<"SUCCESSFULLY  DELETED.";
getch();
return;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
inline void voting_border(short n)
{
   ::xborderstyle=220;
   ::yborderstyle=219;
 short i,j,k;
 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(9,5);
 cout<<"Type the student ID for whom you want to vote and press enter.";
 gotoxy(1,6);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 gotoxy(4,6);

 for(i=2;i<80;i++)
 {
  gotoxy(i,7);
  cout<<::xborderstyle;
  gotoxy(i,9);
  cout<<::xborderstyle;
 }

 j=11;
 for(k=1;k<n;k++,j+=2)
 {
  gotoxy(1,j);
  line();
 }

 for(i=2;i<80;i++)
 {
  gotoxy(i,j);
  cout<<::xborderstyle;
 }

 for(i=8; i<=j; i++)
 {
  gotoxy(6,i);
  cout<<::yborderstyle;
 }
 all_border();


 gotoxy(3,8);
 cout<<"ID";
 gotoxy(8,8);
 cout<<"For Post: ";


 /*gotoxy(10,21); type this in voting process
 cout<<"Enter your choice: ";*/
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void voting()
{
 char te[2]="E";
 char path_name2[50];
 char fol[7]="RVSREC";
 char pass[password_size+1],ch;
 char nam[4];

 short sid, pid, no_of_post, no_of_cand, size_of_post, size_of_cand;
 short i,u,j,v,flag,vflag=0,k;

 strcpy(pass,pass_global.mod_pass);


 clrscr();
 gotoxy(19,3);
 cout<<"Ryan Ghaziabad Electronic Voting System.";
 gotoxy(1,4);
 line();
 gotoxy(1,22);
 line();
 gotoxy(4,23);
 cout<<"Product by Vaibhav Gupta. For any bugs, contact at vaibhavgupta40@gmail.com";
 gotoxy(4,6);
 all_border();
 input_year("Enter the year for which you want to start voting: ",4,10);
 flag=check_voting_status(::year);
 if(flag==1)
 {
  gotoxy(4,12);
  cout<<"VOTING FOR THE YEAR IS ALREADY DONE.";
  gotoxy(20,14);
  cout<<"Press any key.";
  getch();
  return;
 }

 create_path_name(::year,te);
 ofstream fout;
 fout.open(path_name);
 if(!fout)
 {
     fout.close();
  gotoxy(4,12);
  cout<<"NO records exist for the year.";
  gotoxy(20,14);
  cout<<"Press any key.";
  getch();
  return;
 }

 fout.close();
 remove(path_name);

 gotoxy(4,12);
 cout<<"Enter voting Password: ";
 strcpy(pass,password_input());
 flag=check_pass(global_password,3);
 if(flag!=1)
 {
  gotoxy(31,14);
  cout<<"WRONG PASSWORD.";
  gotoxy(20,18);
  cout<<"Press any key.";
  getch();
  return;
 }

 create_path_name(::year,fol);
 strcpy(path_name2,path_name); //path_name2 holds address of RVSREC
 ifstream fin1,fin2; //fin1 for RVSREC
 size_of_post=sizeof(post_global);
 size_of_cand=sizeof(cand_global);

start:
 i=0;
 read_post:
      fin1.open(path_name2,ios::binary|ios::in);
      fin1.seekg(0,ios::end);
      no_of_post=fin1.tellg()/size_of_post;
      no_of_post-=1;
      fin1.seekg(0,ios::beg);

    for(u=0; u<=i; u++)
     fin1.read((char*)&post_global,size_of_post);
    fin1.close();

    clrscr();
    all_border();
    gotoxy(4,10);
    cout<<"Now vote for "<<post_global.post<<".";
    gotoxy(20,18);
    cout<<"Press any key.";
    getch();

    k=post_global.id;

     for(u=0;k!=0;u++)
     {
     nam[u]=(k%10)+48;
     k=k/10;
     }

    nam[u]='\0';
    create_path_name(::year,nam);

    j=0;
    fin2.open(path_name,ios::binary);

    if(!fin2)
    {
     fin2.close();
     if(masterflag!=0)
        error(path_name,"Could not open this file while display for voting.");
     else
        error("Could not read records", "Technical issue.");
     return;
    }

      fin2.seekg(0,ios::end);
      no_of_cand=fin2.tellg()/size_of_cand;
      fin2.seekg(0,ios::beg);

    dispcand:
        voting_border(no_of_cand);
        gotoxy(18,8);
        cout<<post_global.post;
        for(u=0,v=10; u<no_of_cand; v+=2,u++)
        {
         fin2.read((char*)&cand_global,size_of_cand);
         gotoxy(3,v);
         cout<<cand_global.stud_id;
         gotoxy(8,v);
         cout<<cand_global.name;
        }
      fin2.close();

      take:
      sid=only_number_input("Enter you choice: ",10,21);
      if(sid<1 || sid>no_of_cand)
        goto take;
      flag=vote(path_name,sid,no_of_cand,size_of_cand);
      if(flag!=1)
      {
       return;
      }

    if(vflag==0)
    {
     voting_status_input(::year);
     vflag=21;
    }

     if(i<no_of_post)
     {
      i++;
      goto read_post;
     }


clrscr();
all_border();

    gotoxy(29,5);
    cout<<"DO NOT PRESS ANY  KEY.";

    for(u=0;u<4;u++)
   {
    gotoxy(30,12);
    cout<<"                          ";
    gotoxy(30,12);
    delay(100);
    cout<<"Thank you for voting !!";
    cout<<'\a';
    delay(520);
    }
 ch=0;


     st:
 clrscr();
 cout<<"\n\n\n\n\t\t* Press Esc to stop voting.";
 cout<<"\n\t\t* Press Enter to continue voting.";
 all_border();
 re:
   ch=getch();
   if(ch==13)
   goto start;

   else if(ch==27)
   {
    st1:
    clrscr();
    all_border();
    gotoxy(20,10);
    cout<<"Press Enter to go back.";
    gotoxy(20,12);
    cout<<"Enter voting password: ";
    password_input();

    if(global_password[0]=='\0')
    goto st;

    flag=strcmp(pass,global_password);

    if(flag!=0)
    {
     cout<<"\n\n\t\t\t\tWRONG PASSWORD.";
     cout<<"\n\n\t\tPress Enter Key.";
     getch();
     goto st1;
     }
    else return;
    }
 else goto re;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
short vote(char fil[],short sid, short no_of_cand, short size_of_cand) //return 0 if not done, 1 if done
{
ifstream fin;
ofstream fout;
char path_name2[50];
strcpy(path_name2,path_name);
char te[2]="W";

fin.open(path_name2,ios::binary);
if(!fin)
{
 clrscr();
 fin.close();
 if(masterflag!=0)
    error(fil,"Could not open this while modifying votes.");
 else
    error("Could not vote.","Technical issue.");
 return 0;
}

create_path_name(::year,te);
fout.open(path_name,ios::binary);
if(!fout)
{
 clrscr();
 fout.close();
 if(masterflag!=0)
    error(fil,"Could not open this while modifying votes.");
 else
    error("Could not vote.","Technical issue.");
 return 0;
}


short i;

for(i=0; i<no_of_cand; i++)
{
 fin.read((char*)&cand_global,size_of_cand);
 if(cand_global.stud_id==sid)
  cand_global.no_of_votes+=1;
 fout.write((char*)&cand_global,size_of_cand);
 }

fin.close();
fout.close();

remove(path_name2);
rename(path_name,path_name2);
return 1;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
inline void box()
{
 int i,j;
 char  x,y;
 all_border();

 x=240;

 y=219;
 for(i=8; i<=11;i++)
 {
  for(j=10; j<=14;j++)
  {
   gotoxy(j,i);
   cout<<y;
   }
  }



 for(i=9; i<=11;i++)     //vote box
 {
  for(j=32; j<=43;j++)
  {
   gotoxy(j,i);
   cout<<y;
   }
  }

 gotoxy(33,10);
 cout<<" VOTE BOX ";


 for(i=8; i<=11;i++)
 {
  for(j=60; j<=67;j++)
  {
   gotoxy(j,i);
   cout<<x;
   }
  }

y=221;
for(j=8;j<=11;j++)
{
 gotoxy(60,j);
 cout<<y;
 }

y=222;
for(j=8;j<=11;j++)
{
 gotoxy(67,j);
 cout<<y;
 }

y=220;
for(i=60;i<=67;i++)
{
 gotoxy(i,7);
 cout<<y;
 }

y=223;
for(i=60;i<=67;i++)
{
 gotoxy(i,12);
 cout<<y;
 }
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

inline void ani()
{
 char x=178;
 char y;
 char ch;
 int i;

for(i=3;i<=12;i++)
{
 gotoxy(i,4);
 cout<<x;
 delay(120);
 gotoxy(i,4);
 cout<<" ";
 }


i--;
x=178;
gotoxy(i,4);
cout<<x;

delay(50);
gotoxy(32,2);
cout<<"Press Enter Key.";

gotoxy(4,13);
cout<<" *****************    Fill Registration Form.    *****************";
gotoxy(3,15);
cout<<"* You need to first Add/ Feed posts in the software before filling form. ";
gotoxy(3,16);
cout<<"* Select the option to fill registration form in main menu.";
gotoxy(3,17);
cout<<"* Enter the year for which you want to fill the registration form.";
gotoxy(3,18);
cout<<"* If voting is done for the year, you cannot fill form.";
gotoxy(3,19);
cout<<"* Max 5 candidates can stand for 1 post/ position.";
gotoxy(3,20);
cout<<"* Form can be modified/ deleted any time if voting is not done.";
gotoxy(3,21);
cout<<"* You can delete all forms for a year if voting is not done.";
gotoxy(3,22);
cout<<"* If voting is done, you need to enter voting password to view form.";
gotoxy(3,23);
cout<<"* Admission number of candidate is the primary key.";

getch();
clrscr();
box();

for(;i<=37;i++)
{
 gotoxy(i,4);
 cout<<x;
 delay(100);
 gotoxy(i,4);
 cout<<" ";
 }

i--;
gotoxy(i,4);
cout<<x--;
delay(100);
gotoxy(i,4);
cout<<x++;
delay(100);
gotoxy(i,4);
cout<<x;

int j;
y=219;
for(j=5;j<9;j++)
{
 gotoxy(37,j);
 cout<<y;
 delay(150);
 gotoxy(37,j);
 cout<<" ";
 }

delay(50);
gotoxy(32,2);
cout<<"Press Enter Key.";

gotoxy(4,13);
cout<<" *******************     Time for voting.   *******************";
gotoxy(3,15);
cout<<"* Opt for voting after forms are filled.";
gotoxy(3,16);
cout<<"* Note if you modify/ delete the name of posts of council after filling.";
gotoxy(3,17);
cout<<"   the forms, the action will have no effect on already filled forms.";
gotoxy(3,18);
cout<<"* To modify the name of post in forms for above action, you need to";
gotoxy(3,19);
cout<<"   delete the form(s) as per your requirement and fill them again.";
gotoxy(3,20);
cout<<"* After voting, records in the database will be fixed and sticked and";
gotoxy(3,21);
cout<<"   hence cannot be modified/ deleted anytime in the future.";
gotoxy(3,22);
cout<<"* NOTE, you will be asked for password to start and to even stop voting.";

getch();
clrscr();
box();

x=178;
for(i=37;i<=63;i++)
{
 gotoxy(i,4);
 cout<<x;
 delay(120);
 gotoxy(i,4);
 cout<<" ";
 }

i--;
gotoxy(32,2);
cout<<"Press Enter Key.";
gotoxy(4,13);
cout<<" *******************    Time for results.    *******************";
gotoxy(3,15);
cout<<"* After voting, you will automatically jump to main menu.";
gotoxy(3,16);
cout<<"* Opt to see records and search for the record of the year to see results.";
gotoxy(3,17);
cout<<"* You need to enter voting password to see records/ form of a year if for.";
gotoxy(3,18);
cout<<"   that particular year, voting is already done.";
gotoxy(3,19);
cout<<"* You will be asked for password to delete a particular record.";
gotoxy(3,20) ;
cout<<"* NOTE, the 3 passwords, to open software, start and stop voting";
gotoxy(3,21);
cout<<"   and to modify /delete a record should not be identical.";

for(;;)
{
gotoxy(i,4);
cout<<x--;
delay(100);
gotoxy(i,4);
cout<<x++;
delay(100);

if(kbhit())
{
 ch=getch();
 if(ch==13)
 break;
 }
}

clrscr();
  cout<<"\n\n\n\n\tThis Software is created by Vaibhav Gupta.";
  cout<<"\n\tClass 12th-B. Batch: 2015 - 2016";
  cout<<"\n\n\t\t\tFor any queries contact: ";
  cout<<"\n\t\tMobile: +91 7503063253";
  cout<<"\n\t\temail - vaibhavgupta40@gmail.com";
  cout<<"\n\n\n\n\n\n\n\t\t\t\tPress Enter Key.";
  all_border();
  getch();
}











/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/





























/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void gotoxy(int x, int y)
{
 coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

 void set_window_size()
 {
  system("mode 81,26");
  SMALL_RECT WinRect = {0,0,81,26};
  SMALL_RECT* WinSize =&WinRect;
  SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),true, WinSize);
 }

void clrscr()
 {
  system("cls");
 }


void delay(int x)
{
 clock_t goal=x+clock();
 while(goal>clock());
}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/



