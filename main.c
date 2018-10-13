/*
 *
 * Compilation Instruction:
 * gcc commandline_parser.c -o commandline_parser
 * ./commandline_parser
 *
 */

#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <wait.h>
#include <inttypes.h>
#include "Queue.h"
#include <pthread.h>

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condA = PTHREAD_COND_INITIALIZER;
pthread_cond_t condB = PTHREAD_COND_INITIALIZER;
pthread_cond_t emptyQ = PTHREAD_COND_INITIALIZER;
pthread_cond_t emptyA = PTHREAD_COND_INITIALIZER;
pthread_cond_t emptyB = PTHREAD_COND_INITIALIZER;
pthread_cond_t schedA = PTHREAD_COND_INITIALIZER;
pthread_cond_t schedB = PTHREAD_COND_INITIALIZER;
pthread_cond_t quitC = PTHREAD_COND_INITIALIZER;
pthread_t tid;

/* Error Code */
#define EINVAL       1
#define E2BIG        2

#define MAXMENUARGS  4
#define MAXCMDLINE   64

struct Queue_Node* job_queue;
void menu_execute(char *line, int isargs);
int cmd_run(int nargs, char **args);

int cmd_list(int nargs, char **args);
int cmd_quit(int nargs, char **args);

void schedulerMod();

void schedulerMod2();
void dispactherMod();
void showmenu(const char *name, const char *x[]);
int cmd_helpmenu(int n, char **a);
int cmd_dispatch(char *cmd);
void create_modules(void *module);

char sched[15] = "FCFS";
int reschedule = 0;
int quitBool = 0;


/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args) {
    job_t* job = malloc(sizeof(job_t));
    if (nargs != 4) {
        printf("Usage: run <job> <time> <priority>\n");
        return EINVAL;
    }

    int burst = atoi(args[2]);
    int priority = atoi(args[3]);
    job->run_time = burst;
    job->priority = priority;
    strcpy(job->name, args[1]);

    if(job_queue->count < 1) {
        job->sub_time = currentTimeMillis();
        job_queue->job = job;
        job_queue->count++;
    } else {
        job_queue->add(job_queue, job);
    }

    if (job_queue->count == 1) {
        pthread_cond_signal((pthread_cond_t *) queue_mutex);
        pthread_cond_signal(&condA);
        pthread_cond_signal(&condB);
    }
    pid_t child = fork();
    char *execv_args[] = {"C:\\Users\\jazart\\CLionProjects\\CSUBatch\\job.exe", NULL };
    if(child == 0) {
        if(execv("C:\\Users\\jazart\\CLionProjects\\CSUBatch\\job.exe",
                execv_args) < 0) {
            printf("\nError\n");
            exit(0);
        }
    }

    if(child != 0) {
        waitpid(-1, NULL, 0);
    }
    printf("\nuse execv to run the job in csubatch.\n");
    return 1;
}


int cmd_sched(int nargs, char **args) {
    strcpy(sched, args[0]);
    printf("%s\n", sched);
    printf("%d\n", job_queue->count);
//    create_modules(schedulerMod);
    return 1;
}

/*
 * Display menu information
 */
void showmenu(const char *name, const char *x[]) {
    int ct, half, i;

    printf("\n");
    printf("%s\n", name);

    for (i = ct = 0; x[i]; i++) {
        ct++;
    }
    half = (ct + 1) / 2;

    for (i = 0; i < half; i++) {
        printf("    %-36s", x[i]);
        if (i + half < ct) {
            printf("%s", x[i + half]);
        }
        printf("\n");
    }

    printf("\n");
}


static const char *helpmenu[] = {
        "[run] <job> <time> <priority>       ",
        "[quit] Exit csubatch                 ",
        "[help] Print help menu              ",
        /* Please add more menu options below */
        "[list] List all jobs               ",
        NULL
};

int cmd_helpmenu(int n, char **a) {
    (void) n;
    (void) a;

    showmenu("csubatch help menu", helpmenu);
    return 0;
}

/*
 *  Command table.
 */
static struct {
    const char *name;
    int (*func)(int nargs, char **args);
} cmdtable[] = {
        /* commands: single command must end with \n */
        {"?\n",    cmd_helpmenu},
        {"h\n",    cmd_helpmenu},
        {"help\n", cmd_helpmenu},
        {"r",      cmd_run},
        {"run",    cmd_run},
        {"q\n",    cmd_quit},
        {"quit\n", cmd_quit},
        {"list\n", cmd_list},
        {"FCFS\n", cmd_sched},
        {"SJF\n", cmd_sched},
        {"Priority\n", cmd_sched},
        /* Please add more operations below. */
        {NULL, NULL}
};

/*
 * List out the jobs
 */
int cmd_list(int nargs, char **args) {
    int i;
    printf("The Current Scheduling policy is:%s\n", sched);
    printf("The following are the list of jobs:\n");
    printf("Sub Time  \tJob Name\tBurst Time\tPriority\n");
    queue_t* jobs = job_queue;
    int count = job_queue->count;
    for (i = 0; i < count; i++) {
        printf("%" PRId64 "\t%s\t\t%ld\t\t%d\n", jobs->job->sub_time, jobs->job->name, jobs->job->run_time, jobs->job->priority);
        jobs = jobs->next;
    }
    return (0);
}


/*
 * after 'quit', display performance
 */
void dis_perfo() {
    int result_count = job_queue->count;
    queue_t *jobs = job_queue->next;
    double turnaround = 0;
    double burstTime = 0;
    if(result_count == 0)
    {
        printf("Program end\n");
        return ;
    }
    for(int i = 0;i < result_count; i++)
    {
        turnaround = currentTimeMillis() - jobs->job->sub_time;
        burstTime += jobs->job->run_time;

    }
    printf("Total number jobs submitted: %d\n", result_count);
    printf("Average BurstTime:\t\t %.2f\n",burstTime/result_count);
    printf("Average waiting time:\t\t %.2f\n",(turnaround-burstTime)/result_count);
    printf("Average Throughput:\t\t %.3f\n",(1/(turnaround/result_count)));
}

/*
 * The quit command.
 */
int cmd_quit(int nargs, char **args) {
    dis_perfo();
    printf("Please display performance information before exiting csubatch!\n");
    exit(0);
}

/*
 * Process a single command.
 */
int cmd_dispatch(char *cmd) {
    time_t beforesecs, aftersecs, secs;
    u_int32_t beforensecs, afternsecs, nsecs;
    char *args[MAXMENUARGS];
    int nargs = 0;
    char *word;
    char *context;
    int i, result;

    for (word = strtok_r(cmd, " ", &context);
         word != NULL;
         word = strtok_r(NULL, " ", &context)) {

        if (nargs >= MAXMENUARGS) {
            printf("Command line has too many words\n");
            return E2BIG;
        }
        args[nargs++] = word;
    }

    if (nargs == 0) {
        return 0;
    }

    for (i = 0; cmdtable[i].name; i++) {
        if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
            assert(cmdtable[i].func != NULL);

            /* Call function through the cmd_table */
            result = cmdtable[i].func(nargs, args);
            return result;
        }
    }

    printf("%s: Command not found\n", args[0]);
    return EINVAL;
}

void create_modules(void *module) {
    pthread_create(&tid, NULL, module, NULL);
}

void schedulerMod() {

    //pthread_mutex_lock(queue_mutex);
    while (1) {while (job_queue->count == 0) {
        pthread_cond_wait(&emptyQ, &queue_mutex);
    }
    if (strcmp(sched, "FCFS\n") == 0) {
        sort(job_queue, 2);
    }

    if (strcmp(sched, "Priority\n") == 0) {
        sort(job_queue, 1);
    }

    if (strcmp(sched, "SJF\n") == 0) {
        printf("%s", sched);
        sort(job_queue, 3);
    }

    pthread_cond_signal(&condB);
    pthread_mutex_lock(&queue_mutex);
    pthread_cond_wait(&condA, &queue_mutex);
        pthread_cond_signal(&condB);
        pthread_mutex_lock(&queue_mutex);
        pthread_cond_wait(&condA, &queue_mutex);


    }
}

void dispatcherMod() {
    while (1) {
        if (quitBool == 1) {
            pthread_exit(NULL);
        }

        if (job_queue->count == 0) {
            pthread_mutex_lock(&queue_mutex);
            while (pthread_cond_wait(&condB, &queue_mutex) != 0);
            pthread_mutex_unlock(&queue_mutex);
        }

        if (reschedule == 1) {
            pthread_mutex_lock(&queue_mutex);
            while (pthread_cond_wait(&condB, &queue_mutex) != 0);
        }

        execv(remove_head(job_queue)->job->name, NULL);
        sleep(15);

    }
}

void schedulerMod2() {

    //pthread_mutex_lock(queue_mutex);
    while (1) {

        if (quitBool == 1) {
            pthread_exit(NULL);
        }

        if (job_queue->count == 0) {
            pthread_mutex_lock(&queue_mutex);
            while (pthread_cond_wait(&condA, &queue_mutex) != 0) {
                if (quitBool == 1) {
                    pthread_exit(NULL);
                }
            }
            pthread_mutex_unlock(&queue_mutex);
        }
        if (reschedule == 0) {
            pthread_mutex_lock(&queue_mutex);
            while (pthread_cond_wait(&condA, &queue_mutex) != 0) {
                if (quitBool == 1) {
                    pthread_exit(NULL);
                }
            }
        }

        pthread_mutex_lock(&queue_mutex);

        if (strcmp(sched, "FCFS\n") == 0) {
            sort(job_queue, 2);
            printf("Sorted");
        }

        if (strcmp(sched, "Priority\n") == 0) {
            sort(job_queue, 1);
            printf("Sorted");
        }

        if (strcmp(sched, "SJF\n") == 0) {
            printf("%s", sched);
            sort(job_queue, 3);
            printf("Sorted");
        }
        reschedule = 0;

            execv(remove_head(job_queue)->job->name, 1);
    }
}
        //pthread_cond_signal(&condB);



    }
}


/*
 * Command line main loop.
 */
int main() {
    char *buffer;
    size_t bufsize = 64;
    job_queue = init_queue(job_queue);
    int bool = 1;

    for(int i = 0; i < 5; ++i) {
        job_t* job = malloc(sizeof(job_t));
        job->run_time = i * i;
        job->priority = i + 1;
        strcpy(job->name, "job");
        char num [3];
        strcat(job->name, num);
        if(i == 1) {
            job_queue->job = job;
            continue;
        }
        job_queue->add(job_queue, job);
    }
    job_queue = sort(job_queue, 1);
    for (int j = 0; j < 5; ++j) {
        queue_t* cpy = job_queue;
        printf("%s   %d\n", job_queue->job->name, job_queue->job->priority);
        job_queue = job_queue->next;
    }


//
//    buffer = (char *) malloc(bufsize * sizeof(char));
//    if (buffer == NULL) {
//        perror("Unable to malloc buffer");
//        exit(1);
//    }
//
//    //create_modules(schedulerMod);
//    //create_modules(dispatcherMod);
//    while (1) {
//        printf("> [? for menu]: ");
//        getline(&buffer, &bufsize, stdin);
//        cmd_dispatch(buffer);
//    }
    create_modules(schedulerMod2);
    sleep(8);
    create_modules(dispatcherMod);
    while (bool == 1) {
        printf("> [? for menu]: ");
        getline(&buffer, &bufsize, stdin);
        if (strcmp(buffer, "quit") == 0) {
            bool = 0;
        }
        cmd_dispatch(buffer);
    }
    return 0;
}


#pragma clang diagnostic pop