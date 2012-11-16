#include <stdio.h>
#include <stdlib.h>
#include "platformcode.h"

#define NUM_NODES                          10
#define NONE                               9999

struct _NODE
{
  int iDist;
  int iPrev;
};
typedef struct _NODE NODE;

struct _QITEM
{
  int iNode;
  int iDist;
  int iPrev;
  struct _QITEM *qNext;
};
typedef struct _QITEM QITEM;

QITEM *qHead = NULL;

int AdjMatrix[NUM_NODES][NUM_NODES] = {{32,  32,  54,  12,  52,  56,  8,   30,  44,  94},
                                       {76,  54,  65,  14,  89,  69,  4,   16,  24,  47},
                                       {38,  31,  75,  40,  61,  21,  84,  51,  86,  41},
                                       {80,  16,  53,  14,  94,  29,  77,  99,  16,  29},
                                       {59,  7,   14,  78,  79,  45,  54,  83,  8,   94},
                                       {94,  41,  3,   61,  27,  19,  33,  35,  78,  38},
                                       {3,   55,  41,  76,  49,  68,  83,  23,  67,  15},
                                       {68,  28,  47,  12,  82,  6,   26,  96,  98,  75},
                                       {7,   1,   46,  39,  12,  68,  41,  28,  31,  0},
                                       {82,  97,  72,  61,  39,  48,  11,  99,  38,  49}};

int g_qCount = 0;
NODE rgnNodes[NUM_NODES];
int ch;
int iPrev, iNode;
int i, iCost, iDist;


// void print_path (NODE *rgnNodes, int chNode)
// {
//   if (rgnNodes[chNode].iPrev != NONE)
//     {
//       print_path(rgnNodes, rgnNodes[chNode].iPrev);
//     }
//   // printf (" %d", chNode);
//   // fflush(stdout);
// }


void enqueue (int iNode, int iDist, int iPrev)
{
  QITEM *qNew = (QITEM *) malloc(sizeof(QITEM));
  QITEM *qLast = qHead;

  // if (!qNew)
  //   {
  //     fprintf(stderr, "Out of memory.\n");
  //     exit(1);
  //   }
  qNew->iNode = iNode;
  qNew->iDist = iDist;
  qNew->iPrev = iPrev;
  qNew->qNext = NULL;

  if (!qLast)
    {
      qHead = qNew;
    }
  else
    {
      while (qLast->qNext) qLast = qLast->qNext;
      qLast->qNext = qNew;
    }
  g_qCount++;
  //               ASSERT(g_qCount);
}


QITEM* dequeue (int *piNode, int *piDist, int *piPrev)
{
  QITEM *qKill = qHead;

  if (qHead != 0)
    {
      //                 ASSERT(g_qCount);
      *piNode = qHead->iNode;
      *piDist = qHead->iDist;
      *piPrev = qHead->iPrev;
      qHead = qHead->qNext;
      g_qCount--;
      //free(qKill);
      return qKill;
    }
    return 0;
}


int qcount (void)
{
  return(g_qCount);
}

int dijkstra(int chStart, int chEnd)
{



  for (ch = 0; ch < NUM_NODES; ch++)
    {
      rgnNodes[ch].iDist = NONE;
      rgnNodes[ch].iPrev = NONE;
    }

  if (chStart == chEnd)
    {
      return 0;
    }
  else
    {
      rgnNodes[chStart].iDist = 0;
      rgnNodes[chStart].iPrev = NONE;

      enqueue (chStart, 0, NONE);

     while (qcount() > 0)
	{
	  QITEM *tmp = dequeue (&iNode, &iDist, &iPrev);
          if(tmp != 0)
                free(tmp);
	  for (i = 0; i < NUM_NODES; i++)
	    {
                iCost = AdjMatrix[iNode][i];
	      if (iCost != NONE)
		{
		  if ((NONE == rgnNodes[i].iDist) ||
		      (rgnNodes[i].iDist > (iCost + iDist)))
		    {
		      rgnNodes[i].iDist = iDist + iCost;
		      rgnNodes[i].iPrev = iNode;
		      enqueue (i, iDist + iCost, iNode);
		    }
		}
	    }
	}

      // printf("Shortest path is %d in cost. ", rgnNodes[chEnd].iDist);
      // printf("Path is: ");
      // print_path(rgnNodes, chEnd);
      // printf("\n");
    }
  return 0;
}

int main() {
  int i,j,n;

  initialise_trigger();
  start_trigger();
  /* finds 10 shortest paths between nodes */
  for(n = 0; n < REPEAT_FACTOR >> 9; ++n) {
  for(j = 0; j < NUM_NODES; ++j)
    for (i=0;i<NUM_NODES;i++) {
        dijkstra(i,j);
    }
  }
  stop_trigger();

  return 0;
}
