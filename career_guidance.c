#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

#define INFINITY 9999
#define MAX 10
#define MAX_SIZE 35
#define MAX_VERTICES 100
#define MAX_LINE_LENGTH 100
#define MAX_STRINGS 5
#define MAX_STRING_LENGTH 20
#define ROWS 35
#define COLS 35


int mat[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

//structure to store student details
struct student
{
    char fname[10];
    char lname[10];
    int rank;
    char email[20];
};

//structure to store college details
struct college {
    char state[100];
    char name[100];
    char location[100];
};


void bubblesort(struct student *s)
{
    struct student temp;
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(s[j].rank>s[j+1].rank)
            {
                temp=s[j];
                s[j]=s[j+1];
                s[j+1]=temp;
            }
        }
    }
}

//this function is used to make the text color in console red
void red () {
  printf("\033[1;31m");
}


void reset()
{
	printf("\033[0m");
}

//this function is used to make the text color in console purple
void purple()
{
    printf("\033[0;35m");
}

//this function is used to make the text color in console green
void green()
{
    printf("\033[0;32m");
}

//this function is used to make the text color in console yellow
void yellow()
{
    printf("\033[1;33m");
}

//this function is used to make the text color in console cyan
void cyan()
{
    printf("\033[0;36m");
}

//this function is used to make the text color in console orange
void orange()
{
    printf("\033[38;2;255;165;0m");
}

//this function is used to make the text color in console blue
void blue()
{
    printf("\033[0;34m");
}

//this function is used to make the text color in console light purple
void lightpurple()
{
    printf("\033[1;35m");
}

// To calculate the minimum distance which is used in dijkstra algorithm
int minDistance(int dist[], int sptSet[], int n)
{
    int min = INFINITY, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dfs(int i, int j, int visited[][COLS], FILE* fp2) {
    visited[i][j] = 1;
    fprintf(fp2, "%d\n", j);
    // write current node to file
    // explore neighbors
    if (i-1 >= 0 && mat[i-1][j] && !visited[i-1][j])
        dfs(i-1, j, visited, fp2);
    if (i+1 < ROWS && mat[i+1][j] && !visited[i+1][j])
        dfs(i+1, j, visited, fp2);
    if (j-1 >= 0 && mat[i][j-1] && !visited[i][j-1])
        dfs(i, j-1, visited, fp2);
    if (j+1 < COLS && mat[i][j+1] && !visited[i][j+1])
        dfs(i, j+1, visited, fp2);
}


void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // partition the array and get the pivot index
        int pivot_index = low;
        int pivot_value = arr[high];
        for (int i = low; i < high; i++) {
            if (arr[i] < pivot_value) {
                int temp = arr[i];
                arr[i] = arr[pivot_index];
                arr[pivot_index] = temp;
                pivot_index++;
            }
        }
        int temp = arr[pivot_index];
        arr[pivot_index] = arr[high];
        arr[high] = temp;

        // recursively quicksort the left and right subarrays
        quicksort(arr, low, pivot_index - 1);
        quicksort(arr, pivot_index + 1, high);
    }
}



//to find the correct match-check suffix
void goodSuffix(char* pat, int M, int* suffix)
{
    int len = 0;

    suffix[0] = 0; // suffix[0] is always 0

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len])
        {
            len++;
            suffix[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = suffix[len - 1];
            }
            else
            {
                suffix[i] = 0;
                i++;
            }
        }
    }
}

//compares pattern with given text and finds match
void KMP(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int suffix[M];

    goodSuffix(pat, M, suffix);

    int i = 0;  // index for txt[]
    int j = 0;  // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            //printf("Pattern found at index %d\n", i - j);
            j = suffix[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match suffix[0..suffix[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = suffix[j - 1];
            else
                i = i + 1;
        }
    }
}

// Function to read the colleges from a file and store them in an array
void read_colleges(struct college colleges[], int* num_colleges)
{
    FILE* fp = fopen("colleges.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        char* state = strtok(line, ","); //strtok-breaks string str into a series of tokens using the delimiter delim.
        char* name = strtok(NULL, ",");
        char* location = strtok(NULL, ",");
        if (state && name && location)
        {
            // Add college to array
            strcpy(colleges[*num_colleges].state, state);
            strcpy(colleges[*num_colleges].name, name);
            strcpy(colleges[*num_colleges].location, location);
            (*num_colleges)++;
        }
    }
    fclose(fp);
}

// Function to retrieve the colleges based on a given state
void get_colleges_by_state(struct college colleges[], int num_colleges, char* state, char results[][500]) {
    int num_results = 0;
    for (int i = 0; i < num_colleges; i++)
    {
        if (strcmp(colleges[i].state, state) == 0)
        {
            strcpy(results[num_results], colleges[i].name);
            num_results++;
        }
    }
    results[num_results][0] = '\0'; // Add null terminator to end of results
}


//to calculate min distance of a city from other places in a state
void dijkstra(int graph[MAX][MAX],int n,int startnode)
{

    int dist[MAX];
    int sptSet[MAX];

    for (int i = 0; i < n; i++)
        dist[i] = INFINITY, sptSet[i] = 0;

    dist[startnode] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minDistance(dist, sptSet,n);
        sptSet[u] = 1;

        for (int v = 0; v < n; v++)

            if (!sptSet[v] && graph[u][v] && dist[u] != INFINITY && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    orange();
    printf("All distances are with respect to vertex %d\n",startnode);
    reset();
    green();
    printf("Vertex \t Distance from Source\n");
    reset();
    for (int i = 0; i < n; i++)
    {
         cyan();
        printf("  %d\t\t %d\n", i, dist[i]);
        reset();
    }
}


int main()
{
    //create structure to store student details
      struct student s[20];
      // Create an array to store the colleges
      struct college colleges[2000];
      int num_colleges = 0;
      int ch,i,n=1;// n-no. of students
         int visited[ROWS][COLS] = {0};
      //create a matrix G
      int G[MAX][MAX];
      int j,v,u;
      //create a string pat
      char pat[10];

      char txt[]="10th Diploma Governmentservice Science Commerce Arts B.Sc B.Pharma B.E. BAMS MBBS BDS B.Com BBA C.A. BSW B.A. LLB LLM M.A. MSW BCA MCA MBA M.Com B.Ed M.Ed C.S. MDS MD M.Tech M.Pharma M.Sc Ph.D";
      //declare FILE pointers
      FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7,*fp8;

      orange();
      printf("CAREER GUIDANCE:\n");
      reset();

      yellow();
      printf("If you're looking for career guidance, the first step is to take stock of your interests, skills, and values. This will help you identify potential careers that align with your strengths and goals. It's also important to research different career options and talk to professionals in the field to gain insights and advice.\n");
      printf("With some effort and exploration, you can find a fulfilling career that matches your passions and skills.\n");
      reset();

      purple();
      //read student structure
      printf("\nEnter your details to proceed further:\n");
      reset();

      green();
       printf("Enter | first name | last name | rank | email:\n");
       reset();

       // fp1=fopen("students1.txt","w");
        for(i=0;i<n;i++)
        {
            scanf("%s %s %d %s",s[i].fname,s[i].lname,&s[i].rank,s[i].email);
           // fprintf(fp1,"%s %s %d %s\n",s[i].fname,s[i].lname,s[i].rank,s[i].email);
        }

       bubblesort(s);

        fp1=fopen("students1.txt","w");
        for(i=0;i<n;i++)
        {
            //scanf("%s %s %d %s",s[i].fname,s[i].lname,&s[i].rank,s[i].email);
            fprintf(fp1,"%s %s %d %s\n",s[i].fname,s[i].lname,s[i].rank,s[i].email);
        }

        fclose(fp1);

    while(1)

    {
        orange();
        printf("\n1.Reviewing list of all courses\n");
        printf("2.Enter the degree of your choice to get the guidance about it\n");
        printf("3.Want to know job opportunity for the degree you are searching for??:\n");
        printf("4.Just enter the state and know the best colleges in them\n");
        printf("5.To check the distances between the colleges in the below given states\n");
        printf("6.Exit\n\n");
        reset();

        yellow();
        printf("Enter choice:\n");
        reset();

        scanf("%d",&ch);

        switch(ch)
        {

            case 1://displaying list of courses to ease the searching
                    fp2=fopen("graph.txt", "r");
                     for(int a=0;a<35;a++)
                     {
                         for(int b=0;b<35;b++)
                         {
                             fscanf(fp2,"%d",&mat[a][b]);
                         }
                     }
                    fclose(fp2);
                     fp2 = fopen("output.txt", "w");
                    for (int i = 0; i < ROWS; i++)
                    {
                        for (int j = 0; j < COLS; j++)
                        {
                                if (!visited[i][j] && mat[i][j])
                                {
                                    dfs(i, j, visited, fp2);
                                }
                        }
                    }
                    fclose(fp2);
                    fp2=fopen("output.txt","r");
                    int a[100];
                    for(int i=0;i<37;i++)
                    {
                        fscanf(fp2,"%d",&a[i]);
                    }

                    fclose(fp2);
                   /* for(int i=0;i<36;i++)
                    {
                        printf("%d ",a[i]);
                    }*/
                   // printf("\n");

                    quicksort(a, 0, 34);
                    int c2=0,c5=0,c3=0,c4=0,c19=0,c6=0;
                    green();
                    //printf("Sorted array: \n");
                    reset();
                   /* for(int i=0;i<n;i++)
                    {
                        printf("%d ",a[i]);
                    }*/
                    lightpurple();
                    for (int i = 0; i < 37; i++)
                    {
                       //printf("%d ", a[i]);
                        if(a[i]==0)
                        {
                            printf("10th \t");
                        }
                        if(a[i]==1)
                        {
                            printf("Diploma \t");
                        }
                        if(a[i]==2)
                        {
                            if(c2<1)
                            {
                                printf("Govt services \t");
                                c2++;
                            }
                            else
                                continue;
                        }
                        if(a[i]==3)
                        {
                            if(c3<1)
                            {
                                printf("science \t");
                                c3++;
                            }
                            else
                                continue;
                        }
                        if(a[i]==4)
                        {
                            if(c4<1)
                            {
                                printf("Commerce\t");
                                c4++;
                            }
                            else
                                continue;
                        }
                        if(a[i]==5)
                        {
                            if(c5<1)
                            {
                                printf("Arts\t");
                                c5++;
                            }
                            else
                                continue;
                        }
                        if(a[i]==6)
                        {
                             if(c6<1)
                            {
                                printf("Arts\t");
                                c6++;
                            }
                            else
                                continue;
                        }
                        if(a[i]==7)
                        {
                            printf("B.Sc \t");
                        }
                        if(a[i]==8)
                        {
                            printf("B.Pharma \t");
                        }
                        if(a[i]==9)
                        {
                            printf("B.E. \t");
                        }
                        if(a[i]==10)
                        {
                            printf("BAMS \t");
                        }
                        if(a[i]==11)
                        {
                            printf("MBBS \t");
                        }
                        if(a[i]==12)
                        {
                            printf("BDS \t");
                        }
                        if(a[i]==13)
                        {
                            printf("B.Com \t");
                        }
                        if(a[i]==14)
                        {
                            printf("BBA \t");
                        }
                        if(a[i]==15)
                        {
                            printf("CA \t");
                        }
                        if(a[i]==16)
                        {
                            printf("BSW \t");
                        }
                        if(a[i]==17)
                        {
                            printf("B.A. \t");
                        }
                        if(a[i]==18)
                        {
                            printf("LLB \t");
                        }
                        if(a[i]==19)
                        {
                           if(c19<1)
                            {
                                printf("LLM \t");
                                c19++;
                            }
                            else
                                continue;
                        }
                        if(a[i]==20)
                        {
                          printf("M.A. \t\n");
                        }
                        if(a[i]==21)
                        {
                           printf("MSW \t");
                        }
                        if(a[i]==22)
                        {
                            printf("BCA \t");
                        }
                        if(a[i]==23)
                        {
                            printf("MCA \t");
                        }
                        if(a[i]==24)
                        {
                            printf("MBA \t");
                        }
                        if(a[i]==25)
                        {
                           printf("M.Com \t");
                        }
                        if(a[i]==26)
                        {
                            printf("B.Ed \t");
                        }
                        if(a[i]==27)
                        {
                            printf("M.Ed \t\n");
                        }
                        if(a[i]==28)
                        {
                            printf("C.S. \t");
                        }
                        if(a[i]==29)
                        {
                            printf("MDS \t");
                        }
                        if(a[i]==30)
                        {
                            printf("MD \t");
                        }
                        if(a[i]==31)
                        {
                            printf(" M.Tech \t");
                        }
                        if(a[i]==32)
                        {
                            printf("M.Pharma \t");
                        }
                        if(a[i]==33)
                        {
                            printf("M.Sc \t");
                        }
                        if(a[i]==34)
                        {
                            printf("Ph.D \t\n");
                        }

                    }
                    printf("\n");
                    reset();

                     break;

            case 2: yellow();
                    // getting degree and finding the path to it
                    printf("Enter the degree you are interested in :\n");
                    reset();
                    scanf("%s",pat);
                    red();
                    KMP(pat, txt);
                    if(strcasecmp(pat,"Diploma")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->Diploma\n");
                        printf("Period of Study:3 years\n");
                    }
                    else if(strcasecmp(pat,"Government Service")==0)
                    {
                        printf("Exam required:UPSC\n");
                        printf("Guiding path:10th-->Government Service\n");
                        printf("Period of Study:Direct Exam or after 12th\n");
                    }
                    else if(strcasecmp(pat,"Science")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Science)\n");
                        printf("Period of Study:2 years\n");
                    }
                    else if(strcasecmp(pat,"Commerce")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Commerce)\n");
                        printf("Period of Study:2 years\n");
                    }
                    else if(strcasecmp(pat,"Arts")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Arts)\n");
                        printf("Period of Study:2 years\n");
                    }
                    else if(strcasecmp(pat,"B.Arch")==0)
                    {
                        printf("Exam required:NATA\n");
                        printf("Guiding path:10th-->12th(Science)-->B.Arch\n");
                        printf("Period of Study:2+5=7 years\n");
                    }
                    else if(strcasecmp(pat,"B.Sc")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Science)-->B.Sc\n");
                        printf("Period of Study:2+4=6 years\n");
                    }
                    else if(strcasecmp(pat,"B.Pharma")==0)
                    {
                        printf("Exam required:CET\n");
                        printf("Guiding path:10th-->12th(Science)-->B.Pharma\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"B.E")==0)
                    {
                        printf("Exam required:CET/JEE\n");
                        printf("Guiding path:10th-->12th(Science)-->B.E\n");
                        printf("Period of Study:2+4=6 years\n");
                    }
                    else if(strcasecmp(pat,"BAMS")==0)
                    {
                        printf("Exam required:NEET\n");
                        printf("Guiding path:10th-->12th(Science)-->BAMS\n");
                        printf("Period of Study:2+5=7 years\n");
                    }
                    else if(strcasecmp(pat,"MBBS")==0)
                    {
                        printf("Exam required:NEET\n");
                        printf("Guiding path:10th-->12th(Science)-->MBBS\n");
                        printf("Period of Study:2+5=7 years\n");
                    }
                    else if(strcasecmp(pat,"BDS")==0)
                    {
                        printf("Exam required:NEET\n");
                        printf("Guiding path:10th-->12th(Science)-->BDS\n");
                        printf("Period of Study:2+4=6 years\n");
                    }
                    else if(strcasecmp(pat,"B.Com")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Commerce)-->B.Com\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"BBA")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Commerce)-->BBA\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"CA")==0)
                    {
                        printf("Exam required:CA Foundation->CA Intermediate->CA Final\n");
                        printf("Guiding path:10th-->12th(Commerce)-->CA\n");
                        printf("Period of Study:2+5=7 years\n");
                    }
                    else if(strcasecmp(pat,"BSW")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Arts)-->BSW\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"B.A.")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Arts)-->B.A\n");
                        printf("Period of Study:2+4=6 years\n");
                    }
                    else if(strcasecmp(pat,"LLB")==0)
                    {
                        printf("Exam required:CLAT\n");
                        printf("Guiding path:10th-->12th(Arts)-->LLB\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"LLM")==0)
                    {
                        printf("Exam required:CLAT\n");
                        printf("Guiding path:10th-->12th(Arts)-->LLB-->LLM\n");
                        printf("Period of Study:2+3+2=7 years\n");
                    }
                    else if(strcasecmp(pat,"M.A")==0)
                    {
                        printf("Exam required:PU CET\n");
                        printf("Guiding path:10th-->12th(Arts)-->B.A->M.A\n");
                        printf("Period of Study:2+4+2=8 years\n");
                    }
                    else if(strcasecmp(pat,"MSW")==0)
                    {
                        printf("Exam required:DSSW\n");
                        printf("Guiding path:10th-->12th(Arts)-->BSW-->MSW\n");
                        printf("Period of Study:2+3+2=7 years\n");
                    }
                    else if(strcasecmp(pat,"BCA")==0)
                    {
                        printf("Exam required:None\n");
                        printf("Guiding path:10th-->12th(Commerce)-->BCA\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"MCA")==0)
                    {
                        printf("Exam required:NIMCET\n");
                        printf("Guiding path:10th-->12th(Commerce)-->BCA-->MCA\n");
                        printf("Period of Study:2+3+3=8 years\n");
                    }
                    else if(strcasecmp(pat,"MBA")==0)
                    {
                        printf("Exam required:CAT\n");
                        printf("Guiding path:10th-->12th(Commerce)-->BBA->MBA\n");
                        printf("Period of Study:2+3+2=7 years\n");
                    }
                    else if(strcasecmp(pat,"M.Com")==0)
                    {
                        printf("Exam required:CUET\n");
                        printf("Guiding path:10th-->12th(Commerce)-->B.Com->M.Com\n");
                        printf("Period of Study:2+3+2=7 years\n");
                    }
                    else if(strcasecmp(pat,"B.Ed")==0)
                    {
                        printf("Exam required:B.Ed Entrance\n");
                        printf("Guiding path:10th-->12th(Of Any Stream)->Bachelor Degree of Stream->B.Ed\n");
                        printf("Period of Study:2+3+2=7 years\n");
                    }
                    else if(strcasecmp(pat,"M.Ed")==0)
                    {
                        printf("Exam required:DUET\n");
                        printf("Guiding path:10th-->12th(Of Any Stream)->Bachelor Degree of Stream->B.Ed->M.Ed\n");
                        printf("Period of Study:2+3+2+2=9 years\n");
                    }
                    else if(strcasecmp(pat,"C.S.")==0)
                    {
                        printf("Exam required:CSEET\n");
                        printf("Guiding path:10th-->12th(Commerce)->C.S.\n");
                        printf("Period of Study:2+3=5 years\n");
                    }
                    else if(strcasecmp(pat,"MDS")==0)
                    {
                        printf("Exam required:PG NEET\n");
                        printf("Guiding path:10th-->12th(Science)->BDS->MDS\n");
                        printf("Period of Study:2+4+3=9 years\n");
                    }
                    else if(strcasecmp(pat,"MD")==0)
                    {
                        printf("Exam required:PG NEET\n");
                        printf("Guiding path:10th-->12th(Science)->MBBS/BAMS->MD\n");
                        printf("Period of Study:2+5+3=10 years\n");
                    }
                    else if(strcasecmp(pat,"M.Tech")==0)
                    {
                        printf("Exam required:GATE\n");
                        printf("Guiding path:10th-->12th(Science)->B.E/B.Tech->M.Tech\n");
                        printf("Period of Study:2+4+2=8 years\n");
                    }
                    else if(strcasecmp(pat,"M.Pharma")==0)
                    {
                        printf("Exam required:GPAT\n");
                        printf("Guiding path:10th-->12th(Science)->B.Pharma->M.Pharma\n");
                        printf("Period of Study:2+3+2=7 years\n");
                    }
                    else if(strcasecmp(pat,"M.Sc")==0)
                    {
                        printf("Exam required:CUET\n");
                        printf("Guiding path:10th-->12th(Science)->B.Sc->M.Sc\n");
                        printf("Period of Study:2+4+2=8 years\n");
                    }
                    else if(strcasecmp(pat,"Ph.D")==0)
                    {
                        printf("Exam required:CSIR UGC NET/UGC NET/IIT JAM/NPAT\n");
                        printf("Guiding path:10th-->12th(Science)->UnderGraduation->PostGraduation->Ph.D\n");
                        printf("Period of Study:2+3/4/5+2+5=13-15 years\n");
                    }
                    reset();
                    break;


            case 3 : cyan();
                    //reading degree to get the appropriate job opportunities list
                    printf("Enter the degree and know it!!\n");
                    reset();
                    scanf("%s",pat);
                    purple();
                    printf("\nJob Opportunities:\n");
                    reset();
                    yellow();
                    if(strcasecmp(pat,"Diploma")==0)
                    {
                        printf("Junior Engineer, IT Assistant, PSU jobs, Clerk, Technician\n");
                    }
                    else if(strcasecmp(pat,"Government Service")==0)
                    {
                       printf("In SSC,Defence,States,Railways,PSU's, as Gram Dak Sevak\n");
                    }
                    else if(strcasecmp(pat,"Science")==0)
                    {
                       printf("Medical and allied sciences, Pure Science, Agriculture and allied streams,Biotechnology, Engineering,\n");
                    }
                    else if(strcasecmp(pat,"Commerce")==0)
                    {
                        printf("Management,CA,Marketing Management,CS,Finance Management,International Business Management,Operation Management\n");
                    }
                    else if(strcasecmp(pat,"Arts")==0)
                    {
                        printf("Arts/ Humanities,Law Courses,Photography,Animation & Multimedia,Mass Communications,Hotel Management & Catering,Fashion\n");
                    }
                    else if(strcasecmp(pat,"B.Arch")==0)
                    {
                      printf("Architectural Assistant,Architectural Historian/Journalist,Architecture Designer,Landscape Architect\n");
                    }
                    else if(strcasecmp(pat,"B.Sc")==0)
                    {
                        printf("Oil Industry,Agriculture Industry,Educational Institutes,Food Institutes,Space Research Institutes,Hospitals,Health Care Providers,Chemical Industry\n");
                    }
                    else if(strcasecmp(pat,"B.Pharma")==0)
                    {
                        printf("Analytical Chemist,Food and Drug Inspector,Hospital Drug Coordinator,Drug Therapist,Chemical Technician,Drug Technician\n");
                    }
                    else if(strcasecmp(pat,"B.E")==0)
                    {
                       printf("Public Service Undertakings,Management,Entrepreneurship,Civil Services\n");
                    }
                    else if(strcasecmp(pat,"BAMS")==0)
                    {
                        printf("Clinical practice,Academic,Research,Management and administration,Drug manufacturing\n");
                    }
                    else if(strcasecmp(pat,"MBBS")==0)
                    {
                       printf("Jobs in health services departments,Defence Services,Opportunities in Research and Academics,Health Administration/Hospital Management,Biomedical Engineering and Sciences ,Self-employment through private practice/ Public health\n");
                    }
                    else if(strcasecmp(pat,"BDS")==0)
                    {
                      printf("Lecturer ,Clinical practice,Research,Dental cosmetology,Forensic dentistry,Medical transcription\n");
                    }
                    else if(strcasecmp(pat,"B.Com")==0)
                    {
                       printf("Accountant, Business Executive, Financial Analyst, Tax Consultant, Accounts Manager, Finance Manager, Financial Analyst\n");
                    }
                    else if(strcasecmp(pat,"BBA")==0)
                    {
                        printf("Retail Manager,Branch Manager,Human Resource Manager,Hotel General manager,Event Manager,Airport Manager\n");
                    }
                    else if(strcasecmp(pat,"CA")==0)
                    {
                       printf("Internal Auditor, Banking and Insurance Sector,Finance Management,Business\n");
                    }
                    else if(strcasecmp(pat,"BSW")==0)
                    {printf("Field Worker Volunteer,Social Worker,Program Coordinator,Teacher,Influencer,Community Organizer\n");
                    }
                    else if(strcasecmp(pat,"B.A.")==0)
                    {
                        printf( "Executive Assistant, Operations Manager, HR Manager, Graphic Designer, Marketing Manager, Business Development Manager\n");
                    }
                    else if(strcasecmp(pat,"LLB")==0)
                    {
                      printf("Advocate,Legal Advisor,Journalist,Teaching,Legal Outsourcing,Legal Analyst,Legal Researcher\n");
                    }
                    else if(strcasecmp(pat,"LLM")==0)
                    {
                        printf("Consulting Bodies,Law Firms,Corporate,Finance,Courthouses,Media and Publishing Houses,NGO,UN and UNICEF International Organizations,Real Estate\n");
                    }
                    else if(strcasecmp(pat,"M.A")==0)
                    {
                       printf("Social worker,Teacher,Journalist,author,politician,Content writer,Administrative officer,Research,Economist,Historian,Psychologist\n");
                    }
                    else if(strcasecmp(pat,"MSW")==0)
                    {
                        printf("Social Worker,Public Welfare Managers,Consultants,Project Coordinator,Professor,Program Coordinator,Training Coordinator\n");
                    }
                    else if(strcasecmp(pat,"BCA")==0)
                    {
                       printf("Data Scientist,Web Developer,Digital Marketer,Software Developer Trainee,Banking Sector,E-commerce Executive,Educator\n");
                    }
                    else if(strcasecmp(pat,"MCA")==0)
                    {
                       printf("Computer System Analyst,Database Administrator,Hardware Engineer,Web Designer or Web Developer,Software Architect and Software Consultant\n");
                    }
                    else if(strcasecmp(pat,"MBA")==0)
                    {
                       printf("Human Resources Manager,Operations Manager,Product Manager,Finance Manager,Marketing Manager,Project Manager\n");
                    }
                    else if(strcasecmp(pat,"M.Com")==0)
                    {
                      printf("Digital marketing,Investment Banker,Tax Consultant,Certified Management Accountant,Financial Analyst\n");
                    }
                    else if(strcasecmp(pat,"B.Ed")==0)
                    {
                        printf("Teacher,Educational Counsellor,Content Write,Researcher,Online Tutor\n");
                    }
                    else if(strcasecmp(pat,"M.Ed")==0)
                    {
                        printf("Teachers, Counsellors, Administrators, Headmasters\n");
                    }
                    else if(strcasecmp(pat,"C.S.")==0)
                    {
                      printf("Legal Counsellor,Human Resource Manager,Legal Manager,Executive Assistant,In-house legal expert\n");
                    }
                    else if(strcasecmp(pat,"MDS")==0)
                    {
                      printf("Lecturer ,Clinical practice,Research,Dental cosmetology,Forensic dentistry,Medical transcription\n");
                    }
                    else if(strcasecmp(pat,"MD")==0)
                    {
                      printf("Internal Medicine Doctor,Internal Medicine Physician,General Physician,Biomedical Companies,Surgical specialisation\n");
                    }
                    else if(strcasecmp(pat,"M.Tech")==0)
                    {
                      printf("Service Engineer,Network Planning engineer,R&D Software engineer,Software Analyst,Technical Directors\n");
                    }
                    else if(strcasecmp(pat,"M.Pharma")==0)
                    {
                        printf("Academic Researcher,Analytical Chemist,Biomedical Scientist,Clinical Research Associate,Medicinal Chemist,Pharmacologist\n");
                    }
                    else if(strcasecmp(pat,"M.Sc")==0)
                    {
                       printf("Professor,Lab Technician, Chemical Analyst,Food and Drug Inspector,Biochemist,Statistician,Mathematician,Research Scientist\n");
                    }
                    else if(strcasecmp(pat,"Ph.D")==0)
                    {
                        printf("Completing Ph.D after a post-grad degree in any field opens many doors to various fields\n");
                        printf("Academics,Government Jobs,Entrepreneur, Consultancy,Digital Media Company,Research Associate\n");
                    }
                    reset();
                    break;

            case 4: // Create an array to store the colleges
                    // Read the colleges from the file
                    read_colleges(colleges, &num_colleges);
                    green();
                    printf("NOTE: The state_names are not case-sensitive, so enter as given below as per choice\n");
                    printf("Valid states: Karnataka, Maharashtra, Uttar_Pradesh, West_Bengal, Andhra_Pradesh, Gujarat\n");
                    reset();
                    // Get the colleges for a given state
                    char results[1000][500];
                    char state_name[50];
                    cyan();
                    printf("Enter the State:\n");
                    scanf("%s",state_name);
                    reset();
                    get_colleges_by_state(colleges, num_colleges, state_name, results);

                    // Print the results
                    red();
                    for (int i = 0; results[i][0] != '\0'; i++)
                    {
                        printf("%s\n", results[i]);
                    }
                    reset();
                    break;

            case 5:{int key;
                    blue();
                    printf("1. Karnataka\n");
                    printf("2. Andhra Predesh\n");
                    printf("3. Gujarat\n");
                    printf("4. Maharashtra\n");
                    printf("5. Uttar Pradesh\n");
                    printf("6. West Bengal\n");
                    reset();
                    red();
                    printf("Enter number:");
                    scanf("%d",&key);
                    reset();
                    switch(key)
                    {

                        case 1: cyan();
                                //gives list of cities and their min distance in the places where we have considered colleges to be
                                fp3 = fopen("karnataka1.txt","r");
                                int g1[10][10];
                                for(int i=0;i<5;i++)
                                {
                                    for(int j=0;j<5;j++)
                                    {
                                        fscanf(fp3,"%d",&g1[i][j]);
                                    }
                                }
                                printf("The nodes indicate the cities of Karnataka as shown:\n\n");
                                printf("0->Bangalore\t1->Dharwad\t2->Hubli\t3->Bagalkot\t4->Mandya\n");
                                dijkstra(g1,5,0);
                                fclose(fp3);
                                printf("\n");
                                reset();
                                break;
                        case 2: orange();
                                //gives list of cities and their min distance in the places where we have considered colleges to be
                                fp4 = fopen("andhrapradesh6.txt","r");
                                int g2[10][10];
                                for(int i=0;i<5;i++)
                                {
                                    for(int j=0;j<5;j++)
                                    {
                                        fscanf(fp4,"%d",&g2[i][j]);
                                    }
                                }
                                printf("The nodes indicate the cities of Andhra_Pradesh as shown:\n\n");
                                printf("0->Vishakapatnam\t1->Guntur\t2->Vijaywada\t3->Kurnool\t4->Nellore\n");
                                dijkstra(g2,5,0);
                                fclose(fp4);
                                printf("\n");
                                reset();
                                break;
                        case 3: red();
                                //gives list of cities and their min distance in the places where we have considered colleges to be
                                fp5 = fopen("Gujarat2.txt","r");
                                int g3[10][10];
                                for(int i=0;i<5;i++)
                                {
                                    for(int j=0;j<5;j++)
                                    {
                                        fscanf(fp5,"%d",&g3[i][j]);
                                    }
                                }
                                printf("The nodes indicate the cities of Gujarat as shown:\n\n");
                                printf("0->Ahmedabad\t1->GandhiNagar\t2->Vadodara\t3->Surat\t4->Rajkot\n");
                                dijkstra(g3,5,0);
                                fclose(fp5);
                                printf("\n");
                                reset();
                                break;
                        case 4: lightpurple();
                                //gives list of cities and their min distance in the places where we have considered colleges to be
                                fp6 = fopen("maharashtra5.txt","r");
                                int g4[10][10];
                                for(int i=0;i<5;i++)
                                {
                                    for(int j=0;j<5;j++)
                                    {
                                        fscanf(fp6,"%d",&g4[i][j]);
                                    }
                                }
                                printf("The nodes indicate the cities of Maharashtra as shown:\n\n");
                                printf("0->Mumbai\t1->Pune\t 2->Kolhapur\t3->Nagpur\t4->Aurangabad\n");
                                dijkstra(g4,5,0);
                                fclose(fp6);
                                printf("\n");
                                reset();
                                break;
                        case 5: cyan();
                                //gives list of cities and their min distance in the places where we have considered colleges to be
                                fp7= fopen("uttarpradesh3.txt","r");
                                int g5[10][10];
                                for(int i=0;i<6;i++)
                                {
                                    for(int j=0;j<6;j++)
                                    {
                                        fscanf(fp7,"%d",&g5[i][j]);
                                    }
                                }
                                printf("The nodes indicate the cities of Uttar_Pradesh as shown:\n\n");
                                printf("0->Ayodhya\t1->Varanasi\t2->Lucknow\t3->Vrindavan\t4->Mathura\t5->Chitrakoot\n");
                                dijkstra(g5,6,0);
                                fclose(fp7);
                                printf("\n");
                                reset();
                                break;
                        case 6: green();
                                //gives list of cities and their min distance in the places where we have considered colleges to be
                                fp8 = fopen("westbengal4.txt","r");
                                int g6[10][10];
                                for(int i=0;i<5;i++)
                                {
                                    for(int j=0;j<5;j++)
                                    {
                                        fscanf(fp8,"%d",&g6[i][j]);
                                    }
                                }
                                printf("The nodes indicate the cities of West_Bengal as shown:\n\n");
                                printf("0->Kolkata\t1->Howrah\t2->Durgapur\t3->Hoogly\t4->Siliguri\n");
                                dijkstra(g6,5,0);
                                fclose(fp8);
                                printf("\n");
                                reset();
                                break;



                    }
                    }
                    break;
            default:exit(0);
        }
    }
}
