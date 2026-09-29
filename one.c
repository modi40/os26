#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
int id;
int at;
int bt1;
int bt2;
int total_bt;
int rem_bt;
int pr;
int ct;
int tat;
int wt;
} Process;
int main() {
int n, i;
srand(time(NULL));
printf("Enter number of processes: ");
if(scanf("%d", &n) != 1) return 0;
Process p[20];
for(i = 0; i < n; i++) {
p[i].id = i + 1;
printf("Process P%d - Arrival Time: ", i + 1);
scanf("%d", &p[i].at);
printf("Process P%d - First CPU Burst: ", i + 1);
scanf("%d", &p[i].bt1);
printf("Process P%d - Priority (lower number = higher priority): ", i + 1);
scanf("%d", &p[i].pr);
p[i].bt2 = (rand() % 10) + 1;
p[i].total_bt = p[i].bt1 + p[i].bt2;
p[i].rem_bt = p[i].total_bt;
printf("Process P%d - Next CPU Burst (random): %d (Total Burst: %d)\n", i + 1, p[i].bt2, p[i].total_bt);
}
int current_time = 0, completed = 0;
int gantt_p[500], gantt_t[500], g_cnt = 0;
gantt_t[0] = 0;
while(completed < n) {
int idx = -1, highest_pr = 1e9;
for(i = 0; i < n; i++) {
if(p[i].at <= current_time && p[i].rem_bt > 0) {
if(p[i].pr < highest_pr) {
highest_pr = p[i].pr;
idx = i;
}
}
}
if(idx == -1) {
current_time++;
continue;
}
p[idx].rem_bt--;
current_time++;
if(g_cnt == 0 || gantt_p[g_cnt - 1] != p[idx].id) {
gantt_p[g_cnt] = p[idx].id;
gantt_t[g_cnt] = current_time - 1;
g_cnt++;
}
gantt_t[g_cnt] = current_time;
if(p[idx].rem_bt == 0) {
p[idx].ct = current_time;
p[idx].tat = p[idx].ct - p[idx].at;
p[idx].wt = p[idx].tat - p[idx].total_bt;
completed++;
}
}
printf("\nGantt Chart:\n|");
for(i = 0; i < g_cnt; i++) printf(" P%d |", gantt_p[i]);
printf("\n");
for(i = 0; i <= g_cnt; i++) printf("%d    ", gantt_t[i]);
printf("\n\nProcess\tAT\tPriority\tTotal BT\tCT\tTAT\tWT\n");
float total_tat = 0, total_wt = 0;
for(i = 0; i < n; i++) {
total_tat += p[i].tat;
total_wt += p[i].wt;
printf("P%d\t%d\t%d\t\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].pr, p[i].total_bt, p[i].ct, p[i].tat, p[i].wt);
}
printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
printf("Average Waiting Time = %.2f\n", total_wt / n);
return 0;
}
