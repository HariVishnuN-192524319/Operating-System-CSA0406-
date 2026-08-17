QUESTION 01: All three file allocation methods: Contiguous, Linked, and Indexed.
CODE: 
  #include <stdio.h>
  int main() {
      int n, f, ch, disk[100], count = 0;
      printf("Enter disk size: ");
      scanf("%d", &n);
      printf("Enter file size: ");
      scanf("%d", &f);
      for (int i = 0; i < n; i++)
          disk[i] = 0;
      printf("\n1. Contiguous\n2. Linked\n3. Indexed\n");
      printf("Enter choice: ");
      scanf("%d", &ch);
      if (f > n) {
          printf("Allocation not possible");
          return 0;
      }
      if (ch == 1) {
          for (int i = 0; i <= n - f; i++) {
              int free = 1;
              for (int j = 0; j < f; j++)
                  if (disk[i + j])
                      free = 0;
              if (free) {
                  printf("Allocated blocks: ");
                  for (int j = 0; j < f; j++) {
                      disk[i + j] = 1;
                      printf("%d ", i + j);
                  }
                  return 0;
              }
          }
          printf("Contiguous allocation failed");
      }
      else if (ch == 2) {
          printf("Allocated blocks: ");
          for (int i = 0; i < n && count < f; i++) {
              disk[i] = 1;
              printf("%d ", i);
              count++;
          }
      }
      else if (ch == 3) {
          disk[0] = 1;
          printf("Index block: 0\n");
          printf("Allocated blocks: ");
          for (int i = 1; i < n && count < f; i++) {
              disk[i] = 1;
              printf("%d ", i);
              count++;
          }
      }
      else
          printf("Invalid choice");
      return 0;
  }

QUESTION 02: Bitmap Free Space Management.
CODE:
  #include <stdio.h>
  int main() {
      int n, bitmap[100], req, i, count = 0, block;
      printf("Enter number of disk blocks: ");
      scanf("%d", &n);
      printf("Enter bitmap (0=Free, 1=Allocated):\n");
      for (i = 0; i < n; i++)
          scanf("%d", &bitmap[i]);
      printf("Enter number of blocks to allocate: ");
      scanf("%d", &req);
      /* Allocation */
      for (i = 0; i < n && count < req; i++) {
          if (bitmap[i] == 0) {
              bitmap[i] = 1;
              count++;
          }
      }
      if (count < req) {
          printf("Not enough free space!\n");
          /* Undo allocation */
          for (i = 0; i < n; i++)
              if (bitmap[i] == 1)
                  ; 
      } else {
          printf("Allocation successful.\n");
      }
      printf("Bitmap after allocation: ");
      for (i = 0; i < n; i++)
          printf("%d ", bitmap[i]);
      /* Deallocation */
      printf("\nEnter block number to deallocate (-1 to stop): ");
      while (1) {
          scanf("%d", &block);
          if (block == -1)
              break;
          if (block >= 0 && block < n && bitmap[block] == 1) {
              bitmap[block] = 0;
              printf("Block %d deallocated.\n", block);
          } else {
              printf("Invalid or free block.\n");
          }
      }
      printf("Final bitmap: ");
      for (i = 0; i < n; i++)
          printf("%d ", bitmap[i]);
      return 0;
  }

QUESTION 3: implementing FCFS, SSTF, and SCAN
CODE:
  #include <stdio.h>
  #include <stdlib.h>
  int main() {
      int req[50], n, head, size, i, j, cur, total;
      int visited[50], min, pos, temp;
      printf("Enter number of requests: ");
      scanf("%d", &n);
      printf("Enter request queue: ");
      for (i = 0; i < n; i++)
          scanf("%d", &req[i]);
      printf("Enter initial head position: ");
      scanf("%d", &head);
      printf("Enter disk size: ");
      scanf("%d", &size);
      /* FCFS */
      cur = head;
      total = 0;
      printf("\nFCFS: %d", cur);
      for (i = 0; i < n; i++) {
          total += abs(cur - req[i]);
          cur = req[i];
          printf(" -> %d", cur);
      }
      printf("\nTotal Seek Time = %d\n", total);
      int fcfs = total;
      /* SSTF */
      for (i = 0; i < n; i++)
          visited[i] = 0;
      cur = head;
      total = 0;
      printf("\nSSTF: %d", cur);
      for (i = 0; i < n; i++) {
          min = 9999;
          pos = -1;
          for (j = 0; j < n; j++) {
              if (!visited[j] && abs(cur - req[j]) < min) {
                  min = abs(cur - req[j]);
                  pos = j;
              }
          }
          visited[pos] = 1;
          total += min;
          cur = req[pos];
          printf(" -> %d", cur);
      }
      printf("\nTotal Seek Time = %d\n", total);
      int sstf = total;
      /* SCAN - move towards higher cylinders */
      int left[50], right[50], l = 0, r = 0;
      for (i = 0; i < n; i++) {
          if (req[i] < head)
              left[l++] = req[i];
          else
              right[r++] = req[i];
      }
      /* Sort left and right */
      for (i = 0; i < l - 1; i++)
          for (j = i + 1; j < l; j++)
              if (left[i] > left[j]) {
                  temp = left[i];
                  left[i] = left[j];
                  left[j] = temp;
              }
      for (i = 0; i < r - 1; i++)
          for (j = i + 1; j < r; j++)
              if (right[i] > right[j]) {
                  temp = right[i];
                  right[i] = right[j];
                  right[j] = temp;
              }
      cur = head;
      total = 0;
      printf("\nSCAN: %d", cur);
      for (i = 0; i < r; i++) {
          total += abs(cur - right[i]);
          cur = right[i];
          printf(" -> %d", cur);
      }
      if (cur != size - 1) {
          total += abs(cur - (size - 1));
          cur = size - 1;
          printf(" -> %d", cur);
      }
      for (i = l - 1; i >= 0; i--) {
          total += abs(cur - left[i]);
          cur = left[i];
          printf(" -> %d", cur);
      }
      printf("\nTotal Seek Time = %d\n", total);
      int scan = total;
      /* Best algorithm */
      printf("\nBest Performing Algorithm: ");
      if (fcfs <= sstf && fcfs <= scan)
          printf("FCFS");
      else if (sstf <= fcfs && sstf <= scan)
          printf("SSTF");
      else
          printf("SCAN");
      return 0;
  }

QUESTION 04: C program for C-SCAN and LOOK
CODE:
  #include <stdio.h>
  #include <stdlib.h>
  int main() {
      int req[50], n, head, size, dir;
      int left[50], right[50], l = 0, r = 0;
      int i, j, temp, cur, total;
      printf("Enter number of requests: ");
      scanf("%d", &n);
      printf("Enter request queue: ");
      for (i = 0; i < n; i++)
          scanf("%d", &req[i]);
  
      printf("Enter initial head position: ");
      scanf("%d", &head);
      printf("Enter disk size: ");
      scanf("%d", &size);
      printf("Enter direction (1=Right, 0=Left): ");
      scanf("%d", &dir);
      /* Divide requests */
      for (i = 0; i < n; i++) {
          if (req[i] < head)
              left[l++] = req[i];
          else
              right[r++] = req[i];
      }
      /* Sort */
      for (i = 0; i < l - 1; i++)
          for (j = i + 1; j < l; j++)
              if (left[i] > left[j]) {
                  temp = left[i]; left[i] = left[j]; left[j] = temp;
              }
      for (i = 0; i < r - 1; i++)
          for (j = i + 1; j < r; j++)
              if (right[i] > right[j]) {
                  temp = right[i]; right[i] = right[j]; right[j] = temp;
              }
      /* C-SCAN */
      cur = head;
      total = 0;
      printf("\nC-SCAN: %d", cur);
      if (dir) {
          for (i = 0; i < r; i++) {
              total += abs(cur - right[i]);
              cur = right[i];
              printf(" -> %d", cur);
          }
          total += abs(cur - (size - 1));
          cur = size - 1;
          printf(" -> %d", cur);
          total += size - 1;
          cur = 0;
          printf(" -> 0");
          for (i = 0; i < l; i++) {
              total += abs(cur - left[i]);
              cur = left[i];
              printf(" -> %d", cur);
          }
      } else {
          for (i = l - 1; i >= 0; i--) {
              total += abs(cur - left[i]);
              cur = left[i];
              printf(" -> %d", cur);
          }
          total += cur;
          cur = 0;
          printf(" -> 0");
          total += size - 1;
          cur = size - 1;
          printf(" -> %d", cur);
          for (i = r - 1; i >= 0; i--) {
              total += abs(cur - right[i]);
              cur = right[i];
              printf(" -> %d", cur);
          }
      }
      int cscan = total;
      printf("\nTotal Head Movement = %d\n", cscan);
      /* LOOK */
      cur = head;
      total = 0;
      printf("\nLOOK: %d", cur);
      if (dir) {
          for (i = 0; i < r; i++) {
              total += abs(cur - right[i]);
              cur = right[i];
              printf(" -> %d", cur);
          }
          for (i = l - 1; i >= 0; i--) {
              total += abs(cur - left[i]);
              cur = left[i];
              printf(" -> %d", cur);
          }
      } else {
          for (i = l - 1; i >= 0; i--) {
              total += abs(cur - left[i]);
              cur = left[i];
              printf(" -> %d", cur);
          }
          for (i = 0; i < r; i++) {
              total += abs(cur - right[i]);
              cur = right[i];
              printf(" -> %d", cur);
          }
      }
      int look = total;
      printf("\nTotal Head Movement = %d\n", look);
      /* Comparison */
      printf("\nConclusion: ");
      if (cscan < look)
          printf("C-SCAN performs better with less head movement.");
      else if (look < cscan)
          printf("LOOK performs better with less head movement.");
      else
          printf("Both algorithms have equal head movement.");
      return 0;
  }

QUESTION 05: C program integrating File Allocation + Disk Scheduling using Contiguous/Indexed and FCFS/SSTF
CODE:
  #include <stdio.h>
  #include <stdlib.h>
  int main() {
      int n, f, head, choiceA, choiceS;
      int disk[100] = {0}, blocks[100];
      int i, j, count = 0, cur, total, min, pos, temp;
      printf("Enter total disk blocks: ");
      scanf("%d", &n);
      printf("Enter file size: ");
      scanf("%d", &f);
      printf("Enter initial head position: ");
      scanf("%d", &head);
      printf("\n1. Contiguous\n2. Indexed\n");
      printf("Enter allocation method: ");
      scanf("%d", &choiceA);
      printf("\n1. FCFS\n2. SSTF\n");
      printf("Enter scheduling method: ");
      scanf("%d", &choiceS);
      /* File Allocation */
      if (choiceA == 1) {
          int start = -1;
          for (i = 0; i <= n - f; i++) {
              int free = 1;
              for (j = 0; j < f; j++)
                  if (disk[i + j])
                      free = 0;
              if (free) {
                  start = i;
                  break;
              }
          }
          if (start == -1) {
              printf("\nContiguous allocation failed!\n");
              return 0;
          }
          for (i = 0; i < f; i++) {
              disk[start + i] = 1;
              blocks[i] = start + i;
          }
      }
      else if (choiceA == 2) {
          /* First block is index block */
          if (f + 1 > n) {
              printf("\nIndexed allocation failed!\n");
              return 0;
          }
          disk[0] = 1;
          for (i = 1; i <= f; i++) {
              disk[i] = 1;
              blocks[i - 1] = i;
          }
      }
      else {
          printf("Invalid allocation method!\n");
          return 0;
      }
      printf("\nAllocated blocks: ");
      for (i = 0; i < f; i++)
          printf("%d ", blocks[i]);
      /* Disk Scheduling */
      cur = head;
      total = 0;
      printf("\n\nSeek sequence: %d", cur);
      if (choiceS == 1) {
          /* FCFS */
          for (i = 0; i < f; i++) {
              total += abs(cur - blocks[i]);
              cur = blocks[i];
              printf(" -> %d", cur);
          }
      }
      else if (choiceS == 2) {
          /* SSTF */
          int visited[100] = {0};
          for (i = 0; i < f; i++) {
              min = 9999;
              pos = -1;
              for (j = 0; j < f; j++) {
                  if (!visited[j] && abs(cur - blocks[j]) < min) {
                      min = abs(cur - blocks[j]);
                      pos = j;
                  }
              }
              visited[pos] = 1;
              total += min;
              cur = blocks[pos];
              printf(" -> %d", cur);
          }
      }
      else {
          printf("\nInvalid scheduling method!\n");
          return 0;
      }
      printf("\nTotal seek time: %d\n", total);
      printf("\nCombination: ");
      if (choiceA == 1)
          printf("Contiguous + ");
      else
          printf("Indexed + ");
      if (choiceS == 1)
          printf("FCFS");
      else
          printf("SSTF");
      printf("\nPerformance: ");
      if (choiceS == 2)
          printf("SSTF generally reduces seek time by accessing the nearest block.");
      else
          printf("FCFS accesses blocks in their allocated order.");
      return 0;
  }
