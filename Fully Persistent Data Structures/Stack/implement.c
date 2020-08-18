#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

int_Node* addNode(int data, int version)
{
  int_Node* newnode = (int_Node*) malloc(sizeof(int_Node));
  newnode->data = data;
  newnode->next = NULL;
  newnode->prev = NULL;
  newnode->node_version = version;
  
  newnode->mod = (int_Mod*) malloc(sizeof(int_Mod));
  newnode->mod->data = JUNK;
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}



int_stack_fp* int_init_stack_fp()
{
  int_stack_fp* newlist = (int_stack_fp*) malloc(sizeof(int_stack_fp));

  if(!newlist)
    {
      printf("Error in list creation\n");
      return NULL;
    }

  newlist->live_version = 0;

  for(int i = 0; i < MAX_OP; i++)
    newlist->head[i] = NULL;

  newlist->num_el = 0;
  
  return newlist;
}



void int_print_stack_fp(int_stack_fp* list, int version)
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
      printf("Memory allocation error\n");
      return;
    }

  printf("TOP<->");
    
  for(pCrawl = list->head[version]; pCrawl != NULL;)
    {
      if(pCrawl->node_version > version)
      	break;
      
      if((pCrawl->mod->version <= version) && (pCrawl->mod->version > UNUSED))
	{
	  //printf("dat %d, vers %d/////->", pCrawl->mod->data, pCrawl->mod->version);
	  printf("%d<->", pCrawl->mod->data);
	  pCrawl = pCrawl->mod->next;
	}
      else
	{
	  //printf("dat %d, vers %d/////->", pCrawl->data, pCrawl->node_version);
	  printf("%d<->", pCrawl->data);
	  pCrawl = pCrawl->next;
	}
    }
  
  printf("BOTTOM\n");
}


int_Node* int_update_parentLeft_list_fp(int_stack_fp* list, int_Node* lCrawl, int_Node* newnode, int live_version, int version)
{

  if(lCrawl == NULL) return NULL;

  if(lCrawl->mod->version == UNUSED)
    {
      lCrawl->mod->data = lCrawl->data;
      lCrawl->mod->version = live_version;
      lCrawl->mod->next = newnode;
      //lCrawl->mod->prev = lCrawl->prev;

      //changed here
      lCrawl->mod->prev = int_update_parentLeft_list_fp(list, lCrawl->prev, lCrawl, live_version, version);
	
      list->head[live_version] = list->head[version];
      return lCrawl;
    }
  else
    {
      int_Node* newnode_parent;

      if(lCrawl->mod->version <= version)
	{
	  newnode_parent = addNode(lCrawl->mod->data, live_version);
	  newnode_parent->next = newnode;

	  if(lCrawl->mod->prev == NULL)
	    {
	      list->head[live_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev, newnode_parent, live_version, version);
	}
      else
	{
	  newnode_parent = addNode(lCrawl->data, live_version);
	  newnode_parent->next = newnode;

	  if(lCrawl->prev == NULL)
	    {
	      list->head[live_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = int_update_parentLeft_list_fp(list, lCrawl->prev, newnode_parent, live_version, version);
	}
      

      
      /*      int_Node* newnode_parent = addNode(lCrawl->mod->data, live_version);
      //changed here
      
      if(lCrawl->mod->version <= version)
      newnode_parent = addNode(lCrawl->mod->data, live_version);
      else
      newnode_parent = addNode(lCrawl->data, live_version);
      
      newnode_parent->next = newnode;

      if(lCrawl->mod->prev == NULL)
      {
      list->head[live_version] = newnode_parent;
      return newnode_parent;
      }

      newnode_parent->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev, newnode_parent, live_version, version);
      */
      return newnode_parent;
    }

}



int_Node* int_update_parentRight_list_fp(int_stack_fp* list, int_Node* lCrawl, int_Node* newnode, int live_version, int version)
{
  if(lCrawl == NULL) return NULL;

  if(lCrawl->node_version > version) return NULL;
  
  if(lCrawl->mod->version == UNUSED)
    {
      lCrawl->mod->data = lCrawl->data;
      lCrawl->mod->version = live_version;
      lCrawl->mod->prev = newnode;
      //lCrawl->mod->next = lCrawl->next;
      //changed here
      lCrawl->mod->next =  int_update_parentRight_list_fp(list, lCrawl->next, lCrawl, live_version, version);

      return lCrawl;
    }
  else
    {
      int_Node* newnode_parent;
      
      if(lCrawl->mod->version <= version)
	{	  
	  newnode_parent = addNode(lCrawl->mod->data, live_version);
	  newnode_parent->prev = newnode;
	  newnode_parent->next = int_update_parentRight_list_fp(list, lCrawl->mod->next, newnode_parent, live_version, version);
	}
      else
	{
	  newnode_parent = addNode(lCrawl->data, live_version);

	  newnode_parent->prev = newnode;
	  newnode_parent->next = int_update_parentRight_list_fp(list, lCrawl->next, newnode_parent, live_version, version);
	}
      

      /*int_Node* newnode_parent = addNode(lCrawl->mod->data, live_version);
      //changed here
      if(lCrawl->mod->version <= version)
      newnode_parent = addNode(lCrawl->mod->data, live_version);
      else
      newnode_parent = addNode(lCrawl->data, live_version);

      newnode_parent->next = int_update_parentRight_list_fp(list, lCrawl->mod->next, newnode_parent, live_version, version);

      newnode_parent->prev = newnode;
      */
      return newnode_parent;
    }

}



bool int_insert_list_fp(int_stack_fp* list, int data, int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }

  int index_count = 0;
  int live_version = list->live_version;
  int_Node* newnode = addNode(data, UNUSED);

  if(version > live_version)
    {
      printf("Version does not exist\n");
      return false;
    }
      
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
 
  for(lCrawl = list->head[version], lCrawl_prev = list->head[version]; lCrawl != NULL; index_count++)
    {
      if(lCrawl != list->head[version])
	lCrawl_prev = lCrawl;
	    
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;

    }

  if(lCrawl == NULL) index_count--;
    
  if(list->head[live_version] == NULL)
    {
      list->head[live_version] = newnode;
      newnode->node_version = live_version;
      return true;
    }

  /* if(index != index_count) 
     {
     printf("Index greater than length of the list. The element will be appended at the end of the list\n");
     }
  */
  
  /*if(lCrawl_prev == list->head[version] && index == 1)
    lCrawl = lCrawl_prev;
    else if((lCrawl == NULL) && (lCrawl_prev->mod->version == UNUSED))
    lCrawl = lCrawl_prev->next;
    else if((lCrawl == NULL) && (lCrawl_prev->mod->version != UNUSED))
    lCrawl = lCrawl_prev->mod->next;
    else*/
  
  lCrawl = lCrawl_prev;  

  if(lCrawl->mod->version == UNUSED)
    {      
      live_version++;
      
      //lCrawl->mod->data = lCrawl->data;
      //lCrawl->mod->version = live_version;

      newnode->node_version = live_version;
      
      if(index != 0)
	{
	  lCrawl->mod->next = newnode;
	  lCrawl->mod->prev = lCrawl->prev;

	  newnode->next = int_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
	  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);
	}
      else
	{
	  newnode->next = lCrawl;
	  lCrawl->mod->data = lCrawl->data;
  	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = newnode;
	  lCrawl->mod->version = live_version;
	  
	  list->head[live_version] = newnode;
      	}
    }
  else
    {
      live_version++;
      
      newnode->node_version = live_version;

      if(index !=0)
	{
	  //changeed here
	  if(lCrawl->mod->version <= version)
	    {
	      newnode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
	      newnode->prev = int_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);
	    }
	  else
	    {
	      newnode->next = int_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
	      newnode->prev = int_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);
	    }
	}
      else
	{
	  int_Node* trailNode;
	  if(lCrawl->mod->version <= version)
	    {
	      trailNode = addNode(lCrawl->mod->data, live_version);
	      trailNode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next, trailNode, live_version, version);	
	    }
	  else
	    {
	      trailNode = addNode(lCrawl->data, live_version);
	      trailNode->next = int_update_parentRight_list_fp(list, lCrawl->next, trailNode, live_version, version);	
	    }

	  trailNode->prev = newnode;
	  newnode->next = trailNode;
  	  
	  list->head[live_version] = newnode;

	  /*else
	    {
	    live_version++;
      
	    newnode->node_version = live_version;

	    if(index !=0)
	    {
	    newnode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
	    newnode->prev = int_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);
	    }
	    else
	    {
	    int_Node* trailNode = addNode(lCrawl->mod->data, live_version);
	 
	    trailNode->prev = newnode;
	    trailNode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next, trailNode, live_version, version);	
	  
	    newnode->next = trailNode;
  	  
	    list->head[live_version] = newnode;
	    }
	    }*/
	}
    }
  
  list->live_version = live_version;
  return true;
}




bool int_delete_list_fp(int_stack_fp* list, int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int live_version = list->live_version;

  int_Node* lCrawl = (int_Node*) malloc(sizeof(int_Node));

  if(version > live_version)
    {
      printf("Version does not exist\n");
      return false;
    }
     
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[version] == NULL)
    {
      printf("List is empty. Cannot delete from empty list");
      return false;
    }
   
  if((list->head[version]->next == NULL) && (list->head[version]->mod->next == NULL) || (version == 0))
    {
      live_version++;
      list->head[live_version] = NULL;

      list->live_version = live_version;
      return true;
    }
  
  for(lCrawl = list->head[version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= version) && lCrawl->mod->version != UNUSED)
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
	  if((lCrawl->mod->version == UNUSED) || (lCrawl->mod->version > version))
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
		  /////////// if check
		  int_Node* newnode;
		  
		  if(lCrawl->next->mod->version <= version)
		    {
		      newnode = addNode(lCrawl->next->mod->data, live_version);
		      newnode->next = int_update_parentRight_list_fp(list, lCrawl->next->mod->next, newnode, live_version, version);
		    }
		  else
		    {
		      newnode = addNode(lCrawl->next->data, live_version);
		      newnode->next = int_update_parentRight_list_fp(list, lCrawl->next->next, newnode, live_version, version);
		    }
		  
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

		  int_Node* newnode;;

		  if(lCrawl->mod->next->mod->version <= version)
		    {
		      newnode = addNode(lCrawl->mod->next->mod->data, live_version);
		      newnode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next->mod->next, newnode, live_version, version);
		    }
		  else
		    {
		      newnode = addNode(lCrawl->mod->next->data, live_version);
		      newnode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next->next, newnode, live_version, version);
		    }
		  
		  list->head[live_version] = newnode;
		}
	    }
	  
	  list->live_version = live_version;
	  return true;
	}
    
      if((lCrawl->next == NULL) && (lCrawl->mod->version == UNUSED) || (lCrawl->mod->version > version))
	{
	  if(lCrawl->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      lCrawl->prev->mod->data = lCrawl->prev->data;
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else
	    {
	      live_version++;
	   
	      int_Node* newnode;
	      
	      if(lCrawl->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->prev->mod->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->prev->mod->prev == NULL) list->head[live_version] = newnode;
		}
	      else
		{ 
		  newnode = addNode(lCrawl->prev->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->prev->prev, newnode, live_version, version);

		  if(lCrawl->prev->prev == NULL) list->head[live_version] = newnode;
		}
	    }
	  
	  list->live_version = live_version;
	  return true;
	}
	   
      if((lCrawl->mod->next == NULL) && (lCrawl->mod->version != UNUSED) && (lCrawl->mod->version <= version))
	{
	  if(lCrawl->mod->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      lCrawl->mod->prev->mod->data = lCrawl->mod->prev->data;
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else
	    {
	      live_version++;

	      int_Node* newnode;;

	      if(lCrawl->mod->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->mod->prev->mod->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->mod->prev == NULL) list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->mod->prev->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->prev == NULL) list->head[live_version] = newnode;
		}
	    }

	  list->live_version = live_version;
	  return true;
	}
        

      if((lCrawl->mod->version == UNUSED) || (lCrawl->mod->version > version))
	{
	  if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {  
	      live_version++;
	      //printf("1\n");
	      lCrawl->prev->mod->data = lCrawl->prev->data;
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      lCrawl->next->mod->data = lCrawl->next->data;
	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = lCrawl->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version != UNUSED))
	    {
	      live_version++;
	      //printf("2\n");
	      int_Node* newnode;
	      
	      lCrawl->prev->mod->data = lCrawl->prev->data;
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = newnode;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      if(lCrawl->next->mod->version <= version)
		{
		  newnode = addNode(lCrawl->next->mod->data, live_version);
		  newnode->next = int_update_parentRight_list_fp(list, lCrawl->next->mod->next, newnode, live_version, version);
		}
	      else
		{
		  newnode = addNode(lCrawl->next->data, live_version);
		  newnode->next = int_update_parentRight_list_fp(list, lCrawl->next->next, newnode, live_version, version);
		}
	      
	      newnode->prev = lCrawl->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->prev->mod->version != UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {
	      live_version++;
	      //printf("3\n");
	      int_Node* newnode;
	      
	      lCrawl->next->mod->data = lCrawl->next->data;
	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = newnode;

	      if(lCrawl->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->prev->mod->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->prev->mod->prev == NULL)  list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->prev->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->prev->prev, newnode, live_version, version);

		  if(lCrawl->prev->prev == NULL)  list->head[live_version] = newnode;
		}
	      
	      newnode->next = lCrawl->next;
	    }
	  else
	    {
	      live_version++;
	      //printf("4\n");       
	      int_Node* newnode_prev;
	      int_Node* newnode_next;

	      if(lCrawl->prev->mod->version <= version)
		{
		  newnode_prev = addNode(lCrawl->prev->mod->data, live_version);
		  newnode_prev->prev = int_update_parentLeft_list_fp(list, lCrawl->prev->mod->prev, newnode_prev, live_version, version);

		  if(lCrawl->prev->mod->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(lCrawl->prev->data, live_version);
		  newnode_prev->prev = int_update_parentLeft_list_fp(list, lCrawl->prev->prev, newnode_prev, live_version, version);

		  if(lCrawl->prev->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      
	      if(lCrawl->next->mod->version <= version)
		{
		  newnode_next = addNode(lCrawl->next->mod->data, live_version);
		  newnode_next->next = int_update_parentRight_list_fp(list, lCrawl->next->mod->next, newnode_next, live_version, version);
		}
	      else
		{
		  newnode_next = addNode(lCrawl->next->data, live_version);
		  newnode_next->next = int_update_parentRight_list_fp(list, lCrawl->next->next, newnode_next, live_version, version);
		}

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	    }
	}
      else
	{
	  if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {  
	      live_version++;
	      //printf("5\n");  
	      lCrawl->mod->prev->mod->data = lCrawl->mod->prev->data;
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      lCrawl->mod->next->mod->data = lCrawl->mod->next->data;
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version != UNUSED))
	    {
	      live_version++;
	      //printf("6\n"); 	      	  
	      int_Node* newnode;

	      lCrawl->mod->prev->mod->data = lCrawl->mod->prev->data;
	      lCrawl->mod->prev->mod->version = live_version;
	      
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;
	      lCrawl->mod->prev->mod->next = newnode; 
	     
	      
	      if(lCrawl->mod->next->mod->version <= version)
		{
		  newnode = addNode(lCrawl->mod->next->mod->data, live_version);
		  newnode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next->mod->next, newnode, live_version, version);
		}
	      else
		{
		  newnode = addNode(lCrawl->mod->next->data, live_version);
		  newnode->next = int_update_parentRight_list_fp(list, lCrawl->mod->next->next, newnode, live_version, version);
		}

	      newnode->prev = lCrawl->mod->prev;
	      
	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->mod->prev->mod->version != UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {
	      live_version++;
	      //printf("7\n");	      	      
	      int_Node* newnode;       

	      lCrawl->mod->next->mod->data = lCrawl->mod->next->data;
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = newnode;

	      if(lCrawl->mod->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->mod->prev->mod->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->mod->prev == NULL)  list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->mod->prev->data, live_version);
		  newnode->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->prev == NULL)  list->head[live_version] = newnode;
		}

	      newnode->next = lCrawl->mod->next;
	    }
	  else
	    {
	      live_version++;
	      //printf("8\n");	        
	      int_Node* newnode_prev;
	      int_Node* newnode_next;

	      if(lCrawl->mod->prev->mod->version <= version)
		{
		  newnode_prev = addNode(lCrawl->mod->prev->mod->data, live_version);
		  newnode_prev->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev->mod->prev, newnode_prev, live_version, version);

		  if(lCrawl->mod->prev->mod->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(lCrawl->mod->prev->data, live_version);
		  newnode_prev->prev = int_update_parentLeft_list_fp(list, lCrawl->mod->prev->prev, newnode_prev, live_version, version);

		  if(lCrawl->mod->prev->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      
	      if(lCrawl->mod->next->mod->version <= version)
		{
		  newnode_next = addNode(lCrawl->mod->next->mod->data, live_version);
		  newnode_next->next = int_update_parentRight_list_fp(list, lCrawl->mod->next->mod->next, newnode_next, live_version, version);
		}
	      else
		{
		  newnode_next = addNode(lCrawl->mod->next->data, live_version);
		  newnode_next->next = int_update_parentRight_list_fp(list, lCrawl->mod->next->next, newnode_next, live_version, version);
		}

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;
	    }
	  	  
	}
      
      list->live_version = live_version;
    }
  return true;
}


bool int_stack_isEmpty_fp(int_stack_fp* stack, int version)
{
  if(stack->head[version] == NULL) return true;
  else false;
}

bool int_stack_push_fp(int_stack_fp* stack, int data, int version)
{
  return (int_insert_list_fp(stack, data, 0, version));
}

int int_stack_pop_fp(int_stack_fp* stack, int version)
{
  return int_delete_list_fp(stack, 0, version);
}
