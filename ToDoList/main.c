#include <stdio.h>
#include <string.h>
struct ToDo{
    int no;
    char task[200];
    int availability;
};

int main(){
    struct ToDo x[15];
    int ch=-1, i=0;
    int deleted_no;

    FILE *fp = fopen("ToDoList.txt", "a+");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }
    rewind(fp);
    while(fscanf(fp,"%d,%[^,],%d",&x[i].no,x[i].task,&x[i].availability)!=EOF)
    {
        i++;
    }
    rewind(fp);
    
    while (ch!=0)
    {
        switch(ch)
        {
            case -1:
                {
                    printf("Welcome to ToDo List\n");
                    printf("Menu\n----------\n");
                    printf("To go out,0\n");
                    printf("To add to the list,1\n");
                    printf("To remove from list,2\n");
                    printf("To see the list,3\n");
                    printf("Your choice:");
                    scanf("%d",&ch);
                    break;
                }
            case 1:
                {
                    x[i].no=i+1;
                    x[i].availability=0;
                    printf("Enter your task:");
                    while(getchar() != '\n');
                    fgets(x[i].task,200,stdin);
                    x[i].task[strcspn(x[i].task, "\n")] = '\0';
                    fprintf(fp,"%d,%s,%d\n",x[i].no,x[i].task,x[i].availability);
                    fflush(fp);//yazılanları hemen dosyaya yazıyormuş
                    i++;
                    printf("Your choice:");
                    scanf("%d", &ch);
                    
                    break;
                }
            case 2:
                {
                    printf("Enter the task number you wish to delete:");
                    scanf("%d",&deleted_no);
                    fclose(fp);
                    FILE *gecici = fopen("gecici.txt", "w");
                    int new_i = 0; 
                    for(int j = 0; j < i; j++) {
                        if(x[j].no != deleted_no) {
                            x[j].no = new_i + 1;
                            x[new_i] = x[j];
                            fprintf(gecici, "%d,%s,%d\n", x[j].no, x[j].task, x[j].availability);
                            new_i++;
                        }
                    }
                    i = new_i;
                    fclose(gecici);
                    remove("ToDoList.txt");
                    rename("gecici.txt","ToDoList.txt");
                    printf("Your choice:");
                    scanf("%d", &ch);
                    fp = fopen("ToDoList.txt", "a+");
                    break;
                }
            case 3:
                {
                    printf("current list:\n");
                    for(int j=0;j<i;j++)
                    {
                        if(x[j].availability==0)printf("%d)%s,not completed:(\n",x[j].no,x[j].task);
                        else printf("%d)%s,completed:)\n",x[j].no,x[j].task);
                    }
                    printf("Your choice:");
                    scanf("%d", &ch);
                    break;   
                }
            default :
                {
                    printf("invalid transaction,You are being sent to menu");
                    ch=-1;
                    break;
                }
            
        }
    }
    fclose(fp);
    return 0;
}