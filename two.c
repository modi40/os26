#include <stdio.h>
#include <stdlib.h>
int main() {
int ref[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
int n_pages = sizeof(ref) / sizeof(ref[0]);
int n_frames, i, j, k, faults = 0, fifo_idx = 0;
printf("Reference String: ");
for(i = 0; i < n_pages; i++) printf("%d ", ref[i]);
printf("\nEnter number of frames: ");
if(scanf("%d", &n_frames) != 1) return 0;
int frames[20];
for(i = 0; i < n_frames; i++) frames[i] = -1;
printf("\nPage\tFrames\t\t\tPage Fault\n");
for(i = 0; i < n_pages; i++) {
int page = ref[i];
int found = 0;
for(j = 0; j < n_frames; j++) {
if(frames[j] == page) {
found = 1;
break;
}
}
char status[4] = "No";
if(!found) {
frames[fifo_idx] = page;
fifo_idx = (fifo_idx + 1) % n_frames;
faults++;
status[0] = 'Y'; status[1] = 'e'; status[2] = 's'; status[3] = '\0';
}
printf("%d\t", page);
for(k = 0; k < n_frames; k++) {
if(frames[k] != -1) printf("%d ", frames[k]);
else printf("- ");
}
printf("\t\t%s\n", status);
}
printf("\nTotal Page Faults: %d\n", faults);
return 0;
}
