/**
 * fast.c
 *  The program will output a list the twenty most frequently used word common
 *  amongst all files provided. The list is produced in descending order of
 *  appearance. It parses one file at a time using multiple threads as long
 *  as the file is greater than 80 bytes in length, where it will use only one.
 *  The results are stored in a hash table, which is then fed into a linked-
 *  list sorted by word count.
 *
 *  Clocked around .085s on average for 25 sample files.
 *
 *  Created on: Mar 19, 2012
 *  Last modified: Apr 3,2012
 *  Author: jdb
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/sysinfo.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

/*Structs*/
typedef struct entry {
  char word[50]; //stored word; should be < 46 chars
  int fCount; //number of files word has appeared in
  int count; //number of times word has appeared
  pthread_mutex_t lock;
  struct entry* next;
} entry;

typedef struct elem {
  struct entry* word; //pointer to entry with word
  struct elem* next; //ptr to next elem
} elem;

typedef struct info {
  char* bfr; //pointer to file buffer
  int id; //thread id
} info;

/*functions*/
static int findSmallest(int argc, char* argv[]);
void openFile(char* filename);
void* actions(void* infoStruct);
static void setRange(char* bfr, int id, int* r);
//int readWord(int fileDescriptor, char* wordToRead);
void update(char* word);
entry* add(char* word);
int hash(char*, int);
void topTwenty(void);
static void buildList(void);
static void listAdd(entry*);

/*Globals*/
#define tableSize 2048
#define MAX_T 8
static int fileCount = 0; //number of files processed/being processed
static int fLength; //length of current file being processed
static int blockSize; //initial # of bytes each thread is to process
static int totalFiles; //total number of files to process
static int tActive; //number of threads active for current file
static int fd; //file descriptor of current file
static entry* ht[tableSize]; //hash table
static pthread_mutex_t bktLocks[tableSize]; //array of bucket locks
static pthread_t threads[MAX_T]; //thread array
static char* buffer;
static elem* head = NULL; //head of top20 list
static elem* tail = NULL; //tail of top20 list

/*Program*/
int main(int argc, char *argv[]) {
  //fprintf(stderr, "fast running . . . \n");
  //start_timer();
  if (argc < 2) { //No files provided; close
    fprintf(stderr, "no files provided\n");
    exit(-1);
  } else { //process files
    //fprintf(stderr, "initializing bucket locks\n");
    int i;
    for (i = 0; i < tableSize; i++) { //initialize bucket locks
      if (pthread_mutex_init(&bktLocks[i], NULL) != 0) {
        fprintf(stderr, "bucket lock %d failed to initialize", i);
        exit(-1);
      }
    }
    int smallest = findSmallest(argc, argv);
    totalFiles = argc - 1;
    //fprintf(stderr, "%d files to read\n", totalFiles);

    openFile(argv[smallest]); //process smallest file

    i = 1;
    while (i < argc) { //file loop
      if (i != smallest)
        openFile(argv[i]);
      i++;
    } //end of file loop
  } //end of main loop

  topTwenty();
  return 0;
}

/**
 * Handles the opening of files and initialization of threads for each file.
 * This includes reading the file into a buffer.
 */
void openFile(char* filename) {
  fd = open(filename, O_RDONLY);
  if (fd == -1) { //bad file
    printf("file %s could not be opened; exiting\n", filename);
    exit(-1);
  } else {
    fprintf(stderr, "Starting %s\n", filename);
    fileCount++;
    fLength = (int) lseek(fd, 0, SEEK_END); //get file size
    fprintf(stderr,"\tfilesize: %d\n",fLength);
    blockSize = fLength / MAX_T; //get block size
    fprintf(stderr,"\tblockSize: %d\n",blockSize);
    lseek(fd, 0, SEEK_SET); //return fpos to start
    fprintf(stderr,"back to start of file\n");
    char bfr[fLength];
    //buffer = malloc(fLength);
    fprintf(stderr,"bfr[%d] assigned\n",fLength);
    if ((read(fd, bfr, fLength)) <= 0) { //read in file
      fprintf(stderr, "failed to read %s to buffer\n", filename);
      exit(-1);
    }
    fprintf(stderr,"read in file\n");
    if (fLength < 80) //if file too small, only use one thread
      tActive = 1;
    else
      tActive = MAX_T;
    //start all threads
    int j;fprintf(stderr,"starting threads\n");
    for (j = 0; j < tActive; j++) { //thread loop
      info* threadInfo = malloc(sizeof(info));
      if (threadInfo == NULL) {
        fprintf(stderr, "No more memory");
        exit(-1);
      }
      threadInfo->bfr = bfr;
      threadInfo->id = j;
      if (pthread_create(&threads[j], NULL, actions, (void*) threadInfo)
          != 0) {
        fprintf(stderr, "thread %d failed to initialize on %s\n", j, filename);
        exit(-1);
      }
    } //end of thread loop

    //wait on threads
    int k;
    for (k = 0; k < tActive; k++) { //wait for all threads to finish
      if (pthread_join(threads[k], NULL) != 0) {
        fprintf(stderr, "failed to join on thread %d, %s\n", k, filename);
        exit(-1);
      }
      fprintf(stderr, "thread[%d] finished\n", k);
    }
    close(fd);
    //free(buffer);
    fprintf(stderr, "  Done with %s\n", filename);
  }
}

/**
 * Serially process the file list and returns the index of the smallest
 */
static int findSmallest(int argc, char* argv[]) {
  int idx = 1; //start with first file
  int fd = open(argv[1], O_RDONLY);
  int smallest = lseek(fd, 0, SEEK_END);
  close(fd);

  int i, fsize;
  for (i = 2; i < argc; i++) {
    fd = open(argv[i], O_RDONLY);
    fsize = lseek(fd, 0, SEEK_END);
    if (fsize == 0) {
      exit(-1);
    }
    if (fsize < smallest) {
      smallest = fsize;
      idx = i;
    }
    close(fd);
  }
  //fprintf(stderr, "%s is the smallest file\n", argv[idx]);
  return idx;
}

/**action
 * Processes current file. Reads in every word and updates their count within
 * the hash table.
 */
void* actions(void* data) {
  info* tInfo = (info*) data;
  int threadID = tInfo->id; //get id
  //fprintf(stderr,"thread[%d] active\n",threadID);
  char* bfr = tInfo->bfr;
  int range[2];
  setRange(tInfo->bfr, threadID, range); //get range from id
  fprintf(stderr, "thread[%d]: [%d,%d] \n", threadID, range[0], range[1]);
  char word[50];
  int len = 0;
  //int h;
  //bucket* head;
  //entry* entry;

  /**For multi threaded:
   * 1) while within max range
   * 2) read in words until you hit a non-alpha
   */
  int x;
  int b = range[0]; //set min
  while (b < range[1]) { //go until max; main loop
    //memset(&word[0], 0, sizeof(word)); //clear word[]
    len = 0; //reset length
    for (;; ++b) { //readWord loop(infinite)
      x = (int)bfr[b];
      //((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
      if (!((x >= 65 && x <= 90) || (x >= 97 && x <= 122))) { //if char is non-alpha
        if (len == 0) //and word length is zero(no letters yet)
          continue; //skip over to next
        else
          break; //otherwise stop and return word as is
      }
      //word[len++] = tolower(x);

      if( x >= 65 && x <= 90 )//if capital letter
        word[len++] = x+32;
      else
        word[len++] = x;
    } //end of readWord loop
    if (len < 6 || len > 50) //test for valid length
      continue; //go to next word

    word[len] = '\0'; //return word with null char
    //printf("readWord: %s\nbytes read in = %d\n",word,b);
    update(word);
  } //end main loop

  return (void *) 0;
}

/**
 * Determines the range in bytes the thread will read in from the file, based
 * off of thread id. Sets [min,max] based on size of file and number of threads
 * running. Tests the starting position to ensure it doesn't begin working from
 * the middle of a word by starting at (min-1) and continuing until it hits a
 * non-alpha char. Returns the number of bytes in from the min it was moved
 * to accommodate starting in the middle of a word.
 */
static void setRange(char* bfr, int id, int* r) {
  if (tActive == 1) { //Single thread case
    r[0] = 0;
    r[1] = fLength;
    return;
  }
  if (id == 0) { //if first thread
    r[0] = 0; //start at zero
    r[1] = blockSize - 1;
    return;
  }
  r[0] = id * blockSize; //get min
  if (id == MAX_T - 1) //if last thread
    r[1] = fLength; //read to the end
  else
    r[1] = (id + 1) * blockSize - 1;

//check for correct positioning
  if (isalpha((int)bfr[r[0]-1])) //if char before min is alphabetic
    while (isalpha((int)bfr[r[0]])) //go until it isn't
      r[0]++;

}

/**
 * Updates word counts in the hashtable. Adds all words if this is the first
 * file. Otherwise, only updates word counts. If this is not the first file,
 * does nothing.
 */
void update(char* word) {
  int h = hash(word, strlen(word));
  pthread_mutex_lock(&bktLocks[h]); //lock on bucket
  entry* entry = ht[h]; //get head entry
  while (entry != NULL && strcmp(word, entry->word) != 0)
    entry = entry->next;
  if (entry == NULL) { //Word not yet entered
    if (fileCount == 1) //if first file
      entry = add(word); //add word
    pthread_mutex_unlock(&bktLocks[h]); //unlock
  } else {
    pthread_mutex_lock(&entry->lock); //lock on word entry
    pthread_mutex_unlock(&bktLocks[h]); //unlock on bucket
    entry->count++;
    if (entry->fCount == (fileCount - 1)) //off by one
      entry->fCount++;
    pthread_mutex_unlock(&entry->lock); //unlock
  }
}

/**
 * Adds a new entry to the hash table. Mallocs the entry, then adds to the head
 * of the chain.
 */
entry* add(char* word) {
  int h = hash(word, strlen(word));
  entry* p = malloc(sizeof(entry)); //allocate new entry
  if (p == NULL) {
    fprintf(stderr, "No more memory");
    exit(-1);
  }
  if (pthread_mutex_init(&p->lock, NULL) != 0) //initialize lock
    exit(-1);
  p->next = ht[h]; //p points to current head entry, null or not
  ht[h] = p; //head now points to p

  p->count = 1;
  p->fCount = 1;
  strcpy(p->word, word);
//fprintf(stderr,"\t%s added\n",p->word);
  return p;
}

/*Hash function. Straight copy of FNV hash*/
int hash(char *key, int len) {
  unsigned int h = 2166136261u;
  int i;

  for (i = 0; i < len; i++)
    h = (h * 16777619) ^ key[i];

  h &= 0x7ff; //0111 1111 1111
//printf("hash: %s -----> %d\n", key, h);
  return h;
}

/**
 * Prints top 20 words.
 */
void topTwenty(void) {
//fprintf(stderr,"topTwenty called\n");
  buildList();
  //if (head == NULL)
  //  fprintf(stderr, "top20: head was still null after list creation");

  elem* p = head;
  int i = 0;
  while (p != NULL && i < 20) {
    //printf("%d: %s[%d]\n", i + 1, p->word->word, p->word->count);
    printf("%s\n", p->word->word);
    if (i == 19) {
      elem* q = p->next;
      while (q != NULL && q->word->count == p->word->count) {
        //rank: word[count]
        //printf("%d: %s[%d]\n", i + 1, q->word->word, q->word->count);
        //word
        printf("%s\n", q->word->word);
        q = q->next;
      }
      i++;
    }

    p = p->next;
    i++;
  }
}

/**
 * Builds a linked list from the hash table to determine the 20 most used words.
 */
static void buildList(void) {
  entry* p;
  int i;
  for (i = 0; i < tableSize; i++) {
    p = ht[i];
    while (p != NULL) {
      if (p->fCount == totalFiles) //if word was there in every file
        listAdd(p);
      p = p->next;
    }
  }
}

/**
 * Adds an elem to the list of words
 */
static void listAdd(entry * entry) {
  elem* p = malloc(sizeof(elem));
  if (p == NULL) {
    fprintf(stderr, "No more memory");
    exit(-1);
  }
  p->word = entry;
  p->next = NULL;

  if (head == NULL) { //empty list, add as head
    head = tail = p;
  } else if (entry->count >= head->word->count) { //add to head
    p->next = head;
    head = p;
  } else if (entry->count <= tail->word->count) { //add to tail
    tail->next = p;
    tail = p;
  } else {
    elem* prev = NULL;
    elem* q = head;
    //while things there and they're bigger than what you've got
    while (q->word->count > entry->count) {
      //fprintf(stderr,"\t\tlistAdd.%d > %d\n",q->word->count,entry->count);
      prev = q;
      q = q->next; //go to the next one
    }
    prev->next = p;
    p->next = q;
  }
}
