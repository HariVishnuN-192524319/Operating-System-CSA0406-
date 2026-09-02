/* ============================================================================
 * os_simulators.c
 * CSA04 - Operating Systems | Team 2 - Ride-Hailing Dispatch System
 *
 * Combined simulator for all three parts of the report:
 *   Part I   - CPU Scheduling      : FCFS, SJF, Priority, Round Robin (q=3)
 *   Part II  - Page Replacement    : FIFO, LRU, Optimal (4 frames)
 *   Part III - Disk Scheduling     : FCFS, SSTF, SCAN, C-SCAN
 *
 * This file merges cpu_scheduling.c, page_replacement.c and disk_scheduling.c
 * into a single translation unit (functions/globals prefixed cpu_/page_/disk_
 * to avoid name collisions) and runs all three in sequence from one main().
 *
 * Compile : gcc -Wall -O2 -o os_simulators os_simulators.c
 * Run     : ./os_simulators
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==========================================================================
 * PART I - CPU SCHEDULING
 * ======================================================================= */

#define N 5
#define QUANTUM 3

typedef struct {
    char name[4];
    int at;         /* arrival time            */
    int bt;         /* burst time               */
    int pri;        /* priority (1 = highest)   */
    int rem;        /* remaining burst (for RR) */
    int ct;         /* completion time          */
    int tat;        /* turnaround time          */
    int wt;         /* waiting time             */
    int started;    /* has the process begun?   */
} Process;

typedef struct {
    char name[4];
    int start;
    int end;
} GanttEntry;

static Process base[N] = {
    {"P1", 0, 6, 3, 6, 0, 0, 0, 0},
    {"P2", 2, 4, 1, 4, 0, 0, 0, 0},
    {"P3", 3, 2, 4, 2, 0, 0, 0, 0},
    {"P4", 5, 7, 5, 7, 0, 0, 0, 0},
    {"P5", 6, 3, 2, 3, 0, 0, 0, 0},
};

/* ---------------------------------------------------------------------- */
static void cpu_print_gantt(GanttEntry *g, int n) {
    printf("Gantt chart: ");
    for (int i = 0; i < n; i++)
        printf("| %s(%d-%d) ", g[i].name, g[i].start, g[i].end);
    printf("|\n");
}

static void cpu_print_table_and_summary(const char *title, Process p[N]) {
    double tat_sum = 0, wt_sum = 0;
    printf("\n--- %s ---\n", title);
    printf("%-6s%-6s%-6s%-6s%-6s%-6s\n", "Proc", "AT", "BT", "CT", "TAT", "WT");
    for (int i = 0; i < N; i++) {
        printf("%-6s%-6d%-6d%-6d%-6d%-6d\n",
               p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        tat_sum += p[i].tat;
        wt_sum  += p[i].wt;
    }
    printf("Average Turnaround Time = %.2f\n", tat_sum / N);
    printf("Average Waiting Time    = %.2f\n", wt_sum / N);
}

/* ---------------------------------------------------------------------- */
/* FCFS: processes serviced strictly in arrival order                     */
static void cpu_fcfs(void) {
    Process p[N];
    memcpy(p, base, sizeof(base));
    /* already sorted by arrival time in 'base' */
    int t = 0;
    GanttEntry g[N];
    for (int i = 0; i < N; i++) {
        int start = (t > p[i].at) ? t : p[i].at;
        int end = start + p[i].bt;
        strcpy(g[i].name, p[i].name);
        g[i].start = start; g[i].end = end;
        p[i].ct = end;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        t = end;
    }
    cpu_print_gantt(g, N);
    cpu_print_table_and_summary("FCFS", p);
}

/* ---------------------------------------------------------------------- */
/* SJF (non-preemptive): shortest burst time among arrived, unfinished    */
static void cpu_sjf(void) {
    Process p[N];
    memcpy(p, base, sizeof(base));
    int done[N] = {0};
    int t = 0, completed = 0;
    GanttEntry g[N];
    int gi = 0;

    while (completed < N) {
        int idx = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && p[i].at <= t) {
                if (idx == -1 || p[i].bt < p[idx].bt ||
                    (p[i].bt == p[idx].bt && p[i].at < p[idx].at))
                    idx = i;
            }
        }
        if (idx == -1) {           /* CPU idle: jump to next arrival */
            int next_at = 1 << 30;
            for (int i = 0; i < N; i++)
                if (!done[i] && p[i].at < next_at) next_at = p[i].at;
            t = next_at;
            continue;
        }
        int start = t;
        int end = t + p[idx].bt;
        strcpy(g[gi].name, p[idx].name);
        g[gi].start = start; g[gi].end = end; gi++;
        p[idx].ct = end;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        t = end;
        done[idx] = 1;
        completed++;
    }
    cpu_print_gantt(g, gi);
    cpu_print_table_and_summary("SJF (Non-Preemptive)", p);
}

/* ---------------------------------------------------------------------- */
/* Priority (non-preemptive): lower number = higher priority              */
static void cpu_priority_sched(void) {
    Process p[N];
    memcpy(p, base, sizeof(base));
    int done[N] = {0};
    int t = 0, completed = 0;
    GanttEntry g[N];
    int gi = 0;

    while (completed < N) {
        int idx = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && p[i].at <= t) {
                if (idx == -1 || p[i].pri < p[idx].pri ||
                    (p[i].pri == p[idx].pri && p[i].at < p[idx].at))
                    idx = i;
            }
        }
        if (idx == -1) {
            int next_at = 1 << 30;
            for (int i = 0; i < N; i++)
                if (!done[i] && p[i].at < next_at) next_at = p[i].at;
            t = next_at;
            continue;
        }
        int start = t;
        int end = t + p[idx].bt;
        strcpy(g[gi].name, p[idx].name);
        g[gi].start = start; g[gi].end = end; gi++;
        p[idx].ct = end;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        t = end;
        done[idx] = 1;
        completed++;
    }
    cpu_print_gantt(g, gi);
    cpu_print_table_and_summary("Priority Scheduling (Non-Preemptive)", p);
}

/* ---------------------------------------------------------------------- */
/* Round Robin, quantum = 3. Newly arrived processes are enqueued before  */
/* the pre-empted process is re-queued at each quantum boundary.          */
static void cpu_round_robin(void) {
    Process p[N];
    memcpy(p, base, sizeof(base));

    int queue[100], front = 0, rear = 0;   /* simple circular-ish array queue */
    int arrived[N] = {0};
    int t = 0, remaining_procs = N;
    GanttEntry g[100];
    int gi = 0;

    /* bring in processes that arrive at t=0 (sorted by arrival, 'base' already is) */
    for (int i = 0; i < N; i++) {
        if (p[i].at <= t && !arrived[i]) {
            queue[rear++] = i;
            arrived[i] = 1;
        }
    }

    while (remaining_procs > 0) {
        int idx = queue[front++];
        int run = (p[idx].rem < QUANTUM) ? p[idx].rem : QUANTUM;
        int start = t;
        t += run;
        p[idx].rem -= run;

        /* Merge into the previous Gantt block if it's the same process
           running back-to-back (happens when it is the only process left
           in the ready queue for consecutive quanta) so the chart reads
           the same way a hand-drawn Gantt chart would. */
        if (gi > 0 && strcmp(g[gi - 1].name, p[idx].name) == 0 && g[gi - 1].end == start) {
            g[gi - 1].end = t;
        } else {
            strcpy(g[gi].name, p[idx].name);
            g[gi].start = start; g[gi].end = t; gi++;
        }

        /* enqueue any process that arrived during [start, t] */
        for (int i = 0; i < N; i++) {
            if (!arrived[i] && p[i].at <= t) {
                queue[rear++] = i;
                arrived[i] = 1;
            }
        }

        if (p[idx].rem > 0) {
            queue[rear++] = idx;               /* re-queue pre-empted process */
        } else {
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            remaining_procs--;
        }
    }
    cpu_print_gantt(g, gi);
    cpu_print_table_and_summary("Round Robin (Quantum = 3)", p);
}

/* ---------------------------------------------------------------------- */
static void run_cpu_scheduling(void) {
    printf("============================================================\n");
    printf(" CPU Scheduling Simulator - Ride-Hailing Dispatch System\n");
    printf(" Processes P1-P5 | RR quantum = %d\n", QUANTUM);
    printf("============================================================\n");

    cpu_fcfs();
    cpu_sjf();
    cpu_priority_sched();
    cpu_round_robin();

    printf("\n============================================================\n");
    printf(" Summary (Avg WT / Avg TAT):\n");
    printf("   FCFS      : WT=6.20  TAT=10.60\n");
    printf("   SJF       : WT=4.80  TAT=9.20\n");
    printf("   Priority  : WT=5.60  TAT=10.00\n");
    printf("   RR (q=3)  : WT=7.60  TAT=12.00\n");
    printf("============================================================\n");
}

/* ==========================================================================
 * PART II - PAGE REPLACEMENT
 * ======================================================================= */

#define FRAMES 4
#define REFS 12

static int pr_ref[REFS] = {0, 1, 2, 3, 1, 4, 1, 5, 2, 6, 5, 1};

static void page_print_frames(int frames[], int count) {
    printf("[ ");
    for (int i = 0; i < count; i++) printf("%d ", frames[i]);
    for (int i = count; i < FRAMES; i++) printf(". ");
    printf("]");
}

/* ---------------------------------------------------------------------- */
static int page_fifo(void) {
    int frames[FRAMES];
    int count = 0;      /* how many frames currently occupied */
    int oldest = 0;      /* index (in frames[]) to evict next  */
    int faults = 0;

    printf("\n--- FIFO ---\n");
    for (int i = 0; i < REFS; i++) {
        int page = pr_ref[i];
        int hit = 0;
        for (int j = 0; j < count; j++)
            if (frames[j] == page) { hit = 1; break; }

        if (hit) {
            printf("ref=%d  ", page); page_print_frames(frames, count); printf("  HIT\n");
            continue;
        }
        faults++;
        if (count < FRAMES) {
            frames[count++] = page;
        } else {
            frames[oldest] = page;
            oldest = (oldest + 1) % FRAMES;
        }
        printf("ref=%d  ", page); page_print_frames(frames, count); printf("  FAULT\n");
    }
    printf("Total page faults (FIFO) = %d / %d\n", faults, REFS);
    return faults;
}

/* ---------------------------------------------------------------------- */
static int page_lru(void) {
    int frames[FRAMES];
    int last_used[FRAMES];   /* "time" each frame's page was last referenced */
    int count = 0;
    int faults = 0;

    printf("\n--- LRU ---\n");
    for (int i = 0; i < REFS; i++) {
        int page = pr_ref[i];
        int hit_idx = -1;
        for (int j = 0; j < count; j++)
            if (frames[j] == page) { hit_idx = j; break; }

        if (hit_idx != -1) {
            last_used[hit_idx] = i;    /* refresh recency */
            printf("ref=%d  ", page); page_print_frames(frames, count); printf("  HIT\n");
            continue;
        }

        faults++;
        if (count < FRAMES) {
            frames[count] = page;
            last_used[count] = i;
            count++;
        } else {
            /* find the frame whose last-used time is smallest (least recently used) */
            int victim = 0;
            for (int j = 1; j < FRAMES; j++)
                if (last_used[j] < last_used[victim]) victim = j;
            frames[victim] = page;
            last_used[victim] = i;
        }
        printf("ref=%d  ", page); page_print_frames(frames, count); printf("  FAULT\n");
    }
    printf("Total page faults (LRU) = %d / %d\n", faults, REFS);
    return faults;
}

/* ---------------------------------------------------------------------- */
static int page_optimal(void) {
    int frames[FRAMES];
    int count = 0;
    int faults = 0;

    printf("\n--- OPTIMAL ---\n");
    for (int i = 0; i < REFS; i++) {
        int page = pr_ref[i];
        int hit = 0;
        for (int j = 0; j < count; j++)
            if (frames[j] == page) { hit = 1; break; }

        if (hit) {
            printf("ref=%d  ", page); page_print_frames(frames, count); printf("  HIT\n");
            continue;
        }

        faults++;
        if (count < FRAMES) {
            frames[count++] = page;
        } else {
            /* pick the frame whose page is used farthest in the future
               (or never again) */
            int victim = 0, farthest = -1;
            for (int j = 0; j < FRAMES; j++) {
                int next_use = REFS;  /* "never again" sentinel */
                for (int k = i + 1; k < REFS; k++) {
                    if (pr_ref[k] == frames[j]) { next_use = k; break; }
                }
                if (next_use > farthest) { farthest = next_use; victim = j; }
            }
            frames[victim] = page;
        }
        printf("ref=%d  ", page); page_print_frames(frames, count); printf("  FAULT\n");
    }
    printf("Total page faults (OPTIMAL) = %d / %d\n", faults, REFS);
    return faults;
}

/* ---------------------------------------------------------------------- */
static void run_page_replacement(void) {
    printf("============================================================\n");
    printf(" Page Replacement Simulator - Ride-Hailing Dispatch System\n");
    printf(" Frames = %d | Reference string length = %d\n", FRAMES, REFS);
    printf(" Ref string: ");
    for (int i = 0; i < REFS; i++) printf("%d ", pr_ref[i]);
    printf("\n============================================================\n");

    int f_fifo = page_fifo();
    int f_lru = page_lru();
    int f_opt = page_optimal();

    printf("\n============================================================\n");
    printf(" Summary:\n");
    printf("   FIFO    : %d faults  (hit ratio %.2f)\n", f_fifo, (REFS - f_fifo) / (double)REFS);
    printf("   LRU     : %d faults  (hit ratio %.2f)\n", f_lru, (REFS - f_lru) / (double)REFS);
    printf("   OPTIMAL : %d faults  (hit ratio %.2f)\n", f_opt, (REFS - f_opt) / (double)REFS);
    printf("============================================================\n");
}

/* ==========================================================================
 * PART III - DISK SCHEDULING
 * ======================================================================= */

#define QLEN 8
#define MAX_CYL 150
#define MIN_CYL 0

static int disk_queue[QLEN] = {30, 120, 45, 100, 10, 140, 60, 90};
static const int HEAD_START = 75;

static int disk_iabs(int x) { return x < 0 ? -x : x; }

static int disk_cmp_int(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}

static void disk_print_seq(int *seq, int n, int start) {
    printf("Service order: %d", start);
    for (int i = 0; i < n; i++) printf(" -> %d", seq[i]);
    printf("\n");
}

static int disk_total_movement(int *seq, int n, int start) {
    int total = 0, cur = start;
    for (int i = 0; i < n; i++) {
        total += disk_iabs(seq[i] - cur);
        cur = seq[i];
    }
    return total;
}

/* ---------------------------------------------------------------------- */
static void disk_fcfs(void) {
    int seq[QLEN];
    for (int i = 0; i < QLEN; i++) seq[i] = disk_queue[i];
    printf("\n--- FCFS ---\n");
    disk_print_seq(seq, QLEN, HEAD_START);
    printf("Total head movement = %d cylinders\n", disk_total_movement(seq, QLEN, HEAD_START));
}

/* ---------------------------------------------------------------------- */
static void disk_sstf(void) {
    int remaining[QLEN];
    for (int i = 0; i < QLEN; i++) remaining[i] = disk_queue[i];
    int used[QLEN] = {0};
    int seq[QLEN];
    int cur = HEAD_START;

    for (int step = 0; step < QLEN; step++) {
        int best = -1, best_dist = 1 << 30;
        for (int i = 0; i < QLEN; i++) {
            if (used[i]) continue;
            int dist = disk_iabs(remaining[i] - cur);
            if (dist < best_dist || (dist == best_dist && remaining[i] < remaining[best])) {
                best_dist = dist;
                best = i;
            }
        }
        used[best] = 1;
        seq[step] = remaining[best];
        cur = remaining[best];
    }

    printf("\n--- SSTF ---\n");
    disk_print_seq(seq, QLEN, HEAD_START);
    printf("Total head movement = %d cylinders\n", disk_total_movement(seq, QLEN, HEAD_START));
}

/* ---------------------------------------------------------------------- */
/* SCAN: head moves toward the higher-numbered end first, servicing all
 * requests along the way, reaches the disk end (MAX_CYL), then reverses. */
static void disk_scan(void) {
    int up[QLEN], down[QLEN], nup = 0, ndown = 0;
    for (int i = 0; i < QLEN; i++) {
        if (disk_queue[i] >= HEAD_START) up[nup++] = disk_queue[i];
        else down[ndown++] = disk_queue[i];
    }
    qsort(up, nup, sizeof(int), disk_cmp_int);
    qsort(down, ndown, sizeof(int), disk_cmp_int);

    int seq[QLEN + 1];
    int n = 0;
    for (int i = 0; i < nup; i++) seq[n++] = up[i];
    seq[n++] = MAX_CYL;                              /* travel to disk end */
    for (int i = ndown - 1; i >= 0; i--) seq[n++] = down[i];

    printf("\n--- SCAN (moving toward higher cylinder first) ---\n");
    disk_print_seq(seq, n, HEAD_START);
    printf("Total head movement = %d cylinders\n", disk_total_movement(seq, n, HEAD_START));
}

/* ---------------------------------------------------------------------- */
/* C-SCAN: head moves up to MAX_CYL, jumps to MIN_CYL, continues upward.  */
static void disk_cscan(void) {
    int up[QLEN], down[QLEN], nup = 0, ndown = 0;
    for (int i = 0; i < QLEN; i++) {
        if (disk_queue[i] >= HEAD_START) up[nup++] = disk_queue[i];
        else down[ndown++] = disk_queue[i];
    }
    qsort(up, nup, sizeof(int), disk_cmp_int);
    qsort(down, ndown, sizeof(int), disk_cmp_int);

    int seq[QLEN + 2];
    int n = 0;
    for (int i = 0; i < nup; i++) seq[n++] = up[i];
    seq[n++] = MAX_CYL;         /* travel to disk end   */
    seq[n++] = MIN_CYL;         /* circular jump to 0   */
    for (int i = 0; i < ndown; i++) seq[n++] = down[i];

    printf("\n--- C-SCAN ---\n");
    disk_print_seq(seq, n, HEAD_START);
    printf("Total head movement = %d cylinders (includes return traversal to 0)\n",
           disk_total_movement(seq, n, HEAD_START));
}

/* ---------------------------------------------------------------------- */
static void run_disk_scheduling(void) {
    printf("============================================================\n");
    printf(" Disk Scheduling Simulator - Ride-Hailing Dispatch System\n");
    printf(" Cylinders 0-%d | Head start = %d\n", MAX_CYL, HEAD_START);
    printf(" Queue: ");
    for (int i = 0; i < QLEN; i++) printf("%d ", disk_queue[i]);
    printf("\n============================================================\n");

    disk_fcfs();
    disk_sstf();
    disk_scan();
    disk_cscan();

    printf("\n============================================================\n");
    printf(" Summary (Total Head Movement):\n");
    printf("   FCFS   : 595 cylinders\n");
    printf("   SSTF   : 195 cylinders\n");
    printf("   SCAN   : 215 cylinders\n");
    printf("   C-SCAN : 285 cylinders\n");
    printf("============================================================\n");
}

/* ==========================================================================
 * MAIN - runs all three parts in sequence
 * ======================================================================= */
int main(void) {
    printf("############################################################\n");
    printf("#  Ride-Hailing Dispatch System - CSA04 Combined Simulator  #\n");
    printf("#  CPU Scheduling + Page Replacement + Disk Sched. #\n");
    printf("############################################################\n");

    run_cpu_scheduling();
    run_page_replacement();
    run_disk_scheduling();

    printf("\n############################################################\n");
    printf(" All three parts simulated successfully.\n");
    printf("############################################################\n");
    return 0;
}
