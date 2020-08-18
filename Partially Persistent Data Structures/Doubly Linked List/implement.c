#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

int_Node* addNode(int data)
{
  int_Node* newnode = (int_Node*) malloc(sizeof(int_Node));
  newnode->data = data;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (int_Mod*) malloc(sizeof(int_Mod));
  newnode->mod->data = JUNK;
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}



int_list_pp* int_init_list_pp()
{
  int_list_pp* newlist = (int_list_pp*) malloc(sizeof(int_list_pp));

  if(!newlist)
    {
      printf("Error in list creation\n");
      return NULL;
    }

  newlist->live_version = 0;

  for(int i = 0; i < MAX_OP; i++)
    newlist->head[i] = NULL;
      
  return newlist;
}



void int_print_list_pp(int_list_pp* list, int version)
{
  if(list->live_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
  
  int_Node* pCrawl = (int_Node*) malloc(sizeof(int_Node));

  printf("List of version %d\n", version);
	
  if(!pCrawl)	
    {
      printf("Memory allocation error");
      return;
    }

  for(pCrawl = list->head[version]; pCrawl != NULL; )
    {
      if((pCrawl->mod->version <= version) && (pCrawl->mod->version != UNUSED))
	{
	  printf("%d->", pCrawl->mod->data);
	  pCrawl = pCrawl->mod->next;
	}
      else
	{
	  printf("%d->", pCrawl->data);
	  pCrawl = pCrawl->next;
	}
    }
  
  printf("NULL\n");
}



int_Node* int_update_parentLeft_list_pp(int_list_pp* list, int_Node* lCrawl, int_Node* newnode, int live_version)
{

  if(lCrawl == NULL) return NULL;

  if(lCrawl->mod->version == UNUSED)
    {
      lCrawl->mod->data = lCrawl->data;
      lCrawl->mod->version = live_version;
      lCrawl->mod->next = newnode;
      lCrawl->mod->prev = lCrawl->prev;

      list->head[live_version] = list->head[live_version-1];
      return lCrawl;
    }
  else
    {
      int_Node* newnode_parent = addNode(lCrawl->mod->data);
    
      newnode_parent->next = newnode;

      if(lCrawl->mod->prev == NULL)
	{
	  list->head[live_version] = newnode_parent;
	  return newnode_parent;
	}
      
      newnode_parent->prev = int_update_parentLeft_list_pp(list, lCrawl->mod->prev, newnode_parent, live_version);
    }

}



int_Node* int_update_parentRight_list_pp(int_list_pp* list, int_Node* lCrawl, int_Node* newnode, int live_version)
{

  if(lCrawl == NULL) return NULL;
    
  if(lCrawl->mod->version == UNUSED)
    {
      lCrawl->mod->data = lCrawl->data;
      lCrawl->mod->version = live_version;
      lCrawl->mod->prev = newnode;
      lCrawl->mod->next = lCrawl->next;

      return lCrawl;
    }
  else
    {
      int_Node* newnode_parent = addNode(lCrawl->mod->data);
 
      newnode_parent->prev = newnode;

      // if(lCrawl->mod->next == NULL) return newnode_parent;
	
      newnode_parent->next = int_update_parentRight_list_pp(list, lCrawl->mod->next, newnode_parent, live_version);
    }

}



bool int_insert_list_pp(int_list_pp* list, int data, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;
  int_Node* newnode = addNode(data);
  
  int_Node* lCrawl = (int_Node*) malloc(sizeof(int_Node));
  int_Node* lCrawl_prev = (int_Node*) malloc(sizeof(int_Node));
  
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(!lCrawl_prev)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(lCrawl = list->head[live_version], lCrawl_prev = list->head[live_version]; lCrawl != NULL; index_count++)
    {
      // Check here redundancy
      if(lCrawl != list->head[live_version])
	lCrawl_prev = lCrawl->prev;
      
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= live_version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }
  
  if(list->head[live_version] == NULL)
    {
      list->head[live_version] = newnode;
      return true;
    }

  if(lCrawl == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index greater than length of the list. The element will be appended at the end of the list\n");
    }
  
  if(lCrawl_prev == list->head[live_version] && index == 1)
    lCrawl = lCrawl_prev;
  else if((lCrawl == NULL) && (lCrawl_prev->mod->version == UNUSED))
    lCrawl = lCrawl_prev->next;
  else if((lCrawl == NULL) && (lCrawl_prev->mod->version != UNUSED))
    lCrawl = lCrawl_prev->mod->next;
  else
    lCrawl = lCrawl_prev;  

  if(lCrawl->mod->version == UNUSED)
    {      
      live_version++;
      
      lCrawl->mod->data = lCrawl->data;
      lCrawl->mod->version = live_version;

      if(index != 0)
	{
	  lCrawl->mod->next = newnode;
	  lCrawl->mod->prev = lCrawl->prev;

	  newnode->next = int_update_parentRight_list_pp(list, lCrawl->next, newnode, live_version);
	  newnode->prev = int_update_parentLeft_list_pp(list, lCrawl, newnode, live_version);
	}
      else
	{
	  newnode->next = lCrawl;
  	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = newnode;
	  
	  list->head[live_version] = newnode;
      	}
    }
  else
    {
      live_version++;

      if(index !=0)
	{
	  newnode->next = int_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	  newnode->prev = int_update_parentLeft_list_pp(list, lCrawl, newnode, live_version);
	}
      else
	{
	  int_Node* trailNode = addNode(lCrawl->mod->data);
	  trailNode->next = lCrawl->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[live_version] = newnode;
	}
    }
  
  list->live_version = live_version;
  return true;
}



bool int_update_list_pp(int_list_pp* list, int data, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;

  int_Node* lCrawl = (int_Node*) malloc(sizeof(int_Node));
  
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(lCrawl = list->head[live_version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= live_version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }

  if(lCrawl == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      int_insert_list_pp(list, data, index);
    }
  else
    {     
      if(lCrawl->mod->version == UNUSED)
	{  
	  live_version++;
      
	  lCrawl->mod->data = data;
	  lCrawl->mod->version = live_version;

	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = lCrawl->prev;

	  list->head[live_version] = list->head[live_version-1];
	}
      else
	{
	  live_version++;
	  if(index != 0)
	    {
	      int_Node* newnode = addNode(data);
	  
	      newnode->next = int_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	      newnode->prev = int_update_parentLeft_list_pp(list, lCrawl->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      int_Node* newnode = addNode(data);
	  
	      newnode->next = int_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	      list->head[live_version] = newnode;
	    }
	}

      list->live_version = live_version;
    }
  return true;
}






bool int_delete_list_pp(int_list_pp* list, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int live_version = list->live_version;

  int_Node* lCrawl = (int_Node*) malloc(sizeof(int_Node));
  
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[live_version] == NULL)
    {
      printf("List is empty. Cannot delete from empty list");
      return false;
    }
  
  if(list->head[live_version]->next == NULL)
    {
      live_version++;
      list->head[live_version] = NULL;
       
      list->live_version = live_version;
      return true;
    }
  
  for(lCrawl = list->head[live_version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= live_version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }
  
  if(lCrawl == NULL) index_count--;

  if(index != index_count) 
    {
      printf("Index not found in the list\n");
      return false;
    }
  else
    {
      if(index == 0)
	{
	  if(lCrawl->mod->version == UNUSED)
	    {
	      if(lCrawl->next->mod->version == UNUSED)
		{  
		  live_version++;
		
		  lCrawl->next->mod->data = lCrawl->next->data;
		  lCrawl->next->mod->version = live_version;

		  lCrawl->next->mod->next = lCrawl->next->next;
		  lCrawl->next->mod->prev = lCrawl->prev;

		  list->head[live_version] = lCrawl->next;
		}
	      else
		{
		  live_version++;

		  int_Node* newnode = addNode(lCrawl->next->mod->data);

		  newnode->next = int_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode, live_version);
	  	  
		  list->head[live_version] = newnode;
		}
	    }
	  else
	    {
	      if(lCrawl->mod->next->mod->version == UNUSED)
		{  
		  live_version++;
		
		  lCrawl->mod->next->mod->data = lCrawl->mod->next->data;
		  lCrawl->mod->next->mod->version = live_version;

		  lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
		  lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

		  list->head[live_version] = lCrawl->mod->next;
		}
	      else
		{
		  live_version++;

		  int_Node* newnode = addNode(lCrawl->mod->next->mod->data);

		  newnode->next = int_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode, live_version);
	  	  
		  list->head[live_version] = newnode;
		}
	    }
	  
	  list->live_version = live_version;
	  return true;
	}

      if((lCrawl->next == NULL) && (lCrawl->mod->version == UNUSED))
	{
	  if(lCrawl->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      lCrawl->prev->mod->data = lCrawl->prev->data;
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else
	    {
	      live_version++;

	      int_Node* newnode = addNode(lCrawl->prev->mod->data);
	      
	      newnode->prev = int_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode, live_version);
	    }
 
	  list->live_version = live_version;
	  return true;
	}
      
      if((lCrawl->mod->next == NULL) && (lCrawl->mod->version != UNUSED))
	{
	  if(lCrawl->mod->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      lCrawl->mod->prev->mod->data = lCrawl->mod->prev->data;
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else
	    {
	      live_version++;

	      int_Node* newnode = addNode(lCrawl->mod->prev->mod->data);
	      
	      newnode->prev = int_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode, live_version);
	    }

	  list->live_version = live_version;
	  return true;
	}
      

      if(lCrawl->mod->version == UNUSED)
	{
	  if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {  
	      live_version++;

	      lCrawl->prev->mod->data = lCrawl->prev->data;
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      lCrawl->next->mod->data = lCrawl->next->data;
	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = lCrawl->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version != UNUSED))
	    {
	      live_version++;

	      int_Node* newnode = addNode(lCrawl->next->mod->data);
	      
	      lCrawl->prev->mod->data = lCrawl->prev->data;
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = newnode;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      newnode->prev = lCrawl->prev;		
	      newnode->next = int_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode, live_version);
	  	  
	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->prev->mod->version != UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {
	      live_version++;

	      int_Node* newnode = addNode(lCrawl->prev->mod->data);
	      
	      lCrawl->next->mod->data = lCrawl->next->data;
	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = newnode;

	      newnode->next = lCrawl->next;
	      newnode->prev = int_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      live_version++;
        
	      int_Node* newnode_prev = addNode(lCrawl->prev->mod->data);
	      int_Node* newnode_next = addNode(lCrawl->next->mod->data);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = int_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode_prev, live_version);
	      newnode_next->next = int_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode_next, live_version);
 	    }
	}
      else
	{
	  if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {  
	      live_version++;

	      lCrawl->mod->prev->mod->data = lCrawl->mod->prev->data;
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      lCrawl->mod->next->mod->data = lCrawl->mod->next->data;
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version != UNUSED))
	    {
	      live_version++;
	      	  
	      int_Node* newnode = addNode(lCrawl->mod->next->mod->data);
	  
	      lCrawl->mod->prev->mod->data = lCrawl->mod->prev->data;
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = newnode;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;
	      
	      newnode->prev = lCrawl->mod->prev;
	      newnode->next = int_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode, live_version);
	  	  
	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->mod->prev->mod->version != UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {
	      live_version++;
	      
	      int_Node* newnode = addNode(lCrawl->mod->prev->mod->data);       

	      lCrawl->mod->next->mod->data = lCrawl->mod->next->data;
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = newnode;

	      newnode->next = lCrawl->mod->next;

	      newnode->prev = int_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      live_version++;
	      
	      int_Node* newnode_prev = addNode(lCrawl->mod->prev->mod->data);
	      int_Node* newnode_next = addNode(lCrawl->mod->next->mod->data);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = int_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode_prev, live_version);
	      newnode_next->next = int_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode_next, live_version);
	    }

	}
      
      list->live_version = live_version;
    }
  return true;
}
