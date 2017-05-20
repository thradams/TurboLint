#pragma once


#define List(T)\
struct {\
    T* pHead; \
    T* pTail; \
}
#define LIST_INIT { NULL, NULL }


#define List_Destroy(T, p)\
while ((p)->pHead) {\
    T* pCurrent = (p)->pHead; \
    (p)->pHead = (p)->pHead->pNext; \
    T##_Delete(pCurrent); \
}

#define ForEachListItem(T, var, list)\
  for (T * var = (list)->pHead ; var != NULL; var =  var->pNext)

#define List_IsFirstItem(pList, pItem) ((pList)->pHead == (pItem))
#define List_IsLastItem(pList, pItem) ((pList)->pTail == (pItem))

#define List_HasItems(pList) \
 ((pList)->pHead != NULL)

#define List_IsEmpty(pList) \
 ((pList)->pHead == NULL)

#define List_Back(pList) \
 ((pList)->pTail)

#define List_Front(pList) \
 ((pList)->pHead)

#define List_HasOneItem(pList) \
 ((pList)->pHead != NULL && (pList)->pHead == (pList)->pTail)

#define List_Add(pList, pItem) \
if ((pList)->pHead == NULL) {\
    (pList)->pHead = (pItem); \
    (pList)->pTail = (pItem); \
}\
else {\
      (pList)->pTail->pNext = (pItem); \
      (pList)->pTail = (pItem); \
  }

