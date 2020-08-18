#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

map_Node* addNode(char input_key[], char input_value[])
{
  //char key[STR_SIZE], value[STR_SIZE];
  
  map_Node* newnode = (map_Node*) malloc(sizeof(map_Node));
  // newnode->key = malloc(sizeof(STR_SIZE));
  // newnode->value = malloc(sizeof(STR_SIZE));
  strcpy(newnode->key, input_key);
  strcpy(newnode->value, input_value);
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (map_Mod*) malloc(sizeof(map_Mod));
  //  newnode->mod->key = malloc(sizeof(STR_SIZE));
  //  newnode->mod->value = malloc(sizeof(STR_SIZE));
  strcpy(newnode->mod->key, JUNK);
  strcpy(newnode->mod->value, JUNK);
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
  
  return newnode;
}



map_pp* map_init_pp()
{
  map_pp* newlist = (map_pp*) malloc(sizeof(map_pp));

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


void map_search_pp(map_pp* list, char str[])
{
    
  char search_key[STR_SIZE];
  int version;

  sscanf(str, "%[^,],%d", search_key, &version);
    
  if(list->live_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }

  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));

  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return;
    }

  printf("Searching list of version %d\n", version);
	
  for(lCrawl = list->head[version]; lCrawl != NULL; )
    {
      if((lCrawl->mod->version <= version) && (lCrawl->mod->version != UNUSED))
	{
	  if(!strcmp(lCrawl->mod->key, search_key))
	    {
	      printf("Key found\nKey : %s, Value : %s\n", lCrawl->mod->key, lCrawl->mod->value);
	      return;
	    }
	  lCrawl = lCrawl->mod->next;
	}
      else
	{
	  if(!strcmp(lCrawl->key, search_key))
	    {
	      printf("Key found\nKey : %s, Value : %s\n", lCrawl->key, lCrawl->value);
	      return;
	    }

	  lCrawl = lCrawl->next;
	}
    }
  
  printf("Key not found\n");
}





void map_print_pp(map_pp* list, int version)
{
  if(list->live_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
  
  map_Node* pCrawl = (map_Node*) malloc(sizeof(map_Node));

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
	  printf("Key : %s, Value : %s\n", pCrawl->mod->key, pCrawl->mod->value);
	  pCrawl = pCrawl->mod->next;
	}
      else
	{
	  printf("Key : %s, Value : %s\n", pCrawl->key, pCrawl->value);
	  pCrawl = pCrawl->next;
	}
    }
  
  printf("NULL\n");
}



map_Node* map_update_parentLeft_list_pp(map_pp* list, map_Node* lCrawl, map_Node* newnode, int live_version)
{

  if(lCrawl == NULL) return NULL;

  if(lCrawl->mod->version == UNUSED)
    {
      strcpy(lCrawl->mod->key, lCrawl->key);
      strcpy(lCrawl->mod->value,  lCrawl->value);
      
      lCrawl->mod->version = live_version;
      lCrawl->mod->next = newnode;
      lCrawl->mod->prev = lCrawl->prev;

      list->head[live_version] = list->head[live_version-1];
      return lCrawl;
    }
  else
    {

      map_Node* newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value);
    
      newnode_parent->next = newnode;

      if(lCrawl->mod->prev == NULL)
	{
	  list->head[live_version] = newnode_parent;
	  return newnode_parent;
	}
      
      newnode_parent->prev = map_update_parentLeft_list_pp(list, lCrawl->mod->prev, newnode_parent, live_version);
      return newnode_parent;
    }
}



map_Node* map_update_parentRight_list_pp(map_pp* list, map_Node* lCrawl, map_Node* newnode, int live_version)
{

  if(lCrawl == NULL) return NULL;
    
  if(lCrawl->mod->version == UNUSED)
    {
      strcpy(lCrawl->mod->key, lCrawl->key);
      strcpy(lCrawl->mod->value, lCrawl->value);
            
      lCrawl->mod->version = live_version;
      lCrawl->mod->prev = newnode;
      lCrawl->mod->next = lCrawl->next;

      return lCrawl;
    }
  else
    {

      map_Node* newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value);
 
      newnode_parent->prev = newnode;

      // if(lCrawl->mod->next == NULL) return newnode_parent;
	
      newnode_parent->next = map_update_parentRight_list_pp(list, lCrawl->mod->next, newnode_parent, live_version);
    }

}



bool map_insert_pp(map_pp* list, char str[], int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;
  char key[STR_SIZE], value[STR_SIZE];

  sscanf(str, "%[^,],%[^,]", key,value);
  
  map_Node* newnode = addNode(key, value);
  
  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));
  map_Node* lCrawl_prev = (map_Node*) malloc(sizeof(map_Node));
  
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
      
      strcpy(lCrawl->mod->key, lCrawl->key);
      strcpy(lCrawl->mod->value, lCrawl->value);
      
      lCrawl->mod->version = live_version;

      if(index != 0)
	{
	  lCrawl->mod->next = newnode;
	  lCrawl->mod->prev = lCrawl->prev;

	  newnode->next = map_update_parentRight_list_pp(list, lCrawl->next, newnode, live_version);
	  newnode->prev = map_update_parentLeft_list_pp(list, lCrawl, newnode, live_version);
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
	  newnode->next = map_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	  newnode->prev = map_update_parentLeft_list_pp(list, lCrawl, newnode, live_version);
	}
      else
	{
	  
	  map_Node* trailNode = addNode(lCrawl->mod->key, lCrawl->mod->value);
	  trailNode->next = lCrawl->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[live_version] = newnode;
	}
    }
  
  list->live_version = live_version;
  return true;
}



bool map_update_pp(map_pp* list, char str[], int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;

  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));
  
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
      map_insert_pp(list, str, index);
    }
  else
    {     
      if(lCrawl->mod->version == UNUSED)
	{
	  live_version++;

	  char key[STR_SIZE], value[STR_SIZE];

	  sscanf(str, "%[^,],%[^,]", key,value);
	      
	  strcpy(lCrawl->mod->key, key);
	  strcpy(lCrawl->mod->value, value);
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
	      char key[STR_SIZE], value[STR_SIZE];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      map_Node* newnode = addNode(key, value);

	      newnode->next = map_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	      newnode->prev = map_update_parentLeft_list_pp(list, lCrawl->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      char key[STR_SIZE], value[STR_SIZE];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      map_Node* newnode = addNode(key, value);

	      newnode->next = map_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	      list->head[live_version] = newnode;
	    }
	}

      list->live_version = live_version;
    }
  return true;
}





bool map_delete_pp(map_pp* list, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int live_version = list->live_version;

  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));
  
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
		
		  strcpy(lCrawl->next->mod->key, lCrawl->next->key);
		  strcpy(lCrawl->next->mod->value, lCrawl->next->value);
		  
		  lCrawl->next->mod->version = live_version;

		  lCrawl->next->mod->next = lCrawl->next->next;
		  lCrawl->next->mod->prev = lCrawl->prev;

		  list->head[live_version] = lCrawl->next;
		}
	      else
		{
		  live_version++;

		  map_Node* newnode = addNode(lCrawl->next->mod->key, lCrawl->next->mod->value);

		  newnode->next = map_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode, live_version);
	  	  
		  list->head[live_version] = newnode;
		}
	    }
	  else
	    {
	      if(lCrawl->mod->next->mod->version == UNUSED)
		{  
		  live_version++;
		
		  strcpy(lCrawl->mod->next->mod->key, lCrawl->mod->next->key);
		  strcpy(lCrawl->mod->next->mod->value, lCrawl->mod->next->value);
		  
		  lCrawl->mod->next->mod->version = live_version;

		  lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
		  lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

		  list->head[live_version] = lCrawl->mod->next;
		}
	      else
		{
		  live_version++;

		  map_Node* newnode = addNode(lCrawl->mod->next->mod->key, lCrawl->mod->next->mod->value);

		  newnode->next = map_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode, live_version);
	  	  
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

	      strcpy(lCrawl->prev->mod->key, lCrawl->prev->key);
	      strcpy(lCrawl->prev->mod->value, lCrawl->prev->value);
	      
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else
	    {
	      live_version++;

	      map_Node* newnode = addNode(lCrawl->prev->mod->key,lCrawl->prev->mod->value);
	      
	      newnode->prev = map_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode, live_version);
	    }
 
	  list->live_version = live_version;
	  return true;
	}
      
      if((lCrawl->mod->next == NULL) && (lCrawl->mod->version != UNUSED))
	{
	  if(lCrawl->mod->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      strcpy(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->key);
	      strcpy(lCrawl->mod->prev->mod->value, lCrawl->mod->prev->value);

	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else
	    {
	      live_version++;

	      map_Node* newnode = addNode(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->mod->value);
	      
	      newnode->prev = map_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode, live_version);
	    }

	  list->live_version = live_version;
	  return true;
	}
      

      if(lCrawl->mod->version == UNUSED)
	{
	  if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {  
	      live_version++;

	      strcpy(lCrawl->prev->mod->key, lCrawl->prev->key);
	      strcpy(lCrawl->prev->mod->value, lCrawl->prev->value);
	      
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      strcpy(lCrawl->next->mod->key, lCrawl->next->key);
	      strcpy(lCrawl->next->mod->value, lCrawl->next->value);
	       
	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = lCrawl->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version != UNUSED))
	    {
	      live_version++;

	      map_Node* newnode = addNode(lCrawl->next->mod->key, lCrawl->next->mod->value);
	      
	      strcpy(lCrawl->prev->mod->key, lCrawl->prev->key);
	      strcpy(lCrawl->prev->mod->value, lCrawl->prev->value);
	      
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = newnode;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      newnode->prev = lCrawl->prev;		
	      newnode->next = map_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode, live_version);
	  	  
	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->prev->mod->version != UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {
	      live_version++;

	      map_Node* newnode = addNode(lCrawl->prev->mod->key, lCrawl->prev->mod->value);
	      
	      strcpy(lCrawl->next->mod->key, lCrawl->next->key);
	      strcpy(lCrawl->next->mod->value, lCrawl->next->value);
	      
	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = newnode;

	      newnode->next = lCrawl->next;
	      newnode->prev = map_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      live_version++;
        
	      map_Node* newnode_prev = addNode(lCrawl->prev->mod->key, lCrawl->prev->mod->value);
	      map_Node* newnode_next = addNode(lCrawl->next->mod->key, lCrawl->next->mod->value);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = map_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode_prev, live_version);
	      newnode_next->next = map_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode_next, live_version);
 	    }
	}
      else
	{
	  if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {  
	      live_version++;

	      strcpy(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->key);
	      strcpy(lCrawl->mod->prev->mod->value, lCrawl->mod->prev->value);
	      
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      strcpy(lCrawl->mod->next->mod->key, lCrawl->mod->next->key);
	      strcpy(lCrawl->mod->next->mod->value, lCrawl->mod->next->value);
	      
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version != UNUSED))
	    {
	      live_version++;
	      	  
	      map_Node* newnode = addNode(lCrawl->mod->next->mod->key, lCrawl->mod->next->mod->value);
	  
	      strcpy(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->key);
	      strcpy(lCrawl->mod->prev->mod->value, lCrawl->mod->prev->value);

	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = newnode;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;
	      
	      newnode->prev = lCrawl->mod->prev;
	      
	      newnode->next = map_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode, live_version);
	  	  
	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->mod->prev->mod->version != UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {
	      live_version++;
	      
	      map_Node* newnode = addNode(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->mod->value);       

	      strcpy(lCrawl->mod->next->mod->key, lCrawl->mod->next->key);
	      strcpy(lCrawl->mod->next->mod->value, lCrawl->mod->next->value);
	      
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = newnode;

	      newnode->next = lCrawl->mod->next;

	      newnode->prev = map_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      live_version++;
	      
	      map_Node* newnode_prev = addNode(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->mod->value);
	      map_Node* newnode_next = addNode(lCrawl->mod->next->mod->key, lCrawl->mod->next->mod->value);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = map_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode_prev, live_version);
	      newnode_next->next = map_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode_next, live_version);
	    }

	}
      
      list->live_version = live_version;
    }
  return true;
}

