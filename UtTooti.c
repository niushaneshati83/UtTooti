#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<f.h>

struct Post{
    //char* Text;
    char Text[500];
    int Post_size;
    int Post_Id;
    int Like_Num;
    struct Post* Next;
};
struct User{
    char User_Name[500];
    int User_Name_Len;
    char Pass[500];
    int Pass_Len;
    int Total_Post;
    int Total_Like;
    struct Post* First_Post;
    struct Post* Last_Post;
};
struct UT_TOOTI{
    struct User *List[1000];
    int index;
    int temp;
};

struct UT_TOOTI Social_Network;

void Sign_Up(char username[],char pass[], int j, int u){
    struct User* new_user= (struct User*) malloc(1*sizeof(struct User));
    new_user->User_Name=username;
    for (int i=0; i<u; i++) new_user->User_Name[i]=username[i];
    new_user->Pass=pass;
    for (int i=0; i<j; i++) new_user->Pass[i]=pass[i];
    new_user->User_Name_Len=u;
    new_user->Pass_Len=j;
   for (int i=0; i<strlen(username); i++) new_user->User_Name[i]=username[i];
   for (int i=0; i<strlen(pass); i++) new_user->Pass[i]=pass[i];
    new_user->Total_Like=0;
    new_user->Total_Post=0;
    new_user->First_Post=NULL;
    new_user->Last_Post=NULL;

    Social_Network.List[Social_Network.index]=new_user;
    Social_Network.temp=Social_Network.index;
    Social_Network.index= Social_Network.index+1;
}

int same(char a[], char b[], int i, int j){
    if (i!=j) return 0;
    int ch=0;
    for (int k=0; k<i; k++){
        if (a[k]!=b[k]) ch=1;
    }
    if (ch==1) return 0;
    return 1;
}

void Log_In(char username[],char pass[], int j, int u){
    int finder=-1;
    for (int i=0; i<Social_Network.index; i++){
        if (Social_Network.List[i]->User_Name==username){
            finder=i;
            break;
        }
        if (same(username,Social_Network.List[i]->User_Name,u,Social_Network.List[i]->User_Name_Len)==1) {
            finder=i;
            break;
        } 
    }
    if (finder==-1) {
        printf("Not Valid Username! \n");
    }
    else {
       if (pass!=Social_Network.List[finder]->Pass){
            printf("Incorrect Password! \n");
        }
        int farghdare=0;
        if (j!=Social_Network.List[finder]->Pass_Len) {
            farghdare=1;
            
        }
        for (int i=0; i<j; i++) if (pass[i]!=Social_Network.List[finder]->Pass[i]) farghdare=1;

        if (farghdare==1){
            printf("Incorrect Password! \n");
        }
        else {
            Social_Network.temp=finder;
        }
    }
}

void Post_Maker(char text[], int lll){//check
    if (Social_Network.temp!=-1){
        if (Social_Network.List[Social_Network.temp]->Total_Post==0){
            struct Post* new_post= (struct Post*) malloc(1*sizeof(struct Post));
            new_post->Like_Num=0;
            new_post->Next=NULL;
            new_post->Post_Id=1;
            //new_post->Text=text;
            for (int i=0; i<lll; i++) new_post->Text[i]=text[i];
            new_post->Post_size=lll;
            Social_Network.List[Social_Network.temp]->First_Post=new_post;
            Social_Network.List[Social_Network.temp]->Last_Post=new_post;
            Social_Network.List[Social_Network.temp]->Last_Post->Next=NULL;
        }
        else {
            struct Post* new_post= (struct Post*) malloc(1*sizeof(struct Post));
            new_post->Like_Num=0;
            new_post->Next=NULL;
            new_post->Post_Id= Social_Network.List[Social_Network.temp]->Total_Post+1;
            //new_post->Text=text;
            for (int i=0; i<lll; i++) new_post->Text[i]=text[i];
            new_post->Post_size=lll;
            Social_Network.List[Social_Network.temp]->Last_Post->Next=new_post;
            Social_Network.List[Social_Network.temp]->Last_Post=Social_Network.List[Social_Network.temp]->Last_Post->Next;
            Social_Network.List[Social_Network.temp]->Last_Post->Next=NULL;
        }
        Social_Network.List[Social_Network.temp]->Total_Post=Social_Network.List[Social_Network.temp]->Total_Post+1;
    }
}

void Like(char username[], int post_id, int u){//check


    if (Social_Network.temp!=-1 ){
        int finder=-1;
        for (int i=0; i<Social_Network.index; i++){
            if (same(username,Social_Network.List[i]->User_Name,u,Social_Network.List[i]->User_Name_Len)==1) {
                finder=i;
                break;
            } 
        }
        if (finder==-1) {
            //printf(Social_Network.List[finder]->Total_Post);
            printf("Not Valid Username or TotalPost Error!!!\n");
        }
        else {
            int ppp= Social_Network.List[finder]->Total_Post;
            //printf("%d , %d \n",ppp,post_id);
            if (ppp>=post_id){
                
                struct Post* zzz= Social_Network.List[finder]->First_Post;
                
                int yyy=1;
                while (yyy<post_id && zzz!=NULL){
                    
                    yyy=yyy+1;
                    zzz= zzz->Next;
                }
                
                int lll=zzz->Like_Num;
                int ttt= Social_Network.List[finder]->Total_Like;
                
                ttt=ttt+1;
                lll=lll+1;
                zzz->Like_Num = lll;
                Social_Network.List[finder]->Total_Like = ttt;
            }
            
           
        }
    }
}

void Log_Out(){
    Social_Network.temp=-1;
}


void Delete(int post_id){//check
    struct Post* zzz= Social_Network.List[Social_Network.temp]->First_Post;
    int yyy=1;
    if (post_id==1){
        Social_Network.List[Social_Network.temp]->Total_Post=Social_Network.List[Social_Network.temp]->Total_Post-1;
        Social_Network.List[Social_Network.temp]->Total_Like=Social_Network.List[Social_Network.temp]->Total_Like-(zzz->Like_Num);
        zzz=zzz->Next;
        Social_Network.List[Social_Network.temp]->First_Post=zzz;

    }
    else {
        while (yyy<post_id-1){
            zzz=zzz->Next;
            yyy=yyy+1;
        }
        struct Post* ccc= zzz->Next;
        zzz->Next= ccc->Next;
        Social_Network.List[Social_Network.temp]->Total_Post=Social_Network.List[Social_Network.temp]->Total_Post-1;
        Social_Network.List[Social_Network.temp]->Total_Like=Social_Network.List[Social_Network.temp]->Total_Like-(ccc->Like_Num);
        free(ccc);
    }
    
}

void Info(){//check
    for (int i=0; i<Social_Network.List[Social_Network.temp]->User_Name_Len; i++) printf("%c",Social_Network.List[Social_Network.temp]->User_Name[i]);
    printf("\n");
    for (int i=0; i<Social_Network.List[Social_Network.temp]->Pass_Len; i++) printf("%c",Social_Network.List[Social_Network.temp]->Pass[i]);
    printf("\n");
    // printf("%s %s  \n",Social_Network.List[Social_Network.temp]->User_Name,Social_Network.List[Social_Network.temp]->Pass);
    printf("%d : \n",Social_Network.List[Social_Network.temp]->Total_Post);
    struct Post* zzz= Social_Network.List[Social_Network.temp]->First_Post;
    int yyy=1;
    while (zzz!=NULL){
        //printf("POSTID: %d  TEXT: %s   LIKES: %d   \n",zzz->Post_Id,zzz->Text,zzz->Like_Num);
        printf("POSTID: %d  TEXT: ",zzz->Post_Id);
        for (int i=0; i<(zzz->Post_size); i++) printf("%c",zzz->Text[i]);
        printf("    LIKES: %d  \n",zzz->Like_Num);
        zzz=zzz->Next;
    }
   // if (zzz!=NULL) printf("POSTID: %d  TEXT: %s   LIKES: %d   \n",zzz->Post_Id,zzz->Text,zzz->Like_Num);
}

void Find_User(char username[], int u){//check
    int finder=-1;
    for (int i=0; i<Social_Network.index; i++){
        if (same(username,Social_Network.List[i]->User_Name,u,Social_Network.List[i]->User_Name_Len)==1) {
            finder=i;
            break;
        } 
    }
    if (finder==-1) {
        printf("Not Valid Username! \n");
    }
    else {
         for (int i=0; i<Social_Network.List[finder]->User_Name_Len; i++) printf("%c",Social_Network.List[finder]->User_Name[i]);
        printf("\n");
        printf("%d : \n",Social_Network.List[finder]->Total_Post);
        struct Post* zzz= Social_Network.List[finder]->First_Post;
        int yyy=1;
        while (zzz!=NULL){
            //printf("POSTID: %d  TEXT: %s   LIKES: %d   \n",zzz->Post_Id,zzz->Text,zzz->Like_Num);
            printf("POSTID: %d  TEXT: ",zzz->Post_Id);
            for (int i=0; i<(zzz->Post_size); i++) printf("%c",zzz->Text[i]);
            printf("    LIKES: %d  \n",zzz->Like_Num);
            zzz=zzz->Next;
        }
        //printf("POSTID: %d  TEXT: %s   LIKES: %d   \n",zzz->Post_Id,zzz->Text,zzz->Like_Num);
    }
}

int strconvertint(char s[], int sizee){//Check
    int num=0;
    for (int i=0; i<sizee; i++){
      //  printf("%c",s[i]);
        num*=10;
        num+=(s[i]-'0');
    }
    return num;
}*/

int main(){
    int MaxN=1000;  
 
   Social_Network.index=0;
   Social_Network.temp=-1;
    int manager=1;
    while (manager==1){
        printf("\n");
        char order[MaxN];
        gets(order);
        char substring[4];
        for (int i=0; i<4; i++) substring[i]=order[i];
        
        if (substring[0]=='s'){//signup

            char username[MaxN];
            int i=7;
            int j=0;
            while (order[i]!=' '){
                username[j]=order[i];
                j++;
                i++;
            }       
            int u=j;
            char pass[MaxN];
            j=0;
            i++;
            while (i<strlen(order)){
                pass[j]=order[i];
                i++;
                j++;
            }     
            
            Sign_Up(username,pass,j,u);
            
            FILE *acc = fopen("account.txt","w");
            for (i=0; i<Social_Network.index; i++){
                //social_network.list[i]->u,p,t
                fwrite(Social_Network.List[i]->User_Name,sizeof(char),Social_Network.List[i]->User_Name_Len,acc);
                fwrite(" ",sizeof(char),1,acc);
                fwrite(Social_Network.List[i]->Pass,sizeof(char),Social_Network.List[i]->Pass_Len,acc);
                fwrite(" ",sizeof(char),1,acc);
                
                char str[50];
                snprintf(str,50,"%d\n" ,Social_Network.List[i]->Total_Post);
                fwrite(str,sizeof(char),strlen(str),acc);
                fwrite("\n",sizeof(char),strlen("\n"),acc);
            }
            
            fclose(acc);
            
        
        }
        else if (substring[0]=='l' && substring[3]=='i'){//login
            char username[MaxN];
            int i=6;
            int j=0;
            while (order[i]!=' '){
                username[j]=order[i];
                j++;
                i++;
            }      
            int u=j;
            char pass[MaxN];
            j=0;
            i++;
            while (i<strlen(order)){
                pass[j]=order[i];
                i++;
                j++;
            }     
            //printf("%s %d ",pass,j);
            Log_In(username,pass,j,u);
        }
        else if (substring[0]=='p'){//post
            char text[MaxN];
            int i=5;
            int j=0;
            while (i<strlen(order)){
                text[j]=order[i];
                i++;
                j++;
            } 
             
            Post_Maker(text,j);

            FILE *acc = fopen("account.txt","w");
            for (i=0; i<Social_Network.index; i++){
                //social_network.list[i]->u,p,t
                fwrite(Social_Network.List[i]->User_Name,sizeof(char),Social_Network.List[i]->User_Name_Len,acc);
                fwrite(" ",sizeof(char),1,acc);
                fwrite(Social_Network.List[i]->Pass,sizeof(char),Social_Network.List[i]->Pass_Len,acc);
                fwrite(" ",sizeof(char),1,acc);
                
                char str[50];
                snprintf(str,50,"%d\n" ,Social_Network.List[i]->Total_Post);
                fwrite(str,sizeof(char),strlen(str),acc);
                fwrite("\n",sizeof(char),strlen("\n"),acc);
            }
            
            fclose(acc);

            FILE *pos = fopen("post.txt","w");
            for (i=0; i<Social_Network.index; i++){
                //social_network.list[i]->u,p,t
                struct Post* zzz= Social_Network.List[i]->First_Post;
                while (zzz!=NULL){
                    fwrite(Social_Network.List[i]->User_Name,sizeof(char),Social_Network.List[i]->User_Name_Len,pos);
                    fwrite(" ",sizeof(char),1,pos);
                    //fwrite(Social_Network.List[i]->Pass,sizeof(char),Social_Network.List[i]->Pass_Len,acc);
                    //fwrite(" ",sizeof(char),1,acc);
                    fwrite(zzz->Text,sizeof(char),zzz->Post_size, pos);
                    fwrite(" ",sizeof(char),1,pos);

                    char str[50];
                    snprintf(str,50,"%d\n" ,zzz->Like_Num);
                    fwrite(str,sizeof(char),strlen(str),pos);
                    fwrite("\n",sizeof(char),strlen("\n"),pos);

                    zzz=zzz->Next;
                }
            }
            
            fclose(pos);
        }
        else if (substring[0]=='l' && substring[2]=='k'){//like
            char username[MaxN];
            int i=5;
            int j=0;
            while (order[i]!=' '){
                username[j]=order[i];
                j++;
                i++;
            }   
            int u=j;  
            char postd[MaxN];
            j=0;
            i++;
            printf("%d \n",i);
            while (i<strlen(order)){
                postd[j]=order[i];
                printf("%c",postd[j]);
                i++;
                j++;
            }     
            int ppp= strconvertint(postd,j);
            //printf("\n %d\n",ppp);
            Like(username,ppp,u);
             FILE *pos = fopen("post.txt","w");
            for (i=0; i<Social_Network.index; i++){
                //social_network.list[i]->u,p,t
                struct Post* zzz= Social_Network.List[i]->First_Post;
                while (zzz!=NULL){
                    fwrite(Social_Network.List[i]->User_Name,sizeof(char),Social_Network.List[i]->User_Name_Len,pos);
                    fwrite(" ",sizeof(char),1,pos);
                    //fwrite(Social_Network.List[i]->Pass,sizeof(char),Social_Network.List[i]->Pass_Len,acc);
                    //fwrite(" ",sizeof(char),1,acc);
                    fwrite(zzz->Text,sizeof(char),zzz->Post_size, pos);
                    fwrite(" ",sizeof(char),1,pos);

                    char str[50];
                    snprintf(str,50,"%d\n" ,zzz->Like_Num);
                    fwrite(str,sizeof(char),strlen(str),pos);
                    fwrite("\n",sizeof(char),strlen("\n"),pos);

                    zzz=zzz->Next;
                }
            }
            
            fclose(pos);
        }
        else if (substring[0]=='l' && substring[2]=='g'){//logout
            Log_Out();
        }
        else if (substring[0]=='d'){//delete
            char postd[MaxN];
            int i=7;
            int j=0;
            while (i<strlen(order)){
                postd[j]=order[i];
                i++;
                j++;
            }     
            int ppp= strconvertint(postd,j);
            Delete(ppp);

             FILE *acc = fopen("account.txt","w");
            for (i=0; i<Social_Network.index; i++){
                //social_network.list[i]->u,p,t
                fwrite(Social_Network.List[i]->User_Name,sizeof(char),Social_Network.List[i]->User_Name_Len,acc);
                fwrite(" ",sizeof(char),1,acc);
                fwrite(Social_Network.List[i]->Pass,sizeof(char),Social_Network.List[i]->Pass_Len,acc);
                fwrite(" ",sizeof(char),1,acc);
                
                char str[50];
                snprintf(str,50,"%d\n" ,Social_Network.List[i]->Total_Post);
                fwrite(str,sizeof(char),strlen(str),acc);
                fwrite("\n",sizeof(char),strlen("\n"),acc);
            }
            
            fclose(acc);

             FILE *pos = fopen("post.txt","w");
            for (i=0; i<Social_Network.index; i++){
                //social_network.list[i]->u,p,t
                struct Post* zzz= Social_Network.List[i]->First_Post;
                while (zzz!=NULL){
                    fwrite(Social_Network.List[i]->User_Name,sizeof(char),Social_Network.List[i]->User_Name_Len,pos);
                    fwrite(" ",sizeof(char),1,pos);
                    //fwrite(Social_Network.List[i]->Pass,sizeof(char),Social_Network.List[i]->Pass_Len,acc);
                    //fwrite(" ",sizeof(char),1,acc);
                    fwrite(zzz->Text,sizeof(char),zzz->Post_size, pos);
                    fwrite(" ",sizeof(char),1,pos);

                    char str[50];
                    snprintf(str,50,"%d\n" ,zzz->Like_Num);
                    fwrite(str,sizeof(char),strlen(str),pos);
                    fwrite("\n",sizeof(char),strlen("\n"),pos);

                    zzz=zzz->Next;
                }
            }
            
            fclose(pos);
        }
        else if (substring[2]=='f'){//info
            printf("\n");
            Info();
            printf("\n");
        }
        else if (substring[0]=='f'){//find_user
            char username[MaxN];
            int i=10;
            int j=0;
            while (i<strlen(order)){
                username[j]=order[i];
                j++;
                i++;
            }     
            printf("\n");
            Find_User(username,j);
            
        }
    }
}
